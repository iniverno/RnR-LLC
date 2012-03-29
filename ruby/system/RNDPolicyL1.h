
#ifndef RNDPolicyL1_H
#define RNDPolicyL1_H

#include "AbstractReplacementPolicy.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"
/* Simple true NRU replacement policy */

class RNDPolicyL1 : public AbstractReplacementPolicy {
 public:

  RNDPolicyL1(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a); //SOLO PARA QUE COMPILE
  RNDPolicyL1(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~RNDPolicyL1();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<L1Cache_Entry> > *m_cache;
  
  
  Index* m_pointer;
  uint64* m_Xn;
  uint m_M;
    void printStats(ostream& out);
    
    void printStats(ostream& out) const;

};


//SOLO PARA QUE COMPILE
inline
RNDPolicyL1::RNDPolicyL1(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
RNDPolicyL1::RNDPolicyL1(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{

}

inline
RNDPolicyL1::~RNDPolicyL1()
{
}

inline 
void RNDPolicyL1::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

}

inline
Index RNDPolicyL1::getVictim(Index set, uint proc) const {
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
void RNDPolicyL1::printStats(ostream& out) const
{}
#endif // PSEUDONRUBITS_H
