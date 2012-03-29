

#ifndef NRUPolicy_DRRIPb_H
#define NRUPolicy_DRRIPb_H

// Si un elemento se elige como v’ctima pero est‡ en las caches privadas se meter‡ en la cabeza de la pila

#include "AbstractReplacementPolicy.h"

#define USE_INSERTION_POLICY  2     // Use TADIP
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



// SDM Types
typedef enum 
{
    DIP_FOLLOWERS       = 0,
    DIP_LRU_SDM         = 1,  
    DIP_BIP_SDM         = 2,
} DIP_SDM_Type_t;

// SDM Descriptor
typedef struct 
{
    uint32       SDM_Type;   // What type of SDM 
    uint32       SDM_Owner;  // Who manages the SDM
} DIP_SDM_t;

// Insertion Policy
typedef enum
{
    INSERTION_POLICY_NONE                    = 0,
    INSERTION_POLICY_THREAD_UNAWARE          = 1,
    INSERTION_POLICY_THREAD_AWARE            = 2,
    INSERTION_POLICY_BIMODAL                 = 3,
} DIP_t;


class DIP;

class NRUPolicy_DRRIPb : public AbstractReplacementPolicy {
 public:

  NRUPolicy_DRRIPb(Index num_sets, Index assoc, Vector<Vector<L1Cache_Entry> > *a, uint version);
  NRUPolicy_DRRIPb(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a, uint version);
  ~NRUPolicy_DRRIPb();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  Vector<Vector<L2Cache_Entry> > *m_cache;
  
  bool subSet(L2Cache_Entry *a, uint set) const;
  uint whatSubSet(L2Cache_Entry &a) const;
  uint countSegments(uint set, uint what) const;
  void replacementLower(Index set, Index way) const;
  //unsigned int GetCurrentInsertionPolicy( unsigned int cpuid ) ;
  
  void UpdateRRIP( unsigned int tid, unsigned int setIndex, int updateWayID, bool cacheHit );

  Index* m_pointer;

  void printStats(ostream& out, char* name);
  void printStats(ostream& out) const;
  void clearStats() ;
  
  int** R;
  uint m_version;
  
  //DRRIP
  
	DIP *rrip;
};

class DIP
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
    DIP_SDM_t   *SDM_Info;

    uint32      NumThreadsPerCache;  // number threads per cache
    uint32      SDM_Size;            // Size of an SDM

    uint32      BIP_epsilon;         // BIP epsilon
    uint32      BIP_mask;            // Mask to define static BIP
    
    unsigned long dip_rand_seed ;
	unsigned long dip_max_rand ;

  public:

    //  This is the interface for creating cache SDMs. The args are:
    //   a)  cache name (debugging purpose)
    //   b)  bank # (debugging purpose)
    //   c)  threads sharing this cache
    //   d)  total sets in the cache
    //   e)  insertion policy to use (as defined by DIP_t above)
    //   f)  Max PSEL value (if 10-bit PSEL, use argument of 2^10)
    //   g)  # of sets per SDM

    DIP( 
        string _cachename,
        uint32 _myID,
        uint32 _tpc,
        uint32 _totalSets=2048,
        uint32 _usePolicy=INSERTION_POLICY_THREAD_AWARE,
        uint32 _maxPSEL=1024, 
        uint32 _sizeOfSDM=32 );

    // Initialize Stats
    void Init();

    // Initialize BIP Mask
    void InitBIPmask( uint32 _mask ) { BIP_mask = _mask; };

    // Destructor deletes dynamic structures
    ~DIP();

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
    
    int dip_rand(void);
    void dip_srand(unsigned seed) ;

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
NRUPolicy_DRRIPb::clearStats(){}

inline
NRUPolicy_DRRIPb::NRUPolicy_DRRIPb(Index num_sets, Index assoc, Vector<Vector<L2Cache_Entry> > *a, uint version)
  : AbstractReplacementPolicy(num_sets, assoc)
{
  m_version = version;
  m_cache = a;
  m_num_sets = num_sets;
  

	rrip = new DIP( "LLC", 0, 8, num_sets, USE_INSERTION_POLICY, ((1<<USE_PSELwidth)-1),USE_SDMsize);
}

inline
NRUPolicy_DRRIPb::~NRUPolicy_DRRIPb()
{
}


inline void NRUPolicy_DRRIPb::replacementLower(Index set, Index way) const  {

}
 
 
 
inline 
void NRUPolicy_DRRIPb::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

	L2Cache_Entry &p=(*m_cache)[set][index];
	
	if(time==0) {
		//It is set to the last group. UpdateRRIP will decide
		p.m_RRPV = maxRPV; 
		
		rrip->RecordMiss( proc, set, 1, 0);
		UpdateRRIP(proc, set, index, 0);
		
	} else {
		rrip->RecordHit( proc, set, 1, 0 );
		UpdateRRIP(proc, set, index, 1);
		
  		//p.m_RRPV > 0 ? p.m_RRPV-- : 0;
  		p.m_RRPV = 0;
  	}
	
}

inline
Index NRUPolicy_DRRIPb::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  	
  
	L2Cache_Entry *p;
	bool found = false;
	
	
	while(!found)
	{
		uint k=0;
		//buscamos el primero con el RRPV a 2^m-1
		for(uint i = 0; i < m_assoc; i++) {
			p = &(*m_cache)[set][i];
			//cerr << "p->m_RRPV: " << p->m_RRPV << " DISTANT_VALUE: " << DISTANT_VALUE<< endl;	
			if(p->m_RRPV == DISTANT_VALUE) {
				if(g_PROTEGE_RRIP && p->m_Sharers.count() > 0) {
					//p->m_RRPV = DISTANT_VALUE - 1;
					p->m_RRPV = 0;
					k++;
				}
				else {
					return i;
				}
			}
		}
		if(k==m_assoc) { //caso patologico
			return 0;
		}
		//si no lo encontramos incrementamos todos y repetimos
		for(uint i = 0; i < m_assoc; i++) {
			p = &(*m_cache)[set][i];
			p->m_RRPV < DISTANT_VALUE ? p->m_RRPV++ : 0;
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
bool NRUPolicy_DRRIPb::subSet(L2Cache_Entry *a, uint set) const
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
uint NRUPolicy_DRRIPb::whatSubSet(L2Cache_Entry &a) const
{
  if(a.m_Sharers.count()==0 && !a.m_reused) return 0;
  if(a.m_Sharers.count()==0 && a.m_reused) return 1;
  if(a.m_Sharers.count()!=0) return 2;

  assert(0);
  return -1;
  
}

inline 
uint NRUPolicy_DRRIPb::countSegments(uint set, uint what) const
{
	uint aux=0;
	for(uint i=0; i<m_assoc; i++) if(whatSubSet((*m_cache)[set][i]) == what) aux++;
	
	return aux;
	
	uint res[]={0,0,0};
	
	for(uint i=0; i<3; i++) res[whatSubSet((*m_cache)[set][i])]++;
	
	//return res;
  
}

inline
void NRUPolicy_DRRIPb::printStats(ostream& out, char* name)   
{ int a=0;
	cout << "Stats DRRIPb:" << endl;
	rrip->PrintStats(0);
}

inline
void NRUPolicy_DRRIPb::printStats(ostream& out)  const
{ int a=0;}






inline void NRUPolicy_DRRIPb::UpdateRRIP( unsigned int tid, unsigned int setIndex, int updateWayID, bool cacheHit )
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


//******************************************************************************************************




////////////////////////

// This is the interface for creating cache SDMs. The args are:
//   a)  cache name (debugging purpose)
//   b)  bank # (debugging purpose)
//   c)  threads sharing this cache
//   d)  total sets in the cache
//   e)  insertion policy to use (as defined by DIP_t)
//   f)  Max PSEL value (if 10-bit PSEL, use argument of 2^10)
//   g)  # of sets per SDM

inline DIP::DIP ( 
    string _cachename,
    unsigned int _myID,
    unsigned int _tpc,
    unsigned int _totalSets,
    unsigned int _usePolicy,
    unsigned int _maxPSEL,
    unsigned int _sizeOfSDM )
{
dip_rand_seed = 1;
dip_max_rand  = 1048576;
cerr << "DIP::DIP()" << endl;

    cerr << "Initializing DIP-"<<_cachename<<"-"<<_myID
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
      case INSERTION_POLICY_THREAD_UNAWARE:
        DEBUG_PRINT("Do not distinguish threads");
        InsertionPolicy = INSERTION_POLICY_THREAD_AWARE;            
        distinguishThreads = false;
        break;
    }

    if( InsertionPolicy == INSERTION_POLICY_THREAD_AWARE )
    {
    cerr << "AGGGGGGGGGGG "  << endl;
        DEBUG_PRINT("Creating SDMs: "<<(_sizeOfSDM)<<" PSELmax: "<<PSELmax);

        CreateSDM( _sizeOfSDM );         
    }
    else if (InsertionPolicy == INSERTION_POLICY_BIMODAL )
    {
        DEBUG_PRINT("Doing a bimodal insertion policy with mask: "<<hex<<BIP_mask);
    }
    
    cerr << "DIP::DIPf()" << endl;

}

// Clear Stats
inline void DIP::Init()
{
cerr << "DIP::Init()" << endl;
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
    
    cerr << "DIP::Init()f" << endl;
}


// Destructor deletes leaderset info and psel counters
inline DIP::~DIP()
{
    SetMissHistogram();
    free( SDM_Info );
    free( PSEL_cntr );
}

inline void
DIP::CreateSDM( unsigned int _sizeOfSDM )
{    
    SDM_Info = (DIP_SDM_t*) calloc( NumSets(), sizeof(DIP_SDM_t) );

    RandomlyChooseSDMs();

//     SetIndexBitBasedSDM();
}

// Choose Leader Sets Based on bits 0-5 and 6-10 of the set index
inline void DIP::SetIndexBitBasedSDM()
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
                if( SDM_Info[si].SDM_Type != DIP_FOLLOWERS )
                {
                    cout<<"This set: "<<si<<" already assigned to: "
                        <<SDM_Info[si].SDM_Owner<<endl;
                    exit(0);
                }

                SDM_Info[si].SDM_Type = DIP_LRU_SDM;
                SDM_Info[si].SDM_Owner = c;

                DEBUG_PRINT("Assigning: "<<si<<" as NF for core: "<<c);
            }

            index = si + c + 1;
            if( !BIT5(index) && index<=2047 && (TOP5(index) == BOT5(index)) )
            {
                // Check to make sure this set isn't already assigned
                if( SDM_Info[si].SDM_Type != DIP_FOLLOWERS )
                {
                    cout<<"This set: "<<si<<" already assigned to: "
                        <<SDM_Info[si].SDM_Owner<<endl;
                    exit(0);
                }


                SDM_Info[si].SDM_Type = DIP_BIP_SDM;
                SDM_Info[si].SDM_Owner = c;

                DEBUG_PRINT("Assigning: "<<si<<" as BF for core: "<<c);
            }
        }
    }
}

///////////////////////////////////////
// My Pseudo Random Number Generator //
///////////////////////////////////////

inline int DIP::dip_rand(void) {
    dip_rand_seed = dip_rand_seed * 1103515245 + 12345;
    return((unsigned)(dip_rand_seed/65536) % dip_max_rand);
}

inline void DIP::dip_srand(unsigned seed) {
    dip_rand_seed = seed;
}

///////////////////////////////////////
///////////////////////////////////////

// Randomly assign sets to SDMs
inline void DIP::RandomlyChooseSDMs() 
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
    dip_rand_seed = 1;

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
                rand_set_indx = dip_rand() % NumSets();

            }
            while( SDM_Info[rand_set_indx].SDM_Type != DIP_FOLLOWERS );

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
inline bool DIP::BimodalSuggestion( unsigned int throttle )
{
    // If random number less than throttle, need to do NF
    if( (unsigned int) (rand() % 100) <= throttle ) return true;

    // Do VF
    return false;
}

// Input:  CPU or Thread ID and set number
// Output: none
// Function: update PSEL counter based on misses in competing insertion policy
inline void DIP::RecordMiss(
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
inline void DIP::RecordHit(
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
inline bool DIP::DoNormalFill(
    unsigned int cpuid,
    unsigned int setnum )
{
    bool  updateLRU = true;
    
    //cpuid = cpuid % NumThreadsPerCache;
//DEBUG_PRINT(" DoNormalFill ");

//if(InsertionPolicy == INSERTION_POLICY_NONE) cerr << "InsertionPolicy = INSERTION_POLICY_NONE" << endl;



    if( InsertionPolicy == INSERTION_POLICY_THREAD_AWARE )
    {
    
        updateLRU = SetDuel_DoNormalFill( cpuid, setnum );

        if( updateLRU == false ) 
        {
            totalVulnerableInsertions++;
            totalPerThreadVulnerableInsertions[cpuid]++;
        }
    }
    else if( InsertionPolicy == INSERTION_POLICY_BIMODAL ) 
    {
    	
        updateLRU = BimodalSuggestion( BIP_epsilon );

        if( ((1<<cpuid) & BIP_mask)==0 )
        {
            updateLRU = true;
        }        
    }
    else if( InsertionPolicy != INSERTION_POLICY_NONE )
    {
        cout <<"Unimplemented Insertion Policy -- What is this policy supposed to do?"<<endl;
        assert(0);
    }

    return updateLRU;
}
    
// Input:  CPU or Thread ID and set number
// Output: none
// Function: update PSEL counter based on misses in competing insertion policy
inline void DIP::SetDuel_RecordMiss(
    unsigned int cpuid,
    unsigned int setnum,
    bool   warmup_mode)
{
    unsigned int owner   = SDM_Info[setnum].SDM_Owner;
    unsigned int settype = SDM_Info[setnum].SDM_Type;

    // if it is an SDM that does NF policy increment PSEL
    if( settype == DIP_LRU_SDM ) 
    {
        if( PSEL_cntr[owner] < PSELmax ) PSEL_cntr[owner]++;

        // Track number of misses to the dedicated sets
        SDMmissCountPerThread[owner]++;
    }
    // if it is an SDM that does BF policy decrement PSEL
    else if( settype == DIP_BIP_SDM ) 
    {
        if( PSEL_cntr[owner] > 0 ) PSEL_cntr[owner]--;
            
        // Track number of misses to the dedicated sets
        SDMmissCountPerThread[owner]++;
    }
}

// Input:  CPU or Thread ID and set number
// Output: true if LRU should be updated, false if VF
// Function: Should the current cpuid do a NF or VF in this set?
inline bool DIP::SetDuel_DoNormalFill(
    unsigned int cpuid,
    unsigned int setnum )
{
    bool updateLRU = true;
    
    //DEBUG_PRINT( "SetDuel_DoNormalFill1: "<<cpuid<<" setnum: "<<setnum);
    
    // Is it an SDM that does NF policy and is dedicated to this cpu?
    if( setnum != (unsigned int) -1
        && SDM_Info[setnum].SDM_Type == DIP_LRU_SDM  
        && SDM_Info[setnum].SDM_Owner == cpuid ) 
    {
    	
    	//cerr <<this << " SetDuel_DoNormalFill1: "<<cpuid<<" setnum: "<<setnum << endl;
    	
        updateLRU = true;
    }
    // Is it an SDM that does BF policy and is dedicated to this cpu?
    else if( setnum != (unsigned int) -1
             && SDM_Info[setnum].SDM_Type == DIP_BIP_SDM
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

        updateLRU = (InsertionPolicy == DIP_LRU_SDM) ? true : BimodalSuggestion( BIP_epsilon );
    }

    return updateLRU;
}    

// Input:  CPU or Thread ID
// Output: Insertion Policy for current CPU
// Function: We determine the current insertion policy

inline unsigned int DIP::GetCurrentInsertionPolicy( unsigned int cpuid ) 
{
    // If we are not adapting at all, then just return true
    //if( !adapt ) return DIP_LRU_SDM;

    if( PSEL_cntr[cpuid] > policy_selecton_threshold[cpuid] ) 
    {
        return DIP_BIP_SDM;            
    }
    else if( PSEL_cntr[cpuid] <= (policy_selecton_threshold[cpuid]) ) 
    {
        return DIP_LRU_SDM;
    }

    return DIP_LRU_SDM;
}

// Print Dynamic Throttles
inline void DIP::PrintThrottles(bool warmup_mode) 
{
    if( DEBUG_PRINT_ON )
    {
        PrintStats( warmup_mode );
    }
}

// Print Dynamic Throttles
inline void DIP::PrintStats( bool warmup_mode )
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
        
            if( InsertionPolicy == INSERTION_POLICY_THREAD_AWARE )
            {
                cout<<" Selector: "<<PSEL_cntr[tid]
                    <<" Throttle: "<<(GetCurrentInsertionPolicy(tid)==DIP_BIP_SDM ? (BIP_epsilon):(100));
                    
            }

            uint64 threadRefs = totalPerThreadMisses[tid]+totalPerThreadHits[tid];
            double MR = threadRefs ? ((double)totalPerThreadMisses[tid]/threadRefs*100) : 0;
        
            cout<<"\tMisses: "<<totalPerThreadMisses[tid]<<"/"<<threadRefs<<" Miss Rate: "<<MR<<endl;
            
        }
        
    }
}

// Set Miss Histograms
inline void DIP::SetMissHistogram()
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

            if( InsertionPolicy == INSERTION_POLICY_THREAD_AWARE )
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
