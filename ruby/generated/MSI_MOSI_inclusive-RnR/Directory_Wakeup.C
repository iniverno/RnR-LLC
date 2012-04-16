// Auto generated C++ code started by symbols/StateMachine.C:425
// Directory: MOSI Directory Optimized

#include "Global.h"
#include "RubySlicc_includes.h"
#include "Directory_Controller.h"
#include "Directory_State.h"
#include "Directory_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

void Directory_Controller::wakeup()
{

int counter = 0;
  while (true) {
    // Some cases will put us into an infinite loop without this limit
    assert(counter <= RubyConfig::DirectoryTransitionsPerCycle());
    if (counter == RubyConfig::DirectoryTransitionsPerCycle()) {
      g_system_ptr->getProfiler()->controllerBusy(m_machineID); // Count how often we're fully utilized
      g_eventQueue_ptr->scheduleEvent(this, 1); // Wakeup in another cycle and try again
      break;
    }
    // DirectoryInPort dramResponseNetwork_in
      if ((((*(m_chip_ptr->m_Directory_dramToDirQueue_vec[m_version]))).isReady())) {
        {
          const ResponseMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_Directory_dramToDirQueue_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA)) {
                        {
              Address addr = ((*in_msg_ptr)).m_Address;
              TransitionResult result = doTransition(Directory_Event_DATA, Directory_getState(addr), addr);
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
                        cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-dir.sm:178, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid message") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
          }
        }
      }

    // DirectoryInPort dramPrefResponseNetwork_in
      if ((((*(m_chip_ptr->m_Directory_dramToDirPrefQueue_vec[m_version]))).isReady())) {
        {
          const ResponseMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_Directory_dramToDirPrefQueue_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
          if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_DATA)) {
                        {
              Address addr = ((*in_msg_ptr)).m_Address;
              TransitionResult result = doTransition(Directory_Event_DATA_P, Directory_getState(addr), addr);
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
                        cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-dir.sm:193, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid message") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
          }
        }
      }

    // DirectoryInPort finalAckNetwork_in
      if ((((*(m_chip_ptr->m_Directory_finalAckToDir_vec[m_version]))).isReady())) {
        {
          const ResponseMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_Directory_finalAckToDir_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
                    if (ASSERT_FLAG && !(((((*in_msg_ptr)).m_Destination).isElement(m_machineID)))) {
            cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-dir.sm:202, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
          if ((((*in_msg_ptr)).m_Type == CoherenceResponseType_FINALACK)) {
                        {
              Address addr = ((*in_msg_ptr)).m_Address;
              TransitionResult result = doTransition(Directory_Event_FinalAck, Directory_getState(addr), addr);
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
                        cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-dir.sm:206, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid message") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
          }
        }
      }

    // DirectoryInPort requestNetwork_in
      if ((((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).isReady())) {
        {
          const RequestMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
                    if (ASSERT_FLAG && !(((((*in_msg_ptr)).m_Destination).isElement(m_machineID)))) {
            cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-dir.sm:215, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
          if (((1) == (1))) {
            if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS)) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition(Directory_Event_GETS, Directory_getState(addr), addr);
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
                  TransitionResult result = doTransition(Directory_Event_GET_INSTR, Directory_getState(addr), addr);
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
                  if (((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_DirOwner == (false)) && ((L2CacheMachIDToChipID(((*in_msg_ptr)).m_RequestorMachId)) == ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_ProcOwner))) {
                                        {
                      Address addr = ((*in_msg_ptr)).m_Address;
                      TransitionResult result = doTransition(Directory_Event_GETX_Owner, Directory_getState(addr), addr);
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
                      TransitionResult result = doTransition(Directory_Event_GETX_NotOwner, Directory_getState(addr), addr);
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
                  if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_PUTX)) {
                    if (((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_DirOwner == (false)) && ((L2CacheMachIDToChipID(((*in_msg_ptr)).m_RequestorMachId)) == ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_ProcOwner))) {
                                            {
                        Address addr = ((*in_msg_ptr)).m_Address;
                        TransitionResult result = doTransition(Directory_Event_PUTX_Owner, Directory_getState(addr), addr);
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
                        TransitionResult result = doTransition(Directory_Event_PUTX_NotOwner, Directory_getState(addr), addr);
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
                    if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_UPGRADE)) {
                      if ((((Directory_getState(((*in_msg_ptr)).m_Address)) == Directory_State_NP) || ((Directory_getState(((*in_msg_ptr)).m_Address)) == Directory_State_I))) {
                        if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS)) {
                                                    {
                            Address addr = ((*in_msg_ptr)).m_Address;
                            TransitionResult result = doTransition(Directory_Event_GETS, Directory_getState(addr), addr);
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
                              TransitionResult result = doTransition(Directory_Event_GET_INSTR, Directory_getState(addr), addr);
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
                              if (((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_DirOwner == (false)) && ((L2CacheMachIDToChipID(((*in_msg_ptr)).m_RequestorMachId)) == ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_ProcOwner))) {
                                                                {
                                  Address addr = ((*in_msg_ptr)).m_Address;
                                  TransitionResult result = doTransition(Directory_Event_GETX_Owner, Directory_getState(addr), addr);
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
                                  TransitionResult result = doTransition(Directory_Event_GETX_NotOwner, Directory_getState(addr), addr);
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
                      } else {
                                                {
                          Address addr = ((*in_msg_ptr)).m_Address;
                          TransitionResult result = doTransition(Directory_Event_UG_PREFETCH, Directory_getState(addr), addr);
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
                                            cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-dir.sm:262, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid message") << ", PID: " << getpid() << endl;
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

    // DirectoryInPort prefRequestNetwork_in
      if ((((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).isReady())) {
        {
          const RequestMsg* in_msg_ptr;
          in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).peek());
          assert(in_msg_ptr != NULL);
                    if (ASSERT_FLAG && !(((((*in_msg_ptr)).m_Destination).isElement(m_machineID)))) {
            cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-dir.sm:273, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

          }
;
          if (((1) == (1))) {
            if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_PREFS)) {
                            {
                Address addr = ((*in_msg_ptr)).m_Address;
                TransitionResult result = doTransition(Directory_Event_PREFS, Directory_getState(addr), addr);
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
                  TransitionResult result = doTransition(Directory_Event_PREFX, Directory_getState(addr), addr);
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
                                cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-dir.sm:285, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("Invalid message") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
              }
            }
          }
        }
      }

    break;  // If we got this far, we have nothing left todo
  }
}

