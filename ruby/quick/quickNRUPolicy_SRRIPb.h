

#ifndef quickNRUPolicy_SRRIPb_H
#define quickNRUPolicy_SRRIPb_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"


#define DISTANT_VALUE ((1<<g_RRIP_N_BITS) - 1) //  =LRU = it will be chosen as victim

/* Simple true NRU replacement policy */

class quickNRUPolicy_SRRIPb : public AbstractReplacementPolicyQuick {
 public:

  quickNRUPolicy_SRRIPb(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a, uint version);
  ~quickNRUPolicy_SRRIPb();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<CacheEntryQuick> > *m_cache;
  
  bool subSet(CacheEntryQuick *a, uint set) const;
  uint whatSubSet(CacheEntryQuick &a) const;
  uint countSegments(uint set, uint what) const;
  void replacementLower(Index set, Index way) ;
  
  Index* m_pointer;

  void printStats(ostream& out, char* name);
  void printStats(ostream& out);
  void clearStats() ;
  
  int** R;
  uint m_version;
};


	inline void
quickNRUPolicy_SRRIPb::clearStats(){}


inline
quickNRUPolicy_SRRIPb::quickNRUPolicy_SRRIPb(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a, uint version)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_version = version;
  m_cache = a;
}

inline
quickNRUPolicy_SRRIPb::~quickNRUPolicy_SRRIPb()
{
}


inline void quickNRUPolicy_SRRIPb::replacementLower(Index set, Index way)  {

}
 
 
 
inline 
void quickNRUPolicy_SRRIPb::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);
	CacheEntryQuick &p=(*m_cache)[set][index];
	
	if(time==0) {
		p.m_RRPV = DISTANT_VALUE-1;
	} else {
  		//p.m_RRPV > 0 ? p.m_RRPV-- : 0;  //versi—n basada en frecuencia
  		p.m_RRPV = 0;
  	}
	
	
}

inline
Index quickNRUPolicy_SRRIPb::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  
	CacheEntryQuick *p;
	bool found = false;
	
	
	while(!found)
	{
	int k=0;
		//buscamos el primero con el RRPV a 2^m-1
		for(uint i = 0; i < m_assoc; i++) {
			p = &(*m_cache)[set][i];
			//cerr << "p->m_RRPV: " << p->m_RRPV << " DISTANT_VALUE: " << DISTANT_VALUE<< endl;	
			if(p->m_RRPV == DISTANT_VALUE ) {
				//found = true;
				if(g_PROTEGE_RRIP && p->m_Sharers.count() > 0) {
					p->m_RRPV = DISTANT_VALUE - 1;
					k++;
				}
				else {
					return i;
				}
			}
		}
		if(k==m_assoc) { //caso patologico
			return 0;
		}
		//si no lo encontramos incrementamos todos y repetimos
		for(uint i = 0; i < m_assoc; i++) {
			p = &(*m_cache)[set][i];
			p->m_RRPV < DISTANT_VALUE ? p->m_RRPV++ : 0;
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
bool quickNRUPolicy_SRRIPb::subSet(CacheEntryQuick *a, uint set) const
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
uint quickNRUPolicy_SRRIPb::whatSubSet(CacheEntryQuick &a) const
{
  if(a.m_Sharers.count()==0 && !a.m_reused) return 0;
  if(a.m_Sharers.count()==0 && a.m_reused) return 1;
  if(a.m_Sharers.count()!=0) return 2;

  assert(0);
  return -1;
  
}

inline 
uint quickNRUPolicy_SRRIPb::countSegments(uint set, uint what) const
{
	uint aux=0;
	for(uint i=0; i<m_assoc; i++) if(whatSubSet((*m_cache)[set][i]) == what) aux++;
	
	return aux;
	
	uint res[]={0,0,0};
	
	for(uint i=0; i<3; i++) res[whatSubSet((*m_cache)[set][i])]++;
	
	//return res;
  
}

inline
void quickNRUPolicy_SRRIPb::printStats(ostream& out, char* name)  
{ int a=0;}

inline
void quickNRUPolicy_SRRIPb::printStats(ostream& out)  
{ int a=0;}
#endif // PSEUDONRUBITS_H
