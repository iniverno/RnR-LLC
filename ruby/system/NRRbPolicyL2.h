

#ifndef NRRbPolicyL2_H
#define NRRbPolicyL2_H

#include "AbstractReplacementPolicy.h"

/* Simple true NRU replacement policy */

class NRRbPolicyL2 : public AbstractReplacementPolicy {
 public:

  NRRbPolicyL2(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  NRRbPolicyL2(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a);
  ~NRRbPolicyL2();

  void touch(Index set, Index way, Time time);
  Index getVictim(Index set) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  
  bool subSet(L2Cache_Entry *a, uint set) const;
  uint whatSubSet(L2Cache_Entry &a) const;
  void replacementLower(Index set, Index way) const;
  
  Index* m_pointer;

  void printStats(ostream& out, char* name)const ;
  void printStats(ostream& out) const;

  
};




inline
NRRbPolicyL2::NRRbPolicyL2(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  m_cache = a;
  m_pointer = new Index(0);
  
}

inline
NRRbPolicyL2::NRRbPolicyL2(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}


inline
NRRbPolicyL2::~NRRbPolicyL2()
{
}

inline 
void NRRbPolicyL2::touch(Index set, Index index, Time time){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if(time==0) return;
  
  L2Cache_Entry &p=(*m_cache)[set][index], *q;
    
  uint total = 0;
  uint used = 0;
  
  p.m_NRU = 1;
  
  for (unsigned int i=0; i < m_assoc; i++) {
      q->m_NRU ? used++ : 0;
    
  }
  
  if(m_assoc==used)
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
Index NRRbPolicyL2::getVictim(Index set) const {
  //  assert(m_assoc != 0);
  
  L2Cache_Entry *p;
  int ret[]={-1,-1,-1,-1};
  int pres[]={0,0,0,0};

  Index sem= *m_pointer;
  Index i= sem;
  uint s;
  do {
  	p = &(*m_cache)[set][i];
  	s = whatSubSet(*p);
  	pres[s]=1;
  	if(ret[s]==-1 && p->m_NRU==0) ret[s] = i;
  	i = (i == m_assoc-1) ? 0 : i+1;
  } while (i != sem);
  	
  for(unsigned int k=0; k<2; k++) 
  	if(pres[k]) {
  		if(ret[k]!=-1) {
  			*m_pointer = ret[k];
	  		return ret[k];
		} else {  //caso en el que todos los elementos del segmento que nos toca est‡n a 1
			for (unsigned int j=0; j < m_assoc; j++) {
				p=&(*m_cache)[set][j];
				if(whatSubSet(*p) == k) p->m_NRU = 0;
			}
			do {
				p = &(*m_cache)[set][i];
				if(whatSubSet(*p) == k) {
					*m_pointer = (*m_pointer == m_assoc-1) ? 0 : *m_pointer+1;
					return i;
				}
				i = (i == m_assoc-1) ? 0 : i+1;
			} while (i != sem);
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

inline void NRRbPolicyL2::replacementLower(Index set, Index way) const {
}

inline 
bool NRRbPolicyL2::subSet(L2Cache_Entry *a, uint set) const
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
uint NRRbPolicyL2::whatSubSet(L2Cache_Entry &a) const
{
  if(a.m_Sharers.count()==0) return 0;
  else  return 1;

  assert(0);
  return -1;
  
}

inline
void NRRbPolicyL2::printStats(ostream& out, char* name)  const
{ int a=0;}

inline
void NRRbPolicyL2::printStats(ostream& out)  const
{ int a=0;}
#endif // PSEUDONRUBITS_H
