
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
   This file has been modified by Kevin Moore and Dan Nussbaum of the
   Scalable Systems Research Group at Sun Microsystems Laboratories
   (http://research.sun.com/scalable/) to support the Adaptive
   Transactional Memory Test Platform (ATMTP).

   Please send email to atmtp-interest@sun.com with feedback, questions, or
   to request future announcements about ATMTP.

   ----------------------------------------------------------------------

   File modification date: 2008-02-23

   ----------------------------------------------------------------------
*/

/*
 * $Id$
 *
 */

#include "protocol_name.h"
#include "Global.h"
#include "System.h"
#include "SimicsDriver.h"
#include "SimicsHypervisor.h"
#include "CacheRecorder.h"
#include "Tracer.h"
#include "RubyConfig.h"
#include "interface.h"
#include "Network.h"
#include "TransactionInterfaceManager.h"
#include "TransactionVersionManager.h"
#include "TransactionIsolationManager.h"
#include "XactCommitArbiter.h"
#include "Chip.h"
#include "XactVisualizer.h"

extern "C" {
#include "commands.h"
}

#ifdef CONTIGUOUS_ADDRESSES
#include "ContiguousAddressTranslator.h"

/* Declared in interface.C */
extern ContiguousAddressTranslator * g_p_ca_translator;

memory_transaction_t local_memory_transaction_t_shadow;

#endif // #ifdef CONTIGUOUS_ADDRESSES

//////////////////////// extern "C" api ////////////////////////////////

extern "C"
void ruby_dump_cache(int cpuNumber)
{
  g_system_ptr->getChip(cpuNumber/RubyConfig::numberOfProcsPerChip())->dumpCaches(cout);
}

extern "C"
void ruby_dump_cache_data(int cpuNumber, char* tag)
{
  if (tag == NULL) {
    // No filename, dump to screen
    g_system_ptr->printConfig(cout);
    g_system_ptr->getChip(cpuNumber/RubyConfig::numberOfProcsPerChip())->dumpCacheData(cout);
  } else {
    // File name, dump to file
    string filename(tag);
    
    cout << "Dumping stats to output file '" << filename << "'..." << endl;
    ofstream m_outputFile;
    m_outputFile.open(filename.c_str());
    if(m_outputFile == NULL){
      cout << endl << "Error: error opening output file '" << filename << "'" << endl;
      return;
    }
    g_system_ptr->getChip(cpuNumber/RubyConfig::numberOfProcsPerChip())->dumpCacheData(m_outputFile);
  }
}

extern "C"
void ruby_set_periodic_stats_file(char* filename)
{
  g_system_ptr->getProfiler()->setPeriodicStatsFile(filename);
}

extern "C"
void ruby_set_periodic_stats_interval(int interval)
{
  g_system_ptr->getProfiler()->setPeriodicStatsInterval(interval);
}

extern "C" 
int mh_memorytracer_possible_cache_miss(memory_transaction_t *mem_trans)
{

  memory_transaction_t *p_mem_trans_shadow = mem_trans;

#ifdef CONTIGUOUS_ADDRESSES
  if(g_p_ca_translator!=NULL) {
    memcpy( &local_memory_transaction_t_shadow, mem_trans, sizeof(memory_transaction_t) );
    p_mem_trans_shadow = &local_memory_transaction_t_shadow;
    uint64 contiguous_address = g_p_ca_translator->TranslateSimicsToRuby( p_mem_trans_shadow->s.physical_address );
    p_mem_trans_shadow->s.physical_address = contiguous_address;
  }
#endif // #ifdef CONTIGUOUS_ADDRESSES


  // Pass this request off to SimicsDriver::makeRequest()
  SimicsDriver* simics_interface_ptr = static_cast<SimicsDriver*>(g_system_ptr->getDriver());
  return simics_interface_ptr->makeRequest(p_mem_trans_shadow);
}

extern "C" 
void mh_memorytracer_observe_memory(memory_transaction_t *mem_trans)
{

  memory_transaction_t *p_mem_trans_shadow = mem_trans;


#ifdef CONTIGUOUS_ADDRESSES
  if(g_p_ca_translator!=NULL) {
    memcpy( &local_memory_transaction_t_shadow, mem_trans, sizeof(memory_transaction_t) );
    p_mem_trans_shadow = &local_memory_transaction_t_shadow;
    uint64 contiguous_address = g_p_ca_translator->TranslateSimicsToRuby( p_mem_trans_shadow->s.physical_address );
    p_mem_trans_shadow->s.physical_address = contiguous_address;

 }
#endif // #ifdef CONTIGUOUS_ADDRESSES


  // Pass this request off to SimicsDriver::makeRequest()
  SimicsDriver* simics_interface_ptr = static_cast<SimicsDriver*>(g_system_ptr->getDriver());
  simics_interface_ptr->observeMemoryAccess(p_mem_trans_shadow);
}


void ruby_set_g3_reg(conf_object_t *cpu, lang_void *parameter){
  int proc_num = SIM_get_proc_no(cpu);
  sparc_v9_interface_t * m_v9_interface = (sparc_v9_interface_t *) SIM_get_interface(cpu, SPARC_V9_INTERFACE);

  for(int set=0; set < 4; set++) {
    for(int i=0; i <8; i++) {
      int registerNumber = i;
      uinteger_t value = m_v9_interface->read_global_register((conf_object_t *)cpu, set, registerNumber);
      cout << "ruby_set_g3_reg BEFORE: proc =" << proc_num << " GSET = " << set << " GLOBAL_REG = " << i << " VALUE = " << value << endl;
    }
  }

  uinteger_t value_ptr = (uinteger_t) parameter;
  int g3_regnum = SIM_get_register_number(cpu, "g3");
  SIM_write_register(cpu, g3_regnum, (uinteger_t) value_ptr);

  cout << endl;
  for(int set=0; set < 4; set++) {
    for(int i=0; i <8; i++) {
      int registerNumber = i;
      uinteger_t value = m_v9_interface->read_global_register((conf_object_t *)cpu, set, registerNumber);
      cout << "ruby_set_g3_reg AFTER: proc =" << proc_num << " GSET = " << set << " GLOBAL_REG = " << i << " VALUE = " << value << endl;
    }
  }

}

#define XACT_MGR g_system_ptr->getChip(SIMICS_current_processor_number()/RubyConfig::numberOfProcsPerChip()/RubyConfig::numberofSMTThreads())->getTransactionInterfaceManager( (SIMICS_current_processor_number()/RubyConfig::numberofSMTThreads())%RubyConfig::numberOfProcsPerChip())

extern "C" 
void magic_instruction_callback(void* desc, void* cpu, integer_t val)
{
//fprintf(stderr, "feliz magic: %d\n", val);
}

/* -- Handle command to change the debugging verbosity for Ruby */
extern "C"
void ruby_change_debug_verbosity(char* new_verbosity_str)
{
  g_debug_ptr->setVerbosityString(new_verbosity_str);
}

/* -- Handle command to change the debugging filter for Ruby */
extern "C"
void ruby_change_debug_filter(char* new_filter_str)
{
  g_debug_ptr->setFilterString(new_filter_str);
}

/* -- Handle command to set the debugging output file for Ruby */
extern "C"
void ruby_set_debug_output_file (const char * new_filename)
{
  string filename(new_filename);
  
  filename += "-";
  filename += CURRENT_PROTOCOL;
  // get the date and time to label the debugging file
  const time_t T = time(NULL);
  tm *localTime = localtime(&T);
  char buf[100];
  strftime(buf, 100, ".%b%d.%Y-%H.%M.%S", localTime);

  filename += buf;
  filename += ".debug";
  
  cout << "Dumping debugging output to file '" << filename << "'...";
  g_debug_ptr->setDebugOutputFile (filename.c_str());
}

extern "C"
void ruby_set_debug_start_time(char* start_time_str)
{
  int startTime = atoi(start_time_str);
  g_debug_ptr->setDebugTime(startTime);
}

/* -- Clear stats */
extern "C"
void ruby_clear_stats()
{
  cout << "Clearing stats...";
  fflush(stdout);
  g_system_ptr->clearStats();
  cout << "Done." << endl;
}

/* -- Dump stats */
extern "C"
// File name, dump to file
void ruby_dump_stats(char* filename)
{
  /*g_debug_ptr->closeDebugOutputFile();*/
  if (filename == NULL) {
    // No output file, dump to screen
    cout << "Dumping stats to standard output..." << endl;
    g_system_ptr->printConfig(cout);
    g_system_ptr->printStats(cout);
  } else {
    cout << "Dumping stats to output file '" << filename << "'..." << endl;
    ofstream m_outputFile;
    m_outputFile.open(filename);
    if(m_outputFile == NULL) {
      cout << "Error: error opening output file '" << filename << "'" << endl;
      return;
    }
    g_system_ptr->printConfig(m_outputFile);
    g_system_ptr->printStats(m_outputFile);
  }
  cout << "Dumping stats completed." << endl;
}

/* -- Dump stats */
extern "C"
// File name, dump to file
void ruby_dump_short_stats(char* filename)
{
  g_debug_ptr->closeDebugOutputFile();
  if (filename == NULL) {
    // No output file, dump to screen
    //cout << "Dumping short stats to standard output..." << endl;
    //g_system_ptr->printConfig(cout);
    g_system_ptr->getProfiler()->printStats(cout, true);
  } else {
    cout << "Dumping stats to output file '" << filename << "'..." << endl;
    ofstream m_outputFile;
    m_outputFile.open(filename);
    if(m_outputFile == NULL) {
      cout << "Error: error opening output file '" << filename << "'" << endl;
      return;
    }
    g_system_ptr->getProfiler()->printShortStats(m_outputFile);
    cout << "Dumping stats completed." << endl;
  }
}

extern "C"
void ruby_load_caches(char* name)
{
  if (name == NULL) {
    cout << "Error: ruby_load_caches requires a file name" << endl;
    return;
  } 

  cout << "Reading cache contents from '" << name << "'...";
  int read = Tracer::playbackTrace(name);
  cout << "done. (" << read << " cache lines read)" << endl;
  ruby_clear_stats();
}

extern "C"
void ruby_save_caches(char* name)
{
  if (name == NULL) {
    cout << "Error: ruby_save_caches requires a file name" << endl;
    return;
  } 

  cout << "Writing cache contents to '" << name << "'...";
  CacheRecorder recorder;
  g_system_ptr->recordCacheContents(recorder);
  int written = recorder.dumpRecords(name);
  cout << "done. (" << written << " cache lines written)" << endl;
}

extern "C"
void ruby_set_tracer_output_file (const char * new_filename)
{
  g_system_ptr->getTracer()->startTrace(string(new_filename));
}

/* -- Handle command to set the xact visualizer file for Ruby */
extern "C"
void ruby_xact_visualizer_file (char * new_filename)
{
  cout << "Dumping xact visualizer output to file '" << new_filename << "'...";
  g_system_ptr->getProfiler()->setXactVisualizerFile (new_filename);
}

extern "C"
void ctrl_exception_start(void* desc, void* cpu, integer_t val)
{
  int proc_no = SIM_get_proc_no((conf_object_t*) cpu);
  conf_object_t* cpu_obj = (conf_object_t*) cpu;
  uinteger_t trap_level = SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "tl")); 

  if (!XACT_MEMORY) return;
  TransactionInterfaceManager *xact_mgr = XACT_MGR;
 
  // level {10,14} interrupt
  //
  if (val == 0x4a || val == 0x4e) {
    int rn_tick           = SIM_get_register_number(cpu_obj, "tick");
    uinteger_t tick       = SIM_read_register(cpu_obj, rn_tick);
    int rn_tick_cmpr      = SIM_get_register_number(cpu_obj, "tick_cmpr");
    uinteger_t tick_cmpr  = SIM_read_register(cpu_obj, rn_tick_cmpr);
    int rn_stick          = SIM_get_register_number(cpu_obj, "stick");
    uinteger_t stick      = SIM_read_register(cpu_obj, rn_stick); 
    int rn_stick_cmpr     = SIM_get_register_number(cpu_obj, "stick_cmpr");
    uinteger_t stick_cmpr = SIM_read_register(cpu_obj, rn_stick_cmpr);
    int rn_pc             = SIM_get_register_number(cpu_obj, "pc");
    uinteger_t pc = SIM_read_register(cpu_obj, rn_pc);
    int rn_npc            =  SIM_get_register_number(cpu_obj, "npc");
    uinteger_t npc = SIM_read_register(cpu_obj, rn_npc);
    int rn_pstate         = SIM_get_register_number(cpu_obj, "pstate");
    uinteger_t pstate     = SIM_read_register(cpu_obj, rn_pstate);
    int rn_pil            = SIM_get_register_number(cpu_obj, "pil");
    int pil               = SIM_read_register(cpu_obj, rn_pil);
    g_system_ptr->getProfiler()->profileTimerInterrupt(proc_no,
                                                       tick, tick_cmpr,
                                                       stick, stick_cmpr,
                                                       trap_level,
                                                       pc, npc,
                                                       pstate, pil);
  }

  int smt_thread_num = proc_no % RubyConfig::numberofSMTThreads();
  // The simulated processor number
  int sim_proc_no = proc_no / RubyConfig::numberofSMTThreads();

  uinteger_t pc = SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "pc"));
  uinteger_t npc = SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "npc"));

  g_system_ptr->getProfiler()->profileExceptionStart(xact_mgr->getTransactionLevel(smt_thread_num) > 0, sim_proc_no, smt_thread_num, val, trap_level, pc, npc);

  if((val >= 0x80 && val <= 0x9f) || (val >= 0xc0 && val <= 0xdf)){
      //xact_mgr->setLoggedException(smt_thread_num);
  } 
  // CORNER CASE - You take an exception while stalling for a commit token
  if (XACT_LAZY_VM && !XACT_EAGER_CD){
    if (g_system_ptr->getXactCommitArbiter()->getTokenOwner() == proc_no)
      g_system_ptr->getXactCommitArbiter()->releaseCommitToken(proc_no);
  }           
}

extern "C"
void ctrl_exception_done(void* desc, void* cpu, integer_t val)
{
  int proc_no = SIM_get_proc_no((conf_object_t*) cpu);
  conf_object_t* cpu_obj = (conf_object_t*) cpu;
  uinteger_t trap_level = SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "tl")); 
  uinteger_t pc = SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "pc"));
  uinteger_t npc = SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "npc"));
  uinteger_t tpc = 0;
  uinteger_t tnpc = 0;
  //get the return PC,NPC pair based on the trap level
  ASSERT(1 <= trap_level && trap_level <= 5);
  if(trap_level == 1){
    tpc =  SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "tpc1"));
    tnpc = SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "tnpc1"));
  }
  if(trap_level == 2){
    tpc =  SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "tpc2"));
    tnpc = SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "tnpc2"));
  }
  if(trap_level == 3){
    tpc =  SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "tpc3"));
    tnpc = SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "tnpc3"));
  }
  if(trap_level == 4){
    tpc =  SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "tpc4"));
    tnpc = SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "tnpc4"));
  }
  if(trap_level == 5){
    tpc =  SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "tpc5"));
    tnpc = SIM_read_register(cpu_obj, SIM_get_register_number(cpu_obj, "tnpc5"));
  }
  
  if (!XACT_MEMORY) return;
  TransactionInterfaceManager *xact_mgr = XACT_MGR;

  int smt_thread_num = proc_no % RubyConfig::numberofSMTThreads();
  // The simulated processor number
  int sim_proc_no = proc_no / RubyConfig::numberofSMTThreads();

  if (proc_no != SIMICS_current_processor_number()){
    WARN_EXPR(proc_no);
    WARN_EXPR(SIMICS_current_processor_number());
    WARN_MSG("Callback for a different processor");
  }  

  g_system_ptr->getProfiler()->profileExceptionDone(xact_mgr->getTransactionLevel(smt_thread_num) > 0, sim_proc_no, smt_thread_num, val, trap_level, pc, npc, tpc, tnpc);

  if((val >= 0x80 && val <= 0x9f) || (val >= 0xc0 && val <= 0xdf)){
    //xact_mgr->clearLoggedException(smt_thread_num);
  }

  if ((val == 0x122) && xact_mgr->shouldTrap(smt_thread_num)){
    // use software handler
    if (xact_mgr->shouldUseHardwareAbort(smt_thread_num)){
        xact_mgr->hardwareAbort(smt_thread_num);
    } else {          
      xact_mgr->trapToHandler(smt_thread_num);
    }  
  }
}

extern "C"
void change_mode_callback(void* desc, void* cpu, integer_t old_mode, integer_t new_mode)
{
  if (XACT_ENABLE_VIRTUALIZATION_LOGTM_SE) {
     SimicsDriver* simics_interface_ptr = static_cast<SimicsDriver*>(g_system_ptr->getDriver());
     simics_interface_ptr->getHypervisor()->change_mode_callback(desc, cpu, old_mode, new_mode);
  }
}

extern "C"
void dtlb_map_callback(void* desc, void* chmmu, integer_t tag_reg, integer_t data_reg){
  if (XACT_ENABLE_VIRTUALIZATION_LOGTM_SE) {
     SimicsDriver* simics_interface_ptr = static_cast<SimicsDriver*>(g_system_ptr->getDriver());
     simics_interface_ptr->getHypervisor()->dtlb_map_callback(desc, chmmu, tag_reg, data_reg);
  }
}

extern "C"
void dtlb_demap_callback(void* desc, void* chmmu, integer_t tag_reg, integer_t data_reg){
  if (XACT_ENABLE_VIRTUALIZATION_LOGTM_SE) {
     SimicsDriver* simics_interface_ptr = static_cast<SimicsDriver*>(g_system_ptr->getDriver());
     simics_interface_ptr->getHypervisor()->dtlb_demap_callback(desc, chmmu, tag_reg, data_reg);
  }
}

extern "C"
void dtlb_replace_callback(void* desc, void* chmmu, integer_t tag_reg, integer_t data_reg){
  if (XACT_ENABLE_VIRTUALIZATION_LOGTM_SE) {
     SimicsDriver* simics_interface_ptr = static_cast<SimicsDriver*>(g_system_ptr->getDriver());
     simics_interface_ptr->getHypervisor()->dtlb_replace_callback(desc, chmmu, tag_reg, data_reg);
  }
}

extern "C"
void dtlb_overwrite_callback(void* desc, void* chmmu, integer_t tag_reg, integer_t data_reg){
  if (XACT_ENABLE_VIRTUALIZATION_LOGTM_SE) {
     SimicsDriver* simics_interface_ptr = static_cast<SimicsDriver*>(g_system_ptr->getDriver());
     simics_interface_ptr->getHypervisor()->dtlb_overwrite_callback(desc, chmmu, tag_reg, data_reg);
  }
}

extern "C"
void core_control_register_write_callback(void* desc, void* cpu, integer_t register_number, integer_t value) {
  int proc_no = SIM_get_proc_no((conf_object_t*) cpu);
  conf_object_t* cpu_obj = (conf_object_t*) cpu;
}

integer_t
read_reg(conf_object_t *cpu, const char* reg_name)
{
  int reg_num = SIM_get_register_number(SIM_current_processor(), reg_name);
  if (SIM_clear_exception()) {
    fprintf(stderr, "read_reg: SIM_get_register_number(%s, %s) failed!\n",
            cpu->name, reg_name);
    assert(0);
  }
  integer_t val = SIM_read_register(cpu, reg_num);
  if (SIM_clear_exception()) {
    fprintf(stderr, "read_reg: SIM_read_register(%s, %d) failed!\n",
            cpu->name, reg_num);
    assert(0);
  }
  return val;
}

extern "C"
void dump_registers(conf_object_t *cpu)
{
  const char* reg_names[] = {
    "g0", "g1", "g2", "g3", "g4", "g5", "g6", "g7", 
    "i0", "i1", "i2", "i3", "i4", "i5", "i6", "i7", 
    "l0", "l1", "l2", "l3", "l4", "l5", "l6", "l7", 
    "o0", "o1", "o2", "o3", "o4", "o5", "o6", "o7", 
    "ccr", "pc", "npc"
  };

  printf("Registers for %s\n", cpu->name);
  printf("------------------\n");

  for (int i = 0; i < (sizeof(reg_names) / sizeof(char*)); i++) {
    const char* reg_name = reg_names[i];
    printf(" %3s: 0x%016llx\n", reg_name, read_reg(cpu, reg_name));
    if (i % 8 == 7) {
      printf("\n");
    }
  }

  int myID = SIMICS_get_proc_no(cpu);
  Address myPC = SIMICS_get_program_counter(myID);
  physical_address_t myPhysPC = SIMICS_translate_address(myID, myPC);
  integer_t myInst = SIMICS_read_physical_memory(myID, myPhysPC, 4);
  const char *myInstStr = SIMICS_disassemble_physical(myID, myPhysPC);
  printf("\n *pc: 0x%llx: %s\n", myInst, myInstStr);

  printf("\n\n");
}

extern "C"
void ruby_print_temp()
{
 

  cerr << "Writing cache life-temporal stuff" << "..." << endl;
  g_system_ptr->getChip(0)->printTemp();

  cerr << "done. " << endl;
}

extern "C"
void ruby_reset_temp()
{
 

  cerr << "Reseting cache life-temporal stuff" << "..." << endl;
  g_system_ptr->getChip(0)->resetTemp();

}


extern "C"
void ruby_reset_reuse()
{
 

  cerr << "Reseting cache reuse stuff" << "..." << endl;
  g_system_ptr->getChip(0)->resetReuse();

}

extern "C"
void ruby_print_reuse()
{
 

  cerr << "Writing cache reuse stuff" << "..." << endl;
  g_system_ptr->getChip(0)->printReuse();

}