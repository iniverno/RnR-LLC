

/*
 * $Id: Sequencer.h 1.70 2006/09/27 14:56:41-05:00 bobba@s1-01.cs.wisc.edu $
 *
 * Description: 
 *
 */

#include "Global.h"
#include "RubyConfig.h"
#include "Consumer.h"
#include "CacheRequestType.h"
#include "AccessModeType.h"
#include "GenericMachineType.h"
#include "PrefetchBit.h"
#include "Map.h"
#include "Address.h"
#include "CacheMsg.h"
#include "Address.h"
#include "Profiler.h"
#include "CacheProfiler.h"
#include "AddressProfiler.h"
#include "System.h"
#include "Network.h"
#include "PrioHeap.h"
#include "CacheMsg.h"
#include "Driver.h"
#include "Protocol.h"
#include "util.h"
#include "Map.h"
#include "Debug.h"
#include "MachineType.h"
#include "TransactionInterfaceManager.h"
#include "interface.h"
#include "ResponseMsg.h"
#include "RubySlicc_ComponentMapping.h"
#include "RubySlicc_Util.h"
#include "MessageBuffer.h"
#include "AbstractChip.h"

#include "Prefetcher.h"

#include <queue>

#include "Dram.h"

#define DEBUG_DRAM 0
#define DEBUG_WRITE 0


Dram* Dram::ptrDram[8];
Time Dram::L2thisCycle[16];

bool Dram::isAbleMSHR(int tipo)
{
  return tipo ? (demandMSHR.size() < demandMSHRSizeCt) : (prefMSHR.size() < prefMSHRSizeCt);
}

bool Dram::isPresentMSHR(Address addr, int tipo)
{
      for(it2=((tipo<3) ? demandMSHR : prefMSHR).begin(); it2!=((tipo<3) ? demandMSHR : prefMSHR).end(); it2++)
    {
      if((*it2).addr == addr && (*it2).type == tipo) return true;
      
    }
    return false;
}
  
void Dram::insertMSHR(Address addr, int tipo, MachineID node, bool secondMiss)
{
  int tMSHR=(tipo == 3 ||tipo == 4)? 0:1;
   assert(!isPresentMSHR(addr, tipo));
   assert(isAbleMSHR(tMSHR));
   
   if(DEBUG_DRAM  &&  !g_CARGA_CACHE) cout << "petici—n insertada en el MSHR " <<  tipo << " " << addr << endl;
        
   
   dramRequest request;
   
    request.channel=map_Address_to_DirectoryNode(addr);
    request.requestor=node;
    request.addr=addr;
    request.core=node;
    request.write= (tipo==2);
    if(DEBUG_WRITE  &&  !g_CARGA_CACHE && tipo==2) cout << "WRITE! " << addr << endl;
    request.type=tipo;
    request.MSHRTime = g_eventQueue_ptr->getTime();
    request.valid=true;
    request.bank= getBank(addr);
    if(tMSHR) request.demand=true;
    else request.demand=false;
    request.secondMiss = secondMiss;
    
   (tMSHR ? demandMSHR : prefMSHR).push_back(request);

}

void Dram::removeMSHR(Address addr, int tipo)
{ 

  assert(isPresentMSHR(addr, tipo));


    for(it2=(tipo ? demandMSHR : prefMSHR).begin(); it2!=(tipo ? demandMSHR : prefMSHR).end(); ++it2)
    {
      if((*it2).addr == addr ) {(tipo ? demandMSHR : prefMSHR).erase(it2); return; }
    }  
}

dramRequest Dram::getMSHREntry(Address addr, int tipo)
{
  assert(isPresentMSHR(addr, tipo));
    for(it2=(tipo ? demandMSHR : prefMSHR).begin(); it2!=(tipo ? demandMSHR : prefMSHR).end(); it2++)
    {
      if((*it2).addr == addr ) return *it2; 
      
    }   
}

bool Dram::isMSHRReady(int tipo)
{
  return (tipo ? demandMSHR : prefMSHR).size()>0;
}

  // Constructors
  Dram::Dram(AbstractChip* chip_ptr, int version)
  {
    //CHUNGO!
   ptrDram[version]= this;
    
    //MSHR
  
    demandMSHRSizeCt=32;
    prefMSHRSizeCt=32;
    lastL2BankServed=0;
    
    
    prefetchQueueSizeCt=8;
    demandQueueSizeCt=32;
    //el patr—n de acierto est‡ definido como 4+4+7+4+4
    
    readHitBankBusyMask = 0x7F00;  // 0111 1111 0000 0000  - 7^1 4^0 4^0
    writeHitBankBusyMask = 0x7F00;   // 0111 1111 0000 0000  - 7^1 4^0 4^0
    
    if(g_CYCLES_BUS_DRAM==1) readHitBusBusyMask = 0x80000; // 1000 0000 0000 0000 0000 - 4^1 19^0
    else if(g_CYCLES_BUS_DRAM==4) 
         { 
           readHitBusBusyMask = 0x78000; // 0111 1000 0000 0000 0000 - 4^1 15^0
           writeHitBusBusyMask = 0xf00; // 1111 0000 0000 - 
         }
    else cerr << "HAY un error grave en g_CYCLES_BUS_DRAM" << endl;
 
  //el patr—n de fallo est‡ definido como 4+4+7+8+7+4+4
  readMissBankBusyMask = 0x3FFFFF00; // 0011 1111 1111 1111 1111 1111 0000 0000 - 22^1 8^0
  writeMissBankBusyMask = 0x3FFFFF00; // 0011 1111 1111 1111 1111 1111 0000 0000 - 22^1 8^0
  
  if(g_CYCLES_BUS_DRAM==1) readMissBusBusyMask = 0x400000000; //  0100 0000 0000 0000 0000 0000 0000 0000 0000 -  4^1 34^0  //para ocupar el bus 1 ciclo
    else if(g_CYCLES_BUS_DRAM==4) 
         {
           readMissBusBusyMask = 0x3C0000000;  // 0011 1100 0000 0000 0000 0000 0000 0000 0000 -  4^1 30^0
           writeMissBusBusyMask = 0xf000000;  //  1111 0000 0000 0000 0000 0000 0000 -  4^1 34^0
         }
    else cerr << "HAY un error grave en g_CYCLES_BUS_DRAM" << endl;
    
    m_version=version;
    numOfBanks=16;
    logNumOfBanks=4;
    
    
    m_chip_ptr=chip_ptr;
    banks.setSize(numOfBanks);
    for(int i=0; i<numOfBanks; i++) 
    {
      banks[i].bankBusyBitmap=0;
      banks[i].busy=false;
      banks[i].scheduled=false;
    }
    lastBankUsed=0;
    
    srand(version);
    
    //stats
    cyclesBusBusyPerProc.setSize(RubyConfig::numberOfProcsPerChip());
    cyclesBusBusyRatioPerProc.setSize(RubyConfig::numberOfProcsPerChip());
    
    numRequestsQueued.setSize(numOfBanks);
	numDemandsQueued.setSize(numOfBanks);
	numPrefetchsQueued.setSize(numOfBanks);

	numRequestsServed.setSize(numOfBanks);
	numDemandsServed.setSize(numOfBanks);
	numPrefetchsServed.setSize(numOfBanks);

	numPrefetchPageHits.setSize(numOfBanks);
	numDemandPageHits.setSize(numOfBanks);
	
	cyclesDemandService.setSize(numOfBanks);
	cyclesPrefetchService.setSize(numOfBanks);

  	avgLatDemandService.setSize(numOfBanks);
	avgLatPrefetchService.setSize(numOfBanks);
	avgLatService.setSize(numOfBanks);

	demandPageHitRatio.setSize(numOfBanks);
	prefetchPageHitRatio.setSize(numOfBanks);
	pageHitRatio.setSize(numOfBanks);
	
	numSecondMissesServed.setSize(numOfBanks);
	numSecondMissPageHits.setSize(numOfBanks);
	secondMissPageHitRatio.setSize(numOfBanks);
	
	latDemandMin.setSize(numOfBanks);
	latDemandMax.setSize(numOfBanks);
		
	latPrefetchMin.setSize(numOfBanks);
	latPrefetchMax.setSize(numOfBanks);
	
		
	medDemandQueueSize.setSize(numOfBanks);
	medPrefetchQueueSize.setSize(numOfBanks);
		
	maxDemandQueueSize.setSize(numOfBanks);
	maxPrefetchQueueSize.setSize(numOfBanks);
	
	//PattsMetrics
	coresQueued.setSize(numOfBanks);
	for(int i=0; i<numOfBanks; i++) coresQueued[i].setSize(RubyConfig::numberOfProcsPerChip());
	BWC.setSize(numOfBanks);
	BWNO.setSize(numOfBanks);
	
    //inicializamos stats
    clearStats();
    
    //prefMSHR.setSize(0);
    //demandMSHR.setSize(0);
    
    if(!g_QUICK_MEM) g_eventQueue_ptr->scheduleEvent(this, 1);
  }

  // Destructor
  Dram::~Dram(){0;}
  
  char* Dram::binary (uint64 v) {
static char binstr[65] ;
int i ;

binstr[64] = '\0' ;
for (i=0; i<64; i++) { binstr[63-i] = v & 1 ? '1' : '0' ; v >>= 1 ;}
return binstr;
}
  
  // Public Methods
  void Dram::wakeup()
  {
    //cerr << "wakeup DRAM: " << m_version << " " << g_eventQueue_ptr->getTime() << endl;
     if(DEBUG_DRAM &&  !g_CARGA_CACHE ) cerr << "wakeup DRAM: " << g_eventQueue_ptr->getTime() <<" version:" << m_version<< " nm:" << RubyConfig::numberOfMemories() << endl;
    dramRequest req;
    req.valid=false;
        
    //nos llega una peticion por ciclo (de cpu) a cada controlador de memoria 
    if(m_version<RubyConfig::numberOfMemories())
    {
       prefMSHRsize.add(prefMSHR.size());
       
       req= Dram::getRequestFromMSHR(m_version);
       
       if(DEBUG_DRAM  &&  !g_CARGA_CACHE && req.valid)
       {
         cerr << "wakeup (m_version):" << m_version	<< endl;
         cerr << "wakeup (addr):" << req.addr	<< endl;
  		 cerr << "wakeup (requestor):" << req.requestor<< endl;
  		 cerr << "wakeup (valid):" << req.valid<< endl;
  	   }
  	   if(DEBUG_WRITE  &&  !g_CARGA_CACHE && req.valid && req.write)
  	   {
         cerr << "wakeup (m_version):" << m_version	<< endl;
         cerr << "wakeup (addr):" << req.addr	<< endl;
  		 cerr << "wakeup (requestor):" << req.requestor<< endl;
  		 cerr << "wakeup (valid):" << req.valid<< endl;
  		 cerr << "wakeup (MSHRtime):" << req.MSHRTime<< endl;
  		 cerr << "wakeup (Time in MSHR):" << g_eventQueue_ptr->getTime() - req.MSHRTime<< endl;
  		 cerr << "wakeup [now]:" << g_eventQueue_ptr->getTime()<< endl;
  	   }
  	   
       if(req.valid) request(req);
    
     int i,j;
    dramRequest request;
    bool hit;
    
   if(!g_CARGA_CACHE && !(g_eventQueue_ptr->getTime()%freqRatio)) 
   {
    //taux=0;
  if(DEBUG_DRAM &&  !g_CARGA_CACHE ) cerr << "wakeup DRAM "<< m_version << " acciones: " << g_eventQueue_ptr->getTime() << endl;
   
    
    if(DEBUG_DRAM &&  !g_CARGA_CACHE )
    {              
        cout << "bankBusyBitmap: " ;
        for(i=0; i< numOfBanks; i++) cout << banks[i].bankBusyBitmap ;
        
        cout << endl << "Tama–o demandQueue=" ;
        for(i=0; i< numOfBanks; i++) cout <<banks[i].demandQueue.size() << " ";
        
        cout << endl << "Tama–o prefetchQueue=" ;
        for(i=0; i< numOfBanks; i++) cout <<  banks[i].prefetchQueue.size() << " ";
        
        cout << endl << "Pagina abierta: " ;
        for(i=0; i< numOfBanks; i++) cout << banks[i].pageTAG << " " ;
      
      cout << endl <<endl << "busBusyBitmap: " << busBusyBitmap << endl;
      cout << "primera petici—n en el bus: " << bus.top().addr << " de la L2 " << bus.top().requestor << endl;
    }
    
    //Para cada banco insertamos petici—n si toca
    int aux=0;
    for(i=0; i< numOfBanks; i++)
    { 
      banks[i].bankBusyBitmap & 1 ? aux++ : 0;
      banks[i].bankBusyBitmap >>= 1;
    }
    busyBanks.add(aux);
    
    //stats
    cyclesDRAM++;
    busBusyBitmap & 1 ? cyclesBusBusy++ : 0;
       
    busBusyBitmap >>= 1;
    //cout << "despues: \t" << binary(busBusyBitmap) << "\t" << busBusyBitmap << "\t" <<g_eventQueue_ptr->getTime() <<endl;
    
    //tenemos que sacar algo del bus?
    if(bus.size() > 0  && bus.top().wakeUp <= g_eventQueue_ptr->getTime())
    {
      request=bus.top();
      
     // if(request.wakeUp < taux) cout << "temporizaci—n err—nea" << endl, exit(-1);
      //taux=request.wakeUp;
      
      bus.pop();
      
      if(DEBUG_DRAM  &&  !g_CARGA_CACHE) cout << "petici—n lista: " <<  request.addr << endl;
      if(DEBUG_WRITE  &&  !g_CARGA_CACHE && request.write)  cout << "Ready write: " <<  request.addr << endl;
      if(DEBUG_WRITE  &&  !g_CARGA_CACHE && request.write) cout << "a:" << g_eventQueue_ptr->getTime() - request.queueTime << " " << g_eventQueue_ptr->getTime() << " " << request.wakeUp << endl;
      
      //read request has to send the data to the LLC
      if(!request.write)
      {
      
      //podemos mandar el dato a la L2!
      
        ResponseMsg out_msg;
              
        (out_msg).m_Address = request.addr;
              
        //CAMBIAR PARA A„ADIR ESCRITURA!!!
        (out_msg).m_Type = CoherenceResponseType_DATA;
        (out_msg).m_MessageSize = MessageSizeType_Data;
        (out_msg).m_RequestorMachId = request.requestor;
        (((out_msg).m_Destination).add((map_Address_to_L2(request.addr))));
        
       // if(!g_CARGA_CACHE) cout << "a:" << g_eventQueue_ptr->getTime() - request.queueTime << " " << g_eventQueue_ptr->getTime() << " " << request.wakeUp << endl;
       
        if(DEBUG_DRAM  &&  !g_CARGA_CACHE) cout << "petici—n lista: " <<  request.addr << endl;
        
        DEBUG_SLICC(MedPrio, "DramWakeup (sent message): ", out_msg);
        DEBUG_SLICC(MedPrio, "DramWakeup (L2 destination): ", map_Address_to_L2Node(request.addr));
        
        //m_chip_ptr->m_Directory_dramToDirQueue_vec[0]->enqueue(out_msg, 1);
        if(request.demand)m_chip_ptr->m_L2Cache_responseToL2CacheQueue_vec[map_Address_to_L2Node(request.addr)]->enqueue(out_msg, 1); 
        
        else m_chip_ptr->m_L2Cache_prefResponseToL2CacheQueue_vec[map_Address_to_L2Node(request.addr)]->enqueue(out_msg, 1); 
      }
    }       
    
     if(g_VARIANTE==13) PattsMetrics();
    
    
    //stats
   for(i=0; i< numOfBanks; i++)
    {
     maxDemandQueueSize[i]<banks[i].demandQueue.size() ? maxDemandQueueSize[i]=banks[i].demandQueue.size() : 0;
     maxPrefetchQueueSize[i]<banks[i].prefetchQueue.size() ? maxPrefetchQueueSize[i]=banks[i].prefetchQueue.size() : 0;
     
     medDemandQueueSize[i]+=banks[i].demandQueue.size();
     medPrefetchQueueSize[i]+=banks[i].prefetchQueue.size();
    }
    
 }//dominio 1/4 
   
   prefQueueBank0.add(banks[0].prefetchQueue.size());
   prefQueueBank1.add(banks[1].prefetchQueue.size());
   
   int barrierBank=lastBankUsed;
    //i=firstBank();    
    //j=i;
    j = -1;
   bool reqServed=false;
    int reqType=-1;    
    Time demTime=0, prefTime=0;  //para averiguar quiŽn lleg— antes al controlador
    
  
  bool alldemands=false;
  //cerr << "wakeup DRAM: " << g_eventQueue_ptr->getTime() << endl;
  bool oldestTry = false;
  while(!reqServed && j!=barrierBank)
  { 
    	//cerr << "bucle achedule" << endl;
    reqType=-1;
    
    //This first part of the conditional tries to schedule the oldest queued request
    if(!oldestTry) 
    {
    	oldestTry = true;
    	Time oldestTime = 0;
    	int oldestIndex = -1;
    	for(int auxIndex=0; auxIndex < numOfBanks; auxIndex++) 
    	{
    		if(banks[auxIndex].demandQueue.size()>0)
    		{
    			Time auxTime = banks[auxIndex].demandQueue.front().queueTime;
    			if(auxTime < oldestTime || oldestTime==0)
    			{
    				oldestTime = auxTime;
    				oldestIndex = auxIndex;
    			}
    		}
		}
		if(oldestIndex != -1)
		{
			reqType = 1;
			i = oldestIndex;
			j=(oldestIndex==numOfBanks-1)?0:oldestIndex+1;
		} 
		else 
		{
			i=firstBank();    
    		j=i;
    		continue;
		}
	}
	else 
	{
    
		while(reqType==-1 && j!=barrierBank && !alldemands )
		{  
		  //cout << "buc 1a barrier" << barrierBank << " i: " << i << "  j: " << j << endl;
		  if(banks[j].demandQueue.size()>0) { reqType=1; i=j; j=(j==numOfBanks-1)?0:j+1; goto salida1; }
		  
		 //siguiente banco % #bancos  
		  j=(j==numOfBanks-1)?0:j+1;
		  if(j==barrierBank) alldemands=true;
		  //cout << "buc 1b barrier" << barrierBank << " i: " << i << "  j: " << j << endl;
		}
		
		if(j==barrierBank) j=(j==numOfBanks-1)?0:j+1;
		
		while(reqType==-1)
		{
		  //cout << "buc 2a barrier" << barrierBank << " i: " << i << "  j: " << j << endl;
		  //cout << "i: " << i << " j: " << j << "size: " << banks[j].prefetchQueue.size() << endl;
		  if(banks[j].prefetchQueue.size()>0) { reqType=0; i=j; j=(j==numOfBanks-1)?0:j+1; goto salida1; }
		  //siguiente banco % #bancos  
		  j=(j==numOfBanks-1)?0:j+1;
		  if(j==barrierBank) break;
		  //cout << "buc 2b barrier" << barrierBank << " i: " << i << "  j: " << j << endl;    
		}
		
		if(reqType==-1 || j==barrierBank) { g_eventQueue_ptr->scheduleEvent(this, 1); return; }
     }
     
     salida1:
   
     
      //-------  Hasta aqu’ el c—digo que marca la prioridad
      
      request=(reqType ? banks[i].demandQueue : banks[i].prefetchQueue).front();
      
      //comparamos la p‡gina que abri— el banco la œltima vez con la de la petici—n que vamos a servir
     //if(i==2) cout << "req.addr: " << getPage(request.addr.getAddress()) << "  bank.pag: " << banks[i].pageTAG << endl;     
      hit= getPage(request.addr.getAddress())==banks[i].pageTAG;      
      
     // if(DEBUG_DRAM  &&  !g_CARGA_CACHE)cout << "antes: \t\t" << binary(busBusyBitmap) << endl;
      
   
       if(!(busBusyBitmap & (hit ? (request.write ? Dram::writeHitBusBusyMask : Dram::readHitBusBusyMask) \
       		: (request.write ? Dram::writeMissBusBusyMask : Dram::readMissBusBusyMask)))) //si el bus puede estar libre para la petici—n elegida
        if(!(banks[i].bankBusyBitmap & (hit ? (request.write ? Dram::writeHitBankBusyMask : Dram::readHitBankBusyMask) \
        		: (request.write ? Dram::writeMissBankBusyMask : Dram::readMissBankBusyMask)))) //si el banco puede estar libre para la petici—n elegida
        {   
        
        	//cerr << "core: " << request.core << "\t" << " bank: "<< i << "\t" << (request.write ? "W" : "R") <<  (hit ? "\thit" : "\tmiss") << endl; 
          //la petici—n puede ser servida
          //actualizamos tablas de ocupaci—n
          if(request.write) busBusyBitmap |= (hit ? writeHitBusBusyMask : writeMissBusBusyMask);
          else busBusyBitmap |= (hit ? readHitBusBusyMask : readMissBusBusyMask);
          
           //if(DEBUG_DRAM &&  !g_CARGA_CACHE)
           //cout << "despues: \t" << binary(busBusyBitmap) << "\t" << busBusyBitmap << endl;
          
          if(request.write) banks[i].bankBusyBitmap |= (hit ? writeHitBankBusyMask : writeMissBankBusyMask); 
          else banks[i].bankBusyBitmap |= (hit ? readHitBankBusyMask : readMissBankBusyMask);          
          
          //actualizamos la p‡gina abierta en el banco
          if(!hit) banks[i].pageTAG= getPage(request.addr.getAddress());  
                  
         //PattsMetrics
         //coresQueued[i][L1CacheMachIDToProcessorNum(request.core)]--;
                   
          (reqType ? banks[i].demandQueue : banks[i].prefetchQueue).pop_front();
          
          //Atenci—n si cambiamos la temporizaci—n!!!!
          if(!request.write) request.wakeUp= g_eventQueue_ptr->getTime() + freqRatio* (hit ? 19 : 34);
          else request.wakeUp= g_eventQueue_ptr->getTime() + freqRatio* (hit ? 12 : 28);
          
           //metemos la petici—n en el bus
           //********************************************************
         
         //las peticiones est‡n ordenadas porque el bus es una cola con prioridad
           bus.push(request); 
           
           //stats
          if(!request.write) cyclesBusBusyPerProc[L1CacheMachIDToProcessorNum(request.core)]+=g_CYCLES_BUS_DRAM;
          
          //*********************************
          //stats
          if(hit) (reqType ? numDemandPageHits[i] : numPrefetchPageHits[i])++;  //num aciertos pag
          if(hit && request.secondMiss) numSecondMissPageHits[i]++;  //num aciertos pag
          
          (reqType ? numDemandsServed[i] : numPrefetchsServed[i])++; //num servicios
          if(request.secondMiss) numSecondMissesServed[i]++;
          
          //cout << "lat Servicio:" <<  request.wakeUp - request.queueTime <<endl;
          uint64 aux=request.wakeUp - request.queueTime;
          uint64 aux2=reqType ? latDemandMax[i] : latPrefetchMax[i];
          
          (reqType ? latDemandMax[i] : latPrefetchMax[i])= (aux2>aux ? aux2 : aux);
          
          aux2=reqType ? latDemandMin[i] : latPrefetchMin[i];	
          (reqType ? latDemandMin[i] : latPrefetchMin[i])= (aux2<aux ? aux2 : aux);
          
          (reqType ? cyclesDemandService[i] : cyclesPrefetchService[i])+= aux; //latencia servicio
          
          reqServed=true;
          lastBankUsed=i;	
          
          DEBUG_SLICC(MedPrio, "DramController request programmed (address): ", request.addr);
          DEBUG_SLICC(MedPrio, "DramController request programmed (ReqType): ", reqType);
          DEBUG_SLICC(MedPrio, "DramController request programmed (hit): ", hit);
          DEBUG_SLICC(MedPrio, "DramController request programmed (queue): ", g_eventQueue_ptr->getTime());
          DEBUG_SLICC(MedPrio, "DramController request programmed (wakeup): ", request.wakeUp);
          DEBUG_SLICC(MedPrio, "DramController request programmed (bank): ", i);
          
        
       }
   } //while reqServed    
      //siguiente banco % #bancos  
    
  g_eventQueue_ptr->scheduleEvent(this, 1);
 }//valid memory
  //  cout<< "  dram::wakeup" << endl;
} //wakeup


void Dram::upgrade(Address addr)
{
 int bankMem=getBank(addr);
    for(it=banks[bankMem].prefetchQueue.begin(); it!=banks[bankMem].prefetchQueue.end(); it++)
    {
      if(it->addr == addr )
      {
        dramRequest request=*it;
        it=banks[bankMem].prefetchQueue.erase(it);
        banks[bankMem].demandQueue.push_back(request);
        DEBUG_SLICC(MedPrio, "DramUpgrade: Prefetch found in prefetchQueue and now upgraded in Bank ", bankMem);
        return;
      }
    }
    
  static int nl2=RubyConfig::numberOfL2CachePerChip();

//MSHR
  
  int bankL2=map_Address_to_L2Node(addr);
  
  if(ptrDram[bankL2]->isPresentMSHR(addr,0)) 
  { 
    dramRequest r= ptrDram[bankL2]->getMSHREntry(addr,0);
    
    ptrDram[bankL2]->removeMSHR(addr,0);

    ptrDram[bankL2]->insertMSHR(addr,1, r.core);
  }

  DEBUG_SLICC(MedPrio, "DramUpgrade: Prefetch not found", 0);
}

bool Dram::i_isAble(Address addr, int tipo)
{
  
  return ((*(m_chip_ptr->m_L2Cache_dram_vec[map_Address_to_DirectoryNode(addr)]))).isAble( addr,  tipo);
}


bool Dram::isAble(Address addr, int tipo)
{
  int bank= getBank(addr);
   switch(tipo)
   {
    case 1:
    case 2:  //demandas
    case 5:  //los upgrades se convertir‡n en demanda
      return banks[bank].demandQueue.size() < demandQueueSizeCt; 
      break;
        
    case 3:
    case 4:  //prebusquedas
   
      return banks[bank].prefetchQueue.size() < prefetchQueueSizeCt;
    break;
    
    default:
      break;
  }
}


void Dram::i_request(Address addr, int tipo, MachineID node, MachineID core, bool secondMiss)
{ 
  if(DEBUG_DRAM  &&  !g_CARGA_CACHE)
  {
    cerr << "i_request (addr):" << addr<< endl;
    cerr << "i_request (tipo):" << tipo<< endl;
    cerr << "i_request (node):" << node<< endl;
    cerr << "i_request (core):" << core<< endl;
    cerr << "i_request (secondMiss):" << secondMiss<< endl;
  }
  insertMSHR(addr, tipo, core, secondMiss);
  
  g_eventQueue_ptr->scheduleEvent(this, 1);
}

void Dram::request(Address addr, int tipo, MachineID node, MachineID core)
{
    
    if(g_CARGA_CACHE)
    {
         ResponseMsg out_msg;
              
        (out_msg).m_Address = addr;
        
        //CAMBIAR PARA A„ADIR ESCRITURA!!!
        (out_msg).m_Type = CoherenceResponseType_DATA;
        (out_msg).m_MessageSize = MessageSizeType_Data;
        (out_msg).m_RequestorMachId = node;
        // if(!g_CARGA_CACHE) cout << "a:" << g_eventQueue_ptr->getTime() - request.queueTime << " " << g_eventQueue_ptr->getTime() << " " << request.wakeUp << endl;       
       
        //m_chip_ptr->m_Directory_dramToDirQueue_vec[0]->enqueue(out_msg, 1);
        m_chip_ptr->m_L2Cache_responseToL2CacheQueue_vec[map_Address_to_L2Node(addr)]->enqueue(out_msg, 1);
        return;
    }
    
    //cout << "DRAM" << m_version << endl;
    if(DEBUG_DRAM &&  !g_CARGA_CACHE) cout << "request: " << addr << " " << node << "tipo: " << tipo << endl; 
    
    
    int bank= getBank(addr);
    
    dramRequest request;
    request.requestor=node;
    request.addr=addr;
    request.core=core;
    Time now=g_eventQueue_ptr->getTime()+1;
    
    request.queueTime=now-1;  //for stats
    
    if(addr.getAddress()==0x392afd080)
    {
      cout << addr <<endl;
      cout << tipo << endl;
      cout << node << " " << core << endl;
      cout << bank << endl;
      cout << now << endl;
    }
    
    DEBUG_SLICC(MedPrio, "DramRequest (addr): ", addr);
    DEBUG_SLICC(MedPrio, "DramRequest (tipo): ", tipo);
    DEBUG_SLICC(MedPrio, "DramRequest (node): ", node);
    DEBUG_SLICC(MedPrio, "DramRequest (core): ", core);
    DEBUG_SLICC(MedPrio, "DramRequest (bank): ", bank);
    DEBUG_SLICC(MedPrio, "DramRequest (queueTime): ", now);
    
    
    switch(tipo)
    {
      case 1:
        coresQueued[bank][L1CacheMachIDToProcessorNum(core)]++;
      case 2:  //demandas
        request.write=(tipo==2);
        
        request.demand=true;
        banks[bank].demandQueue.push_back(request);
        numDemandsQueued[bank]++;  //stats
        break;
        
      case 3:
    	coresQueued[bank][L1CacheMachIDToProcessorNum(core)]++;
      case 4:  //prebusquedas
      //PattsMetrics
  
    
        request.demand=false;
        banks[bank].prefetchQueue.push_back(request);
        numPrefetchsQueued[bank]++;  //stats
        break;
      case 5:  //ug prefetch
      //PattsMetrics
        
        upgrade(request.addr);
        break;
      default:
        break;
    }
    
    //programamos la petici—n para un ciclo de bus (modulo freqRatio)
   
    
    //while(now%freqRatio) now++;    
    //optimizacion si freqRatio==4  (asi eliminamos el mod)

    
    g_eventQueue_ptr->scheduleEvent(this, 1); 
    
  } 
  
  
  void Dram::request(dramRequest req)
{
    dramRequest request=req;
    
    if(g_CARGA_CACHE)
    {
         ResponseMsg out_msg;
              
        (out_msg).m_Address = request.addr;
        
        //CAMBIAR PARA A„ADIR ESCRITURA!!!
        (out_msg).m_Type = CoherenceResponseType_DATA;
        (out_msg).m_MessageSize = MessageSizeType_Data;
        (out_msg).m_RequestorMachId = request.core;
        // if(!g_CARGA_CACHE) cout << "a:" << g_eventQueue_ptr->getTime() - request.queueTime << " " << g_eventQueue_ptr->getTime() << " " << request.wakeUp << endl;       
       
        //m_chip_ptr->m_Directory_dramToDirQueue_vec[0]->enqueue(out_msg, 1);
        m_chip_ptr->m_L2Cache_responseToL2CacheQueue_vec[map_Address_to_L2Node(request.addr)]->enqueue(out_msg, 1);
        return;
    }
    
    //cout << "DRAM" << m_version << endl;
    if(DEBUG_DRAM &&  !g_CARGA_CACHE) cout << "request: " << request.addr << " " << request.core << "tipo: " <<request.type << endl; 
    
    
    int bank= getBank(request.addr);
 
    Time now=g_eventQueue_ptr->getTime()+1;
    
    request.queueTime=now-1;  //for stats
    
   
    DEBUG_SLICC(MedPrio, "DramRequest (addr): ", request.addr);
    DEBUG_SLICC(MedPrio, "DramRequest (tipo): ", request.type);
    DEBUG_SLICC(MedPrio, "DramRequest (core): ", request.core);
    DEBUG_SLICC(MedPrio, "DramRequest (bank): ", bank);
    DEBUG_SLICC(MedPrio, "DramRequest (queueTime): ", now);
    
    
    switch(request.type)
    {
      case 1:
		coresQueued[bank][L1CacheMachIDToProcessorNum(request.core)]++;
      case 2:  //demandas
                
        banks[bank].demandQueue.push_back(request);
        numDemandsQueued[bank]++;  //stats
        break;
        
      case 3:
      case 4:  //prebusquedas
      //PattsMetrics
  
    coresQueued[bank][L1CacheMachIDToProcessorNum(request.core)]++;
    
        
        banks[bank].prefetchQueue.push_back(request);
        numPrefetchsQueued[bank]++;  //stats
        break;
      case 5:  //ug prefetch
      //PattsMetrics
       assert(1==0);
        break;
      default:
        break;
    }
    
    //programamos la petici—n para un ciclo de bus (modulo freqRatio)
   
    
    //while(now%freqRatio) now++;    
    //optimizacion si freqRatio==4  (asi eliminamos el mod)

  
  } 
 /*  int Dram::nextBank(int bank)
  {
    
    //round-robin fashion
    (i==numOfBanks-1)?0:i+1;
  
    return lastBankUsed;
    
  }*/
  
  int Dram::firstBank()
  {
    //round-robin fashion
    lastBankUsed= (lastBankUsed== numOfBanks-1) ? 0 : lastBankUsed+1;
  
    return lastBankUsed;   
  }
  
  uint64 Dram::getBank(Address addr)
  {
    if(g_GROUP_L2BANKS_TO_MEM) return addr.bitSelect(14,  14+logNumOfBanks-1);
    else return addr.bitSelect(13,  13+logNumOfBanks-1);    
    //Vamos a probar asignar el banco de manera aleatoria
    //return rand() % 16;
  }
  
  uint64 Dram::getPage(uint64 addr)
  {    
    //return addr >> 13+logNumOfBanks;
    //uint64 mask= ~(((~0)>>12)<<12);
    
    //return (addr>>RubyConfig::dataBlockBits()) & mask;
    return addr >> 12;
  }
    
  void Dram::PattsMetrics()
  {
    dramRequest req;
    int coreServed, aux;
    
    for(int i=0; i<numOfBanks; i++)
    {
      if(banks[i].demandQueue.size()>0) req=banks[i].demandQueue.front();
      else if(banks[i].prefetchQueue.size()>0) req=banks[i].prefetchQueue.front();
      else continue;
      BWC[L1CacheMachIDToProcessorNum(req.core)]++;
      for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++)
        if((coresQueued[i][j] - (int)(j==L1CacheMachIDToProcessorNum(req.core))) >0) BWNO[j]++;
    }
  }	
  
  Vector<int> Dram::getPattsMetricsBWC()
  { Vector <int> aux (BWC); for(int i=0; i<numOfBanks; i++) BWC[i]=0; return aux;
  }
  
  Vector<int> Dram::getPattsMetricsBWNO()
  { Vector <int> aux (BWNO); for(int i=0; i<numOfBanks; i++) BWNO[i]=0; return aux;
  }
  
  void Dram::printStats(ostream& out)
  {
     out << "prefMSHRsize : " << prefMSHRsize << endl;
    out << "DRAM " << m_version << endl;
    out << "--------------" << endl;
    for(int i=0; i<numOfBanks; i++)
    {
      numRequestsQueued[i]=numDemandsQueued[i] + numPrefetchsQueued[i];
      numRequestsServed[i]=numDemandsServed[i] + numPrefetchsServed[i];
      
      if(numDemandsServed[i]) avgLatDemandService[i]= (double)cyclesDemandService[i]/ (double)numDemandsServed[i];
      if(numPrefetchsServed[i])avgLatPrefetchService[i]= (double)cyclesPrefetchService[i]/ (double)numPrefetchsServed[i];
      
      if(numRequestsServed[i]) avgLatService[i]= (double)(cyclesPrefetchService[i]+cyclesDemandService[i])/  (double)numRequestsServed[i];

	  if(numDemandsServed[i]) demandPageHitRatio[i]=(double) numDemandPageHits[i] / (double)numDemandsServed[i];
	  if(numPrefetchsServed[i]) prefetchPageHitRatio[i]= (double)numPrefetchPageHits[i] / (double)numPrefetchsServed[i];
	  if(numRequestsServed[i]) pageHitRatio[i]= (double)(numPrefetchPageHits[i]+numDemandPageHits[i]) / (double)numRequestsServed[i];	
	  if(numSecondMissesServed[i]) secondMissPageHitRatio[i]= (double)numSecondMissPageHits[i] / (double)numSecondMissesServed[i];	
	  
	  
	  medDemandQueueSize[i]= (double)(medDemandQueueSize[i]) / (double)cyclesDRAM;
	  medPrefetchQueueSize[i]= (double)(medPrefetchQueueSize[i]) / (double)cyclesDRAM;
    
    }
    for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) cyclesBusBusyRatioPerProc[i]= cyclesBusBusyPerProc[i] / (double)cyclesDRAM;
    
    out << "bus busy ratio: " <<  cyclesBusBusy / (double)cyclesDRAM << endl << endl;
    out << "bus busy cycles: " <<  cyclesBusBusy<< endl << endl;
    
    double aux=0;
    uint64 aux2=0;
    for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) {aux+=cyclesBusBusyRatioPerProc[i]; aux2+=cyclesBusBusyPerProc[i]; }
    out << "bus busy ratio per PROC: " << aux2 << " -- " << aux << " -- "  <<  cyclesBusBusyRatioPerProc << endl;
    out << "busy banks: " << busyBanks << endl;
   
    out << "prefQueueBank0: " << prefQueueBank0 << endl;
    
     out << "prefQueueBank1: " << prefQueueBank1 << endl;    
    
    out << "numRequestsQueued: " << numRequestsQueued << endl;
    out << "numDemandsQueued: " << numDemandsQueued << endl;
    out << "numPrefetchsQueued: " << numPrefetchsQueued << endl<< endl;
    
    out << "numRequestsServed: " << numRequestsServed << endl;
    out << "numDemandsServed: " << numDemandsServed << endl;
    out << "numPrefetchsServed: " << numPrefetchsServed << endl<< endl;
    
    out << "avgLatService: " << avgLatService << endl;
    out << "avgLatDemandService: " << avgLatDemandService << endl;
    out << "avgLatPrefetchService: " << avgLatPrefetchService << endl << endl;
    
    out << "pageHitRatio: " << pageHitRatio << endl;
    out << "demandPageHitRatio: " << demandPageHitRatio << endl;
    out << "prefetchPageHitRatio: " << prefetchPageHitRatio << endl<< endl;
    
    out << "secondMissPageHitRatio" << secondMissPageHitRatio << endl;
    out << "numSecondMissesServed" << numSecondMissesServed << endl;
    out << "numSecondMissPageHits" << numSecondMissPageHits << endl << endl;
    
    out << "latDemandMin: " << latDemandMin << endl;
    out << "latDemandMax: " << latDemandMax << endl;
    out << "latPrefetchMin: " << latPrefetchMin << endl;
    out << "latPrefetchMax: " << latPrefetchMax << endl<< endl;
    
    out << "demandQueue max size: " << maxDemandQueueSize << endl;
    out << "demandQueue med size: " << medDemandQueueSize << endl<< endl;
    out << "prefetchQueue max size: " << maxPrefetchQueueSize << endl ;
    out << "prefetchQueue med size: " << medPrefetchQueueSize << endl;
    
  } 
  void Dram::clearStats()
  {
     for(int i=0; i< numOfBanks; i++)
     {
        
		numDemandsQueued[i]=0;
		numPrefetchsQueued[i]=0;

		numDemandsServed[i]=0;
		numPrefetchsServed[i]=0;

		numPrefetchPageHits[i]=0;
		numDemandPageHits[i]=0;

		cyclesDemandService[i]=0;
		cyclesPrefetchService[i]=0;
		
		latDemandMin[i]=1000;
		latDemandMax[i]=0;
		
		latPrefetchMin[i]=1000;
		latPrefetchMax[i]=0;
		
		maxDemandQueueSize[i]=0;
		maxPrefetchQueueSize[i]=0;
		
		medDemandQueueSize[i]=0;
		medPrefetchQueueSize[i]=0;
	}
	for(int i=0; i<RubyConfig::numberOfProcsPerChip(); i++) cyclesBusBusyPerProc[i]=0;
	
	cyclesDRAM=0;
	cyclesBusBusy=0;
  } 
  void Dram::print(ostream& out) const{0;} 
  void Dram::printConfig(ostream& out){0;} 
  
  
dramRequest Dram::getRequestFromMSHR(int v)
{

//cerr << " int proc = SIMICS_get_proc_no(mem_trans->s.ini_ptr); " << v << endl;
  dramRequest req;
  Time now= g_eventQueue_ptr->getTime();
  static int l2=0;
  static int nl2=RubyConfig::numberOfL2CachePerChip();
  int i;
 
  int aux;
  //demandas
  for(i=0; i< nl2; i++)
  {
    aux=(l2+i)%nl2;
    if(now!=L2thisCycle[aux] && ptrDram[aux]->isMSHRReady(1) && !(ptrDram[aux]->demandMSHR.empty()))
    {
      req=ptrDram[aux]->demandMSHR.front();
      if(req.channel==v)    //la peticion primera es para este canal
        if(ptrDram[v]->isAble(req.addr, req.type))   //el banco tiene sitio en sus colas
        { 
         L2thisCycle[aux]=now;
 	  	 
  		 ptrDram[aux]->demandMSHR.pop_front();
  		 
  		 if(req.type==5) 
  		   {ptrDram[v]->upgrade(req.addr);
  		    req.valid=false;}
         return  req;
       }
     }
  }
  
  //prebusquedas
  for(i=0; i< nl2; i++)
  {
    aux=(l2+i)%nl2;
    if(now!=L2thisCycle[aux] && ptrDram[aux]->isMSHRReady(0) && !(ptrDram[aux]->prefMSHR.empty()))
    {
      req=ptrDram[aux]->prefMSHR.front();
       if(req.channel==v) 
         if(ptrDram[v]->isAble(req.addr, req.type))
         {        
            L2thisCycle[aux]=now;
		  
		    ptrDram[aux]->prefMSHR.pop_front();
            return  req;
         }
     }
  }
  req.valid=false;
  return  req;
}

