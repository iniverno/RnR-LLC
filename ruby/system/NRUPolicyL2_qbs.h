

#ifndef NRUPolicyL2_qbs_H
#define NRUPolicyL2_qbs_H

#include "AbstractReplacementPolicy.h"
#include "CacheEntryQuick.h"

/* Simple true NRU replacement policy */

class NRUPolicyL2_qbs : public AbstractReplacementPolicy {
 public:

  NRUPolicyL2_qbs(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a);
  NRUPolicyL2_qbs(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~NRUPolicyL2_qbs();

  void touch(Index set, Index way, Time time);
  Index getVictim(Index set) const;
  void replacementLower(Index set, Index way) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  
  uint whatSubSet(L2Cache_Entry &a) const;
  void replacementLower(Index set, Index way)  ;
  
  Index* m_pointer;

  void printStats(ostream& out, char* name) const;
  void printStats(ostream& out) const;

};




inline
NRUPolicyL2_qbs::NRUPolicyL2_qbs(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  m_cache = a;
  m_pointer = new Index(0);
}

inline
NRUPolicyL2_qbs::NRUPolicyL2_qbs(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{

}

inline
NRUPolicyL2_qbs::~NRUPolicyL2_qbs()
{
}


inline
void NRUPolicyL2_qbs::replacementLower(Index set, Index way) const
{

}

inline 
void NRUPolicyL2_qbs::touch(Index set, Index index, Time time){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if(time==0) return;
  
  uint total = 0;
  uint used = 0;
  
  (*m_cache)[set][index].m_NRU = true;
  
  for (unsigned int i=0; i < m_assoc; i++) {    
      total++;
      (*m_cache)[set][i].m_NRU ? used++ : 0;
  }
  
  if(total==used)
  {
    for (unsigned int i=0; i < m_assoc; i++) 
    {
     
      (*m_cache)[set][i].m_NRU = false;
      
    }
    (*m_cache)[set][index].m_NRU = true;
  }

}

inline
Index NRUPolicyL2_qbs::getVictim(Index set) const {
  //  assert(m_assoc != 0);
  
 uint used=0;
  uint i= *m_pointer;
  uint sem= i;
  
  do
  {
  	*m_pointer = (*m_pointer == m_assoc-1) ? 0 : (*m_pointer)+1;
    if(!(*m_cache)[set][i].m_NRU) 
    {
      
      
      if((*m_cache)[set][i].m_Sharers.count() > 0)
      {
		  (*m_cache)[set][i].m_NRU = 1;
		  used=0;
		  for (unsigned int j=0; j < m_assoc; j++) (*m_cache)[set][j].m_NRU ? used++ : 0;
		  if(m_assoc==used)
		  {
			for (unsigned int j=0; j < m_assoc; j++) {
			  (*m_cache)[set][j].m_NRU = 0;
			}
			(*m_cache)[set][i].m_NRU = 1;
  		  }
      }
      else 
        return i;
    }
    i = (i == m_assoc-1) ? 0 : i+1;
  } while(i!= sem);


   do
  {
    *m_pointer = (*m_pointer == m_assoc-1) ? 0 : (*m_pointer)+1;
    if(!(*m_cache)[set][i].m_NRU) 
    {
        return i;
    }
    i = (i == m_assoc-1) ? 0 : i+1;
  } while(i!= sem);
  
  assert(0);
  return -1;
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);
}


inline void NRUPolicyL2_qbs::replacementLower(Index set, Index way)  {
}




inline 
uint NRUPolicyL2_qbs::whatSubSet(L2Cache_Entry &a) const
{
  if(a.m_Sharers.count()==0 ) return 0;
  if(a.m_Sharers.count()!=0) return 1;
  
  assert(0);
  return -1;
  
}

inline
void NRUPolicyL2_qbs::printStats(ostream& out, char* name) const 
{ int a=0;}

inline
void NRUPolicyL2_qbs::printStats(ostream& out)  const
{ int a=0;}
#endif // PSEUDONRUBITS_H
