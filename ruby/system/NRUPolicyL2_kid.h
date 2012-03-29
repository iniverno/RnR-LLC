
#ifndef NRUPolicyL2_kid_H
#define NRUPolicyL2_kid_H

#include "AbstractReplacementPolicy.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"

/* Simple true NRU replacement policy */

class NRUPolicyL2_kid : public AbstractReplacementPolicy {
 public:

  NRUPolicyL2_kid(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a); //SOLO PARA QUE COMPILE
  NRUPolicyL2_kid(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~NRUPolicyL2_kid();

  void touch(Index set, Index way, Time time);
  Index getVictim(Index set) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  
  bool subSet(L2Cache_Entry *a, uint set) const;
  
  Index* m_pointer;

  void printStats(ostream& out) const;

};


//SOLO PARA QUE COMPILE
inline
NRUPolicyL2_kid::NRUPolicyL2_kid(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
NRUPolicyL2_kid::NRUPolicyL2_kid(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  m_cache = a;
  m_pointer = new Index(0);
}

inline
NRUPolicyL2_kid::~NRUPolicyL2_kid()
{
}

inline 
void NRUPolicyL2_kid::touch(Index set, Index index, Time time){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  L2Cache_Entry *p=&(*m_cache)[set][index], *q;
  
  uint total = 0;
  uint used = 0;
  
  (*m_cache)[set][index].m_uses = 1;
  
  //aux guarda si el bloque pertenece al conjunto de los que tienen copia por debajo o no
  bool aux=((*m_cache)[set][index].m_Sharers.count()==0); 
  
  for (unsigned int i=0; i < m_assoc; i++) {
    q=&(*m_cache)[set][i];
    if( (q->m_Sharers.count()==0)==aux) 
    {
      total++;
      q->m_uses ? used++ : 0;
    }
  }
  
  if(total==used)
  {
    for (unsigned int i=0; i < m_assoc; i++) 
    {
      q=&(*m_cache)[set][i];
      if((q->m_Sharers.count()==0)==aux) 
      {
      q->m_uses = 0;
      }
    }
    p->m_uses = 1;
  }
}

inline
Index NRUPolicyL2_kid::getVictim(Index set) const {
  //  assert(m_assoc != 0);
  uint i= *m_pointer;
  
  L2Cache_Entry *p;
  

for(int k=0; k<2; k++)  
{
  int flag=0;
  do
  {
    p=&(*m_cache)[set][i];
    //si es del subconjunto y tiene el bit a 0 es nuestra victima
    if(subSet(p, k)) 
    {
      if(!p->m_uses) {
        *m_pointer = (*m_pointer == m_assoc-1) ? 0 : (*m_pointer)+1;
        return i;
      }
      else {
        flag=1;
      }
    } 
    i = (i == m_assoc-1) ? 0 : i+1;
  } while(i!= *m_pointer);

  if(flag)
  {
	  //no hay ninguno pero el conjunto no esta vacio --> todos a cero
	  for (i=0; i < m_assoc; i++) {
		  p=&(*m_cache)[set][i];
		  if(subSet(p, k)) {
			p->m_uses = 0;
		  }
	  }  
	  
	  i= *m_pointer;
	  do
	  {
	    p=&(*m_cache)[set][i];
		if(subSet(p, k) && !p->m_uses) 
		{
		  *m_pointer = (*m_pointer == m_assoc-1) ? 0 : (*m_pointer)+1;
		  return i;
		}
		i = (i == m_assoc-1) ? 0 : i+1;
	  } while(i!= *m_pointer);
	  assert(0);
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
bool NRUPolicyL2_kid::subSet(L2Cache_Entry *a, uint set) const
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
void NRUPolicyL2_kid::printStats(ostream& out) const 
{}
#endif // PSEUDONRUBITS_H
