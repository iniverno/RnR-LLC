

#ifndef quickNRUPolicy_qbs2_H
#define quickNRUPolicy_qbs2_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true NRU replacement policy */

class quickNRUPolicy_qbs2 : public AbstractReplacementPolicyQuick {
 public:

  quickNRUPolicy_qbs2(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickNRUPolicy_qbs2();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<CacheEntryQuick> > *m_cache;
  
  bool subSet(CacheEntryQuick *a, uint set) const;
  uint whatSubSet(CacheEntryQuick &a) const;
  void replacementLower(Index set, Index way)  ;
  
  Index* m_pointer;

  void printStats(ostream& out, char* name);
  void printStats(ostream& out);

};




inline
quickNRUPolicy_qbs2::quickNRUPolicy_qbs2(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_cache = a;
  m_pointer = new Index(0);
}

inline
quickNRUPolicy_qbs2::~quickNRUPolicy_qbs2()
{
}

inline 
void quickNRUPolicy_qbs2::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

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
Index quickNRUPolicy_qbs2::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
 
 	bool present[]={false,false};
 	
 	CacheEntryQuick *p;
 	uint k=0;
 	
	while(k<2) {
		for(uint i =0; i < m_assoc; i++) {
			p = &(*m_cache)[set][i];
			if(subSet(p, k)) {
				if(!p->m_NRU) return i;
				present[k]=true;
			}
		}
		if(present[k]) {
			for(uint i =0; i < m_assoc; i++) {
				p = &(*m_cache)[set][i];
				if(subSet(p, k)) {
					p->m_NRU = false;
				}
			}
		}
		else {
			k++;
		}
	}
	

  assert(0);
  return -1;
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);
}


inline void quickNRUPolicy_qbs2::replacementLower(Index set, Index way)  {
}


inline 
bool quickNRUPolicy_qbs2::subSet(CacheEntryQuick *a, uint set) const
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
uint quickNRUPolicy_qbs2::whatSubSet(CacheEntryQuick &a) const
{
  if(a.m_Sharers.count()==0 ) return 0;
  if(a.m_Sharers.count()!=0) return 1;
  
  assert(0);
  return -1;
  
}

inline
void quickNRUPolicy_qbs2::printStats(ostream& out, char* name)  
{ int a=0;}

inline
void quickNRUPolicy_qbs2::printStats(ostream& out)  
{ int a=0;}
#endif // PSEUDONRUBITS_H
