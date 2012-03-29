

#ifndef NRUPolicyL2_3SETg_H
#define NRUPolicyL2_3SETg_H

#include "AbstractReplacementPolicy.h"

/* Simple true NRU replacement policy */

class NRUPolicyL2_3SETg : public AbstractReplacementPolicy {
 public:

  NRUPolicyL2_3SETg(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a);
  NRUPolicyL2_3SETg(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a);
  ~NRUPolicyL2_3SETg();

  void touch(Index set, Index way, Time time);
  Index getVictim(Index set) const;
  void replacementLower(Index set, Index way) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  
  uint whatSubSet(L2Cache_Entry &a) const;
  void replacementLower(Index set, Index way)  ;
  
  Index* m_pointer;

  void printStats(ostream& out, char* name) const;
  void printStats(ostream& out) const;

  void printSet(Index set) const;



};




inline
NRUPolicyL2_3SETg::NRUPolicyL2_3SETg(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  m_cache = a;
  m_pointer = new Index(0);
  
}

inline
NRUPolicyL2_3SETg::NRUPolicyL2_3SETg(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a)
  : AbstractReplacementPolicy(num_sets, assoc)
{
}

inline
NRUPolicyL2_3SETg::~NRUPolicyL2_3SETg()
{
}


inline
void NRUPolicyL2_3SETg::replacementLower(Index set, Index way) const
{

}


inline 
void NRUPolicyL2_3SETg::touch(Index set, Index index, Time time){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if(time==0) return;
  
//if(set==17) { cerr << "touch" << endl;  printSet(17); }


  L2Cache_Entry &p=(*m_cache)[set][index], *q;
  
  
  uint total = 0;
  uint used = 0;
  
  p.m_NRU = 1;
  
  uint counters[]={0,0,0,0};

  uint k= whatSubSet(p);
  for (unsigned int i=0; i < m_assoc; i++) {
    q=&(*m_cache)[set][i];
    uint aux=whatSubSet(*q);
    counters[aux]++;
    if(aux == k) 
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
  
  if(counters[0] < g_TAM_MAX_REUSED) {
  	
  	//if(set==17) cerr << "RESET:" << counters[0] << " " << counters[1] << " " <<counters[2] << " " <<counters[3] << endl;
  	
	for(uint i=0; i<m_assoc; i++) 
	{
		(*m_cache)[set][i].m_reused = (*m_cache)[set][i].m_reused2;
		(*m_cache)[set][i].m_reused2 = false;
	}
  }
	
}

inline
Index NRUPolicyL2_3SETg::getVictim(Index set) const {
  //  assert(m_assoc != 0);



//if(set==17) { cerr << "Victim" << endl;  printSet(17); }
  
  L2Cache_Entry *p;
  int ret[]={-1,-1,-1,-1};
  int pres[]={0,0,0,0};

  Index sem= *m_pointer;
  Index i= sem;
  uint k;
  do {
  	p = &(*m_cache)[set][i];
  	k = whatSubSet(*p);
  	pres[k]=1;
  	if(ret[k]==-1 && p->m_NRU==0) ret[k] = i;
  	i = (i == m_assoc-1) ? 0 : i+1;
  } while (i != sem);
  	
  for(unsigned int k=0; k<4; k++) 
  	if(pres[k]) {
  		if(ret[k]!=-1) {
  			*m_pointer = ret[k];
  			//if(set==17)cerr << "v: " <<  ret[k] << endl;
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
					//if(set==17)cerr << "v: " <<  i << endl;
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


inline void NRUPolicyL2_3SETg::replacementLower(Index set, Index way)  {
}



inline 
uint NRUPolicyL2_3SETg::whatSubSet(L2Cache_Entry &a) const
{
  if(a.m_Sharers.count()==0 && !a.m_reused && !a.m_reused2) return 0;
  if(a.m_Sharers.count()==0 && a.m_reused && !a.m_reused2) return 1;
  if(a.m_Sharers.count()==0 && a.m_reused && a.m_reused2) return 2;
  if(a.m_Sharers.count()!=0) return 3;

  assert(0);
  return -1;
  
}

inline 
void NRUPolicyL2_3SETg::printSet(Index set) const {
  uint i;
  for (i=0; i < m_assoc; i++) 
  {
    cerr<< (m_cache) << "add: " << (*m_cache)[set][i].m_Address << " NRU:" << (*m_cache)[set][i].m_NRU << "   reused: " << (*m_cache)[set][i].m_reused  << " sharers: " << (*m_cache)[set][i].m_Sharers.count()<< "   reused2: " << (*m_cache)[set][i].m_reused2 <<endl;
  }
  cerr << endl;
}

inline
void NRUPolicyL2_3SETg::printStats(ostream& out, char* name)  const
{ int a=0;}

inline
void NRUPolicyL2_3SETg::printStats(ostream& out)  const
{ int a=0;}
#endif // PSEUDONRUBITS_H
