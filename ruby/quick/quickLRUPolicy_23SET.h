
#ifndef quickLRUPolicy_23SET_H
#define quickLRUPolicy_23SET_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true LRU replacement policy */

class quickLRUPolicy_23SET : public AbstractReplacementPolicyQuick {
 public:

  quickLRUPolicy_23SET(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickLRUPolicy_23SET();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<CacheEntryQuick> > *m_cache;
  void replacementLower(Index set, Index way)  ;

  void printStats(ostream& out) ;

  void printStats(ostream& out, char* name) ;
  uint whatSubSet(CacheEntryQuick &a) const;
  
  mutable char m_enabled3SET;
  
  mutable uint hits, misses;
  mutable uint64 epochsEnabled, epochsDisabled;
  mutable  uint64  	totalHits ;
  mutable	uint64 totalMisses ;
};


inline
quickLRUPolicy_23SET::quickLRUPolicy_23SET(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_cache = a;
  m_enabled3SET = false;
  epochsEnabled = 0;
  epochsDisabled = 0;
    	totalHits = 0;
  	totalMisses = 0;

}

inline
quickLRUPolicy_23SET::~quickLRUPolicy_23SET()
{
}

inline 
void quickLRUPolicy_23SET::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);
  
  if(time != 0) hits++;
	

  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
}

inline
Index quickLRUPolicy_23SET::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);

  if(hits+misses > (1 << 10)) {
  	m_enabled3SET = (float)misses/(hits + misses) > 0.8;
  	
  	totalHits += hits;
  	totalMisses += misses;
  	
  	//cerr << "misses:" << misses << "  hits:" << hits << endl;
  	
  	//cerr << "ratio: " << (float)misses/(hits + misses) << endl;
  	m_enabled3SET ? epochsEnabled++ : epochsDisabled++;
  	misses = 0; 
  	hits = 0;
  }
  misses++;
	
  Time time[4], smallest_time[4];
  Index smallest_index[4];

  unsigned int i;

  for(i=0; i<4; i++) {
  	smallest_index[i] = -1;
  	smallest_time[i] = g_eventQueue_ptr->getTime()+100;
  }
  
  for (i=0; i < m_assoc; i++) {
  	uint k = whatSubSet((*m_cache)[set][i]);
  	
  	k &= (m_enabled3SET + 2);
  	
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

inline void quickLRUPolicy_23SET::replacementLower(Index set, Index way)  {
}

inline
void quickLRUPolicy_23SET::printStats(ostream& out, char* name) 
{
	out << name << "_no_reused_segment_size_histogram:\t" << m_histoSpace[0] << endl;
	out << name << "_reused_segment_size_histogram:\t" << m_histoSpace[1] << endl;
	out << name << "_epochs_3SET_enabled:\t" << epochsEnabled << endl;
	out << name << "_epochs_3SET_disabled:\t" << epochsDisabled << endl;
	out << name << "_3SET_enabled_ratio:\t" << (float)epochsEnabled/(epochsDisabled+epochsEnabled) << endl;

  	totalHits += hits;
  	totalMisses += misses;


out << name << "_accesses_pol:\t" << totalHits+totalMisses << endl;	
out << name << "_misses_pol:\t" << totalMisses << endl;	
}


inline
void quickLRUPolicy_23SET::printStats(ostream& out) 
{
}

inline 
uint quickLRUPolicy_23SET::whatSubSet(CacheEntryQuick &a) const
{
  if(a.m_Sharers.count()==0 && !a.m_reused) return 0;
  if(a.m_Sharers.count()==0 && a.m_reused) return 1;
  if(a.m_Sharers.count()!=0) return 2;
  
  assert(0);
  return -1;
  
}




#endif // PSEUDOLRUBITS_H
