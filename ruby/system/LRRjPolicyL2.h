
#ifndef LRRjPolicyL2_H
#define LRRjPolicyL2_H

#include "AbstractReplacementPolicy.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"

/* Simple true LRU replacement policy */

class LRRjPolicyL2 : public AbstractReplacementPolicy {
	mutable int trend;
  
 public:

  LRRjPolicyL2(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a); //SOLO PARA QUE COMPILE
  LRRjPolicyL2(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~LRRjPolicyL2();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  void replacementLower(Index set, Index way) const;
  
  void printStats(ostream& out) const;

 
};


//SOLO PARA QUE COMPILE



inline
LRRjPolicyL2::LRRjPolicyL2(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
	trend = 1;
}

inline
LRRjPolicyL2::LRRjPolicyL2(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
	trend = 1;
  m_cache = a;
  //stats
  for(int i=0; i<3; i++) m_select[i]=0;
}

inline
LRRjPolicyL2::~LRRjPolicyL2()
{
}

inline 
void LRRjPolicyL2::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if( time!=0 )
  {
     (*m_cache)[set][index].m_NRU = 1;
     m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
  }
  
}

inline
Index LRRjPolicyL2::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  Time time, smallest_time;
  Index smallest_index;

  smallest_index = -1;
  smallest_time = g_eventQueue_ptr->getTime()+100;

  int i;

// Randomly chose one not reused  nor private element, starting 
	trend*=-1;
  	for (i= (trend==1 ? 0 : m_assoc-1); i < m_assoc && i>=0; i+= trend) 
    	if(!(*m_cache)[set][i].m_NRU)  return i;

  

    //m_select[2]++;
    
    smallest_index=0;
    smallest_time = m_last_ref_ptr[set][0];
    
    for (i=0; i < m_assoc; i++) {
      time = m_last_ref_ptr[set][i];

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
inline void LRRjPolicyL2::replacementLower(Index set, Index way) const {
}


inline
void LRRjPolicyL2::printStats(ostream& out) const
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 

}
#endif // PSEUDOLRUBITS_H

