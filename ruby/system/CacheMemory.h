/*
    Copyright (C) 1999-2008 by Mark D. Hill and David A. Wood for the
    Wisconsin Multifacet Project.  Contact: gems@cs.wisc.edu
    http://www.cs.wisc.edu/gems/

    --------------------------------------------------------------------

    This file is part of the Ruby Multiprocessor Memory System Simulator, 
    a component of the Multifacet GEMS (General Execution-driven 
    Multiprocessor Simulator) software toolset originally developed at 
    the University of Wisconsin-Madison.

    Ruby was originally developed primarily by Milo Martin and Daniel
    Sorin with contributions from Ross Dickson, Carl Mauer, and Manoj
    Plakal.

    Substantial further development of Multifacet GEMS at the
    University of Wisconsin was performed by Alaa Alameldeen, Brad
    Beckmann, Jayaram Bobba, Ross Dickson, Dan Gibson, Pacia Harper,
    Derek Hower, Milo Martin, Michael Marty, Carl Mauer, Michelle Moravan,
    Kevin Moore, Andrew Phelps, Manoj Plakal, Daniel Sorin, Haris Volos, 
    Min Xu, and Luke Yen.
    --------------------------------------------------------------------

    If your use of this software contributes to a published paper, we
    request that you (1) cite our summary paper that appears on our
    website (http://www.cs.wisc.edu/gems/) and (2) e-mail a citation
    for your published paper to gems@cs.wisc.edu.

    If you redistribute derivatives of this software, we request that
    you notify us and either (1) ask people to register with us at our
    website (http://www.cs.wisc.edu/gems/) or (2) collect registration
    information and periodically send it to us.

    --------------------------------------------------------------------

    Multifacet GEMS is free software; you can redistribute it and/or
    modify it under the terms of version 2 of the GNU General Public
    License as published by the Free Software Foundation.

    Multifacet GEMS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the Multifacet GEMS; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307, USA

    The GNU General Public License is contained in the file LICENSE.

### END HEADER ###
*/

/*
 * CacheMemory.h
 * 
 * Description: 
 *
 * $Id: CacheMemory.h,v 3.7 2004/06/18 20:15:15 beckmann Exp $
 *
 */

#ifndef CACHEMEMORY_H
#define CACHEMEMORY_H

#include "AbstractChip.h"
#include "Global.h"
#include "AccessPermission.h"
#include "Address.h"
#include "CacheRecorder.h"
#include "CacheRequestType.h"
#include "Vector.h"
#include "DataBlock.h"
#include "MachineType.h"
#include "RubySlicc_ComponentMapping.h"
#include "RequestMsg.h"
#include "MessageBuffer.h"

#include "PseudoLRUPolicy.h"
#include "PseudoLRUPolicy2.h"

//#include "LRUPolicy.h"
#include "RNDPolicyL1.h"
#include "LRUPolicyL1.h"
#include "LRUPolicyL1_kid.h"
#include "LRUPolicyL2.h"
// #include "LRUPolicyL2_kid.h"
// #include "LRUPolicyL2_kidR.h"
// #include "LRUPolicyL2_qbs.h"
// #include "LRUPolicyL2_use.h"
// #include "LRUPolicyL2_try.h"
// #include "LRUPolicyL2_3set.h"
// #include "LRUPolicyL2_stack.h"

// #include "LRUPolicyL2_kibRP.h"
// #include "LRUPolicyL2_kibRS.h"
// #include "LRUPolicyL2_kibRT.h"

#include "NRUPolicyL2.h"
// #include "NRUPolicyL2_qbs.h"
// #include "NRUPolicyL2_3SETb.h"
// #include "NRUPolicyL2_3SETf.h"
// #include "NRUPolicyL2_3SETg.h"
// #include "NRUPolicyL2_3SETi.h"
// #include "NRUPolicyL2_3SETj.h"
// #include "NRUPolicyL2_3SETk.h"
// #include "NRUPolicyL2_3SETl.h"

#include "LRRcPolicyL2.h"
#include "LRRdPolicyL2.h"
#include "LRRjPolicyL2.h"

//#include "LRRc2PolicyL2.h"
//#include "LRRd2PolicyL2.h"
//#include "LRRePolicyL2.h"
//#include "LRRfPolicyL2.h"

#include "NRRaPolicyL2.h"
#include "NRRjPolicyL2.h"
//#include "NRRbPolicyL2.h"
//#include "NRRdPolicyL2.h"
//#include "NRRePolicyL2.h"


#include "RNDPolicyL2.h"
//#include "RNDPolicyL2_kid.h"
//#include "RNDPolicyL2_kidR.h"
//#include "RNDPolicyL2_3set.h"
//#include "RNDPolicyL2_kidRi.h"

// #include "RNDPolicyL2_kibRP.h"
// #include "RNDPolicyL2_kibRS.h"
// #include "RNDPolicyL2_kibRT.h"

#include "NRUPolicy_SRRIPb.h"
#include "NRUPolicy_DRRIPb.h"
#include "NRUPolicy_SRRIPc.h"
#include "NRUPolicy_DRRIPc.h"
#include "SHiPPolicy.h"

#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"

#include "PerfectCacheMemory.h"

#include "CirBuf.h"

#include <vector>

struct shadowEntry {
	Address m_address;
	uint64 m_nmisses;
};

class AbstractChip;


template<class ENTRY>
class CacheMemory {
public:

  // Constructors
  CacheMemory(AbstractChip* chip_ptr, int numSetBits, int cacheAssoc, const MachineType machType, const string& description, int version, int versionB=0);
// Constructors
  CacheMemory(AbstractChip* chip_ptr, int numSetBits, int cacheAssoc, const MachineType machType, const string& description);

  // Destructor
  ~CacheMemory();
  
  // Public Methods
  void printConfig(ostream& out);

  // perform a cache access and see if we hit or not.  Return true on a hit.
  bool tryCacheAccess(const Address& address, CacheRequestType type, DataBlock*& data_ptr, uint proc);

  // similar to above, but doesn't require full access check
  bool testCacheAccess(const Address& address, CacheRequestType type, DataBlock*& data_ptr);

  // tests to see if an address is present in the cache
  bool isTagPresent(const Address& address) const;

  // Returns true if there is:
  //   a) a tag match on this address or there is 
  //   b) an unused line in the same cache "way"
  bool cacheAvail(const Address& address) const;

  // find an unused entry and sets the tag appropriate for the address
  void allocate(const Address& address);

  // find an unused entry and sets the tag appropriate for the address
  void allocateL2(const Address& address);


  // Explicitly free up this address
  void deallocate(const Address& address);

  // Returns with the physical address of the conflicting cache line
  Address cacheProbe(const Address& address, const MachineID proc) const;
  Address cacheProbe(const Address& address, const int proc) const;

  // looks an address up in the cache
  ENTRY& lookup(const Address& address);
  const ENTRY& lookup(const Address& address) const;

  int insertionDataArray(const Address& address);
  void evictDataArray(const Address& address);

  // Get/Set permission of cache block
  AccessPermission getPermission(const Address& address) const;
  void changePermission(const Address& address, AccessPermission new_perm);

  // Hook for checkpointing the contents of the cache
  void recordCacheContents(CacheRecorder& tr) const;
  void setAsInstructionCache(bool is_icache) { m_is_instruction_cache = is_icache; }

  // Set this address to most recently used
  void setMRU(const Address& address, const NodeID proc);

  void getMemoryValue(const Address& addr, char* value,
                      unsigned int size_in_bytes );
  void setMemoryValue(const Address& addr, char* value,
                      unsigned int size_in_bytes );

  // Print cache contents
  void print(ostream& out) const;
  void printData(ostream& out) const;

  //JORGE
  void printTemp(const Address& address);
  void resetTemp();
  
  void addReused(const Address& address);
   
   void printTempCommand();
   void printReuseCommand();
   void resetReuse();
   
  int getWay(const Address& address);
  void setTimeLast(const Address& address);

   bool wasTagPresent(const Address& address) const;
   ENTRY& lookupPast(const Address& address);
   const ENTRY& lookupPast(const Address& address) const;
   
   void initialTouch(const Address& address, const NodeID proc) ;

   int m_version;

private:
  // Private Methods

  // convert a Address to its location in the cache
  Index addressToCacheSet(const Address& address) const;

  // Given a cache tag: returns the index of the tag in a set.
  // returns -1 if the tag is not found.
  int findTagInSet(Index line, const Address& tag) const;
  int findTagInSetIgnorePermissions(Index cacheSet, const Address& tag) const;

  // Private copy constructor and assignment operator
  CacheMemory(const CacheMemory& obj);
  CacheMemory& operator=(const CacheMemory& obj);
  
  // Data Members (m_prefix)
  AbstractChip* m_chip_ptr;
  MachineType m_machType;
  string m_description;
  bool m_is_instruction_cache;

  // The first index is the # of cache lines.
  // The second index is the the amount associativity.
  Vector<Vector<ENTRY> > m_cache;

  AbstractReplacementPolicy *m_replacementPolicy_ptr;

  int m_cache_num_sets;
  int m_cache_num_set_bits;
  int m_cache_assoc;
  
  //JORGE
  int foundTagInSet(Index line, const Address& tag) const;
  uint64 *timeLoadArray;
  uint64 *timeLastArray;
  uint64 *timeReplArray;
  
  uint64 **timeLoadArrayCore;
  uint64 **timeLastArrayCore;
  uint64 **timeReplArrayCore;
  
  uint64 **reuseArrayCore;
  
  Time m_bigbang;
  
  PerfectCacheMemory<shadowEntry> *m_shadowSet;
  Vector<uint64> m_nmisses;
  Vector<uint64> m_nLast;
  Time m_lastRev;
  Vector<Histogram>  m_histoSets;
  Histogram m_histoGlobal;
  uint64 m_nmissesGlobal;
  uint64 m_nLastGlobal;
  
  Vector<uint64> m_nH [3];
  
    Histogram  *m_histoReuse;
  Histogram  *m_histoReuseThread[16];
  
  CacheMemory* m_shadow;
  
  void* dataArray;
};

// Output operator declaration
//ostream& operator<<(ostream& out, const CacheMemory<ENTRY>& obj);

// ******************* Definitions *******************

// Output operator definition
template<class ENTRY>
inline 
ostream& operator<<(ostream& out, const CacheMemory<ENTRY>& obj)
{
  obj.print(out);
  out << flush;
  return out;
}


// ****************************************************************

template<class ENTRY>
inline 
CacheMemory<ENTRY>::CacheMemory(AbstractChip* chip_ptr, int numSetBits, 
                                      int cacheAssoc, const MachineType machType, const string& description, int version, int versionB)

{
   m_version = version;
   m_bigbang=0;
  cerr << "CacheMemory L2 constructor " << version<< endl;
  m_chip_ptr = chip_ptr;
  m_machType = machType;
  m_description = MachineType_to_string(m_machType)+"_"+description;
  m_cache_num_set_bits = numSetBits;
  m_cache_num_sets = 1 << numSetBits;
  m_cache_assoc = cacheAssoc;
  m_is_instruction_cache = false;

  m_cache.setSize(m_cache_num_sets);
  
  
  switch (machType)
  {
    case MACHINETYPE_L1CACHE_ENUM:
	  if(strcmp(g_REPLACEMENT_POLICY_L1, "PSEDUO_LRU") == 0)
		m_replacementPolicy_ptr = new PseudoLRUPolicy(m_cache_num_sets, m_cache_assoc);
	  else if(strcmp(g_REPLACEMENT_POLICY_L1, "LRU") == 0)
		m_replacementPolicy_ptr = new LRUPolicyL1(m_cache_num_sets, m_cache_assoc, &m_cache);
	  else
		assert(false);
	break;
	
	case MACHINETYPE_L2CACHE_ENUM:
	  if(strcmp(g_REPLACEMENT_POLICY_L2, "PSEDUO_LRU") == 0)
		m_replacementPolicy_ptr = new PseudoLRUPolicy(m_cache_num_sets, m_cache_assoc);
	  else if(strcmp(g_REPLACEMENT_POLICY_L2, "PSEDUO_LRU2") == 0)
		m_replacementPolicy_ptr = new PseudoLRUPolicy2(m_cache_num_sets, m_cache_assoc);
	  else if(strcmp(g_REPLACEMENT_POLICY_L2, "LRU") == 0)
		m_replacementPolicy_ptr = new LRUPolicyL2(m_cache_num_sets, m_cache_assoc, &m_cache);
	  else if(strcmp(g_REPLACEMENT_POLICY_L2, "NRU") == 0)
		m_replacementPolicy_ptr = new NRUPolicyL2(m_cache_num_sets, m_cache_assoc, &m_cache);
	  else if(strcmp(g_REPLACEMENT_POLICY_L2, "LRRc") == 0)
		m_replacementPolicy_ptr = new LRRcPolicyL2(m_cache_num_sets, m_cache_assoc, &m_cache);
	  else if(strcmp(g_REPLACEMENT_POLICY_L2, "LRRd") == 0)
		m_replacementPolicy_ptr = new LRRdPolicyL2(m_cache_num_sets, m_cache_assoc, &m_cache);
	  else if(strcmp(g_REPLACEMENT_POLICY_L2, "LRRj") == 0)
		m_replacementPolicy_ptr = new LRRjPolicyL2(m_cache_num_sets, m_cache_assoc, &m_cache);
	  else if(strcmp(g_REPLACEMENT_POLICY_L2, "NRRa") == 0)
		m_replacementPolicy_ptr = new NRRaPolicyL2(m_cache_num_sets, m_cache_assoc, &m_cache);
	  else if(strcmp(g_REPLACEMENT_POLICY_L2, "NRRj") == 0)
		m_replacementPolicy_ptr = new NRRjPolicyL2(m_cache_num_sets, m_cache_assoc, &m_cache);
      else if(strcmp(g_REPLACEMENT_POLICY_L2, "SRRIPb") == 0)
        m_replacementPolicy_ptr = new NRUPolicy_SRRIPb(m_cache_num_sets, m_cache_assoc, &m_cache);
      else if(strcmp(g_REPLACEMENT_POLICY_L2, "DRRIPb") == 0)
        m_replacementPolicy_ptr = new NRUPolicy_DRRIPb(m_cache_num_sets, m_cache_assoc, &m_cache, version);
     else if(strcmp(g_REPLACEMENT_POLICY_L2, "SRRIPc") == 0)
        m_replacementPolicy_ptr = new NRUPolicy_SRRIPc(m_cache_num_sets, m_cache_assoc, &m_cache);
      else if(strcmp(g_REPLACEMENT_POLICY_L2, "DRRIPc") == 0)
        m_replacementPolicy_ptr = new NRUPolicy_DRRIPc(m_cache_num_sets, m_cache_assoc, &m_cache, version);
     else if(strcmp(g_REPLACEMENT_POLICY_L2, "SHiP") == 0)
        m_replacementPolicy_ptr = new SHiPPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
	  else
		assert(false);
	break;
		
	default:
	      ERROR_MSG("Don't recognize m_machType");
	break;
  }
    
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
//   for(int i=adow; i < numThreads; ++i){
//     cout << "Setting list size for list " << i << endl;
//     m_trans_address_list[i].setSize(30);
//   }
  //cout << "CacheMemory constructor finished" << endl;
  
  if(version==0)
  {
  cerr << "inic on" << endl;
     timeLoadArray= new uint64[50000];
     timeLastArray= new uint64[50000];
     timeReplArray= new uint64[50000];
     
     timeLoadArrayCore= new uint64*[RubyConfig::numberOfL1CachePerChip(0)];
     timeLastArrayCore= new uint64*[RubyConfig::numberOfL1CachePerChip(0)];
     timeReplArrayCore= new uint64*[RubyConfig::numberOfL1CachePerChip(0)];
     
     reuseArrayCore= new uint64*[RubyConfig::numberOfL1CachePerChip(0)];

    for(int i =0; i< RubyConfig::numberOfL1CachePerChip(0); i++)
    {
    	timeLoadArrayCore[i]= new uint64[50000];
		timeLastArrayCore[i]= new uint64[50000];
		timeReplArrayCore[i]= new uint64[50000];
		
		reuseArrayCore[i]= new uint64[9];
		
		for(uint j =0; j< 50000; j++)
		{
			timeLoadArrayCore[i][j]=0;
			timeLastArrayCore[i][j]=0;
			timeReplArrayCore[i][j]=0;
		}
		
		for(uint j =0; j< 9; j++) reuseArrayCore[i][j]=0;
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
  m_shadowSet =  new PerfectCacheMemory<shadowEntry> (m_chip_ptr);
  m_nmisses.setSize(m_cache_num_sets);
  m_nmissesGlobal = 0;
  m_nLastGlobal = 0;
  for (int i = 0; i < m_cache_num_sets; i++) {
  	m_nmisses[i] = 0;
  	m_nLast[i] = 0;
  }
  
  	for (int i = 0; i < 3; i++) m_nH[i].setSize(RubyConfig::numberOfProcsPerChip());
	
  for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
  	for (int j = 0; j < 3; j++) m_nH[j][i]= 0;

  }
  
    m_histoReuse = new Histogram(1, 500);
  for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) m_histoReuseThread[i] = new Histogram(1, 500);

  if(m_version != -1) {
  	if (m_machType == MachineType_L2Cache && g_SHADOW) m_shadow = new CacheMemory(chip_ptr, numSetBits, g_TAM_SHADOW, MachineType_L2Cache, description, -1);  	
  	
	if(g_DATA_FIFO) dataArray = new CirBuf(chip_ptr, g_BLOCKS_FIFO, version);
	else {
	  dataArray = new CacheMemory(chip_ptr, g_DATA_NUM_SETS_BITS, g_DATA_ASSOC, MachineType_L2Cache, description, -1, m_version);  	
	  ((CacheMemory*)dataArray)->m_version = versionB;
	}	
  } 
  else {
  	m_replacementPolicy_ptr = new LRUPolicyL2(m_cache_num_sets, m_cache_assoc, &m_cache);
  }

  
  
  cerr << "inic off" << endl;
}

// ****************************************************************

template<class ENTRY>
inline 
CacheMemory<ENTRY>::CacheMemory(AbstractChip* chip_ptr, int numSetBits, 
                                      int cacheAssoc, const MachineType machType, const string& description)

{
   m_bigbang=0;
   m_version=-1;
  //cout << "CacheMemory constructor numThreads = " << numThreads << endl;
  m_chip_ptr = chip_ptr;
  m_machType = machType;
  m_description = MachineType_to_string(m_machType)+"_"+description;
  m_cache_num_set_bits = numSetBits;
  m_cache_num_sets = 1 << numSetBits;
  m_cache_assoc = cacheAssoc;
  m_is_instruction_cache = false;

  m_cache.setSize(m_cache_num_sets);
  
  switch (machType)
  {
    case MACHINETYPE_L1CACHE_ENUM:
	  if(strcmp(g_REPLACEMENT_POLICY_L1, "PSEUDO_LRU") == 0)
		m_replacementPolicy_ptr = new PseudoLRUPolicy(m_cache_num_sets, m_cache_assoc);
	  else if(strcmp(g_REPLACEMENT_POLICY_L1, "LRU") == 0)
		m_replacementPolicy_ptr = new LRUPolicyL1(m_cache_num_sets, m_cache_assoc, &m_cache);
	  else if(strcmp(g_REPLACEMENT_POLICY_L1, "LRU_kid") == 0)
		m_replacementPolicy_ptr = new LRUPolicyL1_kid(m_cache_num_sets, m_cache_assoc, &m_cache);
	  else
		assert(false);
	break;
	
	case MACHINETYPE_L2CACHE_ENUM:
	  if(strcmp(g_REPLACEMENT_POLICY_L2, "PSEDUO_LRU") == 0)
		m_replacementPolicy_ptr = new PseudoLRUPolicy(m_cache_num_sets, m_cache_assoc);
	  else if(strcmp(g_REPLACEMENT_POLICY_L2, "PSEDUO_LRU2") == 0)
		m_replacementPolicy_ptr = new PseudoLRUPolicy2(m_cache_num_sets, m_cache_assoc);
	  else if(strcmp(g_REPLACEMENT_POLICY_L2, "LRU") == 0)
		m_replacementPolicy_ptr = new LRUPolicyL2(m_cache_num_sets, m_cache_assoc, &m_cache);
	  else if(strcmp(g_REPLACEMENT_POLICY_L2, "NRU") == 0)
		m_replacementPolicy_ptr = new NRUPolicyL2(m_cache_num_sets, m_cache_assoc, &m_cache);
	  else if(strcmp(g_REPLACEMENT_POLICY_L2, "NRRa") == 0)
		m_replacementPolicy_ptr = new NRRaPolicyL2(m_cache_num_sets, m_cache_assoc, &m_cache);
      else if(strcmp(g_REPLACEMENT_POLICY_L2, "SRRIPb") == 0)
        m_replacementPolicy_ptr = new NRUPolicy_SRRIPb(m_cache_num_sets, m_cache_assoc, &m_cache);
     else if(strcmp(g_REPLACEMENT_POLICY_L2, "SHiP") == 0)
        m_replacementPolicy_ptr = new SHiPPolicy(m_cache_num_sets, m_cache_assoc, &m_cache);
	  else
		assert(false);
	break;
	
	default:
	      ERROR_MSG("Don't recognize m_machType");
	break;
  }
    
  for (int i = 0; i < m_cache_num_sets; i++) {
    m_cache[i].setSize(m_cache_assoc);
    for (int j = 0; j < m_cache_assoc; j++) {
      m_cache[i][j].m_Address.setAddress(0);
      m_cache[i][j].m_Permission = AccessPermission_NotPresent;
    }
  }
  
  m_histoReuse = new Histogram(1, 500);
  for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) m_histoReuseThread[i] = new Histogram(1, 500);


  //  cout << "Before setting trans address list size" << endl;
  //create a trans address for each SMT thread
//   m_trans_address_list.setSize(numThreads);
//   for(int i=0; i < numThreads; ++i){
//     cout << "Setting list size for list " << i << endl;
//     m_trans_address_list[i].setSize(30);
//   }
  //cout << "CacheMemory constructor finished" << endl;
  


}

template<class ENTRY>
inline 
CacheMemory<ENTRY>::~CacheMemory()
{
  cerr << "CacheMemory destructor " << m_version<< endl;


  if(m_replacementPolicy_ptr != NULL)
    delete m_replacementPolicy_ptr;
}

template<class ENTRY>
inline 
void CacheMemory<ENTRY>::printConfig(ostream& out)
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
template<class ENTRY>
inline 
Index CacheMemory<ENTRY>::addressToCacheSet(const Address& address) const
{ 
  assert(address == line_address(address));
  Index temp = -1;
  switch (m_machType) {
  case MACHINETYPE_L1CACHE_ENUM:
    temp = map_address_to_L1CacheSet(address, m_cache_num_set_bits);
    break;
  case MACHINETYPE_L2CACHE_ENUM:
    temp = map_address_to_L2CacheSet(address, m_cache_num_set_bits);
    break;
 // case MACHINETYPE_VCACHE_ENUM:
  //  temp = map_address_to_L2CacheSet(address, m_cache_num_set_bits);
   // break;
  default:
    cerr << "m_machType" << m_machType << endl;
    ERROR_MSG("Don't recognize m_machType");
  }
  assert(temp < m_cache_num_sets);
  assert(temp >= 0);
  return temp;
}

template<class ENTRY>
inline 
void CacheMemory<ENTRY>:: addReused(const Address& address)
{
	m_replacementPolicy_ptr->m_nReused[addressToCacheSet(address)]++;
}


// Given a cache index: returns the index of the tag in a set.
// returns -1 if the tag is not found.
template<class ENTRY>
inline 
int CacheMemory<ENTRY>::findTagInSet(Index cacheSet, const Address& tag) const
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
template<class ENTRY>
inline 
int CacheMemory<ENTRY>::getWay(const Address& address)
{
  assert(address == line_address(address));
  DEBUG_EXPR(CACHE_COMP, HighPrio, address);
  Index cacheSet = addressToCacheSet(address);
  
  int loc = findTagInSet(cacheSet, address);
  
  assert(loc!=-1);
  return loc;
}

// ignoramos los permisos del bloque
template<class ENTRY>
inline 
int CacheMemory<ENTRY>::foundTagInSet(Index cacheSet, const Address& tag) const
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
template<class ENTRY>
inline 
int CacheMemory<ENTRY>::findTagInSetIgnorePermissions(Index cacheSet, const Address& tag) const
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
template<class ENTRY>
inline 
bool CacheMemory<ENTRY>::tryCacheAccess(const Address& address, 
                                           CacheRequestType type, 
                                           DataBlock*& data_ptr, 
                                           uint proc)
{
  assert(address == line_address(address));
  DEBUG_EXPR(CACHE_COMP, HighPrio, address);
  Index cacheSet = addressToCacheSet(address);
  int loc = findTagInSet(cacheSet, address);
  if(loc != -1){ // Do we even have a tag match?
    ENTRY& entry = m_cache[cacheSet][loc];
    
	if(m_machType==MachineType_L2Cache && g_REPLACEMENT_POLICY_L2_3SET) {
		m_nH[m_replacementPolicy_ptr->whatSubSet(&entry)][proc]++;
	}

    m_replacementPolicy_ptr->touch(cacheSet, loc, g_eventQueue_ptr->getTime(), proc);
    
    

    if(entry.m_Permission == AccessPermission_Read_Write) {
      return true;
    } 
    if ((entry.m_Permission == AccessPermission_Read_Only) && 
        (type == CacheRequestType_LD || type == CacheRequestType_IFETCH)) {
      return true;
    }
    // The line must not be accessible
  }
  return false;
}


// Normally used to check the L1 caches
// (in Sequencer.C)
template<class ENTRY>
inline 
bool CacheMemory<ENTRY>::testCacheAccess(const Address& address, 
                                           CacheRequestType type, 
                                           DataBlock*& data_ptr)
{
  assert(address == line_address(address));
  DEBUG_EXPR(CACHE_COMP, HighPrio, address);
  Index cacheSet = addressToCacheSet(address);
  int loc = findTagInSet(cacheSet, address);
  if(loc != -1){ // Do we even have a tag match?
    //ENTRY& entry = m_cache[cacheSet][loc];
    m_replacementPolicy_ptr->touch(cacheSet, loc, g_eventQueue_ptr->getTime(), 0);
    
    //data_ptr = &(entry.getDataBlk());

    return (m_cache[cacheSet][loc].m_Permission != AccessPermission_NotPresent);
  }
  //
  //data_ptr = NULL;
  return false;
}

// tests to see if an address is present in the cache
template<class ENTRY>
inline 
bool CacheMemory<ENTRY>::isTagPresent(const Address& address) const
{
  assert(address == line_address(address));
  Index cacheSet = addressToCacheSet(address);
  int location = findTagInSet(cacheSet, address);

  if (location == -1) {
    // We didn't find the tag
    DEBUG_EXPR(CACHE_COMP, LowPrio, address);
    DEBUG_MSG(CACHE_COMP, LowPrio, "No tag match");
    return false;
  } 
  DEBUG_EXPR(CACHE_COMP, LowPrio, address);
  DEBUG_MSG(CACHE_COMP, LowPrio, "found");
  return true;
}


//JORGE
template<class ENTRY>
inline 
bool CacheMemory<ENTRY>::wasTagPresent(const Address& address) const
{
  assert(address == line_address(address));
  Index cacheSet = addressToCacheSet(address);
  int location = foundTagInSet(cacheSet, address);

  if (location == -1) {
    // We didn't find the tag
    DEBUG_EXPR(CACHE_COMP, LowPrio, address);
    DEBUG_MSG(CACHE_COMP, LowPrio, "No tag match");
    return false;
  } 
  DEBUG_EXPR(CACHE_COMP, LowPrio, address);
  DEBUG_MSG(CACHE_COMP, LowPrio, "found");
  return true;
}



// Returns true if there is:
//   a) a tag match on this address or there is 
//   b) an unused line in the same cache "way"
template<class ENTRY>
inline 
bool CacheMemory<ENTRY>::cacheAvail(const Address& address) const
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

template<class ENTRY>
inline 
void CacheMemory<ENTRY>::allocate(const Address& address) 
{
  assert(address == line_address(address));
  assert(!isTagPresent(address));
  assert(cacheAvail(address));
  DEBUG_EXPR(CACHE_COMP, HighPrio, address);

  // Find the first open slot
  Index cacheSet = addressToCacheSet(address);
  for (int i=0; i < m_cache_assoc; i++) {
    if (m_cache[cacheSet][i].m_Permission == AccessPermission_NotPresent) {
      //Address a=m_cache[cacheSet][i].m_Last_Address;
      ENTRY a=ENTRY(m_cache[cacheSet][i]);
      m_cache[cacheSet][i] = ENTRY();  // Init entry
      m_cache[cacheSet][i].m_prefDWG= a.m_prefDWG;
      m_cache[cacheSet][i].m_PrevLocalCacheState= a.m_PrevLocalCacheState;
      m_cache[cacheSet][i].m_prevOwner= a.m_prevOwner;
      m_cache[cacheSet][i].m_prevSharers= a.m_prevSharers;
       m_cache[cacheSet][i].m_prefTypeRepl= a.m_prefTypeRepl;
	  m_cache[cacheSet][i].m_Last_Address=a.m_Address;
      m_cache[cacheSet][i].m_Address = address;
      m_cache[cacheSet][i].m_Permission = AccessPermission_Invalid;
      m_cache[cacheSet][i].m_reusedL1 = false;
      m_cache[cacheSet][i].m_reused = false;
      
      m_replacementPolicy_ptr->touch(cacheSet, i, 0, 0);

      return;
    }
  }
  ERROR_MSG("Allocate didn't find an available entry");
}

template<class ENTRY>
inline 
void CacheMemory<ENTRY>::allocateL2(const Address& address) 
{
  assert(address == line_address(address));
  assert(!isTagPresent(address));
  assert(cacheAvail(address));
  DEBUG_EXPR(CACHE_COMP, HighPrio, address);

  // Find the first open slot
  Index cacheSet = addressToCacheSet(address);
  
  
  for (int i=0; i < m_cache_assoc; i++) {
    if (m_cache[cacheSet][i].m_Permission == AccessPermission_NotPresent) {
      //Address a=m_cache[cacheSet][i].m_Last_Address;
      ENTRY a=ENTRY(m_cache[cacheSet][i]);
      m_cache[cacheSet][i] = ENTRY();  // Init entry
      m_cache[cacheSet][i].m_prefDWG= a.m_prefDWG;
      m_cache[cacheSet][i].m_PrevLocalCacheState= a.m_PrevLocalCacheState;
      m_cache[cacheSet][i].m_prevOwner= a.m_prevOwner;
      m_cache[cacheSet][i].m_prevSharers= a.m_prevSharers;
       m_cache[cacheSet][i].m_prefTypeRepl= a.m_prefTypeRepl;
	  m_cache[cacheSet][i].m_Last_Address=a.m_Address;
      m_cache[cacheSet][i].m_Address = address;
      m_cache[cacheSet][i].m_Permission = AccessPermission_Invalid;
      m_cache[cacheSet][i].m_uses = 0;
      m_cache[cacheSet][i].m_reused = false;
      //m_cache[cacheSet][i].m_reuseL1 = 0;
      m_cache[cacheSet][i].m_timeLoad = g_eventQueue_ptr->getTime();
      m_cache[cacheSet][i].m_timeLast = g_eventQueue_ptr->getTime();
      

      return;
    }
  }
  ERROR_MSG("Allocate didn't find an available entry");
}

template<class ENTRY>
inline 
int CacheMemory<ENTRY>::insertionDataArray(const Address& address) 
{
  assert(address == line_address(address));
  if(!g_DATA_FIFO) assert(!((CacheMemory*) dataArray)->isTagPresent(address));
  DEBUG_EXPR(CACHE_COMP, HighPrio, address);	
	
  if(g_DATA_FIFO)
	return ((CirBuf*) dataArray)->insert(address);
  else
  {
  	CacheMemory* cm = ((CacheMemory*) dataArray);
    if( !cm->cacheAvail(address)) {
	  Address a = cm->cacheProbe(address, 0);
	  
	  RequestMsg out_msg;      
	  (out_msg).m_Address = a;
	  (out_msg).m_Type = CoherenceRequestType_DATA_REPL;
	  m_chip_ptr->m_L2Cache_dataArrayReplQueue_vec[map_Address_to_L2(address).num]->enqueue(out_msg); 
	  
	  cm->lookup(a).m_Permission = AccessPermission_NotPresent;
    }
  	cm->allocateL2(address);
    return 0;
  }

  ERROR_MSG("Allocate didn't find an available entry");
}

template<class ENTRY>
inline 
void CacheMemory<ENTRY>::evictDataArray(const Address& address) 
{
  assert(address == line_address(address));
  if(!g_DATA_FIFO) assert(((CacheMemory*) dataArray)->isTagPresent(address));
  DEBUG_EXPR(CACHE_COMP, HighPrio, address);

  if(g_DATA_FIFO) ((CirBuf*)dataArray)->remove(address);
  else ((CacheMemory*) dataArray)->lookup(address).m_Permission = AccessPermission_NotPresent;;

  //ERROR_MSG("Allocate didn't find an available entry");
}

template<class ENTRY>
inline 
void CacheMemory<ENTRY>::initialTouch(const Address& address, const NodeID proc) 
{
	  Index cacheSet = addressToCacheSet(address);
	  
	  int i=findTagInSet(cacheSet, address);
	  
	     Time aux=0;
		if((m_machType==MachineType_L2Cache) {
			m_cache[cacheSet][i].m_uses = 1;
			if(g_SHADOW && m_version != -1) {
				if(m_shadow->isTagPresent( address)) {
					m_shadow->deallocate(address);
					aux=1;
					//cerr << "HIT!" << endl;
					m_cache[cacheSet][i].m_NRU = true;
				}
			}
		}
      m_replacementPolicy_ptr->touch(cacheSet, i, aux, proc);
}

template<class ENTRY>
inline 
void CacheMemory<ENTRY>::deallocate(const Address& address)
{
  assert(address == line_address(address));
  assert(isTagPresent(address));
  DEBUG_EXPR(CACHE_COMP, HighPrio, address);
  

	if(m_machType == MACHINETYPE_L2CACHE_ENUM && m_version!=-1) {
		//L2Cache_Entry a = (L2Cache_Entry) lookup(address);
		m_histoReuseThread[(lookup(address)).m_owner.num]->add((lookup(address)).m_uses);  
		m_histoReuse->add(( lookup(address)).m_uses);
		printTemp(address);
	}
	
  lookup(address).m_Last_Address= address;
  bool NRU = lookup(address).m_NRU;
  lookup(address).m_Permission = AccessPermission_NotPresent;

	if((m_machType==MachineType_L2Cache) && g_SHADOW && m_version != -1 && NRU) {
		if(!m_shadow->cacheAvail(address)) {
			Address a = m_shadow->cacheProbe(address, 0);
			m_shadow->deallocate(a);
		}
		 m_shadow->allocateL2(address);
	}

 }

// Returns with the physical address of the conflicting cache line
// *Only called when replacing a cache line [in the protocol .sm]
template<class ENTRY>
inline 
Address CacheMemory<ENTRY>::cacheProbe(const Address& address, const MachineID proc) const
{
  return cacheProbe(address, proc.num);
  //if(LRU_STACK) return m_cache[cacheSet][m_replacementPolicy_ptr->getVictim(cacheSet, address)].m_Address;
}

template<class ENTRY>
inline 
Address CacheMemory<ENTRY>::cacheProbe(const Address& address, const int proc) const
{
  assert(address == line_address(address));
  assert(!cacheAvail(address));

  Index cacheSet = addressToCacheSet(address);
  
  return m_cache[cacheSet][m_replacementPolicy_ptr->getVictim(cacheSet, proc)].m_Address;  
  //if(LRU_STACK) return m_cache[cacheSet][m_replacementPolicy_ptr->getVictim(cacheSet, address)].m_Address;
}


// looks an address up in the cache
template<class ENTRY>
inline 
ENTRY& CacheMemory<ENTRY>::lookup(const Address& address)
{

  assert(address == line_address(address));
  Index cacheSet = addressToCacheSet(address);
  int loc = findTagInSet(cacheSet, address);
  assert(loc != -1);
  return m_cache[cacheSet][loc];
}

// looks an address up in the cache
template<class ENTRY>
inline 
const ENTRY& CacheMemory<ENTRY>::lookup(const Address& address) const
{
  assert(address == line_address(address));
  Index cacheSet = addressToCacheSet(address);
  int loc = findTagInSet(cacheSet, address);
  assert(loc != -1);
  return m_cache[cacheSet][loc];
}


//JORGE
template<class ENTRY>
inline 
ENTRY& CacheMemory<ENTRY>::lookupPast(const Address& address)
{
  assert(address == line_address(address));
  Index cacheSet = addressToCacheSet(address);
  int loc = foundTagInSet(cacheSet, address);
  assert(loc != -1);
  return m_cache[cacheSet][loc];
}

template<class ENTRY>
inline 
const ENTRY& CacheMemory<ENTRY>::lookupPast(const Address& address) const
{
  assert(address == line_address(address));
  Index cacheSet = addressToCacheSet(address);
  int loc = foundTagInSet(cacheSet, address);
  assert(loc != -1);
  return m_cache[cacheSet][loc];
}



template<class ENTRY>
inline
AccessPermission CacheMemory<ENTRY>::getPermission(const Address& address) const
{
  //cout << "get Perm" << endl;

  assert(address == line_address(address));
  return lookup(address).m_Permission;
}

template<class ENTRY>
inline 
void CacheMemory<ENTRY>::changePermission(const Address& address, AccessPermission new_perm)
{
 // cout << "change Perm" << endl;

  assert(address == line_address(address));
  lookup(address).m_Permission = new_perm;
  assert(getPermission(address) == new_perm);
}


// Sets the most recently used bit for a cache block
template<class ENTRY>
inline 
void CacheMemory<ENTRY>::setMRU(const Address& address, const NodeID proc)
{
  Index cacheSet;

  cacheSet = addressToCacheSet(address);
  int way=  findTagInSet(cacheSet, address);
    
  m_cache[cacheSet][way].m_uses++;
  
  m_replacementPolicy_ptr->touch(cacheSet, 
                                 way, 
                                 g_eventQueue_ptr->getTime(), proc);
  
}



template<class ENTRY>
inline 
void CacheMemory<ENTRY>::recordCacheContents(CacheRecorder& tr) const
{
  for (int i = 0; i < m_cache_num_sets; i++) {
    for (int j = 0; j < m_cache_assoc; j++) {
      AccessPermission perm = m_cache[i][j].m_Permission;
      CacheRequestType request_type = CacheRequestType_NULL;
      if (perm == AccessPermission_Read_Only) {
        if (m_is_instruction_cache) {
          request_type = CacheRequestType_IFETCH;
        } else {
          request_type = CacheRequestType_LD;
        }
      } else if (perm == AccessPermission_Read_Write) {
        request_type = CacheRequestType_ST;
      }

      if (request_type != CacheRequestType_NULL) {
        tr.addRecord(m_chip_ptr->getID(), m_cache[i][j].m_Address, 
                     Address(0), request_type, m_replacementPolicy_ptr->getLastAccess(i, j));
      }
    }
  }
}

template<class ENTRY>
inline 
void CacheMemory<ENTRY>::print(ostream& out) const
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

template<class ENTRY>
inline 
void CacheMemory<ENTRY>::printData(ostream& out) const
{ 
  out << "printData() not supported" << endl;
}

template<class ENTRY>
inline 
void CacheMemory<ENTRY>::printTempCommand()
{ 
  assert(m_version==0);
  
  uint64 *tLoad=new uint64[50000];
  uint64 *tLast=new uint64[50000];    
     
   uint64**  tLoadCore= new uint64*[RubyConfig::numberOfL1CachePerChip(0)];
   uint64**   tLastCore= new uint64*[RubyConfig::numberOfL1CachePerChip(0)];

    for(int i =0; i< RubyConfig::numberOfL1CachePerChip(0); i++)
    {
    	tLoadCore[i]= new uint64[50000];
		tLastCore[i]= new uint64[50000];
    }
 
  cerr << "PRINT_TEMP" << endl;
 // for(int i=0; i<10000; i++) cerr << timeLoadArray[i] << "\t" << timeLastArray[i]  << "\t" <<timeReplArray[i] << endl;
  
  tLoad[0]= timeLoadArray[0] - timeLastArray[0];
  tLast[0]= timeLastArray[0] - timeReplArray[0];
  
  for(int i =0; i< RubyConfig::numberOfL1CachePerChip(0); i++)
  {
  	tLoadCore[i][0]= timeLoadArrayCore[i][0] - timeLastArrayCore[i][0];
  	tLastCore[i][0]= timeLastArrayCore[i][0] - timeReplArrayCore[i][0];
  }
  
  for(int i=1; i<50000; i++)
  {
    tLoad[i]= timeLoadArray[i] + tLoad[i-1] - timeLastArray[i];
    tLast[i]= timeLastArray[i] + tLast[i-1] - timeReplArray[i];
    
	  for(int j =0; j< RubyConfig::numberOfL1CachePerChip(0); j++)
	  {
		tLoadCore[j][i]= timeLoadArrayCore[j][i] + tLoadCore[j][i-1] - timeLastArrayCore[j][i];
		tLastCore[j][i]= timeLastArrayCore[j][i] + tLastCore[j][i-1] - timeReplArrayCore[j][i];
		
		cerr << tLoadCore[j][i] << "\t" << tLastCore[j][i]  << "\t" ;
	  }
    
    cerr << tLoad[i] << "\t" << tLast[i]  << "\t" << (float)tLoad[i] / (float)tLast[i] << "\t" << (float)tLoad[i] / (float)(tLast[i] + tLoad[i]) << endl;
  }
  
/*  cerr << "Reuse patterns per core:" ;
  for(int i =0; i< RubyConfig::numberOfL1CachePerChip(0); i++)
  {
  	cerr << endl << "core " << i<< ": " ;
  	for(int j=0; j<9; j++) cerr << reuseArrayCore[i][j] << "\t";
  }
*/
}


template<class ENTRY>
inline 
void CacheMemory<ENTRY>::printReuseCommand()
{ 
  cerr << "Reuse patterns per core:" ;
  for(int i =0; i< RubyConfig::numberOfL1CachePerChip(0); i++)
  {
  	cerr << endl << "core " << i<< ": " ;
  	for(int j=0; j<9; j++) cerr << reuseArrayCore[i][j] << "\t";
  }
  
  
  cerr << endl << m_histoGlobal << endl;
  cerr << "The number of not referenced blocks after 1K misses is: " << m_nLastGlobal << endl;
  /*for(uint i=0; i<m_cache_num_sets; i++)
  	cerr << m_histoSets[i] << endl;*/
  	
  m_replacementPolicy_ptr->printStats(cerr);	
  
  for(int i =0; i< RubyConfig::numberOfL1CachePerChip(0); i++) 
  	cerr  << "_reuse_thread_" << i << ":\t" <<  *m_histoReuseThread[i] << endl;
  	
  cerr  << "_reuse_total_" << ":\t" <<  *m_histoReuse << endl;
  
  
}

template<class ENTRY>
inline 
void CacheMemory<ENTRY>::printTemp(const Address& address)
{ 
  
  if(m_version==0 && !g_CARGA_CACHE  )
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
     
/*    int reusoL1 = m_cache[cacheSet][loc].m_reuseL1;
    if( (reusoL1==1 || reusoL1==3 ) && g_NO_REUSE_LRU) {
    	m_replacementPolicy_ptr->touch(cacheSet, loc, -1, 0);
    }
    
    if(!m_cache[cacheSet][loc].m_reused) {
    	reuseArrayCore[core][reusoL1]++;
    }
	else {
		reuseArrayCore[core][reusoL1+4]++;
	}
	
	m_shadowSet->allocate(address);
	m_shadowSet->lookup(address).m_nmisses= m_nmisses[cacheSet];
	
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
*/
	//cerr << "meto el bloque " << address << " con " << m_nmisses[cacheSet] << " fallos " << m_shadowSet->lookup(address).m_nmisses << endl;
	
  }  //m_version && CARGA_CACHE		

//  cerr << m_cache[cacheSet][loc].m_timeLoad << "\t" << m_cache[cacheSet][loc].m_timeLast 
//  << "\t" << m_cache[cacheSet][loc].m_timeRepl << endl;

}



template<class ENTRY>
inline 
void CacheMemory<ENTRY>::resetTemp()
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

template<class ENTRY>
inline 
void CacheMemory<ENTRY>::resetReuse()
{ 
	for(int i =0; i< RubyConfig::numberOfL1CachePerChip(0); i++)
		for(uint j =0; j< 9; j++) reuseArrayCore[i][j]=0;
  
  	cerr << "finished reseting reuse" << endl;
}

// PUBLIC METHODS
template<class ENTRY>
inline 
void CacheMemory<ENTRY>::setTimeLast(const Address& address)
{
if(m_version==0 && !g_CARGA_CACHE)
{
  assert(address == line_address(address));
  DEBUG_EXPR(CACHE_COMP, HighPrio, address);
  Index cacheSet = addressToCacheSet(address);
  int loc = findTagInSet(cacheSet, address);
  assert(loc!=-1);
  
  m_cache[cacheSet][loc].m_timeLast = g_eventQueue_ptr->getTime();
}
  //cerr << "cacheSet:" << cacheSet << "  loc:" << loc << "t:" << g_eventQueue_ptr->getTime() << endl;
}


template<class ENTRY>
void CacheMemory<ENTRY>::getMemoryValue(const Address& addr, char* value,
                                           unsigned int size_in_bytes ){
  //cout << "getmv" << endl;

  ENTRY entry = lookup(line_address(addr));
  unsigned int startByte = addr.getAddress() - line_address(addr).getAddress();
  for(unsigned int i=0; i<size_in_bytes; ++i){
    value[i] = entry.m_DataBlk.getByte(i + startByte);
  }
}

template<class ENTRY>
void CacheMemory<ENTRY>::setMemoryValue(const Address& addr, char* value,
                                           unsigned int size_in_bytes ){
          //cout << "setmv" << endl;
                                   
  ENTRY& entry = lookup(line_address(addr));
  unsigned int startByte = addr.getAddress() - line_address(addr).getAddress();
  assert(size_in_bytes > 0);
  for(unsigned int i=0; i<size_in_bytes; ++i){
    entry.m_DataBlk.setByte(i + startByte, value[i]);
  }

  entry = lookup(line_address(addr));
}

#endif //CACHEMEMORY_H

