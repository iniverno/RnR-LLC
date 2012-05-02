/*
 * $Id: Sequencer.h 1.70 2006/09/27 14:56:41-05:00 bobba@s1-01.cs.wisc.edu $
 *
 * Description: 
 *
 */

#ifndef DRAM_H
#define DRAM_H

#include "Global.h"
#include "RubyConfig.h"
#include "Consumer.h"
#include "CacheRequestType.h"
#include "AccessModeType.h"
#include "GenericMachineType.h"
#include "PrefetchBit.h"
#include "Map.h"
#include "Address.h"
#include <queue>
#include <list>
#include <vector>
#include "Histogram.h"

//#include <priority_queue>

class DataBlock;
class AbstractChip;
class CacheMsg;
class Address;
class MachineID;
 



struct dramRequest
{
  Address addr;  
  MachineID requestor; //para insertar en la máquina adecuada
  Time wakeUp;  //para retirar de la cola del bus
  Time MSHRTime; //time the request is in the MSHR
  Time queueTime;  //para estadisticas (momento en el que es encolada)
  bool demand;  //demanda o prebúsqueda
  MachineID core;  //core provocador
  bool write;
  int type;
  int channel;
  bool valid;
  int bank;
};


struct Bank
{
  list <dramRequest> demandQueue;
  list <dramRequest> prefetchQueue;
  uint64 pageTAG;
  
  bool busy;
  bool hit;
  bool scheduled;
  uint64 bankBusyBitmap;
 
};

class mycomparison
{
  
public:
 
  bool operator() (const dramRequest& lhs, const dramRequest&rhs) const
  {
   return lhs.wakeUp > rhs.wakeUp;
  }
};



class Dram : public Consumer {
public:
  // Constructors
  Dram(AbstractChip* chip_ptr, int version);

  // Destructor
  ~Dram();
  
  // Public Methods
  void wakeup(); // Used only for deadlock detection 
 
   uint64 getPage(uint64 addr);
  void request(Address addr, int tipo, MachineID node, MachineID core);
  void request(dramRequest req);
  void i_request(Address addr, int tipo, MachineID node, MachineID core);
  
  bool isAble(Address, int);  //nos dira si el banco al que queremos insertar está lleno o no
   bool i_isAble(Address, int);  //nos dira si el banco al que queremos insertar está lleno o no
   
  void printStats(ostream& out);
  void clearStats();
  void print(ostream& out) const;
  static void printConfig(ostream& out);

  //PattsMetrics
  Vector<int> getPattsMetricsBWC();
  Vector<int> getPattsMetricsBWNO();
  
  //MSHR
  bool isAbleMSHR(int);
  bool isPresentMSHR(Address addr, int);
  void insertMSHR(Address addr, int tipo, MachineID node);
  void removeMSHR(Address addr, int tipo);
  dramRequest getMSHREntry(Address addr, int tipo);

   static dramRequest getRequestFromMSHR(int v);
   bool isMSHRReady(int tipo);
   
   
private:
 static void setPtr(int a, Dram* b);
   static Time L2thisCycle[16];
   static Dram* ptrDram[8];
  
   Histogram prefMSHRsize;
   
   Histogram prefQueueBank0;
   Histogram prefQueueBank1;
   
   char* binary (uint64 v);

   //PattsMetrics
   void PattsMetrics();
   
  list<dramRequest>::iterator it;
  list<dramRequest>::iterator it2;
  
   void upgrade(Address addr);
   
  // Private Methods
   int firstBank();
   uint64 getBank(Address addr);
    

  // Private copy constructor and assignment operator
  
  // Data Members (m_ prefix)
  AbstractChip* m_chip_ptr;

  Consumer* m_consumer_ptr;

  // indicates what processor on the chip this dram is associated with
  int m_version;
  
  MachineID m_requestor;  //guarda qué máquina provocó el fallo

  Time taux;
  
  //Si cambiamos temporización revisar procedimiento wakeup donde se asigna el ciclo de dar una petición por servida
  
  //asignación en el constructor!!!
  
  //el patrón de acierto está definido como 4+4+7+4+4
  uint64 readHitBankBusyMask;  // 0111 1111 0000 0000  - 7^1 4^0 4^0
  uint64 readHitBusBusyMask; // 0111 1000 0000 0000 0000 0000 - 4^1 19^0
  
  uint64 writeHitBankBusyMask;  //
  uint64 writeHitBusBusyMask; // 
  
  //static const uint64 hitBusBusyMask ; // 1000 0000 0000 0000 0000 - 4^1 19^0   //para ocupar el bus 1 ciclo
  
  //el patrón de fallo está definido como 4+4+7+8+7+4+4
  uint64 readMissBankBusyMask; // 0011 1111 1111 1111 1111 1111 0000 0000 - 22^1 8^0
  uint64 readMissBusBusyMask; // 0011 1100 0000 0000 0000 0000 0000 0000 0000 0000 -  4^1 34^0
  
  uint64 writeMissBankBusyMask; // 
  uint64 writeMissBusBusyMask; // 
  
  //static const uint64 missBusBusyMask; //  0100 0000 0000 0000 0000 0000 0000 0000 0000 -  4^1 34^0  //para ocupar el bus 1 ciclo

  int logNumOfBanks;
  int numOfBanks;
  Vector <Bank> banks;
  int lastBankUsed;
  unsigned int prefetchQueueSizeCt;
  unsigned int demandQueueSizeCt;
  
  uint64 busBusyBitmap;
  //priority_queue <dramRequest> bus;
  
 
  priority_queue<dramRequest, vector<dramRequest>,mycomparison > bus;
  
  static const int freqRatio=4; //bus cpu=2Ghz, bus sistema=500Mhz
  
  //Variables para estadísticas
  uint64 cyclesDRAM;
  uint64 cyclesBusBusy;
  Vector <uint64> cyclesBusBusyPerProc;
  Vector <double> cyclesBusBusyRatioPerProc;
  
  Vector <uint64> maxDemandQueueSize;
  Vector <uint64> maxPrefetchQueueSize;
    
  Vector <uint64> medDemandQueueSize;
  Vector <uint64> medPrefetchQueueSize;
    
  Vector <int64> latPrefetchMax;
  Vector <int64> latPrefetchMin;
  
  Vector <int64> latDemandMax;
  Vector <int64> latDemandMin;
  
  Vector <int64> numRequestsQueued;
  Vector <int64> numDemandsQueued;
  Vector <int64> numPrefetchsQueued;
  
  Vector <int64> numRequestsServed;
  Vector <int64> numDemandsServed;
  Vector <int64> numPrefetchsServed;
  
  Vector <int64> numPrefetchPageHits;
  Vector <int64> numDemandPageHits;
  

  Vector <int64> cyclesDemandService;
  Vector <int64> cyclesPrefetchService;
  
  Vector <double> avgLatDemandService;
  Vector <double> avgLatPrefetchService;
  Vector <double> avgLatService;
  
  Vector <double> demandPageHitRatio;
  Vector <double> prefetchPageHitRatio;
  Vector <double> pageHitRatio;
  
  Histogram busyBanks;
  
  
  //PattsMetrics
  Vector <int> BWC;
  Vector <int> BWNO;
  Vector < Vector <int> > coresQueued;
  
  //parte de los MSHRs activos el banco de la L2 correspondiente
  
  list <dramRequest> prefMSHR;
  list <dramRequest> demandMSHR;
  
  uint prefMSHRSizeCt;
  uint demandMSHRSizeCt;
  
  int lastL2BankServed;
 
};


// Output operator declaration
ostream& operator<<(ostream& out, const Dram& obj);

// ******************* Definitions *******************

// Output operator definition
extern inline 
ostream& operator<<(ostream& out, const Dram& obj)
{
  obj.print(out);
  out << flush;
  return out;
}



#endif //PREFETCHER_H

