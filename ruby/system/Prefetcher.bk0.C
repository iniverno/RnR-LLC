
/*
 * Profiler.C
 * 
 * Description: See Profiler.h
 *
 * $Id$
 *
 */

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
#include "XactVisualizer.h"
#include "XactProfiler.h"
#include "RequestMsg.h"
#include "RubySlicc_ComponentMapping.h"
#include "RubySlicc_Util.h"
#include "MessageBuffer.h"

 Prefetcher::Prefetcher(AbstractChip* chip_ptr, int version)
 {
  if(isPrefetcher())
  {
    m_chip_ptr = chip_ptr;
    m_version = version;
  
     m_metodo= prefetchMechanism(); 
     
     //parte adaptativa
     degree_index=4;
     degree_incr=1;
     //{0,1,2,3,4,6,8,12,16,24,32,48,64};
     degrees[0]=0;
     degrees[1]=1;
     degrees[2]=2;
     degrees[3]=3;
     degrees[4]=4;
     degrees[5]=6;
     degrees[6]=8;
     degrees[7]=12;
     degrees[8]=16;
     degrees[9]=24;
     degrees[10]=32;
     degrees[11]=48;
     degrees[12]=64;    
 
     next_stop= 65536;
     inst_ant_tot=0;
     inst_ant_par=0;
     //fin adaptativa
     
    //1=seqt, 2=pdfcm
    if(m_metodo==1)
    {
      m_st_base_degree=prefetchDegree();
      //definimos cu‡l ser‡ el bloque pedido cada vez dependiendo de la configuraci—n con la que estemos trabajando
      //Actualmente bloques contiguos van a bancos contiguos (a slices contiguas) por lo que para que un procesador 
      //pida para s’ mismo hay que saltar #procs
      m_stride=RubyConfig::numberOfProcsPerChip();
    }
   
    if(m_metodo==2)
    {
      m_PDA_base_degree=prefetchDegree();
      m_PDA_degree=0;
      m_old_addr=Address(0);
      m_gen_last_addr=Address(0);
      m_pref_last_addr=Address(0);
      m_flag_cabeza=0;
      PDFCM_HT=(PDFCM_HT_entry *) calloc(PDFCM_HT_size, sizeof(PDFCM_HT_entry));
      PDFCM_DT=(PDFCM_DT_entry *) calloc(PDFCM_DT_size, sizeof(PDFCM_DT_entry));       
    }
    
     m_sent_prefetches=0;
  cout << "Soy un prefetcher " << version << endl;
     
     cont.setSize(30);
     
       for(int j=0; j< 30; j++)
       	 cont[j]=0;
  }
 }

  // Destructor
  Prefetcher::~Prefetcher(){0;}
  #define MASK_16b (0xffff)



  // Public Methods

//###################################################
  void Prefetcher::wakeup()
  {  
  Address predicted_address;
 // cout << next_stop << " a:" << g_system_ptr->getDriver()->getCycleCount(m_version) << " version: " << m_version << endl;
  
    //parte adaptativa 
    if(next_stop <= g_system_ptr->getDriver()->getCycleCount(m_version))
    {
      
      
      next_stop= g_system_ptr->getDriver()->getCycleCount(m_version) + 65536; //sig parada
      
      if(inst_ant_par >= g_system_ptr->getDriver()->getInstructionCount(m_version) - inst_ant_tot)
      //si vamos peor hay cambiar la pol’tica
        degree_incr *= -1;
                
      degree_index += degree_incr;
      if(degree_index <0) degree_index=0;
      if(degree_index >12) degree_index=12;
      
      m_st_base_degree=degrees[degree_index];
      m_PDA_base_degree=degrees[degree_index];
      
      inst_ant_par=g_system_ptr->getDriver()->getInstructionCount(m_version) - inst_ant_tot;
      inst_ant_tot=g_system_ptr->getDriver()->getInstructionCount(m_version);
      
     // cout << "revision:" << m_version << " grado:" << m_PDA_base_degree << " ind:" << degree_index << " incr:"<< degree_incr<< endl;
    }
    
    
  if(m_metodo==1)  //SEQT
  {
  
     Address aux2, aux=m_last_addr;
     
     //Direcci—n del siguiente bloque
     m_last_addr.setAddress( m_last_addr.maskLowOrderBits(RubyConfig::dataBlockBits()) + m_stride*RubyConfig::dataBlockBytes()); 
      aux2=m_last_addr;
      
      aux.makePageAddress();
      aux2.makePageAddress();
      //Si la prebœsqueda va a una p‡gina distinta, no la queremos
     if(aux == aux2)
      {   
       //buscamos la prebœsqueda en el buffer, si no est‡ la insertamos
        RequestMsg out_msg;
        
        if(!buffer.esta(m_last_addr)) buffer.insert(m_last_addr);
       if(!buffer.empty())
       {
        //extraemos la prebusqueda que toca del buffer 
        (out_msg).m_Address = buffer.remove();
      
        //CAMBIAR PARA A„ADIR ESCRITURA!!!
        (out_msg).m_Type = m_tipo==1 ? CoherenceRequestType_PREFS : CoherenceRequestType_PREFS;
        (out_msg).m_MessageSize = MessageSizeType_Control;
        m_chip_ptr->m_L2Cache_prefetchQueue_vec[m_version]->enqueue(out_msg, 1);
  
        Time current_time = g_eventQueue_ptr->getTime();
     
        if(m_st_degree > 0)
        {
  	      g_eventQueue_ptr->scheduleEvent(this, 1);
  	      m_st_degree--;
  	    }
  	   }
  	  }
  	  
  } else if (m_metodo==2)  //PDFCM
  {
  
     predicted_address = Address(0); 
     if(m_flag_cabeza)
     {
       m_flag_cabeza=0;
      if(PDFCM_update_and_predict())
       {
         //cambio variables generador
         m_PDA_degree=m_PDA_base_degree;
         m_gen_last_addr=m_pref_last_addr;
         m_gen_history=m_pref_history;
       }
     }
     if(m_PDA_degree>0)
     {    
       predicted_address = PDFCM_predict_next(); 
      }
       
       
     if (predicted_address.getAddress() && predicted_address!=m_gen_last_addr  )
     {
        RequestMsg out_msg;
        
        //buscamos la prebœsqueda en el buffer, si no est‡ la insertamos
        
        if(!buffer.esta(predicted_address)) buffer.insert(predicted_address);
              
        //extraemos la prebusqueda que toca del buffer 
      if(!buffer.empty())
      {
        (out_msg).m_Address = buffer.remove();
        //CAMBIAR PARA A„ADIR ESCRITURA!!!

        (out_msg).m_Type = m_tipo==1 ? CoherenceRequestType_PREFS : CoherenceRequestType_PREFS;
        (out_msg).m_MessageSize = MessageSizeType_Control;
        m_chip_ptr->m_L2Cache_prefetchQueue_vec[m_version]->enqueue(out_msg, 1);
        
        m_old_addr=m_gen_last_addr;
        m_gen_last_addr= predicted_address;  
        
        if(m_PDA_degree > 0)
        {
          m_PDA_degree--; 
          g_eventQueue_ptr->scheduleEvent(this, 1);	  
           
	    }
	   }
      }
         
  
    
  }//PDFCM
    	  	
  
  }
  


#define MASK_16b (0xffff)

    int Prefetcher::PDFCM_update_and_predict (){
      Address new_last_addr;
      unsigned short new_history;
      short actual_delta, predicted_delta;
      Address pc=m_last_pc, addr=m_pref_last_addr;
      
      // read PDFCM_HT entry
      unsigned int index = pc.getAddress() & PDFCM_HT_mask;
      Address old_last_addr = PDFCM_HT[index].last_addr; 
      unsigned short old_history = PDFCM_HT[index].history; 
      char count = PDFCM_HT[index].count;
   
      if (PDFCM_HT[index].PC != pc ){
         // if it's a new PC replace the entry
         m_pref_history=0;
         PDFCM_HT[index].PC=pc;
         PDFCM_HT[index].history=0; 
         PDFCM_HT[index].last_addr=Address(addr.getLineAddress());
         PDFCM_HT[index].count=0;
         PDFCM_HT[index].tipo=m_tipo;
         //PDFCM_HT[index].proc=
      
      return 0;
      }
   
      // compute deltas & update confidence counter
      predicted_delta=PDFCM_DT[old_history].delta;
     
     actual_delta = addr.getLineAddress()-old_last_addr.getAddress();
     
  //    cout << "real: " << actual_delta << " pred: " << predicted_delta << endl;
      if (actual_delta==predicted_delta){
         if (count<3) count++;
      }
      else{ 
         if (count>0) count--;
      }
   
      // compute new history
      
      m_pref_history = PDFCM_hash(old_history, actual_delta);
    //cout << "history: " << m_pref_history << endl;
      // write PDFCM_HT entry
      addr.makeLineAddress();
      PDFCM_HT[index].last_addr = Address(addr.getLineAddress());
      PDFCM_HT[index].history   = m_pref_history;
      PDFCM_HT[index].count=count;
   
      // update PDFCM_DT entry
      PDFCM_DT[old_history].delta = actual_delta;
   
      // predict a new delta using the new history 
      if (count<2) 
      { 
         return 0;
      }
      else 
      {
      
        return 1;
       
      }
   }

    Address Prefetcher::PDFCM_predict_next (){
      int delta;
       
      // compute delta 
      
  
  
    // predict a new delta using the new history   
      Address aux, aux2;
      aux= m_gen_last_addr;
      aux2= Address(m_gen_last_addr.getAddress() + (PDFCM_DT[m_gen_history].delta << RubyConfig::dataBlockBits()));
      aux2.makeLineAddress();
      
	  aux.makePageAddress();
      aux2.makePageAddress(); 
      if(aux==aux2)
      {
        
        //Address aux3=Address(m_last_addr.getAddress() + (PDFCM_DT[m_history].delta <<  RubyConfig::dataBlockBits()));
      	Address aux3=m_gen_last_addr;
      	aux3.makeNextStrideAddress(PDFCM_DT[m_gen_history].delta);
      	aux3.makeLineAddress();
      	
      	delta=PDFCM_DT[m_gen_history].delta;
      	m_gen_history=PDFCM_hash(m_gen_history, delta);
      	return aux3;
      } else
        return Address(0);
   }

    unsigned short Prefetcher::PDFCM_hash (unsigned short old_history, short delta){
    // R5-->  R(16, 16, 16)  F(t, t, t)  S(10, 5, 0) ; (number of entries of PDFCM_DT = 2^t)
   
      unsigned short select, folded, shift;
      select = delta;
   
      for(folded=0; select;) {
         folded ^= select & PDFCM_DT_mask;  // fold t bits
         select= select >> PDFCM_DT_bits;
      }
      shift = (old_history << 5) & PDFCM_DT_mask;     // shift 5 bits   
      return shift ^ folded;
   }

//##############################################

  void Prefetcher::firstUse(Address addr, Address pc, int tipo)
  {
  //	cout << "firstUse " <<  int_to_string(g_eventQueue_ptr->getTime()) << endl;
  Time current_time = g_eventQueue_ptr->getTime();
  m_tipo=tipo;
  //CAMBIAR!!
  
  
  if(m_metodo==1)
  {
    m_st_degree=m_st_base_degree;
     m_last_addr=Address(addr.maskLowOrderBits(RubyConfig::dataBlockBits()));
    
  } else if(m_metodo==2)
  {
    m_last_pc=pc;
    m_pref_last_addr=Address(addr.maskLowOrderBits(RubyConfig::dataBlockBits()));
    m_flag_cabeza=1;
  }

    g_eventQueue_ptr->scheduleEvent(this, 1); 
    
  }
  
  
  
  //#############################################
  
  
  void Prefetcher::miss(Address addr, Address pc, int tipo, MachineID node)
  {
    //	cout << "Prebuscador " <<  m_version << " @pc: " << pc << " node: " << node << " this: " << this <<endl;

  Time current_time = g_eventQueue_ptr->getTime();
  
  //CAMBIAR PARA A„ADIR ESCRITURA!!!

  //m_tipo= tipo;
  m_tipo=1;
  if(tipo!=1) return; 
  
 
  
  if(m_metodo==1)
  {
    m_st_degree=m_st_base_degree;
     m_last_addr=Address(addr.maskLowOrderBits(RubyConfig::dataBlockBits()));
  } else if(m_metodo==2)
  {
    // std::cout << "AAA: " << machineIDToVersion(node) << endl;
    m_last_pc=Address((pc.getAddress() << RubyConfig::procsPerChipBits()) + machineIDToVersion(node));
     m_pref_last_addr=Address(addr.maskLowOrderBits(RubyConfig::dataBlockBits()));
     m_flag_cabeza=1;
  }
	
	
    g_eventQueue_ptr->scheduleEvent(this, 1);
  }
  
 

void Prefetcher::print(ostream& out) const { 0;}
  
  void Prefetcher::printConfig(ostream& out)
 {
 0;
}

//Si recibimos un:
//mirar documento externo
 void Prefetcher::stats(int t)
 {
   if(t<0 || t>21) {ERROR_MSG("Parametro fuera de rango");}
   else
     cont[t]++;
  }


void Prefetcher::printStats()
{
  cout << cont << endl;
}
  // Private copy constructor and assignment operator
 // Prefetcher::Prefetcher(const Prefetcher& obj) {0; }
  //	Prefetcher::Prefetcher& operator=(const Prefetcher& obj)  {0; }
  
