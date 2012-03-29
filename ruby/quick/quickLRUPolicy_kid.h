
#ifndef quickLRUPOLICYKID_H
#define quickLRUPOLICYKID_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true LRU replacement policy */

class quickLRUPolicy_kid : public AbstractReplacementPolicyQuick {
 public:

  quickLRUPolicy_kid(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickLRUPolicy_kid();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<CacheEntryQuick> > *m_cache;
  void replacementLower(Index set, Index way)  ;

  void printStats(ostream& out) ;

  void printStats(ostream& out, char* name) ;

};


inline
quickLRUPolicy_kid::quickLRUPolicy_kid(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_cache = a;
}

inline
quickLRUPolicy_kid::~quickLRUPolicy_kid()
{
}

inline 
void quickLRUPolicy_kid::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
}

inline
Index quickLRUPolicy_kid::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  Time time, smallest_time;
  Index smallest_index;

  smallest_index = -1;
  smallest_time = g_eventQueue_ptr->getTime()+100;

  unsigned int i;
  
  for (i=0; i < m_assoc; i++) {
    if((*m_cache)[set][i].m_Sharers.count()==0)  //if there is no included below
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
    smallest_index=0;
    smallest_time = m_last_ref_ptr[set][0];
    
    for (i=0; i < m_assoc; i++) {
      time = m_last_ref_ptr[set][i];

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

inline void quickLRUPolicy_kid::replacementLower(Index set, Index way)  {
}

inline
void quickLRUPolicy_kid::printStats(ostream& out, char* name) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
int a=0;
}

inline
void quickLRUPolicy_kid::printStats(ostream& out) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
int a=0;
}
#endif // PSEUDOLRUBITS_H
