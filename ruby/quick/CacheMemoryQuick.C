#include "CacheMemoryQuick.h"
//#include "CacheEntryQuick.h"
 
#define DEBUG_SET2 1
#define DEBUGED2 991


CacheMemoryQuick::CacheMemoryQuick(int numSetBits, int cacheAssoc, const MachineTypeQuick machType, CacheMgr* a, char* name, int version)
{
   m_version = version;
   m_bigbang=0;
 
  m_cache_num_set_bits = numSetBits;
  m_cache_num_sets = 1 << numSetBits;
  m_cache_assoc = cacheAssoc;
  m_is_instruction_cache = false;

  m_machType = machType;
  m_cache.setSize(m_cache_num_sets);
  
	switch (machType)
  	{
  	
 		case MachineTypeQuick_L0Cache:
 		 	//cerr << "CacheMemoryQuick L0 constructor " << endl;
			if(strcmp(g_REPLACEMENT_POLICY_QUICK_L0, "LRU") == 0)
				m_replacementPolicy_ptr = new quickLRUPolicyL1(m_cache_num_sets, m_cache_assoc, &m_cache);
			else assert(0);
		break;
		
		case MachineTypeQuick_L1Cache:	
			//cerr << "CacheMemoryQuick L1 constructor " << endl;
			if(strcmp(g_REPLACEMENT_POLICY_QUICK_L1, "LRU") == 0)
				m_replacementPolicy_ptr = new quickLRUPolicyL1(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L1, "RND") == 0)
				m_replacementPolicy_ptr = new quickRNDPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L1, "NRU") == 0)
				m_replacementPolicy_ptr = new quickNRUPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L1, "SRRIP") == 0)
				m_replacementPolicy_ptr = new quickNRUPolicy_SRRIP(m_cache_num_sets, m_cache_assoc, &m_cache, version);
			else
				assert(false);
		break;		
		
		case MachineTypeQuick_L15Cache:	
			//cerr << "CacheMemoryQuick L1 constructor " << endl;
			if(strcmp(g_REPLACEMENT_POLICY_QUICK_L15, "LRU") == 0)
				m_replacementPolicy_ptr = new quickLRUPolicyL1(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L15, "LRR") == 0)
				m_replacementPolicy_ptr = new quickLRRPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
			else
				assert(false);
		break;		


		case MachineTypeQuick_L2Cache: 
			//cerr << "CacheMemoryQuick L2 constructor " << endl;
			if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "LRU") == 0)
				m_replacementPolicy_ptr = new quickLRUPolicy(m_cache_num_sets, m_cache_assoc, &m_cache, a);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "LRUb") == 0)
				m_replacementPolicy_ptr = new quickLRUPolicyb(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "LRUc") == 0)
				m_replacementPolicy_ptr = new quickLRUPolicyc(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "LRRd") == 0)
				m_replacementPolicy_ptr = new quickLRRdPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "LRRdt") == 0)
				m_replacementPolicy_ptr = new quickLRRdtPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "RND") == 0)
				m_replacementPolicy_ptr = new quickRNDPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "NRU") == 0)
				m_replacementPolicy_ptr = new quickNRUPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "SRRIP") == 0)
				m_replacementPolicy_ptr = new quickNRUPolicy_SRRIP(m_cache_num_sets, m_cache_assoc, &m_cache, version);
//			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "DRRIP") == 0)
//				m_replacementPolicy_ptr = new quickNRUPolicy_DRRIP(m_cache_num_sets, m_cache_assoc, &m_cache, version);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "SRRIPb") == 0)
				m_replacementPolicy_ptr = new quickNRUPolicy_SRRIPb(m_cache_num_sets, m_cache_assoc, &m_cache, version);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "DRRIPb") == 0)
				m_replacementPolicy_ptr = new quickNRUPolicy_DRRIPb(m_cache_num_sets, m_cache_assoc, &m_cache, version);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "LRRc") == 0)
				m_replacementPolicy_ptr = new quickLRRcPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "NRRa") == 0)
				m_replacementPolicy_ptr = new quickNRRaPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "NRRb") == 0)
				m_replacementPolicy_ptr = new quickNRRbPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "NRUa") == 0)
				m_replacementPolicy_ptr = new quickNRUaPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
			else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "DRRIPc") == 0)
				m_replacementPolicy_ptr = new quickDRRIPcPolicy(m_cache_num_sets, m_cache_assoc, &m_cache, version);
			else
				assert(false);
		break;
		
		case MachineTypeQuick_PILA_L2_0: 
		case MachineTypeQuick_PILA_L2_2: 
		case MachineTypeQuick_PILA1:
		
			//cerr << "CacheMemoryQuick L2 constructor " << endl;
				m_replacementPolicy_ptr = new quickLRUPolicyPILA(m_cache_num_sets, m_cache_assoc, &m_cache);
		break;

		case MachineTypeQuick_PILA0: 
		case MachineTypeQuick_PILA_L2_1: 
		 
			//cerr << "CacheMemoryQuick L2 constructor " << endl;
				m_replacementPolicy_ptr = new quickLRUPolicyPILAF(m_cache_num_sets, m_cache_assoc, &m_cache, true);
		break;
		
		case MachineTypeQuick_PILA2: 
				m_replacementPolicy_ptr = new quickLRUPolicyPILAF2(m_cache_num_sets, m_cache_assoc, &m_cache);
		break;
		
		case MachineTypeQuick_PILA4: 
				m_replacementPolicy_ptr = new quickLRUPolicyPILAF(m_cache_num_sets, m_cache_assoc, &m_cache, false);
		break;
		case MachineTypeQuick_PILA_L1: 
			//cerr << "CacheMemoryQuick L2 constructor " << endl;
				m_replacementPolicy_ptr = new quickLRUPolicyPILA_L1(m_cache_num_sets, m_cache_assoc, &m_cache);
		break;

		case MachineTypeQuick_Shadow: 
		case MachineTypeQuick_Shadow_L2: 
			//cerr << "CacheMemoryQuick L2 constructor " << endl;
				m_replacementPolicy_ptr = new quickLRUshadowPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
		break;

		
		default:
			assert(0);
	}

//	else if(strcmp(g_REPLACEMENT_POLICY_QUICK_L2, "NRU_kibRS") == 0)
//		m_replacementPolicy_ptr = new quickNRUPolicy_kibRS(m_cache_num_sets, m_cache_assoc, &m_cache);

    
  for (int i = 0; i < m_cache_num_sets; i++) {
    m_cache[i].setSize(m_cache_assoc);
    for (int j = 0; j < m_cache_assoc; j++) {
      m_cache[i][j].m_Address.setAddress(0);
      m_cache[i][j].m_Permission = AccessPermission_NotPresent;
    }
  }
  
 

  //  cout << "Before setting trans address list size" << endl;
  //create a trans address for each SMT thread
//   m_trans_address_list.setSize(numThreads);
//   for(int i=0; i < numThreads; ++i){
//     cout << "Setting list size for list " << i << endl;
//     m_trans_address_list[i].setSize(30);
//   }
  //cout << "CacheMemoryQuick constructor finished" << endl;
  
  if(version==0)
  {
     timeLoadArray= new uint64[50000];
     timeLastArray= new uint64[50000];
     timeReplArray= new uint64[50000];
     
     timeLoadArrayCore= new uint64*[RubyConfig::numberOfL1CachePerChip(0)];
     timeLastArrayCore= new uint64*[RubyConfig::numberOfL1CachePerChip(0)];
     timeReplArrayCore= new uint64*[RubyConfig::numberOfL1CachePerChip(0)];
     
    for(uint i =0; i< RubyConfig::numberOfL1CachePerChip(0); i++)
    {
    	timeLoadArrayCore[i]= new uint64[50000];
		timeLastArrayCore[i]= new uint64[50000];
		timeReplArrayCore[i]= new uint64[50000];
		
		
		for(uint j =0; j< 50000; j++)
		{
			timeLoadArrayCore[i][j]=0;
			timeLastArrayCore[i][j]=0;
			timeReplArrayCore[i][j]=0;
		}
		
    }

    for(uint i =0; i< 50000; i++)
    {
      timeLoadArray[i]=0;
      timeLastArray[i]=0;
      timeReplArray[i]=0;
    }
  }
  
  m_histoSets.setSize(m_cache_num_sets);
  m_nLast.setSize(m_cache_num_sets);
  //m_shadowSet =  new PerfectCacheMemory<shadowEntry> (m_chip_ptr);
  m_nmisses.setSize(m_cache_num_sets);
  m_nmissesGlobal = 0;
  m_nLastGlobal = 0;
  for (int i = 0; i < m_cache_num_sets; i++) {
  	m_nmisses[i] = 0;
  	m_nLast[i] = 0;
  }
  
  	//Contadores estadisticas
	m_nA.setSize(RubyConfig::numberOfProcsPerChip());
	m_nM.setSize(RubyConfig::numberOfProcsPerChip()); 
	m_nAP.setSize(RubyConfig::numberOfProcsPerChip());
	m_nMP.setSize(RubyConfig::numberOfProcsPerChip()); 
	for (int i = 0; i < 3; i++) m_nH[i].setSize(RubyConfig::numberOfProcsPerChip());
	
  for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
  	for (int j = 0; j < 3; j++) m_nH[j][i]= 0;
  	m_nA[i] = 0;
  	m_nM[i] = 0;
  	m_nAP[i] = 0;
  	m_nMP[i] = 0;
  }
  
  m_cacheMgr = a;
  int i=-1;
  do { i++; m_name[i]= name[i];  } while(name[i]!='\0');
  
  m_replacementPolicy_ptr->putCache(this);
  
  m_histoReuse = new Histogram(1, 500);
  for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) m_histoReuseThread[i] = new Histogram(1, 500);
  
  if(m_version != -1) {
  	if (m_machType == MachineTypeQuick_L2Cache) m_shadow = new CacheMemoryQuick(numSetBits, 64, MachineTypeQuick_Shadow_L2, a, name, -1);
  }
  
  
}

// ****************************************************************


 
CacheMemoryQuick::~CacheMemoryQuick()
{
  cerr << "CacheMemoryQuick destructor " << m_version<< endl;


  if(m_replacementPolicy_ptr != NULL)
    delete m_replacementPolicy_ptr;
}

 
void CacheMemoryQuick::printConfig(ostream& out)
{
  out << "Cache config: " << m_description << endl;
  out << "  cache_associativity: " << m_cache_assoc << endl;
  out << "  num_cache_sets_bits: " << m_cache_num_set_bits << endl;
  const int cache_num_sets = 1 << m_cache_num_set_bits;
  out << "  num_cache_sets: " << cache_num_sets << endl;
  out << "  cache_set_size_bytes: " << cache_num_sets * RubyConfig::dataBlockBytes() << endl;
  out << "  cache_set_size_Kbytes: " 
      << double(cache_num_sets * RubyConfig::dataBlockBytes()) / (1<<10) << endl;
  out << "  cache_set_size_Mbytes: " 
      << double(cache_num_sets * RubyConfig::dataBlockBytes()) / (1<<20) << endl;
  out << "  cache_size_bytes: " 
      << cache_num_sets * RubyConfig::dataBlockBytes() * m_cache_assoc << endl;
  out << "  cache_size_Kbytes: " 
      << double(cache_num_sets * RubyConfig::dataBlockBytes() * m_cache_assoc) / (1<<10) << endl;
  out << "  cache_size_Mbytes: " 
      << double(cache_num_sets * RubyConfig::dataBlockBytes() * m_cache_assoc) / (1<<20) << endl;
}

// PRIVATE METHODS

// convert a Address to its location in the cache
 
Index CacheMemoryQuick::addressToCacheSet(const Address& address) const
{ 
  assert(address == line_address(address));
  Index temp = -1;

  switch (m_machType) {
    case MachineTypeQuick_L0Cache:
    temp = map_address_to_L1CacheSet(address, m_cache_num_set_bits);
    break;

  case MachineTypeQuick_L1Cache:
  case MachineTypeQuick_L15Cache:
  case MachineTypeQuick_PILA_L1:
  case MachineTypeQuick_PILA_L2_0:
  case MachineTypeQuick_PILA_L2_1:
  case MachineTypeQuick_PILA_L2_2:
    temp = map_address_to_L1CacheSet(address, m_cache_num_set_bits);
    break;
  case MachineTypeQuick_L2Cache:
  case MachineTypeQuick_PILA0:
  case MachineTypeQuick_PILA1:
  case MachineTypeQuick_PILA2:
  case MachineTypeQuick_PILA4:
  case MachineTypeQuick_Shadow:
  case MachineTypeQuick_Shadow_L2:
    temp = map_address_to_L2CacheSet(address, m_cache_num_set_bits);
    break;
  
 // case MachineTypeQuick_VCACHE_ENUM:
  //  temp = map_address_to_L2CacheSet(address, m_cache_num_set_bits);
   // break;
  default:
    ERROR_MSG("Don't recognize m_machType");
  }

  assert(temp < m_cache_num_sets);
  assert(temp >= 0);
  return temp;
}

// Given a cache index: returns the index of the tag in a set.
// returns -1 if the tag is not found.
 
int CacheMemoryQuick::findTagInSet(Index cacheSet, const Address& tag) const
{
  assert(tag == line_address(tag));
  // search the set for the tags
  for (int i=0; i < m_cache_assoc; i++) {
    if ((m_cache[cacheSet][i].m_Address == tag) && 
        (m_cache[cacheSet][i].m_Permission != AccessPermission_NotPresent)) {
      return i;
    }
  }
  return -1; // Not found
}



//JORGE
// PUBLIC METHODS
 
int CacheMemoryQuick::getWay(const Address& address)
{
  assert(address == line_address(address));
  //DEBUG_EXPR(CACHE_COMP, HighPrio, address);
  Index cacheSet = addressToCacheSet(address);
  
  int loc = findTagInSet(cacheSet, address);
  
  assert(loc!=-1);
  return loc;
}

// ignoramos los permisos del bloque
 
int CacheMemoryQuick::foundTagInSet(Index cacheSet, const Address& tag) const
{
  assert(tag == line_address(tag));
  // search the set for the tags
  for (int i=0; i < m_cache_assoc; i++) {
    if (m_cache[cacheSet][i].m_Last_Address == tag) {
      return i;
    }
  }
  //cout << "ay" << endl;
  return -1; // Not found
}


// Given a cache index: returns the index of the tag in a set.
// returns -1 if the tag is not found.
 
int CacheMemoryQuick::findTagInSetIgnorePermissions(Index cacheSet, const Address& tag) const
{
  assert(tag == line_address(tag));
  // search the set for the tags
  for (int i=0; i < m_cache_assoc; i++) {
    if (m_cache[cacheSet][i].m_Address == tag)  
      return i;
  }
  return -1; // Not found
}

// PUBLIC METHODS
 
 
void CacheMemoryQuick::statsPartialTags(const Address& address, int loc) {
	const uint rndBits []= {0,1,2,7,12,15,16,18,23,30};
	const uint tamBits = 10;
	//Address aux = Address(address.getAddress() >> (L2_CACHE_NUM_SETS_BITS + g_NUM_L2_BANKS_BITS + g_DATA_BLOCK_BITS)) ;
	
	uint offset = L2_CACHE_NUM_SETS_BITS + g_NUM_L2_BANKS_BITS + g_DATA_BLOCK_BITS;
	
	for(uint i=0; i<m_cache_assoc; i++) {
		m_cache[loc][i].m_looked = false;
	}
	for(uint i=0; i<tamBits; i++) {
		uint k = 0;
		physical_address_t b = address.bitSelect(rndBits[i] + offset, rndBits[i] + offset);
		for(uint j=0; j<m_cache_assoc; j++) {
			if(!m_cache[loc][j].m_looked)
				if(m_cache[loc][j].m_Address.bitSelect(rndBits[i] + offset, rndBits[i] + offset) == b) {
					k++;
					m_cache[loc][j].m_looked = true;
				}
		}
		histoRemoved[i].add(k);
	}
}


int CacheMemoryQuick::tryCacheAccess(const Address& address, 
                                           CacheRequestTypeQuick type, uint proc)
{
  assert(address == line_address(address));
  //DEBUG_EXPR(CACHE_COMP, HighPrio, address);
  Index cacheSet = addressToCacheSet(address);
  int loc = findTagInSet(cacheSet, address);

  //stats
  if(type == CacheRequestTypeQuick_LD)
  	(m_machType==MachineTypeQuick_L2Cache) ? m_nA[proc]++ : m_nA[proc & (g_NUM_SMT_THREADS-1)]++;  
  else
  	(m_machType==MachineTypeQuick_L2Cache) ? m_nAP[proc]++ : m_nAP[proc & (g_NUM_SMT_THREADS-1)]++;  
  
  int insideAssoc = 0;
  
  if(loc != -1) { // Do we even have a tag match?
  
  
  	insideAssoc = 1;
  	//if (m_machType==MachineTypeQuick_L2Cache)statsPartialTags(address, loc);
  	
  	CacheEntryQuick& entry = m_cache[cacheSet][loc];
  	
	//stats  
	if(type == CacheRequestTypeQuick_LD) {
		if(m_machType==MachineTypeQuick_L2Cache && g_REPLACEMENT_POLICY_QUICK_L2_3SET) 
		{
			m_nH[m_replacementPolicy_ptr->whatSubSet(&entry)][proc]++;
		}
		
		if(g_REUSED_PAGE && m_machType==MachineTypeQuick_L2Cache) {
			
			if(!entry.m_prefetch) {
				//Address aux(address);
				//aux.onlyPageAddress();
				
				//Ojo, se actualiza la tabla en CADA acierto
				m_table.hit(address, proc);
			
				if(!entry.m_reused) {
					entry.m_reused = true;
					m_replacementPolicy_ptr->m_nReused[cacheSet]++;
				}
			} else entry.m_prefetch = false;
						
		} else {
		
			if(!entry.m_reused) {
				//cerr << "no reusado" << endl;
				if(!entry.m_prefetch) {
					entry.m_reused = true;
					m_replacementPolicy_ptr->m_nReused[cacheSet]++;
				} else entry.m_prefetch = false;
			}
			else {  entry.m_reused2 = true; }
		}
		
		m_replacementPolicy_ptr->overAssoc = -1;
		
		m_replacementPolicy_ptr->touch(cacheSet, loc, g_eventQueue_ptr->getTime(), proc);		
		
		if(m_machType == MachineTypeQuick_L2Cache) {
			m_overAssocAddress = Address(0);
			if(m_replacementPolicy_ptr->overAssoc != -1) {
				m_overAssocAddress= m_replacementPolicy_ptr->overAssocAddress;		
				
				//cerr << "establecemos dirección: " << m_overAssocAddress << endl;
				m_replacementPolicy_ptr->overAssoc = -1;
			}
			m_cache[cacheSet][loc].m_uses++;
		}
	} 
 	
 	if (m_machType == MachineTypeQuick_L2Cache) insideAssoc = m_replacementPolicy_ptr->insideAsoc;
 	
  	if(insideAssoc == 2) return 2;
  	else return (m_cache[cacheSet][loc].m_Permission != AccessPermission_NotPresent) && (insideAssoc == 1);
  	
    // The line must not be accessible
  }
  if(type == CacheRequestTypeQuick_LD) (m_machType==MachineTypeQuick_L2Cache) ? (m_nM[proc]++) : (m_nM[proc & (g_NUM_SMT_THREADS-1)]++);  
  else (m_machType==MachineTypeQuick_L2Cache) ? (m_nMP[proc]++) : (m_nMP[proc & (g_NUM_SMT_THREADS-1)]++); 
  
 // assert((proc & (g_NUM_SMT_THREADS-1)) == (proc%g_NUM_SMT_THREADS));
  return 0;
}

 
bool CacheMemoryQuick::testCacheAccess(const Address& address, 
                                           CacheRequestTypeQuick type)
{
  assert(address == line_address(address));
  //DEBUG_EXPR(CACHE_COMP, HighPrio, address);
  Index cacheSet = addressToCacheSet(address);
  int loc = findTagInSet(cacheSet, address);
  if(loc != -1){ // Do we even have a tag match?
    CacheEntryQuick& entry = m_cache[cacheSet][loc];

    return (m_cache[cacheSet][loc].m_Permission != AccessPermission_NotPresent);
  }
  return false;
}

// tests to see if an address is present in the cache
 
bool CacheMemoryQuick::isTagPresent(const Address& address) const
{
  assert(address == line_address(address));
  Index cacheSet = addressToCacheSet(address);
  int location = findTagInSet(cacheSet, address);

  if (location == -1) {
    // We didn't find the tag
    //DEBUG_EXPR(CACHE_COMP, LowPrio, address);
    DEBUG_MSG(CACHE_COMP, LowPrio, "No tag match");
    return false;
  } 
  //DEBUG_EXPR(CACHE_COMP, LowPrio, address);
  DEBUG_MSG(CACHE_COMP, LowPrio, "found");
  return true;
}


//JORGE
 
bool CacheMemoryQuick::wasTagPresent(const Address& address) const
{
  assert(address == line_address(address));
  Index cacheSet = addressToCacheSet(address);
  int location = foundTagInSet(cacheSet, address);

  if (location == -1) {
    // We didn't find the tag
    //DEBUG_EXPR(CACHE_COMP, LowPrio, address);
    DEBUG_MSG(CACHE_COMP, LowPrio, "No tag match");
    return false;
  } 
  //DEBUG_EXPR(CACHE_COMP, LowPrio, address);
  DEBUG_MSG(CACHE_COMP, LowPrio, "found");
  return true;
}



// Returns true if there is:
//   a) a tag match on this address or there is 
//   b) an unused line in the same cache "way"
 
bool CacheMemoryQuick::cacheAvail(const Address& address) 
{
  assert(address == line_address(address));

  Index cacheSet = addressToCacheSet(address);

  for (int i=0; i < m_cache_assoc; i++) {
    if (m_cache[cacheSet][i].m_Address == address) {
      // Already in the cache
      
      return true;
    }      

    if (m_cache[cacheSet][i].m_Permission == AccessPermission_NotPresent) {
      // We found an empty entry
      return true;
    }
  }
  return false;
}

 
void CacheMemoryQuick::allocate(const Address& address, const uint proc) 
{
  assert(address == line_address(address));
  assert(!isTagPresent(address));
  assert(cacheAvail(address));
  //DEBUG_EXPR(CACHE_COMP, HighPrio, address);

assert(m_machType != MachineTypeQuick_L2Cache);
  // Find the first open slot
  Index cacheSet = addressToCacheSet(address);
  for (int i=0; i < m_cache_assoc; i++) {
    if (m_cache[cacheSet][i].m_Permission == AccessPermission_NotPresent) {
      //Address a=m_cache[cacheSet][i].m_Last_Address;
	  //CacheEntryQuick a = CacheEntryQuick(m_cache[cacheSet][i]);
      //m_cache[cacheSet][i] = CacheEntryQuick();  // Init entry
      //m_cache[cacheSet][i].m_prefDWG= a.m_prefDWG;
      //m_cache[cacheSet][i].m_prefTypeRepl= a.m_prefTypeRepl;
	  //m_cache[cacheSet][i].m_Last_Address=a.m_Address;
      m_cache[cacheSet][i].m_Address = address;
      m_cache[cacheSet][i].m_Permission = AccessPermission_Read_Write;
      m_cache[cacheSet][i].m_reused = false;
      
      m_cache[cacheSet][i].m_reused2 = false;
      m_cache[cacheSet][i].m_Sharers.reset();
      m_cache[cacheSet][i].m_uses = 0;
      m_cache[cacheSet][i].m_owner = proc;
      m_cache[cacheSet][i].m_isFirst = true;
      
      /*Time aux=0;
		if(0 && m_machType==MachineTypeQuick_L15Cache && g_SHADOW && m_version != -1) {
			//if(m_shadow->isTagPresent( address)) {
			if(m_shadow->tryCacheAccess(address, CacheRequestTypeQuick_LD, proc)) {
				m_shadow->deallocate(address);
				aux=1;
				m_cache[cacheSet][i].m_shadowed = true;
			}
		}
	*/
	
      m_replacementPolicy_ptr->touch(cacheSet, i, 0, proc);


      return;
    }
  }
  ERROR_MSG("Allocate didn't find an available entry");
}

 
void CacheMemoryQuick::allocateL2(const Address& address, const uint proc) 
{
  assert(address == line_address(address));
  assert(!isTagPresent(address));
  assert(cacheAvail(address));
  //DEBUG_EXPR(CACHE_COMP, HighPrio, address);

  // Find the first open slot
  Index cacheSet = addressToCacheSet(address);
  for (int i=0; i < m_cache_assoc; i++) {
    if (m_cache[cacheSet][i].m_Permission == AccessPermission_NotPresent) {
      m_cache[cacheSet][i].m_Address = address;
      m_cache[cacheSet][i].m_Permission = AccessPermission_Read_Write;
      m_cache[cacheSet][i].m_reused = false;
      
      if(g_REUSED_PAGE)  { 
      	//Address aux(address);
		//aux.onlyPageAddress();
      	m_cache[cacheSet][i].m_reused = m_table.whatToDo(address, proc);
      }
      
      m_cache[cacheSet][i].m_reused2 = false;
      m_cache[cacheSet][i].m_Sharers.reset();
      m_cache[cacheSet][i].m_uses = 0;
      m_cache[cacheSet][i].m_owner = proc;
       m_cache[cacheSet][i].m_NRU = false;
      
      Time aux=0;
		if(g_SHADOW && m_version != -1) {
			//if(m_shadow->isTagPresent( address)) {
			if(m_shadow->tryCacheAccess(address, CacheRequestTypeQuick_LD, proc)) {
				m_shadow->deallocate(address);
				if(g_FUNCTIONAL_SHADOW) {
					aux=1;
					m_cache[cacheSet][i].m_NRU = true;
				}
			}
		}
		
	m_replacementPolicy_ptr->overAssoc = -1;

	m_replacementPolicy_ptr->touch(cacheSet, i, aux, proc);

	m_overAssocAddress = Address(0);
	if(m_replacementPolicy_ptr->overAssoc != -1) {
		m_overAssocAddress= m_replacementPolicy_ptr->overAssocAddress;	
		m_replacementPolicy_ptr->overAssoc = -1;
	}
	
      return;
    }
  }
  ERROR_MSG("Allocate didn't find an available entry");
}
 
void CacheMemoryQuick::deallocate(const Address& address)
{
  assert(address == line_address(address));
  assert(isTagPresent(address));
  //DEBUG_EXPR(CACHE_COMP, HighPrio, address);

	CacheEntryQuick a = lookup(address);
	(m_machType==MachineTypeQuick_L2Cache) ? \
		m_histoReuseThread[a.m_owner]->add(a.m_uses) : m_histoReuseThread[a.m_owner & (g_NUM_SMT_THREADS-1)]->add(a.m_uses);  
	m_histoReuse->add(a.m_uses);
	
  lookup(address).m_Last_Address= address;
  
  // This is the only important thing in this function
  ///************
  lookup(address).m_Permission = AccessPermission_NotPresent;
  //************* 
  
  
	if((m_machType==MachineTypeQuick_L2Cache) && g_SHADOW && m_version != -1) {
		if(!m_shadow->cacheAvail(address)) {
			Address auxAd = m_shadow->cacheProbe(address);
			m_shadow->deallocate(auxAd);
		}
		m_shadow->allocateL2(address, 0);
		m_shadow->lookup(address).m_NRU = a.m_NRU;
		
	}


}

// Returns with the physical address of the conflicting cache line
// *Only called when replacing a cache line [in the protocol .sm]
 
Address CacheMemoryQuick::cacheProbe(const Address& address, uint proc) const
{
  assert(address == line_address(address));
 // assert(!cacheAvail(address));

  Index cacheSet = addressToCacheSet(address);

	//m_replacementPolicy_ptr->m_wayOut = findTagInSet(cacheSet, address);
	
	CacheEntryQuick aux;
  
/*	if( g_REUSED_PAGE && m_machType==MachineTypeQuick_L2Cache) {
  	
		Address auxP;
		uint saltados=-1;
		do {
			saltados++;
			aux =  m_cache[cacheSet][m_replacementPolicy_ptr->getVictim(cacheSet, proc)];
			auxP = Address(aux.m_Address);
			auxP.makePageAddress();
			
		} while(m_table.whatToDo(auxP)!=0 && saltados!=m_cache_assoc);
		
		
  	
	} else {
	*/
  	
  	aux =  m_cache[cacheSet][m_replacementPolicy_ptr->getVictim(cacheSet, proc)];
	
	//}
  
    if(aux.m_reused) m_replacementPolicy_ptr->m_nReused[cacheSet]--;
    
    if(g_REUSED_PAGE && m_machType==MachineTypeQuick_L2Cache) {
    	//Address auxRepl(aux);
		//auxRepl.onlyPageAddress();
    	m_table.replaced(address, proc);
	}
	
  return aux.m_Address;  
  //if(LRU_STACK) return m_cache[cacheSet][m_replacementPolicy_ptr->getVictim(cacheSet, address)].m_Address;
}



// looks an address up in the cache
 
CacheEntryQuick& CacheMemoryQuick::lookup(const Address& address)
{

  assert(address == line_address(address));
  Index cacheSet = addressToCacheSet(address);
  int loc = findTagInSet(cacheSet, address);
  assert(loc != -1);
  return m_cache[cacheSet][loc];
}

// looks an address up in the cache
 
const CacheEntryQuick& CacheMemoryQuick::lookup(const Address& address) const
{
  assert(address == line_address(address));
  Index cacheSet = addressToCacheSet(address);
  int loc = findTagInSet(cacheSet, address);
  assert(loc != -1);
  return m_cache[cacheSet][loc];
}

CacheEntryQuick& CacheMemoryQuick::lookup(const int set, const int pos) {
	return m_cache[set][pos];
}

//JORGE



 
CacheEntryQuick& CacheMemoryQuick::lookupPast(const Address& address)
{
  assert(address == line_address(address));
  Index cacheSet = addressToCacheSet(address);
  int loc = foundTagInSet(cacheSet, address);
  assert(loc != -1);
  return m_cache[cacheSet][loc];
}

 
const CacheEntryQuick& CacheMemoryQuick::lookupPast(const Address& address) const
{
  assert(address == line_address(address));
  Index cacheSet = addressToCacheSet(address);
  int loc = foundTagInSet(cacheSet, address);
  assert(loc != -1);
  return m_cache[cacheSet][loc];
}




AccessPermission CacheMemoryQuick::getPermission(const Address& address) const
{
  //cout << "get Perm" << endl;

  assert(address == line_address(address));
  return lookup(address).m_Permission;
}

 
void CacheMemoryQuick::changePermission(const Address& address, AccessPermission new_perm)
{
 // cout << "change Perm" << endl;

  assert(address == line_address(address));
  lookup(address).m_Permission = new_perm;
  assert(getPermission(address) == new_perm);
}

// Sets the most recently used bit for a cache block
 
void CacheMemoryQuick::setMRU(const Address& address)
{
assert(address == line_address(address));
  Index cacheSet;

  cacheSet = addressToCacheSet(address);
  m_replacementPolicy_ptr->touch(cacheSet, 
                                 findTagInSet(cacheSet, address), 
                                 g_eventQueue_ptr->getTime(), 0);


}

 
void CacheMemoryQuick::replacementLower(Address a) const
{
assert(a == line_address(a));
  Index cacheSet;

  cacheSet = addressToCacheSet(a);
  m_replacementPolicy_ptr->replacementLower(cacheSet, 
                                 findTagInSet(cacheSet, a));
}
 
void CacheMemoryQuick::recordCacheContents(CacheRecorder& tr) const
{
int a = 0;
}

void CacheMemoryQuick::invalidateAddress(const Address& a) {
	assert(testCacheAccess(a, CacheRequestTypeQuick_LD));
	changePermission(a, AccessPermission_NotPresent);
}
 
void CacheMemoryQuick::print(ostream& out) const
{ 
  out << "Cache dump: " << m_description << endl;
  for (int i = 0; i < m_cache_num_sets; i++) {
    for (int j = 0; j < m_cache_assoc; j++) {
      out << "  Index: " << i 
          << " way: " << j 
          << " entry: " << m_cache[i][j] << endl;
    }
  }
}

 
void CacheMemoryQuick::printData(ostream& out) const
{ 
  out << "printData() not supported" << endl;
}

 
void CacheMemoryQuick::printTempCommand()
{ 
  assert(m_version==0);
  
  uint64 *tLoad=new uint64[50000];
  uint64 *tLast=new uint64[50000];    
     
   uint64**  tLoadCore= new uint64*[RubyConfig::numberOfL1CachePerChip(0)];
   uint64**   tLastCore= new uint64*[RubyConfig::numberOfL1CachePerChip(0)];

    for(uint i =0; i< RubyConfig::numberOfL1CachePerChip(0); i++)
    {
    	tLoadCore[i]= new uint64[50000];
		tLastCore[i]= new uint64[50000];
    }
 
  cerr << "PRINT_TEMP" << endl;
 // for(int i=0; i<10000; i++) cerr << timeLoadArray[i] << "\t" << timeLastArray[i]  << "\t" <<timeReplArray[i] << endl;
  
  tLoad[0]= timeLoadArray[0] - timeLastArray[0];
  tLast[0]= timeLastArray[0] - timeReplArray[0];
  
  for(uint i =0; i< RubyConfig::numberOfL1CachePerChip(0); i++)
  {
  	tLoadCore[i][0]= timeLoadArrayCore[i][0] - timeLastArrayCore[i][0];
  	tLastCore[i][0]= timeLastArrayCore[i][0] - timeReplArrayCore[i][0];
  }
  
  for(int i=1; i<50000; i++)
  {
    tLoad[i]= timeLoadArray[i] + tLoad[i-1] - timeLastArray[i];
    tLast[i]= timeLastArray[i] + tLast[i-1] - timeReplArray[i];
    
	  for(uint j =0; j< RubyConfig::numberOfL1CachePerChip(0); j++)
	  {
		tLoadCore[j][i]= timeLoadArrayCore[j][i] + tLoadCore[j][i-1] - timeLastArrayCore[j][i];
		tLastCore[j][i]= timeLastArrayCore[j][i] + tLastCore[j][i-1] - timeReplArrayCore[j][i];
		
		cerr << tLoadCore[j][i] << "\t" << tLastCore[j][i]  << "\t" ;
	  }
    
    cerr << tLoad[i] << "\t" << tLast[i]  << "\t" << (float)tLoad[i] / (float)tLast[i] << endl;
  }
  
    cerr << "posicion: " << endl;
  	cerr << m_replacementPolicy_ptr->m_histoSpace[0];

}

 
void CacheMemoryQuick::printReuseCommand()
{   
   	

}

 
void CacheMemoryQuick::printTemp(const Address& address)
{ 
  
/*  if(m_version==0 && !g_CARGA_CACHE  )
  {    
  
  //if(map_L1CacheMachId_to_L2Cache(address,getL1MachineID(0))==mach)
      Index cacheSet = addressToCacheSet(address);
      int loc = findTagInSet(cacheSet, address);

     assert(loc!=-1);

    int core= m_cache[cacheSet][loc].m_owner.num;
   
   
   if(g_LIFETRACE)
   {
    uint idx= (m_cache[cacheSet][loc].m_timeLoad - m_bigbang) / 10000;
    assert(idx<50000);   
    timeLoadArray[idx] ++;
    timeLoadArrayCore[core][idx] ++;
    
    
    idx= (m_cache[cacheSet][loc].m_timeLast - m_bigbang) / 10000;
    assert(idx<50000);
    timeLastArray[idx] ++;
    timeLastArrayCore[core][idx] ++;
    
    idx= (g_eventQueue_ptr->getTime() - m_bigbang) / 10000;
    assert(idx<50000);
    timeReplArray[idx] ++;
    timeReplArrayCore[core][idx] ++;
   }
     
    int reusoL1 = m_cache[cacheSet][loc].m_reuseL1;
    if( (reusoL1==1 || reusoL1==3 ) && g_NO_REUSE_LRU) {
    	m_replacementPolicy_ptr->touch(cacheSet, loc, -1);
    }
    
    if(!m_cache[cacheSet][loc].m_reused) {
    	reuseArrayCore[core][reusoL1]++;
    }
	else {
		reuseArrayCore[core][reusoL1+4]++;
	}
	
	//m_shadowSet->allocate(address);
	//m_shadowSet->lookup(address).m_nmisses= m_nmisses[cacheSet];
	
	m_lastRev++;
	
	Vector<Address> keys= m_shadowSet->keys();
	if(m_lastRev >= 10000) {
		m_lastRev=0;
		//cerr << "recuento..." << keys.size() <<  endl;
  		for (uint i=0; i < keys.size(); i++) {
  			uint set= addressToCacheSet(keys[i]);
  			uint misses= m_nmisses[set] - m_shadowSet->lookup(keys[i]).m_nmisses;
  			
  			
  			if(misses >= 1000) {
  				cerr << "...Habemus..." <<  endl;
  				//m_histoSets[set].add(misses);
  				m_nLast[set]++; 
  				m_nLastGlobal++;
  				m_shadowSet->deallocate(keys[i]);
  			}
  		}  		 
 	}
	//cerr << "meto el bloque " << address << " con " << m_nmisses[cacheSet] << " fallos " << m_shadowSet->lookup(address).m_nmisses << endl;
	
  }  //m_version && CARGA_CACHE		

//  cerr << m_cache[cacheSet][loc].m_timeLoad << "\t" << m_cache[cacheSet][loc].m_timeLast 
//  << "\t" << m_cache[cacheSet][loc].m_timeRepl << endl;
*/

int a=0;
}



 
void CacheMemoryQuick::resetTemp()
{ 
  uint64 n_bloques=0;
  Time aux= g_eventQueue_ptr->getTime();
  m_bigbang= aux;
  assert(m_version==0);
    for (int i = 0; i < m_cache_num_sets; i++) {
      for (int j = 0; j < m_cache_assoc; j++) {
        m_cache[i][j].m_timeLoad= aux;
        m_cache[i][j].m_timeLast= aux;
        
        n_bloques++;
    }
  }
  cerr << "finished reseting (" << n_bloques << " blocks)" << endl;
}

 
void CacheMemoryQuick::resetReuse()
{ 
  	cerr << "finished reseting reuse" << endl;
}

// PUBLIC METHODS
 
void CacheMemoryQuick::setTimeLast(const Address& address)
{
if(m_version==0 && !g_CARGA_CACHE)
{
  assert(address == line_address(address));
  //DEBUG_EXPR(CACHE_COMP, HighPrio, address);
  Index cacheSet = addressToCacheSet(address);
  int loc = findTagInSet(cacheSet, address);
  assert(loc!=-1);
  
  m_cache[cacheSet][loc].m_timeLast = g_eventQueue_ptr->getTime();
}
  //cerr << "cacheSet:" << cacheSet << "  loc:" << loc << "t:" << g_eventQueue_ptr->getTime() << endl;
}


void CacheMemoryQuick::getMemoryValue(const Address& addr, char* value,
                                           unsigned int size_in_bytes ){
  //cout << "getmv" << endl;

  CacheEntryQuick entry = lookup(line_address(addr));
  unsigned int startByte = addr.getAddress() - line_address(addr).getAddress();
}


void CacheMemoryQuick::setMemoryValue(const Address& addr, char* value,
                                           unsigned int size_in_bytes ){
          //cout << "setmv" << endl;
                                   
  CacheEntryQuick& entry = lookup(line_address(addr));
  unsigned int startByte = addr.getAddress() - line_address(addr).getAddress();
  assert(size_in_bytes > 0);

  entry = lookup(line_address(addr));
}

void CacheMemoryQuick::printStats(ostream& out) 
{
	uint THREADS_IN_CACHE = (m_machType==MachineTypeQuick_L2Cache) ?  \
	RubyConfig::numberOfProcsPerChip() : g_NUM_SMT_THREADS;
		
	out << "--------------------------------------------------------" << endl;
	uint totalInst=0;
	uint totalAcc=0, totalMiss=0, totalAccP=0, totalMissP=0;
	
	out << "m_version: " << m_version << endl;
	

	for(int i=0; i< THREADS_IN_CACHE && m_version!=-1; i++)
	{
		uint nThreadAux = (m_machType==MachineTypeQuick_L2Cache ? 0 : m_version)*THREADS_IN_CACHE + i;
		
		out << endl << m_name << "_accesses_thread_" << nThreadAux << ":\t" << m_nA[i] << endl;
		out << m_name <<"_misses_thread_" << nThreadAux << ":\t" << m_nM[i] << endl;
		out << m_name <<"_hits_thread_" << nThreadAux << ":\t" << m_nA[i] - m_nM[i] << endl;
		out << m_name <<"_miss_rate_thread_" << nThreadAux << ":\t" << (float) m_nM[i] / m_nA[i] << endl;
	
		totalAcc += m_nA[i];
		totalMiss += m_nM[i];
		
		out << endl << m_name << "_prefetch_lookups_thread_" << nThreadAux << ":\t" << m_nAP[i] << endl;
		out << m_name <<"_prefetch_misses_thread_" << nThreadAux << ":\t" << m_nMP[i] << endl;
		out << m_name <<"_prefetch_hits_thread_" << nThreadAux << ":\t" << m_nAP[i] - m_nMP[i] << endl;
	
		//totalAcPc += m_nAP[i];
		//totalMissP += m_nMP[i];
		
		uint aux= m_cacheMgr->m_driver->getInstructionCount(nThreadAux);
		totalInst += aux;
		out << m_name <<  "_executed_instructions_thread_" << nThreadAux << ":\t" << aux << endl;
		out << m_name <<  "_MPKI_thread_" << nThreadAux << ":\t" << (float)m_nM[i]/aux*1000 << endl;
		out << m_name << "_reuse_thread_" << nThreadAux << ":\t" <<  *m_histoReuseThread[i] << endl;
		
		if(m_machType==MachineTypeQuick_L2Cache && g_REPLACEMENT_POLICY_QUICK_L2_3SET) {
			for (int j = 0; j < 3; j++)
				out << m_name << "_hit_ratio_segment_"<< j <<"_thread_" << nThreadAux << ":\t" <<  (float) m_nH[j][i]/(m_nA[i]-m_nM[i])  << endl;
		}
	}
	if(m_version!=-1) {
		out << endl << m_name << "_accesses_cache:\t" << totalAcc << endl;
		out << endl << m_name << "_misses_cache:\t" << totalMiss << endl;
		out << endl << m_name << "_miss_rate_cache:\t" << (float) totalMiss / totalAcc << endl;
		out << m_name << "_MPKI_cache:\t" << (float)totalMiss / totalInst*1000 << endl;
	
		out << m_name << "_reuse_cache:\t" <<  *m_histoReuse << endl;
	}
	
	if (m_machType==MachineTypeQuick_L2Cache) {
		for(uint i=0; i<10; i++) out << m_name << "_partialTags:\t" <<  histoRemoved[i] << endl;
	}
	switch(m_machType) {
		case MachineTypeQuick_L2Cache:
		case MachineTypeQuick_PILA0:
		case MachineTypeQuick_PILA1:
		case MachineTypeQuick_PILA2:
		case MachineTypeQuick_PILA4:
		case MachineTypeQuick_PILA_L1:
		case MachineTypeQuick_PILA_L2_0:
		case MachineTypeQuick_PILA_L2_1:
		case MachineTypeQuick_PILA_L2_2:
		case MachineTypeQuick_Shadow:
		case MachineTypeQuick_Shadow_L2:
			out << "POLITIC" << endl;
			 m_replacementPolicy_ptr->printStats(out, (char*) m_name);
		break;
		default:
		break;
	}
	
	if(m_machType==MachineTypeQuick_L2Cache) m_table.printStats(out, (char*) m_name);	

	if(m_machType==MachineTypeQuick_L2Cache && m_version!=-1) {
		m_shadow->printStats(out);
	}
}

void CacheMemoryQuick::clearStats() 
{
cerr << "CacheMemoryQuick::clearStats()" << endl;

  m_nmissesGlobal = 0;
  m_nLastGlobal = 0;
  for (int i = 0; i < m_cache_num_sets; i++) {
  	m_nmisses[i] = 0;
  	m_nLast[i] = 0;
  }  
	
  for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
  	for (int j = 0; j < 3; j++) m_nH[j][i]= 0;
  	m_nA[i] = 0;
  	m_nM[i] = 0;
  	m_nAP[i] = 0;
  	m_nMP[i] = 0;
  }
  
  m_replacementPolicy_ptr->clearStats();
  
  if(m_machType==MachineTypeQuick_L2Cache && m_version!=-1 && g_SHADOW)  m_shadow->clearStats();
}

 
void CacheMemoryQuick::printSet(ostream& out, uint set) 
{ 
    for (int j = 0; j < m_cache_assoc; j++) {
      out <<" way: " << j 
          << " entry: " << m_cache[set][j] << endl;
    }

}

