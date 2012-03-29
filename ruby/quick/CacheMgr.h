#ifndef CacheMgr_H
#define CacheMgr_H

#include "interface.h"
#include "CacheEntryQuick.h"
#include "CacheMemoryQuick.h"
 #include "SimicsDriver.h"

#include <vector>
#include "Histogram.h"

class StreamQuick;
class CacheMemoryQuick;
class CacheMgr
{
  
public:
	CacheMgr(SimicsDriver* a);
	~CacheMgr();
	
	uint access(  memory_transaction_t* mt, bool isPrefetch=false, Address prefetchAddress=Address(0), uint prefetchThread=0);
	void printStats(ostream& out);
	void clearStats();
	
	SimicsDriver* m_driver;

private:	
	CacheMemoryQuick** caches [3];
	CacheMemoryQuick* PILAS[5];
	CacheMemoryQuick** PILAS_L1;
	CacheMemoryQuick** PILAS_L2[3];

	bool visit[4096];
	uint totalVisit;
	
	Vector<uint> instrThread;
	Vector<uint> cyclesThread;
	Vector<uint> LLCMissesThread;
	
	uint cyclesTotal;
	uint instrTotal;
	uint LLCMissesTotal;
	
	
  //PREFETCH

	uint degreesS[11];
	uint distances[11];
	uint degreeIndex[16];

	StreamQuick** streams;
	int n_streams;
	int n_streams_activos;

	void newStream(uint i, uint64 a, uint pr, int degr, int dis, int version);
	bool accessStream(Address a, uint proc, bool miss);
	void actualizaLRUstreams(int i);
	void actualizaLRUstreamsInv(int i);
	void actualizaLRUstreamsDel(int i);
	void streamsAggrReview();
	
	void generatePrefetchs(uint proc);
	
	bool sampledSet(Address* a);
	uint whatSubSet(CacheEntryQuick &a);
	void pinta(Address *a);
	void invalidateCopies(const Address& a);
	
	bool checkAddress(Address addr);


		ofstream fich[8];
	int monitoredSets[8];
  

};


class StreamQuick
  {
   
    public:
       StreamQuick(uint64 a, uint pr, int degr, int dis, int version);
   
       StreamQuick(){state=-1;} 
       bool test(uint64 a , uint node);
     //private:
      uint64 A, E;
      int state;
      int dir; //true = hacia+ , false=hacia-
      uint64 last;
      uint proc;
      uint nproc;
      int deg;
      int d;
      int LRUpos;
       int m_version;
  };
  
#endif
