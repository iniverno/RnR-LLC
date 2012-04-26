
#ifndef LRUPOLICYL1_kid_H
#define LRUPOLICYL1_kid_H

#include "AbstractReplacementPolicy.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"

/* Simple true LRU replacement policy */

class LRUPolicyL1_kid : public AbstractReplacementPolicy {
 public:

  LRUPolicyL1_kid(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a);
  LRUPolicyL1_kid(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~LRUPolicyL1_kid();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<L1Cache_Entry> > *m_cache;
  void replacementLower(Index set, Index way) const;
  void printStats(ostream& out) const;
};

inline
LRUPolicyL1_kid::LRUPolicyL1_kid(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
    m_cache = a;
}

inline
LRUPolicyL1_kid::LRUPolicyL1_kid(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
LRUPolicyL1_kid::~LRUPolicyL1_kid()
{
}

inline   void LRUPolicyL1::replacementLower(Index set, Index way) const {}

inline 
void LRUPolicyL1_kid::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
}

inline
Index LRUPolicyL1_kid::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  Time time, smallest_time;
  Index smallest_index;


  smallest_index = -1;
  smallest_time = g_eventQueue_ptr->getTime()+100;
  
  for (unsigned int i=0; i < m_assoc; i++) {
    if((*m_cache)[set][i].m_incl==0)
    {
		time = m_last_ref_ptr[set][i];
		//assert(m_cache[cacheSet][i].m_Permission != AccessPermission_NotPresent);
	
		if (time < smallest_time){
		  smallest_index = i;
		  smallest_time = time;
		}
	}
  }
  if(smallest_index==-1)
  {
    smallest_index = 0;
    smallest_time = m_last_ref_ptr[set][0];

  for (unsigned int i=0; i < m_assoc; i++) {
    time = m_last_ref_ptr[set][i];
    //assert(m_cache[cacheSet][i].m_Permission != AccessPermission_NotPresent);

    if (time < smallest_time){
      smallest_index = i;
      smallest_time = time;
    }
  }

  }
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);

  return smallest_index;
}

inline
void LRUPolicyL1_kid::printStats(ostream& out) const
{
}
#endif // PSEUDOLRUBITS_H
