
#ifndef quickLRRbPolicy_H
#define quickLRRbPolicy_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheMemoryQuick.h"



/* two lists completely sorted by reuse order and touch in private replacement  */


class quickLRRbPolicy : public AbstractReplacementPolicyQuick {
 public:

  quickLRRbPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickLRRbPolicy();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  void replacementLower(Index set, Index way)  ;
  uint whatSubSet(CacheEntryQuick &a) const;
  
  int posInSubset(int set, int index, CacheEntryQuick &p);
  uint whatSubset(CacheEntryQuick& a);
  
  void printStats(ostream& out, char* name) ;
  void printStats(ostream& out) ;
  
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
quickLRRbPolicy::quickLRRbPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
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
quickLRRbPolicy::~quickLRRbPolicy()
{
}

inline 
void quickLRRbPolicy::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if( time==0 )  { 
    m_last_ref_ptr[set][index] = 1;
    return;
  }
  //para la distribucion de aciertos por segmentos
  //time==1 solo puede aparecer si g_SHADOW activo
  if(time > 1) {
  	m_nH[(*m_cache)[set][index].m_NRU][proc]++;
  	m_nTH[proc]++;
  }  

  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
  (*m_cache)[set][index].m_NRU = 1;   //para marcar reuso dinamico (reuso del mecanismo, no reuso en general)

  int ant = m_LRUorder[set][index];
  for (unsigned int i=0; i < m_assoc; i++) {
    m_LRUorder[set][i]= m_LRUorder[set][i]<=ant && m_LRUorder[set][i]>0  ? m_LRUorder[set][i]+1 : m_LRUorder[set][i];
  }
  if(time > 1) {
    m_posPILAthLRU[proc]->add(m_LRUorder[set][index]);
  	m_posPILALRU->add(m_LRUorder[set][index]);
  		
  	 CacheEntryQuick &p = (*m_cache)[set][index];
  	 int pos = posInSubset(set, index, p);
  	if(p.m_reused) {
  		m_posPILAthRe[proc]->add(pos);
  		m_posPILARe->add(pos);
  	}
  	else {
  		m_posPILAth1st[proc]->add(pos);
  		m_posPILA1st->add(pos);
  	}
  }
  
  m_LRUorder[set][index]=1;
}

inline
Index quickLRRbPolicy::getVictim(Index set, uint proc) const {
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);

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

  assert(0);

}

inline 
uint quickLRRbPolicy::whatSubSet(CacheEntryQuick &a) const
{
  if(a.m_Sharers.count()==0 && !a.m_NRU) return 0;
  if(a.m_Sharers.count()==0 && a.m_NRU) return 1;
  if(a.m_Sharers.count()!=0  && !a.m_NRU) return 2;
  if(a.m_Sharers.count()!=0  && a.m_NRU) return 3;

  assert(0);  
}

inline int quickLRRbPolicy::posInSubset(int set, int index, CacheEntryQuick &p) {

	
	int blkSubset = whatSubset(p);
	int blkLRUpos = m_LRUorder[set][index];
	int blkSubsetPos = 1;
	
	for(int i=0; i<m_assoc; i++) {
		if(m_LRUorder[set][i] < blkLRUpos && whatSubset((*m_cache)[set][i])==blkSubset)
			blkSubsetPos++;
	}
	return blkSubsetPos;
 
}

inline uint quickLRRbPolicy::whatSubset(CacheEntryQuick& a) {
	if(!a.m_NRU) return 0;
	else return 1;
}
inline void quickLRRbPolicy::replacementLower(Index set, Index way)  {

	//if((*m_cache)[set][way].m_reused) m_last_ref_ptr[set][way] = g_eventQueue_ptr->getTime();
	if((*m_cache)[set][way].m_NRU) {
		int ant = m_LRUorder[set][way];
		for (unsigned int i=0; i < m_assoc; i++) {
    		m_LRUorder[set][i]= m_LRUorder[set][i]<=ant && m_LRUorder[set][i]>0  ? m_LRUorder[set][i]+1 : m_LRUorder[set][i];
   		}
   		m_LRUorder[set][way]=1;
	}
}

inline
void quickLRRbPolicy::printStats(ostream& out, char* name) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRRbPolicy::printStats" << endl;
	for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
		for (int j = 0; j < 2; j++)
			out << "LRRb" << "_hit_ratio_segment_"<< j <<"_thread_" << i << ":\t" <<  (float) m_nH[j][i]/(m_nTH[i])  << endl;
	}

}

inline
void quickLRRbPolicy::printStats(ostream& out) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRRbPolicy::printStats" << endl;
}
#endif // PSEUDOLRUBITS_H
