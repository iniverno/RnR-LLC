// Auto generated C++ code started by symbols/SymbolTable.C:376

#include "Chip.h"
#include "Network.h"
#include "CacheRecorder.h"

// Includes for controllers
#include "L1Cache_Controller.h"
#include "L2Cache_Controller.h"
#include "Directory_Controller.h"

Chip::Chip(NodeID id, Network* net_ptr):AbstractChip(id, net_ptr)
{
  m_chip_ptr = this;
  // L1Cache_requestFromL1Cache
  m_L1Cache_requestFromL1Cache_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_requestFromL1Cache_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfL1CachePerChip()+MachineType_base_number(string_to_MachineType("L1Cache")), true, 0);
    assert(m_L1Cache_requestFromL1Cache_vec[i] != NULL);
    m_L1Cache_requestFromL1Cache_vec[i]->setOrdering(true);
    if (FINITE_BUFFERING) {
      m_L1Cache_requestFromL1Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // L1Cache_responseFromL1Cache
  m_L1Cache_responseFromL1Cache_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_responseFromL1Cache_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfL1CachePerChip()+MachineType_base_number(string_to_MachineType("L1Cache")), false, 3);
    assert(m_L1Cache_responseFromL1Cache_vec[i] != NULL);
    m_L1Cache_responseFromL1Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L1Cache_responseFromL1Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // L1Cache_requestToL1Cache
  m_L1Cache_requestToL1Cache_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_requestToL1Cache_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfL1CachePerChip()+MachineType_base_number(string_to_MachineType("L1Cache")), true, 2);
    assert(m_L1Cache_requestToL1Cache_vec[i] != NULL);
    m_L1Cache_requestToL1Cache_vec[i]->setOrdering(true);
    if (FINITE_BUFFERING) {
      m_L1Cache_requestToL1Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // L1Cache_responseToL1Cache
  m_L1Cache_responseToL1Cache_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_responseToL1Cache_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfL1CachePerChip()+MachineType_base_number(string_to_MachineType("L1Cache")), false, 3);
    assert(m_L1Cache_responseToL1Cache_vec[i] != NULL);
    m_L1Cache_responseToL1Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L1Cache_responseToL1Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // L1Cache_L1_TBEs
  m_L1Cache_L1_TBEs_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1_TBEs_vec[i] = new TBETable<L1Cache_TBE>(this);

    assert(m_L1Cache_L1_TBEs_vec[i] != NULL);
  }

  // L1Cache_L1IcacheMemory
  m_L1Cache_L1IcacheMemory_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1IcacheMemory_vec[i] = new CacheMemory<L1Cache_Entry>(this, L1_CACHE_NUM_SETS_BITS,L1_CACHE_ASSOC,MachineType_L1Cache,int_to_string(i)+"_L1I");

    assert(m_L1Cache_L1IcacheMemory_vec[i] != NULL);
  }

  // L1Cache_L1DcacheMemory
  m_L1Cache_L1DcacheMemory_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1DcacheMemory_vec[i] = new CacheMemory<L1Cache_Entry>(this, L1_CACHE_NUM_SETS_BITS,L1_CACHE_ASSOC,MachineType_L1Cache,int_to_string(i)+"_L1D");

    assert(m_L1Cache_L1DcacheMemory_vec[i] != NULL);
  }

  // L1Cache_L15cacheMemory
  m_L1Cache_L15cacheMemory_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L15cacheMemory_vec[i] = new CacheMemory<L1Cache_Entry>(this, L15_CACHE_NUM_SETS_BITS,L15_CACHE_ASSOC,MachineType_L1Cache,int_to_string(i)+"_L15");

    assert(m_L1Cache_L15cacheMemory_vec[i] != NULL);
  }

  // L1Cache_mandatoryQueue
  m_L1Cache_mandatoryQueue_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_mandatoryQueue_vec[i] = new MessageBuffer(this);

    assert(m_L1Cache_mandatoryQueue_vec[i] != NULL);
    m_L1Cache_mandatoryQueue_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L1Cache_mandatoryQueue_vec[i]->setSize(PROCESSOR_BUFFER_SIZE);
    }
  }

  // L1Cache_optionalQueue
  m_L1Cache_optionalQueue_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_optionalQueue_vec[i] = new MessageBuffer(this);

    assert(m_L1Cache_optionalQueue_vec[i] != NULL);
    m_L1Cache_optionalQueue_vec[i]->setOrdering(true);
    m_L1Cache_optionalQueue_vec[i]->setPriority(101);
    if (FINITE_BUFFERING) {
      m_L1Cache_optionalQueue_vec[i]->setSize(PROCESSOR_BUFFER_SIZE);
    }
  }

  // L1Cache_sequencer
  m_L1Cache_sequencer_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_sequencer_vec[i] = new Sequencer(this, i);

    assert(m_L1Cache_sequencer_vec[i] != NULL);
  }

  // L2Cache_L1RequestFromL2Cache
  m_L2Cache_L1RequestFromL2Cache_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L1RequestFromL2Cache_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfL2CachePerChip()+MachineType_base_number(string_to_MachineType("L2Cache")), true, 2);
    assert(m_L2Cache_L1RequestFromL2Cache_vec[i] != NULL);
    m_L2Cache_L1RequestFromL2Cache_vec[i]->setOrdering(true);
    if (FINITE_BUFFERING) {
      m_L2Cache_L1RequestFromL2Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // L2Cache_responseFromL2Cache
  m_L2Cache_responseFromL2Cache_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_responseFromL2Cache_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfL2CachePerChip()+MachineType_base_number(string_to_MachineType("L2Cache")), false, 3);
    assert(m_L2Cache_responseFromL2Cache_vec[i] != NULL);
    m_L2Cache_responseFromL2Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L2Cache_responseFromL2Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // L2Cache_finalAckFromL2Cache
  m_L2Cache_finalAckFromL2Cache_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_finalAckFromL2Cache_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfL2CachePerChip()+MachineType_base_number(string_to_MachineType("L2Cache")), false, 4);
    assert(m_L2Cache_finalAckFromL2Cache_vec[i] != NULL);
    m_L2Cache_finalAckFromL2Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L2Cache_finalAckFromL2Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // L2Cache_L1RequestToL2Cache
  m_L2Cache_L1RequestToL2Cache_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L1RequestToL2Cache_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfL2CachePerChip()+MachineType_base_number(string_to_MachineType("L2Cache")), true, 0);
    assert(m_L2Cache_L1RequestToL2Cache_vec[i] != NULL);
    m_L2Cache_L1RequestToL2Cache_vec[i]->setOrdering(true);
    if (FINITE_BUFFERING) {
      m_L2Cache_L1RequestToL2Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // L2Cache_forwardedRequestToL2Cache
  m_L2Cache_forwardedRequestToL2Cache_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_forwardedRequestToL2Cache_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfL2CachePerChip()+MachineType_base_number(string_to_MachineType("L2Cache")), true, 2);
    assert(m_L2Cache_forwardedRequestToL2Cache_vec[i] != NULL);
    m_L2Cache_forwardedRequestToL2Cache_vec[i]->setOrdering(true);
    if (FINITE_BUFFERING) {
      m_L2Cache_forwardedRequestToL2Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // L2Cache_responseToL2Cache
  m_L2Cache_responseToL2Cache_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_responseToL2Cache_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfL2CachePerChip()+MachineType_base_number(string_to_MachineType("L2Cache")), false, 3);
    assert(m_L2Cache_responseToL2Cache_vec[i] != NULL);
    m_L2Cache_responseToL2Cache_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L2Cache_responseToL2Cache_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // L2Cache_L2_TBEs
  m_L2Cache_L2_TBEs_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L2_TBEs_vec[i] = new TBETable<L2Cache_TBE>(this);

    assert(m_L2Cache_L2_TBEs_vec[i] != NULL);
  }

  // L2Cache_Pref_TBEs
  m_L2Cache_Pref_TBEs_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_Pref_TBEs_vec[i] = new TBETable<L2Cache_TBE>(this);

    assert(m_L2Cache_Pref_TBEs_vec[i] != NULL);
  }

  // L2Cache_L2cacheMemory
  m_L2Cache_L2cacheMemory_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L2cacheMemory_vec[i] = new CacheMemory<L2Cache_Entry>(this, L2_CACHE_NUM_SETS_BITS,L2_CACHE_ASSOC,MachineType_L2Cache,int_to_string(i),i);

    assert(m_L2Cache_L2cacheMemory_vec[i] != NULL);
  }

  // L2Cache_prefetcher
  m_L2Cache_prefetcher_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_prefetcher_vec[i] = new Prefetcher(this, i);

    assert(m_L2Cache_prefetcher_vec[i] != NULL);
  }

  // L2Cache_dataArrayReplQueue
  m_L2Cache_dataArrayReplQueue_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_dataArrayReplQueue_vec[i] = new MessageBuffer(this);

    assert(m_L2Cache_dataArrayReplQueue_vec[i] != NULL);
    m_L2Cache_dataArrayReplQueue_vec[i]->setOrdering(true);
    if (FINITE_BUFFERING) {
      m_L2Cache_dataArrayReplQueue_vec[i]->setSize(PROCESSOR_BUFFER_SIZE);
    }
  }

  // L2Cache_prefetchQueue
  m_L2Cache_prefetchQueue_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_prefetchQueue_vec[i] = new MessageBuffer(this);

    assert(m_L2Cache_prefetchQueue_vec[i] != NULL);
    m_L2Cache_prefetchQueue_vec[i]->setOrdering(true);
    if (FINITE_BUFFERING) {
      m_L2Cache_prefetchQueue_vec[i]->setSize(PROCESSOR_BUFFER_SIZE);
    }
  }

  // L2Cache_prefResponseToL2CacheQueue
  m_L2Cache_prefResponseToL2CacheQueue_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_prefResponseToL2CacheQueue_vec[i] = new MessageBuffer(this);

    assert(m_L2Cache_prefResponseToL2CacheQueue_vec[i] != NULL);
    m_L2Cache_prefResponseToL2CacheQueue_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L2Cache_prefResponseToL2CacheQueue_vec[i]->setSize(PROCESSOR_BUFFER_SIZE);
    }
  }

  // L2Cache_responseToL2CacheQueue
  m_L2Cache_responseToL2CacheQueue_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_responseToL2CacheQueue_vec[i] = new MessageBuffer(this);

    assert(m_L2Cache_responseToL2CacheQueue_vec[i] != NULL);
    m_L2Cache_responseToL2CacheQueue_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_L2Cache_responseToL2CacheQueue_vec[i]->setSize(PROCESSOR_BUFFER_SIZE);
    }
  }

  // L2Cache_dram
  m_L2Cache_dram_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_dram_vec[i] = new Dram(this, i);

    assert(m_L2Cache_dram_vec[i] != NULL);
  }

  // Directory_forwardedRequestFromDir
  m_Directory_forwardedRequestFromDir_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_forwardedRequestFromDir_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfDirectoryPerChip()+MachineType_base_number(string_to_MachineType("Directory")), true, 2);
    assert(m_Directory_forwardedRequestFromDir_vec[i] != NULL);
    m_Directory_forwardedRequestFromDir_vec[i]->setOrdering(true);
    if (FINITE_BUFFERING) {
      m_Directory_forwardedRequestFromDir_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // Directory_responseFromDir
  m_Directory_responseFromDir_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_responseFromDir_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfDirectoryPerChip()+MachineType_base_number(string_to_MachineType("Directory")), false, 3);
    assert(m_Directory_responseFromDir_vec[i] != NULL);
    m_Directory_responseFromDir_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_Directory_responseFromDir_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // Directory_requestToDir
  m_Directory_requestToDir_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_requestToDir_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfDirectoryPerChip()+MachineType_base_number(string_to_MachineType("Directory")), false, 1);
    assert(m_Directory_requestToDir_vec[i] != NULL);
    m_Directory_requestToDir_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_Directory_requestToDir_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // Directory_finalAckToDir
  m_Directory_finalAckToDir_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_finalAckToDir_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfDirectoryPerChip()+MachineType_base_number(string_to_MachineType("Directory")), false, 4);
    assert(m_Directory_finalAckToDir_vec[i] != NULL);
    m_Directory_finalAckToDir_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_Directory_finalAckToDir_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // Directory_prefRequestToDir
  m_Directory_prefRequestToDir_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_prefRequestToDir_vec[i] = m_net_ptr->getFromNetQueue(i+m_id*RubyConfig::numberOfDirectoryPerChip()+MachineType_base_number(string_to_MachineType("Directory")), false, 5);
    assert(m_Directory_prefRequestToDir_vec[i] != NULL);
    m_Directory_prefRequestToDir_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_Directory_prefRequestToDir_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // Directory_prefResponseFromDir
  m_Directory_prefResponseFromDir_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_prefResponseFromDir_vec[i] = m_net_ptr->getToNetQueue(i+m_id*RubyConfig::numberOfDirectoryPerChip()+MachineType_base_number(string_to_MachineType("Directory")), false, 5);
    assert(m_Directory_prefResponseFromDir_vec[i] != NULL);
    m_Directory_prefResponseFromDir_vec[i]->setOrdering(false);
    if (FINITE_BUFFERING) {
      m_Directory_prefResponseFromDir_vec[i]->setSize(PROTOCOL_BUFFER_SIZE);
    }
  }
  // Directory_directory
  m_Directory_directory_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_directory_vec[i] = new DirectoryMemory(this, i);

    assert(m_Directory_directory_vec[i] != NULL);
  }

  // Directory_dramToDirQueue
  m_Directory_dramToDirQueue_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_dramToDirQueue_vec[i] = new MessageBuffer(this);

    assert(m_Directory_dramToDirQueue_vec[i] != NULL);
    m_Directory_dramToDirQueue_vec[i]->setOrdering(true);
    if (FINITE_BUFFERING) {
      m_Directory_dramToDirQueue_vec[i]->setSize(PROCESSOR_BUFFER_SIZE);
    }
  }

  // Directory_dramToDirPrefQueue
  m_Directory_dramToDirPrefQueue_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_dramToDirPrefQueue_vec[i] = new MessageBuffer(this);

    assert(m_Directory_dramToDirPrefQueue_vec[i] != NULL);
    m_Directory_dramToDirPrefQueue_vec[i]->setOrdering(true);
    if (FINITE_BUFFERING) {
      m_Directory_dramToDirPrefQueue_vec[i]->setSize(PROCESSOR_BUFFER_SIZE);
    }
  }

  m_L1Cache_Controller_vec.setSize(RubyConfig::numberOfL1CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_Controller_vec[i] = new L1Cache_Controller(this, i);
    assert(m_L1Cache_Controller_vec[i] != NULL);
  }

  m_L2Cache_Controller_vec.setSize(RubyConfig::numberOfL2CachePerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_Controller_vec[i] = new L2Cache_Controller(this, i);
    assert(m_L2Cache_Controller_vec[i] != NULL);
  }

  m_Directory_Controller_vec.setSize(RubyConfig::numberOfDirectoryPerChip(m_id));
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    m_Directory_Controller_vec[i] = new Directory_Controller(this, i);
    assert(m_Directory_Controller_vec[i] != NULL);
  }

}

Chip::~Chip()
{
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_L1_TBEs_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_L1IcacheMemory_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_L1DcacheMemory_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_L15cacheMemory_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_mandatoryQueue_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_optionalQueue_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_sequencer_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    delete m_L2Cache_L2_TBEs_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    delete m_L2Cache_Pref_TBEs_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    delete m_L2Cache_L2cacheMemory_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    delete m_L2Cache_prefetcher_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    delete m_L2Cache_dataArrayReplQueue_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    delete m_L2Cache_prefetchQueue_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    delete m_L2Cache_prefResponseToL2CacheQueue_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    delete m_L2Cache_responseToL2CacheQueue_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    delete m_L2Cache_dram_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    delete m_Directory_directory_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    delete m_Directory_dramToDirQueue_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    delete m_Directory_dramToDirPrefQueue_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    delete m_L1Cache_Controller_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    delete m_L2Cache_Controller_vec[i];
  }
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    delete m_Directory_Controller_vec[i];
  }
}

void Chip::clearStats()
{
  L1Cache_Controller::clearStats();
  L2Cache_Controller::clearStats();
  Directory_Controller::clearStats();
}

void Chip::printStats(ostream& out)
{
  out << endl;
  out << "Chip Stats" << endl;
  out << "----------" << endl << endl;
  L1Cache_Controller::dumpStats(out);
  L2Cache_Controller::dumpStats(out);
  Directory_Controller::dumpStats(out);
}

void Chip::printConfig(ostream& out)
{
  out << "Chip Config" << endl;
  out << "-----------" << endl;
  out << "Total_Chips: " << RubyConfig::numberOfChips() << endl;
  out << "\nL1Cache_L1_TBEs numberPerChip: " << RubyConfig::numberOfL1CachePerChip() << endl;
  m_L1Cache_L1_TBEs_vec[0]->printConfig(out);
  out << "\nL1Cache_L1IcacheMemory numberPerChip: " << RubyConfig::numberOfL1CachePerChip() << endl;
  m_L1Cache_L1IcacheMemory_vec[0]->printConfig(out);
  out << "\nL1Cache_L1DcacheMemory numberPerChip: " << RubyConfig::numberOfL1CachePerChip() << endl;
  m_L1Cache_L1DcacheMemory_vec[0]->printConfig(out);
  out << "\nL1Cache_L15cacheMemory numberPerChip: " << RubyConfig::numberOfL1CachePerChip() << endl;
  m_L1Cache_L15cacheMemory_vec[0]->printConfig(out);
  out << "\nL1Cache_mandatoryQueue numberPerChip: " << RubyConfig::numberOfL1CachePerChip() << endl;
  m_L1Cache_mandatoryQueue_vec[0]->printConfig(out);
  out << "\nL1Cache_optionalQueue numberPerChip: " << RubyConfig::numberOfL1CachePerChip() << endl;
  m_L1Cache_optionalQueue_vec[0]->printConfig(out);
  out << "\nL1Cache_sequencer numberPerChip: " << RubyConfig::numberOfL1CachePerChip() << endl;
  m_L1Cache_sequencer_vec[0]->printConfig(out);
  out << "\nL2Cache_L2_TBEs numberPerChip: " << RubyConfig::numberOfL2CachePerChip() << endl;
  m_L2Cache_L2_TBEs_vec[0]->printConfig(out);
  out << "\nL2Cache_Pref_TBEs numberPerChip: " << RubyConfig::numberOfL2CachePerChip() << endl;
  m_L2Cache_Pref_TBEs_vec[0]->printConfig(out);
  out << "\nL2Cache_L2cacheMemory numberPerChip: " << RubyConfig::numberOfL2CachePerChip() << endl;
  m_L2Cache_L2cacheMemory_vec[0]->printConfig(out);
  out << "\nL2Cache_prefetcher numberPerChip: " << RubyConfig::numberOfL2CachePerChip() << endl;
  m_L2Cache_prefetcher_vec[0]->printConfig(out);
  out << "\nL2Cache_dataArrayReplQueue numberPerChip: " << RubyConfig::numberOfL2CachePerChip() << endl;
  m_L2Cache_dataArrayReplQueue_vec[0]->printConfig(out);
  out << "\nL2Cache_prefetchQueue numberPerChip: " << RubyConfig::numberOfL2CachePerChip() << endl;
  m_L2Cache_prefetchQueue_vec[0]->printConfig(out);
  out << "\nL2Cache_prefResponseToL2CacheQueue numberPerChip: " << RubyConfig::numberOfL2CachePerChip() << endl;
  m_L2Cache_prefResponseToL2CacheQueue_vec[0]->printConfig(out);
  out << "\nL2Cache_responseToL2CacheQueue numberPerChip: " << RubyConfig::numberOfL2CachePerChip() << endl;
  m_L2Cache_responseToL2CacheQueue_vec[0]->printConfig(out);
  out << "\nL2Cache_dram numberPerChip: " << RubyConfig::numberOfL2CachePerChip() << endl;
  m_L2Cache_dram_vec[0]->printConfig(out);
  out << "\nDirectory_directory numberPerChip: " << RubyConfig::numberOfDirectoryPerChip() << endl;
  m_Directory_directory_vec[0]->printConfig(out);
  out << "\nDirectory_dramToDirQueue numberPerChip: " << RubyConfig::numberOfDirectoryPerChip() << endl;
  m_Directory_dramToDirQueue_vec[0]->printConfig(out);
  out << "\nDirectory_dramToDirPrefQueue numberPerChip: " << RubyConfig::numberOfDirectoryPerChip() << endl;
  m_Directory_dramToDirPrefQueue_vec[0]->printConfig(out);
  out << endl;
}

void Chip::print(ostream& out) const
{
  out << "Ruby Chip" << endl;
}
#ifdef CHECK_COHERENCE

bool Chip::isBlockShared(const Address& addr) const
{
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    if (m_L1Cache_Controller_vec[i]->L1Cache_isBlockShared(addr)) {
      return true; 
    }
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    if (m_L2Cache_Controller_vec[i]->L2Cache_isBlockShared(addr)) {
      return true; 
    }
  }
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    if (m_Directory_Controller_vec[i]->Directory_isBlockShared(addr)) {
      return true; 
    }
  }
  return false;
}


bool Chip::isBlockExclusive(const Address& addr) const
{
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    if (m_L1Cache_Controller_vec[i]->L1Cache_isBlockExclusive(addr)) {
      return true; 
    }
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    if (m_L2Cache_Controller_vec[i]->L2Cache_isBlockExclusive(addr)) {
      return true; 
    }
  }
  for (int i = 0; i < RubyConfig::numberOfDirectoryPerChip(m_id); i++)  {
    if (m_Directory_Controller_vec[i]->Directory_isBlockExclusive(addr)) {
      return true; 
    }
  }
  return false;
}

#endif /* CHECK_COHERENCE */ 

void Chip::dumpCaches(ostream& out) const
{
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1IcacheMemory_vec[i]->print(out);
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1DcacheMemory_vec[i]->print(out);
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L15cacheMemory_vec[i]->print(out);
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L2cacheMemory_vec[i]->print(out);
  }
}

void Chip::dumpCacheData(ostream& out) const
{
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1IcacheMemory_vec[i]->printData(out);
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1DcacheMemory_vec[i]->printData(out);
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L15cacheMemory_vec[i]->printData(out);
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L2cacheMemory_vec[i]->printData(out);
  }
}

void Chip::recordCacheContents(CacheRecorder& tr) const
{
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1IcacheMemory_vec[i]->recordCacheContents(tr);
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L1DcacheMemory_vec[i]->recordCacheContents(tr);
  }
  for (int i = 0; i < RubyConfig::numberOfL1CachePerChip(m_id); i++)  {
    m_L1Cache_L15cacheMemory_vec[i]->recordCacheContents(tr);
  }
  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
    m_L2Cache_L2cacheMemory_vec[i]->recordCacheContents(tr);
  }
}
void Chip::printTemp() const
{
cerr << "chip->printTemp" << endl;
/*  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
m_L2Cache_L2cacheMemory_vec[i]->printTempCommand(); 
}*/
m_L2Cache_L2cacheMemory_vec[0]->printTempCommand();
}

void Chip::resetTemp() const
{
cerr << "chip->resetTemp" << endl;
/*  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
m_L2Cache_L2cacheMemory_vec[i]->printTempCommand(); 
}*/
m_L2Cache_L2cacheMemory_vec[0]->resetTemp();
}

void Chip::printReuse() const
{
cerr << "chip->printReuse" << endl;
/*  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
m_L2Cache_L2cacheMemory_vec[i]->printReuseCommand(); 
}*/
m_L2Cache_L2cacheMemory_vec[0]->printReuseCommand();
}

void Chip::resetReuse() const
{
cerr << "chip->resetReuse" << endl;
/*  for (int i = 0; i < RubyConfig::numberOfL2CachePerChip(m_id); i++)  {
m_L2Cache_L2cacheMemory_vec[i]->resetReuse(); 
}*/
m_L2Cache_L2cacheMemory_vec[0]->resetReuse();
}

