
#ifndef quickNRUPolicy_H
#define quickNRUPolicy_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true NRU replacement policy */

class quickNRUPolicy : public AbstractReplacementPolicyQuick {
 public:

  quickNRUPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickNRUPolicy();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<CacheEntryQuick> > *m_cache;
  void replacementLower(Index set, Index way)  ;
  
  Index* m_pointer;

  void printStats(ostream& out, char* name) ;
  void printStats(ostream& out) ;
  void clearStats() ;
};



inline
quickNRUPolicy::quickNRUPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_cache = a;
  m_pointer = new Index(0);
}

inline
quickNRUPolicy::~quickNRUPolicy()
{
}

inline 
void quickNRUPolicy::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  uint total = 0;
  uint used = 0;
  
  (*m_cache)[set][index].m_NRU = 1;
  
  for (unsigned int i=0; i < m_assoc; i++) {    
      total++;
      (*m_cache)[set][i].m_NRU ? used++ : 0;
  }
  
  if(total==used)
  {
    for (unsigned int i=0; i < m_assoc; i++) 
    {
     
      (*m_cache)[set][i].m_NRU = 0;
      
    }
    (*m_cache)[set][index].m_NRU = 1;
  }
}

inline
Index quickNRUPolicy::getVictim(Index set, uint proc) const {
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

inline void quickNRUPolicy::replacementLower(Index set, Index way)  {
}

inline
void quickNRUPolicy::printStats(ostream& out, char* name)  
{ int a=0;}

inline
void quickNRUPolicy::printStats(ostream& out)  
{ int a=0;}

inline
void quickNRUPolicy::clearStats()  
{ int a=0;}

#endif // PSEUDONRUBITS_H
