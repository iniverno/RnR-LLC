
#ifndef RNDPolicyL2_kid_H
#define RNDPolicyL2_kid_H

#include "AbstractReplacementPolicy.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"

/* Simple true NRU replacement policy */

class RNDPolicyL2_kid : public AbstractReplacementPolicy {
 public:

  RNDPolicyL2_kid(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a); //SOLO PARA QUE COMPILE
  RNDPolicyL2_kid(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~RNDPolicyL2_kid();

  void touch(Index set, Index way, Time time);
  Index getVictim(Index set) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  
  bool subSet(L2Cache_Entry *a, uint set) const;
  
  Index* m_pointer;

  void printStats(ostream& out)const;

};


//SOLO PARA QUE COMPILE
inline
RNDPolicyL2_kid::RNDPolicyL2_kid(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
RNDPolicyL2_kid::RNDPolicyL2_kid(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  srand(time(NULL));
  m_cache = a;
  m_pointer = new Index(0);
}

inline
RNDPolicyL2_kid::~RNDPolicyL2_kid()
{
}

inline 
void RNDPolicyL2_kid::touch(Index set, Index index, Time time){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

}

inline
Index RNDPolicyL2_kid::getVictim(Index set) const {
  //  assert(m_assoc != 0);
  //  assert(m_assoc != 0);
  uint i = 0;
  L2Cache_Entry *p;
 
  uint entries[m_assoc];
 
  
	for(int k=0; k<2; k++)  
	{
	   uint nEntries=0;
	  //look for a member of each set
	  for (i=0; i < m_assoc; i++) {
	    p=&(*m_cache)[set][i];
		if(subSet(p, k)) {
		  entries[nEntries++] = i;
	    }
	  }
	  
	  //if there is any -> we select one of them randomly
	  if(nEntries) 
	  {
	    return entries[rand() % nEntries];
	   
	  }
	}  

  assert(0);
  return -1;
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);
}

inline 
bool RNDPolicyL2_kid::subSet(L2Cache_Entry *a, uint set) const
{
/*  if(a->m_Permission == AccessPermission_NotPresent ||
        a->m_Permission == AccessPermission_Invalid)
    return false;
*/
  
  switch(set)
  {
    //conjunto de los bloques que no tienen copia por debajo
    case 0:
      return a->m_Sharers.count()==0;
    break;
    case 1:
      return a->m_Sharers.count()!=0;
    break;
    default:
    break;
    
  }
  assert(0);
  return false;
  
}

inline
void RNDPolicyL2_kid::printStats(ostream& out) const
{

}
#endif // PSEUDONRUBITS_H
