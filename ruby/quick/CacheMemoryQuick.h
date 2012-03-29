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
 * CacheMemoryQuick.h
 * 
 * Description: 
 *
 * $Id: CacheMemoryQuick.h,v 3.7 2004/06/18 20:15:15 beckmann Exp $
 *
 */

#ifndef CacheMemoryQuick_H
#define CacheMemoryQuick_H

#include "AbstractChip.h"
#include "Global.h"
#include "AccessPermission.h"
#include "Address.h"
#include "CacheRecorder.h"
#include "CacheRequestTypeQuick.h"
#include "Vector.h"
#include "DataBlock.h"
#include "MachineTypeQuick.h"
#include "RubySlicc_ComponentMapping.h"
//#include "PseudoLRUPolicy.h"
//#include "LRUPolicy.h"


#include "quickLRUPolicy.h" 
#include "quickLRUPolicyb.h" 
#include "quickLRUPolicyc.h" 
#include "quickLRUshadowPolicy.h" 
#include "quickLRUPolicyL1.h" 
#include "quickRNDPolicy.h"
#include "quickNRUPolicy.h"
// #include "quickNRUPolicy_3SET.h"
// #include "quickNRUPolicy_3SETb.h"
// #include "quickNRUPolicy_3SETc.h" 
// #include "quickNRUPolicy_3SETd.h" 
// #include "quickNRUPolicy_3SETe.h"
// #include "quickNRUPolicy_3SETf.h" 
// #include "quickNRUPolicy_3SETg.h" 
// #include "quickNRUPolicy_3SETh.h" 
// #include "quickNRUPolicy_3SETi.h" 
// 
 #include "quickLRRPolicy.h" 
// #include "quickLRRaPolicy.h" 
// #include "quickLRRbPolicy.h" 
#include "quickLRRcPolicy.h" 
#include "quickLRRdPolicy.h" 
#include "quickLRRdtPolicy.h" 

//#include "quickLRRdPolicy.h" 

#include "quickNRRaPolicy.h" 
#include "quickNRRbPolicy.h" 
#include "quickNRUaPolicy.h" 
#include "quickNRUbPolicy.h" 

#include "quickNRUPolicy_SRRIP.h" 
//#include "quickNRUPolicy_DRRIP.h" 
#include "quickNRUPolicy_SRRIPb.h" 
#include "quickNRUPolicy_DRRIPb.h" 

#include "quickDRRIPcPolicy.h"

/*
#include "quickPLIPolicy.h"
#include "quickPLIaPolicy.h"
#include "quickPLIbPolicy.h"
#include "quickPLIcPolicy.h"
#include "quickPLIdPolicy.h"
#include "quickPLIePolicy.h"
#include "quickPLIfPolicy.h"
#include "quickPLIgPolicy.h"
#include "quickPLIiPolicy.h"

#include "quickNRUPolicy_qbs.h"
#include "quickNRUPolicy_qbs2.h"

#include "quickNRUPolicy_kid.h"
#include "quickLRUPolicy_kid.h"
#include "quickRNDPolicy_kid.h"
#include "quickRNDPolicy_kibRS.h"
#include "quickRNDPolicy_kibRSa.h"
#include "quickLRUPolicy_3SET.h" 
#include "quickLRUPolicy_3SETb.h" 
#include "quickLRUPolicy_23SET.h" 
//#include "quickNRUPolicy_kibRS.h"
*/
#include "quickLRUPolicyPILA.h" 
#include "quickLRUPolicyPILAF.h" 
#include "quickLRUPolicyPILAF2.h" 
#include "quickLRUPolicyPILA_L1.h" 



#include "AbstractReplacementPolicyQuick.h"

#include "CacheMgr.h"
#include "CacheEntryQuick.h"
#include "PageTableQuick.h"

#include <vector>

class CacheEntryQuick;
class CacheMgr;
class PageTableQuick;


class CacheMemoryQuick {
public:

  // Constructors
  CacheMemoryQuick( int numSetBits, int cacheAssoc, const MachineTypeQuick machType, CacheMgr* a, char* name, int version = 0);

  // Destructor
  ~CacheMemoryQuick();
  
  // Public Methods
  void printConfig(ostream& out);

  // perform a cache access and see if we hit or not.  Return true on a hit.
  int tryCacheAccess(const Address& address, CacheRequestTypeQuick type, uint proc);

  // similar to above, but doesn't require full access check
  bool testCacheAccess(const Address& address, CacheRequestTypeQuick type);

  // tests to see if an address is present in the cache
  bool isTagPresent(const Address& address) const;

  // Returns true if there is:
  //   a) a tag match on this address or there is 
  //   b) an unused line in the same cache "way"
  bool cacheAvail(const Address& address) ;

  // find an unused entry and sets the tag appropriate for the address
  void allocate(const Address& address, const uint proc);

  // find an unused entry and sets the tag appropriate for the address
  void allocateL2(const Address& address, const uint proc);


  // Explicitly free up this address
  void deallocate(const Address& address);

  // Returns with the physical address of the conflicting cache line
  Address cacheProbe(const Address& address, uint proc=0) const;

  // looks an address up in the cache
  CacheEntryQuick& lookup(const Address& address);
  const CacheEntryQuick& lookup(const Address& address) const;
  CacheEntryQuick& lookup(const int set, const int pos);
  
  // Get/Set permission of cache block
  AccessPermission getPermission(const Address& address) const;
  void changePermission(const Address& address, AccessPermission new_perm);

  // Hook for checkpointing the contents of the cache
  void recordCacheContents(CacheRecorder& tr) const;
  void setAsInstructionCache(bool is_icache) { m_is_instruction_cache = is_icache; }

  // Set this address to most recently used
  void setMRU(const Address& address);

  void getMemoryValue(const Address& addr, char* value,
                      unsigned int size_in_bytes );
  void setMemoryValue(const Address& addr, char* value,
                      unsigned int size_in_bytes );

  // Print cache contents
  void print(ostream& out) const;
  void printData(ostream& out) const;

  void printStats(ostream& out);
  void clearStats();
  
  //JORGE
  void printTemp(const Address& address);
  void resetTemp();
   
   void printTempCommand();
   void printReuseCommand();
   void resetReuse();
   
  int getWay(const Address& address);
  void setTimeLast(const Address& address);

   bool wasTagPresent(const Address& address) const;
   CacheEntryQuick& lookupPast(const Address& address);
   const CacheEntryQuick& lookupPast(const Address& address) const;

	void replacementLower(Address a) const;
	
// convert a Address to its location in the cache
  Index addressToCacheSet(const Address& address) const;

	void printSet(ostream& out, uint set);
	
	//esta aqui para llamar a su printStats desde CacheMgr, despues de debug volver a mover
	AbstractReplacementPolicyQuick *m_replacementPolicy_ptr;
	
	void invalidateAddress(const Address& a);

void statsPartialTags(const Address& address, int loc);

  	//Esto es suc’simo
  	Address m_overAssocAddress;


private:
  // Private Methods
  
  // Given a cache tag: returns the index of the tag in a set.
  // returns -1 if the tag is not found.
  int findTagInSet(Index line, const Address& tag) const;
  int findTagInSetIgnorePermissions(Index cacheSet, const Address& tag) const;

  // Private copy constructor and assignment operator
  CacheMemoryQuick(const CacheMemoryQuick& obj);
  CacheMemoryQuick& operator=(const CacheMemoryQuick& obj);
  
  // Data Members (m_prefix)
  MachineTypeQuick m_machType;
  string m_description;
  bool m_is_instruction_cache;

  // The first index is the # of cache lines.
  // The second index is the the amount associativity.
  Vector<Vector <CacheEntryQuick> > m_cache;


  int m_cache_num_sets;
  int m_cache_num_set_bits;
  int m_cache_assoc;
  
  //JORGE
  int foundTagInSet(Index line, const Address& tag) const;
  int m_version;
  uint64 *timeLoadArray;
  uint64 *timeLastArray;
  uint64 *timeReplArray;
  
  uint64 **timeLoadArrayCore;
  uint64 **timeLastArrayCore;
  uint64 **timeReplArrayCore;
  
  Histogram  *m_histoReuse;
  Histogram  *m_histoReuseThread[16];
  
  Time m_bigbang;
  
  //PerfectCacheMemory<shadowEntry> *m_shadowSet;
  Vector<uint64> m_nmisses;
  Vector<uint64> m_nLast;
  Time m_lastRev;
  Vector<Histogram>  m_histoSets;
  Histogram m_histoGlobal;
  uint64 m_nmissesGlobal;
  uint64 m_nLastGlobal;
  
  Vector<uint64> m_nA, m_nM, m_nAP, m_nMP;
  Vector<uint64> m_nH [3];

  CacheMgr* m_cacheMgr;	
  
  	char m_name[100];
  	
  	PageTableQuick m_table;
  	Histogram histoRemoved[10];
  	
  	CacheMemoryQuick* m_shadow;
  	

};

// Output operator declaration
//ostream& operator<<(ostream& out, const CacheMemoryQuick& obj);

// ******************* Definitions *******************

// Output operator definition
/*
inline 
ostream& operator<<(ostream& out, const CacheMemoryQuick& obj)
{
  obj.print(out);
  out << flush;
  return out;
}
*/

// ****************************************************************



#endif //CacheMemoryQuick_H

