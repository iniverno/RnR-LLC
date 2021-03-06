
#ifndef LRUPOLICY_H
#define LRUPOLICY_H

#include "AbstractReplacementPolicy.h"

/* Simple true LRU replacement policy */

class LRUPolicy : public AbstractReplacementPolicy {
 public:

  LRUPolicy(Index num_sets, Index assoc);
  ~LRUPolicy();

  void touch(Index set, Index way, Time time);
  Index getVictim(Index set) const;
  void replacementLower(Index set, Index way) const;
  Vector<Vector<ENTRY> > *m_cache;
  
  void printStats(ostream& out) const;

};

inline
LRUPolicy::LRUPolicy(Index num_sets, Index assoc)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
LRUPolicy::~LRUPolicy()
{
}

inline 
void LRUPolicy::touch(Index set, Index index, Time time){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  m_last_ref_ptr[set][index] = time;
}

inline  void LRUPolicy::replacementLower(Index set, Index way) const {}

inline
Index LRUPolicy::getVictim(Index set) const {
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
void LRUPolicy::printStats(ostream& out)
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 

}
#endif // PSEUDOLRUBITS_H
