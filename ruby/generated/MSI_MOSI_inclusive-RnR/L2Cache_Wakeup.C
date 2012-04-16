// Auto generated C++ code started by symbols/StateMachine.C:425
// L2Cache: MOSI Directory L2 Cache CMP

#include "Global.h"
#include "RubySlicc_includes.h"
#include "L2Cache_Controller.h"
#include "L2Cache_State.h"
#include "L2Cache_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

void L2Cache_Controller::wakeup()
{

int counter = 0;
  while (true) {
    // Some cases will put us into an infinite loop without this limit
    assert(counter <= RubyConfig::L2CacheTransitionsPerCycle());
    if (counter == RubyConfig::L2CacheTransitionsPerCycle()) {
      g_system_ptr->getProfiler()->controllerBusy(m_machineID); // Count how often we're fully utilized
      g_eventQueue_ptr->scheduleEvent(this, 1); // Wakeup in another cycle and try again
      break;
    }
    // L2CacheInPort responseIntraChipL2Network_in
      if ((((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).isReady())) {
        {
          const ResponseMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:500: ", ((*in_msg_ptr)).m_Address);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:501: ", m_chip_ptr->getID());
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:502: ", (L2Cache_getState(((*in_msg_ptr)).m_Address)));
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:503: ", ((*in_msg_ptr)).m_SenderMachId);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:504: ", ((*in_msg_ptr)).m_Type);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:505: ", ((*in_msg_ptr)).m_NumPendingExtAcks);
;
                    if (ASSERT_FLAG && !(((((*in_msg_ptr)).m_Destination).isElement(m_machineID)))) {
            cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:507, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
          if (((machineIDToMachineType(((*in_msg_ptr)).m_SenderMachId)) == MachineType_L1Cache)) {
            if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA)) {
              if ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).isPresent(((*in_msg_ptr)).m_Address))) {
                if ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_NumPendingIntAcks == (1))) {
                                    {
                    Address addr = ((*in_msg_ptr)).m_Address;
                    TransitionResult result = doTransition(L2Cache_Event_Data_int_ack, L2Cache_getState(addr), addr);
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
                  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:515: ", ((*in_msg_ptr)).m_Address);
;
                  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:516: ", ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_NumPendingIntAcks);
;
                                    cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:517, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid L1 sent data when L2 wasn't expecting it") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
                }
              } else {
                if ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).isPresent(((*in_msg_ptr)).m_Address))) {
                  if ((((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_NumPendingIntAcks == (1))) {
                                        {
                      Address addr = ((*in_msg_ptr)).m_Address;
                      TransitionResult result = doTransition(L2Cache_Event_Data_int_ack, L2Cache_getState(addr), addr);
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
                    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:525: ", ((*in_msg_ptr)).m_Address);
;
                    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:526: ", ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_NumPendingIntAcks);
;
                                        cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:527, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid L1 sent data when L2 Pref TBE wasn't expecting it") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
                  }
                }
              }
            } else {
              if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_INV_ACK)) {
                if ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).isPresent(((*in_msg_ptr)).m_Address))) {
                  if ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_NumPendingIntAcks == (1))) {
                                        {
                      Address addr = ((*in_msg_ptr)).m_Address;
                      TransitionResult result = doTransition(L2Cache_Event_Proc_last_int_ack, L2Cache_getState(addr), addr);
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
                      Address addr = ((*in_msg_ptr)).m_Address;
                      TransitionResult result = doTransition(L2Cache_Event_Proc_int_ack, L2Cache_getState(addr), addr);
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
                  if ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).isPresent(((*in_msg_ptr)).m_Address))) {
                    if ((((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_NumPendingIntAcks == (1))) {
                                            {
                        Address addr = ((*in_msg_ptr)).m_Address;
                        TransitionResult result = doTransition(L2Cache_Event_Proc_last_int_ack, L2Cache_getState(addr), addr);
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
                        Address addr = ((*in_msg_ptr)).m_Address;
                        TransitionResult result = doTransition(L2Cache_Event_Proc_int_ack, L2Cache_getState(addr), addr);
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
          } else {
                        if (ASSERT_FLAG && !(((1) == (0)))) {
              cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:549, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

            }
;
          }
        }
      }

    // L2CacheInPort forwardedRequestIntraChipL2Network_in
      if ((((*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version]))).isReady())) {
        {
          const RequestMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:560: ", ((*in_msg_ptr)).m_Address);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:561: ", m_chip_ptr->getID());
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:562: ", (L2Cache_getState(((*in_msg_ptr)).m_Address)));
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:563: ", ((*in_msg_ptr)).m_RequestorMachId);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:564: ", ((*in_msg_ptr)).m_Type);
;
                    if (ASSERT_FLAG && !(((((*in_msg_ptr)).m_Destination).isElement(m_machineID)))) {
            cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:565, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
          if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS)) {
                        {
              Address addr = ((*in_msg_ptr)).m_Address;
              TransitionResult result = doTransition(L2Cache_Event_Forwarded_GETS, L2Cache_getState(addr), addr);
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
            if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GET_INSTR)) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition(L2Cache_Event_Forwarded_GET_INSTR, L2Cache_getState(addr), addr);
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
              if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETX)) {
                                {
                  Address addr = ((*in_msg_ptr)).m_Address;
                  TransitionResult result = doTransition(L2Cache_Event_Forwarded_GETX, L2Cache_getState(addr), addr);
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
                    TransitionResult result = doTransition(L2Cache_Event_L2_INV, L2Cache_getState(addr), addr);
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
                  if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_WB_ACK)) {
                                        {
                      Address addr = ((*in_msg_ptr)).m_Address;
                      TransitionResult result = doTransition(L2Cache_Event_Dir_WB_ack, L2Cache_getState(addr), addr);
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
                    if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_EXE_ACK)) {
                                            {
                        Address addr = ((*in_msg_ptr)).m_Address;
                        TransitionResult result = doTransition(L2Cache_Event_Dir_exe_ack, L2Cache_getState(addr), addr);
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
                      if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_PREFS)) {
                                                {
                          Address addr = ((*in_msg_ptr)).m_Address;
                          TransitionResult result = doTransition(L2Cache_Event_Forwarded_PREFS, L2Cache_getState(addr), addr);
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
                        if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_PREFX)) {
                                                    {
                            Address addr = ((*in_msg_ptr)).m_Address;
                            TransitionResult result = doTransition(L2Cache_Event_Forwarded_PREFX, L2Cache_getState(addr), addr);
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
                                                    cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:583, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid L2 forwarded request type") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

    // L2CacheInPort dataArrayReplQueueNetwork_in
      if ((((*(m_chip_ptr->m_L2Cache_dataArrayReplQueue_vec[m_version]))).isReady())) {
        {
          const RequestMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_dataArrayReplQueue_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:593: ", ((*in_msg_ptr)).m_Address);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:594: ", m_chip_ptr->getID());
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:595: ", (L2Cache_getState(((*in_msg_ptr)).m_Address)));
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:596: ", ((*in_msg_ptr)).m_RequestorMachId);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:597: ", ((*in_msg_ptr)).m_Type);
;
          if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_DATA_REPL)) {
                        {
              Address addr = ((*in_msg_ptr)).m_Address;
              TransitionResult result = doTransition(L2Cache_Event_Data_replacement, L2Cache_getState(addr), addr);
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
                        cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:602, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid L2 forwarded request type") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
          }
        }
      }

    // L2CacheInPort responseDram_in
      if ((((*(m_chip_ptr->m_L2Cache_responseToL2CacheQueue_vec[m_version]))).isReady())) {
        {
          const ResponseMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2CacheQueue_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:612: ", ((*in_msg_ptr)).m_Address);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:613: ", m_chip_ptr->getID());
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:614: ", (L2Cache_getState(((*in_msg_ptr)).m_Address)));
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:615: ", ((*in_msg_ptr)).m_SenderMachId);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:616: ", ((*in_msg_ptr)).m_Type);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:617: ", ((*in_msg_ptr)).m_NumPendingExtAcks);
;
                    if (ASSERT_FLAG && !((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA))) {
            cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:621, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
                    if (ASSERT_FLAG && !((((*in_msg_ptr)).m_NumPendingExtAcks == (0)))) {
            cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:622, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
                    {
            Address addr = ((*in_msg_ptr)).m_Address;
            TransitionResult result = doTransition(L2Cache_Event_Data_ext_ack_0, L2Cache_getState(addr), addr);
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

    // L2CacheInPort L1RequestIntraChipL2Network_in
      if (((((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).isReady()) && (((*(m_chip_ptr->m_L2Cache_dram_vec[m_version]))).isAbleMSHR((1))))) {
        {
          const RequestMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:634: ", ((*in_msg_ptr)).m_Address);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:635: ", m_chip_ptr->getID());
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:636: ", m_version);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:637: ", (L2Cache_getState(((*in_msg_ptr)).m_Address)));
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:638: ", ((*in_msg_ptr)).m_RequestorMachId);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:639: ", ((*in_msg_ptr)).m_Type);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:640: ", ((*in_msg_ptr)).m_Destination);
;
                    if (ASSERT_FLAG && !(((((*in_msg_ptr)).m_Destination).isElement(m_machineID)))) {
            cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:641, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
          if ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).isTagPresent(((*in_msg_ptr)).m_Address))) {
                        {
              Address addr = ((*in_msg_ptr)).m_Address;
              TransitionResult result = doTransition((L2Cache_L1Cache_request_type_to_event(((*in_msg_ptr)).m_Type, ((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_RequestorMachId)), L2Cache_getState(addr), addr);
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
            if ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheAvail(((*in_msg_ptr)).m_Address))) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition((L2Cache_L1Cache_request_type_to_event(((*in_msg_ptr)).m_Type, ((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_RequestorMachId)), L2Cache_getState(addr), addr);
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
              (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats2((4), ((*in_msg_ptr)).m_RequestorMachId, (0)));
                            {
                Address addr = (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_coreID));
                TransitionResult result = doTransition(L2Cache_Event_L2_Replacement, L2Cache_getState(addr), addr);
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

    // L2CacheInPort prefResponseDram_in
      if ((((*(m_chip_ptr->m_L2Cache_prefResponseToL2CacheQueue_vec[m_version]))).isReady())) {
        {
          const ResponseMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_prefResponseToL2CacheQueue_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:662: ", ((*in_msg_ptr)).m_Address);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:663: ", m_chip_ptr->getID());
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:664: ", (L2Cache_getState(((*in_msg_ptr)).m_Address)));
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:665: ", ((*in_msg_ptr)).m_SenderMachId);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:666: ", ((*in_msg_ptr)).m_Type);
;
          DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:667: ", ((*in_msg_ptr)).m_NumPendingExtAcks);
;
                    if (ASSERT_FLAG && !((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA))) {
            cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:671, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
                    if (ASSERT_FLAG && !((((*in_msg_ptr)).m_NumPendingExtAcks == (0)))) {
            cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:672, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
                    {
            Address addr = ((*in_msg_ptr)).m_Address;
            TransitionResult result = doTransition(L2Cache_Event_PrefData_ext_ack_0, L2Cache_getState(addr), addr);
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

    // L2CacheInPort prefetch_in
      if ((((*(m_chip_ptr->m_L2Cache_prefetchQueue_vec[m_version]))).isReady())) {
        {
          const RequestMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_prefetchQueue_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          if ((((*(m_chip_ptr->m_L2Cache_dram_vec[m_version]))).isAbleMSHR((0)))) {
            (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).getPrefetch());
            DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:687: ", ((*in_msg_ptr)).m_Address);
;
            DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:688: ", m_chip_ptr->getID());
;
            DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:689: ", m_version);
;
            DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:690: ", (L2Cache_getState(((*in_msg_ptr)).m_Address)));
;
            DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:692: ", ((*in_msg_ptr)).m_Type);
;
            if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_PREFS)) {
              if (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).isTagPresent(((*in_msg_ptr)).m_Address)) != (true)) && ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).isPresent(((*in_msg_ptr)).m_Address)) != (true))) && ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).isPresent(((*in_msg_ptr)).m_Address)) != (true)))) {
                if ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheAvail(((*in_msg_ptr)).m_Address))) {
                  (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats2((0), ((*in_msg_ptr)).m_RequestorMachId, (0)));
                                    {
                    Address addr = ((*in_msg_ptr)).m_Address;
                    TransitionResult result = doTransition(L2Cache_Event_PrefetchS, L2Cache_getState(addr), addr);
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
                  if (((((*in_msg_ptr)).m_coreID == ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_coreID))))).m_owner) && (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_coreID))))).m_prefetch == PrefetchBit_No))) {
                    (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).bloomL((1), (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_coreID)), ((*in_msg_ptr)).m_coreID));
                  }
                  if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_coreID))))).m_prefetch == PrefetchBit_No)) {
                    (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).bloomG((1), (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_coreID)), ((*in_msg_ptr)).m_coreID, ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_coreID))))).m_owner));
                  }
                  (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats2((4), ((*in_msg_ptr)).m_RequestorMachId, (0)));
                                    {
                    Address addr = (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_coreID));
                    TransitionResult result = doTransition(L2Cache_Event_L2_PrefetchS_Replacement, L2Cache_getState(addr), addr);
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
                (((*(m_chip_ptr->m_L2Cache_prefetchQueue_vec[m_version]))).dequeue());
              }
            } else {
              if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_PREFX)) {
                if (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).isTagPresent(((*in_msg_ptr)).m_Address)) != (true)) && ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).isPresent(((*in_msg_ptr)).m_Address)) != (true))) && ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).isPresent(((*in_msg_ptr)).m_Address)) != (true)))) {
                  if ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheAvail(((*in_msg_ptr)).m_Address))) {
                                        {
                      Address addr = ((*in_msg_ptr)).m_Address;
                      TransitionResult result = doTransition(L2Cache_Event_PrefetchX, L2Cache_getState(addr), addr);
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
                    (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats2((4), ((*in_msg_ptr)).m_RequestorMachId, (0)));
                                        {
                      Address addr = (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).cacheProbe(((*in_msg_ptr)).m_Address, ((*in_msg_ptr)).m_coreID));
                      TransitionResult result = doTransition(L2Cache_Event_L2_PrefetchX_Replacement, L2Cache_getState(addr), addr);
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
                  if ((((L2Cache_getState(((*in_msg_ptr)).m_Address)) == L2Cache_State_L2_S) || ((L2Cache_getState(((*in_msg_ptr)).m_Address)) == L2Cache_State_L2_SS))) {
                    (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats2((4), ((*in_msg_ptr)).m_RequestorMachId, (0)));
                                        {
                      Address addr = ((*in_msg_ptr)).m_Address;
                      TransitionResult result = doTransition(L2Cache_Event_PrefetchX, L2Cache_getState(addr), addr);
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
                    (((*(m_chip_ptr->m_L2Cache_prefetchQueue_vec[m_version]))).dequeue());
                  }
                }
              }
            }
          }
        }
      }

    break;  // If we got this far, we have nothing left todo
  }
}

