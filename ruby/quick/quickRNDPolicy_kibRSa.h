
#ifndef quickRNDPolicy_kibRSa_H
#define quickRNDPolicy_kibRSa_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"
#include <time.h>

/* Simple true NRU replacement policy */

class quickRNDPolicy_kibRSa : public AbstractReplacementPolicyQuick {
 public:

  quickRNDPolicy_kibRSa(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickRNDPolicy_kibRSa();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<CacheEntryQuick> > *m_cache;
  void replacementLower(Index set, Index way)  ;
  
  bool subSet(CacheEntryQuick *a, uint set) const;
  uint whatSubSet(CacheEntryQuick *a) const;
  
  Index* m_pointer;
  
  mutable Histogram  m_histoSpace[2];

  void printStats(ostream& out, char* name) ;
  void printStats(ostream& out) ;

  
};


inline
quickRNDPolicy_kibRSa::quickRNDPolicy_kibRSa(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  srand(time(NULL));
  m_cache = a;
  m_pointer = new Index(0);
}

inline
quickRNDPolicy_kibRSa::~quickRNDPolicy_kibRSa()
{
}

inline 
void quickRNDPolicy_kibRSa::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  //(*m_cache)[set][index].m_uses = 1;
	if(m_nReused[set] > m_assoc-4) 
	for(uint i=0; i<m_assoc; i++) 
	{
		(*m_cache)[set][i].m_reused = false;
		m_nReused[set]=0;
	}
	
}

inline
Index quickRNDPolicy_kibRSa::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  uint i=0;
  
  CacheEntryQuick *p;
 
  uint entries[3][16];
  uint nEntries[] = {0,0,0};
  uint rnd[] = {0,0,0 };
  uint flag[] = {0,0,0};
  
  uint k;
  for (i=0; i < m_assoc ; i++) {
	p=&(*m_cache)[set][i];
	k=whatSubSet(p);	
	entries[k][nEntries[k]++] = i;
	if(flag[k]) rnd[k] += i&1; //generamos nœmeros entre 0 y nEntries[k]
	flag[k]=1;
  }
  
	for(int k=0; k<3; k++) {
		if(k<2)m_histoSpace[k].add(nEntries[k]);
		if(nEntries[k]) return entries[k][rnd[k]];
	}
	
    assert(0);
  return -1;
  
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);
}

inline void quickRNDPolicy_kibRSa::replacementLower(Index set, Index way)  {
}

inline 
bool quickRNDPolicy_kibRSa::subSet(CacheEntryQuick *a, uint subset) const
{
//  if(a->m_Permission == AccessPermission_NotPresent ||
//        a->m_Permission == AccessPermission_Invalid)
//    return false;

  
  switch(subset)
  {
    //conjunto de los bloques que no tienen copia por debajo
    case 0:
      return a->m_Sharers.count()==0 && !a->m_reused;
    break;
    case 1:
      return a->m_Sharers.count()==0 && a->m_reused;
    break;
    case 2:
      return a->m_Sharers.count()!=0;
    break;
    
    default:
    break;
    
  }
  
    assert(0);
  return false;
  
}

inline 
uint quickRNDPolicy_kibRSa::whatSubSet(CacheEntryQuick *a) const
{
  if(a->m_Sharers.count()==0 && !a->m_reused) return 0;
  if(a->m_Sharers.count()==0 && a->m_reused) return 1;
  if(a->m_Sharers.count()!=0) return 2;
  
  assert(0);
  return -1;
  
}

inline
void quickRNDPolicy_kibRSa::printStats(ostream& out, char* name) 
{	
	out << name << "_no_reused_segment_size_histogram:\t" << m_histoSpace[0] << endl;
	out << name << "_reused_segment_size_histogram:\t" << m_histoSpace[1] << endl;
}

inline
void quickRNDPolicy_kibRSa::printStats(ostream& out) 
{

}
#endif // PSEUDONRUBITS_H
