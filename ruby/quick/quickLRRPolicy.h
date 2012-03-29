
#ifndef quickLRRPolicy_H
#define quickLRRPolicy_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheMemoryQuick.h"

/* Simple true LRU replacement policy */

class quickLRRPolicy : public AbstractReplacementPolicyQuick {
 public:

  quickLRRPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickLRRPolicy();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  void replacementLower(Index set, Index way)  ;

  void printStats(ostream& out, char* name) ;
  void printStats(ostream& out) ;
  void clearStats() ;
  Vector<Vector<CacheEntryQuick> > *m_cache;
};


//SOLO PARA QUE COMPILE

inline
quickLRRPolicy::quickLRRPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_cache = a;
  cerr << "constructor LRR" << endl;
}


inline
quickLRRPolicy::~quickLRRPolicy()
{
}

inline 
void quickLRRPolicy::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if( time==0 )  { 
    m_last_ref_ptr[set][index] = 1;
    return;
  }
  
  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
}

inline
Index quickLRRPolicy::getVictim(Index set, uint proc) const {
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

  return smallest_index;
}

inline void quickLRRPolicy::replacementLower(Index set, Index way)  {
	if((*m_cache)[set][way].m_reused) m_last_ref_ptr[set][way] = g_eventQueue_ptr->getTime();
}

inline
void quickLRRPolicy::printStats(ostream& out, char* name) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRRPolicy::printStats" << endl;
}

inline
void quickLRRPolicy::printStats(ostream& out) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRRPolicy::printStats" << endl;
}

inline
void quickLRRPolicy::clearStats() 
{

}
#endif // PSEUDOLRUBITS_H
