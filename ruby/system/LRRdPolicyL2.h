
#ifndef LRRdPolicyL2_H
#define LRRdPolicyL2_H

#include "AbstractReplacementPolicy.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"

/* Simple true LRU replacement policy */

class LRRdPolicyL2 : public AbstractReplacementPolicy {
	mutable int trend;
  
 public:

  LRRdPolicyL2(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a); //SOLO PARA QUE COMPILE
  LRRdPolicyL2(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~LRRdPolicyL2();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  void replacementLower(Index set, Index way) const;
  
  void printStats(ostream& out) const;

 
};


//SOLO PARA QUE COMPILE



inline
LRRdPolicyL2::LRRdPolicyL2(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
	trend = 1;
}

inline
LRRdPolicyL2::LRRdPolicyL2(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
	trend = 1;
  m_cache = a;
  //stats
  for(int i=0; i<3; i++) m_select[i]=0;
}

inline
LRRdPolicyL2::~LRRdPolicyL2()
{
}

inline 
void LRRdPolicyL2::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if( time!=0 )
  {
     (*m_cache)[set][index].m_NRU = 1;
     m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
  }
  
}

inline
Index LRRdPolicyL2::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  Time time, smallest_time;
  Index smallest_index;

  smallest_index = -1;
  smallest_time = g_eventQueue_ptr->getTime()+100;

  int i;

// Randomly chose one not reused  nor private element, starting 
	trend*=-1;
  	for (i= (trend==1 ? 0 : m_assoc-1); i < m_assoc && i>=0; i+= trend) 
    	if(!(*m_cache)[set][i].m_NRU && (*m_cache)[set][i].m_Sharers.count()==0)  return i;

  
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
  } 
  

  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);

  return smallest_index;
}
inline void LRRdPolicyL2::replacementLower(Index set, Index way) const {
}


inline
void LRRdPolicyL2::printStats(ostream& out) const
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 

}
#endif // PSEUDOLRUBITS_H

