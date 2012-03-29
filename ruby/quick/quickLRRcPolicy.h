
#ifndef quickLRRcPolicy_H
#define quickLRRcPolicy_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheMemoryQuick.h"

/* two lists completely sorted by reuse order and NO touch in private replacement  */

class quickLRRcPolicy : public AbstractReplacementPolicyQuick {
 public:

  quickLRRcPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickLRRcPolicy();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  void replacementLower(Index set, Index way)  ;
  uint whatSubSet(CacheEntryQuick &a) const;
  int posInSubset(int set, int index, CacheEntryQuick &p) ;
  uint whatSubset(CacheEntryQuick &a) ;
  void printStats(ostream& out, char* name) ;
  void printStats(ostream& out) ;
  void clearStats() ;
  
  Vector<Vector<CacheEntryQuick> > *m_cache;
    Vector<uint64> m_nH [2];
  Vector<uint64> m_nTH;

  uint** m_LRUorder;
  
  Histogram  *m_posPILALRU;
  Histogram  **m_posPILAthLRU;
  
  Histogram  *m_posPILA1st;
  Histogram  **m_posPILAth1st;

  Histogram  *m_posPILARe;
  Histogram  **m_posPILAthRe;

};


//SOLO PARA QUE COMPILE

inline
quickLRRcPolicy::quickLRRcPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_cache = a;
  m_nH[0].setSize(RubyConfig::numberOfProcsPerChip());
  m_nH[1].setSize(RubyConfig::numberOfProcsPerChip());
  m_nTH.setSize(RubyConfig::numberOfProcsPerChip());
  
  for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
  	for (int j = 0; j < 2; j++) m_nH[j][i]= 0;
  	m_nTH[i] = 0;
  }
	m_LRUorder = new uint* [num_sets] ();
	for (unsigned int i=0; i < num_sets; i++) {
		m_LRUorder[i] = new uint [m_assoc] ();
		for (unsigned int j=0; j < m_assoc; j++) m_LRUorder[i][j] = 0;
	}

	m_posPILALRU = new Histogram(1, m_assoc+2);
	m_posPILAthLRU = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILA1st = new Histogram(1, m_assoc+2);
	m_posPILAth1st = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILARe = new Histogram(1, m_assoc+2);
	m_posPILAthRe = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	
	for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) {
		m_posPILAth1st[i] = new Histogram(1, m_assoc+2);
		m_posPILAthRe[i] = new Histogram(1, m_assoc+2);
		m_posPILAthLRU[i] = new Histogram(1, m_assoc+2);
	}
}


inline
quickLRRcPolicy::~quickLRRcPolicy()
{
}

inline 
void quickLRRcPolicy::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();

  int ant = m_LRUorder[set][index];
  
  if(DEBUG_SET && set==17) {
  	if(DEBUG_SET && set==17) cerr << "HIT at " << index << " LRUpos: " << ant << endl;
    for(int i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << "\t" << (*m_cache)[set][i] << endl;
  }


  
  if(time > 1) {
    m_posPILAthLRU[proc]->add(ant);
  	m_posPILALRU->add(ant);
  	if(DEBUG_SET && set==17)cerr << this << "LRU at " << ant << endl;
  	
  	 CacheEntryQuick &p = (*m_cache)[set][index];
  	 
  	 int pos = posInSubset(set, index, p);
  	if(p.m_NRU) {
  		m_posPILAthRe[proc]->add(pos);
  		m_posPILARe->add(pos);
  		if(DEBUG_SET && set==17)cerr << this << " reuse at " << pos << endl;
  	}
  	else {
  		m_posPILAth1st[proc]->add(pos);
  		m_posPILA1st->add(pos);
  		if(DEBUG_SET && set==17)cerr << this << " 1st use at " << pos << endl;
  	}
  	p.m_NRU = 1;
  }

  //inicializacion
  if(ant == 0) {
  	for(int i=0; i<m_assoc; i++)m_LRUorder[set][i]= m_LRUorder[set][i]>ant ? m_LRUorder[set][i]+1 : 0;
  }
  else {
    for (unsigned int i=0; i < m_assoc; i++) {
    	int aux= m_LRUorder[set][i];
    //m_LRUorder[set][i]= m_LRUo;rder[set][i]==m_assoc ? m_LRUorder[set][i] : m_LRUorder[set][i]+1;
      m_LRUorder[set][i]= aux<=ant && aux != 0 ? aux+1 : aux;
    }
  }

  m_LRUorder[set][index]=1;
  
  if(ant>16) insideAsoc= 2;
  else insideAsoc= 1;
  
}

inline
Index quickLRRcPolicy::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  int maxPos[4],pos[4], maxIndex[4];

  unsigned int i;

  for(i=0; i<4; i++) {
  	maxIndex[i] = -1;
  	maxPos[i] = 0;
  }
  
  for (i=0; i < m_assoc; i++) {
  	uint k = whatSubSet((*m_cache)[set][i]);
  	pos[k] = m_LRUorder[set][i];
  	
  	if (pos[k] > maxPos[k]){
        maxIndex[k] = i;
        maxPos[k] = pos[k];
    }
  }
  
  for(i=0; i<4; i++) 
  	if(maxIndex[i]!=-1) return maxIndex[i];

assert(0);

  Time time[4], smallest_time[4];
  Index smallest_index[4];


  for(i=0; i<4; i++) {
  	smallest_index[i] = -1;
  	smallest_time[i] = g_eventQueue_ptr->getTime()+100;
  }
  
  for (i=0; i < m_assoc; i++) {
  	uint k=whatSubSet((*m_cache)[set][i]);
  	time[k] = m_last_ref_ptr[set][i];
  	
  	if (time[k] < smallest_time[k]){
        smallest_index[k] = i;
        smallest_time[k] = time[k];
    }
  }
  
  for(i=0; i<4; i++) 
  	if(smallest_index[i]!=-1) return smallest_index[i];

}

inline void quickLRRcPolicy::replacementLower(Index set, Index way)  {
	//if((*m_cache)[set][way].m_reused) m_last_ref_ptr[set][way] = g_eventQueue_ptr->getTime();
}

inline 
uint quickLRRcPolicy::whatSubSet(CacheEntryQuick &a) const
{
  if(a.m_Sharers.count()==0 && !a.m_NRU) return 0;
  if(a.m_Sharers.count()==0 && a.m_NRU) return 1;
  if(a.m_Sharers.count()!=0  && !a.m_NRU) return 2;
  if(a.m_Sharers.count()!=0  && a.m_NRU) return 3;

  assert(0);
  return -1;
  
}

inline int quickLRRcPolicy::posInSubset(int set, int index, CacheEntryQuick &p) {

	
	int blkSubset = whatSubset(p);
	int blkLRUpos = m_LRUorder[set][index];
	int blkSubsetPos = 1;
	
	for(int i=0; i<m_assoc; i++) {		
		if(m_LRUorder[set][i] < blkLRUpos && m_LRUorder[set][i] > 0 && whatSubset((*m_cache)[set][i])==blkSubset)
			blkSubsetPos++;
	}
	
	return blkSubsetPos;
 
}

inline uint quickLRRcPolicy::whatSubset(CacheEntryQuick& a) {
	if(!a.m_NRU) return 0;
	else return 1;
}


inline
void quickLRRcPolicy::printStats(ostream& out, char* name) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRRcPolicy::printStats" << endl;
	for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
		for (int j = 0; j < 2; j++)
			out << "LRRc" << "_hit_ratio_segment_"<< j <<"_thread_" << i << ":\t" <<  (float) m_nH[j][i]/(m_nTH[i])  << endl;
	}

  out << "HistoLRU gral" << name << " " << *m_posPILALRU << endl;  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "HistoLRU "<< name << " thread " << i << "\t" << *m_posPILAthLRU[i] << endl;

  out << "Histo1st gral " << name << " " << *m_posPILA1st << endl;  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "Histo1st "<< name << " thread " << i << "\t" << *m_posPILAth1st[i] << endl;

  out << "HistoRe gral " << name << " " << *m_posPILARe << endl;  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "HistoRe "<< name << " thread " << i << "\t" << *m_posPILAthRe[i] << endl;

}

inline
void quickLRRcPolicy::clearStats() 
{
cerr << "quickLRRcPolicy::clearStats()" << endl;

  for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
  	for (int j = 0; j < 2; j++) m_nH[j][i]= 0;
  	m_nTH[i] = 0;
  }

	m_posPILALRU = new Histogram(1, m_assoc+2);
	m_posPILAthLRU = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILA1st = new Histogram(1, m_assoc+2);
	m_posPILAth1st = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILARe = new Histogram(1, m_assoc+2);
	m_posPILAthRe = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	
	for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) {
		m_posPILAth1st[i] = new Histogram(1, m_assoc+2);
		m_posPILAthRe[i] = new Histogram(1, m_assoc+2);
		m_posPILAthLRU[i] = new Histogram(1, m_assoc+2);
	}
}

inline
void quickLRRcPolicy::printStats(ostream& out) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRRcPolicy::printStats" << endl;
}
#endif // PSEUDOLRUBITS_H
