#include "replacement_state.h"
#include "dip.h"

#define DEBUG_PRINT(X) cerr<<X<<dec<<endl;
/********************************************************************************
** Parameter for Re-Reference Interval Prediction (RRIP) [ISCA'2010]:
** ===================================================================
** 
** Change macro maxRPV below to simulate one of the following policies:
**
**     (a)  maxRPV=1 simulates Not Recently Used (NRU) replacement.
**          NRU is the policy commonly used in microprocessors today.
**
**     (b)  maxRPV=3 simulates Static RRIP (SRRIP) with max prediction of 3
**
**     (c)  maxRPV=7 simulates Static RRIP (SRRIP) with max prediction of 7
**
**
** Dynamic Insertion Policy (DIP) [ISCA'07 and PACT'08]:
** ======================================================
** 
** Change macro USE_INSERTION_POLICY below to choose one of the following policies:
**
**     (a)  USE_INSERTION_POLICY=0 simulates baseline policy where all newly
**          inserted blocks are moved to head of RRIP chain (i.e. MRU position)
**
**     (b)  USE_INSERTION_POLICY=1 simulates DIP where newly inserted blocks
**          are inserted either at head of RRIP chain or tail of RRIP chain. In
**          a shared cache, the policy decision is thread-unaware [ISCA'07]
**
**     (c)  USE_INSERTION_POLICY=2 simulates TADIP where newly inserted blocks
**          are inserted either at head of RRIP chain or tail of RRIP chain on a
**          per-thread basis. The policy decisions are thread-aware [PACT'08]
**
** Other DIP Parameters:
** =====================
**     
**     (a) USE_PSELwidth: The number of bits in the Policy Selection (PSEL) counter
**
**     (b) USE_SDMsize:   The number of sets sampled in a Set Dueling Monitor (SDM)
**
** IMPORTANT NOTES:
** =====================
**
** NOTE 1:  The DIP and TADIP papers illustrated a mechanism for using the 
** cache set index to identify SDMs.  To provide a generalized framework 
** where SDMs can be selected for any cache configuration, this source code release
** selects SDMs at random and store the SDM type in a separate data structure.
** However, note that this extra data structure is NOT required as described in the
** DIP and TADIP papers.
**
** NOTE 2:  DRRIP policy configuration is maxRPV > 1 and USE_INSERTION_POLICY=2 (TADIP)
**
********************************************************************************/

#define maxRPV                1     // Use SRRIP replacement

#define USE_INSERTION_POLICY  0     // Use TADIP
#define USE_PSELwidth         10    // Width of the PSEL counter
#define USE_SDMsize           32    // Use 32 sets per SDM

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This file is distributed as part of the Cache Replacement Championship     //
// workshop held in conjunction with ISCA'2010.                               //
//                                                                            //
//                                                                            //
// Everyone is granted permission to copy, modify, and/or re-distribute       //
// this software.                                                             //
//                                                                            //
// Please contact Aamer Jaleel <ajaleel@gmail.com> should you have any        //
// questions                                                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/*
** This file implements the cache replacement state. Users can enhance the code
** below to develop their cache replacement ideas.
**
*/


////////////////////////////////////////////////////////////////////////////////
// The replacement state constructor:                                         //
// Inputs: number of sets, associativity, and replacement policy to use       //
// Outputs: None                                                              //
//                                                                            //
// DO NOT CHANGE THE CONSTRUCTOR PROTOTYPE                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
CACHE_REPLACEMENT_STATE::CACHE_REPLACEMENT_STATE( unsigned int _sets, unsigned int _assoc, unsigned int _pol )
{

    numsets    = _sets;
    assoc      = _assoc;
    replPolicy = _pol;

    mytimer    = 0;

    InitReplacementState();
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This function initializes the replacement policy hardware by creating      //
// storage for the replacement state on a per-line/per-cache basis.           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
void CACHE_REPLACEMENT_STATE::InitReplacementState()
{
    // Create the state for sets, then create the state for the ways
    repl  = new LINE_STATE* [ numsets ];

    // ensure that we were able to create replacement state
    assert(repl);

    // Create the state for the sets
    for(unsigned int setIndex=0; setIndex<numsets; setIndex++) 
    {
        repl[ setIndex ]  = new LINE_STATE[ assoc ];

        for(unsigned int way=0; way<assoc; way++) 
        {
            // initialize stack position (for true LRU)
            repl[ setIndex ][ way ].LRUstackposition = way;

            // initialize RPV to be furthest in future
            repl[ setIndex ][ way ].RPV = maxRPV;
        }
    }

    // Contestants:  ADD INITIALIZATION FOR YOUR HARDWARE HERE
    rrip = new DIP( "LLC", 0, 8, numsets, 
                    USE_INSERTION_POLICY, ((1<<USE_PSELwidth)-1), USE_SDMsize );

}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This function is called by the cache on every cache miss. The input        //
// arguments are the thread id, set index, pointers to ways in current set    //
// and the associativity.  We are also providing the PC, physical address,    //
// and accesstype should you wish to use them at victim selection time.       //
// The return value is the physical way index for the line being replaced.    //
// Return -1 if you wish to bypass LLC.                                       //
//                                                                            //
// vicSet is the current set. You can access the contents of the set by       //
// indexing using the wayID which ranges from 0 to assoc-1 e.g. vicSet[0]     //
// is the first way and vicSet[4] is the 4th physical way of the cache.       //
// Elements of LINE_STATE are defined in crc_cache_defs.h                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
int CACHE_REPLACEMENT_STATE::GetVictimInSet( unsigned int setIndex )
{
    // If no invalid lines, then replace based on replacement policy
        // Contestants:  ADD YOUR VICTIM SELECTION FUNCTION HERE
        return Get_RRIP_Victim( setIndex );
    

    // We should never get here
    assert(0);

    return -1; // Returning -1 bypasses the LLC
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This function is called by the cache after every cache hit/miss            //
// The arguments are: the set index, the physical way of the cache,           //
// the pointer to the physical line (should contestants need access           //
// to information of the line filled or hit upon), the thread id              //
// of the request, the PC of the request, the accesstype, and finall          //
// whether the line was a cachehit or not (cacheHit=true implies hit)         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
void CACHE_REPLACEMENT_STATE::UpdateReplacementState( 
    unsigned int setIndex, int updateWayID,
    unsigned int tid, bool cacheHit )
{

        // Contestants:  ADD YOUR UPDATE REPLACEMENT STATE FUNCTION HERE

        // Record the fact that there was a hit/miss in the RRIP structure
       
            if( cacheHit ) 
            {
                rrip->RecordHit( tid, setIndex );
            }
            else 
            {
                rrip->RecordMiss( tid, setIndex );
            }
        
        
        // Feel free to use any of the input parameters to make
        // updates to your replacement policy

        UpdateRRIP( tid, setIndex, updateWayID, cacheHit );
    
    
    
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//////// HELPER FUNCTIONS FOR REPLACEMENT UPDATE AND VICTIM SELECTION //////////
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This function finds the LRU victim in the cache set by returning the       //
// cache block at the bottom of the LRU stack. Top of LRU stack is '0'        //
// while bottom of LRU stack is 'assoc-1'                                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
int CACHE_REPLACEMENT_STATE::Get_RRIP_Victim( unsigned int setIndex )
{
    // Get pointer to replacement state of current set
    LINE_STATE *replSet = repl[ setIndex ];

    int   vicWay   = 0;
    bool    vicFound = false;

    do 
    {
        // Search for victim whose RPV is furthest in future
        for(unsigned int way=0; way<assoc; way++) 
        {
            if( replSet[way].RPV == maxRPV ) 
            {
                vicWay   = way;
                vicFound = true;
                break;
            }
        }

        // If victim is not found, then move all RPVs into future and
        // then repeat the search again

        if( !vicFound ) 
        {
            for(unsigned int way=0; way<assoc; way++) 
            {
                replSet[way].RPV++;

            }
        }

    } while( !vicFound );

    // return vic way
    return vicWay;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This function finds the LRU victim in the cache set by returning the       //
// cache block at the bottom of the LRU stack. Top of LRU stack is '0'        //
// while bottom of LRU stack is 'assoc-1'                                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This function finds a random victim in the cache set                       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This function implements the LRU update routine for the traditional        //
// LRU replacement policy. The arguments to the function are the physical     //
// way and set index.                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This function implements the RRIP update routine. The arguments to         //
// the function are the physical way and set index.                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
void CACHE_REPLACEMENT_STATE::UpdateRRIP( unsigned int tid, unsigned int setIndex, int updateWayID, bool cacheHit )
{
    // Set the RPV of line to near-immediate
    if( cacheHit ) 
    {
        repl[ setIndex ][ updateWayID ].RPV = 0;
    }
    else 
    {
        bool updateLRUstateOnMiss = rrip->DoNormalFill( tid, setIndex );
        
        if( updateLRUstateOnMiss ) 
        {
            repl[ setIndex ][ updateWayID ].RPV = (maxRPV-1);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// The function prints the statistics for the cache                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
ostream & CACHE_REPLACEMENT_STATE::PrintStats(ostream &out)
{

    out<<"=========================================================="<<endl;
    out<<"=========== Replacement Policy Statistics ================"<<endl;
    out<<"=========================================================="<<endl;

    // CONTESTANTS:  Insert your statistics printing here
    rrip->PrintStats( false );

    return out;
    
}

////////////////////////

// This is the interface for creating cache SDMs. The args are:
//   a)  cache name (debugging purpose)
//   b)  bank # (debugging purpose)
//   c)  threads sharing this cache
//   d)  total sets in the cache
//   e)  insertion policy to use (as defined by DIP_t)
//   f)  Max PSEL value (if 10-bit PSEL, use argument of 2^10)
//   g)  # of sets per SDM

DIP::DIP ( 
    string _cachename,
    unsigned int _myID,
    unsigned int _tpc,
    unsigned int _totalSets,
    unsigned int _usePolicy,
    unsigned int _maxPSEL,
    unsigned int _sizeOfSDM )
{
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
void DIP::Init()
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
DIP::~DIP()
{
    SetMissHistogram();
    free( SDM_Info );
    free( PSEL_cntr );
}

void
DIP::CreateSDM( unsigned int _sizeOfSDM )
{    
    SDM_Info = (DIP_SDM_t*) calloc( NumSets(), sizeof(DIP_SDM_t) );

    RandomlyChooseSDMs();

//     SetIndexBitBasedSDM();
}

// Choose Leader Sets Based on bits 0-5 and 6-10 of the set index
void DIP::SetIndexBitBasedSDM()
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

unsigned long dip_rand_seed = 1;
unsigned long dip_max_rand  = 1048576;

int dip_rand(void) {
    dip_rand_seed = dip_rand_seed * 1103515245 + 12345;
    return((unsigned)(dip_rand_seed/65536) % dip_max_rand);
}

void dip_srand(unsigned seed) {
    dip_rand_seed = seed;
}

///////////////////////////////////////
///////////////////////////////////////

// Randomly assign sets to SDMs
void DIP::RandomlyChooseSDMs() 
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
bool DIP::BimodalSuggestion( unsigned int throttle )
{
    // If random number less than throttle, need to do NF
    if( (unsigned int) (rand() % 100) <= throttle ) return true;

    // Do VF
    return false;
}

// Input:  CPU or Thread ID and set number
// Output: none
// Function: update PSEL counter based on misses in competing insertion policy
void DIP::RecordMiss(
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
    if( distinguishThreads == false ) cpuid = 0;

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

    if( InsertionPolicy == INSERTION_POLICY_THREAD_AWARE )
    {
        SetDuel_RecordMiss( cpuid, setnum, warmup_mode );
    }
}

// Input:  CPU or Thread ID and set number
// Output: none
// Function: update PSEL counter based on misses in competing insertion policy
void DIP::RecordHit(
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
    if( distinguishThreads == false ) cpuid = 0;

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
bool DIP::DoNormalFill(
    unsigned int cpuid,
    unsigned int setnum )
{
    bool  updateLRU = true;
    
    //cpuid = cpuid % NumThreadsPerCache;
//DEBUG_PRINT(" DoNormalFill ");

//if(InsertionPolicy == INSERTION_POLICY_NONE) cerr << "InsertionPolicy = INSERTION_POLICY_NONE" << endl;

    // If we are not distinguishing threads, then set the cpuid = 0
    if( distinguishThreads == false ) cpuid = 0;

    if( !thread_active[cpuid] ) 
    {
        // register the thread as having activity in the cache
        thread_active[ cpuid ] = 1;

//         PSEL_cntr[cpuid] = pselMAX/2;
    }

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
void DIP::SetDuel_RecordMiss(
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
bool DIP::SetDuel_DoNormalFill(
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

unsigned int DIP::GetCurrentInsertionPolicy( unsigned int cpuid ) 
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
void DIP::PrintThrottles(bool warmup_mode) 
{
    if( DEBUG_PRINT_ON )
    {
        PrintStats( warmup_mode );
    }
}

// Print Dynamic Throttles
void DIP::PrintStats( bool warmup_mode )
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
void DIP::SetMissHistogram()
{
    if( DEBUG_PRINT_ON )
    {
        cout<<cachename<<": "<<myID<<" Cache Statistics: "<<totalDemandMisses<<"/"<<NumRefs()
            <<" Miss Rate: "<<((double)totalDemandMisses/NumDemandRefs()*100)<<endl;
    
        // Per Thread Stats
        for(unsigned int tid=0; tid<NumThreadsPerCache; tid++) 
        {
            if( thread_active[tid] ) 
            {
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
