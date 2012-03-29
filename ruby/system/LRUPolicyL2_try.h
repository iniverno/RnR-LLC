
#ifndef LRUPOLICYL2try_H
#define LRUPOLICYL2try_H

#include "AbstractReplacementPolicy.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"

/* Simple true LRU replacement policy */

class LRUPolicyL2_try : public AbstractReplacementPolicy {
 public:

  LRUPolicyL2_try(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a); //SOLO PARA QUE COMPILE
  LRUPolicyL2_try(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~LRUPolicyL2_try();
  void printSet(Index set);
  
  void touch(Index set, Index way, Time time);
  Index getVictim(Index set) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;

  void printStats(ostream& out)const;

};


//SOLO PARA QUE COMPILE
inline
LRUPolicyL2_try::LRUPolicyL2_try(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
LRUPolicyL2_try::LRUPolicyL2_try(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  m_cache = a;
}

inline
LRUPolicyL2_try::~LRUPolicyL2_try()
{
}

inline 
void LRUPolicyL2_try::touch(Index set, Index index, Time time){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);
  unsigned int i=0;
  
  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
  
  if(time!=0 && (*m_cache)[set][index].m_uses == 0)
  {
    (*m_cache)[set][index].m_uses = 1;
    m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
    
    unsigned int nnormal=0;
    for (i=0; i < m_assoc; i++) ((*m_cache)[set][i].m_uses==1) ? nnormal++ : 0;
    
    //lo siguiente para pasar el LRU de "normal" a "test"
    if(nnormal > m_assoc - g_TRY_SIZE )
    {
      Time time2, smallest_time;
  	  Index smallest_index;

   	  smallest_index = -1;
 	  smallest_time = g_eventQueue_ptr->getTime()+100;

	  for (i=0; i < m_assoc; i++) 
	  {
		if((*m_cache)[set][i].m_uses==1)  //if it is on the  partition for trying
		{
		  time2 = m_last_ref_ptr[set][i];
		  //assert(m_cache[cacheSet][i].m_Permission != AccessPermission_NotPresent);
	
		  if (time2 < smallest_time){
			smallest_index = i;
			smallest_time = time2;
		  }
		}
      }  //for assoc
      assert(smallest_index!=-1);
      (*m_cache)[set][smallest_index].m_uses = 0;
      m_last_ref_ptr[set][smallest_index] = g_eventQueue_ptr->getTime();
    }  //if nnormal
  }  
  
  /*if(set==0) 
  {
    cerr << (m_cache) <<"touch -- " << "index: " << index << endl;
    printSet(set);
  }*/
}


inline
Index LRUPolicyL2_try::getVictim(Index set) const {
  //  assert(m_assoc != 0);
  Time time, smallest_time;
  Index smallest_index;

 //if(set==0)  cerr << (m_cache)<< "victim -- "  << endl;
 
  smallest_index = -1;
  //smallest_time = m_last_ref_ptr[set][0];
  smallest_time = g_eventQueue_ptr->getTime()+100;
  
  unsigned int i;
  
  //primero los no usados y que no tienen copia abajo
  for (i=0; i < m_assoc; i++) {
    if((*m_cache)[set][i].m_uses==0)  //if it is on the  partition for trying
    {
      time = m_last_ref_ptr[set][i];
      //assert(m_cache[cacheSet][i].m_Permission != AccessPermission_NotPresent);

      if (time < smallest_time){
        smallest_index = i;
        smallest_time = time;
      }
    }
  }
  
  assert(smallest_index!=-1);
  
 /* if(set==0) 
  {
    cerr << (m_cache)<< "victim -- " << "index: " << smallest_index << endl;
    for (i=0; i < m_assoc; i++) 
  {
    cerr<< (m_cache) << "add: " << (*m_cache)[set][i].m_Address << "   uses: " << (*m_cache)[set][i].m_uses << "  Time: "<< m_last_ref_ptr[set][i]<<endl;
  }
  cerr << endl;
  }*/


  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);

  return smallest_index;
}

inline 
void LRUPolicyL2_try::printSet(Index set){
  uint i;
  for (i=0; i < m_assoc; i++) 
  {
    cerr<< (m_cache) << "add: " << (*m_cache)[set][i].m_Address << "   uses: " << (*m_cache)[set][i].m_uses << "  Time: "<< m_last_ref_ptr[set][i]<<endl;
  }
  cerr << endl;
}

inline
void LRUPolicyL2_try::printStats(ostream& out) const
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 

}

#endif // PSEUDOLRUBITS_H
