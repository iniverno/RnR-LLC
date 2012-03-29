
#ifndef quickPLIaPolicy_H
#define quickPLIaPolicy_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"
#include <time.h>

/* Simple true NRU replacement policy */

class quickPLIaPolicy : public AbstractReplacementPolicyQuick {
 public:

  quickPLIaPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickPLIaPolicy();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<CacheEntryQuick> > *m_cache;
  
  bool subSet(CacheEntryQuick *a, uint set) const;
  uint whatSubSet(CacheEntryQuick *a) const;
  
  Index* m_pointer;
  
  mutable Histogram  m_histoSpace[2];
  mutable Histogram  m_histoSpaceCore[16];

  void printStats(ostream& out, char* name) ;
  void printStats(ostream& out) ;
  
  uint m_steps[16];
};


inline
quickPLIaPolicy::quickPLIaPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  cerr << "Constructor quickPLI" << endl;
  srand(time(NULL));
  m_cache = a;
  m_pointer = new Index(0);
  
  m_steps[0]=1;
  m_steps[1]=2;
  m_steps[2]=3;
  m_steps[3]=4;
  
  m_steps[4]=5;
  m_steps[5]=6;
  m_steps[6]=7;
  m_steps[7]=8;
  
  m_steps[8]=9;
  m_steps[9]=10;
  m_steps[10]=11;
  m_steps[11]=12;
  
  m_steps[12]=13;
  m_steps[13]=14;
  m_steps[14]=15;
  m_steps[15]=16;
  
}

inline
quickPLIaPolicy::~quickPLIaPolicy()
{
	cerr << "Aqui se invoca al destructor" << endl;
	cerr << "Histograma sobre bloques no comprometidos:" << endl;
	cerr << m_histoSpace[0] << endl;
	
	cerr << "Histograma sobre bloques reusados:" << endl;
	cerr << m_histoSpace[1] << endl;
}

inline 
void quickPLIaPolicy::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);
 Time  smallest_time;
  Index smallest_index;

	Time aux;
  //(*m_cache)[set][index].m_uses = 1;
  if( time==0 )
  {
  	smallest_time = 0; smallest_index=0;
	for (unsigned int i=0; i < m_assoc; i++) {
		aux = m_last_ref_ptr[set][i];
    //assert(m_cache[cacheSet][i].m_Permission != AccessPermission_NotPresent);
    	if (aux > smallest_time){
      		smallest_index = i;
      		smallest_time = aux;
    	}
  	}

  	
  	if(m_last_ref_ptr[set][smallest_index]!=m_assoc) m_last_ref_ptr[set][index] = m_last_ref_ptr[set][smallest_index] + 1;
  	
  } else {
  	m_histoSpace[0].add( m_last_ref_ptr[set][index]);
  	m_histoSpaceCore[proc].add( m_last_ref_ptr[set][index]);
  }
  
}

inline
Index quickPLIaPolicy::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  uint i=0;
  
  CacheEntryQuick *p;
 
  uint entries[3][16];
  uint nEntries[] = {0,0,0};
  uint rnd[] = {0,0,0 };
  uint flag[] = {0,0,0};
  
  uint total[] = {0,0,0};
  uint steps[3][16];
  
  uint k;
  
  
  for (i=0; i < m_assoc ; i++) {
	p=&(*m_cache)[set][i];
	k= g_KIB==1 ? whatSubSet(p) : 0;	
	entries[k][nEntries[k]] = i;
	
	//total[k] += m_last_ref_ptr[set][i];
	//steps[k][nEntries[k]++] = m_last_ref_ptr[set][i];
	total[k] += m_steps[m_last_ref_ptr[set][i] - 1];
	steps[k][nEntries[k]++] = m_steps[m_last_ref_ptr[set][i] - 1];
  }

	for(int k=0; k<2; k++) {
		//if(k<2)m_histoSpace[k].add(nEntries[k]);
		if(nEntries[k]) {
			uint aux= rand() % total[k];
			uint res = 0;
			for (i=0; i < nEntries[k]; i++) {
				res += steps[k][i];  //marcamos intervalo
				if(aux < res) {
					//envejecemos los m‡s j—venes que la v’ctima
					for (uint j=0; j < m_assoc; j++) (m_last_ref_ptr[set][entries[k][i]] < m_last_ref_ptr[set][j] ? m_last_ref_ptr[set][j]-- : 0);
					m_last_ref_ptr[set][entries[k][i]] = m_assoc; 
					
					return entries[k][i];  //si el generado esta en el intervalo ya esta
				}
			}			
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
bool quickPLIaPolicy::subSet(CacheEntryQuick *a, uint subset) const
{
//  if(a->m_Permission == AccessPermission_NotPresent ||
//        a->m_Permission == AccessPermission_Invalid)
//    return false;

  
  switch(subset)
  {
    //conjunto de los bloques que no tienen copia por debajo
    case 0:
      return a->m_Sharers.count()==0;
    break;
    case 1:
      return a->m_Sharers.count()!=0 ;
    break;
    
    default:
    break;
    
  }
  
    assert(0);
  return false;
  
}

inline 
uint quickPLIaPolicy::whatSubSet(CacheEntryQuick *a) const
{
  if(a->m_Sharers.count()==0 ) return 0;
  if(a->m_Sharers.count()!=0) return 1;
  
  assert(0);
  return -1;
  
}

inline
void quickPLIaPolicy::printStats(ostream& out, char* name) 
{
	out << name << "_hit_position_histogram:\t" << m_histoSpace[0] << endl;
	for(int i=0; i<RubyConfig::numberOfProcessors(); i++)  out << name << "_hit_position_histogram_thread_" << i << ":\t" << m_histoSpaceCore[i] << endl;
	
}

inline
void quickPLIaPolicy::printStats(ostream& out) 
{

	for(int i=0; i<RubyConfig::numberOfProcessors(); i++) cerr << "Core " << i << ": " << m_histoSpaceCore[i] << endl;	
}
#endif // PSEUDONRUBITS_H
