
#ifndef quickRNDPolicy_H
#define quickRNDPolicy_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true NRU replacement policy */

class quickRNDPolicy : public AbstractReplacementPolicyQuick {
 public:

  quickRNDPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickRNDPolicy();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<CacheEntryQuick> > *m_cache;
  void replacementLower(Index set, Index way) ;
  bool subSet(CacheEntryQuick *a, uint set) const;
  
  Index* m_pointer;
  uint64* m_Xn;
  uint m_M;
  void printStats(ostream& out, char* name);
  void printStats(ostream& out);
  void clearStats();
};



inline
quickRNDPolicy::quickRNDPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
}

inline
quickRNDPolicy::~quickRNDPolicy()
{
}

inline 
void quickRNDPolicy::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

}

inline
Index quickRNDPolicy::getVictim(Index set, uint proc) const {
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

inline void quickRNDPolicy::replacementLower(Index set, Index way)  {
}

inline 
bool quickRNDPolicy::subSet(CacheEntryQuick *a, uint set) const
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
void quickRNDPolicy::printStats(ostream& out, char* name) 
{ int a=0;}

inline
void quickRNDPolicy::printStats(ostream& out) 
{ int a=0;}

inline
void quickRNDPolicy::clearStats() 
{ int a=0;}
#endif // PSEUDONRUBITS_H
