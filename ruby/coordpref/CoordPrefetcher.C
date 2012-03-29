#include "CoordPrefetcher.h"
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
#include "XactVisualizer.h"
#include "XactProfiler.h"
#include "Address.h"
#include "RubySlicc_ComponentMapping.h"


CoordPrefetcher::CoordPrefetcher()
 
{
//cerr << "Hola, soy el coordinador Gral de los prefetchers, este es mi constructor " << missesGlobalThisEpoch << endl;
  for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) 
    for(int k=0; k<4096; k++) bloomFilter[j][k].valid=false;
  missesGlobalThisEpoch=0;
}

CoordPrefetcher::~CoordPrefetcher()
{
 0==0;
}

void CoordPrefetcher::wakeup()
{
0==0;
}

void CoordPrefetcher::miss(Address addr, Address pc, int tipo, MachineID node, int firstUse)
{
  //cerr << "Hola, soy el coordinador Gral de los prefetchers, en esta época: " << missesGlobalThisEpoch << endl;
  for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) 
  {  
     bloomFilterEntry aux=bloomFilter[j][bloomBitAddress(addr)]; 
     if(aux.valid && aux.proc==node) m_pol_this_epoch[j]++;
  }
  
  if(++missesGlobalThisEpoch==8192)
  {
    BWC=  (g_system_ptr->getDram(0)->getPattsMetricsBWC());
    BWNO= (g_system_ptr->getDram(0)->getPattsMetricsBWNO());
   
    missesGlobalThisEpoch=0;  
    
    
    
    uint64 *tratadas,  *utiles, tratadasTotal[NPROC], utilesTotal[NPROC];;
    
    
    for(int i=0; i<RubyConfig::numberOfL2Cache(); i++)
    {      
      tratadas=g_system_ptr->getPrefetcher(i)->getTratadas();
      utiles=g_system_ptr->getPrefetcher(i)->getUtiles();
      for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++)
      {
        tratadasTotal[j]+=tratadas[j];
        utilesTotal[j]+=utiles[j];
      }
    }
    for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++)
    {
      ACC[j]=double(utiles[j])/double(tratadas[j]);
    }
    
    evaluateMetrics();
    for(int j=0; j<RubyConfig::numberOfL2CachePerChip(); j++) g_system_ptr->getPrefetcher(j)->pattsDecision(dec);
    
    cout << "prebuscador:\t";
   // for(int j=0; j<RubyConfig::numberOfL2CachePerChip() ; j++) g_system_ptr->getPrefetcher(j)->getPattsMetricsPOL(); 
    
        //for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cout << m_st_base_degree[j] << "\t";      
        for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cout << BWC[j] << " " << BWNO[j] << "\t";      
        cout <<endl;
        for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cout << m_pol_this_epoch [j] << ", " << ACC[j] << "\t";      
        cout <<endl;
   
     for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) m_pol_this_epoch[j]=0;
     
  } //missesGlobalThisEpoch==8192
}

void CoordPrefetcher::evaluateMetrics()
{
  for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++)
  {
    if(ACC[j] < 0.15)  //ACCi=low
    {
      if(BWNO[j] > 75000){ dec[j]=3; continue; }
      if(m_pol_this_epoch[j] > 90) {dec[j]=3; continue;}
      if(BWC[j] < 50000) {dec[j]=2; continue;}
      else {dec[j]=1; continue; }     
    
    } else //ACCi=high
    {
      if(m_pol_this_epoch[j] < 90) { dec[j]=1; continue; }
      else 
        if(BWC[j] < 50000)
        {
          if(BWNO[j] < 75000) {dec[j]=1; continue;}
          else { dec[j]=2; continue; }
        } else 
            if(BWNO[j] < 75000) {dec[j]=2; continue;}
            else {dec[j]=3; continue; } 
       cout << "alarm" << endl;
    }
    
  } //for
}


int CoordPrefetcher::bloomBitAddress(Address addr)
{
   //Hacemos 0:11 xor 12:23 de los bits de la dirección de bloque
   Address aux=addr;
   aux.makeLineAddress();
   
   return aux.bitSelect(0,11) ^ aux.bitSelect(12,23);
   
}

void CoordPrefetcher::bloom(int t, Address a, MachineID core, MachineID owner)
{
  switch(t)
  {
    case 0:
     for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) 
     {  
        bloomFilterEntry aux=bloomFilter[j][bloomBitAddress(a)];
        if(aux.valid && aux.proc==owner) bloomFilter[j][bloomBitAddress(a)].bit=0;
     }
     
      break;
    case 1:
      bloomFilter[L1CacheMachIDToProcessorNum(core)][bloomBitAddress(a)].bit=1;
      bloomFilter[L1CacheMachIDToProcessorNum(core)][bloomBitAddress(a)].proc=owner;
      bloomFilter[L1CacheMachIDToProcessorNum(core)][bloomBitAddress(a)].valid=true;
      
break;
    default:
      cerr << "algo esta jodido en las llamadas al bloomF" << endl;
      exit(1);
    break;
  }
}

void CoordPrefetcher::printStats(ostream& out)
{0==0;

}
void CoordPrefetcher::print(ostream& out) const
{
  out << "[Profiler]";
}