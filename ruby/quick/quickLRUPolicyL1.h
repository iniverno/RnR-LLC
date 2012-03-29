
#ifndef quickLRUPolicyL1_H
#define quickLRUPolicyL1_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true LRU replacement policy */

class quickLRUPolicyL1 : public AbstractReplacementPolicyQuick {
 public:

  quickLRUPolicyL1(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickLRUPolicyL1();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  void replacementLower(Index set, Index way)  ;

  void printStats(ostream& out, char* name) ;
  void printStats(ostream& out) ;
  void clearStats() ;

};


//SOLO PARA QUE COMPILE

inline
quickLRUPolicyL1::quickLRUPolicyL1(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
	cerr << "constructor LRU" << endl;
}


inline
quickLRUPolicyL1::~quickLRUPolicyL1()
{
}

inline 
void quickLRUPolicyL1::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();

}

inline
Index quickLRUPolicyL1::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  Time time, smallest_time;
  Index smallest_index;

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

  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);

  return smallest_index;
}


inline void quickLRUPolicyL1::replacementLower(Index set, Index way)  {
}

inline
void quickLRUPolicyL1::printStats(ostream& out, char* name) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRUPolicyL1::printStats" << endl;


}

inline
void quickLRUPolicyL1::printStats(ostream& out) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRUPolicyL1::printStats" << endl;
}

inline
void quickLRUPolicyL1::clearStats() 
{

}
#endif // PSEUDOLRUBITS_H
