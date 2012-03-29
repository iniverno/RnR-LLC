
#ifndef LRUPolicyL2_stack_H
#define LRUPolicyL2_stack_H

#include "AbstractReplacementPolicy.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"


struct listNode {
public:
	listNode *next, *prev; //next node
	uint accesses;  //number of accesses since the node was inserted in the set
	uint way;
	Address* addr;
	
	listNode (listNode* p, listNode* n, uint w, Address* ad) : next(n), prev(p),  accesses(0), way(w), addr(ad) {} ;
};

/* Simple true LRU replacement policy */

class LRUPolicyL2_stack : public AbstractReplacementPolicy {
 public:

  LRUPolicyL2_stack(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a); //SOLO PARA QUE COMPILE
  LRUPolicyL2_stack(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~LRUPolicyL2_stack();

  //JORGE
  //The address is needed to look for that address in the aux LRU stack
  /* returns the way to replace */
 //  Index getVictim(Index set, Address a) const = 0;
  // void murderAddress(Address m) ;

  void touch(Index set, Index way, Time time);
  Index getVictim(Index set) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  
  //JORGE
  //vars for LRU stack
  mutable listNode *first, *last, *LRU;
  mutable Address* murder;
  mutable uint n;

  void printStats(ostream& out)const;

};


//SOLO PARA QUE COMPILE
inline
LRUPolicyL2_stack::LRUPolicyL2_stack(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
LRUPolicyL2_stack::LRUPolicyL2_stack(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  m_cache = a;
  first= NULL;
  last=NULL;
  LRU= NULL;
  n=0;
}

inline
LRUPolicyL2_stack::~LRUPolicyL2_stack()
{
}

inline 
void LRUPolicyL2_stack::touch(Index set, Index index, Time time){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if( time!=0 )
  {
    
     m_last_ref_ptr[set][index] = time;
  }
  else
     m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
     
 	//Address aux =  
	//for (p = first; p != last->next; p++) {
		//if(m_cache[cacheSet][i].)
	//}
     
	first = LRU;
	//LRU = LRU->
	
	
}

inline
Index LRUPolicyL2_stack::getVictim(Index set) const {
  //  assert(m_assoc != 0);
	
		//murder =  new Address(m);
		
	listNode* p;
  
  for (p = first; p != last->next; p++) {

  }  
  	
	uint way = LRU->way;
	
  	listNode* aux = new listNode(NULL, first, LRU->way, murder);
  	first->prev = aux;
  	first = aux;  	 	
  	
  	if(n == 0) LRU = aux;
  	else {
  		LRU = LRU->prev; 
  		
  		if(n < 128) n++;
  		else {
  			last = last->prev;
  			
  			delete (last->next->addr);
  			delete (last->next);
  		}
  	}

	
	return way;	
	
  for (unsigned int i=0; i < m_assoc; i++) {
    //assert(m_cache[cacheSet][i].m_Permission != AccessPermission_NotPresent);


  }

	
	return LRU->way;
  
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);

}

inline
void LRUPolicyL2_stack::printStats(ostream& out) const
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 

}

#endif // PSEUDOLRUBITS_H
