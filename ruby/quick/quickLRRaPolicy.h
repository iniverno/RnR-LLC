
#ifndef quickLRRaPolicy_H
#define quickLRRaPolicy_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheMemoryQuick.h"

/* Simple true LRU replacement policy */

class quickLRRaPolicy : public AbstractReplacementPolicyQuick {
 public:

  quickLRRaPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickLRRaPolicy();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  void replacementLower(Index set, Index way)  ;

  void printStats(ostream& out, char* name) ;
  void printStats(ostream& out) ;
  
  Vector<Vector<CacheEntryQuick> > *m_cache;
};


//SOLO PARA QUE COMPILE

inline
quickLRRaPolicy::quickLRRaPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_cache = a;
}


inline
quickLRRaPolicy::~quickLRRaPolicy()
{
}

inline 
void quickLRRaPolicy::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if( time==0 )  { 
    m_last_ref_ptr[set][index] = 1;
    return;
  }
  
  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
}

inline
Index quickLRRaPolicy::getVictim(Index set, uint proc) const {
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

inline void quickLRRaPolicy::replacementLower(Index set, Index way)  {
	if((*m_cache)[set][way].m_reused) m_last_ref_ptr[set][way] = g_eventQueue_ptr->getTime();
}

inline
void quickLRRaPolicy::printStats(ostream& out, char* name) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRRaPolicy::printStats" << endl;
}

inline
void quickLRRaPolicy::printStats(ostream& out) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRRaPolicy::printStats" << endl;
}
#endif // PSEUDOLRUBITS_H
