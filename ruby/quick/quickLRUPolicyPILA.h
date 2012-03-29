
#ifndef quickLRUPolicyPILA_H
#define quickLRUPolicyPILA_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true LRU replacement policy */

class quickLRUPolicyPILA : public AbstractReplacementPolicyQuick {
 public:

  quickLRUPolicyPILA(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickLRUPolicyPILA();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  void replacementLower(Index set, Index way)  ;

  void printStats(ostream& out, char* name) ;
  void printStats(ostream& out) ;
  void clearStats() ;
  uint **m_LRUorder;
  Histogram  *m_posPILA;
  Histogram  **m_posPILAth;

};


//SOLO PARA QUE COMPILE

inline
quickLRUPolicyPILA::quickLRUPolicyPILA(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
	m_LRUorder = new uint* [num_sets] ();
	for (unsigned int i=0; i < num_sets; i++) {
		m_LRUorder[i] = new uint [m_assoc] ();
		for (unsigned int j=0; j < m_assoc; j++) m_LRUorder[i][j] = 0;
	}
	m_posPILA = new Histogram(1, 131);
	m_posPILAth = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) m_posPILAth[i] = new Histogram(1, 131);
	
}


inline
quickLRUPolicyPILA::~quickLRUPolicyPILA()
{
}

inline 
void quickLRUPolicyPILA::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if(time==0) {
  	uint ant=m_LRUorder[set][index];
  	
  	m_posPILA->add(130);  //llamada desde allocate=fallos=infinito
  	m_posPILAth[proc]->add(130);  //llamada desde allocate=fallos=infinito
  	for (unsigned int i=0; i < m_assoc; i++) {
  		//m_LRUorder[set][i]= m_LRUo;rder[set][i]==m_assoc ? m_LRUorder[set][i] : m_LRUorder[set][i]+1;
  		m_LRUorder[set][i]= m_LRUorder[set][i]<=ant ? m_LRUorder[set][i]+1 : m_LRUorder[set][i];
  	}
  	m_LRUorder[set][index]=1;
  	return;
  }
  
  uint aux =  m_LRUorder[set][index];
  assert(aux <= m_assoc);
  m_posPILA->add(aux);
  m_posPILAth[proc]->add(aux);
  
  m_out = aux;
  
  //Pila normal, cuando acertamos en una posici—n, se pone tal posicion en la cabeza y se ajusta
  //(todos los que estaban antes incrementan una posicion)
/*  
  for (unsigned int i=0; i < m_assoc; i++) {
  	if(m_LRUorder[set][i] < aux) m_LRUorder[set][i]++;
  }
  m_LRUorder[set][index]=1;
  */
  
  //ahora no queremos hacer nada de esto, simplemente despues de acertar eliminaremos la entrada,
  //esto se hara en CacheMgr
}

inline
Index quickLRUPolicyPILA::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  Time time, smallest_time;
  Index smallest_index;

   uint aux = 0;
  for (unsigned int i=0; i < m_assoc; i++) {
  	if(m_LRUorder[set][i] == m_assoc) {
  		return i; //aux = i; 
  	}
  }  
  
  int a[129];
  for (unsigned int i=0; i < 129; i++) a[i]=0;
  
  for (unsigned int i=0; i < m_assoc; i++) {
  	cerr << m_LRUorder[set][i] << " " ;
  	a[m_LRUorder[set][i]]=1;
  	
  }  
  cerr << endl;
  
  for (unsigned int i=0; i < 129; i++) 
  	if(a[i]==0) 
  		cerr << "El " << i  << " est‡ vac’o!!!" << endl;
  
  assert(0);

  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);

  return smallest_index;
}

inline void quickLRUPolicyPILA::replacementLower(Index set, Index way)  {
}

inline
void quickLRUPolicyPILA::printStats(ostream& out, char* name) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
  out << "Histo gral "<< name << endl;
  out << *m_posPILA << endl;
  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "Histo "<< name << " thread " << i << endl << *m_posPILAth[i] << endl;
cerr << "quickLRUPolicyPILA::printStats" << endl;

  m_posPILA->clear(1, 131);
  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) { 
  	m_posPILAth[i]->clear(1, 131);
  }
  
}

inline
void quickLRUPolicyPILA::printStats(ostream& out) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRUPolicyPILA::printStats" << endl;
}

inline
void quickLRUPolicyPILA::clearStats() 
{

}
#endif // PSEUDOLRUBITS_H
