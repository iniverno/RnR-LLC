

#ifndef quickNRUPolicy_3SETd_H
#define quickNRUPolicy_3SETd_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true NRU replacement policy */

class quickNRUPolicy_3SETd : public AbstractReplacementPolicyQuick {
 public:

  quickNRUPolicy_3SETd(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a, uint version);
  ~quickNRUPolicy_3SETd();

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

  int** R;
  uint m_version;
};




inline
quickNRUPolicy_3SETd::quickNRUPolicy_3SETd(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a, uint version)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_version = version;
  m_cache = a;
  m_pointer = new Index(0);
    R= new int* [num_sets];
  for (unsigned int i=0; i < num_sets; i++) {
  	R[i]= new int [4];
  	
  	R[i][0]=0; // no reused=0
  	R[i][1]=0; // reused>0
  	R[i][2]=4; // R
  	R[i][3]=0;  // accesos
  }
}

inline
quickNRUPolicy_3SETd::~quickNRUPolicy_3SETd()
{
}


inline void quickNRUPolicy_3SETd::replacementLower(Index set, Index way)  {

	if((*m_cache)[set][way].m_reused) {
		int aux= countSegments(set, 2);
		R[set][2]+= (R[set][2]>=(m_assoc - aux - 2) ? 0 : 1);
	}
}
 
 
 
inline 
void quickNRUPolicy_3SETd::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);



  CacheEntryQuick &p=(*m_cache)[set][index], *q;
  
  
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
  
	R[set][3]++;
	
	//incrementamos el contador de un segmento de acuerdo al tama–o del otro (teniendo en cuenta el nœmero de
	//elementos incluidos en las caches privadas)
	int aux= countSegments(set, 2);
	R[set][p.m_reused] += (p.m_reused ? m_assoc - aux- R[set][2] : R[set][2]);
	
	if(R[set][3] >= 16) {
		bool comp= R[set][0] <= R[set][1];
		
		if(set==2000  && m_version==1) {
			cerr << "comp:\t " << comp << "\tnoreused:\t " << R[set][0] << "\treused:\t" << R[set][1]<< "\tRobj:\t" << R[set][2]<< "\tRreal:\t" << countSegments(set, 1) << "\tm_nReused:\t" <<  (int)m_nReused[set] << endl;
		}
		
		if(comp) R[set][2]+= (R[set][2]>=(m_assoc - aux - 2) ? 0 : 1);
		else R[set][2]-= R[set][2]==2 ? 0 : 1;
		
		R[set][3] = 0;
		R[set][0] = 0;
		R[set][1] = 0;
		
		
	}
	
}

inline
Index quickNRUPolicy_3SETd::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  
  CacheEntryQuick *p;
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

  int ind[3];
  
  if(countSegments(set, 1) <= R[set][2]) {
  	ind[0]=0; ind[1]=1; ind[2]=2;
  	/*if(set==2000 && m_version==1) {
  		cerr << "repl NOreused" << endl;
  	}*/
  } else {
  	ind[0]=1; ind[1]=0; ind[2]=2;
  	/*if(set==2000 && m_version==1) {
  		cerr << "repl Reused" << endl;
  	}*/
  }
  
  for(int k=ind[0],m=0; m<3; m++, k=ind[m]) {
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
  }
  
  assert(0);
  return -1;
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);
}

inline 
bool quickNRUPolicy_3SETd::subSet(CacheEntryQuick *a, uint set) const
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
uint quickNRUPolicy_3SETd::whatSubSet(CacheEntryQuick &a) const
{
  if(a.m_Sharers.count()==0 && !a.m_reused) return 0;
  if(a.m_Sharers.count()==0 && a.m_reused) return 1;
  if(a.m_Sharers.count()!=0) return 2;

  assert(0);
  return -1;
  
}

inline 
uint quickNRUPolicy_3SETd::countSegments(uint set, uint what) const
{
	uint aux=0;
	for(uint i=0; i<m_assoc; i++) if(whatSubSet((*m_cache)[set][i]) == what) aux++;
	
	return aux;
	
	uint res[]={0,0,0};
	
	for(uint i=0; i<3; i++) res[whatSubSet((*m_cache)[set][i])]++;
	
	//return res;
  
}

inline
void quickNRUPolicy_3SETd::printStats(ostream& out, char* name)  
{ int a=0;}

inline
void quickNRUPolicy_3SETd::printStats(ostream& out)  
{ int a=0;}
#endif // PSEUDONRUBITS_H
