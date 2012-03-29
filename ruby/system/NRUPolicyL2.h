
#ifndef NRUPolicyL2_H
#define NRUPolicyL2_H

#include "AbstractReplacementPolicy.h"
#include "L2Cache_Entry.h"

/* Simple true NRU replacement policy */

class NRUPolicyL2 : public AbstractReplacementPolicy {
 public:

  NRUPolicyL2(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  NRUPolicyL2(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a);
  ~NRUPolicyL2();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;

  void replacementLower(Index set, Index way) const;
  
  Index* m_pointer;

  void printStats(ostream& out, char* name) const;
  void printStats(ostream& out) const ;

};

inline
void NRUPolicyL2::replacementLower(Index set, Index way) const
{

}

inline
NRUPolicyL2::NRUPolicyL2(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  m_cache = a;
  m_pointer = new Index(0);
  
  cerr << "NRU replacement policy L2 constructor" << endl;
}

inline
NRUPolicyL2::NRUPolicyL2(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
NRUPolicyL2::~NRUPolicyL2()
{
}

inline 
void NRUPolicyL2::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  uint used = 0;
  
  (*m_cache)[set][index].m_NRU = 1;
  
  for (unsigned int i=0; i < m_assoc; i++) {    
      (*m_cache)[set][i].m_NRU ? used++ : 0;
  }
  
  if(m_assoc==used) {
    for (unsigned int i=0; i < m_assoc; i++) {     
      (*m_cache)[set][i].m_NRU = 0;      
    }
    (*m_cache)[set][index].m_NRU = 1;
  }
}

inline
Index NRUPolicyL2::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  
  uint i= *m_pointer;
  
  do
  {
    if(!(*m_cache)[set][i].m_NRU) 
    {
      *m_pointer = (*m_pointer == m_assoc-1) ? 0 : (*m_pointer)+1;
      return i;
    }
    i = (i == m_assoc-1) ? 0 : i+1;
  } while(i!= *m_pointer);

  assert(0);
  //no hay ninguno --> todos a cero
  for (i=0; i < m_assoc; i++)  {      
        (*m_cache)[set][i].m_NRU = 0;      
  }  
  
  i= *m_pointer;
  do
  {
    if(!(*m_cache)[set][i].m_NRU) 
    {
      *m_pointer = (*m_pointer == m_assoc-1) ? 0 : (*m_pointer)+1;
      return i;
    }
    i = (i == m_assoc-1) ? 0 : i+1;
  } while(i!= *m_pointer);
  
  assert(0);
  
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);

}


inline
void NRUPolicyL2::printStats(ostream& out, char* name) const 
{ int a=0;}

inline
void NRUPolicyL2::printStats(ostream& out)  const
{ int a=0;}
#endif // PSEUDONRUBITS_H
