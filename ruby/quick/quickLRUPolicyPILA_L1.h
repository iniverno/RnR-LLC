
#ifndef quickLRUPolicyPILA_L1_H
#define quickLRUPolicyPILA_L1_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true LRU replacement policy */

class quickLRUPolicyPILA_L1 : public AbstractReplacementPolicyQuick {
 public:

  quickLRUPolicyPILA_L1(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickLRUPolicyPILA_L1();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  void replacementLower(Index set, Index way)  ;

  void printStats(ostream& out, char* name) ;
  void printStats(ostream& out) ;
  void clearStats() ;
  uint **m_LRUorder;
  Histogram  *m_posPILA;

};


//SOLO PARA QUE COMPILE

inline
quickLRUPolicyPILA_L1::quickLRUPolicyPILA_L1(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
	m_LRUorder = new uint* [num_sets] ();
	for (unsigned int i=0; i < num_sets; i++) {
		m_LRUorder[i] = new uint [m_assoc] ();
		for (unsigned int j=0; j < m_assoc; j++) m_LRUorder[i][j] = 0;
	}
	m_posPILA = new Histogram(1, 131);	
}


inline
quickLRUPolicyPILA_L1::~quickLRUPolicyPILA_L1()
{
}

inline 
void quickLRUPolicyPILA_L1::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if(time==0) {
  	m_posPILA->add(130);  //llamada desde allocate=fallos=infinito
  	for (unsigned int i=0; i < m_assoc; i++) {
  		m_LRUorder[set][i]++;
  	}
  	m_LRUorder[set][index]=1;
  	return;
  }
  
  uint aux =  m_LRUorder[set][index];
  assert(aux <= m_assoc);
  m_posPILA->add(aux);
  
  for (unsigned int i=0; i < m_assoc; i++) {
  	if(m_LRUorder[set][i] < aux) m_LRUorder[set][i]++;
  }
  m_LRUorder[set][index]=1;
  
}

inline
Index quickLRUPolicyPILA_L1::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  Time time, smallest_time;
  Index smallest_index;

  for (unsigned int i=0; i < m_assoc; i++) {
  	if(m_LRUorder[set][i] == m_assoc) return i; 
  }
  
  assert(false);
  
  
  smallest_index = 0;
  smallest_time = m_last_ref_ptr[set][0];

  for (unsigned int i=0; i < m_assoc; i++) {
    time = m_last_ref_ptr[set][i];
    //assert(m_cache[cacheSet][i].m_Permission != AccessPermission_NotPresent);

    if (time < smallest_time){
      smallest_index = i;
      smallest_time = time;
    }
  }

  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);

  return smallest_index;
}

inline void quickLRUPolicyPILA_L1::replacementLower(Index set, Index way)  {
}

inline
void quickLRUPolicyPILA_L1::printStats(ostream& out, char* name) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
  out << "Histo gral "<< name << endl;
  out << *m_posPILA << endl;
  
cerr << "quickLRUPolicyPILA_L1::printStats" << endl;
}

inline
void quickLRUPolicyPILA_L1::printStats(ostream& out) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRUPolicyPILA_L1::printStats" << endl;
}
inline
void quickLRUPolicyPILA_L1::clearStats() 
{

}
#endif // PSEUDOLRUBITS_H
