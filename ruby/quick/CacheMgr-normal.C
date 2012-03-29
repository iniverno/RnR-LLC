#include "CacheMgr.h"
#include "CacheEntryQuick.h"
#include "CacheMemoryQuick.h"



#define inclusion_L2_L1 g_INCLUSION_L2_L1
#define inclusion_L3_L2 1 

#define exclusion_L2_L1 0
#define exclusion_L3_L2 g_EXCLUSION_L3

#define victimL3 0

#define latencyL1I g_L1Ilatency   //load-use !!!
#define latencyL1D g_L1Dlatency
#define latencyL2 10
#define latencyL3 24
#define latencyMem 175


#define penalL1I (latencyL1I-1)
#define penalL1D (latencyL1D-1)
#define penalL2 latencyL2-1
#define penalL3 latencyL3-1
#define penalMem latencyMem-1

#define numSetsBitsL1 7
#define numSetsBitsL2 9
// poner en orden con respecto a exclusion* !!!

#define fetchL1 1
#define fetchL2 1
#define fetchL3 1

#define NUM_CORES (RubyConfig::numberOfProcsPerChip() / g_NUM_SMT_THREADS)

#define DEBUG_CACHE_MGR 0
#define g_DEBUG_PREFETCHER 0

#define ndegreesStr 5

CacheMgr::CacheMgr(SimicsDriver* a) {
	m_driver = a;
	
	//L1s
	caches[0]= new CacheMemoryQuick* [NUM_CORES*2] ();
	
	//L2
	caches[1]= new CacheMemoryQuick* [NUM_CORES] ();

	char name[100];
	for(uint i=0; i<NUM_CORES; i++) {
		sprintf(name, "L1D_%d\0", i);
		caches[0][i]= new CacheMemoryQuick ( numSetsBitsL1, 4, MachineTypeQuick_L0Cache, this, name, i);
		sprintf(name, "L1I_%d\0", i);
		caches[0][i + NUM_CORES]= new CacheMemoryQuick ( numSetsBitsL1, 4, MachineTypeQuick_L0Cache, this, name, i);

		sprintf(name, "L2_%d\0", i);
		caches[1][i]= new CacheMemoryQuick(numSetsBitsL2, 8, MachineTypeQuick_L15Cache, this, name, i);
	}
	
	//¡¡ LOS BANCOS !!!
	//L3 L2_CACHE_NUM_SETS_BITS
	caches[2]= new CacheMemoryQuick* [g_NUM_L2_BANKS] ();
	for(uint i=0; i<g_NUM_L2_BANKS; i++) {
		sprintf(name, "L3_bank_%d\0", i);
		cerr << "La L3 tiene : " << L2_CACHE_NUM_SETS_BITS << endl;
		caches[2][i]= new CacheMemoryQuick ( L2_CACHE_NUM_SETS_BITS, 16, MachineTypeQuick_L2Cache, this, name, i);
	}
	
	if(g_PILAS) {
		PILAS[0] = new CacheMemoryQuick ( L2_CACHE_NUM_SETS_BITS, 128, MachineTypeQuick_PILA0, this, "PILA0", 0);
		PILAS[1] = new CacheMemoryQuick ( L2_CACHE_NUM_SETS_BITS, 128, MachineTypeQuick_PILA1, this, "PILA1", 0);
		PILAS[2] = new CacheMemoryQuick ( L2_CACHE_NUM_SETS_BITS, 128, MachineTypeQuick_PILA2, this, "PILA2", 0);
		
		cerr << "PILAS[0]: " << PILAS[0] << " PILAS[1]: " << PILAS[1] << " PILAS[2]: " << PILAS[2] << endl; 
		
		PILAS_L1 = new CacheMemoryQuick* [RubyConfig::numberOfProcsPerChip()] ();
		PILAS_L2 = new CacheMemoryQuick* [RubyConfig::numberOfProcsPerChip()] ();
		for(uint i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
			sprintf(name, "PILA_L1_%d", i);
			PILAS_L1[i] = new CacheMemoryQuick ( numSetsBitsL1, 128, MachineTypeQuick_PILA_L1, this, name, 0);
			sprintf(name, "PILA_L2_%d", i);
			PILAS_L2[i] = new CacheMemoryQuick ( numSetsBitsL2, 128, MachineTypeQuick_PILA_L2, this, name, 0);
		}
	}
	
	//PREFETCHER
	
	degreesS[0]=1;
 	degreesS[1]=1;
 	degreesS[2]=2;
	degreesS[3]=4;
	degreesS[4]=8;

	distances[0]=4;
	distances[1]=8;
	distances[2]=16;
	distances[3]=32;
	distances[4]=64;
 
	for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) {
		degreeIndex[j]=2;
	}
#define g_NUMBER_OF_STREAMS 16
	n_streams=g_NUMBER_OF_STREAMS*RubyConfig::numberOfProcsPerChip();
     cerr << "n_streams: " << n_streams << endl;
	streams=new StreamQuick*[n_streams];
	n_streams_activos=0;
	for(int j=0; j<n_streams; j++){ streams[j]=new StreamQuick(); streams[j]->state=-1;}
	
	
	instrThread.setSize(RubyConfig::numberOfProcsPerChip());
	cyclesThread.setSize(RubyConfig::numberOfProcsPerChip());
	LLCMissesThread.setSize(RubyConfig::numberOfProcsPerChip());
	
	for(uint i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
		instrThread[i] = 0;
		cyclesThread[i] = 0;
		LLCMissesThread[i] = 0;
	}
	cyclesTotal=0;
	instrTotal=0;
	LLCMissesTotal=0;

}

CacheMgr::~CacheMgr()
{ int a =0;
}

/* AJUSTAR STATS y VARIABLES INCLUSION  */

uint CacheMgr::access(memory_transaction_t* mt, bool isPrefetch, Address prefetchAddress, uint prefetchThread) {
	
	
	Address *auxAdr, *addr;
	uint bank, thread, proc;
	bool isFetch=false;
	uint nCores = RubyConfig::numberOfProcsPerChip() / g_NUM_SMT_THREADS;
	bool pendingPrefetch = false;
	CacheRequestTypeQuick request = isPrefetch ? CacheRequestTypeQuick_PREFETCH : CacheRequestTypeQuick_LD;
	
	if(!isPrefetch) {	
		auxAdr= new Address(mt->s.physical_address);
		addr= new Address(line_address(*auxAdr));
			
		thread = SIMICS_get_proc_no(mt->s.ini_ptr);
		isFetch = (mt->s.type == Sim_Trans_Instr_Fetch);
		
	} else {
		auxAdr= new Address(prefetchAddress);
		addr= new Address(line_address(*auxAdr));
		thread= prefetchThread;
	}
	bank = map_Address_to_L2(*addr).num;
	proc = thread / g_NUM_SMT_THREADS;
	
	if(isFetch) {
		instrThread[thread]++;
		instrTotal++;
	} 
	//return 0;
	
	//cerr << "\tTime:"  << g_eventQueue_ptr->getTime()<< "  transaccion: " << (isFetch ? "fetch" : "mem") << " atomica: "  << endl;

		
	if(DEBUG_CACHE_MGR) { 
	//	if(caches[2][0]->addressToCacheSet(*addr) == 17) cerr << "Acceso a L1:" << *addr << endl;
	}
	
	
	if(g_PILAS && !isPrefetch && !isFetch) {
		uint aux2=caches[0][0]->addressToCacheSet(*addr);
	
		if((aux2 && 0xf) == 1) {
			if(!PILAS_L1[thread]->tryCacheAccess(*addr, request, thread)) {
				if(!PILAS_L1[thread]->cacheAvail(*addr)) {
					Address aux = PILAS_L1[thread]->cacheProbe(*addr);
					PILAS_L1[thread]->deallocate(aux);
				}
				PILAS_L1[thread]->allocate(*addr, thread);
			}
			
		}
	}

	
	if(!isPrefetch && caches[0][proc + nCores*isFetch]->tryCacheAccess(*addr, request, thread)) {
		
		bool flag=false;
		uint kaux=0;
		
		
	   //hit  L1
	   
	   //assert(!caches[0][proc + nCores*(!isFetch)]->testCacheAccess(*addr, request));
	   //assert(caches[1][proc]->testCacheAccess(*addr, CacheRequestTypeQuick_LD));
	   
	   if(DEBUG_CACHE_MGR) { 
		//if(caches[2][0]->addressToCacheSet(*addr) == 17) cerr << "Hit L1" << endl;
		}
		//if(exclusion_L3_L2) assert(!caches[2][bank]->testCacheAccess(*addr, CacheRequestTypeQuick_LD));
		
		if(isFetch) {			
			cyclesThread[thread] += latencyL1I;
		  	cyclesTotal += latencyL1I;
		} 
		/*else {
			//cyclesThread[thread] += latencyL1D;
		  	//cyclesTotal += latencyL1D;
		}*/
		
		delete auxAdr;
		delete addr;
		return isFetch ? penalL1I : penalL1D;
	} 
	else {
	
	/************* L1 miss *************************/
		if(DEBUG_CACHE_MGR) { 
		//	if(caches[2][0]->addressToCacheSet(*addr) == 17) cerr << "Miss L1" << endl;
		}		
		
		if(!isPrefetch) {
		
			  if(caches[0][proc + nCores*(!isFetch)]->testCacheAccess(*addr, request)) {
				caches[0][proc + nCores*(!isFetch)]->deallocate(*addr);
				if(caches[1][proc]->testCacheAccess(*addr, request)) {
				
					//assert(caches[1][proc]->lookup(*addr).m_Sharers.bitMap[proc + nCores * (!isFetch)]);
					
					if(caches[1][proc]->lookup(*addr).m_Sharers.bitMap[proc + nCores * (!isFetch)])
						caches[1][proc]->lookup(*addr).m_Sharers.del(proc + nCores * (!isFetch));
					caches[1][proc]->lookup(*addr).m_instr = isFetch;
				}
				if(!exclusion_L3_L2) {//P 
					assert(caches[2][bank]->lookup(*addr).m_Sharers.bitMap[proc + nCores * (!isFetch)]);//P 
					assert(caches[2][bank]->testCacheAccess(*addr, CacheRequestTypeQuick_LD));//P 
					caches[2][bank]->lookup(*addr).m_Sharers.del(proc + nCores * (!isFetch));//P 
					caches[2][bank]->lookup(*addr).m_instr = isFetch;//P 
				}//P 
			   }

		
			//si no hay sitio (suponemos FETCH ON MISS)
			if(!caches[0][proc + nCores*isFetch]->cacheAvail(*addr)) {
			
				Address aux= caches[0][proc + nCores*isFetch]->cacheProbe(*addr);   //chosing a victim
				
				//bool wasInstr = caches[2][bank]->lookup(aux).m_instr;
				caches[0][proc + nCores * isFetch]->deallocate(aux);  //lo quitamos de la cache L1 que toca
				if(!exclusion_L3_L2) {
					//assert(map_Address_to_L2(aux).num == bank);
					//assert(caches[2][bank]->lookup(aux).m_Sharers.bitMap[proc + nCores * isFetch]);
					//assert(caches[2][bank]->testCacheAccess(aux, CacheRequestTypeQuick_LD));
					caches[2][map_Address_to_L2(aux).num]->lookup(aux).m_Sharers.del(proc + nCores * isFetch);  //dir preciso//P 
				} 
				
				if(inclusion_L2_L1) {
					assert(caches[1][proc]->lookup(aux).m_Sharers.bitMap[proc + nCores * isFetch]);
					caches[1][proc]->lookup(aux).m_Sharers.del(proc + nCores * isFetch);  //apuntamos que ya no está por debajo
					
				} else {  //sending the line to L2
					if(!caches[1][proc]->testCacheAccess(aux, request)) {
						if(!caches[1][proc]->cacheAvail(aux)) {
							Address aux2= caches[1][proc]->cacheProbe(aux);				
							//assert(map_Address_to_L2(aux2).num == bank);
							uint auxBank = map_Address_to_L2(aux2).num;
							
							uint owner = caches[1][proc]->lookup(aux2).m_owner;
							bool wasInstr = caches[1][proc]->lookup(aux2).m_instr;
							if(exclusion_L3_L2)
							{
								//comprobamos que no hay copia en ninguna L1
								bool flag=false;
								for(uint i=0; i<nCores && !flag; i++) {
									if(caches[0][i]->testCacheAccess(aux2,request)) flag=true;
									if(caches[0][i+nCores]->testCacheAccess(aux2, request)) flag=true;
									//if(caches[1][i]->testCacheAccess(aux2,CacheRequestTypeQuick_LD)) flag=true;
								}
									
								if(!flag) {//P 
								//if(0) {
									if(!caches[2][auxBank]->cacheAvail(aux2)) {
										Address aux3= caches[2][auxBank]->cacheProbe(aux2);
										//assert(map_Address_to_L2(aux3).num == bank);
										caches[2][auxBank]->deallocate(aux3);
									}
									if(!caches[2][auxBank]->testCacheAccess(aux2,request))
										caches[2][auxBank]->allocateL2(aux2, owner );
									caches[2][auxBank]->lookup(aux2).m_instr = wasInstr;
								}
							}
							else {//P 
								assert(caches[2][auxBank]->lookup(aux2).m_Sharers.bitMap[proc + nCores * 2]);//P 
								//assert(caches[2][bank]->testCacheAccess(aux2, CacheRequestTypeQuick_LD));//P 
								//P 
								caches[2][auxBank]->lookup(aux2).m_Sharers.del(proc + nCores*2);   //directorio preciso	//P 
								caches[2][auxBank]->m_replacementPolicy_ptr->reusedL1 = caches[1][proc]->lookup(aux2).m_reused;//P 
								caches[2][auxBank]->replacementLower(aux2);//P 
							}//P 
							
							caches[1][proc]->deallocate(aux2); 
							//assert(caches[2][bank]->testCacheAccess(aux2, CacheRequestTypeQuick_LD));
						}
						caches[1][proc]->allocate(aux, thread);
						
						
						//if(exclusion_L3_L2) assert(!caches[2][bank]->testCacheAccess(aux, CacheRequestTypeQuick_LD)) ;
						if(!exclusion_L3_L2)  {//P 
							//assert(caches[2][bank]->testCacheAccess(aux, CacheRequestTypeQuick_LD));//P 
							caches[2][map_Address_to_L2(aux).num]->lookup(aux).m_Sharers.add(proc + nCores*2);   //directorio preciso//P 
						}//P 
					} else {  //if(!caches[1][proc]->testCacheAccess(aux, request)) {
						if(caches[1][proc]->lookup(aux).m_Sharers.bitMap[proc + nCores*isFetch])
							caches[1][proc]->lookup(aux).m_Sharers.del(proc + nCores*isFetch);
					}
				}
			} 
			if(exclusion_L3_L2)//P 
				if(caches[2][bank]->testCacheAccess(*addr, request))  //P 
						caches[2][bank]->deallocate(*addr);//P 
			caches[0][proc + nCores*isFetch]->allocate(*addr, thread);
		} //isPrefetch
		
		
	/************* L2  *************************/
		if(caches[1][proc]->tryCacheAccess(*addr, request, thread)) {
		
			if(DEBUG_CACHE_MGR) { 
				//if(caches[2][0]->addressToCacheSet(*addr) == 17) cerr << "Hit L2" << endl;
			}

			//Asegurar que la L2 sabe que la L1 lo contiene y cual
			if(!isPrefetch) {
				caches[1][proc]->lookup(*addr).m_Sharers.add(proc + nCores*isFetch);
				caches[1][proc]->lookup(*addr).m_instr = isFetch;
			}
			
			if(!exclusion_L3_L2) {//P 
				//assert(caches[2][bank]->testCacheAccess(*addr, CacheRequestTypeQuick_LD));//P 
				caches[2][bank]->lookup(*addr).m_Sharers.add(proc + nCores*isFetch);//P 
				caches[2][bank]->lookup(*addr).m_instr = isFetch;//P 
			} //else assert(!caches[2][bank]->testCacheAccess(*addr, CacheRequestTypeQuick_LD));//P 
			
	/************* L2 hit *************************/
		  	if(g_PREFETCHER && caches[1][proc]->lookup(*addr).m_prefetch && !isPrefetch) accessStream(*addr, thread, true);
		  	
		  	if(isFetch) {
		  		cyclesThread[thread] += latencyL2;
		  		cyclesTotal += latencyL2;
		  	}
		  	else {
		  		cyclesThread[thread] += penalL2;
		  		cyclesTotal += penalL2;
		  	}
		  	
		  	delete auxAdr;
			delete addr;
			return penalL2;
		}
		else {
	/************* L2 miss *************************/
			if(DEBUG_CACHE_MGR) { 
				//		if(caches[2][0]->addressToCacheSet(*addr) == 17) cerr << "Miss L2" << endl;
			}
			if(!caches[1][proc]->cacheAvail(*addr)) {
				Address aux = caches[1][proc]->cacheProbe(*addr);
				//assert(map_Address_to_L2(aux).num == bank);
				bool wasFetch = caches[1][proc]->lookup(aux).m_instr;
				uint owner = caches[1][proc]->lookup(aux).m_owner/g_NUM_SMT_THREADS;
				
				//Si tenemos inclusion entre L1 y L2 y el bloque está por debajo hay que expulsarlo
				if(inclusion_L2_L1 && caches[0][proc + nCores*wasFetch]->testCacheAccess(aux, request)) {
					caches[0][proc + nCores*wasFetch]->deallocate(aux);
					if(!exclusion_L3_L2) {//P 
						assert(caches[2][map_Address_to_L2(aux).num]->lookup(aux).m_Sharers.bitMap[proc + nCores * wasFetch]);//P 
						caches[2][map_Address_to_L2(aux).num]->lookup(aux).m_Sharers.del(proc + nCores*wasFetch);   //directorio preciso//P 
					}//P 
					//assert(!caches[0][proc + nCores*(!wasFetch)]->testCacheAccess(aux, CacheRequestTypeQuick_LD));
				}
				

				if(DEBUG_CACHE_MGR) { 
				//	if(caches[2][0]->addressToCacheSet(*addr) == 17) cerr << "Reemplazo L2" << aux << endl;
				}
				
				if(exclusion_L3_L2) {
					//comprobamos que no hay copia en ninguna L1
					bool flag=false;
					for(uint i=0; i<nCores && !flag; i++) {
						if(caches[0][i]->testCacheAccess(aux,request)) flag=true;
						if(caches[0][i+nCores]->testCacheAccess(aux, request)) flag=true;
						//if(caches[1][i]->testCacheAccess(aux,CacheRequestTypeQuick_LD)) flag=true;
					}
								
					if(!flag) {
						if(!caches[2][map_Address_to_L2(aux).num]->cacheAvail(aux)) {
							Address aux3= caches[2][map_Address_to_L2(aux).num]->cacheProbe(aux);
							//assert(map_Address_to_L2(aux3).num == bank);
							caches[2][map_Address_to_L2(aux3).num]->deallocate(aux3);
						}
						if(!caches[2][map_Address_to_L2(aux).num]->testCacheAccess(aux,request))
							caches[2][map_Address_to_L2(aux).num]->allocateL2(aux, owner);
						caches[2][map_Address_to_L2(aux).num]->lookup(aux).m_instr = wasFetch;
					}
				} 
				else {//P 
					//assert(caches[2][bank]->testCacheAccess(aux, CacheRequestTypeQuick_LD));//P 
					assert(caches[2][map_Address_to_L2(aux).num]->lookup(aux).m_Sharers.bitMap[proc + nCores * 2]);//P 
					caches[2][map_Address_to_L2(aux).num]->lookup(aux).m_Sharers.del(proc + 2*nCores);   //directorio preciso					//P 
					caches[2][map_Address_to_L2(aux).num]->replacementLower(aux);//P 
				}//P 
				caches[1][proc]->deallocate(aux); 
				//assert(caches[2][bank]->testCacheAccess(aux, CacheRequestTypeQuick_LD));
				
			} 
			//assert(!caches[1][proc]->testCacheAccess(*addr, CacheRequestTypeQuick_LD));
			caches[1][proc]->allocate(*addr, thread);
			if(exclusion_L3_L2)
				if(caches[2][bank]->testCacheAccess(*addr, request))
					caches[2][bank]->deallocate(*addr);
			
			caches[1][proc]->lookup(*addr).m_prefetch = isPrefetch;
			caches[1][proc]->lookup(*addr).m_instr = isFetch;
			
			//Asegurar que la L2 sabe que la L1 lo contiene y cual
			if(!isPrefetch) caches[1][proc]->lookup(*addr).m_Sharers.add(proc + isFetch*nCores);

			if(g_PREFETCHER && !isPrefetch) pendingPrefetch = true; 
			
			if(g_PILAS) {
				uint aux2=caches[2][0]->addressToCacheSet(*addr);
				
				if((aux2 && 0xf) == 1) {
					if(!PILAS[0]->tryCacheAccess(*addr, request, thread)) {
						if(!PILAS[0]->cacheAvail(*addr)) {
							Address aux = PILAS[0]->cacheProbe(*addr);
							PILAS[0]->deallocate(aux);
							
						}
						PILAS[0]->allocate(*addr, thread);
					}
					
					if(PILAS[1]->tryCacheAccess(*addr, request, thread)) {
						PILAS[1]->deallocate(*addr);
						assert(!PILAS[2]->tryCacheAccess(*addr, request, thread));
						if(!PILAS[2]->cacheAvail(*addr)) {
							Address aux = PILAS[2]->cacheProbe(*addr);
							PILAS[2]->deallocate(aux);
						}
						PILAS[2]->allocate(*addr, thread);
					}
					else {
						if(!PILAS[2]->tryCacheAccess(*addr, request, thread)) {
							if(!PILAS[1]->cacheAvail(*addr)) {
								Address aux = PILAS[1]->cacheProbe(*addr);
								PILAS[1]->deallocate(aux);
							}
							PILAS[1]->allocate(*addr, thread);
						}
					}
				}
				delete auxAdr;
				delete addr;
				return 30;
			}
			else {
	/************* L3  *************************/
			if(caches[2][bank]->tryCacheAccess(*addr, request, thread)) {
				if(DEBUG_CACHE_MGR) { 
					if(bank==0 && caches[2][0]->addressToCacheSet(*addr) == 17)  {
						cerr << "============== Hit L3" << *addr << endl;
						caches[2][0]->m_replacementPolicy_ptr->printStats(std::cerr);
					}
				}
			
	/************* L3 hit *************************/
				if(!exclusion_L3_L2) {
					
					caches[2][bank]->lookup(*addr).m_Sharers.add(proc + 2*nCores);  //directorio preciso
					
					if(!isPrefetch) caches[2][bank]->lookup(*addr).m_Sharers.add(proc + isFetch * nCores);  //directorio preciso
					caches[2][bank]->lookup(*addr).m_instr = isFetch;
				} else {
					caches[2][bank]->deallocate(*addr);
					
				}
				
				if(pendingPrefetch) accessStream(*addr, thread, true);
				
				if(isFetch) {
					cyclesThread[thread] += latencyL3;
					cyclesTotal += latencyL3;
				}
				else {
					cyclesThread[thread] += penalL3;
					cyclesTotal += penalL3;
				}
				
				delete auxAdr;
				delete addr;
				return penalL3;

			}
			else {
				/*if(!visit[caches[2][bank]->addressToCacheSet(*addr) + 1024*bank]) { 
					totalVisit++; 
					visit[caches[2][bank]->addressToCacheSet(*addr)  + 1024*bank] =1; }*/
				
	/************* L3 miss *************************/
				if(!exclusion_L3_L2) {  //ambos flags deberían ser complementarios --> poner en orden
					if(DEBUG_CACHE_MGR) { 
						if(bank==0 && caches[2][0]->addressToCacheSet(*addr) == 17) { 
							cerr << "miss L3" << *addr << endl;
							caches[2][0]->printSet(std::cerr, 17);
							
							caches[2][0]->m_replacementPolicy_ptr->printStats(std::cerr);
						}
					}
					if(!caches[2][bank]->cacheAvail(*addr)) {
						Address aux= caches[2][bank]->cacheProbe(*addr, thread);
						//assert(map_Address_to_L2(aux).num == bank);
						
						if(DEBUG_CACHE_MGR) { 
							if(bank==0 && caches[2][0]->addressToCacheSet(*addr) == 17) { 
								cerr << "Line for replacement:" << aux << endl;
								
							}
						}
						//Si tenemos inclusion entre L1 y L2 y el bloque está por debajo hay que expulsarlo
						if(caches[2][bank]->lookup(aux).m_Sharers.count() > 0) {
							for(uint i=0; i<NUM_CORES; i++) {
								if(inclusion_L3_L2 && caches[1][i]->testCacheAccess(aux, request)) {
									//assert(entryAux.m_Sharers.bitMap[i]);
									caches[1][i]->deallocate(aux);
								}
								if(inclusion_L3_L2 && caches[0][i + nCores]->testCacheAccess(aux, request)) {
									//assert(entryAux.m_Sharers.bitMap[i]);
									caches[0][i + nCores]->deallocate(aux);
								}
								if(inclusion_L3_L2 && caches[0][i]->testCacheAccess(aux, request)) {
									//assert(entryAux.m_Sharers.bitMap[i]);
									caches[0][i]->deallocate(aux);
								}
							}
						}
						caches[2][bank]->deallocate(aux);						
						//for(uint i=0; i<NUM_CORES; i++) { assert(!caches[1][i]->testCacheAccess(aux, CacheRequestTypeQuick_LD)); }
					} 
					caches[2][bank]->allocateL2(*addr, thread);
					
					caches[2][bank]->lookup(*addr).m_instr = isFetch;
					
					caches[2][bank]->lookup(*addr).m_Sharers.add(proc + 2*nCores);  //directorio preciso
					
					if(!isPrefetch) caches[2][bank]->lookup(*addr).m_Sharers.add(proc + nCores*isFetch);  //directorio preciso
					
					//assert( caches[0][proc + nCores*isFetch]->testCacheAccess(*addr, CacheRequestTypeQuick_LD) && caches[1][proc]->testCacheAccess(*addr, CacheRequestTypeQuick_LD));
						
					if(DEBUG_CACHE_MGR ) { 
						if(bank==0 && caches[2][0]->addressToCacheSet(*addr) == 17) { 
						cerr << "POST:" << endl;
							caches[2][0]->printSet(std::cerr, 17);
							cerr << "miss L3" << *addr << endl;
						}
					}
					
				} //exclusion_L3
				else {
					assert(!caches[2][bank]->testCacheAccess(*addr,request));
				}
				
				if(pendingPrefetch) accessStream(*addr, thread, true);
				
				//assert(caches[2][bank]->testCacheAccess(*addr, CacheRequestTypeQuick_LD));
				
				if(isFetch) {
					cyclesThread[thread] += latencyMem;
		  			cyclesTotal += latencyMem;
		  		}
		  		else {
		  			cyclesThread[thread] += penalMem;
		  			cyclesTotal += penalMem;
		  		}
				LLCMissesThread[thread]++;
				LLCMissesTotal++;
				
				delete auxAdr;
				delete addr;
				return penalMem;
			}  //miss L3
			}  //g_PILAS
		} //miss L2
	}  //miss L1
	delete auxAdr;
	delete addr;
}

void CacheMgr::printStats(ostream& out) {

	for(uint i=0; i<NUM_CORES; i++) {
		caches[0][i + NUM_CORES]->printStats(out);
	}
		for(uint i=0; i<NUM_CORES; i++) {
		caches[0][i]->printStats(out);
	}

	for(uint i=0; i<NUM_CORES; i++) {
		caches[1][i]->printStats(out);
	}
	for(uint i=0; i<g_NUM_L2_BANKS; i++) {
		caches[2][i]->printStats(out);
	}
	
	if(g_PILAS) {
		out << endl<< "Estadísticas PILA0" << endl;
		PILAS[0]->printStats(out);
		out << endl<< "Estadísticas PILA1" << endl;
		PILAS[1]->printStats(out);
		out << endl<< "Estadísticas PILA2" << endl;
		PILAS[2]->printStats(out);
		
		for(uint i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
			out << endl<< "Estadísticas PILA_L1_" << i << endl;
			PILAS_L1[i]->printStats(out);
		}
		
		for(uint i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
			out << endl<< "Estadísticas PILA_L2_" << i << endl;
			PILAS_L2[i]->printStats(out);
		}
	}
	
	out << endl<< "Estadísticas generales CacheMgr" << endl;
	out << "-------------------------------"  << endl;
	for(uint i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
		out << "CacheMgr_executed_instructions_thread_" << i << ":\t" << instrThread[i] << endl;
	}
	out << "CacheMgr_executed_instructions_total:\t" << instrTotal << endl << endl;
	
	for(uint i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
		out << "CacheMgr_cycles_thread_" << i << ":\t" << cyclesThread[i] << endl;
	}
	out << "CacheMgr_cycles_total:\t" << cyclesTotal << endl << endl;
	
	for(uint i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
		out << "CacheMgr_MPKI_thread_" << i << ":\t" << (float)LLCMissesThread[i]/(float)instrThread[i]*1000 << endl;
	}
	out << "CacheMgr_MPKI_total:\t" << (float)LLCMissesTotal/(float)instrTotal *1000 << endl << endl;;
	
	for(uint i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
		out << "CacheMgr_IPC_thread_" << i << ":\t" << (float)instrThread[i]/(float)cyclesThread[i] << endl;
	}
	out << "CacheMgr_IPC_total:\t" << (float)instrTotal/(float)cyclesTotal << endl << endl;
	
	for(uint i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
		out << "CacheMgr_CPI_thread_" << i << ":\t" << (float)cyclesThread[i]/(float)instrThread[i] << endl;
	}
	out << "CacheMgr_CPI_total:\t" << (float)cyclesTotal/(float)instrTotal << endl << endl;
	
}

void CacheMgr::clearStats() {
	
	cerr << "Limpiando las estadisticas de la quick cache..." << endl;
	
	for(uint i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {
		instrThread[i] = 0;
		cyclesThread[i] = 0;
		LLCMissesThread[i] = 0;
	}
	cyclesTotal=0;
	instrTotal=0;
	LLCMissesTotal=0;


}


struct System;
//***************************  STREAMS ****************************************************************

//#define n_streams 32*16

void CacheMgr::actualizaLRUstreams(int i)
{
// cerr << "actualizaLRUstreams " << i	<< endl;
  
  //assert(streams[i]!=NULL);
  
  int aux=streams[i]->LRUpos;
  
  int j=0;
 // cout <<"***************** " << n_streams << " " << streams[i]->state<< endl;
  
    for(j=0; j<n_streams ; j++)
    {
      assert(streams[j]!=NULL && streams[j]->state!=-1);
      //cout <<"xxxxxxxxxxxxxxxxxxxx" << (streams[j]!=NULL) << " " << (streams[j]->state!=-1) << " " << (j!=i) <<  endl;
      streams[j]->LRUpos++;
    }
  
  //  for(j=0; j<n_streams ; j++) if(streams[j]!=NULL) {cerr << "i: " << j << " " << streams[j]->LRUpos << endl;}
}

//asumimos que i es invalido y vamos a allocatarlo e incrementamos todas las otras posiciones
void CacheMgr::actualizaLRUstreamsInv(int i)
{
 //if (m_version==0) cerr << "actualizaLRUstreamsInv " << i	<< endl;
  //int aux=streams[i]->LRUpos;
  
  int j=0;
  for(; j<n_streams ; j++) 
  {
    if(streams[j]!=NULL)
      streams[j]->LRUpos++;
  }
 
    //for(j=0; j<n_streams ; j++) if(streams[j]!=NULL) {cerr << "i: " << j << " " << streams[j]->LRUpos << endl;}
}

//vamos a eliminar i,  decrementamos a sus sucesores
void CacheMgr::actualizaLRUstreamsDel(int i)
{
// cerr << "actualizaLRUstreamsDel " << i	<< endl;
  
  assert(streams[i]!=NULL);
  
  int aux=streams[i]->LRUpos;
  
  int j=0;
  for(; j<n_streams ; j++) if(streams[j]!=NULL && streams[j]->state!=-1 && streams[j]->LRUpos > aux)  streams[j]->LRUpos--;

  streams[i]->LRUpos=0;
  //  for(j=0; j<n_streams ; j++) if(streams[j]!=NULL) {cerr << "i: " << j << " " << streams[j]->LRUpos << endl;}
}


bool CacheMgr::accessStream(Address a, uint proc, bool miss)
{
 
  Address add=a;
  add.makeLineAddress();
  
  uint64 aAux=add.getAddress();
  
  //int nproc= L1CacheMachIDToProcessorNum(node);
  
  //uint proc= node;
  
  
//  cerr << "p:" << nproc << endl;
//   if(g_DEBUG_PREFETCHER)   if(m_version==0 && nproc==4)  cerr << "Entramos en access"<< (miss?" fallo" : " acierto" )<<endl;	
//if(g_DEBUG_PREFETCHER)   cerr << "Entramos en access"<< (miss?" fallo" : " acierto" )<<endl;	
  
  //s_accesos[nproc]++;
  
  int aux;
  ////Stream* streams= stream.streams
  //(Stream*) streams[n_streams]= &(streams.streams);
  int flag=0;
  int i=0;
  
  //if(g_DEBUG_PREFETCHER) if(proc==0)  cerr << "accessStream" << endl;
  
    //for(; i<n_streams && !flag; i++)
    for(; i<n_streams; i++)
    { 
      if(streams[i]!=NULL && streams[i]->state!=-1 && streams[i]->test(aAux, proc) )
      {
        
        switch(streams[i]->state)
        {
          
          case 2:          
          case 3:
           //streams[i]->deg=degrees[streams[i]->nproc];            
              if(g_DEBUG_PREFETCHER) if(proc==0)  cerr << "Stream\t" << i << " en estado " << streams[i]->state<< " aumenta el grado  A:" <<
                    streams[i]->A << " " << aAux <<endl;
              //s_positivos[nproc]++;
              
              streams[i]->deg+= degreesS[degreeIndex[proc]];
              //g_eventQueue_ptr->scheduleEvent(this, 1); 
              //cerr << "encontrado stream valido " << i << endl;
              flag=1;
              
              //ideal[proc]+=degreesS[degree_index[proc]];
            break;
          default:
              break;
       } //switch
        
     } //if valid
    } //for n_streams
    
    if(miss && !flag)
    //if(miss )
    for(i=0; i<n_streams; i++)
    {
      if(streams[i]!=NULL && streams[i]->state>-1 && streams[i]->test(aAux, proc) )
      switch(streams[i]->state)
      {
        case 0:
           if(g_DEBUG_PREFETCHER) if(proc==0) cerr << "Stream\t" << i << " pasa al estado 1 A:" <<
                    streams[i]->A << " " << aAux <<endl;
          if(streams[i]->A==aAux) {flag=1; break; }
           
          streams[i]->dir=streams[i]->A < aAux ? 1 : -1; //establecemos la dir
          streams[i]->last=aAux;  //guardamos la dir para la proxima comparacion
          if (streams[i]->dir==-1) cout << "desc" << endl;
            
       //   if(g_DEBUG_PREFETCHER)   if(m_version==0 && streams[i]->nproc==4) cerr << " dir: " << streams[i]->dir << endl;
            
          streams[i]->state=1;
           
           // cerr << "stream " << i<<" desalocatado2 version:" << m_version << endl ; 
            
          flag=1;
          break;
        case 1:
            
          aux=streams[i]->last < aAux ? 1 : -1;
                                
          if(aux==streams[i]->dir) 
          {
            streams[i]->E=aAux;
            streams[i]->last=aAux;
            
            streams[i]->d=distances[degreeIndex[streams[i]->nproc]];
            
            uint64 daux;

           // if(g_DEBUG_PREFETCHER) if(m_version==0 && nproc==6)cerr << "nproc: " << streams[i]->nproc << " dis: " << distances[degree_index[streams[i]->nproc]]] << " ABS((int)aAux - (int)streams[i]->A) : " << ABS((int)aAux - (int)streams[i]->A) << "  streams[i]->d*RubyConfig::dataBlockBytes(): " << streams[i]->d << " " << RubyConfig::dataBlockBytes() << endl; 
            
            if(ABS((int)aAux - (int)streams[i]->A) < streams[i]->d*RubyConfig::dataBlockBytes())  //no hemos llegado al tamaño de region = distancia
            {
              
              if(g_DEBUG_PREFETCHER) if(proc==0) cerr << "Stream\t" << i << " pasa al estado 2 A:" <<
                  streams[i]->A << " " << aAux  <<endl;
                  
              streams[i]->state=2; 
              //g_eventQueue_ptr->scheduleEvent(this, 1); 

            } else 
            {  //hemos llegado a un tamaño de región igual a d
              
             
             if(g_DEBUG_PREFETCHER) if(proc==0) cerr << "Stream\t" << i << " pasa al estado 3 A:" << 
                      streams[i]->A << " " << aAux  <<endl;
                      
             streams[i]->state=3;
             //g_eventQueue_ptr->scheduleEvent(this, 1); 
              streams[i]->A= streams[i]->E - streams[i]->d * RubyConfig::dataBlockBytes() * streams[i]->dir;
            }
            
            streams[i]->deg=degreesS[degreeIndex[proc]];
            
            //stats
            //ideal[streams[i]->proc]+=streams[i]->deg;
          } 
          else 
          {
            actualizaLRUstreamsDel(i); 
            streams[i]->state=-1; 
            n_streams_activos--; 
           
          }
          //cerr << "stream pasa a estado estable" << endl;
          flag=1;
        break;
        default: 
          break;
      } //switch
    } //for n_streams

    //Ningún stream correspondia, buscamos una entrada invalida
    for(i=0; i<n_streams && !flag && miss; i++) 
      if(streams[i]==NULL  || (streams[i]!=NULL && streams[i]->state==-1))
      {  
        //if(g_DEBUG_PREFETCHER)  if(m_version==0 &&nproc==4)  cerr << "entradica invalida " << a.getAddress() <<endl;
        actualizaLRUstreamsInv(i); 
        //if(streams[i]!=NULL) delete streams[i]; 
         if(g_DEBUG_PREFETCHER) if(proc==0) cerr << "Stream\t" << i  << " creado por el procesador " << proc << " (invalida)" << endl;
          
         //if(g_DEBUG_PREFETCHER)  cerr << "Stream\t" << i  << " creado por el procesador " << nproc << " (invalida)" <<
          //       " [" <<g_system_ptr->getDriver()->getCycleCount(m_version) << "]" << endl;
        //streams[i]=new Stream(aAux, node, degreesS[degree_index[nproc]], distances[degree_index[nproc]], m_version); 
        newStream(i, aAux, proc, degreesS[degreeIndex[proc]], distances[degreeIndex[proc]], proc); 
       
       // for(int j=0; j<n_streams ; j++) if(streams[j]!=NULL) {cerr << " j:" << j << " " << streams[j]->LRUpos << ", ";}
       //cerr << endl;
        n_streams_activos++;
        //cerr << "encontramos invalido" << endl;
        flag=1;
      }
    

    //no hemos encontrado ni entradas validas correspondientes ni invalidas libres -> eliminamos el LRU
   // cerr << "flag: " << flag << " miss: " << miss << endl;
    if(!flag && miss)
    {  
      //if(g_DEBUG_PREFETCHER) cerr << "noflag" << endl;
      for(i=0; i<n_streams && !flag; i++) 
        if(streams[i]->state!=-1 && streams[i]->LRUpos==n_streams_activos-1) 
        {
          //if(g_DEBUG_PREFETCHER)  cerr << "Stream " << i << " es el LRU"<< endl;  
          flag=1; 
        }
        
      if(flag) i--;
     
      actualizaLRUstreams(i);
     
      // for(int j=0; j<n_streams ; j++) if(streams[j]!=NULL) {cerr << " i:" << j << " " << streams[j]->LRUpos << " "<< streams[j]->state <<", ";}
       //cerr << endl;
      
      
      
       // if(g_DEBUG_PREFETCHER) cerr <<"================================= " << i  << endl;
       
        //if(g_DEBUG_PREFETCHER)   cerr << "Posicion " << i << " streams activos: " << n_streams_activos;
        
        //n_streams_activos--;
        //actualizaLRUstreamsDel(i);    
        
        //for(int j=0; j<n_streams ; j++) if(streams[j]!=NULL) {cerr << " y:" << j << " " << streams[j]->LRUpos << " "<< streams[j]->state <<", ";}
        //if(g_DEBUG_PREFETCHER)   cerr << " vamos a expulsar al stream" << i << endl;
      //  delete streams[i];
       
      //if(g_DEBUG_PREFETCHER) if(proc==0) cerr << "Stream\t" << i  << " creado por el procesador " << 
        //      proc << " [" <<g_system_ptr->getDriver()->getCycleCount(0) << "]" << endl;
              
       //if(g_DEBUG_PREFETCHER) cerr << "Stream\t" << i  << " creado por el procesador " << nproc <<  endl;
       
        //streams[i]=new Stream(aAux, node, degreesS[degree_index[nproc]], distances[degree_index[nproc]], m_version); 
        
        
        newStream(i, aAux, proc, degreesS[degreeIndex[proc]], distances[degreeIndex[proc]], proc); 
        
        
          //if(g_DEBUG_PREFETCHER) if(m_version==0 && nproc==4) cerr << "i:" << i <<" ";
        
        flag=1;
        
        //s_eliminados[proc]++;
      
      
    }

    if(!flag && miss) cerr << proc <<" la destruccion de Occidente " << endl, exit(0);
    
    generatePrefetchs(proc);
  
//  cerr << proc <<"access F " << endl;
  
    return true;
} //access

void CacheMgr::newStream(uint i, uint64 a, uint pr, int degr, int dis, int version)
{
//if(g_DEBUG_PREFETCHER) if(pr==0) cerr << "newStream" << endl;

  streams[i]->m_version=version;
  streams[i]->A=a;
  streams[i]->state=0;
  streams[i]->proc=pr;
  streams[i]->nproc=pr;
  streams[i]->E= a + 16*RubyConfig::dataBlockBytes();
  streams[i]->LRUpos=0;
  streams[i]->deg=degr;
  streams[i]->d=dis;
}

bool StreamQuick::test(uint64 a , uint node)
{
         //bool aux=A.getAddress()<a.getAddress() && a.getAddress()<E.getAddress() && node==proc;
         //return aux || (A.getAddress()>a.getAddress() && a.getAddress()>E.getAddress() && node==proc);
  if(A<E) return (a>A && a<E && node==proc);
  else return (a<A && a>E && node==proc);
}

void CacheMgr::generatePrefetchs(uint proc)
{
//if(g_DEBUG_PREFETCHER) cerr << proc <<"generate" << endl;
    //static int i=0;
    //int bar=i;
    int flag=0;
    int i;
    for(i=0; i<n_streams; i++)
    { 
      uint aux;
      if(streams[i]!=NULL) aux=streams[i]->deg;
      
      if(streams[i]!=NULL && (streams[i]->state != -1)) 
        for(uint k=0; k<aux; k++) {
		  if(streams[i]->state==2) 
		  {  
			streams[i]->E+= RubyConfig::dataBlockBytes() * streams[i]->dir;
			if(streams[i]->E ==  streams[i]->A + streams[i]->dir * streams[i]->d * RubyConfig::dataBlockBytes())
			{ streams[i]->state=3;
			 
			  if(g_DEBUG_PREFETCHER) if( streams[i]->proc==0) cerr << "Stream\t" << i <<
				" pasa al estado 3 B:" << streams[i]->A <<endl;
			}
			 
			flag=1;
		  // if(g_DEBUG_PREFETCHER) if(m_version==0) cerr << "a " << g_system_ptr->getDriver()->getCycleCount(m_version) <<  " stream " << i << " que esta en estado " << streams[i]->state << " inserta dir " << streams[i]->last << " para el proc " << streams[i]->proc << " con un grado " << streams[i]->deg<< endl ;
			//n_avances2[streams[i]->nproc]++;
		  }
		  else if(streams[i]->state==3) 
		  {
		   streams[i]->E += RubyConfig::dataBlockBytes() * streams[i]->dir;
		   streams[i]->A += RubyConfig::dataBlockBytes() * streams[i]->dir;
			flag=1;
			//n_avances3[streams[i]->nproc]++;
			if(g_DEBUG_PREFETCHER)  if(proc==0) cerr << "b stream " << i << " que esta en estado " << streams[i]->state << "inserta dir " << streams[i]->last << " para el proc " << streams[i]->proc << endl ;
		  }
		  
		if(flag)
		{
		  Address aux3, aux2, aux=Address(streams[i]->last);
		  //Dirección del siguiente bloque
		  //m_last_addr[m_proc_miss].setAddress( m_last_addr[m_proc_miss].maskLowOrderBits(RubyConfig::dataBlockBits()) + RubyConfig::dataBlockBytes()); 
		  //aux2=m_last_addr[m_proc_miss];      
		  
		  aux2.setAddress(streams[i]->E); 
		  aux3=aux2;
		  
		  aux.makePageAddress();
		  aux2.makePageAddress();
		 
		 
		 //Si la prebúsqueda va a una página distinta, no la queremos 
		 if(aux.getAddress() == aux2.getAddress())
		  {   
		   //buscamos la prebúsqueda en el buffer, si no está la insertamos
		   streams[i]->last=aux3.getAddress();
			
			  //generadas[m_proc_miss]++;
			
		   // if(!buffer.esta(Address(streams[i]->last)) && port.addr!=Address(streams[i]->last)) { 
			  
		   //   cerr << "insertamos2 : " << m_last_addr[m_proc_miss] << endl;
				 if(g_DEBUG_PREFETCHER)  if(streams[i]->nproc==0)  cerr << "stream\t" << i << " prebusca " << streams[i]->state << 
				   " inserta dir " << streams[i]->last << " para el proc " << streams[i]->proc << " con un grado " << streams[i]->deg <<endl ;
			  
			 
			 //streams[i]->dir==1 ? insertadasAsc[streams[i]->nproc]++ : insertadasDesc[streams[i]->nproc]++;
			  
			  //-----buffer.insert(Address(streams[i]->last),streams[i]->proc); 
			  
			  //insertadasPAB[streams[i]->nproc]++;
	
			  //si el puerto está vacio...
			  //if(vacio) getPrefetch();
			  //cerr << "cache"<< endl;
			  access(NULL, true, Address(streams[i]->last), streams[i]->proc);
			  //cerr << "cacheF"<< endl;
			//}
			
			 streams[i]->deg--;
			//if(streams[i]->deg>0) g_eventQueue_ptr->scheduleEvent(this, 1);
			//i= (i==n_streams-1) ? 0 : i+1;
			//return;
			
		  } // if cambio de página
		  else streams[i]->deg=0;
		 } //if flag 
  	 } //for k --> deg
  	 
     //i= (i==n_streams-1) ? 0 : i+1;
     //if(bar==i || flag) break;
    } //while
   // if(g_DEBUG_PREFETCHER) cerr << proc <<"generateF" << endl;


}