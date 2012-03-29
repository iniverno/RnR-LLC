
#ifndef quickDIPPolicy_H
#define quickDIPPolicy_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"


#include "replacement_state.h"
#include "dip.h"


/* Simple true NRU replacement policy */

class quickDIPPolicy : public AbstractReplacementPolicyQuick {
 public:

  quickDIPPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickDIPPolicy();

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
  
  CACHE_REPLACEMENT_STATE *state;
 
};



inline
quickDIPPolicy::quickDIPPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
	state = new CACHE_REPLACEMENT_STATE(num_sets, assoc, 0);
}

inline
quickDIPPolicy::~quickDIPPolicy()
{
}

inline 
void quickDIPPolicy::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  state->UpdateReplacementState(set, index, proc, true);
}

inline
Index quickDIPPolicy::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  //  assert(m_assoc != 0);
  //  cerr << "vic" << endl;

  
  state->UpdateReplacementState(set, m_wayOut, proc, false);
  
  Index aux = state->GetVictimInSet( set );
  

    //cerr << "vicf" << endl;
  return aux;
  
  assert(0);
  return -1;
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);
}


inline void quickDIPPolicy::replacementLower(Index set, Index way)  {
}

inline 
bool quickDIPPolicy::subSet(CacheEntryQuick *a, uint set) const
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
void quickDIPPolicy::printStats(ostream& out, char* name) 
{ int a=0;}

inline
void quickDIPPolicy::printStats(ostream& out) 
{ int a=0;}
#endif // PSEUDONRUBITS_H
