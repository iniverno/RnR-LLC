

#ifndef quickDRRIPcPolicy_H
#define quickDRRIPcPolicy_H

// Si un elemento se elige como víctima pero está en las caches privadas se meterá en 2^m -2

#include "AbstractReplacementPolicyQuick.h"

#define USE_INSERTION_POLICY  2     // Use TAquickDIP
#define USE_PSELwidth         10    // Width of the PSEL counter
#define USE_SDMsize           32    // Use 32 sets per SDM


#define DISTANT_VALUE ((1<<g_RRIP_N_BITS) - 1)

#define maxRPV                7

#ifndef DEBUG_PRINT_ON
#define DEBUG_PRINT_ON 1
#endif

#if DEBUG_PRINT_ON
#define DEBUG_PRINT(X) cout<<X<<dec<<endl;
#else
#define DEBUG_PRINT(X)
#endif

#define DEBUG_PRINT(X) cout<<X<<dec<<endl;

#define USE_PSELwidth         10    // Width of the PSEL counter
#ifdef PSELmax
#undef PSELmax
#endif
//#define PSELmax ((1<<USE_PSELwidth)-1)

#define DEBUG_SET 0



// SDM Types
typedef enum 
{
    quickDIP_FOLLOWERS       = 0,
    quickDIP_LRU_SDM         = 1,  
    quickDIP_BIP_SDM         = 2,
} quickDIP_SDM_Type_t;

// SDM Descriptor
typedef struct 
{
    uint32       SDM_Type;   // What type of SDM 
    uint32       SDM_Owner;  // Who manages the SDM
} quickDIP_SDM_t;

// Insertion Policy
typedef enum
{
    INSERTION_POLICY_NONEc                    = 0,
    INSERTION_POLICY_THREAD_UNAWAREc          = 1,
    INSERTION_POLICY_THREAD_AWAREc            = 2,
    INSERTION_POLICY_BIMODALc                 = 3,
} quickDIP_t;


class quickDIP;

class quickDRRIPcPolicy : public AbstractReplacementPolicyQuick {
 public:

  quickDRRIPcPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a, uint version);
  ~quickDRRIPcPolicy();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<CacheEntryQuick> > *m_cache;
  
  bool subSet(CacheEntryQuick *a, uint set) const;
  uint whatSubSet(CacheEntryQuick &a) const;
  uint countSegments(uint set, uint what) const;
  void replacementLower(Index set, Index way) ;
  //unsigned int GetCurrentInsertionPolicy( unsigned int cpuid ) ;
  Index victimPriv(Index set);
  int posInSubset(int set, int index, CacheEntryQuick &p) ;
  

  
  void UpdateRRIP( unsigned int tid, unsigned int setIndex, int updateWayID, bool cacheHit );

  Index* m_pointer;

  void printStats(ostream& out, char* name);
  void printStats(ostream& out) ;
  void clearStats() ;
  
  int** R;
  uint m_version;
  
  //DRRIP
   int** m_LRUorder;
  
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

 
  quickDIP *rrip;
  
  mutable int *members;
};

class quickDIP
{
    uint32      myID;
    string      cachename;

    uint32      NumberSetsInCache;
    
    // Policy Selector Counter and Max Value
    uint32      *PSEL_cntr;
    uint64      *SDMmissCountPerThread;
    uint32      *policy_selecton_threshold;
    uint32      *thread_active;
    uint32      PSELmax;

    bool        distinguishThreads;
    bool        printStatsPostWarmup;
    bool        adapt;
    
    // Which policy should I use?
    uint32      InsertionPolicy;

    // Statistics on hits and misses
    uint64      totalDemandMisses;
    uint64      totalDemandHits;

    uint64      totalPrefetchMisses;
    uint64      totalPrefetchHits;

    uint64      totalVulnerableInsertions; // insertions at RRIP tail (i.e. "LRU position")

    uint64      *totalPerThreadMisses;
    uint64      *totalPerThreadHits;

    uint64      *totalPerThreadVulnerableInsertions;

    // Per Set Cache Misses by Thread
    uint64      **perSetMisses;
    uint64      **perSetHits;

    /*************************************************************/
    /*    SET DUELING SPECIFIC PARAMS                            */
    /*************************************************************/
    quickDIP_SDM_t   *SDM_Info;

    uint32      NumThreadsPerCache;  // number threads per cache
    uint32      SDM_Size;            // Size of an SDM

    uint32      BIP_epsilon;         // BIP epsilon
    uint32      BIP_mask;            // Mask to define static BIP
    
    unsigned long quickDIP_rand_seed ;
	unsigned long quickDIP_max_rand ;

  public:

    //  This is the interface for creating cache SDMs. The args are:
    //   a)  cache name (debugging purpose)
    //   b)  bank # (debugging purpose)
    //   c)  threads sharing this cache
    //   d)  total sets in the cache
    //   e)  insertion policy to use (as defined by quickDIP_t above)
    //   f)  Max PSEL value (if 10-bit PSEL, use argument of 2^10)
    //   g)  # of sets per SDM

    quickDIP( 
        string _cachename,
        uint32 _myID,
        uint32 _tpc,
        uint32 _totalSets=2048,
        uint32 _usePolicy=INSERTION_POLICY_THREAD_AWAREc,
        uint32 _maxPSEL=1024, 
        uint32 _sizeOfSDM=32 );

    // Initialize Stats
    void Init();

    // Initialize BIP Mask
    void InitBIPmask( uint32 _mask ) { BIP_mask = _mask; };

    // Destructor deletes dynamic structures
    ~quickDIP();

    // Input:  CPU or Thread ID and set number
    // Output: none
    // Function: update PSEL counter based on misses in competing fill policy
    void RecordMiss(
        uint32 cpuid,
        uint32 setnum,
        bool   is_demand=true,
        bool   warmup_mode=false);

    // Input:  CPU or Thread ID and set number
    // Output: none
    // Function: update PSEL counter based on misses in competing fill policy
    void RecordHit(
        uint32 cpuid,
        uint32 setnum,
        bool   is_demand=true,
        bool   warmup_mode=false);

    // Input:  CPU or Thread ID and set number
    // Output: true if LRU should be updated, false if VF
    // Function: Should the current cpuid do a NF or VF in this set?
    bool DoNormalFill(
        uint32 cpuid,
        uint32 setnum );

    bool DoNormalFill(
        uint32 cpuid,
        uint32 setnum,
        uint64 cycle) 
    {
        return DoNormalFill( cpuid, setnum );
    }

    // Set Miss Histograms
    void SetMissHistogram();
    
    int quickDIP_rand(void);
    void quickDIP_srand(unsigned seed) ;

  private:

    inline uint32 NumSets() { return NumberSetsInCache; }
    inline uint32 NumDemandRefs() { return (totalDemandHits+totalDemandMisses); }
    inline uint32 NumPrefetchRefs() { return (totalPrefetchHits+totalPrefetchMisses); }
    inline uint64 NumRefs() { return (NumDemandRefs() + NumPrefetchRefs()); }


    // Create SDMs for threads sharing the cache
    void CreateSDM( uint32 _sizeOfSDM );

    // Randomly create SDM entries
    void RandomlyChooseSDMs() ;

    // Choose SDMs Based on bits 0-5 and 6-10 of the set index
    void SetIndexBitBasedSDM() ;

    // Input:  A threshold value describing the percent of misses normally filled
    // Output: True if fill should be normal, false if fill is vulnerable
    bool BimodalSuggestion( uint32 throttle );

    // Input:  CPU or Thread ID
    // Output: Fill Policy for current CPU
    // Function: Depending on whether hysteresis is enabled or not, we determine
    // the current fill policy
    uint32 GetCurrentInsertionPolicy( uint32 cpuid );
    
    // Input:  CPU or Thread ID and set number
    // Output: none
    // Function: update PSEL counter based on misses in competing fill policy
    void SetDuel_RecordMiss(
        uint32 cpuid,
        uint32 setnum,
        bool   warmup_mode=false);

    // Input:  CPU or Thread ID and set number
    // Output: true if LRU should be updated, false if VF
    // Function: Should the current cpuid do a NF or VF in this set?
    bool SetDuel_DoNormalFill(
        uint32 cpuid,
        uint32 setnum );

  public:

    // Print Throttle Traces
    void PrintThrottles( bool warmup_mode );

    // Print Stats
    void PrintStats( bool warmup_mode );

    // Return the PSEL value for the current processor
    uint32 GetPSEL( uint32 cpuid ) 
    { 
        // determine PSEL id
        uint32 PSELid = cpuid % NumThreadsPerCache;        

        // return PSEL value
        return PSEL_cntr[ PSELid ]; 
    } 

};



	inline void
quickDRRIPcPolicy::clearStats(){

cerr << "quickDRRIPcPolicy::clearStats()" << endl;


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
quickDRRIPcPolicy::quickDRRIPcPolicy(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a, uint version)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_version = version;
  m_cache = a;
  m_num_sets = num_sets;

	m_LRUorder = new int* [num_sets] ();
	for (unsigned int i=0; i < num_sets; i++) {
		m_LRUorder[i] = new int [m_assoc] ();
		for (unsigned int j=0; j < m_assoc; j++) m_LRUorder[i][j] = -1;
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
  
  	members = new int [num_sets];
	for(uint i=0; i< num_sets; i++) members[i] = 0;

	rrip = new quickDIP( "LLC", 0, 8, num_sets, USE_INSERTION_POLICY, ((1<<USE_PSELwidth)-1),USE_SDMsize);
}

inline
quickDRRIPcPolicy::~quickDRRIPcPolicy()
{
}


 
 
 
inline 
void quickDRRIPcPolicy::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  CacheEntryQuick &p = (*m_cache)[set][index];

  int ant;
  //int ant = m_LRUorder[set][index];
  if(m_LRUorder[set][index] == 0) {
  	ant = p.m_RRPV*2+1;
  }
  else {
  	ant = m_LRUorder[set][index];
  }
  
  if(DEBUG_SET && set==1879) {
  	if(DEBUG_SET && set==1879) cerr << "HIT at " << index << " LRUpos: " << ant << endl;
    for(int i=0; i<m_assoc; i++) cerr  << this << "\t" << m_LRUorder[set][i] << "\t" << (*m_cache)[set][i].m_RRPV << "\t" << (*m_cache)[set][i] << endl;
  }
  
  if(time > 1) {
    m_posPILAthLRU[proc]->add(ant);
  	m_posPILALRU->add(ant);
  	if(DEBUG_SET && set==1879)cerr << this << "LRU at " << ant << endl;
  	
  	 
  	 int pos = posInSubset(set, index, p);
  	if(p.m_NRU) {
  		m_posPILAthRe[proc]->add(pos);
  		m_posPILARe->add(pos);
  		
  		m_posPILALRUre->add(ant);
  		m_posPILAthLRUre[proc]->add(ant);
  		
  		if(DEBUG_SET && set==1879)cerr << this << " reuse at " << pos << endl;
  	}
  	else {
  		m_posPILAth1st[proc]->add(pos);
  		m_posPILA1st->add(pos);
  		
  		m_posPILAthLRU1st[proc]->add(ant);
  		m_posPILALRU1st->add(ant);
  		
  		if(DEBUG_SET && set==1879)cerr << this << " 1st use at " << pos << endl;
  	}
  	
  	//Hit
  	if(m_LRUorder[set][index] == 0) {
  		p.m_NRU = 1;
  		rrip->RecordHit( proc, set, 1, 0 );
		UpdateRRIP(proc, set, index, 1);
		
  		//p.m_RRPV > 0 ? p.m_RRPV-- : 0;
  		p.m_RRPV = 0;
  	}
  	
  } 
  else { 
  	members[set]++; 
		//It is set to the last group. UpdateRRIP will decide
	p.m_RRPV = maxRPV; 
		
	rrip->RecordMiss( proc, set, 1, 0);
	UpdateRRIP(proc, set, index, 0);
  }


  //inicializacion
  if(m_LRUorder[set][index] == -1) {
  		if(members[set] > 16) {
	  		Index victim = victimPriv(set);
  			for (unsigned int i=0; i < m_assoc; i++) {
  				if(m_LRUorder[set][i] > 16) {
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
		rrip->RecordMiss( proc, set, 1, 0);
		UpdateRRIP(proc, set, index, 0);  	
  }
  else {
  	//hit on  segment 17--64
  	if(m_LRUorder[set][index] > 16) {
  		//hit on shadow segment 17--64
  		for (unsigned int i=0; i < m_assoc; i++) {
  			if(m_LRUorder[set][i] >= 17 && m_LRUorder[set][i] < m_LRUorder[set][index]) m_LRUorder[set][i]++;
  		}
  		Index victim = victimPriv(set);
  		m_LRUorder[set][victim]=17;
  		if(g_RESET_REUSED_FROM_SHADOW) (*m_cache)[set][victim].m_NRU = 0;
  		
  		// if victim is private!!!
  		if((*m_cache)[set][victim].m_Sharers.count() > 0) {
  			overAssoc = victim; 
  			overAssocAddress=(*m_cache)[set][victim].m_Address; 
  		}
  		  		
		rrip->RecordMiss( proc, set, 1, 0);
		UpdateRRIP(proc, set, index, 0);  	

  	} 	
  }//else ant==0

  
  if(m_LRUorder[set][index] > 16) insideAsoc = 2;
  else insideAsoc = 1;	
	
  m_LRUorder[set][index] = 0;
	
}

inline
Index quickDRRIPcPolicy::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  	
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
Index quickDRRIPcPolicy::victimPriv(Index set)  {

	
	CacheEntryQuick *p;
	bool found = false;
	
	
	while(!found)
	{
		uint k=0, total=0; 
		//buscamos el primero con el RRPV a 2^m-1
		for(uint i = 0; i < m_assoc; i++) {
			p = &(*m_cache)[set][i];
			//cerr << "p->m_RRPV: " << p->m_RRPV << " DISTANT_VALUE: " << DISTANT_VALUE<< endl;	
			if(p->m_RRPV == DISTANT_VALUE && m_LRUorder[set][i] == 0) {
				total++;
				if(g_PROTEGE_RRIP && p->m_Sharers.count() > 0) {
					p->m_RRPV = DISTANT_VALUE - 1;
					//p->m_RRPV = 0;
					k++;
				}
				else {
					return i;
				}
			}
		}
		if(k==total && k!=0) { //caso patologico
			for(uint i = 0; i < m_assoc; i++) if(m_LRUorder[set][i] == 0) return i;
		}
		//si no lo encontramos incrementamos todos y repetimos
		for(uint i = 0; i < m_assoc; i++) {
			p = &(*m_cache)[set][i];
			 if(m_LRUorder[set][i] == 0)
				p->m_RRPV < DISTANT_VALUE ? p->m_RRPV++ : 0;
		}
	}
  
  assert(0);
  return -1;
}
inline 
bool quickDRRIPcPolicy::subSet(CacheEntryQuick *a, uint set) const
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
uint quickDRRIPcPolicy::whatSubSet(CacheEntryQuick &a) const
{
  if(a.m_Sharers.count()==0 && !a.m_reused) return 0;
  if(a.m_Sharers.count()==0 && a.m_reused) return 1;
  if(a.m_Sharers.count()!=0) return 2;

  assert(0);
  return -1;
  
}

inline 
uint quickDRRIPcPolicy::countSegments(uint set, uint what) const
{
	uint aux=0;
	for(uint i=0; i<m_assoc; i++) if(whatSubSet((*m_cache)[set][i]) == what) aux++;
	
	return aux;
	
	uint res[]={0,0,0};
	
	for(uint i=0; i<3; i++) res[whatSubSet((*m_cache)[set][i])]++;
	
	//return res;
  
}

inline
void quickDRRIPcPolicy::printStats(ostream& out, char* name)   
{ int a=0;
	cout << "Stats DRRIPb:" << endl;
	rrip->PrintStats(0);
	
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



inline int quickDRRIPcPolicy::posInSubset(int set, int index, CacheEntryQuick &p) {

	
return 1;
}


inline void quickDRRIPcPolicy::UpdateRRIP( unsigned int tid, unsigned int setIndex, int updateWayID, bool cacheHit )
{
    // Set the RPV of line to near-immediate
    if( cacheHit ) 
    {
       // repl[ setIndex ][ updateWayID ].RPV = 0;
        (*m_cache)[ setIndex ][ updateWayID ].m_RRPV = 0;
    }
    else 
    {
        bool updateLRUstateOnMiss = rrip->DoNormalFill( tid, setIndex );
        
        if( updateLRUstateOnMiss ) 
        {
            (*m_cache)[ setIndex ][ updateWayID ].m_RRPV =  (maxRPV-1);
        }
    }
}

inline void quickDRRIPcPolicy::replacementLower(Index set, Index way)  {
	//if((*m_cache)[set][way].m_reused) m_last_ref_ptr[set][way] = g_eventQueue_ptr->getTime();
}

inline
void quickDRRIPcPolicy::printStats(ostream& out) 
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 
cerr << "quickLRRdtPolicy::printStats" << endl;
}


//******************************************************************************************************




////////////////////////

// This is the interface for creating cache SDMs. The args are:
//   a)  cache name (debugging purpose)
//   b)  bank # (debugging purpose)
//   c)  threads sharing this cache
//   d)  total sets in the cache
//   e)  insertion policy to use (as defined by quickDIP_t)
//   f)  Max PSEL value (if 10-bit PSEL, use argument of 2^10)
//   g)  # of sets per SDM

inline quickDIP::quickDIP ( 
    string _cachename,
    unsigned int _myID,
    unsigned int _tpc,
    unsigned int _totalSets,
    unsigned int _usePolicy,
    unsigned int _maxPSEL,
    unsigned int _sizeOfSDM )
{
quickDIP_rand_seed = 1;
quickDIP_max_rand  = 1048576;
cerr << "quickDIP::quickDIP()" << endl;

    cerr << "Initializing quickDIP-"<<_cachename<<"-"<<_myID
                <<" TPC: "<<_tpc<<" Policy: "<<_usePolicy << endl;

    cachename            = _cachename;  // Initialize the cache name
    myID                 = _myID;       // Initialize My ID
    NumThreadsPerCache   = _tpc;        // Initialize # threads per cache
    NumberSetsInCache    = _totalSets;  // Initialize total set count    
    InsertionPolicy      = _usePolicy;  // Initialize Insertion Policy
    PSELmax              = _maxPSEL;    // Initialize Max PSEL Value
    SDM_Size             = _sizeOfSDM;  // Initialize the SDM size

    BIP_epsilon          = 5;           // Minimum VSBF thresholds
    distinguishThreads   = true;        // distinguish threads
    printStatsPostWarmup = true;        // Should I Print Stats Post Warm-Up
    adapt                = true;        // adapt the insertion policy    
    BIP_mask             = ~0;          // static BIP all threads do BIP

    // Initialize the Insertion Policy and stats
    Init();

cerr << "Content of InsertionPolicy " << InsertionPolicy << endl;
    switch( InsertionPolicy ) 
    {
      case INSERTION_POLICY_THREAD_UNAWAREc:
        DEBUG_PRINT("Do not distinguish threads");
        InsertionPolicy = INSERTION_POLICY_THREAD_AWARE;            
        distinguishThreads = false;
        break;
    }

    if( InsertionPolicy == INSERTION_POLICY_THREAD_AWAREc )
    {
    cerr << "AGGGGGGGGGGG "  << endl;
        DEBUG_PRINT("Creating SDMs: "<<(_sizeOfSDM)<<" PSELmax: "<<PSELmax);

        CreateSDM( _sizeOfSDM );         
    }
    else if (InsertionPolicy == INSERTION_POLICY_BIMODALc )
    {
        DEBUG_PRINT("Doing a bimodal insertion policy with mask: "<<hex<<BIP_mask);
    }
    
    cerr << "quickDIP::quickDIPf()" << endl;

}

// Clear Stats
inline void quickDIP::Init()
{
cerr << "quickDIP::Init()" << endl;
    // Initialize Cache Miss Stats
    perSetMisses   = (uint64 **) calloc( NumSets(), sizeof(uint64*) );
    perSetHits     = (uint64 **) calloc( NumSets(), sizeof(uint64*) );
    for(unsigned int i=0; i<NumSets(); i++) 
    {
        perSetMisses[i] = (uint64 *) calloc( NumThreadsPerCache, sizeof(uint64) );
        perSetHits[i]   = (uint64 *) calloc( NumThreadsPerCache, sizeof(uint64) );
    }

    // Per Thread Stats
    totalPerThreadMisses = (uint64 *) calloc( NumThreadsPerCache, sizeof(uint64) );
    totalPerThreadHits   = (uint64 *) calloc( NumThreadsPerCache, sizeof(uint64) );
    totalPerThreadVulnerableInsertions   = (uint64 *) calloc( NumThreadsPerCache, sizeof(uint64) );

    // total misses
    totalDemandMisses = 0;
    totalPrefetchMisses = 0;
    
    // total misses
    totalVulnerableInsertions = 0;

    // total hits
    totalDemandHits   = 0;        
    totalPrefetchHits = 0;

    // Per Thread Miss Stats in SDMs
    SDMmissCountPerThread = (uint64*) calloc( NumThreadsPerCache, sizeof(uint64) );

    // Initialize the per thread selection counters
    thread_active = (unsigned int*) calloc( NumThreadsPerCache, sizeof(unsigned int) );
    PSEL_cntr      = (unsigned int*) calloc( NumThreadsPerCache, sizeof(unsigned int) );
    policy_selecton_threshold  = (unsigned int*) calloc( NumThreadsPerCache, sizeof(unsigned int) );
            
    for(unsigned int i=0; i<NumThreadsPerCache; i++)
    {
        PSEL_cntr[i]  = 0;
        policy_selecton_threshold[i] = (unsigned int) ((float) PSELmax * 0.5);
    }
    
    cerr << "quickDIP::Init()f" << endl;
}


// Destructor deletes leaderset info and psel counters
inline quickDIP::~quickDIP()
{
    SetMissHistogram();
    free( SDM_Info );
    free( PSEL_cntr );
}

inline void
quickDIP::CreateSDM( unsigned int _sizeOfSDM )
{    
    SDM_Info = (quickDIP_SDM_t*) calloc( NumSets(), sizeof(quickDIP_SDM_t) );

    RandomlyChooseSDMs();

//     SetIndexBitBasedSDM();
}

// Choose Leader Sets Based on bits 0-5 and 6-10 of the set index
inline void quickDIP::SetIndexBitBasedSDM()
{
#define MASK 31
#define TOP5(x) ((x>>6)&MASK)
#define BOT5(x) (x&MASK)
#define BIT5(x) ((x>>5)&1)

    for( unsigned int si=0; si<NumSets(); si++) 
    {
        // Dedicate Per Thread SDMs
        // Can determine if it is my dedicated set or not
        for( unsigned int c=0; c<NumThreadsPerCache; c++ )
        {
            int index = si - c - 1;

            if( BIT5(index) && index>=0 && (TOP5(index) == BOT5(index)) )
            {
                // Check to make sure this set isn't already assigned
                if( SDM_Info[si].SDM_Type != quickDIP_FOLLOWERS )
                {
                    cout<<"This set: "<<si<<" already assigned to: "
                        <<SDM_Info[si].SDM_Owner<<endl;
                    exit(0);
                }

                SDM_Info[si].SDM_Type = quickDIP_LRU_SDM;
                SDM_Info[si].SDM_Owner = c;

                DEBUG_PRINT("Assigning: "<<si<<" as NF for core: "<<c);
            }

            index = si + c + 1;
            if( !BIT5(index) && index<=2047 && (TOP5(index) == BOT5(index)) )
            {
                // Check to make sure this set isn't already assigned
                if( SDM_Info[si].SDM_Type != quickDIP_FOLLOWERS )
                {
                    cout<<"This set: "<<si<<" already assigned to: "
                        <<SDM_Info[si].SDM_Owner<<endl;
                    exit(0);
                }


                SDM_Info[si].SDM_Type = quickDIP_BIP_SDM;
                SDM_Info[si].SDM_Owner = c;

                DEBUG_PRINT("Assigning: "<<si<<" as BF for core: "<<c);
            }
        }
    }
}

///////////////////////////////////////
// My Pseudo Random Number Generator //
///////////////////////////////////////

inline int quickDIP::quickDIP_rand(void) {
    quickDIP_rand_seed = quickDIP_rand_seed * 1103515245 + 12345;
    return((unsigned)(quickDIP_rand_seed/65536) % quickDIP_max_rand);
}

inline void quickDIP::quickDIP_srand(unsigned seed) {
    quickDIP_rand_seed = seed;
}

///////////////////////////////////////
///////////////////////////////////////

// Randomly assign sets to SDMs
inline void quickDIP::RandomlyChooseSDMs() 
{
    unsigned int      tot_SDM_Size;        // total SDM size of cache
    unsigned int      tot_SDM_Count;       // Number of SDMs per thread

    tot_SDM_Size  = SDM_Size * NumThreadsPerCache;
    tot_SDM_Count = 2;

    if( NumSets() < (tot_SDM_Size * tot_SDM_Count ) ) {
        cout<<"Size of SDMs is Greater Than Total Sets"<<endl;
        assert(0);
    }

    // When using multiple cache banks, seeding is to ensure that all
    // banks use the same sampled sets
    quickDIP_rand_seed = 1;

    for(unsigned int p=0; p<tot_SDM_Count; p++) 
    {
        // Assign per-thread SDMs
        unsigned int tid = 0;
        unsigned int ownerSets = SDM_Size;
            
        for(unsigned int ldr=0; ldr<tot_SDM_Size; ldr++) 
        {
            unsigned int rand_set_indx;
            do 
            {
//                 rand_set_indx = rand() % NumSets();
                rand_set_indx = quickDIP_rand() % NumSets();

            }
            while( SDM_Info[rand_set_indx].SDM_Type != quickDIP_FOLLOWERS );

            // Set the Leader Set Type (NF or BF)
            SDM_Info[rand_set_indx].SDM_Type = p+1;

            // Set the leader set owner
            SDM_Info[rand_set_indx].SDM_Owner = tid;

            DEBUG_PRINT("Assigning: "<<rand_set_indx<<" as Type: "<<(p+1)<<" for core: "<<tid);

            --ownerSets;

            // If owner sets has reached zero, move to next tid
            if( ownerSets == 0 ) 
            {
                tid++;
                ownerSets = SDM_Size;
            }
        }
    }
}

// Input:  A threshold value describing the percent of misses normally filled
// Output: True if insertion should be normal, false if insertion is vulnerable
inline bool quickDIP::BimodalSuggestion( unsigned int throttle )
{
    // If random number less than throttle, need to do NF
    if( (unsigned int) (rand() % 100) <= throttle ) return true;

    // Do VF
    return false;
}

// Input:  CPU or Thread ID and set number
// Output: none
// Function: update PSEL counter based on misses in competing insertion policy
inline void quickDIP::RecordMiss(
    unsigned int cpuid,
    unsigned int setnum,
    bool   is_demand_req,
    bool   warmup_mode )
{    

    //cpuid = cpuid % NumThreadsPerCache;
    
/*    if( setnum >= NumSets() ) 
    {
        cout<<cachename<<": Requested Set is: "<<setnum<<" > "<<NumSets()<<endl;
        exit(0);
    }
*/
    // total misses increment
    if( is_demand_req ) 
        totalDemandMisses++;
    else
        totalPrefetchMisses++;
    
    perSetMisses[setnum][cpuid]++;
    totalPerThreadMisses[cpuid]++;

/*    if( (warmup_mode == false) && (printStatsPostWarmup) ) 
    {
        printStatsPostWarmup = false;
        SetMissHistogram();
    }

    if( (NumRefs() % PRINT_EVERY) == 0)
    {
        PrintThrottles( warmup_mode );
    }
*/

    // If we are not distinguishing threads, then set the cpuid = 0
//    if( distinguishThreads == false ) cpuid = 0;

//     if( !thread_active[cpuid] ) 
//     {
//         DEBUG_PRINT(cachename<<": "<<myID<<" Registering Thread: "<<cpuid);
// 
//         // register the thread as having activity in the cache
//         thread_active[ cpuid ] = 1;
// 
//         // reset the PSEL value
//         PSEL_cntr[cpuid] = 0;
//     }

	 SetDuel_RecordMiss( cpuid, setnum );
    
}

// Input:  CPU or Thread ID and set number
// Output: none
// Function: update PSEL counter based on misses in competing insertion policy
inline void quickDIP::RecordHit(
    unsigned int cpuid,
    unsigned int setnum,
    bool   is_demand_req,
    bool   warmup_mode)
{
    cpuid = cpuid % NumThreadsPerCache;

/*    if( (warmup_mode == false) && (printStatsPostWarmup) ) 
    {
        printStatsPostWarmup = false;
        SetMissHistogram();
    }*/

    // total hits increment
    if( is_demand_req ) 
        totalDemandHits++;
    else
        totalPrefetchHits++;
    
    perSetHits[setnum][cpuid]++;
    totalPerThreadHits[cpuid]++;

/*    if( (NumRefs() % PRINT_EVERY) == 0 )
    {
        PrintThrottles( warmup_mode );
    }
*/
    // If we are not distinguishing threads, then set the cpuid = 0
    //if( distinguishThreads == false ) cpuid = 0;

//     if( !thread_active[cpuid] ) 
//     {
//         DEBUG_PRINT(cachename<<": "<<myID<<" Registering Thread: "<<cpuid);
// 
//         // register the thread as having activity in the cache
//         thread_active[ cpuid ] = 1;
//     }
}

// Input:  CPU or Thread ID and set number
// Output: true if LRU should be updated, false if VF
// Function: Should the current cpuid do a NF or VF in this set?
inline bool quickDIP::DoNormalFill(
    unsigned int cpuid,
    unsigned int setnum )
{
    bool  updateLRU = true;
    
    //cpuid = cpuid % NumThreadsPerCache;
//DEBUG_PRINT(" DoNormalFill ");

//if(InsertionPolicy == INSERTION_POLICY_NONE) cerr << "InsertionPolicy = INSERTION_POLICY_NONE" << endl;



    if( InsertionPolicy == INSERTION_POLICY_THREAD_AWAREc )
    {
    
        updateLRU = SetDuel_DoNormalFill( cpuid, setnum );

        if( updateLRU == false ) 
        {
            totalVulnerableInsertions++;
            totalPerThreadVulnerableInsertions[cpuid]++;
        }
    }
    else if( InsertionPolicy == INSERTION_POLICY_BIMODALc ) 
    {
    	
        updateLRU = BimodalSuggestion( BIP_epsilon );

        if( ((1<<cpuid) & BIP_mask)==0 )
        {
            updateLRU = true;
        }        
    }
    else if( InsertionPolicy != INSERTION_POLICY_NONEc )
    {
        cout <<"Unimplemented Insertion Policy -- What is this policy supposed to do?"<<endl;
        assert(0);
    }

    return updateLRU;
}
    
// Input:  CPU or Thread ID and set number
// Output: none
// Function: update PSEL counter based on misses in competing insertion policy
inline void quickDIP::SetDuel_RecordMiss(
    unsigned int cpuid,
    unsigned int setnum,
    bool   warmup_mode)
{
    unsigned int owner   = SDM_Info[setnum].SDM_Owner;
    unsigned int settype = SDM_Info[setnum].SDM_Type;

    // if it is an SDM that does NF policy increment PSEL
    if( settype == quickDIP_LRU_SDM ) 
    {
        if( PSEL_cntr[owner] < PSELmax ) PSEL_cntr[owner]++;

        // Track number of misses to the dedicated sets
        SDMmissCountPerThread[owner]++;
    }
    // if it is an SDM that does BF policy decrement PSEL
    else if( settype == quickDIP_BIP_SDM ) 
    {
        if( PSEL_cntr[owner] > 0 ) PSEL_cntr[owner]--;
            
        // Track number of misses to the dedicated sets
        SDMmissCountPerThread[owner]++;
    }
}

// Input:  CPU or Thread ID and set number
// Output: true if LRU should be updated, false if VF
// Function: Should the current cpuid do a NF or VF in this set?
inline bool quickDIP::SetDuel_DoNormalFill(
    unsigned int cpuid,
    unsigned int setnum )
{
    bool updateLRU = true;
    
    //DEBUG_PRINT( "SetDuel_DoNormalFill1: "<<cpuid<<" setnum: "<<setnum);
    
    // Is it an SDM that does NF policy and is dedicated to this cpu?
    if( setnum != (unsigned int) -1
        && SDM_Info[setnum].SDM_Type == quickDIP_LRU_SDM  
        && SDM_Info[setnum].SDM_Owner == cpuid ) 
    {
    	
    	//cerr <<this << " SetDuel_DoNormalFill1: "<<cpuid<<" setnum: "<<setnum << endl;
    	
        updateLRU = true;
    }
    // Is it an SDM that does BF policy and is dedicated to this cpu?
    else if( setnum != (unsigned int) -1
             && SDM_Info[setnum].SDM_Type == quickDIP_BIP_SDM
             && SDM_Info[setnum].SDM_Owner == cpuid ) 
    {
        
        unsigned int useThreshold = BIP_epsilon;
        
        //cerr << this <<" SetDuel_DoNormalFill12: "<<cpuid<<" setnum: "<<setnum << endl;


        updateLRU = BimodalSuggestion( useThreshold );
    }
    else // it is a follower set
    {
        unsigned int InsertionPolicy = GetCurrentInsertionPolicy( cpuid );

		//DEBUG_PRINT("SetDuel_DoNormalFill13: "<<cpuid<<" setnum: "<<setnum);

        updateLRU = (InsertionPolicy == quickDIP_LRU_SDM) ? true : BimodalSuggestion( BIP_epsilon );
    }

    return updateLRU;
}    

// Input:  CPU or Thread ID
// Output: Insertion Policy for current CPU
// Function: We determine the current insertion policy

inline unsigned int quickDIP::GetCurrentInsertionPolicy( unsigned int cpuid ) 
{
    // If we are not adapting at all, then just return true
    //if( !adapt ) return quickDIP_LRU_SDM;

    if( PSEL_cntr[cpuid] > policy_selecton_threshold[cpuid] ) 
    {
        return quickDIP_BIP_SDM;            
    }
    else if( PSEL_cntr[cpuid] <= (policy_selecton_threshold[cpuid]) ) 
    {
        return quickDIP_LRU_SDM;
    }

    return quickDIP_LRU_SDM;
}

// Print Dynamic Throttles
inline void quickDIP::PrintThrottles(bool warmup_mode) 
{
    if( DEBUG_PRINT_ON )
    {
        PrintStats( warmup_mode );
    }
}

// Print Dynamic Throttles
inline void quickDIP::PrintStats( bool warmup_mode )
{
    unsigned int missrate = (totalDemandMisses * 100) / (totalDemandMisses+totalDemandHits);
    
    cout<<cachename<<": "<<myID
        <<" WarmUp: "<<(unsigned int)warmup_mode
        <<" Miss Rate: "<<missrate
        <<" Total Fills: "<<totalDemandMisses
        <<" Vulnerable Fills: "<<totalVulnerableInsertions
        <<" Total Demand References: "<<NumDemandRefs()
        <<" Total Prefetch Fills: "<<totalPrefetchMisses
        <<" Total Prefetch References: "<<NumPrefetchRefs()
        <<endl;

    for(unsigned int tid=0; tid<NumThreadsPerCache; tid++) 
    {

        if( thread_active[tid] ) 
        {

            cout<<"\tCPU ID: "<<tid;
        
            if( InsertionPolicy == INSERTION_POLICY_THREAD_AWAREc )
            {
                cout<<" Selector: "<<PSEL_cntr[tid]
                    <<" Throttle: "<<(GetCurrentInsertionPolicy(tid)==quickDIP_BIP_SDM ? (BIP_epsilon):(100));
                    
            }

            uint64 threadRefs = totalPerThreadMisses[tid]+totalPerThreadHits[tid];
            double MR = threadRefs ? ((double)totalPerThreadMisses[tid]/threadRefs*100) : 0;
        
            cout<<"\tMisses: "<<totalPerThreadMisses[tid]<<"/"<<threadRefs<<" Miss Rate: "<<MR<<endl;
            
        }
        
    }
}

// Set Miss Histograms
inline void quickDIP::SetMissHistogram()
{
    if( DEBUG_PRINT_ON )
    {
        cout<<cachename<<": "<<myID<<" Cache Statistics: "<<totalDemandMisses<<"/"<<NumRefs()
            <<" Miss Rate: "<<((double)totalDemandMisses/NumDemandRefs()*100)<<endl;
    
        // Per Thread Stats
        for(unsigned int tid=0; tid<NumThreadsPerCache; tid++) {
            if( thread_active[tid] ) {
                uint64 threadRefs = totalPerThreadMisses[tid]+totalPerThreadHits[tid];
                cout<<"\ttid: "<<tid<<" "<<totalPerThreadMisses[tid]<<"/"<<threadRefs
                    <<" Miss Rate: "<<((double)totalPerThreadMisses[tid]/threadRefs*100)<<endl;
            }
        }
    
        cout<<endl<<"Per Set Statistics"<<endl;
        for(unsigned int setnum=0; setnum<NumSets(); setnum++) 
        {
            cout<<"\tSet:\t"<<setnum<<"\t";

            if( InsertionPolicy == INSERTION_POLICY_THREAD_AWAREc )
            {
                cout<<"owner:\t"<<SDM_Info[setnum].SDM_Owner<<"\t"
                    <<"type:\t"<<SDM_Info[setnum].SDM_Type<<"\t";
            }

            uint64 setMisses = 0;
            for(unsigned int tid=0; tid<NumThreadsPerCache; tid++) 
            {
                if( thread_active[tid] ) 
                {
                    uint64 tidMisses = perSetMisses[setnum][tid];
                    uint64 tidHits   = perSetHits[setnum][tid];
                    uint64 tidRefs   = tidMisses + tidHits;
                
                    cout<<"tid: "<<tid<<" Misses: "<<tidMisses<<"/"<<tidRefs<<"\t";
                    setMisses += tidMisses;
                }
            }
         
            cout<<"Total Misses:\t"<<setMisses<<endl;
        }
        cout<<endl<<endl;
    }
    else 
    {
        PrintStats( false );
    }
}
#endif
