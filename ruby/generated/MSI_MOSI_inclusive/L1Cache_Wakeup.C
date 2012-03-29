// Auto generated C++ code started by symbols/StateMachine.C:425
// L1Cache: MSI Directory L1 Cache CMP

#include "Global.h"
#include "RubySlicc_includes.h"
#include "L1Cache_Controller.h"
#include "L1Cache_State.h"
#include "L1Cache_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

void L1Cache_Controller::wakeup()
{

int counter = 0;
  while (true) {
    // Some cases will put us into an infinite loop without this limit
    assert(counter <= RubyConfig::L1CacheTransitionsPerCycle());
    if (counter == RubyConfig::L1CacheTransitionsPerCycle()) {
      g_system_ptr->getProfiler()->controllerBusy(m_machineID); // Count how often we're fully utilized
      g_eventQueue_ptr->scheduleEvent(this, 1); // Wakeup in another cycle and try again
      break;
    }
    // L1CacheInPort responseIntraChipL1Network_in
      if ((((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).isReady())) {
        {
          const ResponseMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:308: ", ((*in_msg_ptr)).m_Address);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:309: ", ((*in_msg_ptr)).m_Destination);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:310: ", ((*in_msg_ptr)).m_SenderMachId);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:311: ", m_machineID);
;
          if (((machineIDToMachineType(((*in_msg_ptr)).m_SenderMachId)) == MachineType_L2Cache)) {
            if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA)) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition(L1Cache_Event_L1_Data, L1Cache_getState(addr), addr);
                if (result == TransitionResult_Valid) {
                  counter++;
                  continue; // Check the first port again
                }
                if (result == TransitionResult_ResourceStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
              }
;
            } else {
              if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA_S)) {
                                {
                  Address addr = ((*in_msg_ptr)).m_Address;
                  TransitionResult result = doTransition(L1Cache_Event_L1_Data_S, L1Cache_getState(addr), addr);
                  if (result == TransitionResult_Valid) {
                    counter++;
                    continue; // Check the first port again
                  }
                  if (result == TransitionResult_ResourceStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                }
;
              } else {
                if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA_I)) {
                                    {
                    Address addr = ((*in_msg_ptr)).m_Address;
                    TransitionResult result = doTransition(L1Cache_Event_L1_Data_I, L1Cache_getState(addr), addr);
                    if (result == TransitionResult_Valid) {
                      counter++;
                      continue; // Check the first port again
                    }
                    if (result == TransitionResult_ResourceStall) {
                      g_eventQueue_ptr->scheduleEvent(this, 1);
                      // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                    }
                  }
;
                } else {
                  if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_ACK)) {
                                        {
                      Address addr = ((*in_msg_ptr)).m_Address;
                      TransitionResult result = doTransition(L1Cache_Event_L1_PutAck, L1Cache_getState(addr), addr);
                      if (result == TransitionResult_Valid) {
                        counter++;
                        continue; // Check the first port again
                      }
                      if (result == TransitionResult_ResourceStall) {
                        g_eventQueue_ptr->scheduleEvent(this, 1);
                        // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                      }
                    }
;
                  } else {
                                        cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-L115cache.sm:323, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid L1 response type") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
                  }
                }
              }
            }
          } else {
                        cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-L115cache.sm:326, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("A non-L2 cache sent a response to a L1 cache") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
          }
        }
      }

    // L1CacheInPort requestIntraChipL1Network_in
      if ((((*(m_chip_ptr->m_L1Cache_requestToL1Cache_vec[m_version]))).isReady())) {
        {
          const RequestMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L1Cache_requestToL1Cache_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:336: ", ((*in_msg_ptr)).m_Address);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:337: ", ((*in_msg_ptr)).m_Destination);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:338: ", m_machineID);
;
          if (((machineIDToMachineType(((*in_msg_ptr)).m_RequestorMachId)) == MachineType_L2Cache)) {
            if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_L1_DG)) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition(L1Cache_Event_L1_DownGrade, L1Cache_getState(addr), addr);
                if (result == TransitionResult_Valid) {
                  counter++;
                  continue; // Check the first port again
                }
                if (result == TransitionResult_ResourceStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
              }
;
            } else {
              if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_INV)) {
                                {
                  Address addr = ((*in_msg_ptr)).m_Address;
                  TransitionResult result = doTransition(L1Cache_Event_L1_INV, L1Cache_getState(addr), addr);
                  if (result == TransitionResult_Valid) {
                    counter++;
                    continue; // Check the first port again
                  }
                  if (result == TransitionResult_ResourceStall) {
                    g_eventQueue_ptr->scheduleEvent(this, 1);
                    // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                  }
                }
;
              } else {
                if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_INV_S)) {
                                    {
                    Address addr = ((*in_msg_ptr)).m_Address;
                    TransitionResult result = doTransition(L1Cache_Event_L1_INV_S, L1Cache_getState(addr), addr);
                    if (result == TransitionResult_Valid) {
                      counter++;
                      continue; // Check the first port again
                    }
                    if (result == TransitionResult_ResourceStall) {
                      g_eventQueue_ptr->scheduleEvent(this, 1);
                      // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                    }
                  }
;
                } else {
                  if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_INV_P)) {
                                        {
                      Address addr = ((*in_msg_ptr)).m_Address;
                      TransitionResult result = doTransition(L1Cache_Event_L1_INV_P, L1Cache_getState(addr), addr);
                      if (result == TransitionResult_Valid) {
                        counter++;
                        continue; // Check the first port again
                      }
                      if (result == TransitionResult_ResourceStall) {
                        g_eventQueue_ptr->scheduleEvent(this, 1);
                        // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                      }
                    }
;
                  } else {
                    if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_INV_S_P)) {
                                            {
                        Address addr = ((*in_msg_ptr)).m_Address;
                        TransitionResult result = doTransition(L1Cache_Event_L1_INV_S_P, L1Cache_getState(addr), addr);
                        if (result == TransitionResult_Valid) {
                          counter++;
                          continue; // Check the first port again
                        }
                        if (result == TransitionResult_ResourceStall) {
                          g_eventQueue_ptr->scheduleEvent(this, 1);
                          // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                        }
                      }
;
                    } else {
                                            cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-L115cache.sm:353, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid forwarded request type") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
                    }
                  }
                }
              }
            }
          } else {
                        cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-L115cache.sm:356, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("A non-L2 cache sent a request to a L1 cache") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
          }
        }
      }

    // L1CacheInPort mandatoryQueue_in
      if ((((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).isReady())) {
        {
          const CacheMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:368: ", ((*in_msg_ptr)).m_Address);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:369: ", m_machineID);
;
          if ((((*in_msg_ptr)).m_Type == CacheRequestType_IFETCH)) {
            if ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(((*in_msg_ptr)).m_Address))) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition(L1Cache_Event_L1_WriteBack, L1Cache_getState(addr), addr);
                if (result == TransitionResult_Valid) {
                  counter++;
                  continue; // Check the first port again
                }
                if (result == TransitionResult_ResourceStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
              }
;
            }
            if ((((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).isTagPresent(((*in_msg_ptr)).m_Address))) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition((L1Cache_mandatory_request_type_to_event(((*in_msg_ptr)).m_Type)), L1Cache_getState(addr), addr);
                if (result == TransitionResult_Valid) {
                  counter++;
                  continue; // Check the first port again
                }
                if (result == TransitionResult_ResourceStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
              }
;
            } else {
              if ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).isTagPresent(((*in_msg_ptr)).m_Address))) {
                if ((((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).cacheAvail(((*in_msg_ptr)).m_Address))) {
                                    {
                    Address addr = ((*in_msg_ptr)).m_Address;
                    TransitionResult result = doTransition((L1Cache_mandatory_request_type_to_event(((*in_msg_ptr)).m_Type)), L1Cache_getState(addr), addr);
                    if (result == TransitionResult_Valid) {
                      counter++;
                      continue; // Check the first port again
                    }
                    if (result == TransitionResult_ResourceStall) {
                      g_eventQueue_ptr->scheduleEvent(this, 1);
                      // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                    }
                  }
;
                } else {
                                    {
                    Address addr = (((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_ThreadID));
                    TransitionResult result = doTransition(L1Cache_Event_L1_Replacement, L1Cache_getState(addr), addr);
                    if (result == TransitionResult_Valid) {
                      counter++;
                      continue; // Check the first port again
                    }
                    if (result == TransitionResult_ResourceStall) {
                      g_eventQueue_ptr->scheduleEvent(this, 1);
                      // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                    }
                  }
;
                }
              } else {
                if ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).cacheAvail(((*in_msg_ptr)).m_Address))) {
                  if ((((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).cacheAvail(((*in_msg_ptr)).m_Address))) {
                                        {
                      Address addr = ((*in_msg_ptr)).m_Address;
                      TransitionResult result = doTransition((L1Cache_mandatory_request_type_to_event(((*in_msg_ptr)).m_Type)), L1Cache_getState(addr), addr);
                      if (result == TransitionResult_Valid) {
                        counter++;
                        continue; // Check the first port again
                      }
                      if (result == TransitionResult_ResourceStall) {
                        g_eventQueue_ptr->scheduleEvent(this, 1);
                        // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                      }
                    }
;
                  } else {
                                        {
                      Address addr = (((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_ThreadID));
                      TransitionResult result = doTransition(L1Cache_Event_L1_Replacement, L1Cache_getState(addr), addr);
                      if (result == TransitionResult_Valid) {
                        counter++;
                        continue; // Check the first port again
                      }
                      if (result == TransitionResult_ResourceStall) {
                        g_eventQueue_ptr->scheduleEvent(this, 1);
                        // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                      }
                    }
;
                  }
                } else {
                                    {
                    Address addr = (((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_ThreadID));
                    TransitionResult result = doTransition(L1Cache_Event_L15_Replacement, L1Cache_getState(addr), addr);
                    if (result == TransitionResult_Valid) {
                      counter++;
                      continue; // Check the first port again
                    }
                    if (result == TransitionResult_ResourceStall) {
                      g_eventQueue_ptr->scheduleEvent(this, 1);
                      // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                    }
                  }
;
                }
              }
            }
          } else {
            if ((((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).isTagPresent(((*in_msg_ptr)).m_Address))) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition(L1Cache_Event_L1_WriteBack, L1Cache_getState(addr), addr);
                if (result == TransitionResult_Valid) {
                  counter++;
                  continue; // Check the first port again
                }
                if (result == TransitionResult_ResourceStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
              }
;
            }
            if ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(((*in_msg_ptr)).m_Address))) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition((L1Cache_mandatory_request_type_to_event(((*in_msg_ptr)).m_Type)), L1Cache_getState(addr), addr);
                if (result == TransitionResult_Valid) {
                  counter++;
                  continue; // Check the first port again
                }
                if (result == TransitionResult_ResourceStall) {
                  g_eventQueue_ptr->scheduleEvent(this, 1);
                  // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                }
              }
;
            } else {
              if ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).isTagPresent(((*in_msg_ptr)).m_Address))) {
                if ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).cacheAvail(((*in_msg_ptr)).m_Address))) {
                                    {
                    Address addr = ((*in_msg_ptr)).m_Address;
                    TransitionResult result = doTransition((L1Cache_mandatory_request_type_to_event(((*in_msg_ptr)).m_Type)), L1Cache_getState(addr), addr);
                    if (result == TransitionResult_Valid) {
                      counter++;
                      continue; // Check the first port again
                    }
                    if (result == TransitionResult_ResourceStall) {
                      g_eventQueue_ptr->scheduleEvent(this, 1);
                      // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                    }
                  }
;
                } else {
                                    {
                    Address addr = (((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_ThreadID));
                    TransitionResult result = doTransition(L1Cache_Event_L1_Replacement, L1Cache_getState(addr), addr);
                    if (result == TransitionResult_Valid) {
                      counter++;
                      continue; // Check the first port again
                    }
                    if (result == TransitionResult_ResourceStall) {
                      g_eventQueue_ptr->scheduleEvent(this, 1);
                      // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                    }
                  }
;
                }
              } else {
                if ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).cacheAvail(((*in_msg_ptr)).m_Address))) {
                  if ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).cacheAvail(((*in_msg_ptr)).m_Address))) {
                                        {
                      Address addr = ((*in_msg_ptr)).m_Address;
                      TransitionResult result = doTransition((L1Cache_mandatory_request_type_to_event(((*in_msg_ptr)).m_Type)), L1Cache_getState(addr), addr);
                      if (result == TransitionResult_Valid) {
                        counter++;
                        continue; // Check the first port again
                      }
                      if (result == TransitionResult_ResourceStall) {
                        g_eventQueue_ptr->scheduleEvent(this, 1);
                        // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                      }
                    }
;
                  } else {
                                        {
                      Address addr = (((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_ThreadID));
                      TransitionResult result = doTransition(L1Cache_Event_L1_Replacement, L1Cache_getState(addr), addr);
                      if (result == TransitionResult_Valid) {
                        counter++;
                        continue; // Check the first port again
                      }
                      if (result == TransitionResult_ResourceStall) {
                        g_eventQueue_ptr->scheduleEvent(this, 1);
                        // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                      }
                    }
;
                  }
                } else {
                                    {
                    Address addr = (((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_ThreadID));
                    TransitionResult result = doTransition(L1Cache_Event_L15_Replacement, L1Cache_getState(addr), addr);
                    if (result == TransitionResult_Valid) {
                      counter++;
                      continue; // Check the first port again
                    }
                    if (result == TransitionResult_ResourceStall) {
                      g_eventQueue_ptr->scheduleEvent(this, 1);
                      // Cannot do anything with this transition, go check next doable transition (mostly likely of next port)
                    }
                  }
;
                }
              }
            }
          }
        }
      }

    break;  // If we got this far, we have nothing left todo
  }
}

