
#ifndef quickLRUPolicyPILAF_H
#define quickLRUPolicyPILAF_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"

/* Simple true LRU replacement policy */

class quickLRUPolicyPILAF : public AbstractReplacementPolicyQuick {
 public:

  quickLRUPolicyPILAF(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a, bool ignoreVery1st);
  ~quickLRUPolicyPILAF();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  void replacementLower(Index set, Index way)  ;

  void printStats(ostream& out, char* name) ;
  void printStats(ostream& out) ;
  void clearStats() ;
  uint **m_LRUorder;  			//normal LRU position
  
  Histogram  *m_posPILA;  		// global LRU position when accessing
  Histogram  **m_posPILAth;		// per thread LRU posticion when accessing 
  
  uint **m_LRU1stReuse;  			// LRU position of the first reuse of that block
  Histogram  *m_pos1stReuse;	// tracks LRU position of the first reuse of that block, global
  Histogram  **m_pos1stReuseTh;	// tracks LRU position of the first reuse of that block, per thread
  
  bool m_ignoreVery1st;
  //int m_in, m_out;

};


//SOLO PARA QUE COMPILE

inline
quickLRUPolicyPILAF::quickLRUPolicyPILAF(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a, bool ignoreVery1st)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
	m_LRUorder = new uint* [num_sets] ();
	m_LRU1stReuse = new uint* [num_sets] ();
	for (unsigned int i=0; i < num_sets; i++) {
		m_LRUorder[i] = new uint [m_assoc] ();
		m_LRU1stReuse[i] = new uint [m_assoc] ();
		for (unsigned int j=0; j < m_assoc; j++) {
			m_LRUorder[i][j] = 0;
			m_LRU1stReuse[i][j] = 0;
		}
	}
	m_posPILA = new Histogram(1, 131);
	m_posPILAth = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) m_posPILAth[i] = new Histogram(1, 131);
	
	m_pos1stReuse = new Histogram(1, 131);
	m_pos1stReuseTh = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) m_pos1stReuseTh[i] = new Histogram(1, 131);
	
	m_ignoreVery1st = ignoreVery1st;

}


inline
quickLRUPolicyPILAF::~quickLRUPolicyPILAF()
{
}



inline 
void quickLRUPolicyPILAF::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  if(time==0) {
  	m_posPILA->add(130);  //llamada desde allocate=fallos=infinito
  	m_posPILAth[proc]->add(130);
  	for (unsigned int i=0; i < m_assoc; i++) {
  		m_LRUorder[set][i]++;
  	}
  	m_LRUorder[set][index]=1;
  	
  	m_LRU1stReuse[set][index] = m_in;
  	return;
  }
    
  uint aux =  m_LRUorder[set][index];
  assert(aux <= m_assoc);
  m_posPILA->add(aux);
  m_posPILAth[proc]->add(aux);
  
  m_out = aux;
  
  //Pila con eliminaci—n, se toca una posici—n y se asume que ser‡ eliminada, se compacta ocupandola
  //(Todos los que estaban despues se compactan hacia arriba)
  
  /*for (unsigned int i=0; i < m_assoc; i++) {
  	if(m_LRUorder[set][i] > aux) m_LRUorder[set][i]--;
  }*/
  
  for (unsigned int i=0; i < m_assoc; i++) {
  	if(m_LRUorder[set][i] < aux) m_LRUorder[set][i]++;
  }
  m_LRUorder[set][index]=1;
  
  if(m_ignoreVery1st) {
  	   //this one is used with LRU stack
	  // Tracking position where the line was reused for the firt time
	  if(m_LRU1stReuse[set][index] == 0) { // First reuse
		m_LRU1stReuse[set][index] = aux;
	  }
	  else {
		m_pos1stReuse->add(m_LRU1stReuse[set][index]);
		m_pos1stReuseTh[proc]->add(m_LRU1stReuse[set][index]);
	  }
  }
  else {
    //for reuse stack
  	if(m_LRU1stReuse[set][index] == 0) { // First reuse
		m_LRU1stReuse[set][index] = m_in;
	}
	m_pos1stReuse->add(m_LRU1stReuse[set][index]);
	m_pos1stReuseTh[proc]->add(m_LRU1stReuse[set][index]);
  }
  
}

inline
Index quickLRUPolicyPILAF::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);

  uint aux = 0;
  for (unsigned int i=0; i < m_assoc; i++) {
  	if(m_LRUorder[set][i] == m_assoc) {
  		m_LRU1stReuse[set][i] = 0;
  		return i; //aux = i; 
  	}
  }  
  
  //return aux;
  
  assert(false);
  

  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);

}

inline void quickLRUPolicyPILAF::replacementLower(Index set, Index way)  {
}

inline
void quickLRUPolicyPILAF::printStats(ostream& out, char* name) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
  out << "Histo gral "<< name << "\t";
  out << *m_posPILA << endl;
  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "Histo "<< name << " thread " << i << "\t" << *m_posPILAth[i] << endl;
  cerr << "quickLRUPolicyPILAF::printStats" << endl;

  out << "Histo gral 1st reuse pos"<< name << "\t";
  out << *m_pos1stReuse << endl;
  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "Histo 1st reuse pos"<< name << " thread " << i << "\t" << *m_pos1stReuseTh[i] << endl;
  cerr << "quickLRUPolicyPILAF::printStats" << endl;

///////////

  
  m_posPILA->clear(1, 131);
  m_pos1stReuse->clear(1, 131);
  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) { 
  	m_posPILAth[i]->clear(1, 131);
	m_pos1stReuseTh[i]->clear(1, 131);
  }
  

  
}

inline
void quickLRUPolicyPILAF::printStats(ostream& out) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRUPolicyPILAF::printStats" << endl;
}

inline
void quickLRUPolicyPILAF::clearStats() 
{

}
#endif // PSEUDOLRUBITS_H
