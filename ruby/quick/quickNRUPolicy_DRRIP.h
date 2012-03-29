

#ifndef quickNRUPolicy_DRRIP_H
#define quickNRUPolicy_DRRIP_H

#include "AbstractReplacementPolicyQuick.h"
#include "CacheEntryQuick.h"
#include "dip.h"

#define DISTANT_VALUE ((1<<g_RRIP_N_BITS) - 1)

#ifndef DEBUG_PRINT_ON
#define DEBUG_PRINT_ON 1
#endif

#if DEBUG_PRINT_ON
#define DEBUG_PRINT(X) cout<<X<<dec<<endl;
#else
#define DEBUG_PRINT(X)
#endif

#define USE_PSELwidth         10    // Width of the PSEL counter
#define PSELmax ((1<<USE_PSELwidth)-1)


/* Simple true NRU replacement policy */

class quickNRUPolicy_DRRIP : public AbstractReplacementPolicyQuick {
 public:

  quickNRUPolicy_DRRIP(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a, uint version);
  ~quickNRUPolicy_DRRIP();

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
  void clearStats() ;
  int** R;
  uint m_version;
  
  //DRRIP
  unsigned long dip_rand_seed;
  unsigned long dip_max_rand;
  DIP_SDM_t *SDM_Info; 
  uint m_num_sets;
  uint *PSEL_cntr;
  uint *policy_selection_threshold;
  
	void CreateSDM( unsigned int _sizeOfSDM );
	void SetIndexBitBasedSDM();
	int dip_rand(void);
	void dip_srand(unsigned seed);
	void RandomlyChooseSDM() ;
	void SetDuel_RecordMiss(unsigned int cpuid, unsigned int setnum, bool warmup_mode)const ;
};


	

inline
quickNRUPolicy_DRRIP::quickNRUPolicy_DRRIP(Index num_sets, Index assoc, Vector<Vector<CacheEntryQuick> > *a, uint version)
  : AbstractReplacementPolicyQuick(num_sets, assoc)
{
  m_version = version;
  m_cache = a;
  m_num_sets = num_sets;
  
  dip_rand_seed = 1;
  dip_max_rand = 1048576;	
  
	SDM_Info = new DIP_SDM_t [m_num_sets];
	PSEL_cntr = new uint [8];
	policy_selection_threshold = new uint [8];
            
    for(unsigned int i=0; i<8; i++)
    {
        PSEL_cntr[i]  = 0;
        policy_selection_threshold[i] = 1<<9;
    }

	RandomlyChooseSDM();

}

inline
quickNRUPolicy_DRRIP::~quickNRUPolicy_DRRIP()
{
}


inline void quickNRUPolicy_DRRIP::replacementLower(Index set, Index way)  {

}
 
 
 
inline 
void quickNRUPolicy_DRRIP::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

	CacheEntryQuick &p=(*m_cache)[set][index];
	
	if(time==0) {
		uint que;
		
		if(SDM_Info[set].SDM_Type == DIP_LRU_SDM  
        && SDM_Info[set].SDM_Owner == proc ) {
        	//cerr << "tipo0 proc: " << proc << endl;
        	que=0;	
        } else if(SDM_Info[set].SDM_Type == DIP_BIP_SDM  
        && SDM_Info[set].SDM_Owner == proc ) {
        	//cerr << "tipo1 proc: " << proc << endl;
        	que=1;
        } else {
        	que = (PSEL_cntr[proc] > policy_selection_threshold[proc]) ? 1 : 0;
        }
	
		p.m_RRPV = (que == 0) ? DISTANT_VALUE : DISTANT_VALUE-1;
	} else {
		
  		//p.m_RRPV > 0 ? p.m_RRPV-- : 0;
  		p.m_RRPV = 0;
  	}
	
}

inline
Index quickNRUPolicy_DRRIP::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);
  	
  	SetDuel_RecordMiss(proc, set, 0);
  
	CacheEntryQuick *p;
	bool found = false;
	
	while(!found)
	{
		//buscamos el primero con el RRPV a 2^m-1
		for(uint i = 0; i < m_assoc; i++) {
			p = &(*m_cache)[set][i];
			//cerr << "p->m_RRPV: " << p->m_RRPV << " DISTANT_VALUE: " << DISTANT_VALUE<< endl;	
			if(p->m_RRPV == DISTANT_VALUE) {
				//found = true;
				return i;
			}
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
bool quickNRUPolicy_DRRIP::subSet(CacheEntryQuick *a, uint set) const
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
uint quickNRUPolicy_DRRIP::whatSubSet(CacheEntryQuick &a) const
{
  if(a.m_Sharers.count()==0 && !a.m_reused) return 0;
  if(a.m_Sharers.count()==0 && a.m_reused) return 1;
  if(a.m_Sharers.count()!=0) return 2;

  assert(0);
  return -1;
  
}

inline 
uint quickNRUPolicy_DRRIP::countSegments(uint set, uint what) const
{
	uint aux=0;
	for(uint i=0; i<m_assoc; i++) if(whatSubSet((*m_cache)[set][i]) == what) aux++;
	
	return aux;
	
	uint res[]={0,0,0};
	
	for(uint i=0; i<3; i++) res[whatSubSet((*m_cache)[set][i])]++;
	
	//return res;
  
}

inline
void quickNRUPolicy_DRRIP::printStats(ostream& out, char* name)  
{ int a=0;}

inline
void quickNRUPolicy_DRRIP::printStats(ostream& out)  
{ int a=0;}


// Choose Leader Sets Based on bits 0-5 and 6-10 of the set index
inline void quickNRUPolicy_DRRIP::SetIndexBitBasedSDM()
{
#define MASK 31
#define TOP5(x) ((x>>6)&MASK)
#define BOT5(x) (x&MASK)
#define BIT5(x) ((x>>5)&1)

    for( unsigned int si=0; si<m_num_sets; si++) 
    {
        // Dedicate Per Thread SDMs
        // Can determine if it is my dedicated set or not
        for( unsigned int c=0; c<8; c++ )
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


inline int quickNRUPolicy_DRRIP::dip_rand(void) {
    dip_rand_seed = dip_rand_seed * 1103515245 + 12345;
    return((unsigned)(dip_rand_seed/65536) % 1048576);
}

inline void quickNRUPolicy_DRRIP::dip_srand(unsigned seed) {
    dip_rand_seed = 1;
}

///////////////////////////////////////
///////////////////////////////////////

// Randomly assign sets to SDMs
inline void quickNRUPolicy_DRRIP::RandomlyChooseSDM() 
{
    unsigned int      tot_SDM_Size;        // total SDM size of cache
    unsigned int      tot_SDM_Count;       // Number of SDMs per thread

    tot_SDM_Size  = 32 * 8;
    tot_SDM_Count = 2;

    if( m_num_sets < (tot_SDM_Size * tot_SDM_Count ) ) {
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
        unsigned int ownerSets = 32; //numero de conjuntan que conforman el SDM
            
        for(unsigned int ldr=0; ldr<tot_SDM_Size; ldr++) 
        {
            unsigned int rand_set_indx;
            do 
            {
                rand_set_indx = dip_rand() % m_num_sets;
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
                ownerSets = 32;
            }
        }
    }
}

// Input:  CPU or Thread ID and set number
// Output: none
// Function: update PSEL counter based on misses in competing insertion policy
inline void quickNRUPolicy_DRRIP::SetDuel_RecordMiss(
    unsigned int cpuid,
    unsigned int setnum,
    bool   warmup_mode) const
{
    unsigned int owner   = SDM_Info[setnum].SDM_Owner;
    unsigned int settype = SDM_Info[setnum].SDM_Type;

    // if it is an SDM that does NF policy increment PSEL
    if( settype == DIP_LRU_SDM ) 
    {
        if( PSEL_cntr[owner] < PSELmax ) PSEL_cntr[owner]++;

        // Track number of misses to the dedicated sets
        //SDMmissCountPerThread[owner]++;
    }
    // if it is an SDM that does BF policy decrement PSEL
    else if( settype == DIP_BIP_SDM ) 
    {
        if( PSEL_cntr[owner] > 0 ) PSEL_cntr[owner]--;
            
        // Track number of misses to the dedicated sets
        //SDMmissCountPerThread[owner]++;
    }
}

inline
void quickNRUPolicy_DRRIP::clearStats()  
{

}
#endif // PSEUDONRUBITS_H
