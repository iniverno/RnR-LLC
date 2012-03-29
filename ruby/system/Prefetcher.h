

/*
 * $Id: Sequencer.h 1.70 2006/09/27 14:56:41-05:00 bobba@s1-01.cs.wisc.edu $
 *
 * Description: 
 *
 */

#ifndef PREFETCHER_H
#define PREFETCHER_H

#include "Global.h"
#include "RubyConfig.h"
#include "Consumer.h"
#include "CacheRequestType.h"
#include "AccessModeType.h"
#include "GenericMachineType.h"
#include "PrefetchBit.h"
#include "Map.h"
#include "Histogram.h"
#include "RubySlicc_ComponentMapping.h"

class DataBlock;
class AbstractChip;
class CacheMsg;
class Address;
class MachineID;

#define PDFCM_HT_bits (14)
#define PDFCM_HT_size (1 << PDFCM_HT_bits)
#define PDFCM_HT_mask (PDFCM_HT_size - 1)
#define PDFCM_DT_bits (9)
#define PDFCM_DT_size (1 << PDFCM_DT_bits)
#define PDFCM_DT_mask (PDFCM_DT_size - 1)

#define DS_HT_bits (L2_CACHE_NUM_SETS_BITS)
#define DS_HT_size (1 << DS_HT_bits)
#define DS_HT_mask (DS_HT_size - 1)
#define DS_DT_bits (9)
#define DS_DT_size (1 << DS_DT_bits)
#define DS_DT_mask (DS_DT_size - 1)

#define PCTABLE_BITS 12
#define PCTABLE_ENTRIES (1 << PCTABLE_BITS)
#define PCTABLE_MASK (PCTABLE_ENTRIES - 1)

#define ABS(a)	   (((a) < 0) ? -(a) : (a))


#define NPROC 16


   typedef struct PDFCM_HT_entry PDFCM_HT_entry;
    struct PDFCM_HT_entry { 
      Address PC;		// address of the memory access instruction
      Address last_addr;		// last address that missed the cache
      unsigned short history;		// hashed history of deltas
      char count;			// Confidence counter
      char tipo;
      char proc;
   };
   	//
   
   typedef struct PDFCM_DT_entry PDFCM_DT_entry;
    struct PDFCM_DT_entry {
      short delta;			// delta between consecutive addresses	
   };   
   
      typedef struct DS_HT_entry DS_HT_entry;
    struct DS_HT_entry { 
      int set;
      long int last_addr;		// last address that missed the cache
      unsigned short history;		// hashed history of deltas
      char count;			// Confidence counter
      char tipo;
      char proc;
   };
   	//
   
   typedef struct DS_DT_entry DS_DT_entry;
    struct DS_DT_entry {
      short delta;			// delta between consecutive addresses	
   };   


struct PCTableEntry { 
  Address PC;		// address of the memory access instruction
  uint prefCnt;			// Confidence counter
  uint useCnt;
  uint aggr;
};
   
 struct nodo 
	  {
	  	Address addr;
	  	MachineID req;
	  	Address pc;
	  };	
 struct nodoLat
	  {
	  	Address addr;
	  	Time time;
	  	int proc;
	  	nodoLat(Address a, Time t, int p ){ addr=a; time=t; proc=p;}
	  	nodoLat(){ 0==0; }
	  };	
 

class Stream
  {
   
    public:
       Stream(uint64 a, MachineID pr, int degr, int dis, int version);
   
       Stream(){state=-1;} 
       bool test(uint64 a , MachineID node);
     //private:
      uint64 A, E;
      int state;
      int dir; //true = hacia+ , false=hacia-
      uint64 last;
      MachineID proc;
      int nproc;
      int deg;
      int d;
      int LRUpos;
       int m_version;
  };
  
struct bloomFilterEntry
 { unsigned char bit;
   MachineID proc;
   bool valid;
 };
 
 
#define TAMBUF 64
class Bufcir {
	  
    public:
	   
      Vector <nodo> array;  
      int first, next,size;
		bool esta(Address a) {
			for(int i=0;i<TAMBUF;i++) if(array[i].addr==a) return true;  
			
			return false;
		}
      Bufcir () {
          array.setSize (TAMBUF);
          first = 0;
          next = 0;
          size=0;
      }
      bool empty () {
        return first == next && size==0;
      }    
      bool full () {
        return first == next && size==TAMBUF;
      }      
      void insert (Address addr, MachineID req, Address pc) {
        	
        if(full()){ if(++first >= TAMBUF) first=0; }
        else size++; 
        
        if(++next >= TAMBUF) next=0;
        array[next].addr = addr;
        array[next].req = req;  
        array[next].pc = pc;  
    }
    void insert (Address addr, MachineID req) {
        	
        if(full()){ if(++first >= TAMBUF) first=0; }
        else size++; 
        
        if(++next >= TAMBUF) next=0;
        array[next].addr = addr;
        array[next].req = req;  
        
    }
	
     nodo& remove () {
      
         if(++first >= TAMBUF) first=0;
         size--;
        return array[first];
    } 
};


class Prefetcher : public Consumer {
public:
  // Constructors
  Prefetcher(AbstractChip* chip_ptr, int version);

  // Destructor
  ~Prefetcher();
  
  // Public Methods
  void wakeup(); // Used only for deadlock detection 

  void firstUse(Address addr, Address addr, int tipo);
  void miss(Address addr, Address addr, int tipo, MachineID node, int firstUse);
  void issued(Address pc);
 // uint getPCDegree(Address add);
  void hitOnPref (Address pc);
  void missOnNonArrivedPref(MachineID core);

  void getPrefetch();
  void access(Address a,MachineID node);
  void removeAccess(MachineID node);
  void stats(int t);
  void stats2(int t, MachineID node, int epoch);
  void statsLat(int t, Address a);
  void printStats(ostream& out);
  void clearStats();
  void print(ostream& out) const;
  static void printConfig(ostream& out);
  void bloomG(int t, Address a, MachineID core, MachineID owner);
  void bloomL(int t, Address a, MachineID core);
  uint64* getTratadas();
  uint64* getUtiles();
  uint64 getMisses();
  uint64 getAccesos();
  void pattsDecision(uint* dec);
  bool accessStream(Address a , MachineID node, bool miss);
int m_version;

  
  
  unsigned long int numberMisses;
  unsigned long int numberAccesses;
private:
  // Private Methods
  void adaptative();
  void actualizaLRUstreams(int i);
  void actualizaLRUstreamsInv(int i);
  void actualizaLRUstreamsDel(int i);
  void streamsAggrReview();
  void newStream(uint i, uint64 a, MachineID pr, int degr, int dis, int version);
  void adUTNOUT();
  void adUTNOUT2();
  void adUTUT();
  void adUTUT2();
  void adUTUT3();
  void adUTUT4();
  void adUTUT5();
  void adUTUT6();
  void adUTUT7();
  void adUTUT8();
  void adUTUT9();
  void adUTUT10();
  void adUTUT11();
  void adUTUT12();
  void adUTUT14();
  void adUTUT15();
  void adUTUT16();
  void adUTUT17();
  void adUTUT16b();
  void adUTUT17b();
  void adUTUT18();
  void adUTUT19();
  void adUTUT20();
  void adUTUT21();
  void adUTUT22();
   //mecanismo Patt 
  bloomFilterEntry bloomFilterG[NPROC][4096];
  bloomFilterEntry bloomFilterL[NPROC][4096];
  Vector <int> BWC;
  Vector <int> BWNO;
  uint m_pol_this_epoch[NPROC];
  uint m_pol_L_this_epoch[NPROC];
  uint dec[NPROC];
  double ACC[NPROC];
  double lateness[NPROC];
  double pollution[NPROC];  
  
  int flagBeh;
  uint auxMisses;
  
  int bloomBitAddress(Address addr);
  void evaluateMetrics();
  
   uint64 s_eliminados[NPROC];
  uint64 s_accesos[NPROC];
  uint64 s_positivos[NPROC];
  uint64 n_avances3[NPROC];
  uint64 n_avances2[NPROC];

  Stream** streams;
  int n_streams;
  int n_streams_activos;
  // Private copy constructor and assignment operator
 // Prefetcher(const Prefetcher& obj);
  //Prefetcher& operator=(const Prefetcher& obj);
  
  // Data Members (m_ prefix)
  AbstractChip* m_chip_ptr;

  Consumer* m_consumer_ptr;

  // indicates what processor on the chip this sequencer is associated with
  
  int m_adapt;
  
  MachineID m_requestor;  //guarda qué máquina provocó el fallo

#define BITS_SECTOR RubyConfig::dataBlockBits() + RubyConfig::L2CacheBits() + RubyConfig::L2CacheSetsBits()
   long int numOfHits, m_misses, m_misses_1[NPROC], m_misses_sector[NPROC],  m_firstUses[NPROC];
      

   //adaptativo (por epoca)
   uint64 racc, racc2;
   uint staticK, staticK2;
   int m_metodo;
   uint m_epoch;
   int degrees[11];
   int degreesS[11];
   int distances[11];
   int degreesPatt[11];
   int degree_index[NPROC];
   int degree_incr[NPROC];
   long int histo_degrees[NPROC][11];
   long int next_stop;
   long int misses_ant_par[NPROC];
   long int misses_ant_tot[NPROC];
   long int misses_this_epoch[NPROC];
   int confianza[NPROC];
   long int misses_this_epoch_global;
   long int misses_epoch_1_global;
   long int misses_epoch_1[NPROC];
   long int accesos_global;
   long int accesos_epoch_1_global_tot;
   long int accesos_epoch_ref_global;	
   long int accesos_proc[NPROC];
   long int accesos_epoch_1_proc_tot[NPROC];
   long int accesos_epoch_ref_proc[NPROC];	
   long int ins_proc[NPROC];
   long int ins_epoch_1_proc_tot[NPROC];
   long int ins_epoch_ref_proc[NPROC];	
   long int ins_epoch_ref;
   long int ins_epoch_ant;
   long int lat_acum_1[NPROC];
   long int lat_acum_todos;
   Histogram lats_demand;
   Histogram lats_pref;
   Histogram lats_gral;
   int m_proc_miss; //proc que ha fallado
   int m_proc_cambia;  //proc que cambiará en esta época
   int min_owner;
   double utilidad_epoch_1[NPROC];
   double utilidad_epoch[NPROC];
   uint64 utiles_epoch_1[NPROC];
   double utilidad_epoch_global;
   double utilmiss_epoch_global;
   double auxratio;
   uint64 utiles_epoch_global;
   uint64 utiles_ref_epoch_global;
   uint64 tratadas_epoch_1[NPROC];
   uint64 tratadas_epoch_global;
   uint64 lates_epoch_1[NPROC];
   uint64 lates_epoch_global;
   
   int ref;
   
   double WS;
   double amean_epoch_ref;
   
  int m_flag;
  
  //estadisticas long cadenas
  long int cadenas_valor[NPROC][11];
  long int cadenas_nelems[NPROC][11];
  
  //mecanismo dinámico de elección de prebuscador
   int m_alterna;
   int m_test;
   int m_etapa_actual;
   long m_ultima_epoca;
    int m_cambia;
   
// SEQT Degree Automaton (SDA) 
   Address m_last_addr[NPROC];
   int m_stride;
   int m_st_degree[NPROC];
   int m_st_base_degree[NPROC];
   
   //variables para quedarnos con lo mejor del intervalo
   int m_st_base_degree_aux[NPROC];
   int m_proc_cambia_aux;
   double auxratio_aux;
   
   Address m_last_pc[NPROC];
   int m_st_base_degree_matrix[NPROC][NPROC];
   
   void applyDegChange(); 
   void applyDegChange2(); 
   void applyDegChange(int j);
   
   //para las estadísticas de latencia de servicio
   Map<Address, nodoLat> m_map;
   
   //PDCFM
   // PDFCM Degree Automaton (PDA)
   unsigned short m_gen_history, m_pref_history;
   unsigned short m_history;
   Address m_old_addr;
   Address m_gen_last_addr[NPROC], m_pref_last_addr[NPROC];
   
   int PDegree[NPROC];
   int PBaseDegree[NPROC];
   int m_flag_cabeza;
   MachineID m_node; //core que hace la petición
   
   PDFCM_HT_entry * PDFCM_HT; 	
   PDFCM_DT_entry * PDFCM_DT; 	
    
  
   
    //PDFCM methods
    
  unsigned short PDFCM_hash (unsigned short old_history, short delta);
  Address PDFCM_predict_next ();
  Address PDFCM_update_and_predict ();
  
  //##########################
  // stats
  
  long m_sent_prefetches;
  
  long m_harmful_prefetches;
  long m_harmless_prefetches;
  
  long m_useful_prefetches;
  long m_useless_prefetches;
  
  long m_ext_harmful_prefetches;
  
  // array de contadores para la clasificación de las prebúsquedas
  Vector <uint64> cont;
  Vector <uint64> utiles;
  Vector <uint64> inutiles;
  Vector <uint64> m_misses_1_proc;
  Vector <uint64> misses2;
  Vector <uint64> insertadasPAB;
  Vector <uint64> insertadasAsc;
  Vector <uint64> insertadasDesc;
  Vector <uint64> insertadasCache;
  Vector <uint64> tratadas;
  Vector <uint64> generadas;
  Vector <uint64> ideal;
  uint64 inutiles_global;
  
  Vector <uint64> repls_epoch_1;
  uint64 repls_epoch_global;
  
  uint n_epochs;
  
  uint64* pref_epoch_global;
  uint64* pref_epoch_1[NPROC];
  

  
  Bufcir buffer;
  nodo port;  //petición que está en el puerto del banco de la L2 (para que la busqueda en la función
              //"esta" sea completa
  bool vacio;
  int m_tipo;
  
  //PC Aggr
  PCTableEntry* PCTable;
  uint getPCDegree(Address pc);
  

  
};



// Output operator declaration
ostream& operator<<(ostream& out, const Prefetcher& obj);

// ******************* Definitions *******************

// Output operator definition
extern inline 
ostream& operator<<(ostream& out, const Prefetcher& obj)
{
  obj.print(out);
  out << flush;
  return out;
}



#endif //PREFETCHER_H

