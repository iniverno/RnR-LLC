
#ifndef LRUPOLICYL1_H
#define LRUPOLICYL1_H

#include "AbstractReplacementPolicy.h"

/* Simple true LRU replacement policy */

class LRUPolicyL1 : public AbstractReplacementPolicy {
 public:

  LRUPolicyL1(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a);
  LRUPolicyL1(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~LRUPolicyL1();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<L1Cache_Entry> > *m_cache;
  void replacementLower(Index set, Index way) const;

  
  void printStats(ostream& out) const ;
};

inline
LRUPolicyL1::LRUPolicyL1(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
	m_cache= a;
}

inline
LRUPolicyL1::LRUPolicyL1(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
LRUPolicyL1::~LRUPolicyL1()
{
}

inline   void LRUPolicyL1::replacementLower(Index set, Index way) const {}

inline 
void LRUPolicyL1::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);
  
 /* if(time!=0) {
  (*m_cache)[set][index].m_reused = true;
  }
 */ 
  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
}

inline
Index LRUPolicyL1::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  Time time, smallest_time;
  Index smallest_index;

  smallest_index = 0;
  smallest_time = m_last_ref_ptr[set][0];

  //NetDest a= m_cache[set][0].m_Sharers;
  
  for (unsigned int i=0; i < m_assoc; i++) {
    time = m_last_ref_ptr[set][i];
    //assert(m_cache[cacheSet][i].m_Permission != AccessPermission_NotPresent);

    if (time < smallest_time){
      smallest_index = i;
      smallest_time = time;
    }
  }

  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);

  return smallest_index;
}

inline
void LRUPolicyL1::printStats(ostream& out) const 
{}
#endif // PSEUDOLRUBITS_H
