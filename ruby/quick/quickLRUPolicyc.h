
#ifndef quickLRUPolicyc_H
#define quickLRUPolicyc_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheMemoryQuick.h"

/* two lists completely sorted by reuse order and NO touch in private replacement  */

//#define DEBUG_SET 1

class quickLRUPolicyc : public AbstractReplacementPolicyQuick {
 public:

  quickLRUPolicyc(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a);
  ~quickLRUPolicyc();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  void replacementLower(Index set, Index way)  ;
  uint whatSubSet(CacheEntryQuick &a) const;
  int posInSubset(int set, int index, CacheEntryQuick &p) ;
  uint whatSubset(CacheEntryQuick &a) ;
  void printStats(ostream& out, char* name) ;
  void printStats(ostream& out) ;
  void clearStats() ;
  Index victimPriv(Index set);

  Vector<Vector<CacheEntryQuick> > *m_cache;
    Vector<uint64> m_nH [2];
  Vector<uint64> m_nTH;

  uint** m_LRUorder;
  
  Histogram  *m_posPILALRU;
  Histogram  **m_posPILAthLRU;
  
  Histogram  *m_posPILA1st;
  Histogram  **m_posPILAth1st;

  Histogram  *m_posPILARe;
  Histogram  **m_posPILAthRe;
  
  Histogram  *m_posPILALRUre;
  Histogram  *m_posPILALRU1st;
  Histogram  **m_posPILAthLRU1st;
  Histogram  **m_posPILAthLRUre;


  mutable int trend;
  mutable int *members;

};


//SOLO PARA QUE COMPILE

inline
quickLRUPolicyc::quickLRUPolicyc(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_cache = a;
  m_nH[0].setSize(RubyConfig::numberOfProcsPerChip());
  m_nH[1].setSize(RubyConfig::numberOfProcsPerChip());
  m_nTH.setSize(RubyConfig::numberOfProcsPerChip());
  
  for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
  	for (int j = 0; j < 2; j++) m_nH[j][i]= 0;
  	m_nTH[i] = 0;
  }
	m_LRUorder = new uint* [num_sets] ();
	for (unsigned int i=0; i < num_sets; i++) {
		m_LRUorder[i] = new uint [m_assoc] ();
		for (unsigned int j=0; j < m_assoc; j++) m_LRUorder[i][j] = 0;
	}

	m_posPILALRU = new Histogram(1, m_assoc+2);
	m_posPILAthLRU = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILA1st = new Histogram(1, m_assoc+2);
	m_posPILAth1st = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILARe = new Histogram(1, m_assoc+2);
	m_posPILAthRe = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILAthLRU1st = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILAthLRUre = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILALRUre = new Histogram(1, m_assoc+2);
	m_posPILALRU1st = new Histogram(1, m_assoc+2);
	
	for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) {
		m_posPILAth1st[i] = new Histogram(1, m_assoc+2);
		m_posPILAthRe[i] = new Histogram(1, m_assoc+2);
		m_posPILAthLRU[i] = new Histogram(1, m_assoc+2);
		m_posPILAthLRU1st[i] = new Histogram(1, m_assoc+2);
		m_posPILAthLRUre[i] = new Histogram(1, m_assoc+2);
	}
	
	trend = 1;
	members = new int [num_sets];
	for(uint i=0; i< num_sets; i++) members[i] = 0;
}


inline
quickLRUPolicyc::~quickLRUPolicyc()
{
}

inline 
void quickLRUPolicyc::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();

  int ant = m_LRUorder[set][index];
  
  if(DEBUG_SET && set==423) {
  	if(DEBUG_SET && set==423) cerr << "HIT at " << index << " LRUpos: " << ant << endl;
    for(int i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << "\t" << (*m_cache)[set][i] << endl;
  }
  
  if(time > 1) {
    m_posPILAthLRU[proc]->add(ant);
  	m_posPILALRU->add(ant);
  	if(DEBUG_SET && set==423)cerr << this << "LRU at " << ant << endl;
  	
  	 CacheEntryQuick &p = (*m_cache)[set][index];
  	 
  	 int pos = posInSubset(set, index, p);
  	if(p.m_NRU) {
  		m_posPILAthRe[proc]->add(pos);
  		m_posPILARe->add(pos);
  		
  		m_posPILALRUre->add(ant);
  		m_posPILAthLRUre[proc]->add(ant);
  		
  		if(DEBUG_SET && set==423)cerr << this << " reuse at " << pos << endl;
  	}
  	else {
  		m_posPILAth1st[proc]->add(pos);
  		m_posPILA1st->add(pos);
  		
  		m_posPILAthLRU1st[proc]->add(ant);
  		m_posPILALRU1st->add(ant);
  		
  		if(DEBUG_SET && set==423)cerr << this << " 1st use at " << pos << endl;
  	}
  	
  	if(ant<17) p.m_NRU = 1;
  	
  } else { members[set]++; }


  //inicializacion
  if(ant == 0) {
  		if(members[set] > 16) {
	  		Index victim = victimPriv(set);
			int victimPosLRU = m_LRUorder[set][victim];
  			for (unsigned int i=0; i < m_assoc; i++) {
  				if((m_LRUorder[set][i] < victimPosLRU || m_LRUorder[set][i] > 16) && m_LRUorder[set][i] != 0) {
  					m_LRUorder[set][i]++;
  				}
  			}
  			m_LRUorder[set][victim] = 17;
  			if(g_RESET_REUSED_FROM_SHADOW) (*m_cache)[set][victim].m_NRU = 0;
  			
  			// if victim is private!!!
  			if((*m_cache)[set][victim].m_Sharers.count() > 0) {
  				overAssoc = victim; 
  				overAssocAddress=(*m_cache)[set][victim].m_Address; 
  			}
  		}
  		else {
			for(int i=0; i<m_assoc; i++) {
  				m_LRUorder[set][i]= m_LRUorder[set][i]>ant ? m_LRUorder[set][i]+1 : 0;
  			}
  		}
  }
  else {
  	//hit on normal segment 1--16
  	if(ant<17) {
  		for (unsigned int i=0; i < m_assoc; i++) {
  			if(m_LRUorder[set][i] < ant && m_LRUorder[set][i] != 0) m_LRUorder[set][i]++;
  		}
  	}
  	else {
  		//hit on shadow segment 17--64
  		for (unsigned int i=0; i < m_assoc; i++) {
  			if(m_LRUorder[set][i] >= 17 && m_LRUorder[set][i] < ant) m_LRUorder[set][i]++;
  		}
  		Index victim = victimPriv(set);
  		int victimPosLRU = m_LRUorder[set][victim];
  		for (unsigned int i=0; i < m_assoc; i++) {
  			if(m_LRUorder[set][i] < victimPosLRU && m_LRUorder[set][i] != 0) {
  				m_LRUorder[set][i]++;
  			}
  		}
  		m_LRUorder[set][victim]=17;
  		if(g_RESET_REUSED_FROM_SHADOW) (*m_cache)[set][victim].m_NRU = 0;
  		
  		// if victim is private!!!
  		if((*m_cache)[set][victim].m_Sharers.count() > 0) {
  			overAssoc = victim; 
  			overAssocAddress=(*m_cache)[set][victim].m_Address; 
  		}
  	} 	
  }//else ant==0

  m_LRUorder[set][index]=1;
  
  if(ant>16) insideAsoc= 2;
  else insideAsoc= 1;
  
}

inline
Index quickLRUPolicyc::getVictim(Index set, uint proc) const {

	members[set]--;
	
  	int i;

	for (i=0; i < m_assoc; i++) {
 		if(m_LRUorder[set][i] == m_assoc) return i;
  	}
  	  cerr << "SET: " << set << " m_version: " << endl;
  for(int i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << "\t" << (*m_cache)[set][i] << endl;

  	assert(0);
}

inline
Index quickLRUPolicyc::victimPriv(Index set)  {	

  if(DEBUG_SET && set==423) cerr << this << "Victim priv: " << endl;
  if(DEBUG_SET && set==423) for(int i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << endl;
  
  int total = 0;
  
  	for (int i=0; i < m_assoc && total<16; i++) {
   		if(m_LRUorder[set][i] == 16) {
   			if((*m_cache)[set][i].m_Sharers.count() == 0) {
   				if(DEBUG_SET && set==423)cerr << this << "Victim priv: " << i << endl;
  				return i; 
  			}
  			else {
  				for (unsigned int j=0; j < m_assoc; j++) if(m_LRUorder[set][j] < 16 && m_LRUorder[set][j] != 0) m_LRUorder[set][j]++;
  				m_LRUorder[set][i] = 1;
  				i = -1;
  				total++;
  				
  			} 				
  		}
  	}
  if(DEBUG_SET && set==423) for(int i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << endl;
  
	for (int i=0; i < m_assoc; i++) 
   		if(m_LRUorder[set][i] == 16) 
   			return i;

  if(DEBUG_SET && set==423) for(int i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << endl;
  
   	if(DEBUG_SET)cerr << this << "FAllo en set: " << set << endl;
   	assert(0);

}

inline void quickLRUPolicyc::replacementLower(Index set, Index way)  {
	//if((*m_cache)[set][way].m_reused) m_last_ref_ptr[set][way] = g_eventQueue_ptr->getTime();
}

inline 
uint quickLRUPolicyc::whatSubSet(CacheEntryQuick &a) const
{
  if(a.m_Sharers.count()==0 && !a.m_NRU) {assert(0); return 0; }
  if(a.m_Sharers.count()==0 && a.m_NRU) return 1;
  if(a.m_Sharers.count()!=0  && !a.m_NRU) return 2;
  if(a.m_Sharers.count()!=0  && a.m_NRU) return 3;

  assert(0);
  return -1;
  
}

inline int quickLRUPolicyc::posInSubset(int set, int index, CacheEntryQuick &p) {

	
	int blkSubset = whatSubset(p);
	int blkLRUpos = m_LRUorder[set][index];
	int blkSubsetPos = 1;
	
	for(int i=0; i<m_assoc; i++) {		
		if(m_LRUorder[set][i] < blkLRUpos && m_LRUorder[set][i] > 0 && whatSubset((*m_cache)[set][i])==blkSubset)
			blkSubsetPos++;
	}
	
	return blkSubsetPos;
 
}

inline uint quickLRUPolicyc::whatSubset(CacheEntryQuick& a) {
	if(!a.m_NRU) return 0;
	else return 1;
}


inline
void quickLRUPolicyc::printStats(ostream& out, char* name) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRUPolicyc::printStats" << endl;
	for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
		for (int j = 0; j < 2; j++)
			out << "LRRc" << "_hit_ratio_segment_"<< j <<"_thread_" << i << ":\t" <<  (float) m_nH[j][i]/(m_nTH[i])  << endl;
	}

  out << "HistoLRU gral" << name << " " << *m_posPILALRU << endl;  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "HistoLRU "<< name << " thread " << i << "\t" << *m_posPILAthLRU[i] << endl;

  out << "Histo1st gral " << name << " " << *m_posPILA1st << endl;  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "Histo1st "<< name << " thread " << i << "\t" << *m_posPILAth1st[i] << endl;

  out << "HistoRe gral " << name << " " << *m_posPILARe << endl;  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "HistoRe "<< name << " thread " << i << "\t" << *m_posPILAthRe[i] << endl;

  out << "Histo1stI gl " << name << " " << *m_posPILALRU1st << endl;  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "Histo1stI "<< name << " thread " << i << "\t" << *m_posPILAthLRU1st[i] << endl;

  out << "HistoReI gl " << name << " " << *m_posPILALRUre << endl;  
  for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) out << "HistoReI t"<< name << " thread " << i << "\t" << *m_posPILAthLRUre[i] << endl;

}

inline
void quickLRUPolicyc::clearStats() 
{
cerr << "quickLRUPolicyc::clearStats()" << endl;

  for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
  	for (int j = 0; j < 2; j++) m_nH[j][i]= 0;
  	m_nTH[i] = 0;
  }

	m_posPILALRU = new Histogram(1, m_assoc+2);
	m_posPILAthLRU = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILA1st = new Histogram(1, m_assoc+2);
	m_posPILAth1st = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILARe = new Histogram(1, m_assoc+2);
	m_posPILAthRe = new Histogram* [RubyConfig::numberOfProcsPerChip()] ();
	m_posPILALRUre->clear(1, m_assoc+2);
	m_posPILALRU1st->clear(1, m_assoc+2);
	
	for(uint i=0; i< RubyConfig::numberOfProcsPerChip(); i++) {
		m_posPILAth1st[i] = new Histogram(1, m_assoc+2);
		m_posPILAthRe[i] = new Histogram(1, m_assoc+2);
		m_posPILAthLRU[i] = new Histogram(1, m_assoc+2);
		m_posPILAthLRUre[i]->clear(1, m_assoc+2);
		m_posPILAthLRU1st[i]->clear(1, m_assoc+2);
	}
}

inline
void quickLRUPolicyc::printStats(ostream& out) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRUPolicyc::printStats" << endl;
}
#endif // PSEUDOLRUBITS_H
