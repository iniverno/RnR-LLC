
#ifndef RNDPolicyL2_kibRP_H
#define RNDPolicyL2_kibRP_H

#include "AbstractReplacementPolicy.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"
#include <time.h>

/* Simple true NRU replacement policy */

class RNDPolicyL2_kibRP : public AbstractReplacementPolicy {
 public:

  RNDPolicyL2_kibRP(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a); //SOLO PARA QUE COMPILE
  RNDPolicyL2_kibRP(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~RNDPolicyL2_kibRP();

  void touch(Index set, Index way, Time time);
  Index getVictim(Index set) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  
  bool subSet(L2Cache_Entry *a, uint set) const;
  
  Index* m_pointer;

  void printStats(ostream& out) const;

};


//SOLO PARA QUE COMPILE
inline
RNDPolicyL2_kibRP::RNDPolicyL2_kibRP(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
RNDPolicyL2_kibRP::RNDPolicyL2_kibRP(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{

  srand(time(NULL));
  m_cache = a;
  m_pointer = new Index(0);
  
  cerr << "HHHOLA!" << endl;
}

inline
RNDPolicyL2_kibRP::~RNDPolicyL2_kibRP()
{
}

inline 
void RNDPolicyL2_kibRP::touch(Index set, Index index, Time time){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  //(*m_cache)[set][index].m_uses = 1;

}

inline
Index RNDPolicyL2_kibRP::getVictim(Index set) const {
  //  assert(m_assoc != 0);
  uint i=0;
  
  L2Cache_Entry *p;
 
  uint entries[m_assoc];
  
  
	for(int k=0; k<3; k++)  
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
	  if(nEntries) return entries[rand() % nEntries];
	}  
  
    assert(0);
  return -1;
  
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);
}

inline 
bool RNDPolicyL2_kibRP::subSet(L2Cache_Entry *a, uint subset) const
{
//  if(a->m_Permission == AccessPermission_NotPresent ||
//        a->m_Permission == AccessPermission_Invalid)
//    return false;

 
  switch(subset)
  {
    //conjunto de los bloques que no tienen copia por debajo
    case 0:
      return a->m_Sharers.count()==0 && !(a->m_reuseL1==2 || a->m_reuseL1==4);
    break;
    case 1:
      return a->m_Sharers.count()==0 && (a->m_reuseL1==2 || a->m_reuseL1==4);
    break;
    case 2:
      return a->m_Sharers.count()!=0;
    break;
    
    default:
    break;
    
  }
  
    assert(0);
  return false;
  
}
inline
void RNDPolicyL2_kibRP::printStats(ostream& out) const
{

}

#endif // PSEUDONRUBITS_H
