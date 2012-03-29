/*Probar DRRIP con 4 cores

Tocar a la salida de las privadas en LRR

*/



#ifndef quickNRRaPolicy_H
#define quickNRRaPolicy_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true NRU replacement policy */

class quickNRRaPolicy : public AbstractReplacementPolicyQuick {
 public:

  quickNRRaPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickNRRaPolicy();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<CacheEntryQuick> > *m_cache;
  
  bool subSet(CacheEntryQuick *a, uint set) const;
  uint whatSubSet(CacheEntryQuick &a) const;
  void replacementLower(Index set, Index way)  ;
  
  Index* m_pointer;

  void printStats(ostream& out, char* name);
  void printStats(ostream& out);
  void clearStats() ;
  
  Vector<uint64> m_nH [2];
  Vector<uint64> m_nTH;
  
};




inline
quickNRRaPolicy::quickNRRaPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_cache = a;
  m_pointer = new Index(0);
  
  m_nH[0].setSize(RubyConfig::numberOfProcsPerChip());
  m_nH[1].setSize(RubyConfig::numberOfProcsPerChip());
  m_nTH.setSize(RubyConfig::numberOfProcsPerChip());
  
  for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
  	for (int j = 0; j < 2; j++) m_nH[j][i]= 0;
  	m_nTH[i] = 0;
  }
}

inline
quickNRRaPolicy::~quickNRRaPolicy()
{
}

inline 
void quickNRRaPolicy::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if(time==0) return;
  
  CacheEntryQuick &p=(*m_cache)[set][index], *q;

  //para la distribucion de aciertos por segmentos
  //time==1 solo puede aparecer si g_SHADOW activo
  if(time != 1) {
  	m_nH[p.m_NRU][proc]++;
  	m_nTH[proc]++;
  }

  uint total = 0;
  uint used = 0;
  
  p.m_NRU = 1;
  
  uint k= whatSubSet(p);
  for (unsigned int i=0; i < m_assoc; i++) {
    q=&(*m_cache)[set][i];
    if(whatSubSet(*q) == k) 
    {
      total++;
      q->m_NRU ? used++ : 0;
    }
  }
  
  if(total==used)
  {
    for (unsigned int i=0; i < m_assoc; i++) 
    {
      q=&(*m_cache)[set][i];
      if(whatSubSet(*q) == k) 
      {
      q->m_NRU = 0;
      }
    }
    p.m_NRU = 1;
  }

}

inline
Index quickNRRaPolicy::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  
  CacheEntryQuick *p;
  int ret[]={-1,-1,-1,-1};
  int pres[]={0,0,0,0};

  Index sem= *m_pointer;
  Index i= sem;
  uint s;
  do {
  	p = &(*m_cache)[set][i];
  	s = whatSubSet(*p);
  	pres[s]=1;
  	if(ret[s]==-1 && p->m_NRU==0) ret[s] = i;
  	i = (i == m_assoc-1) ? 0 : i+1;
  } while (i != sem);
  	
  for(unsigned int k=0; k<2; k++) 
  	if(pres[k]) {
  		if(ret[k]!=-1) {
  			*m_pointer = ret[k];
	  		return ret[k];
		} else {  //caso en el que todos los elementos del segmento que nos toca est‡n a 1
			for (unsigned int j=0; j < m_assoc; j++) {
				p=&(*m_cache)[set][j];
				if(whatSubSet(*p) == k) p->m_NRU = 0;
			}
			do {
				p = &(*m_cache)[set][i];
				if(whatSubSet(*p) == k) {
					*m_pointer = (*m_pointer == m_assoc-1) ? 0 : *m_pointer+1;
					return i;
				}
				i = (i == m_assoc-1) ? 0 : i+1;
			} while (i != sem);
			assert(0);
		}
  	}
  
  
  assert(0);
  return -1;
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);
}

inline void quickNRRaPolicy::replacementLower(Index set, Index way)  {
}

inline 
bool quickNRRaPolicy::subSet(CacheEntryQuick *a, uint set) const
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
uint quickNRRaPolicy::whatSubSet(CacheEntryQuick &a) const
{
  if(a.m_Sharers.count()==0) return 0;
  else  return 1;

  assert(0);
  return -1;
  
}

inline
void quickNRRaPolicy::printStats(ostream& out, char* name)  { 
	for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
		for (int j = 0; j < 2; j++)
			out << "NRRa" << "_hit_ratio_segment_"<< j <<"_thread_" << i << ":\t" <<  (float) m_nH[j][i]/(m_nTH[i])  << endl;
	}
}

inline
void quickNRRaPolicy::printStats(ostream& out)  
{ int a=0;}

inline
void quickNRRaPolicy::clearStats()  
{
  for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
  	for (int j = 0; j < 2; j++) m_nH[j][i]= 0;
  	m_nTH[i] = 0;
  }
}
#endif // PSEUDONRUBITS_H
