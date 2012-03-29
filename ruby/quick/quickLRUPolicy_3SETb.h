
#ifndef quickLRUPolicy_3SETb_H
#define quickLRUPolicy_3SETb_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true LRU replacement policy */

class quickLRUPolicy_3SETb : public AbstractReplacementPolicyQuick {
 public:

  quickLRUPolicy_3SETb(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickLRUPolicy_3SETb();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<CacheEntryQuick> > *m_cache;
  void replacementLower(Index set, Index way)  ;

  void printStats(ostream& out) ;

  void printStats(ostream& out, char* name) ;
  uint whatSubSet(CacheEntryQuick &a) const;
};


inline
quickLRUPolicy_3SETb::quickLRUPolicy_3SETb(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_cache = a;
}

inline
quickLRUPolicy_3SETb::~quickLRUPolicy_3SETb()
{
}

inline 
void quickLRUPolicy_3SETb::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if(m_nReused[set] > m_assoc-4) 
	for(uint i=0; i<m_assoc; i++) 
	{
		(*m_cache)[set][i].m_reused = false;
		m_nReused[set]=0;
	}
	
  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
}

inline
Index quickLRUPolicy_3SETb::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);

  Time time[4], smallest_time[4];
  Index smallest_index[4];

  unsigned int i;

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

inline void quickLRUPolicy_3SETb::replacementLower(Index set, Index way)  {
}

inline
void quickLRUPolicy_3SETb::printStats(ostream& out, char* name) 
{
	out << name << "_no_reused_segment_size_histogram:\t" << m_histoSpace[0] << endl;
	out << name << "_reused_segment_size_histogram:\t" << m_histoSpace[1] << endl;
}

inline
void quickLRUPolicy_3SETb::printStats(ostream& out) 
{
	out << "m_nReused: " << (int)m_nReused[17] <<endl;
}

inline 
uint quickLRUPolicy_3SETb::whatSubSet(CacheEntryQuick &a) const
{
  if(a.m_Sharers.count()==0 && !a.m_reused) return 0;
  if(a.m_Sharers.count()==0 && a.m_reused) return 1;
  if(a.m_Sharers.count()!=0) return 2;
  
  assert(0);
  return -1;
  
}

#endif // PSEUDOLRUBITS_H
