
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
#include "Prefetcher.h"


#define EPOCH_SIZE_BITS 15

#define ndegreesStr 5
#define ndegreesSEQT 5
#define ndegreesPatt 5
  
#define SPECIAL_DEBUG 0

 Prefetcher::Prefetcher(AbstractChip* chip_ptr, int version)
 {

  
    m_chip_ptr = chip_ptr;
    m_version = version;
    vacio=true;
    
   
  
    m_alterna=0;
  
     m_metodo= prefetchMechanism(); 
     m_adapt= adaptDegree();
    
     cerr << "Mecanismo: " << m_metodo << endl;
     //parte adaptativa
     
     //{0,1,2,3,4,6,8,12,16,24,32,48,64};
     degrees[0]=0;
     degrees[1]=1;
     degrees[2]=2;
     degrees[3]=4;
     degrees[4]=6;
     degrees[5]=8;
     degrees[6]=12;
     degrees[7]=16;
     degrees[8]=24;
     degrees[9]=36;
     degrees[10]=48;
     
     degrees[0]=0;
     degrees[1]=1;
     degrees[2]=4;
     degrees[3]=8;
     degrees[4]=16;
     degrees[5]=36;
     
   /*  degrees[0]=0;
     degrees[0]=1;
     degrees[1]=4;
     degrees[2]=8;
     degrees[3]=16;
     degrees[4]=36;*/
     
     
     degrees[5]=8;
     degrees[6]=12;
     degrees[7]=16;
     degrees[8]=24;
     degrees[9]=36;
     degrees[10]=48;
     
     distances[0]=4;
     distances[1]=8;
     distances[2]=16;
     distances[3]=32;
     distances[4]=64;
     
     degreesS[0]=1;
     degreesS[1]=1;
     degreesS[2]=2;
     degreesS[3]=4;
     degreesS[4]=4;
    
     degreesPatt[0]=1;
     degreesPatt[1]=1;
     degreesPatt[2]=2;
     degreesPatt[3]=4;
     degreesPatt[4]=4;
       
     m_epoch=0;
     
     srand(0);
     next_stop= 65536;
     min_owner=0;
     int i;
     m_flag=0;
     amean_epoch_ref=1000.0;
     m_cambia=1;
     utilidad_epoch_global=1;
     
      if(m_metodo==10 || m_metodo==11)
      {
        n_streams=g_NUMBER_OF_STREAMS*RubyConfig::numberOfProcsPerChip();
     cout << "n_streams: " << n_streams << endl;
        streams=new Stream*[n_streams];
        n_streams_activos=0;
        for(int j=0; j<n_streams; j++){ streams[j]=new Stream(); streams[j]->state=-1;}
      }
      
      
      
     
 	for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) {
 	  
      degree_incr[j]=1;
      
      misses_ant_tot[j]=0;
      misses_ant_par[j]=0;
      
      //cerr << "************  " << g_PREFETCH_DEGREE << endl;
      m_st_base_degree[j]=g_PREFETCH_DEGREE;
      if(m_metodo==10|| m_metodo==11)
      {
        
        degree_index[j]=g_PREFETCH_DEGREE;
      }
      else
      {for(i=0;i<11 && degrees[i]!=g_PREFETCH_DEGREE;i++); 
      degree_index[j]=i;}
      
       if(m_metodo==2)
       {
         m_gen_last_addr[j]=Address(0);
         m_pref_last_addr[j]=Address(0);
       }
   }   
       
    if(g_ONLY_ONE_DIF)
    {
      m_st_base_degree[g_PROC_AISLADO]=g_ONLY_ONE_DIF_DEG;
      for(i=0;i<11 && degrees[i]!=g_ONLY_ONE_DIF_DEG;i++); 
      degree_index[g_PROC_AISLADO]=i;
    }
    
   
     //fin adaptativa
     
  if(m_metodo==2)
    {
      
      m_old_addr=Address(0);
    
      m_flag_cabeza=0;
      PDFCM_HT=(PDFCM_HT_entry *) calloc(PDFCM_HT_size, sizeof(PDFCM_HT_entry));
      PDFCM_DT=(PDFCM_DT_entry *) calloc(PDFCM_DT_size, sizeof(PDFCM_DT_entry));       
    } 
      
      m_stride= g_PAGE_INTERLEAVING ? 1 : RubyConfig::numberOfL2CachePerChip();
      
    
    if(g_PAGE_INTERLEAVING) cerr <<"el entralazado es por p‡gina" << endl;
    else cerr <<"el entralazado es por bloque" << endl;
    
     m_sent_prefetches=0;
  cerr << "Soy un prefetcher " << version << " bits: " << RubyConfig::numberOfL2CachePerChip() << endl;
     
     cont.setSize(40);
     utiles.setSize(RubyConfig::numberOfProcsPerChip());
     inutiles.setSize(RubyConfig::numberOfProcsPerChip());
     tratadas.setSize(RubyConfig::numberOfProcsPerChip());
     generadas.setSize(RubyConfig::numberOfProcsPerChip());
     ideal.setSize(RubyConfig::numberOfProcsPerChip());
     insertadasPAB.setSize(RubyConfig::numberOfProcsPerChip());
     insertadasCache.setSize(RubyConfig::numberOfProcsPerChip());
     insertadasAsc.setSize(RubyConfig::numberOfProcsPerChip());
     insertadasDesc.setSize(RubyConfig::numberOfProcsPerChip());
     m_misses_1_proc.setSize(RubyConfig::numberOfProcsPerChip());
     misses2.setSize(RubyConfig::numberOfProcsPerChip());
     
     repls_epoch_1.setSize(RubyConfig::numberOfProcsPerChip());
     repls_epoch_global=0;
     
     n_epochs=50;
     pref_epoch_global=new uint64[n_epochs];
     for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) pref_epoch_1[j]=new uint64[n_epochs];
     
     for(uint i=0; i<n_epochs; i++)
     {
       for(uint j=0; j<RubyConfig::numberOfProcsPerChip(); j++) pref_epoch_1[j][i]=0;
       pref_epoch_global[i]=0;
     }
     
     
     for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) 
     { 
       
       for(int k=0; k<11; k++) 
       {
         histo_degrees[j][k]=0;
         cadenas_valor[j][k]=0;
         cadenas_nelems[j][k]=0;
       }
       m_misses_sector[j]=0;
       m_misses_1[j]=0;
       m_misses_1_proc[j]=0;
       m_firstUses[j]=0;
       insertadasPAB[j]=0; insertadasCache[j]=0; tratadas[j]=0; utiles[j]=0;inutiles[j]=0; 
       m_misses_1_proc[j]=0; misses2[j]=0;
       insertadasAsc[j]=0; insertadasDesc[j]=0;
       generadas[j]=0; ideal[j]=0;
       misses_epoch_1[j]=10000000000000;
       accesos_epoch_ref_proc[j]=0;
       ins_epoch_ref_proc[j]=10000000000;
       ins_proc[j]=0;
       ins_epoch_1_proc_tot[j]=0;
       lat_acum_1[j]=0;
       utilidad_epoch[j]=0;
       m_pol_L_this_epoch[j]=0;
       m_pol_this_epoch[j]=0;
       repls_epoch_1[j]=0;
     }
     ins_epoch_ref=0;
     ins_epoch_ant=0;
     misses_epoch_1_global=100000000000;
     inutiles_global=0;
     accesos_epoch_ref_global=0;
     lat_acum_todos=0;
       for(int j=0; j< 40; j++)
       	 cont[j]=0;
      	 
    //cerr << "Hola, soy el coordinador Gral de los prefetchers, este es mi constructor " << missesGlobalThisEpoch << endl;
  for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) 
    for(int k=0; k<4096; k++) bloomFilterG[j][k].valid=false,bloomFilterL[j][k].valid=false ;
  
    g_eventQueue_ptr->scheduleEvent(this, next_stop);
    
    PCTable= new PCTableEntry [PCTABLE_ENTRIES];
    
    for(int i=0; i<PCTABLE_ENTRIES; i++) 
    {
      PCTable[i].aggr=0; 
      PCTable[i].PC=Address(0);
      PCTable[i].useCnt=0; 
      PCTable[i].prefCnt=0; }
      
    racc=0; racc2=0; staticK=0; staticK2=0;
    
    ref=1;
 }

  // Destructor
  Prefetcher::~Prefetcher(){0;}
  #define MASK_16b (0xffff)



  // Public Methods

//###################################################
  void Prefetcher::wakeup()
  { 
  if(!g_CARGA_CACHE)
  {
   //    if(g_DEBUG_PREFETCHER) cerr << "wakeup del prebuscador " << m_version << endl;
    adaptative();
     int f=0;
     
  if(m_metodo!=2 && m_metodo!=0 && m_metodo!=10 && m_metodo!=11)  //SEQT
  {
    
     Address aux3, aux2, aux=m_last_addr[m_proc_miss];
     
     //Direcci—n del siguiente bloque
     //m_last_addr[m_proc_miss].setAddress( m_last_addr[m_proc_miss].maskLowOrderBits(RubyConfig::dataBlockBits()) + RubyConfig::dataBlockBytes()); 
      //aux2=m_last_addr[m_proc_miss];      
      
      aux2.setAddress( m_last_addr[m_proc_miss].maskLowOrderBits(RubyConfig::dataBlockBits()) + m_stride*RubyConfig::dataBlockBytes()); 
      aux3=aux2;
      
      aux.makePageAddress();
      aux2.makePageAddress();
     
     
     //Si la prebœsqueda va a una p‡gina distinta, no la queremos 
     if(aux.getAddress() == aux2.getAddress())
      {   
       //buscamos la prebœsqueda en el buffer, si no est‡ la insertamos
        m_last_addr[m_proc_miss]=aux3;
        
        generadas[m_proc_miss]++;
          
        if(!buffer.esta(m_last_addr[m_proc_miss]) && port.addr!=m_last_addr[m_proc_miss] ) { 
        
       // if(g_DEBUG_PREFETCHER) if(m_version==0 ) cerr << "insertamos2 : " << m_last_addr[m_proc_miss]  << "\t" << g_system_ptr->getDriver()->getCycleCount(m_version)<< "\t" <<m_proc_miss<< endl;
        
          //cerr << "insertamos2 : " << m_last_addr[m_proc_miss] << endl;
          buffer.insert(m_last_addr[m_proc_miss], m_requestor, m_last_pc[m_proc_miss]); 
          insertadasPAB[m_proc_miss]++;
          
          //si el puerto est‡ vacio...
          if(vacio) getPrefetch();
        }
  	   
  	   if(0 && m_version==0) {
  	   		cerr << "HEY: ";
  	   		for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cerr << m_st_base_degree[j]  << " " << degree_index[j] << "\t";  
  	   		cerr << endl;
  	   	}
  	   	
  	   m_st_degree[m_proc_miss]--;
  	    if(m_st_degree[m_proc_miss]>0) g_eventQueue_ptr->scheduleEvent(this, 1);
  	    
  	  } // if cambio de p‡gina
  	  else m_st_degree[m_proc_miss]=0;
  	  
  }
  
  else if(m_metodo==10 || m_metodo==11)
  {

    static int i=0;
    int bar=i;
    int flag=0;
    
    while(flag==0)
    { 
      flag=0;
      
      if(streams[i]!=NULL && streams[i]->state==2 && streams[i]->deg>0) 
      {  
        streams[i]->E+= RubyConfig::dataBlockBytes() * streams[i]->dir;
        if(streams[i]->E ==  streams[i]->A + streams[i]->dir * streams[i]->d * RubyConfig::dataBlockBytes())
        { streams[i]->state=3;
         
          if(g_DEBUG_PREFETCHER) if(m_version==0 && streams[i]->nproc==6) cerr << "Stream\t" << i <<
            " pasa al estado 3 B:" << streams[i]->A << " [" <<g_system_ptr->getDriver()->getCycleCount(m_version) << "]" <<endl;
        }
         
        flag=1;
      // if(g_DEBUG_PREFETCHER) if(m_version==0) cerr << "a " << g_system_ptr->getDriver()->getCycleCount(m_version) <<  " stream " << i << " que esta en estado " << streams[i]->state << " inserta dir " << streams[i]->last << " para el proc " << streams[i]->proc << " con un grado " << streams[i]->deg<< endl ;
		n_avances2[streams[i]->nproc]++;
      }
      else if(streams[i]!=NULL && streams[i]->state==3 && streams[i]->deg>0) 
      {
       streams[i]->E += RubyConfig::dataBlockBytes() * streams[i]->dir;
       streams[i]->A += RubyConfig::dataBlockBytes() * streams[i]->dir;
        flag=1;
        n_avances3[streams[i]->nproc]++;
        if(g_DEBUG_PREFETCHER)  if(m_version==0) cerr << "b stream " << i << " que esta en estado " << streams[i]->state << "inserta dir " << streams[i]->last << " para el proc " << streams[i]->proc << endl ;
      }
      
    if(flag)
    {
      Address aux3, aux2, aux=Address(streams[i]->last);
      //Direcci—n del siguiente bloque
      //m_last_addr[m_proc_miss].setAddress( m_last_addr[m_proc_miss].maskLowOrderBits(RubyConfig::dataBlockBits()) + RubyConfig::dataBlockBytes()); 
      //aux2=m_last_addr[m_proc_miss];      
      
      aux2.setAddress(streams[i]->E); 
      aux3=aux2;
      
      aux.makePageAddress();
      aux2.makePageAddress();
     
     
     //Si la prebœsqueda va a una p‡gina distinta, no la queremos 
     if(aux.getAddress() == aux2.getAddress())
      {   
       //buscamos la prebœsqueda en el buffer, si no est‡ la insertamos
       streams[i]->last=aux3.getAddress();
        
          generadas[m_proc_miss]++;
        
        if(!buffer.esta(Address(streams[i]->last)) && port.addr!=Address(streams[i]->last)) { 
          
       //   cerr << "insertamos2 : " << m_last_addr[m_proc_miss] << endl;
             if(g_DEBUG_PREFETCHER)  if(m_version==0 && streams[i]->nproc==6)  cerr << "stream\t" << i << " prebusca " << streams[i]->state << 
               " inserta dir " << streams[i]->last << " para el proc " << streams[i]->proc << " con un grado " << streams[i]->deg<<
                 " [" <<g_system_ptr->getDriver()->getCycleCount(m_version) << "]" <<endl ;
		  
		  streams[i]->dir==1 ? insertadasAsc[streams[i]->nproc]++ : insertadasDesc[streams[i]->nproc]++;
		  
          buffer.insert(Address(streams[i]->last),streams[i]->proc); 
          insertadasPAB[streams[i]->nproc]++;

          //si el puerto est‡ vacio...
          if(vacio) getPrefetch();
        }
  	     streams[i]->deg--;
  	    if(streams[i]->deg>0) g_eventQueue_ptr->scheduleEvent(this, 1);
  	    i= (i==n_streams-1) ? 0 : i+1;
  	    return;
  	    
  	  } // if cambio de p‡gina
  	  else streams[i]->deg=0;
  	 } //if flag 
  	 
     i= (i==n_streams-1) ? 0 : i+1;
     if(bar==i || flag) break;
    } //while
  }//
  
  //if(m_version==0) cerr << "version: "<< m_version << "ciclo: " << g_system_ptr->getDriver()->getCycleCount(m_version) << " proc:"  << m_proc_miss << " grado: " << m_st_degree[m_proc_miss]<< " base: " << m_st_base_degree[m_proc_miss] << endl ;

 } //if g_CARGA_CACHE
} //wakeup

void Prefetcher::adaptative()
{
 // if(g_DEBUG_PREFETCHER) cerr << "entra en adaptative()" << m_version << endl;
  Address m_gen_last_addr; 
 // cerr << "version: " << m_version <<"\ta:\t" << g_system_ptr->getDriver()->getCycleCount(m_version) << endl;
  static Time a=g_system_ptr->getDriver()->getCycleCount(0);
  
    //parte adaptativa 
    if(m_adapt && next_stop <= g_system_ptr->getDriver()->getCycleCount(0) && g_VARIANTE!=13)
    { 
      m_epoch++;
      if(g_EPOCHS_SALTA>0 && g_EPOCHS_SALTA==m_epoch && m_version==0){ flagBeh= g_GOOD_DEC==1 ? 1 : 2; auxMisses=0;}
      else flagBeh=0;
     
     if(g_EPOCHS_SALTA>0 && g_EPOCHS_SALTA+1==m_epoch && m_version==0)
     {
       printStats(std::cout);
       exit(0);
     }
     //cerr << "p" << m_version << " " <<  g_system_ptr->getDriver()->getCycleCount(m_version)  << " m_st_base_degree[j]: " << misses_ant_par[0] << "\t" <<  m_misses - misses_ant_tot[0] << "\t" ;
     //cerr <<g_system_ptr->getDriver()->getCycleCount(m_version)  << "\t" << accesos_epoch_ref_global << "\t" <<  accesos_epoch_1_global_tot << "\t" << accesos_global << "\t" ;
                  
      if(g_TRACE_DEGREE && m_version==0) 
      //if(g_TRACE_DEGREE ) 
      {
        double utilAux=0;
        if(tratadas_epoch_global!=0) utilAux=utiles_epoch_global/(double)tratadas_epoch_global; 
       
        a=g_system_ptr->getDriver()->getCycleCount(0);
        repls_epoch_global=0;
        //cerr << "prebuscador " << m_version<<":\t"<< "pol: " << m_pol_this_epoch <<"\t"; 
        //for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cerr << m_st_base_degree[j] << "\t";     
        cerr << "pref" << m_version << " proc:\t"  << m_proc_cambia <<  "\t" ;
        //for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cerr << (m_metodo!=10 || m_metodo==11 ? m_st_base_degree[j] : degree_index[j]) << "\t";  
        for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cerr <<  m_st_base_degree[j] << " " << degree_index[j] << "\t";  
        cerr << (m_cambia==1? "*" : (m_cambia==2? "<->" :""));
        // cerr   <<  misses_this_epoch_global << "\t" << utilmiss_epoch_global << " "<< auxratio<< endl;
      
        cerr <<endl;
      } 
      if(g_TRACE_METRIC && m_version==0) 
      {
        
        cerr << "prebuscador " << m_version<<":\t" ; 
        for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cerr << g_system_ptr->getDriver()->getInstructionCount(j)-ins_epoch_1_proc_tot[j] << "\t" << accesos_proc[j] - accesos_epoch_1_proc_tot[j] <<  "\t" ;      
        cerr <<endl;
        
        if(m_metodo==0)
          for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++)
          {
            accesos_epoch_1_proc_tot[j]=accesos_proc[j];
            //ins_epoch_1_proc_tot[j]=g_system_ptr->getDriver()->getInstructionCount(j);
          }
      } 
      for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) histo_degrees[j][degree_index[j]]++;
            
      int aux=g_system_ptr->getDriver()->getCycleCount(0);
      
      
      next_stop= aux + g_EPOCH_SIZE*1000;
      g_eventQueue_ptr->scheduleEvent(this, g_EPOCH_SIZE*1000);
     	
      //Patt
      //m_pol_this_epoch=0;
     
if(g_VARIANTE==15)
    {       
	   adUTUT15();        
      
    } else
    if(g_VARIANTE==16)
    {       
	   adUTUT16b();        
      
    } else
    if(g_VARIANTE==17)
    {       
	   adUTUT17b();        
      
    } else
    if(g_VARIANTE==18)
    {       
	   adUTUT18();        
      
    } else if(g_VARIANTE==19)
    {       
	   adUTUT19();        
      
    } else if(g_VARIANTE==20)
    {       
	   adUTUT20();        
      
    } else if(g_VARIANTE==21)
    {       
	   adUTUT21();        
      
    } else if(g_VARIANTE==22)
    {       
	   adUTUT22();        
      
    }
    
    
     misses_this_epoch_global=0;        
     
     // cerr << "revision:" << m_version << " grado:" << m_PDA_base_degree << " ind:" << degree_index << " incr:"<< degree_incr<< endl;
    } //parte adaptativa
    
  //  if(g_DEBUG_PREFETCHER) cerr << "sale de adaptative()" << m_version << endl;
}


//La variante 15 est‡ guiada por la tasa de fallos en el banco y tiene un umbral de corte que usa la utilidad de la preb
void Prefetcher::adUTUT15()
{
		
        utilidad_epoch[m_proc_cambia]*=0.5;
        if(double(tratadas_epoch_1[m_proc_cambia])!=0) utilidad_epoch[m_proc_cambia]+=0.5*(double(utiles_epoch_1[m_proc_cambia])/double(tratadas_epoch_1[m_proc_cambia]));
       // double auxutil, auxmiss;
             
     if(m_version==0 && SPECIAL_DEBUG) cerr << "misses_this_epoch_global " << misses_this_epoch_global << " accesos_global:" << accesos_global<< endl;
       
       if(accesos_global!=0) auxratio=(double)misses_this_epoch_global/(double)accesos_global; 
       else accesos_global=0;
       
        
        utiles_epoch_1[m_proc_cambia]=0, tratadas_epoch_1[m_proc_cambia]=0;
        
       
       if(ref)
       {
       	if(m_version==0  &&  SPECIAL_DEBUG) cerr << " A" << endl;
         ref=0;
         m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
         applyDegChange();
         utilmiss_epoch_global=auxratio;
         
       } else 
       {
       	if(m_version==0  &&  SPECIAL_DEBUG) cerr << " B " << auxratio << " " << utilmiss_epoch_global << " ";
         if(auxratio > utilmiss_epoch_global)
         {           
           if(min_owner==m_proc_cambia)
           {
             m_cambia=2;
             misses_epoch_1_global=misses_this_epoch_global, m_misses_1[m_proc_cambia]=misses_this_epoch[m_proc_cambia] ;  
             utilmiss_epoch_global=auxratio;
             degree_incr[m_proc_cambia] *= -1;
             //cambiamos el grado ya
             applyDegChange();
             ref=1;
             if(m_version==0  &&  SPECIAL_DEBUG) cerr << " C" ;
           } else
           {
           	if(m_version==0  &&  SPECIAL_DEBUG) cerr << " D" ;
             //si vamos peor hay cambiar la pol’tica
             m_cambia=0;
             if(degree_index[m_proc_cambia]!=0 || degree_incr[m_proc_cambia]==1 )
             {//deshacemos el cambio 
               if(m_version==0  &&  SPECIAL_DEBUG) cerr << " E" ;
               //GD  --> para volver al codigo original ejecutar siempre el codigo del condicional
               if(flagBeh!=2 && m_version==0)
     			 {	
     			 	if(m_version==0  &&  SPECIAL_DEBUG) cerr << " F" ;
                   degree_incr[m_proc_cambia] *= -1;
               //cambiamos el grado ya
                   applyDegChange()	;
                 }
             } else  {degree_incr[m_proc_cambia] *= -1; if(m_version==0  &&  SPECIAL_DEBUG) cerr << " G" ; }
             
             m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
             
             utilidad_epoch[m_proc_cambia]*=0.5;
        	 if(double(tratadas_epoch_1[m_proc_cambia])!=0) utilidad_epoch[m_proc_cambia]+=0.5*(double(utiles_epoch_1[m_proc_cambia])/double(tratadas_epoch_1[m_proc_cambia]));
        	 
        	 //cerr << "ut1: " << g_UTILITY_THRES << endl;
        	 if(utilidad_epoch[m_proc_cambia]*100.0<g_UTILITY_THRES && utilidad_epoch[m_proc_cambia]>0 && degree_incr[m_proc_cambia] == 1) degree_incr[m_proc_cambia] *= -1;
             applyDegChange();
          
           }  
          
          } else
          {//vamos bien
          	if(m_version==0  &&  SPECIAL_DEBUG) cerr << " H" ;
              m_cambia=1;
              misses_epoch_1_global=misses_this_epoch_global;
              utilmiss_epoch_global=auxratio;
        	  m_misses_1[m_proc_cambia]=misses_this_epoch[m_proc_cambia];
        	  
        	  //GD->si nos toca hacer lo contrario deshacemos el cambio
        	  //para volver al codigo original eliminar todo el if y su cuerpo
        	   if(flagBeh==2 && m_version==0)
     			 {
     			 	if(m_version==0  &&  SPECIAL_DEBUG) cerr << " I" ;
					degree_incr[m_proc_cambia] *= -1;
               //cambiamos el grado ya
               		applyDegChange()	;        
 			     }
        	  
        	  if(m_version==0  &&  SPECIAL_DEBUG) cerr << " J" ;
             // accesos_epoch_1_global_tot=accesos_global;
        	  min_owner=m_proc_cambia;
        	  m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
        	  
        	  utilidad_epoch[m_proc_cambia]*=0.5;
        	 if(double(tratadas_epoch_1[m_proc_cambia])!=0) utilidad_epoch[m_proc_cambia]+=0.5*(double(utiles_epoch_1[m_proc_cambia])/double(tratadas_epoch_1[m_proc_cambia]));
        	 //cerr << "ut2: " << g_UTILITY_THRES << endl;
        	 
        	 if(utilidad_epoch[m_proc_cambia]*100.0 <g_UTILITY_THRES && utilidad_epoch[m_proc_cambia]>0 && degree_incr[m_proc_cambia] == 1) degree_incr[m_proc_cambia] *= -1;
        	 
             applyDegChange();
          }
          
      }
      
      
      misses_this_epoch[m_proc_cambia]=0; 
      misses_this_epoch_global=0;
      accesos_global=0;
}  

//La variante 16b est‡ guiada por IPC global del sistema y tiene un umbral de corte que usa la utilidad de la preb
void Prefetcher::adUTUT16b()
{
		static int ref=1;
		
        utilidad_epoch[m_proc_cambia]*=0.5;
        if(double(tratadas_epoch_1[m_proc_cambia])!=0) utilidad_epoch[m_proc_cambia]+=0.5*(double(utiles_epoch_1[m_proc_cambia])/double(tratadas_epoch_1[m_proc_cambia]));
       // double auxutil, auxmiss;
             
       
       long unsigned int ins_this_epoch= g_system_ptr->getProfiler()->getTotalInstructionsExecuted() - ins_epoch_ant;
       
       if(accesos_global!=0) auxratio=(double)misses_this_epoch_global/(double)accesos_global; 
       else accesos_global=0;
       
        
        utiles_epoch_1[m_proc_cambia]=0, tratadas_epoch_1[m_proc_cambia]=0;

       if(m_version==0) cerr << "ins_this_epoch " << ins_this_epoch << " accesos_global:" << accesos_global<< endl;        
       
       if(ref)
       {
         ref=0;
         m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
         applyDegChange();
         utilmiss_epoch_global=auxratio;
         
       } else 
       {
         if(ins_this_epoch < ins_epoch_ref)  //hemos ido peor
         {           
           if(min_owner==m_proc_cambia)   //pero hemos probado todos sin exito
           {
             m_cambia=2;
             ins_epoch_ref= ins_this_epoch;
             degree_incr[m_proc_cambia] *= -1;
             //cambiamos el grado ya
             applyDegChange();
             ref=1;
           } else
           {
             //si vamos peor hay cambiar la pol’tica
             m_cambia=0;
             if(degree_index[m_proc_cambia]!=0 || degree_incr[m_proc_cambia]==1 )
             {//deshacemos el cambio 
               
               //GD  --> para volver al codigo original ejecutar siempre el codigo del condicional
               if(flagBeh!=2 && m_version==0)
     			 {
                   degree_incr[m_proc_cambia] *= -1;
               //cambiamos el grado ya
                   applyDegChange()	;
                 }
             } else degree_incr[m_proc_cambia] *= -1;
             
             m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
             
             utilidad_epoch[m_proc_cambia]*=0.5;
        	 if(double(tratadas_epoch_1[m_proc_cambia])!=0) utilidad_epoch[m_proc_cambia]+=0.5*(double(utiles_epoch_1[m_proc_cambia])/double(tratadas_epoch_1[m_proc_cambia]));
        	 
        	 //cerr << "ut1: " << g_UTILITY_THRES << endl;
        	 if(utilidad_epoch[m_proc_cambia]*100.0<g_UTILITY_THRES && utilidad_epoch[m_proc_cambia]>0 && degree_incr[m_proc_cambia] == 1) degree_incr[m_proc_cambia] *= -1;
             applyDegChange();
          
           }  
          
          } else
          {//vamos bien
              m_cambia=1;
              ins_epoch_ref= ins_this_epoch;
        	  
        	  //GD->si nos toca hacer lo contrario deshacemos el cambio
        	  //para volver al codigo original eliminar todo el if y su cuerpo
        	   if(flagBeh==2 && m_version==0)
     			 {
					degree_incr[m_proc_cambia] *= -1;
               //cambiamos el grado ya
               		applyDegChange();        
 			     }
        	  
        	  
             // accesos_epoch_1_global_tot=accesos_global;
        	  min_owner=m_proc_cambia;
        	  m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
        	  
        	  utilidad_epoch[m_proc_cambia]*=0.5;
        	 if(double(tratadas_epoch_1[m_proc_cambia])!=0) utilidad_epoch[m_proc_cambia]+=0.5*(double(utiles_epoch_1[m_proc_cambia])/double(tratadas_epoch_1[m_proc_cambia]));
        	 
        	 if(utilidad_epoch[m_proc_cambia]*100.0 <g_UTILITY_THRES && utilidad_epoch[m_proc_cambia]>0 && degree_incr[m_proc_cambia] == 1) degree_incr[m_proc_cambia] *= -1;
        	 
             applyDegChange();
          }
          
      }
      
      
      misses_this_epoch[m_proc_cambia]=0; 
      misses_this_epoch_global=0;
      accesos_global=0;
      
      ins_epoch_ant= g_system_ptr->getProfiler()->getTotalInstructionsExecuted();
}  

//La variante 17b est‡ guiada por IPC global del sistema y NO tiene un umbral de corte
void Prefetcher::adUTUT17b()
{
		static int ref=1;
		             
       
       long unsigned int ins_this_epoch= g_system_ptr->getProfiler()->getTotalInstructionsExecuted() - ins_epoch_ant;
       
       if(accesos_global!=0) auxratio=(double)misses_this_epoch_global/(double)accesos_global; 
       else accesos_global=0;
       
        
       if(m_version==0) cerr << "ins_this_epoch " << ins_this_epoch << " accesos_global:" << accesos_global<< endl;        
       
       if(ref)
       {
         ref=0;
         m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
         applyDegChange();
         utilmiss_epoch_global=auxratio;
         
       } else 
       {
         if(ins_this_epoch < ins_epoch_ref)  //hemos ido peor
         {           
           if(min_owner==m_proc_cambia)   //pero hemos probado todos sin exito
           {
             m_cambia=2;
             ins_epoch_ref= ins_this_epoch;
             degree_incr[m_proc_cambia] *= -1;
             //cambiamos el grado ya
             applyDegChange();
             ref=1;
           } else
           {
             //si vamos peor hay cambiar la pol’tica
             m_cambia=0;
             if(degree_index[m_proc_cambia]!=0 || degree_incr[m_proc_cambia]==1 )
             {//deshacemos el cambio 
               
               //GD  --> para volver al codigo original ejecutar siempre el codigo del condicional
               if(flagBeh!=2 && m_version==0)
     			 {
                   degree_incr[m_proc_cambia] *= -1;
               //cambiamos el grado ya
                   applyDegChange()	;
                 }
             } else degree_incr[m_proc_cambia] *= -1;
             
             m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
             
        	 
             applyDegChange();
          
           }  
          
          } else
          {//vamos bien
              m_cambia=1;
              ins_epoch_ref= ins_this_epoch;
        	  
             // accesos_epoch_1_global_tot=accesos_global;
        	  min_owner=m_proc_cambia;
        	  m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
        	  
        	  utilidad_epoch[m_proc_cambia]*=0.5;
        	 if(double(tratadas_epoch_1[m_proc_cambia])!=0) utilidad_epoch[m_proc_cambia]+=0.5*(double(utiles_epoch_1[m_proc_cambia])/double(tratadas_epoch_1[m_proc_cambia]));
        	 
        	 if(utilidad_epoch[m_proc_cambia]*100.0 <g_UTILITY_THRES && utilidad_epoch[m_proc_cambia]>0 && degree_incr[m_proc_cambia] == 1) degree_incr[m_proc_cambia] *= -1;
        	 
             applyDegChange();
          }
          
      }
      
      
      misses_this_epoch[m_proc_cambia]=0; 
      misses_this_epoch_global=0;
      accesos_global=0;
      
      ins_epoch_ant= g_system_ptr->getProfiler()->getTotalInstructionsExecuted();
} 

//La variante 18 est‡ guiada por la tasa de fallos GLOBAL y tiene un umbral de corte que usa la utilidad de la preb
void Prefetcher::adUTUT18()
{
		static int ref=1;
		
        utilidad_epoch[m_proc_cambia]*=0.5;
        if(double(tratadas_epoch_1[m_proc_cambia])!=0) utilidad_epoch[m_proc_cambia]+=0.5*(double(utiles_epoch_1[m_proc_cambia])/double(tratadas_epoch_1[m_proc_cambia]));
       // double auxutil, auxmiss;
             
     //  cerr << "misses_this_epoch_global " << misses_this_epoch_global << " accesos_global:" << accesos_global<< endl;
       
       uint64 numberAccesses=0, numberMisses=0;
       
       //cerr << endl << "m_version: " << m_version << " --- " << g_system_ptr->getDriver()->getCycleCount(0) << " ";
       
       
       for(int i=0; i<RubyConfig::numberOfL2CachePerChip(); i++ )
       {
         uint64 a1=g_system_ptr->getPrefetcher(i)->getAccesos();
         uint64 a2=g_system_ptr->getPrefetcher(i)->getMisses();
         
         numberAccesses += a1;
         numberMisses += a2;
         
       }
       
        // cerr << "numberAccesses " << numberAccesses << " numberMisses:" << numberMisses<< endl;

       if(accesos_global!=0) auxratio=(double)numberMisses/(double)numberAccesses; 
       else accesos_global=0;
       
        
        utiles_epoch_1[m_proc_cambia]=0, tratadas_epoch_1[m_proc_cambia]=0;
        
       if(ref)
       {
         ref=0;
         m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
         applyDegChange();
         utilmiss_epoch_global=auxratio;
         
       } else 
       {
         if(auxratio > utilmiss_epoch_global)
         {           
           if(min_owner==m_proc_cambia)
           {
             m_cambia=2;
             misses_epoch_1_global=misses_this_epoch_global, m_misses_1[m_proc_cambia]=misses_this_epoch[m_proc_cambia] ;  
             utilmiss_epoch_global=auxratio;
             degree_incr[m_proc_cambia] *= -1;
             //cambiamos el grado ya
             applyDegChange();
             ref=1;
           } else
           {
             //si vamos peor hay cambiar la pol’tica
             m_cambia=0;
             if(degree_index[m_proc_cambia]!=0 || degree_incr[m_proc_cambia]==1 )
             {//deshacemos el cambio                
                   degree_incr[m_proc_cambia] *= -1;
               //cambiamos el grado ya
                   applyDegChange()	;
             } else degree_incr[m_proc_cambia] *= -1;
             
             m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
             
             utilidad_epoch[m_proc_cambia]*=0.5;
        	 if(double(tratadas_epoch_1[m_proc_cambia])!=0) utilidad_epoch[m_proc_cambia]+=0.5*(double(utiles_epoch_1[m_proc_cambia])/double(tratadas_epoch_1[m_proc_cambia]));
        	 
        	 //cerr << "ut1: " << g_UTILITY_THRES << endl;
        	 if(utilidad_epoch[m_proc_cambia]*100.0<g_UTILITY_THRES && utilidad_epoch[m_proc_cambia]>0 && degree_incr[m_proc_cambia] == 1) degree_incr[m_proc_cambia] *= -1;
             
             applyDegChange();
          
           }  
          
          } else
          {//vamos bien
              m_cambia=1;
              misses_epoch_1_global=misses_this_epoch_global;
              utilmiss_epoch_global=auxratio;
        	  m_misses_1[m_proc_cambia]=misses_this_epoch[m_proc_cambia];
        	  
             // accesos_epoch_1_global_tot=accesos_global;
        	  min_owner=m_proc_cambia;
        	  m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
        	  
        	  utilidad_epoch[m_proc_cambia]*=0.5;
        	 if(double(tratadas_epoch_1[m_proc_cambia])!=0) utilidad_epoch[m_proc_cambia]+=0.5*(double(utiles_epoch_1[m_proc_cambia])/double(tratadas_epoch_1[m_proc_cambia]));
        	 //cerr << "ut2: " << g_UTILITY_THRES << endl;
        	 
        	 if(utilidad_epoch[m_proc_cambia]*100.0 <g_UTILITY_THRES && utilidad_epoch[m_proc_cambia]>0 && degree_incr[m_proc_cambia] == 1) degree_incr[m_proc_cambia] *= -1;
        	 
             applyDegChange();
          }
          
      }
      
      
      misses_this_epoch[m_proc_cambia]=0; 
      misses_this_epoch_global=0;
      accesos_global=0;
}  


//La variante 15 est‡ guiada por la tasa de fallos en el banco y tiene un umbral de corte que usa la utilidad de la preb
void Prefetcher::adUTUT19()
{
		
		
       // double auxutil, auxmiss;
             
     //  cerr << "misses_this_epoch_global " << misses_this_epoch_global << " accesos_global:" << accesos_global<< endl;
       
       if(accesos_global!=0) auxratio=(double)misses_this_epoch_global/(double)accesos_global; 
       else accesos_global=0;
       
       if(ref)
       { 
         ref=0;
         
         //para que las dos epocas de prueba nuevas no coincidan cuando los grados son 0 o 16:
         if(degree_index[m_proc_cambia] ==0 || degree_index[m_proc_cambia] ==(m_metodo==10 || m_metodo==11 ? ndegreesStr : ndegreesSEQT)) 
           degree_incr[m_proc_cambia] *= -1;
     
         applyDegChange2();
         utilmiss_epoch_global=auxratio;
         
         
       } else 
       {
         if(auxratio > utilmiss_epoch_global)
         {           
             //si vamos peor hay cambiar la pol’tica
             m_cambia=0;
            
               
             degree_incr[m_proc_cambia] *= -1;
               //cambiamos el grado ya
             applyDegChange2()	;
             
             m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
             
             if(min_owner==m_proc_cambia)
             { 
               m_cambia=2;
               ref=1;
             } 
             else {
               applyDegChange2();
            }
             
          
          } else
          {//vamos bien 
         
              m_cambia=1;
              misses_epoch_1_global=misses_this_epoch_global;
              utilmiss_epoch_global=auxratio;
        	  m_misses_1[m_proc_cambia]=misses_this_epoch[m_proc_cambia];
        	  
        	          	  
             // accesos_epoch_1_global_tot=accesos_global;
        	  min_owner=m_proc_cambia;
        	  m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
        	  
       	 
             applyDegChange2();
          }
          
      }
      
      
      misses_this_epoch[m_proc_cambia]=0; 
      misses_this_epoch_global=0;
      accesos_global=0;
}  

//mecanismo normal (miss ratio banco) pero sin utilidad
void Prefetcher::adUTUT20()
{
				
       // double auxutil, auxmiss;
             
     //  cerr << "misses_this_epoch_global " << misses_this_epoch_global << " accesos_global:" << accesos_global<< endl;
       
       if(accesos_global!=0) auxratio=(double)misses_this_epoch_global/(double)accesos_global; 
       else accesos_global=0;
               
       
       if(ref)
       { 
         ref=0;
         
         //para que las dos epocas de prueba nuevas no coincidan cuando los grados son 0 o 16:
         if(degree_index[m_proc_cambia] ==0 || degree_index[m_proc_cambia] ==(m_metodo==10 || m_metodo==11 ? ndegreesStr : ndegreesSEQT)) 
           degree_incr[m_proc_cambia] *= -1;
     
         applyDegChange();
         utilmiss_epoch_global=auxratio;
         
         
       } else 
       {
         if(auxratio > utilmiss_epoch_global)
         {           
             //si vamos peor hay cambiar la pol’tica
             m_cambia=0;            
               
             degree_incr[m_proc_cambia] *= -1;
               //cambiamos el grado ya
             applyDegChange()	;
             
             m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
             
             if(min_owner==m_proc_cambia)
             { 
               m_cambia=2;
               ref=1;
             } 
             else {
               applyDegChange();
            }            
          
          } else
          {//vamos bien 
         
              m_cambia=1;
              misses_epoch_1_global=misses_this_epoch_global;
              utilmiss_epoch_global=auxratio;
        	  m_misses_1[m_proc_cambia]=misses_this_epoch[m_proc_cambia];
        	  
        	          	  
             // accesos_epoch_1_global_tot=accesos_global;
        	  min_owner=m_proc_cambia;
        	  m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
        	  
       	 
             applyDegChange();
          }
          
      }
      misses_this_epoch[m_proc_cambia]=0; 
      misses_this_epoch_global=0;
      accesos_global=0;
}  

//mecanismo miss ratio global 
void Prefetcher::adUTUT21()
{
				
       // double auxutil, auxmiss;
             
     //  cerr << "misses_this_epoch_global " << misses_this_epoch_global << " accesos_global:" << accesos_global<< endl;
       
       for(int i=0; i<RubyConfig::numberOfL2CachePerChip(); i++ )
       {
         uint64 a1=g_system_ptr->getPrefetcher(i)->getAccesos();
         uint64 a2=g_system_ptr->getPrefetcher(i)->getMisses();
         
         numberAccesses += a1;
         numberMisses += a2;
         
       }
       
        // cerr << "numberAccesses " << numberAccesses << " numberMisses:" << numberMisses<< endl;

       if(accesos_global!=0) auxratio=(double)numberMisses/(double)numberAccesses; 
       else accesos_global=0;
       
       if(ref)
       { 
         ref=0;
         
         //para que las dos epocas de prueba nuevas no coincidan cuando los grados son 0 o 16:
         if(degree_index[m_proc_cambia] ==0 || degree_index[m_proc_cambia] ==(m_metodo==10 || m_metodo==11 ? ndegreesStr : ndegreesSEQT)) 
           degree_incr[m_proc_cambia] *= -1;
     
         applyDegChange2();
         utilmiss_epoch_global=auxratio;
         
         
       } else 
       {
         if(auxratio > utilmiss_epoch_global)
         {           
             //si vamos peor hay cambiar la pol’tica
             m_cambia=0;            
               
             degree_incr[m_proc_cambia] *= -1;
               //cambiamos el grado ya
             applyDegChange2()	;
             
             m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
             
             if(min_owner==m_proc_cambia)
             { 
               m_cambia=2;
               ref=1;
             } 
             else {
               applyDegChange2();
            }            
          
          } else
          {//vamos bien 
         
              m_cambia=1;
              misses_epoch_1_global=misses_this_epoch_global;
              utilmiss_epoch_global=auxratio;
        	  m_misses_1[m_proc_cambia]=misses_this_epoch[m_proc_cambia];
        	  
        	          	  
             // accesos_epoch_1_global_tot=accesos_global;
        	  min_owner=m_proc_cambia;
        	  m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
        	  
       	 
             applyDegChange2();
          }
          
      }
      misses_this_epoch[m_proc_cambia]=0; 
      misses_this_epoch_global=0;
      accesos_global=0;
}  

//mecanismo miss ratio global pero sin utilidad
void Prefetcher::adUTUT22()
{
				
       // double auxutil, auxmiss;
             
     //  cerr << "misses_this_epoch_global " << misses_this_epoch_global << " accesos_global:" << accesos_global<< endl;
       for(int i=0; i<RubyConfig::numberOfL2CachePerChip(); i++ )
       {
         uint64 a1=g_system_ptr->getPrefetcher(i)->getAccesos();
         uint64 a2=g_system_ptr->getPrefetcher(i)->getMisses();
         
         numberAccesses += a1;
         numberMisses += a2;
         
       }
       
        // cerr << "numberAccesses " << numberAccesses << " numberMisses:" << numberMisses<< endl;

       if(accesos_global!=0) auxratio=(double)numberMisses/(double)numberAccesses; 
       else accesos_global=0;
       
                     
       if(ref)
       { 
         ref=0;
         
         //para que las dos epocas de prueba nuevas no coincidan cuando los grados son 0 o 16:
         if(degree_index[m_proc_cambia] ==0 || degree_index[m_proc_cambia] ==(m_metodo==10 || m_metodo==11 ? ndegreesStr : ndegreesSEQT)) 
           degree_incr[m_proc_cambia] *= -1;
     
         applyDegChange();
         utilmiss_epoch_global=auxratio;
         
         
       } else 
       {
         if(auxratio > utilmiss_epoch_global)
         {           
             //si vamos peor hay cambiar la pol’tica
             m_cambia=0;            
               
             degree_incr[m_proc_cambia] *= -1;
               //cambiamos el grado ya
             applyDegChange()	;
             
             m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
             
             if(min_owner==m_proc_cambia)
             { 
               m_cambia=2;
               ref=1;
             } 
             else {
               applyDegChange();
            }            
          
          } else
          {//vamos bien 
         
              m_cambia=1;
              misses_epoch_1_global=misses_this_epoch_global;
              utilmiss_epoch_global=auxratio;
        	  m_misses_1[m_proc_cambia]=misses_this_epoch[m_proc_cambia];
        	  
        	          	  
             // accesos_epoch_1_global_tot=accesos_global;
        	  min_owner=m_proc_cambia;
        	  m_proc_cambia= (m_proc_cambia < RubyConfig::numberOfProcsPerChip()-1) ? m_proc_cambia+1 : 0;
        	  
       	 
             applyDegChange();
          }
          
      }
      misses_this_epoch[m_proc_cambia]=0; 
      misses_this_epoch_global=0;
      accesos_global=0;
}  
 
void Prefetcher::applyDegChange()
{
  /* if(m_st_base_degree[m_proc_cambia]==0)
   {
     int aux=rand() % 3;
     if(!aux)
     {
       aux=rand() % 3;
       degree_index[m_proc_cambia]= aux ? 1 : 2;;
     }
   }
   else */
   {
     
     degree_index[m_proc_cambia] += degree_incr[m_proc_cambia];
     if(degree_index[m_proc_cambia] <0) degree_index[m_proc_cambia]=0;
     else if(degree_index[m_proc_cambia] ==(m_metodo==10 || m_metodo==11 ? ndegreesStr : ndegreesSEQT)) degree_index[m_proc_cambia]=(m_metodo==10 || m_metodo==11 ? ndegreesStr : ndegreesSEQT)-1;
   }
   
   m_st_base_degree[m_proc_cambia]=(m_metodo==10 || m_metodo==11 ? degreesS : degrees)[degree_index[m_proc_cambia]];
   
    utiles_epoch_1[m_proc_cambia]=0, tratadas_epoch_1[m_proc_cambia]=0;
     
}

void Prefetcher::applyDegChange2()
{

      utilidad_epoch[m_proc_cambia]*=0.5;
      if(double(tratadas_epoch_1[m_proc_cambia])!=0) utilidad_epoch[m_proc_cambia]+=0.5*(double(utiles_epoch_1[m_proc_cambia])/double(tratadas_epoch_1[m_proc_cambia]));
      //cerr << "ut2: " << g_UTILITY_THRES << endl;
        	 
      if(utilidad_epoch[m_proc_cambia]*100.0 <g_UTILITY_THRES && utilidad_epoch[m_proc_cambia]>0 && degree_incr[m_proc_cambia] == 1 && degree_index[m_proc_cambia]!=0) degree_incr[m_proc_cambia] *= -1;
     
     
     degree_index[m_proc_cambia] += degree_incr[m_proc_cambia];
     
     if(degree_index[m_proc_cambia] <0) degree_index[m_proc_cambia]=0;
     else if(degree_index[m_proc_cambia] ==(m_metodo==10 || m_metodo==11 ? ndegreesStr : ndegreesSEQT)) degree_index[m_proc_cambia]=(m_metodo==10 || m_metodo==11 ? ndegreesStr : ndegreesSEQT)-1;
   
   
   m_st_base_degree[m_proc_cambia]=(m_metodo==10 || m_metodo==11 ? degreesS : degrees)[degree_index[m_proc_cambia]];
   
    utiles_epoch_1[m_proc_cambia]=0, tratadas_epoch_1[m_proc_cambia]=0;
     
}

void Prefetcher::applyDegChange(int j)
{
   degree_index[j] += degree_incr[j];
   if(degree_index[j] <0) degree_index[j]=0;
   else 
     if( m_metodo==1)
       if(degree_index[j] ==ndegreesPatt) degree_index[j]=ndegreesPatt-1;
     else
   		if(degree_index[j] ==ndegreesStr) degree_index[j]=ndegreesStr-1;
   		
    m_st_base_degree[j]=degreesPatt[degree_index[j]];
}


void Prefetcher::getPrefetch()
{  
  RequestMsg out_msg;      
  if(!buffer.empty())
  {
  
    //extraemos la prebusqueda que toca del buffer  
    nodo& uno=buffer.remove();
    (out_msg).m_Address = uno.addr;    
        //CAMBIAR PARA A„ADIR ESCRITURA!!!  
    (out_msg).m_Type = m_tipo==1 ? CoherenceRequestType_PREFS : CoherenceRequestType_PREFS;
    (out_msg).m_MessageSize = MessageSizeType_Control;
    (out_msg).m_RequestorMachId = uno.req;
    (out_msg).m_coreID = uno.req;
    (out_msg).m_ProgramCounter = uno.pc;
    assert(uno.req.type == MachineType_L1Cache);
    (out_msg).m_epoch = m_epoch;
         
    insertadasCache[L1CacheMachIDToProcessorNum(uno.req)]++; //cout << "insertadasCache" << endl;
    m_chip_ptr->m_L2Cache_prefetchQueue_vec[m_version]->enqueue(out_msg);
    //para las estad’sticas de latencia de las prebœsquedas en el TBE
    //m_map.add(uno.addr, nodoLat(uno.addr,  g_system_ptr->getDriver()->getCycleCount(m_version) , L1CacheMachIDToProcessorNum(m_requestor)));
    
    port=uno;
  	vacio=false;
  	 return;
  	 
  }
  else vacio=true;
}


//##############################################

  void Prefetcher::firstUse(Address addr, Address pc, int tipo)
  {
  //	cerr << "firstUse " <<  int_to_string(g_eventQueue_ptr->getTime()) << endl;
  Time current_time = g_eventQueue_ptr->getTime();
  m_tipo=tipo;
  //CAMBIAR!!
  
  
  if(m_metodo==1)
  {
    m_st_degree[m_proc_miss]=m_st_base_degree[m_proc_miss];
     m_last_addr[m_proc_miss]=Address(addr.maskLowOrderBits(RubyConfig::dataBlockBits()));
    
  } else if(m_metodo==2)
  {
    m_last_pc[m_proc_miss]=pc;
    m_pref_last_addr[m_proc_miss]=Address(addr.maskLowOrderBits(RubyConfig::dataBlockBits()));
    m_flag_cabeza=1;
  }

    g_eventQueue_ptr->scheduleEvent(this, 1); 
    
  }
  
  
  
  //#############################################
uint Prefetcher::getPCDegree(Address pc)
{
  //cerr << "getPCDegree: " << pc;
  int idx= pc.getAddress() & PCTABLE_MASK;

  if(PCTable[idx].PC==pc)
  {
    //cerr << "getPCDegree: " << pc <<endl;
    return PCTable[idx].aggr;
  } else
  {
     //cerr << "getPCDegree: " << pc << " insertadico " << endl;
    PCTable[idx].PC=pc;
    PCTable[idx].aggr=4;
    PCTable[idx].useCnt=0;
    PCTable[idx].prefCnt=0;
  }
  return PCTable[idx].aggr;
  //cerr << endl;
}

void Prefetcher::hitOnPref (Address pc)
{
if(m_metodo==3)
{
  int idx= pc.getAddress() & PCTABLE_MASK;

  if(PCTable[idx].PC==pc)
  {
    PCTable[idx].useCnt++;
    return;
  } else
  {
    //cerr << "eh" << endl; //assert(1==0);
    
    PCTable[idx].useCnt++;
    return;
    
    PCTable[idx].PC=pc;
    PCTable[idx].aggr=4;
    PCTable[idx].useCnt=0;
    PCTable[idx].prefCnt=0;
  }
}
}
  
void Prefetcher::issued(Address pc)
{
//cerr << "issued: " << pc ;
if(m_metodo==3)
{
  static const uint aggrMax=16;
  int idx= pc.getAddress() & PCTABLE_MASK;
  
  if(PCTable[idx].PC.getAddress()==pc.getAddress())
  {
    PCTable[idx].prefCnt++;
   // cerr << PCTable[idx].PC << " " << PCTable[idx].useCnt << endl;
    if(PCTable[idx].prefCnt ==16)
    {
      PCTable[idx].prefCnt=0;
      if(PCTable[idx].useCnt > 12)
      {
        PCTable[idx].aggr= PCTable[idx].aggr==aggrMax-1 ? aggrMax-1 : PCTable[idx].aggr+1 ;
      } else if(PCTable[idx].useCnt < 3)
      {
        PCTable[idx].aggr= PCTable[idx].aggr==0 ? 0 : PCTable[idx].aggr/2 ;
      } else if(PCTable[idx].useCnt < 8)
      {
        PCTable[idx].aggr= PCTable[idx].aggr==0 ? 0 : PCTable[idx].aggr-1 ;
      }
      
      PCTable[idx].useCnt=0;
    } // ==16
  } else
  {
    //cerr << " insertadico ";
    PCTable[idx].PC=pc;
    PCTable[idx].prefCnt=0;
    PCTable[idx].useCnt=0;
    PCTable[idx].aggr=4;
  }

  //if(PCTable[idx].aggr==0) cerr << "PC " << PCTable[idx].PC << " off" << endl;
   //cerr <<  endl;
}
}
  
  void Prefetcher::miss(Address addr, Address pc, int tipo, MachineID node, int firstUse)
  {
    	// cerr << "Prebuscador " <<  m_version << " addr:" << addr <<" @pc: " << pc << " node: " << node << " this: " << this << " ent:" << L1CacheMachIDToProcessorNum(node)<< endl;
static Time current_time;
static Time past_time;
  //sobre la latencia de servicio:
  //if(m_version==0)
  //  cerr  << "ciclo: " << g_system_ptr->getDriver()->getCycleCount(m_version) << " proc:"  << m_proc_miss << " grado: " << m_st_degree[m_proc_miss]<< " base: " << m_st_base_degree[m_proc_miss] << endl ;
if((!g_ONLY_ONE_PREFETCHING || (g_ONLY_ONE_PREFETCHING && g_PROC_AISLADO==L1CacheMachIDToProcessorNum(node))) &&\
(!g_ONLY_ONE_NO_PREFETCHING || (g_ONLY_ONE_NO_PREFETCHING && g_PROC_AISLADO!=L1CacheMachIDToProcessorNum(node))) && \
!g_CARGA_CACHE)
  {
        //Estad’sticas sobre el corte de secuencias de prebusqueda
    cadenas_valor[m_proc_miss][degree_index[m_proc_miss]]+=m_st_degree[m_proc_miss];
    cadenas_nelems[m_proc_miss][degree_index[m_proc_miss]]++;

    m_proc_miss=L1CacheMachIDToProcessorNum(node);
  
  if(!firstUse)
  {
   // m_map.add(addr, nodoLat(addr,  g_system_ptr->getDriver()->getCycleCount(m_version) , L1CacheMachIDToProcessorNum(node)));
    misses_this_epoch_global++;
    misses_this_epoch[m_proc_miss]++;
    m_misses++;
    m_misses_1_proc[m_proc_miss]++;
    
        
    auxMisses++; //solo para EPOCHS_SALTA
    
    //POL inter-core
    for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) 
      {  
        bloomFilterEntry aux=bloomFilterG[j][bloomBitAddress(addr)]; 
        if(aux.valid && aux.proc==node) {
          m_pol_this_epoch[j]++; 
          
        }
      }
      
    //POL local
    bloomFilterEntry aux=bloomFilterL[m_proc_miss][bloomBitAddress(addr)]; 
        if(aux.valid) {
          m_pol_L_this_epoch[m_proc_miss]++; 
          
        }
    
    //m_misses_1[m_proc_miss]++;
    //if(bloomFilter[L1CacheMachIDToProcessorNum(node)][bloomBitAddress(addr)]) m_pol_this_epoch++;
    
  } else {m_firstUses[m_proc_miss]++;}
  
  if((m_metodo==10 || m_metodo==11) && !firstUse) accessStream(addr, node, true);
  
  
  if(g_PREFETCHER && m_metodo!=10 && m_metodo!=11)
  {       
    assert(node.type==MachineType_L1Cache);
    m_requestor=node;
    past_time= current_time;
    current_time = g_eventQueue_ptr->getTime();

 //   cerr << "tiempo desde anterior fallo (" << m_version<<  "):\t" << current_time-past_time << "\tactualidad:\t" << current_cyc << endl; 
  //
  //CAMBIAR PARA A„ADIR ESCRITURA!!!  --> cambiado

    m_tipo= tipo;
    
    int sector, aux;
    switch(m_metodo)
    {
  	  case 2:
      //if(g_DEBUG_PREFETCHER && m_version==0) std::cerr << "AAA: " << m_last_addr[m_proc_miss] << endl;
        m_last_pc[m_proc_miss]=pc;
        m_last_addr[m_proc_miss]=Address(addr.maskLowOrderBits(RubyConfig::dataBlockBits()));
         m_st_degree[m_proc_miss]=m_st_base_degree[m_proc_miss];
        m_flag_cabeza=1;
       break;
     case 3:
        m_last_pc[m_proc_miss]=pc;
        m_st_degree[m_proc_miss]=getPCDegree(pc); //m_st_base_degree[m_proc_miss];
        m_last_addr[m_proc_miss]=Address(addr.maskLowOrderBits(RubyConfig::dataBlockBits()));
        break;
     default:  //SEQT
        m_st_degree[m_proc_miss]=m_st_base_degree[m_proc_miss];
        m_last_addr[m_proc_miss]=Address(addr.maskLowOrderBits(RubyConfig::dataBlockBits()));
        
       break;
  }
	
	
    g_eventQueue_ptr->scheduleEvent(this, 1);
  
 }//g_PREFETCHER
 }  //ONLY_ONE_PREFETCHING
}

void Prefetcher::pattsDecision(uint* dec)
{
/*
El par‡metro recibido es un vector con un entero para cada proc
En funci—n del valor de ese entero tomaremos una decisi—n para las prebusquedas de cada proc:
1: allow local decision
2: allow local throw down
3: global enforces throw down
*/


  for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) degree_incr[j]=0;

  for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) 
  { 
    if(dec[j]==3) {degree_incr[j] = -1;  if(m_version==0) cerr << "must down:" << j << " 1" << endl;}
    else
    {
      degree_incr[j] = 0;
      if(ACC[j] > 0.75)
      {
        if(lateness[j] > 0.01)
        {
          if(m_version==0) cerr << "proca:" << j << " 1" << endl;
          degree_incr[j] = 1;
        }
        else
        {
          if(pollution[j] <= 0.005)
          {degree_incr[j] = -1; if(m_version==0) cerr << "procb:" << j << " 1" << endl;}
        }
      } else if(ACC[j] > 0.4)
      {
        if(lateness[j] > 0.01)
        {
          if(pollution[j] > 0.005)
          { degree_incr[j] = 1; if(m_version==0) cerr << "procc:" << j << " 1" << endl;}
          else
          { degree_incr[j] = -1; if(m_version==0) cerr << "procd:" << j << " 1" << endl;}
        }
        else
        {
          if(pollution[j] <= 0.005)
          { degree_incr[j] = -1; if(m_version==0) cerr << "proce:" << j << " 1" << endl;}
        }
      } else
      {
        if(lateness[j] > 0.01)
        {
          degree_incr[j] = -1; if(m_version==0) cerr << "procf:" << j << " 1" << endl;
        }
        else
        {
          if(pollution[j] <= 0.005)
          { degree_incr[j] = -1; if(m_version==0) cerr << "procg:" << j << " 1" << endl;}
        }
      }
      if(dec[j]==2 && degree_incr[j] == 1) {degree_incr[j] = 0; if(m_version==0) cerr << "proch:" << j << " 1" << endl;}
    }    
    
    applyDegChange(j);  
    
  }//for(procs)
  
  /*
  
   for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) 
  { 
    if(dec[j]==3) {degree_incr[j] = -1;  if(m_version==0) cerr << "must down:" << j << " 1" << endl;}
    else
    {
      degree_incr[j] = 0;
      if(ACC[j] > 0.75)
      {
        
          if(pollution[j] <= 0.005)
          {degree_incr[j] = -1; if(m_version==0) cerr << "procb:" << j << " 1" << endl;}
        
      } else if(ACC[j] > 0.4)
      {
       
          if(pollution[j] > 0.005)
          { degree_incr[j] = 1; if(m_version==0) cerr << "procc:" << j << " 1" << endl;}
          else
          { degree_incr[j] = -1; if(m_version==0) cerr << "procd:" << j << " 1" << endl;}
        
       
      } else
      {
         degree_incr[j] = -1; if(m_version==0) cerr << "procf:" << j << " 1" << endl;
       
      }
      if(dec[j]==2 && degree_incr[j] == 1) {degree_incr[j] = 0; if(m_version==0) cerr << "proch:" << j << " 1" << endl;}
    }    
    
    applyDegChange(j);
    
  }//for(procs)
 */
 
 
  if(m_version==0) 
  {  
    cerr << "GRADOS: " << "\t";
    for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cerr << m_st_base_degree[j] << "\t";  
        cerr <<endl;
  }
        
  for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) histo_degrees[j][degree_index[j]]++;
}
 
 
void Prefetcher::missOnNonArrivedPref( MachineID node)
{ 
	int core= L1CacheMachIDToProcessorNum(node);
	misses2[core]++;
	
}

void Prefetcher::access(Address a, MachineID node)
{ 

  if((!g_ONLY_ONE_PREFETCHING || (g_ONLY_ONE_PREFETCHING && g_PROC_AISLADO==L1CacheMachIDToProcessorNum(node))) &&\
  (!g_ONLY_ONE_NO_PREFETCHING || (g_ONLY_ONE_NO_PREFETCHING && g_PROC_AISLADO!=L1CacheMachIDToProcessorNum(node))) && \
  !g_CARGA_CACHE)
  {
  
    //if(g_DEBUG_PREFETCHER && m_version==0) cerr << "Llega al prebuscador " << m_version <<" un acceso a la dir " << a << " del proc " << node << endl;
	if(m_metodo==10 || m_metodo==11) accessStream(a, node, false);
	accesos_proc[L1CacheMachIDToProcessorNum(node)]++;
  }
	accesos_global++;
}

void Prefetcher::removeAccess(MachineID node)
{

  if((!g_ONLY_ONE_PREFETCHING || (g_ONLY_ONE_PREFETCHING && g_PROC_AISLADO==L1CacheMachIDToProcessorNum(node))) &&\
  (!g_ONLY_ONE_NO_PREFETCHING || (g_ONLY_ONE_NO_PREFETCHING && g_PROC_AISLADO!=L1CacheMachIDToProcessorNum(node))) && \
  !g_CARGA_CACHE)
  {
  
   // if(g_DEBUG_PREFETCHER && m_version==0) cerr << "Llega al prebuscador " << m_version <<" un acceso a la dir " << a << " del proc " << node << endl;
	
	accesos_proc[L1CacheMachIDToProcessorNum(node)]--;
  }
	accesos_global--;
	numberAccesses--;
}
uint64* Prefetcher::getUtiles()
{
  uint64 *aux=new uint64 [RubyConfig::numberOfProcsPerChip()];
  
  for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) 
  {  aux[j]=utiles_epoch_1[j];
     utiles_epoch_1[j]=0; 
  }
  
  return aux;
}



uint64* Prefetcher::getTratadas()
{
  uint64 *aux=new uint64 [RubyConfig::numberOfProcsPerChip()];
  
  for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) 
  {  aux[j]=tratadas_epoch_1[j];
     tratadas_epoch_1[j]=0; 
  }
  
  return aux;
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


 void Prefetcher::stats2(int t, MachineID node, int epoch)
 {
 
   //cerr << "stats2: " << node << endl;
   int proc=L1CacheMachIDToProcessorNum(node);
   int aux=m_epoch-epoch;
   if(t<0 || t>21) {ERROR_MSG("Parametro fuera de rango");}
   else
     switch(t)
     {
       case 0:
         tratadas[proc]++;
         //cout << "tratadas" << endl;
         tratadas_epoch_1[proc]++;
         tratadas_epoch_global++;
         break;
       case 1:
       case 2:
         utiles[proc]++;
         utiles_epoch_1[proc]++;
         utiles_epoch_global++;        
         
         if(aux > n_epochs-1) aux=n_epochs-1;
         
         pref_epoch_1[proc][aux]++;
         pref_epoch_global[aux]++;
         //if(g_DEBUG_PREFETCHER)   if(m_version==0 ) cerr << "hace estas epocas: " << m_epoch-epoch << endl;
         break;
       case 3:
         inutiles[proc]++;
         inutiles_global++;
         break;
       case 4:  //reemplazos
         repls_epoch_1[proc]++;
         repls_epoch_global++;
         //Patt multibanco, detectamos si la cantidad de reemplazos ha llegado al m‡ximo por Žpoca
         //if(!(repls_epoch_global%500))if(m_version==0) cout << "hey: " <<  repls_epoch_global << endl;
         if(repls_epoch_global>2048 && g_VARIANTE==13)
         { 
           evaluateMetrics();
           repls_epoch_global=0;
           for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++){ misses_this_epoch[j]=0; m_pol_this_epoch[j]=0; m_pol_L_this_epoch[j]=0; lates_epoch_1[j]=0; }
           lates_epoch_global=0;
          
         }
         break;
       case 5:  //prebusquedas late
         lates_epoch_1[proc]++;
         lates_epoch_global++;
         //cout << "hola------------------------------" << endl; 
         break;
       default:
         break;
     }
  }


void Prefetcher::statsLat(int t, Address a)
{
Time aux;
	switch(1)
	{
	 
	  case 2:
	    if(m_map.exist(a)) 
	     {
	       aux=  g_system_ptr->getDriver()->getCycleCount(0)  - (m_map.lookup(a)).time;
	       if(aux>1000)cerr << "a " << a << " ahora: " <<  g_system_ptr->getDriver()->getCycleCount(0)  << "  antes: " << (m_map.lookup(a)).time << " dif: " << aux << endl;
	       //cerr << "dem: " << aux<< endl;
	       lat_acum_1[(m_map.lookup(a)).proc]+=aux;
	       lat_acum_todos+=aux;
	       lats_demand.add(aux);
	       lats_gral.add(aux);
	       //cerr << "time: " << g_eventQueue_ptr->getTime() - aux << endl;
	       m_map.erase(a);
	     }
	     break;
	  case 3:
	     if(m_map.exist(a)) 
	     {
	        
	       aux=  g_system_ptr->getDriver()->getCycleCount(0)  - (m_map.lookup(a)).time;
	       if(aux>1000)cerr << "b ahora: " <<  g_system_ptr->getDriver()->getCycleCount(0)  << "  antes: " << (m_map.lookup(a)).time << " dif: " << aux << endl;
	       //cerr << "preb: " << aux<< endl;
	       lat_acum_1[(m_map.lookup(a)).proc]+=aux;
	       lat_acum_todos+=aux;
	       lats_pref.add(aux);
	        lats_gral.add(aux);
	       //cerr << "time: " << g_eventQueue_ptr->getTime() - aux << endl;
	       m_map.erase(a);
	     }
	    break;
	  default:
	    break;
	}
}


  // Private copy constructor and assignment operator
 // Prefetcher::Prefetcher(const Prefetcher& obj) {0; }
  //	Prefetcher::Prefetcher& operator=(const Prefetcher& obj)  {0; }
  
//Funciones necesarias para el mecanismo propuesto en Coordinated Control of Multiple Prefetchers




//***************************  STREAMS ****************************************************************

//#define n_streams 32*16

void Prefetcher::actualizaLRUstreams(int i)
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
void Prefetcher::actualizaLRUstreamsInv(int i)
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
void Prefetcher::actualizaLRUstreamsDel(int i)
{
// cerr << "actualizaLRUstreamsDel " << i	<< endl;
  
  assert(streams[i]!=NULL);
  
  int aux=streams[i]->LRUpos;
  
  int j=0;
  for(; j<n_streams ; j++) if(streams[j]!=NULL && streams[j]->state!=-1 && streams[j]->LRUpos > aux)  streams[j]->LRUpos--;

  streams[i]->LRUpos=0;
  //  for(j=0; j<n_streams ; j++) if(streams[j]!=NULL) {cerr << "i: " << j << " " << streams[j]->LRUpos << endl;}
}


bool Prefetcher::accessStream(Address a, MachineID node, bool miss)
{
 
  Address add=a;
  add.makeLineAddress();
  
  uint64 aAux=add.getAddress();
  
  int nproc= L1CacheMachIDToProcessorNum(node);
//  cerr << "p:" << nproc << endl;
//   if(g_DEBUG_PREFETCHER)   if(m_version==0 && nproc==4)  cerr << "Entramos en access"<< (miss?" fallo" : " acierto" )<<endl;	
//if(g_DEBUG_PREFETCHER)   cerr << "Entramos en access"<< (miss?" fallo" : " acierto" )<<endl;	
  s_accesos[nproc]++;
  
  int aux;
  ////Stream* streams= stream.streams
  //(Stream*) streams[n_streams]= &(streams.streams);
  int flag=0;
  int i=0;
  
    //for(; i<n_streams && !flag; i++)
    for(; i<n_streams; i++)
    { 
     
      if(streams[i]!=NULL && streams[i]->state!=-1 && streams[i]->test(aAux, node) )
      {
        
        switch(streams[i]->state)
        {
          
          case 2:          
          case 3:
           //streams[i]->deg=degrees[streams[i]->nproc];            
              if(g_DEBUG_PREFETCHER) if(m_version==0)  cerr << "Stream\t" << i << " en estado " << streams[i]->state<< " aumenta el grado  A:" <<
                    streams[i]->A << " " << aAux << " [" <<g_system_ptr->getDriver()->getCycleCount(0) << "]" <<endl;
              s_positivos[nproc]++;
              
              streams[i]->deg+= degreesS[degree_index[nproc]];
              g_eventQueue_ptr->scheduleEvent(this, 1); 
              //cerr << "encontrado stream valido " << i << endl;
              flag=1;
              
              ideal[nproc]+=degreesS[degree_index[nproc]];
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
      if(streams[i]!=NULL && streams[i]->state>-1 && streams[i]->test(aAux, node) )
      switch(streams[i]->state)
      {
        case 0:
           if(g_DEBUG_PREFETCHER) if(m_version==0 && nproc==6) cerr << "Stream\t" << i << " pasa al estado 1 A:" <<
                    streams[i]->A << " " << aAux << " [" <<g_system_ptr->getDriver()->getCycleCount(0) << "]" <<endl;
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
            
            streams[i]->d=distances[degree_index[streams[i]->nproc]];
            
            uint64 daux;

           // if(g_DEBUG_PREFETCHER) if(m_version==0 && nproc==6)cerr << "nproc: " << streams[i]->nproc << " dis: " << distances[degree_index[streams[i]->nproc]]] << " ABS((int)aAux - (int)streams[i]->A) : " << ABS((int)aAux - (int)streams[i]->A) << "  streams[i]->d*RubyConfig::dataBlockBytes(): " << streams[i]->d << " " << RubyConfig::dataBlockBytes() << endl; 
            
            if(ABS((int)aAux - (int)streams[i]->A) < streams[i]->d*RubyConfig::dataBlockBytes())  //no hemos llegado al tama–o de region = distancia
            {
              
              if(g_DEBUG_PREFETCHER) if(m_version==0 && nproc==6) cerr << "Stream\t" << i << " pasa al estado 2 A:" <<
                  streams[i]->A << " " << aAux << " [" <<g_system_ptr->getDriver()->getCycleCount(0) << "]" <<endl;
                  
              streams[i]->state=2; 
              g_eventQueue_ptr->scheduleEvent(this, 1); 

            } else 
            {  //hemos llegado a un tama–o de regi—n igual a d
              
             
             if(g_DEBUG_PREFETCHER) if(m_version==0 && nproc==6) cerr << "Stream\t" << i << " pasa al estado 3 A:" << 
                      streams[i]->A << " " << aAux << " [" <<g_system_ptr->getDriver()->getCycleCount(0) << "]" <<endl;
                      
             streams[i]->state=3;
             g_eventQueue_ptr->scheduleEvent(this, 1); 
              streams[i]->A= streams[i]->E - streams[i]->d * RubyConfig::dataBlockBytes() * streams[i]->dir;
            }
            
            streams[i]->deg=degreesS[degree_index[nproc]];
            
            //stats
            ideal[streams[i]->nproc]+=streams[i]->deg;
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

    //Ningœn stream correspondia, buscamos una entrada invalida
    for(i=0; i<n_streams && !flag && miss; i++) 
      if(streams[i]==NULL  || (streams[i]!=NULL && streams[i]->state==-1))
      {  
        //if(g_DEBUG_PREFETCHER)  if(m_version==0 &&nproc==4)  cerr << "entradica invalida " << a.getAddress() <<endl;
        actualizaLRUstreamsInv(i); 
        //if(streams[i]!=NULL) delete streams[i]; 
         if(g_DEBUG_PREFETCHER) if(m_version==0 && nproc==6) cerr << "Stream\t" << i  << " creado por el procesador " << nproc << " (invalida)" << 
          " [" <<g_system_ptr->getDriver()->getCycleCount(0) << "]" << endl;
          
         //if(g_DEBUG_PREFETCHER)  cerr << "Stream\t" << i  << " creado por el procesador " << nproc << " (invalida)" <<
          //       " [" <<g_system_ptr->getDriver()->getCycleCount(m_version) << "]" << endl;
        //streams[i]=new Stream(aAux, node, degreesS[degree_index[nproc]], distances[degree_index[nproc]], m_version); 
        newStream(i, aAux, node, degreesS[degree_index[nproc]], distances[degree_index[nproc]], m_version); 
       
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
       
      if(g_DEBUG_PREFETCHER) if(m_version==0 && nproc==6) cerr << "Stream\t" << i  << " creado por el procesador " << 
              nproc << " [" <<g_system_ptr->getDriver()->getCycleCount(0) << "]" << endl;
              
       //if(g_DEBUG_PREFETCHER) cerr << "Stream\t" << i  << " creado por el procesador " << nproc <<  endl;
       
        //streams[i]=new Stream(aAux, node, degreesS[degree_index[nproc]], distances[degree_index[nproc]], m_version); 
        
        
        newStream(i, aAux, node, degreesS[degree_index[nproc]], distances[degree_index[nproc]], m_version); 
        
        
          //if(g_DEBUG_PREFETCHER) if(m_version==0 && nproc==4) cerr << "i:" << i <<" ";
        
        flag=1;
        
        s_eliminados[nproc]++;
      
      
    }

    if(!flag && miss) cerr << nproc <<" la destruccion de Occidente " << m_version << endl, exit(0);
    return true;
} //access

void Prefetcher::streamsAggrReview()
{
//  if(g_DEBUG_PREFETCHER) cerr << "entra en aggreRvw()" << m_version << endl;
  for(int i=0; i<n_streams; i++)
  {
    if(streams[i]!=NULL)
    {
      if(streams[i]->state==2) 
      {
        if(ABS((int64)streams[i]->A - (int64)streams[i]->E) >= distances[degree_index[streams[i]->nproc]]*RubyConfig::dataBlockBytes())  //caso normal, aplicamos la nueva distancia
        {
          streams[i]->A=  streams[i]->E - streams[i]->dir*distances[degree_index[streams[i]->nproc]]*RubyConfig::dataBlockBytes();
          streams[i]->state= 3;
        }
        //else --> no pasa nada, seguimos aumentando el tama–o de la ventana
        
      } else if(streams[i]->state==3) 
      {
        if(streams[i]->d < distances[degree_index[streams[i]->nproc]]) //estaremos aumentando la ventana
          streams[i]->state= 2;
        else //
          streams[i]->A=  streams[i]->E - streams[i]->dir*distances[degree_index[streams[i]->nproc]]*RubyConfig::dataBlockBytes();
        
      }
      streams[i]->d=distances[degree_index[streams[i]->nproc]];
      streams[i]->deg=degreesS[degree_index[streams[i]->nproc]];
    }//not NULL
  }//for
 //  if(g_DEBUG_PREFETCHER) cerr << "sale de aggreRvw()" << m_version << endl;
}

Stream::Stream(uint64 a, MachineID pr, int degr, int dis, int version)
{
  m_version=version;
  A=a;
  state=0;
  proc=pr;
  nproc=L1CacheMachIDToProcessorNum(pr);
  E= a + 16*RubyConfig::dataBlockBytes();
  LRUpos=0;
  deg=degr;
  d=dis;
 // if(g_DEBUG_PREFETCHER)  if(m_version==0 && nproc==4)   cerr << "core " << nproc << " proc:" << proc << "\tStream creado con grado " << this->deg << " y distancia " << this->d << "\tdirecc: "<< a<<endl;
}

void Prefetcher::newStream(uint i, uint64 a, MachineID pr, int degr, int dis, int version)
{
  streams[i]->m_version=version;
  streams[i]->A=a;
  streams[i]->state=0;
  streams[i]->proc=pr;
  streams[i]->nproc=L1CacheMachIDToProcessorNum(pr);
  streams[i]->E= a + 16*RubyConfig::dataBlockBytes();
  streams[i]->LRUpos=0;
  streams[i]->deg=degr;
  streams[i]->d=dis;
}

bool Stream::test(uint64 a , MachineID node)
{
         //bool aux=A.getAddress()<a.getAddress() && a.getAddress()<E.getAddress() && node==proc;
         //return aux || (A.getAddress()>a.getAddress() && a.getAddress()>E.getAddress() && node==proc);
  if(A<E) return (a>A && a<E && node==proc);
  else return (a<A && a>E && node==proc);
}

void Prefetcher::clearStats()
{

   for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) { 
   generadas[j]=0; insertadasPAB[j]=0; insertadasCache[j]=0; m_misses=0;  tratadas[j]=0; m_firstUses[j]=0; utiles[j]=0;inutiles[j]=0; m_misses_1[j]=0;
   misses2[j]=0;
   lat_acum_1[j]=0;
   }
   inutiles_global=0;
   lat_acum_todos=0; 
       for(int j=0; j< 40; j++)
       	 cont[j]=0;
  
  lats_demand.clear();
   lats_pref.clear();
  lats_gral.clear();
  
}

uint64 Prefetcher::getMisses()
{

	if(staticK==0) 
	{
	  racc= misses_this_epoch_global;
	}
	
	if(staticK == RubyConfig::numberOfL2CachePerChip()-1) 
	{
	  staticK=0;
	}
	else staticK++;
	
	return racc;
	
}

uint64 Prefetcher::getAccesos()
{

	if(staticK2==0) 
	{
	  racc2= accesos_global;
	}
	  
	if(staticK2 == RubyConfig::numberOfL2CachePerChip()-1) 
	{
	  staticK2=0;
	}
	else staticK2++;
	
   return racc2;
}


void Prefetcher::printStats(ostream& out)
{
  out << cont << endl;
  if(g_PREFETCHER){
  out << "prebuscador " << m_version<<" fallos: " << m_misses	 << endl;
  out << "prebuscador " << m_version<<" fallos ultima epoca: " << auxMisses << endl;
  out << "prebuscador " << m_version<<" primeros usos: " << m_firstUses	 << endl;
  out << "prebuscador " << m_version<<" fallos+primeros usos: " << m_misses+m_firstUses	 << endl;
  for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) out <<  m_misses_1[j]+m_firstUses[j] << "\t";
     out << endl;
  out << "prebuscador " << m_version<<" generadas ideal: " << ideal << endl;  
  out << "prebuscador " << m_version<<" generadas real: " << generadas << endl;
  out << "prebuscador " << m_version<<" insertadas PAB: " << insertadasPAB << endl;
  out << "prebuscador " << m_version<<" lookups: " << insertadasCache << endl;
  out << "prebuscador " << m_version<< " tratadas: " << tratadas << endl;
  out << "prebuscador " << m_version<<" utiles: " << utiles << endl;
  out << "prebuscador " << m_version<<" inutiles: " << inutiles << endl;
  
  out << "prebuscador " << m_version<<" fallos primarios: " << m_misses_1_proc << endl;
  out << "prebuscador " << m_version<<" fallos secundarios: " << misses2 << endl;
   
  out << "latencia gral: " << lats_gral << endl;
  out << "latencia demand: " << lats_demand << endl;
  out << "latencia prefetch: " << lats_pref << endl;
  out << "prebuscador " << m_version << " lat media en el TBE: "<< (double)lat_acum_todos/(double)m_misses <<  endl;
  for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) out << (double)lat_acum_1[j]/(double)m_misses_1_proc[j] << "\t";
   out << endl;
  Vector <double> utilidad; utilidad.setSize(RubyConfig::numberOfProcsPerChip());
  
   for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++)  if(tratadas[j]!=0) utilidad[j]=(double)utiles[j] / (double)tratadas[j];
   	
  out << "prebuscador " << m_version << " utilidad: " << utilidad << endl;
   out << "prebuscador " << m_version << " long media de la cadena restante por grado y proc:" << endl;   
   
   
   for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) 
   {
     for(int k=0; k<11; k++) 
       out << (double)cadenas_valor[j][k] / (double)cadenas_nelems[j][k] << "\t";
     out << endl;
  }  
  
    out << "prebuscador " << m_version<<" grados:" << endl;
    for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++)
    {
      for(int k=0; k<11; k++) out << histo_degrees[j][k] << "\t";
      out << endl;
    }
    
    uint64 aux=0;
    
    out << "prebuscador " << m_version<<" epoca de uso de las prebusquedas:" << endl;
    out << "prebuscador " << m_version<<"global:  " ;
    for(int k=0; k<n_epochs; k++) { aux+= pref_epoch_global[k]; out << pref_epoch_global[k] << "\t";}
      out << endl;
    out << "prebuscador " << m_version<<" right epoch global ratio:  " << (double)pref_epoch_global[0]/(double)aux << endl;  
     for(int k=0; k<n_epochs; k++) out << pref_epoch_global[k] << "\t";
      out << endl;
    
    out << "prebuscador " << m_version<<"local:  " << endl; 
    for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++)
    {
      for(int k=0; k<n_epochs; k++) out << pref_epoch_1[j][k] << "\t";
      out << endl;
    }
    
    out << "prebuscador " << m_version<<" right epoch local ratio: " << endl ;
    for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++)
    {
      aux=0;
      for(int k=0; k<n_epochs; k++) aux+= pref_epoch_1[j][k];
      out << (double)pref_epoch_1[j][0]/(double)aux << "\t";
    }
    out << endl;
    
    
   
      
    if(m_metodo==10 ||m_metodo==11)
    {
      out << "prebuscador " << m_version<< " ascendentes insertadas en el PAB: "  << endl;
      cout << insertadasAsc << endl;
       out << "prebuscador " << m_version<< " descendentes insertadas en el PAB: "  << endl;
      cout << insertadasDesc << endl;
     out << "prebuscador " << m_version<< " s_accesos: "  << endl;
     for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cerr <<  s_accesos[j] << "\t";
     cerr << endl;
     out << "prebuscador " << m_version<< " s_eliminados: "  << endl;
     for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cerr <<  s_eliminados[j] << "\t";
     cerr << endl;
     out << "prebuscador " << m_version<< " s_positivos: "  << endl;
     for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cerr <<  s_positivos[j] << "\t";
     cerr << endl;
     out << "prebuscador " << m_version<< " n_avances2: "  << endl;
     for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cerr <<  n_avances2[j] << "\t";
     cerr << endl;
     out << "prebuscador " << m_version<< " n_avances3: "  << endl;
     for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++)  cerr << n_avances3[j] << "\t";
     cerr << endl;
   }
     
  
  }
  else
  { out << "NO PREFETCHER" << endl; }
  out << "========================="  << endl;
}



#define MASK_16b (0xffff)

    Address Prefetcher::PDFCM_update_and_predict (){
      Address new_last_addr;
      unsigned short new_history;
      short actual_delta, predicted_delta;
      Address pc=m_last_pc[m_proc_miss], addr=m_last_addr[m_proc_miss];
      addr.setAddress(addr.getAddress() >>  RubyConfig::dataBlockBits());
      
      // read PDFCM_HT entry
      // if(g_DEBUG_PREFETCHER) if(m_version==0) cout << "pc: " << pc.getAddress() << endl;
      unsigned int index = pc.getAddress() & PDFCM_HT_mask;
      Address old_last_addr = PDFCM_HT[index].last_addr; 
      unsigned short old_history = PDFCM_HT[index].history; 
      char count = PDFCM_HT[index].count;
   
     //cout << "a:" << PDFCM_HT[index].PC.getAddress() <<"b:" << (pc.getAddress()>>RubyConfig::dataBlockBits()) << endl;
      if (PDFCM_HT[index].PC.getAddress() != ((pc.getAddress() >>PDFCM_HT_bits) & MASK_16b) ){
         // if it's a new PC replace the entry
         PDFCM_HT[index].PC.setAddress(((pc.getAddress() >>PDFCM_HT_bits) & MASK_16b));
         PDFCM_HT[index].history=0; 
         PDFCM_HT[index].last_addr=addr; 
         PDFCM_HT[index].count=0;
         PDFCM_HT[index].tipo=m_tipo;
         //cout << "salida1" << endl;
         return Address(0);
      }
   
      // compute deltas & update confidence counter
      predicted_delta=PDFCM_DT[old_history].delta;
      if(g_DEBUG_PREFETCHER) if(m_version==0) cout << "predicted_delta: " << predicted_delta <<  endl;
      
      actual_delta = (addr.getAddress()-old_last_addr.getAddress()) & MASK_16b;
      if (actual_delta==predicted_delta){
         if (count<3) count++;
      }
      else{ 
         if (count>0) count--;
      }
   
      // compute new history
      
      m_history = PDFCM_hash(old_history, actual_delta);
   
      // write PDFCM_HT entry
      PDFCM_HT[index].last_addr = addr;
      PDFCM_HT[index].history   = m_history;
      PDFCM_HT[index].count=count;
   
      // update PDFCM_DT entry
      PDFCM_DT[old_history].delta = actual_delta;
   
      // predict a new delta using the new history 
      if (count<2) 
      { //cout << "salida2" << endl;
         return Address(0);
      }
      else 
      {
        // cout << "salida3" << endl;
        if(g_DEBUG_PREFETCHER) if(m_version==0) cout << "update:: " << "delta: " <<  PDFCM_DT[m_history].delta << " " << Address((addr.getAddress() + PDFCM_DT[m_history].delta) << RubyConfig::dataBlockBits()) << endl;
         return Address((addr.getAddress() + PDFCM_DT[m_history].delta) << RubyConfig::dataBlockBits());
      }
   }

    Address Prefetcher::PDFCM_predict_next (){

      int delta;
       Address aux=Address(m_last_addr[m_proc_miss].getAddress() >>  RubyConfig::dataBlockBits());
       Address aux2=Address(m_old_addr.getAddress() >>  RubyConfig::dataBlockBits());
       
      // compute delta 
      delta = (aux.getAddress()-aux2.getAddress()) & MASK_16b;
   //cout << "delta: " <<  delta << endl;
      // compute new history
      m_history=PDFCM_hash(m_history, delta);
   //cout << "history: " <<  m_history << endl;
  
  // if(PDFCM_DT[m_history].delta!=0)
     if(g_DEBUG_PREFETCHER) if(m_version==0 ) cerr << "delta: " <<  PDFCM_DT[m_history].delta << endl;
  //cout << "salida next" << m_last_addr.getAddress() + PDFCM_DT[m_history].delta << endl<< endl;;
   
      // predict a new delta using the new history   
     
      	return Address((aux.getAddress() + PDFCM_DT[m_history].delta) <<  RubyConfig::dataBlockBits());

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


void Prefetcher::evaluateMetrics()
{
//cout << "evaluateMetrics" << endl;


    BWC=  (g_system_ptr->getDram(0)->getPattsMetricsBWC());
    BWNO= (g_system_ptr->getDram(0)->getPattsMetricsBWNO());
   
    
    uint64 *tratadas,  *utiles, tratadasTotal[NPROC], utilesTotal[NPROC];;
      
   
    for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++)
    {
      ACC[j]=double(utiles_epoch_1[j])/double(tratadas_epoch_1[j]);
      lateness[j]=double(lates_epoch_1[j])/double(utiles_epoch_1[j]);
      pollution[j]=double(m_pol_L_this_epoch[j])/double(misses_this_epoch[j]);
     // if(g_DEBUG_PREFETCHER && m_version==0) cout << "fallos: " << misses_this_epoch[j] << " pol: " << m_pol_this_epoch[j] <<" ";
    }
 int eliminaHPAC=0;
if(eliminaHPAC)
{
  for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) dec[j]=1;
  pattsDecision(dec);
}

     //if(g_DEBUG_PREFETCHER && m_version==0) cout << endl;
  float cACC=0.6;
  uint cBWNO=75000;
  uint cPOL=90;
  uint cBWC=50000;
  
  cACC=(float)g_pattACC/(float)100;
    cBWNO=g_pattBWNO*1000;
   cPOL=g_pattPOL;
   cBWC=g_pattBWC*1000;
  
  for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++)
  {
    if(ACC[j] < cACC)  //ACCi=low
    {
      if(BWNO[j] > cBWNO){ dec[j]=3; continue; }
      if(m_pol_this_epoch[j] > cPOL) {dec[j]=3; continue;}
      if(BWC[j] < cBWC) {dec[j]=2; continue;}
      else {dec[j]=1; continue; }     
    
    } else //ACCi=high
    {
      if(m_pol_this_epoch[j] < cPOL) { dec[j]=1; continue; }
      else 
        if(BWC[j] < cBWC)
        {
          if(BWNO[j] < cBWNO) {dec[j]=1; continue;}
          else { dec[j]=2; continue; }
        } else 
            if(BWNO[j] < cBWNO) {dec[j]=2; continue;}
            else {dec[j]=3; continue; } 
      // cout << "alarm" << endl;
    }
    
  } //for
   pattsDecision(dec);
    
   if(g_DEBUG_PREFETCHER && m_version==0)
   {
     cout << "prebuscador:\t";
     // for(int j=0; j<RubyConfig::numberOfL2CachePerChip() ; j++) g_system_ptr->getPrefetcher(j)->getPattsMetricsPOL(); 
    
        //for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cout << m_st_base_degree[j] << "\t";      
        for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cout << BWC[j] << "," << BWNO[j] << "," << m_pol_this_epoch [j]<< "\t";      
        cout <<endl;
        for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) cout << lateness[j]<< "," << pollution[j] << ", " << ACC[j] << "\t";      
        cout <<endl;
   }
     for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) m_pol_this_epoch[j]=0;
}


int Prefetcher::bloomBitAddress(Address addr)
{
   //Hacemos 0:11 xor 12:23 de los bits de la direcci—n de bloque
   Address aux=addr;
   aux.makeLineAddress();
   
   return aux.bitSelect(0,11) ^ aux.bitSelect(12,23);
   
}

void Prefetcher::bloomG(int t, Address a, MachineID core, MachineID owner)
{
//cerr << "bloomG" << endl;
  switch(t)
  {
    case 0:
    
     for(int j=0; j<RubyConfig::numberOfProcsPerChip(); j++) 
     {  
        bloomFilterEntry aux=bloomFilterG[j][bloomBitAddress(a)];
        if(aux.valid && aux.proc==owner) bloomFilterG[j][bloomBitAddress(a)].bit=0;
     }
     
      break;
    case 1:
      
      bloomFilterG[L1CacheMachIDToProcessorNum(core)][bloomBitAddress(a)].bit=1;
      bloomFilterG[L1CacheMachIDToProcessorNum(core)][bloomBitAddress(a)].proc=owner;
      bloomFilterG[L1CacheMachIDToProcessorNum(core)][bloomBitAddress(a)].valid=true;
      
break;
    default:
      cerr << "algo esta jodido en las llamadas al bloomF" << endl;
      exit(1);
    break;
  }
  
  //cerr << "bloomG2" << endl;
}

void Prefetcher::bloomL(int t, Address a, MachineID core)
{
//cerr << "bloomL " << t << " " << core << endl;
//if(core.type != MachineType_L1Cache) return;

int nproc=L1CacheMachIDToProcessorNum(core);
 switch(t)
  {
    case 0:
      if(bloomFilterL[nproc][bloomBitAddress(a)].valid) bloomFilterL[nproc][bloomBitAddress(a)].bit=0;
   
     
      break;
    case 1:
      bloomFilterL[nproc][bloomBitAddress(a)].bit=1;
      bloomFilterL[nproc][bloomBitAddress(a)].valid=true;
      
break;
    default:
      cerr << "algo esta jodido en las llamadas al bloomF" << endl;
      exit(1);
    break;
  }
  //cerr << "bloomL2" << endl;
}