
#ifndef LRUPOLICYL2qbs_H
#define LRUPOLICYL2qbs_H

#include "AbstractReplacementPolicy.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"

/* Simple true LRU replacement policy */

class LRUPolicyL2_qbs : public AbstractReplacementPolicy {
 public:

  LRUPolicyL2_qbs(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a); //SOLO PARA QUE COMPILE
  LRUPolicyL2_qbs(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~LRUPolicyL2_qbs();

  void touch(Index set, Index way, Time time);
  Index getVictim(Index set) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;

  void printStats(ostream& out) const;

};


//SOLO PARA QUE COMPILE
inline
LRUPolicyL2_qbs::LRUPolicyL2_qbs(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
LRUPolicyL2_qbs::LRUPolicyL2_qbs(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  m_cache = a;
}

inline
LRUPolicyL2_qbs::~LRUPolicyL2_qbs()
{
}

inline 
void LRUPolicyL2_qbs::touch(Index set, Index index, Time time){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if( time!=0 )
  {
     m_last_ref_ptr[set][index] = time;
  }
  else
     m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
}

inline
Index LRUPolicyL2_qbs::getVictim(Index set) const {
  //  assert(m_assoc != 0);
  Time time, smallest_time;
  Index smallest_index;

  
  unsigned int i;
  uint flag=1;
  
  do
  {
      smallest_index = 0; 
      smallest_time = m_last_ref_ptr[set][0];

	  for (i=0; i < m_assoc; i++) 
	  {
		  time = m_last_ref_ptr[set][i];
		  //assert(m_cache[cacheSet][i].m_Permission != AccessPermission_NotPresent);
	
		  if (time < smallest_time){
			smallest_index = i;
			smallest_time = time;
		  }		
	  }
	  if((*m_cache)[set][smallest_index].m_Sharers.isEmpty()) //nadie lo tiene por debajo, perfecto
	  {
	    flag=0;	    
	  } 
	  else  //hay alguna copia en las corecaches --> tocamos e iteramos
	  {
	    m_last_ref_ptr[set][smallest_index] = g_eventQueue_ptr->getTime();
	    flag++;
	  }
  } while(flag!=0 && flag!=m_assoc+1);
  

  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);

  return smallest_index;
}

inline
void LRUPolicyL2_qbs::printStats(ostream& out) const
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 

}
#endif // PSEUDOLRUBITS_H
