
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
 * $Id: SimicsDriver.C 1.12 05/01/19 13:12:31-06:00 mikem@maya.cs.wisc.edu $
 *
 * Description: See SimicsDriver.h for document.
 */


#include "SimicsDriver.h"
#include "interface.h"
#include "System.h"
#include "SubBlock.h"
#include "Profiler.h"
#include "AddressProfiler.h"
#include "SimicsProcessor.h"
#include "SimicsHypervisor.h"

#include "CacheMgr.h"
//JORGE
#include "CacheProfiler.h"

class CacheMgr;


// Simics includes
extern "C" {
#include "simics/api.h"
}

// Macros to get privileged mode bit
#ifdef SPARC
  #define PRIV_MODE (mem_trans->priv)
#else
// x86
  #define PRIV_MODE (mem_trans->mode)
#endif

#ifdef SIMICS30
#define IS_DEV_MEM_OP(foo) (foo == Sim_Initiator_Device)
#define IS_OTH_MEM_OP(foo) (foo == Sim_Initiator_Other)
#endif

// Contructor
SimicsDriver::SimicsDriver(System* sys_ptr) {
cerr << "hey" <<endl;
	if(g_QUICK_MEM) cacheMgr = new CacheMgr(this);

  mean=0;
  cont=0;
  // make sure that MemoryTransactionResult enum and s_stallCycleMap[] are the same size
  assert(s_stallCycleMap[LAST].result == LAST);
   //JORGE
  m_instrucciones.setSize(RubyConfig::numberOfProcessors());
  m_nprocsYa=0;
  // setup processor objects
  m_processors.setSize(RubyConfig::numberOfProcessors());
  m_perfect_memory_firstcall_flags.setSize(RubyConfig::numberOfProcessors());
  
  for(int i=0; i < RubyConfig::numberOfProcessors(); i++){
    m_processors[i] = new SimicsProcessor(sys_ptr, i);
    m_perfect_memory_firstcall_flags[i] = true;
    m_instrucciones[i]=false;
  }
  // setup hypervisor object
  m_hypervisor = new SimicsHypervisor(sys_ptr, m_processors);
  // in interface.C, this method posts a wakeup on Simics' event queue
  SIMICS_wakeup_ruby();
  // in interface.C, this method causes "core_exception_callback"
  SIMICS_install_exception_callback();
  
  //JORGE
	if(g_SAMPLED_CACHE) {
		m_mask =  (1 << L15_CACHE_NUM_SETS_BITS) - 1; 
		uint NUM_SETS = 64;
		cerr << "SAMPLED_CACHE enabled..." << NUM_SETS << " will be sampled" <<endl;
		//m_sampledSets =  new PerfectCacheMemory<uint> (NULL);
		
		for(uint i=0; i< NUM_SETS; i++) {
			uint aux= rand() % ((1 << L2_CACHE_NUM_SETS_BITS) << g_NUM_L2_BANKS_PER_CHIP_BITS);
			
			if(!m_sampledSetsLLC.exist(aux)) m_sampledSetsLLC.add(aux, aux);
			
			
			if(!m_sampledSetsL2.exist(aux & m_mask)) m_sampledSetsL2.add(aux&m_mask, aux&m_mask);
			if(g_DEBUG_SAMPLED_CACHE) cerr << "Set " << aux << " will be sampled in LLC and " << (aux & m_mask) << " in L2" << endl;
		}		
	} 
  cerr << "Fin constructor SimicsDriver." << endl;


execInst.setSize(8);
penal.setSize(8);
instUnhandled.setSize(8);

for(int i=0; i<8; i++)
{
	execInst[i]=0;
	penal[i]=0;
	auxTime[i] = 0;
	auxInst[i] = 0;
	instUnhandled[i] = 0;
}

  clearStats();

}

// Destructor
SimicsDriver::~SimicsDriver() {
  // in interface.C, this method removes the wakeup on Simics's event queue
  SIMICS_remove_ruby_callback();

  // in interface.C, this method removes the core exception callback
  SIMICS_remove_exception_callback();

  // destory all processors
  for(int i=0; i < RubyConfig::numberOfProcessors(); i++){
    delete m_processors[i];
    m_processors[i] = NULL;
  }

}

// print the config parameters
void SimicsDriver::printConfig(ostream& out) const {
  out << "Simics ruby multiplier: " << SIMICS_RUBY_MULTIPLIER << endl;
  out << "Simics stall time: " << SIMICS_STALL_TIME << endl;
  out << endl;
}

void SimicsDriver::printStats(ostream& out) const {
  out << endl;
  out << "Simics Driver Transaction Stats" << endl;
  out << "----------------------------------" << endl;
  out << "Insn requests: " << m_insn_requests << endl;
  out << "Data requests: " << m_data_requests << endl;
  out << "Unhandled: "  << instUnhandled << endl;
  out << "Memory mapped IO register accesses: " << m_mem_mapped_io_counter << endl;
  out << "Device initiated accesses: " << m_device_initiator_counter << endl;
  out << "Other initiated accesses: " << m_other_initiator_counter << endl;

  out << "Atomic load accesses: " << m_atomic_load_counter << endl;
  out << "Exceptions: " << m_exception_counter << endl;
  out << "Non stallable accesses: " << m_non_stallable << endl;
  out << "Prefetches: " << m_prefetch_counter << endl;
  out << "Cache Flush: " << m_cache_flush_counter << endl;
  out << endl;
  for (int i = 0; i < MAX_ADDRESS_SPACE_ID; i++) {
    if (m_asi_counters[i] != 0) {
      out << "Requests of asi 0x" << hex << i << dec << ": " << m_asi_counters[i] << endl;
    }
  }
  out << endl;

  out << "Simics Driver Transaction Results Stats" << endl;
  out << "------------------------------------------" << endl;
  out << "Fast path: " << m_fast_path_counter << endl;
  out << "Request missed: " << m_request_missed_counter << endl;
  out << "Sequencer not ready: " << m_sequencer_not_ready_counter << endl;
  out << "Duplicate instruction fetches: " << m_duplicate_instruction_fetch_counter << endl;
  out << "Hit return: " << m_hit_return_counter << endl;
  out << "Atomic last accesses: " << m_atomic_last_counter << endl;
  

//JORGE
  out << "Simics Driver Estadisticas a�adidas" << endl;

long totLoads=0, totStores=0, totAtomics=0,totFetches=0;

  for(int i=0; i < RubyConfig::numberOfProcessors(); i++){
  	totLoads+=m_processors[i]->getLoads();
     out << "Num Loads: " << m_processors[i]->getLoads() << endl;
  }
    out << "Num Total Loads: " << totLoads << endl;
  
  for(int i=0; i < RubyConfig::numberOfProcessors(); i++){
    totStores+=m_processors[i]->getStores();
     out << "Num Stores: " << m_processors[i]->getStores() << endl;
  }
   out << "Num Total Stores: " << totStores << endl;
  
  for(int i=0; i < RubyConfig::numberOfProcessors(); i++){
     totAtomics+= m_processors[i]->getAt();
     out << "Num Atomicas: " << m_processors[i]->getAt() << endl;
  }
   out << "Num Total Atomicas: " << totAtomics << endl;
  
  for(int i=0; i < RubyConfig::numberOfProcessors(); i++){
  	 totFetches+=m_processors[i]->getFetches();
     out << "Num Fetches: " << m_processors[i]->getFetches() << endl;
  }
   out << "Num Total Fetches: " << totFetches << endl;
  
  out << "Num total data (ld+st+atm): " << totLoads+totStores+totAtomics << endl;
  
  out << " latencia media: " << mean/(double)cont << endl;
 
  if(g_QUICK_MEM) cacheMgr->printStats(out);
 

     out << "Num exec inst: " << execInst << endl;
     out << "penal: " << penal << endl;
  
}

void SimicsDriver::clearStats() {
  // transaction stats
  m_insn_requests = 0;
  m_data_requests = 0;

  m_mem_mapped_io_counter = 0;
  m_device_initiator_counter = 0;
  m_other_initiator_counter = 0;

  m_atomic_load_counter = 0;
  m_exception_counter = 0;
  m_non_stallable = 0;
  m_prefetch_counter = 0;
  m_cache_flush_counter = 0;

  m_asi_counters.setSize( MAX_ADDRESS_SPACE_ID );
  for(int i=0; i < MAX_ADDRESS_SPACE_ID; i++) {
    m_asi_counters[i] = 0;
  }

  // transaction results stats
  m_fast_path_counter = 0;
  m_request_missed_counter = 0;
  m_sequencer_not_ready_counter = 0;
  m_duplicate_instruction_fetch_counter = 0;
  m_hit_return_counter = 0;
  m_atomic_last_counter = 0;
  
  if(g_QUICK_MEM) cacheMgr->clearStats();

for(int i=0; i<8; i++)
{
	execInst[i]=0;
	penal[i]=0;
}

  cerr << "Fin limpieza SimicsDriver->stats." << endl;
}

integer_t SimicsDriver::getInstructionCount(int proc) const {
  return m_processors[proc]->getInstructionCount();
}

integer_t SimicsDriver::getCycleCount(int proc) const {
  return m_processors[proc]->getCycleCount();
}


/******************************************************************
 * void hitCallback(int cpuNumber)
 * Called by Sequencer when the data is ready in the cache
 ******************************************************************/
void SimicsDriver::hitCallback(NodeID proc, SubBlock& data, CacheRequestType type, int thread) {
  m_processors[proc]->hitCallback(type, data);
}

void SimicsDriver::conflictCallback(NodeID proc, SubBlock& data, CacheRequestType type, int thread) {
  m_processors[proc]->conflictCallback(type, data);
}

void SimicsDriver::abortCallback(NodeID proc, SubBlock& data, CacheRequestType type, int thread) {
  m_processors[proc]->abortCallback(data);
}

/******************************************************************
 * makeRequest(memory_transaction_t *mem_trans)
 * Called by function
 * mh_memorytracer_possible_cache_miss(memory_transaction_t *mem_trans)
 * which was called by Simics via ruby.c.
 * May call Sequencer.
 ******************************************************************/
int SimicsDriver::makeRequest(memory_transaction_t *mem_trans) {

 
       int proc = SIMICS_get_proc_no(mem_trans->s.ini_ptr);

  // Special case here
  if ( 	 PERFECT_MEMORY_SYSTEM && !isUnhandledTransaction(mem_trans)) {
  
    // we need to notify simics...
    if(proc == -1 || PERFECT_MEMORY_SYSTEM_LATENCY==0 ) {
            
      
      // this is OK, since returning zero won't stall simics
      return 0;
    } else {
      assert(PERFECT_MEMORY_SYSTEM_LATENCY>0);
      
      //cacheMgr->access(mem_trans);

      // Simics will re-call makeRequest after the specified number
      // of cycles...at which time we should return 0
      if(m_perfect_memory_firstcall_flags[proc]) {
        execInst[SIMICS_get_proc_no(mem_trans->s.ini_ptr)]++;
        m_perfect_memory_firstcall_flags[proc] = false;
        return PERFECT_MEMORY_SYSTEM_LATENCY;
      } else {
        m_perfect_memory_firstcall_flags[proc] = true;
       // cout << " 2: " << s_stallCycleMap[Hit].cycles << endl;
        return s_stallCycleMap[Hit].cycles;
      }
    }    
  } 
  else {
  		if(g_QUICK_MEM && m_perfect_memory_firstcall_flags[proc]) {
  			 recordTransactionStats(mem_trans);
  		}
  		
		if ( g_QUICK_MEM && !isUnhandledTransaction(mem_trans)) {
	  
		  // we need to notify simics...
		  if(proc == -1 ) {
		    // this is OK, since returning zero won't stall simics
		    return  s_stallCycleMap[Hit].cycles;
		   } else {
		  
		  // Simics will re-call makeRequest after the specified number
		  // of cycles...at which time we should return 0
		  
		 // m_processors[proc]->makeRequestQuick(mem_trans);
		  if(m_perfect_memory_firstcall_flags[proc]) {
				
			uint latency= cacheMgr->access(mem_trans);
			//cerr << "LATENCIA: " << latency << endl;
			//uint latency = 200;
			//penal[SIMICS_get_proc_no(mem_trans->s.ini_ptr)] += latency;
			//execInst[SIMICS_get_proc_no(mem_trans->s.ini_ptr)]++;
			
			
			m_perfect_memory_firstcall_flags[proc] = latency==0 ? true : false;
			return latency;
		  } else {
		  
		  /*	cerr << proc << "\t2\tTime:"  << getCycleCount(proc) << "\tlatencia devuelta: " << 0 << "  transaccion: " << 
					(mem_trans->s.type==Sim_Trans_Instr_Fetch ? "fetch" : (mem_trans->s.type==Sim_Trans_Load ? "load" : 
					(mem_trans->s.type==Sim_Trans_Store ? "store" : "otra"))) <<endl ;*/
					
			m_perfect_memory_firstcall_flags[proc] = true;
			return  0; //s_stallCycleMap[Hit].cycles;
		  }
		}    
	  }
  }
  
  
salir:
  MemoryTransactionResult ret;

  // skip unsupported types
  if (isUnhandledTransaction(mem_trans)) {
    ret = Unhandled;
  } else {
    // perform makeRequest()
    int proc = SIMICS_get_proc_no(mem_trans->s.ini_ptr);
    ret = m_processors[proc]->makeRequest(mem_trans);
  }


//JORGE
//estas dos lineas estaban al final pero las ponemos aqui para acelerar
  int latency = s_stallCycleMap[ret].cycles;
  return latency;
  
  // record transaction stats if they are not duplicated
  if( ret != Not_Ready &&
      ret != I_Replay &&
      ret != D_Replay &&
      ret != A_Replay ) {
    recordTransactionStats(mem_trans);
  }

  // record result stats
  recordTransactionResultStats(ret);

  //JORGE
  //revisamos el n�mero de instrucciones que ha ejecutado cada proc
  //m_accesos_user cuenta el n�mero de accesos a cada cache de instrucciones en modo usuario
  //m_instrucciones[i] nos dice si el procesador i ha llegado a g_INSTRUCTIONS_TO_SIMULATE ins simuladas
  if(g_INSTRUCTIONS_TO_SIMULATE)
  {
    if(g_THREADS_IN_EX==RubyConfig::numberOfProcessors() && !g_SOLO_UNO)
    {
      for(int i=0; i<RubyConfig::numberOfProcessors(); i++)
        if( g_system_ptr->getProfiler()->getInstructionCacheProfiler()->m_accesos_user[i] >= g_INSTRUCTIONS_TO_SIMULATE && !m_instrucciones[i])
        {
          cerr << "PROCESADOR " << i << endl;
          g_system_ptr->getProfiler()->printStats(cerr);
          m_instrucciones[i]=1;
          m_nprocsYa++;
          if(m_nprocsYa==RubyConfig::numberOfProcessors())
            SIM_break_simulation("todos los PROCS han acabado\n");
        }
      
    } else
    {
       if( g_system_ptr->getProfiler()->getInstructionCacheProfiler()->m_accesos_user[g_PROC_AISLADO] >= g_INSTRUCTIONS_TO_SIMULATE)
        {
          cerr << "El procesador aislado (" << g_PROC_AISLADO << ") ha acabado" << endl;
          g_system_ptr->getProfiler()->printStats(cerr);
            SIM_break_simulation("todos los PROCS han acabado\n");
        }
    }
  }

  // stall time

}

// Called whenever we want are about to call the SW handler
void SimicsDriver::notifyTrapStart( int cpuNumber, const Address & handlerPC, int threadID, int smtThread ){
  assert( cpuNumber <  RubyConfig::numberOfProcessors() );
  m_processors[cpuNumber]->notifyTrapStart(handlerPC);
}

// Called whenever we want the SW handler to inform us when it is finished
void SimicsDriver::notifyTrapComplete( int cpuNumber, const Address & newPC, int smtThread ){
  assert( cpuNumber <  RubyConfig::numberOfProcessors() );
  m_processors[cpuNumber]->notifyTrapComplete(newPC);
}

/******************************************************************
 * observeMemoryAccess(memory_transaction_t *mem_trans)
 * This function is called when memory instructions complete, and
 * it allows the cache hierarchy to observe the load/store value that
 * was read/written by the memory request. It is only called when in
 * Simics and DATA_BLOCK is defined, by the function
 * mh_memorytracer_observe_memory(memory_transaction_t *mem_trans)
 * which was called by Simics via ruby.c.
 ******************************************************************/
void SimicsDriver::observeMemoryAccess(memory_transaction_t *mem_trans) {

  // NOTE: we should NOT do any filtering in this function!
  //
  // makeRequest() can be viewed as an information stream of timing of the
  // memory system.
  // observeMemoryAccess() can be viewed as an information stream of value of
  // the memory system.
  //
  // So makeRequest will change the cache's meta-state, observeMemoryAccess
  // will change the cache's state. What we do in this function is that
  //     1. match cache value (if any) for loads
  //     2. update cache content (if any) for stores

  // NEED TO FILTER THESE OUT FOR LAZY XACT SYSTEMS
  if (isUnhandledTransaction(mem_trans)) 
    return;
            
  // perform observeMemoryAccess()
  int proc = SIMICS_get_proc_no(mem_trans->s.ini_ptr);
  m_processors[proc]->observeMemoryAccess(mem_trans);
}

void SimicsDriver::exceptionCallback(conf_object_t *cpuPtr, integer_t exc) {

  m_exception_counter++;

  int proc = SIMICS_get_proc_no(cpuPtr);
  m_processors[proc]->exceptionCallback(exc);
}

void SimicsDriver::recordTransactionStats(memory_transaction_t* mem_trans) {

  if (mem_trans->s.type == Sim_Trans_Prefetch) {
    m_prefetch_counter++;
  }

  if (mem_trans->s.type == Sim_Trans_Cache) {
    m_cache_flush_counter++;
  }

  if(mem_trans->s.type == Sim_Trans_Instr_Fetch) {
    m_insn_requests++;
  } else {
    m_data_requests++;
  }

  generic_transaction_t *g = (generic_transaction_t *)mem_trans;

  // Check for DMA/IO
  /*if (IS_DEV_MEM_OP(g->ini_type)) {
    m_device_initiator_counter++;
  } else if (IS_OTH_MEM_OP(g->ini_type)) {
    m_other_initiator_counter++;
  } else if (mem_trans->s.physical_address > uinteger_t(RubyConfig::memorySizeBytes())) {
    m_mem_mapped_io_counter++;
  }*/

#ifdef SPARC
  // record asi of transaction
  m_asi_counters[mem_trans->address_space]++;

  // atomic loads (ldda), generate LD requests instead of ATOMIC requests
  if ( mem_trans->s.atomic == true && SIMICS_is_ldda(mem_trans)) {
    m_atomic_load_counter++;
  }
#endif

  // count non-stallable requests
  if(!(mem_trans->s.may_stall)) {
    m_non_stallable++;
  }

}

#ifdef SPARC
exception_type_t SimicsDriver::asiCallback(conf_object_t * cpu, generic_transaction_t *g) {

  // only real processor should init ASI accesses
  int proc = SIMICS_get_proc_no(cpu);
  assert(proc != -1);

  return m_processors[proc]->asiCallback((memory_transaction_t*)g);

}
#endif

bool SimicsDriver::isUnhandledTransaction(memory_transaction_t* mem_trans) {
//cout << " b: " << SIMICS_get_proc_no(mem_trans->s.ini_ptr) << " add: " << mem_trans->s.physical_address;
  // only handle user data?
  
  
	int proc = SIMICS_get_proc_no(mem_trans->s.ini_ptr);
  
	if(g_SOLO_UNO && proc!=g_PROC_AISLADO)  return true;
	  
  if (USER_MODE_DATA_ONLY) {
    if(PRIV_MODE) {
    	instUnhandled[proc]++;
      return true;
    }
    if(mem_trans->s.type == Sim_Trans_Instr_Fetch) {
      instUnhandled[proc]++;
      return true;
    }
  }
  
  if (USER_MODE_ONLY) {
    if(PRIV_MODE) {
      instUnhandled[proc]++;
      return true;
    }
  }

  // no prefetches
  if (mem_trans->s.type == Sim_Trans_Prefetch) {
    instUnhandled[proc]++;
    return true;
  }

  // no cache flush
  if (mem_trans->s.type == Sim_Trans_Cache) {
    instUnhandled[proc]++;
    return true;
  }

  // no DMA & IO
  if (IS_DEV_MEM_OP(mem_trans->s.ini_type) ||
      IS_OTH_MEM_OP(mem_trans->s.ini_type) ||
      mem_trans->s.physical_address > uinteger_t(RubyConfig::memorySizeBytes())
     ) {
      if(mem_trans->s.physical_address > uinteger_t(RubyConfig::memorySizeBytes()) && SIMICS_get_proc_no(mem_trans->s.ini_ptr) < 7) cout << "ALLLLLA" << endl;
      instUnhandled[proc]++;
    return true;
  }

  return false;
}

void SimicsDriver::recordTransactionResultStats(
  MemoryTransactionResult result) {

  switch(result) {
    case Hit:
      m_fast_path_counter++;
      break;
    case Miss:
      m_request_missed_counter++;
      break;
    case Non_Stallable:
      {/* nothing yet */};
      break;
    case Unhandled:
      {/* nothing yet */};
      break;
    case Not_Ready:
      m_sequencer_not_ready_counter++;
      break;
    case I_Replay:
      m_duplicate_instruction_fetch_counter++;
      break;
    case D_Replay:
      m_hit_return_counter++;
      break;
    case A_Replay:
      m_atomic_last_counter++;
      break;
    case Conflict_Retry:
      break;  
    default:
      ERROR_MSG("Error: Strange memory transaction result");
  }
}

MemoryTransactionResult string_to_MemoryTransactionResult(const string& str) {
  if (str == "Hit") {
    return Hit;
  } else if (str == "Miss") {
    return Miss;
  } else if (str == "Non_Stallable") {
    return Non_Stallable;
  } else if (str == "Unhandled") {
    return Unhandled;
  } else if (str == "Not_Ready") {
    return Not_Ready;
  } else if (str == "I_Replay") {
    return I_Replay;
  } else if (str == "D_Replay") {
    return D_Replay;
  } else if (str == "A_Replay") {
    return A_Replay;
  } else if (str == "Conflict_Retry") {
    return Conflict_Retry;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type MemoryTransactionResult");
  }
}

integer_t SimicsDriver::readPhysicalMemory(int procID, 
                                           physical_address_t address,
                                           int len ){
  return SIMICS_read_physical_memory(procID, address, len);
}

void SimicsDriver::writePhysicalMemory( int procID, 
                                        physical_address_t address,
                                        integer_t value, 
                                        int len ){
  SIMICS_write_physical_memory(procID, address, value, len);
}

ostream& operator<<(ostream& out, const MemoryTransactionResult& obj) {
  switch(obj) {
    case Hit:
      out << "Hit";
      break;
    case Miss:
      out << "Miss";
      break;
    case Non_Stallable:
      out << "Non_Stallable";
      break;
    case Unhandled:
      out << "Unhandled";
      break;
    case Not_Ready:
      out << "Not_Ready";
      break;
    case I_Replay:
      out << "I_Replay";
      break;
    case D_Replay:
      out << "D_Replay";
      break;
    case A_Replay:
      out << "A_Replay";
      break;
    case Conflict_Retry:
      out << "Conflict_Retry";
      break;
    default:
      ERROR_MSG("Invalid range for type MemoryTransactionResult");
      break;
  }
  out << flush;
  return out;
}

SimicsHypervisor*
SimicsDriver::getHypervisor() 
{
  return m_hypervisor;
}

