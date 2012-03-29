
#ifndef quickLRUPolicy_H
#define quickLRUPolicy_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"




/* Simple true LRU replacement policy */
#define DEBUG_SET 0
#define DEBUGED 234

 class CacheMgr;

class quickLRUPolicy : public AbstractReplacementPolicyQuick {
 public:

  quickLRUPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a, CacheMgr* b);
  quickLRUPolicy(Index num_sets, Index assoc, CacheMemoryQuick *a, CacheMgr* b);
  ~quickLRUPolicy();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  void replacementLower(Index set, Index way)  ;
  int posInSubset(int set, int index, CacheEntryQuick &p) ;
  uint whatSubset(CacheEntryQuick &a) ;

  void printStats(ostream& out, char* name) ;
  void printStats(ostream& out) ;
  void clearStats() ;
  Vector<Vector<CacheEntryQuick> > *m_cache;

  uint** m_LRUorder;
  
  Histogram  *m_posPILALRU;
  Histogram  **m_posPILAthLRU;
  Histogram  *m_posPILALRUre;
  Histogram  **m_posPILAthLRUre;
  Histogram  *m_posPILALRU1st;
  Histogram  **m_posPILAthLRU1st;
  
  Histogram  *m_posPILA1st;
  Histogram  **m_posPILAth1st;

  Histogram  *m_posPILARe;
  Histogram  **m_posPILAthRe;
  
  CacheMgr* cacheMgr_ptr;


};


//SOLO PARA QUE COMPILE

inline
quickLRUPolicy::quickLRUPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a, CacheMgr* b)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
	m_LRUorder = new uint* [num_sets] ();
	for (unsigned int i=0; i < num_sets; i++) {
		m_LRUorder[i] = new uint [m_assoc] ();
		for (unsigned int j=0; j < m_assoc; j++) m_LRUorder[i][j] = 0;
	}

	m_posPILALRU = new Histogram(1, m_assoc+2);
	m_posPILAthLRU = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILALRUre = new Histogram(1, m_assoc+2);
	m_posPILAthLRUre = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILALRU1st = new Histogram(1, m_assoc+2);
	m_posPILAthLRU1st = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILA1st = new Histogram(1, m_assoc+2);
	m_posPILAth1st = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILARe = new Histogram(1, m_assoc+2);
	m_posPILAthRe = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	
	for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) {
		m_posPILAth1st[i] = new Histogram(1, m_assoc+2);
		m_posPILAthRe[i] = new Histogram(1, m_assoc+2);
		m_posPILAthLRU[i] = new Histogram(1, m_assoc+2);
		m_posPILAthLRUre[i] = new Histogram(1, m_assoc+2);
		m_posPILAthLRU1st[i] = new Histogram(1, m_assoc+2);
	}

	cerr << "constructor LRU" << endl;
	
	m_cache = a;
	cacheMgr_ptr = b;
}


inline
quickLRUPolicy::~quickLRUPolicy() {
}


inline
void quickLRUPolicy::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);
	
  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();

  int ant = m_LRUorder[set][index];
  
  if(DEBUG_SET && set==DEBUGED) {
  	if(DEBUG_SET && set==DEBUGED) cerr << "HIT at " << index << " LRUpos: " << ant << endl;
    for(int i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << "\t" << (*m_cache)[set][i] << endl;
  }

  
  if(time > 1) {
    m_posPILAthLRU[proc]->add(ant);
  	m_posPILALRU->add(ant);
  	if(DEBUG_SET && set==DEBUGED)cerr << this << "LRU at " << ant << endl;
  	
  	 CacheEntryQuick &p = (*m_cache)[set][index];
  	   	 
  	 int pos = posInSubset(set, index, p);
  	if(p.m_NRU) {
  		m_posPILAthRe[proc]->add(pos);
  		m_posPILARe->add(pos);
  		
  		m_posPILALRUre->add(ant);
  		m_posPILAthLRUre[proc]->add(ant);
  		
  		if(DEBUG_SET && set==DEBUGED)cerr << this << " reuse at " << pos << endl;
  	}
  	else {
  		m_posPILAth1st[proc]->add(pos);
  		m_posPILA1st->add(pos);
  		
   		m_posPILAthLRU1st[proc]->add(ant);
  		m_posPILALRU1st->add(ant);

  		if(DEBUG_SET && set==DEBUGED)cerr << this << " 1st use at " << pos << endl;
  	}
  	if(ant<17) p.m_NRU = 1;
  }

  //inicializacion
  if(ant == 0) {
  	for(int i=0; i<m_assoc; i++) {
  		m_LRUorder[set][i]= m_LRUorder[set][i]>ant ? m_LRUorder[set][i]+1 : 0;
  		if(g_INCLUSION_L3 && m_LRUorder[set][i]==17) { 
  			overAssoc=i; 
  			overAssocAddress=(*m_cache)[set][i].m_Address; 
  		}  // cacheMgr_ptr->invalidateCopies((*m_cache)[set][index].m_Address);
  	}
  }
  else {
    for (unsigned int i=0; i < m_assoc; i++) {
    	int aux= m_LRUorder[set][i];
    //m_LRUorder[set][i]= m_LRUo;rder[set][i]==m_assoc ? m_LRUorder[set][i] : m_LRUorder[set][i]+1;
     	m_LRUorder[set][i]= aux<=ant && aux != 0 ? aux+1 : aux;
      	if(g_INCLUSION_L3 && m_LRUorder[set][i]==17 && i!=index) { 
      		overAssoc=i; 
      		overAssocAddress=(*m_cache)[set][i].m_Address; 
      	}
    }
  }


  m_LRUorder[set][index]=1;
  
  if(ant>16) insideAsoc= 2;
  else insideAsoc= 1;
  
  return;
}


inline
Index quickLRUPolicy::getVictim(Index set, uint proc) const {


  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);


  //  assert(m_assoc != 0);

  for (unsigned int i=0; i < m_assoc; i++) {
  	if(m_LRUorder[set][i] == m_assoc) {
  		return i; 
  	}
  }  
  cerr << "SET: " << set << " m_version: " << endl;
  for(int i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << "\t" << (*m_cache)[set][i] << endl;
  assert(0);

}

inline int quickLRUPolicy::posInSubset(int set, int index, CacheEntryQuick &p) {


	
	int blkSubset = whatSubset(p);
	int blkLRUpos = m_LRUorder[set][index];
	int blkSubsetPos = 1;
	
	for(int i=0; i<m_assoc; i++) {
		
		if(m_LRUorder[set][i] < blkLRUpos && m_LRUorder[set][i] > 0 && whatSubset((*m_cache)[set][i])==blkSubset)
			blkSubsetPos++;
	}
	return blkSubsetPos;
 
}

inline uint quickLRUPolicy::whatSubset(CacheEntryQuick& a) {
	if(!a.m_NRU) return 0;
	else return 1;
}

inline void quickLRUPolicy::replacementLower(Index set, Index way)  {
}

inline
void quickLRUPolicy::printStats(ostream& out, char* name) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRUPolicy::printStats" << endl;

  out << "HistoLRU gl" << name << " " << *m_posPILALRU << endl;  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "HistoLRU "<< name << " thread " << i << "\t" << *m_posPILAthLRU[i] << endl;

  out << "Histo1st gl " << name << " " << *m_posPILA1st << endl;  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "Histo1st "<< name << " thread " << i << "\t" << *m_posPILAth1st[i] << endl;

  out << "HistoRe gl " << name << " " << *m_posPILARe << endl;  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "HistoRe t"<< name << " thread " << i << "\t" << *m_posPILAthRe[i] << endl;

  out << "Histo1stI gl " << name << " " << *m_posPILALRU1st << endl;  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "Histo1stI "<< name << " thread " << i << "\t" << *m_posPILAthLRU1st[i] << endl;

  out << "HistoReI gl " << name << " " << *m_posPILALRUre << endl;  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "HistoReI t"<< name << " thread " << i << "\t" << *m_posPILAthLRUre[i] << endl;
  
cerr << "quickLRUPolicyPILA::printStats" << endl;

}

inline
void quickLRUPolicy::printStats(ostream& out) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRUPolicy::printStats" << endl;
}

inline
void quickLRUPolicy::clearStats() 
{

	m_posPILALRU->clear(1, m_assoc+2);
	m_posPILA1st->clear(1, m_assoc+2);
	m_posPILARe->clear(1, m_assoc+2);
	m_posPILALRUre->clear(1, m_assoc+2);
	m_posPILALRU1st->clear(1, m_assoc+2);
	
	for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) {
		m_posPILAth1st[i]->clear(1, m_assoc+2);
		m_posPILAthRe[i]->clear(1, m_assoc+2);
		m_posPILAthLRU[i]->clear(1, m_assoc+2);
		m_posPILAthLRUre[i]->clear(1, m_assoc+2);
		m_posPILAthLRU1st[i]->clear(1, m_assoc+2);
	}
}
#endif // PSEUDOLRUBITS_H
