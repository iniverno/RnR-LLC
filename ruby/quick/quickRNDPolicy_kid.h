
#ifndef quickRNDPolicy_kid_H
#define quickRNDPolicy_kid_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true NRU replacement policy */

class quickRNDPolicy_kid : public AbstractReplacementPolicyQuick {
 public:

  quickRNDPolicy_kid(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickRNDPolicy_kid();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<CacheEntryQuick> > *m_cache;
  void replacementLower(Index set, Index way)  ;
  
  bool subSet(CacheEntryQuick *a, uint set) const;
  
  Index* m_pointer;

  void printStats(ostream& out, char* name);
  void printStats(ostream& out);

};


inline
quickRNDPolicy_kid::quickRNDPolicy_kid(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  srand(time(NULL));
  m_cache = a;
  m_pointer = new Index(0);
}

inline
quickRNDPolicy_kid::~quickRNDPolicy_kid()
{
}

inline 
void quickRNDPolicy_kid::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

}

inline
Index quickRNDPolicy_kid::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  //  assert(m_assoc != 0);
  uint i = 0;
  CacheEntryQuick *p;
 
  uint entries[m_assoc];
 
  
	for(int k=0; k<2; k++)  
	{
	   uint nEntries=0;
	  //look for a member of each set
	  for (i=0; i < m_assoc; i++) {
	    p=&(*m_cache)[set][i];
		if(subSet(p, k)) {
		  entries[nEntries++] = i;
	    }
	  }
	  
	  //if there is any -> we select one of them randomly
	  if(nEntries) 
	  {
	    return entries[rand() % nEntries];
	   
	  }
	}  

  assert(0);
  return -1;
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);
}


inline void quickRNDPolicy_kid::replacementLower(Index set, Index way)  {
}

inline 
bool quickRNDPolicy_kid::subSet(CacheEntryQuick *a, uint set) const
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
void quickRNDPolicy_kid::printStats(ostream& out, char* name) 
{
int a=0;
}

inline
void quickRNDPolicy_kid::printStats(ostream& out) 
{
int a=0;
}
#endif // PSEUDONRUBITS_H
