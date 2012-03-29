
#ifndef RNDPolicyL2_H
#define RNDPolicyL2_H

#include "AbstractReplacementPolicy.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"
/* Simple true NRU replacement policy */

class RNDPolicyL2 : public AbstractReplacementPolicy {
 public:

  RNDPolicyL2(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a); //SOLO PARA QUE COMPILE
  RNDPolicyL2(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~RNDPolicyL2();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  
  bool subSet(L2Cache_Entry *a, uint set) const;
  
  Index* m_pointer;
  uint64* m_Xn;
  uint m_M;
    void printStats(ostream& out);
    
    void printStats(ostream& out) const;

};


//SOLO PARA QUE COMPILE
inline
RNDPolicyL2::RNDPolicyL2(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
RNDPolicyL2::RNDPolicyL2(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  m_M = 11*19;
  
  //srand(time(NULL));
  m_Xn = new uint64;
  *m_Xn = 3;
  
  m_cache = a;
  m_pointer = new Index(0);
}

inline
RNDPolicyL2::~RNDPolicyL2()
{
}

inline 
void RNDPolicyL2::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

}

inline
Index RNDPolicyL2::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  //  assert(m_assoc != 0);
  
 /* uint64 aux = (*m_Xn * *m_Xn) % m_M;  // Xn^2 mod M
  *m_Xn = aux;
  
  aux &= 0xf;  //assert(m_assoc==16);
  
  //cerr << " " << aux;
  return aux;
  */
  
  return rand() % m_assoc;

  assert(0);
  return -1;
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);
}

inline 
bool RNDPolicyL2::subSet(L2Cache_Entry *a, uint set) const
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
void RNDPolicyL2::printStats(ostream& out) const
{}
#endif // PSEUDONRUBITS_H
