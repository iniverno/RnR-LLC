

#ifndef NRRjPolicyL2_H
#define NRRjPolicyL2_H

#include "AbstractReplacementPolicy.h"

/* Simple true NRU replacement policy */

class NRRjPolicyL2 : public AbstractReplacementPolicy {
 public:

  NRRjPolicyL2(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  NRRjPolicyL2(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a);
  ~NRRjPolicyL2();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  
  bool subSet(L2Cache_Entry *a, uint set) const;
  uint whatSubSet(L2Cache_Entry &a) const;
  void replacementLower(Index set, Index way) const ;
  
  Index* m_pointer;

  void printStats(ostream& out, char* name) const;
  void printStats(ostream& out) const;

  mutable int trend;
  
};




inline
NRRjPolicyL2::NRRjPolicyL2(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  m_cache = a;
  m_pointer = new Index(0);
  	trend = 1;

}

inline
NRRjPolicyL2::NRRjPolicyL2(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
	trend = 1;
}


inline
NRRjPolicyL2::~NRRjPolicyL2()
{
}

inline 
void NRRjPolicyL2::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if(time==0) return;
  
  L2Cache_Entry &p=(*m_cache)[set][index], *q;
    
  uint total = 0;
  uint used = 0;
  
  p.m_NRU = 1;
  
  for (unsigned int i=0; i < m_assoc; i++) {
    q=&(*m_cache)[set][i];
      q->m_NRU ? used++ : 0;
    
  }
  
  if(m_assoc == used)
  {
    for (unsigned int i=0; i < m_assoc; i++) 
    {
      q=&(*m_cache)[set][i];
      q->m_NRU = 0;
      
    }
    p.m_NRU = 1;
  }

	
}

inline
Index NRRjPolicyL2::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  
// Randomly chose one not reused  nor private element, starting 
	trend*=-1;
  	for (int i= (trend==1 ? 0 : m_assoc-1); i < m_assoc && i>=0; i+= trend) 
    	if(!(*m_cache)[set][i].m_NRU)  return i;

   
  assert(0);
  return -1;
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);
}

inline void NRRjPolicyL2::replacementLower(Index set, Index way) const {
}

inline 
bool NRRjPolicyL2::subSet(L2Cache_Entry *a, uint set) const
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
uint NRRjPolicyL2::whatSubSet(L2Cache_Entry &a) const
{
return 0;

  assert(0);
  return -1;
  
}

inline
void NRRjPolicyL2::printStats(ostream& out, char* name) const 
{ int a=0;}

inline
void NRRjPolicyL2::printStats(ostream& out)  const
{ int a=0;}
#endif // PSEUDONRUBITS_H
