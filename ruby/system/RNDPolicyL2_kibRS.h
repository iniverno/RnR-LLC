
#ifndef RNDPolicyL2_kibRS_H
#define RNDPolicyL2_kibRS_H

#include "AbstractReplacementPolicy.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"
#include <time.h>

/* Simple true NRU replacement policy */

class RNDPolicyL2_kibRS : public AbstractReplacementPolicy {
 public:

  RNDPolicyL2_kibRS(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a); //SOLO PARA QUE COMPILE
  RNDPolicyL2_kibRS(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  ~RNDPolicyL2_kibRS();

  void touch(Index set, Index way, Time time);
  Index getVictim(Index set) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  
  bool subSet(L2Cache_Entry *a, uint set) const;
  uint whatSubSet(L2Cache_Entry *a) const;
  
  Index* m_pointer;
  
  mutable Histogram  m_histoSpace[2];

  void printStats(ostream& out) const;

};


//SOLO PARA QUE COMPILE
inline
RNDPolicyL2_kibRS::RNDPolicyL2_kibRS(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
RNDPolicyL2_kibRS::RNDPolicyL2_kibRS(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  srand(time(NULL));
  m_cache = a;
  m_pointer = new Index(0);
}

inline
RNDPolicyL2_kibRS::~RNDPolicyL2_kibRS()
{
	cerr << "Aqui se invoca al destructor" << endl;
	cerr << "Histograma sobre bloques no comprometidos:" << endl;
	cerr << m_histoSpace[0] << endl;
	
	cerr << "Histograma sobre bloques reusados:" << endl;
	cerr << m_histoSpace[1] << endl;
}

inline 
void RNDPolicyL2_kibRS::touch(Index set, Index index, Time time){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  //(*m_cache)[set][index].m_uses = 1;

}

inline
Index RNDPolicyL2_kibRS::getVictim(Index set) const {
  //  assert(m_assoc != 0);
  uint i=0;
  
  L2Cache_Entry *p;
 
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

inline 
bool RNDPolicyL2_kibRS::subSet(L2Cache_Entry *a, uint subset) const
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
uint RNDPolicyL2_kibRS::whatSubSet(L2Cache_Entry *a) const
{
  if(a->m_Sharers.count()==0 && !a->m_reused) return 0;
  if(a->m_Sharers.count()==0 && a->m_reused) return 1;
  if(a->m_Sharers.count()!=0) return 2;
  
  assert(0);
  return -1;
  
}

inline
void RNDPolicyL2_kibRS::printStats(ostream& out) const
{
	cerr << "Histograma sobre bloques no comprometidos:" << endl;
	cerr << m_histoSpace[0] << endl;
	
	cerr << "Histograma sobre bloques reusados:" << endl;
	cerr << m_histoSpace[1] << endl;
}
#endif // PSEUDONRUBITS_H
