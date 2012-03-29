

#ifndef SHiPPolicy_H
#define SHiPPolicy_H

#include "AbstractReplacementPolicy.h"
#include "System.h"

#define DEBUG_SET 0
#define DEBUGGED 1625

#define DISTANT_VALUE ((1<<g_RRIP_N_BITS) - 1) //  =LRU = it will be chosen as victim

/* Simple true NRU replacement policy */

class SHiPPolicy : public AbstractReplacementPolicy {
 public:

  SHiPPolicy(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  SHiPPolicy(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a);
  
  ~SHiPPolicy();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  
  bool subSet(L2Cache_Entry *a, uint set) const;
  uint whatSubSet(L2Cache_Entry &a) const;
  uint countSegments(uint set, uint what) const;
  void replacementLower(Index set, Index way) const;
  
  Index* m_pointer;

  void printStats(ostream& out, char* name);
  void printStats(ostream& out) const;
  void clearStats() ;
  
  int** R;
  uint m_version;
};


	inline void
SHiPPolicy::clearStats(){}


inline
SHiPPolicy::SHiPPolicy(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
m_cache=a;
}
inline
SHiPPolicy::SHiPPolicy(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{

}
inline
SHiPPolicy::~SHiPPolicy()
{
}


inline void SHiPPolicy::replacementLower(Index set, Index way)  const {

}
 
 
inline 
void SHiPPolicy::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);
	L2Cache_Entry &p=(*m_cache)[set][index];
	
	if(time==0) {
	  	if(DEBUG_SET && set==DEBUGGED) {
  			if(DEBUG_SET && set==DEBUGGED) cerr << "INSERTION at set " << set  << " way: " << index << endl;
    		for(int i=0; i<m_assoc; i++) cerr  << this << "\t" << (*m_cache)[set][i].m_Address  << "\t" << (*m_cache)[set][i].m_RRPV << endl;
  		}

		if(g_system_ptr->m_SHCTTable->counter((*m_cache)[set][index].m_PC)) {
			p.m_RRPV = DISTANT_VALUE-1;	
		}
		else {
			p.m_RRPV = DISTANT_VALUE;  // En el paper no está explicado
		}
		//p.m_RRPV = DISTANT_VALUE-1;
		
	} else {
	  	if(DEBUG_SET && set==DEBUGGED) {
  			if(DEBUG_SET && set==DEBUGGED) cerr << "HIT at set " << set  << " way: " << index << endl;
    		for(int i=0; i<m_assoc; i++) cerr  << this << "\t" << (*m_cache)[set][i].m_Address  << "\t" << (*m_cache)[set][i].m_RRPV << endl;
  		}

  		//p.m_RRPV > 0 ? p.m_RRPV-- : 0;  //versión basada en frecuencia
  		g_system_ptr->m_SHCTTable->hit((*m_cache)[set][index].m_PC);
  		p.m_RRPV = 0;
  	}
		
}



inline
Index SHiPPolicy::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  
  if(DEBUG_SET && set==DEBUGGED) {
  	if(DEBUG_SET && set==DEBUGGED) cerr << "getVictim at set " << set << endl;
    for(int i=0; i<m_assoc; i++) cerr  << this << "\t" << (*m_cache)[set][i].m_Address  << "\t" << (*m_cache)[set][i].m_RRPV << endl;
  }

	L2Cache_Entry *p;
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
				if(0 && g_PROTEGE_RRIP && p->m_Sharers.count() > 0) {
					p->m_RRPV = DISTANT_VALUE - 1;
					k++;
				}
				else {
					g_system_ptr->m_SHCTTable->victim((*m_cache)[set][i].m_PC, (*m_cache)[set][i].m_reused);
					return i;
				}
			}
		}
		if(k==m_assoc) { //caso patologico
			g_system_ptr->m_SHCTTable->victim((*m_cache)[set][0].m_PC, (*m_cache)[set][0].m_reused);
			return 0;
		}
		//si no lo encontramos incrementamos todos y repetimos
		for(uint i = 0; i < m_assoc; i++) {
			//cerr << "KAKAKAKAKAKAKAK" << endl;
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
bool SHiPPolicy::subSet(L2Cache_Entry *a, uint set) const
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
uint SHiPPolicy::whatSubSet(L2Cache_Entry &a) const
{
  if(a.m_Sharers.count()==0 && !a.m_reused) return 0;
  if(a.m_Sharers.count()==0 && a.m_reused) return 1;
  if(a.m_Sharers.count()!=0) return 2;

  assert(0);
  return -1;
  
}

inline 
uint SHiPPolicy::countSegments(uint set, uint what) const
{
	uint aux=0;
	for(uint i=0; i<m_assoc; i++) if(whatSubSet((*m_cache)[set][i]) == what) aux++;
	
	return aux;
	
	uint res[]={0,0,0};
	
	for(uint i=0; i<3; i++) res[whatSubSet((*m_cache)[set][i])]++;
	
	//return res;
  
}

inline
void SHiPPolicy::printStats(ostream& out, char* name)  
{ int a=0;}

inline
void SHiPPolicy::printStats(ostream& out)  const
{ int a=0;
g_system_ptr->m_SHCTTable->printStats(out, "hola");
}
#endif // PSEUDONRUBITS_H
