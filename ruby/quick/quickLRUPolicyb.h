
#ifndef quickLRUPolicyb_H
#define quickLRUPolicyb_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true LRU replacement policy */
#define DEBUG_SET 0
#define DEBUGED 1240

class quickLRUPolicyb : public AbstractReplacementPolicyQuick {
 public:

  quickLRUPolicyb(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickLRUPolicyb();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  void replacementLower(Index set, Index way)  ;
  int posInSubset(int set, int index, CacheEntryQuick &p) ;
  uint whatSubset(CacheEntryQuick &a) ;
  bool checkSet(Index set);

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

};


//SOLO PARA QUE COMPILE

inline
quickLRUPolicyb::quickLRUPolicyb(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
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
	
	for(int i=0; i< RubyConfig::numberOfProcsPerChip(); i++) {
		m_posPILAth1st[i] = new Histogram(1, m_assoc+2);
		m_posPILAthRe[i] = new Histogram(1, m_assoc+2);
		m_posPILAthLRU[i] = new Histogram(1, m_assoc+2);
		m_posPILAthLRUre[i] = new Histogram(1, m_assoc+2);
		m_posPILAthLRU1st[i] = new Histogram(1, m_assoc+2);
	}

	cerr << "constructor LRU" << endl;
	
	m_cache = a;
}

inline
quickLRUPolicyb::~quickLRUPolicyb() {
}

inline 
void quickLRUPolicyb::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();

  uint ant = m_LRUorder[set][index];
  
  //if(DEBUG_SET && set==DEBUGED) {
  //	if(DEBUG_SET && set==DEBUGED) cerr << "HIT at " << index << " LRUpos: " << ant << endl;
  //  for(int i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << "\t" << (*m_cache)[set][i] << endl;
  //}

  
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
	int flag=0;

  if(ant == 0) {
  	for(uint i=0; i<m_assoc; i++) {
  		m_LRUorder[set][i]= m_LRUorder[set][i]>ant ? m_LRUorder[set][i]+1 : 0;
  		if(g_INCLUSION_L3 && m_LRUorder[set][i]==17 && i!=index) { 
  			//if(DEBUG_SET && set==DEBUGED);
  			//cerr << this << " HAY uno que se ha pasado: " << i << " " << (*m_cache)[set][i].m_Address <<  endl;
        		if((*m_cache)[set][i].m_Sharers.count()==0) {
      				overAssoc = i; 
    	  			overAssocAddress = (*m_cache)[set][i].m_Address;
    	  		}
    	  		else { //special case: we do not want to replace a private element. 
    	  			flag=17;
    	  		}	
  		}
  	}
  	m_LRUorder[set][index]=1;
  }
	else {
    	for (unsigned int i=0; i < m_assoc; i++) {
    		uint aux= m_LRUorder[set][i];
      		m_LRUorder[set][i]= aux<ant && aux != 0 ? aux+1 : aux;
      		if(g_INCLUSION_L3 && m_LRUorder[set][i]==17 && i!=index) {
        //cerr << this << " HAY uno que se ha pasado2: " << i << " " << (*m_cache)[set][i].m_Address <<  endl;
        //cerr << this << " HIT en: " << ant << " " << (*m_cache)[set][ant].m_Address <<  endl;
        		if((*m_cache)[set][i].m_Sharers.count()==0) {
      				overAssoc = i; 
    	  			overAssocAddress = (*m_cache)[set][i].m_Address;
    	  		}
    	  		else { //special case: we do not want to replace a private element. 
    	  			flag=17;
    	  		}	
      		}
	    }
	    m_LRUorder[set][index]=1;
	    
  	}

	if(flag) {
		int invLRU[65];
	
		//a reverse index is created
		//invLRU keeps the way index of the element with LRU pos
		for (unsigned int i=0; i < m_assoc; i++) {
			invLRU[m_LRUorder[set][i]] = i;
		}
		do {
			m_LRUorder[set][invLRU[flag--]]--;
		} while((*m_cache)[set][invLRU[flag]].m_Sharers.count() != 0);
		assert(flag != 0 );
		m_LRUorder[set][invLRU[flag]] += 17 - flag; //it increments the number of no private elements at the end of the 16associativity
		assert(m_LRUorder[set][invLRU[flag]] == 17 );
		//the correct victim is notified
		if(invLRU[flag] != index) {
			overAssoc = invLRU[flag]; 
			overAssocAddress = (*m_cache)[set][invLRU[flag]].m_Address;
		}
		//cerr << this << " Reconversion exitosa" << endl;
	}
  
  if(DEBUG_SET && set==DEBUGED) {
  	if(DEBUG_SET && set==DEBUGED) cerr << "HIT at " << index << " LRUpos: " << ant << endl;
    for(uint i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << "\t" << (*m_cache)[set][i] << endl;
  }

  if(ant>16) insideAsoc= 2;
  else insideAsoc= 1;
  
  //assert(checkSet(set));
}
inline
Index quickLRUPolicyb::getVictim(Index set, uint proc) const {


  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);


  //  assert(m_assoc != 0);
  //Buscamod la pos con el valor LRU mayor y que no esté en las privadas
	int max=-1, idx=0; 
	for (uint i=0; i < m_assoc; i++) {
  		if(m_LRUorder[set][i] > max && (*m_cache)[set][i].m_Sharers.count() == 0) {
  			max = m_LRUorder[set][i];
  			idx = i;
  		}
  	}
  	if(max != -1) return idx;
  	
	for (uint i=0; i < m_assoc; i++) {
  		if(m_LRUorder[set][i] == m_assoc) {
  			return i; 
  		}
  	}  
  	cerr << "SET: " << set << " m_version: " << endl;
  	for(uint i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << "\t" << (*m_cache)[set][i] << endl;
  	assert(0);

}

inline int quickLRUPolicyb::posInSubset(int set, int index, CacheEntryQuick &p) {


	
	int blkSubset = whatSubset(p);
	int blkLRUpos = m_LRUorder[set][index];
	int blkSubsetPos = 1;
	
	for(uint i=0; i<m_assoc; i++) {
		
		if(m_LRUorder[set][i] < blkLRUpos && m_LRUorder[set][i] > 0 && whatSubset((*m_cache)[set][i])==blkSubset)
			blkSubsetPos++;
	}
	return blkSubsetPos;
 
}

inline uint quickLRUPolicyb::whatSubset(CacheEntryQuick& a) {
	if(!a.m_NRU) return 0;
	else return 1;
}

inline void quickLRUPolicyb::replacementLower(Index set, Index way)  {
return ;
if(DEBUG_SET && set==DEBUGED) { cerr << this << " LRUway es " << m_LRUorder[set][way] << endl; }
	uint aux = m_LRUorder[set][way];

	for (unsigned int i=0; i < m_assoc; i++) {
		CacheEntryQuick &p = (*m_cache)[set][i];
		
		int n=p.m_Sharers.count();
		
		if((m_LRUorder[set][i] > aux) && (n>0 || p.m_onFly)) {
		
			m_LRUorder[set][i]--;
			m_LRUorder[set][way]++;
			
			if(DEBUG_SET && set==DEBUGED) { cerr << "tocamos " << i << endl; }
		} else
		{
			if(DEBUG_SET && set==DEBUGED) { cerr << "no tocamos " << i <<  " "<< p.m_Sharers.count() << " " << p.m_Sharers << " " << m_LRUorder[set][i] << endl; }
		}
	}  
	
	  if(DEBUG_SET && set==DEBUGED) {
  	if(DEBUG_SET && set==DEBUGED) cerr << "replaced at " << way  << endl;
    for(uint i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << "\t" << (*m_cache)[set][i] << endl;
  }
  //if( set==17) for(uint i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << "\t" << (*m_cache)[set][i] << endl;
  assert(checkSet(set));
}

inline
void quickLRUPolicyb::printStats(ostream& out, char* name) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRUPolicyb::printStats" << endl;

  out << "HistoLRU gral" << name << " " << *m_posPILALRU << endl;  
  for(int i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "HistoLRU "<< name << " thread " << i << "\t" << *m_posPILAthLRU[i] << endl;

  out << "Histo1st gral " << name << " " << *m_posPILA1st << endl;  
  for(int i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "Histo1st "<< name << " thread " << i << "\t" << *m_posPILAth1st[i] << endl;

  out << "HistoRe gral " << name << " " << *m_posPILARe << endl;  
  for(int i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "HistoRe "<< name << " thread " << i << "\t" << *m_posPILAthRe[i] << endl;
  
  out << "Histo1stI gl " << name << " " << *m_posPILALRU1st << endl;  
  for(int i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "Histo1stI "<< name << " thread " << i << "\t" << *m_posPILAthLRU1st[i] << endl;

  out << "HistoReI gl " << name << " " << *m_posPILALRUre << endl;  
  for(int i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "HistoReI t"<< name << " thread " << i << "\t" << *m_posPILAthLRUre[i] << endl;

cerr << "quickLRUPolicybPILA::printStats" << endl;

}

inline
void quickLRUPolicyb::printStats(ostream& out) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRUPolicyb::printStats" << endl;
}

inline
void quickLRUPolicyb::clearStats() 
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

inline
bool quickLRUPolicyb::checkSet(Index set) {
	bool ret= true;
	bool present[65];
	
	for (unsigned int i=0; i < m_assoc+1; i++) 
		present[i] = false;
	
	for (unsigned int i=0; i < m_assoc; i++) {
		if(m_LRUorder[set][i]!=0 && present[m_LRUorder[set][i]]) { 
			ret= false;
			cerr  << "pos maligna " << i << " "  << m_LRUorder[set][i] <<  endl;
		}
		else present[m_LRUorder[set][i]] = true;
	}
	
	if(!ret) {
		cerr  << "El conjunto maligno es el " << set <<  endl;
    	for(uint i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << "\t" << (*m_cache)[set][i] << endl;
  	}
	return ret;
}

#endif // PSEUDOLRUBITS_H
