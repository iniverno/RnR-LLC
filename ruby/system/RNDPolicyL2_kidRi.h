
#ifndef RNDPolicyL2_kidRi_H
#define RNDPolicyL2_kidRi_H

#include "AbstractReplacementPolicy.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"

/* Simple true NRU replacement policy */

class RNDPolicyL2_kidRi : public AbstractReplacementPolicy {
 public:

  RNDPolicyL2_kidRi(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a); //SOLO PARA QUE COMPILE
  RNDPolicyL2_kidRi(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~RNDPolicyL2_kidRi();

  void touch(Index set, Index way, Time time);
  Index getVictim(Index set) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  
  bool subSet(L2Cache_Entry *a, uint set, Time p) const;
  
  Index* m_pointer;

  void printStats(ostream& out) const;

};


//SOLO PARA QUE COMPILE
inline
RNDPolicyL2_kidRi::RNDPolicyL2_kidRi(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
RNDPolicyL2_kidRi::RNDPolicyL2_kidRi(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  srand(time(NULL));
  m_cache = a;
  m_pointer = new Index(0);
}

inline
RNDPolicyL2_kidRi::~RNDPolicyL2_kidRi()
{
}

inline 
void RNDPolicyL2_kidRi::touch(Index set, Index index, Time time){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);
  
  if(time==-1)
  {
    for (uint i=0; i < m_assoc; i++) if (m_last_ref_ptr[set][i]==2) m_last_ref_ptr[set][i]=1;
    m_last_ref_ptr[set][index]=2;
    
  } else
  {
    m_last_ref_ptr[set][index]=0;
  }

}

inline
Index RNDPolicyL2_kidRi::getVictim(Index set) const {
  //  assert(m_assoc != 0);
  //  assert(m_assoc != 0);
  uint i = 0;
  L2Cache_Entry *p;
 
  uint entries[m_assoc];
 
  
	for(int k=0; k<4; k++)  
	{
	   uint nEntries=0;
	  //look for a member of each set
	  for (i=0; i < m_assoc; i++) {
	    p=&(*m_cache)[set][i];
		if(subSet(p, k, m_last_ref_ptr[set][i])) {
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
bool RNDPolicyL2_kidRi::subSet(L2Cache_Entry *a, uint set, Time p) const
{
/*  if(a->m_Permission == AccessPermission_NotPresent ||
        a->m_Permission == AccessPermission_Invalid)
    return false;
*/
  
  switch(set)
  {
    //conjunto de los bloques que no tienen copia por debajo
    case 0:
      return a->m_Sharers.count()==0 && p==2;
      break;
    case 1:
      return a->m_Sharers.count()==0 && p==1;
      break;
    case 2:
      return a->m_Sharers.count()==0 && p==0;
      break;
    case 3:
      return a->m_Sharers.count()!=0;
    break;
    default:
      assert(0);
    break;
    
  }
  assert(0);
  return false;
  
}
inline
void RNDPolicyL2_kidRi::printStats(ostream& out) const
{

}
#endif // PSEUDONRUBITS_H
