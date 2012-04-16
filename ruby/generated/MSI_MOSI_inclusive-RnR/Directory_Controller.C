/** \file Directory.C
  * 
  * Auto generated C++ code started by symbols/StateMachine.C:327
  * Created by slicc definition of Module "MOSI Directory Optimized"
  */

#include "Global.h"
#include "RubySlicc_includes.h"
#include "Directory_Controller.h"
#include "Directory_State.h"
#include "Directory_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

stringstream Directory_transitionComment;
#define APPEND_TRANSITION_COMMENT(str) (Directory_transitionComment << str)
/** \brief static profiler defn */
Directory_Profiler Directory_Controller::s_profiler;

/** \brief constructor */
Directory_Controller::Directory_Controller(Chip* chip_ptr, int version)
{
  m_chip_ptr = chip_ptr;
  m_id = m_chip_ptr->getID();
  m_version = version;
  m_machineID.type = MachineType_Directory;
  m_machineID.num = m_id*RubyConfig::numberOfDirectoryPerChip()+m_version;
  (*(m_chip_ptr->m_Directory_dramToDirQueue_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_Directory_dramToDirPrefQueue_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_Directory_finalAckToDir_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_Directory_requestToDir_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version])).setConsumer(this);

  (*(m_chip_ptr->m_Directory_dramToDirQueue_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", Directory, dramResponseNetwork_in]");
  (*(m_chip_ptr->m_Directory_dramToDirPrefQueue_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", Directory, dramPrefResponseNetwork_in]");
  (*(m_chip_ptr->m_Directory_finalAckToDir_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", Directory, finalAckNetwork_in]");
  (*(m_chip_ptr->m_Directory_requestToDir_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", Directory, requestNetwork_in]");
  (*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", Directory, prefRequestNetwork_in]");

  s_profiler.possibleTransition(Directory_State_OM, Directory_Event_FinalAck);
  s_profiler.possibleTransition(Directory_State_MM, Directory_Event_FinalAck);
  s_profiler.possibleTransition(Directory_State_OO, Directory_Event_FinalAck);
  s_profiler.possibleTransition(Directory_State_MO, Directory_Event_FinalAck);
  s_profiler.possibleTransition(Directory_State_NP, Directory_Event_PUTX_NotOwner);
  s_profiler.possibleTransition(Directory_State_I, Directory_Event_PUTX_NotOwner);
  s_profiler.possibleTransition(Directory_State_S, Directory_Event_PUTX_NotOwner);
  s_profiler.possibleTransition(Directory_State_M, Directory_Event_PUTX_NotOwner);
  s_profiler.possibleTransition(Directory_State_O, Directory_Event_PUTX_NotOwner);
  s_profiler.possibleTransition(Directory_State_OO, Directory_Event_PUTX_NotOwner);
  s_profiler.possibleTransition(Directory_State_OM, Directory_Event_PUTX_NotOwner);
  s_profiler.possibleTransition(Directory_State_MO, Directory_Event_PUTX_NotOwner);
  s_profiler.possibleTransition(Directory_State_MM, Directory_Event_PUTX_NotOwner);
  s_profiler.possibleTransition(Directory_State_NP, Directory_Event_GETS);
  s_profiler.possibleTransition(Directory_State_NP, Directory_Event_GET_INSTR);
  s_profiler.possibleTransition(Directory_State_I, Directory_Event_GETS);
  s_profiler.possibleTransition(Directory_State_I, Directory_Event_GET_INSTR);
  s_profiler.possibleTransition(Directory_State_NP, Directory_Event_PREFS);
  s_profiler.possibleTransition(Directory_State_I, Directory_Event_PREFS);
  s_profiler.possibleTransition(Directory_State_NP, Directory_Event_PREFX);
  s_profiler.possibleTransition(Directory_State_I, Directory_Event_PREFX);
  s_profiler.possibleTransition(Directory_State_NP, Directory_Event_GETX_NotOwner);
  s_profiler.possibleTransition(Directory_State_I, Directory_Event_GETX_NotOwner);
  s_profiler.possibleTransition(Directory_State_NP, Directory_Event_UG_PREFETCH);
  s_profiler.possibleTransition(Directory_State_I, Directory_Event_UG_PREFETCH);
  s_profiler.possibleTransition(Directory_State_S, Directory_Event_GETS);
  s_profiler.possibleTransition(Directory_State_S, Directory_Event_GET_INSTR);
  s_profiler.possibleTransition(Directory_State_S, Directory_Event_PREFS);
  s_profiler.possibleTransition(Directory_State_S, Directory_Event_PREFX);
  s_profiler.possibleTransition(Directory_State_S, Directory_Event_GETX_NotOwner);
  s_profiler.possibleTransition(Directory_State_S, Directory_Event_UG_PREFETCH);
  s_profiler.possibleTransition(Directory_State_SD, Directory_Event_DATA);
  s_profiler.possibleTransition(Directory_State_SPD, Directory_Event_DATA_P);
  s_profiler.possibleTransition(Directory_State_SPD, Directory_Event_DATA);
  s_profiler.possibleTransition(Directory_State_SD, Directory_Event_PREFS);
  s_profiler.possibleTransition(Directory_State_MD, Directory_Event_PREFS);
  s_profiler.possibleTransition(Directory_State_SPD, Directory_Event_UG_PREFETCH);
  s_profiler.possibleTransition(Directory_State_MD, Directory_Event_DATA);
  s_profiler.possibleTransition(Directory_State_MPD, Directory_Event_DATA);
  s_profiler.possibleTransition(Directory_State_O, Directory_Event_GETS);
  s_profiler.possibleTransition(Directory_State_O, Directory_Event_GET_INSTR);
  s_profiler.possibleTransition(Directory_State_O, Directory_Event_PREFS);
  s_profiler.possibleTransition(Directory_State_O, Directory_Event_PREFX);
  s_profiler.possibleTransition(Directory_State_O, Directory_Event_GETX_NotOwner);
  s_profiler.possibleTransition(Directory_State_O, Directory_Event_GETX_Owner);
  s_profiler.possibleTransition(Directory_State_O, Directory_Event_PUTX_Owner);
  s_profiler.possibleTransition(Directory_State_M, Directory_Event_GETS);
  s_profiler.possibleTransition(Directory_State_M, Directory_Event_GET_INSTR);
  s_profiler.possibleTransition(Directory_State_M, Directory_Event_PREFS);
  s_profiler.possibleTransition(Directory_State_M, Directory_Event_PREFX);
  s_profiler.possibleTransition(Directory_State_M, Directory_Event_GETX_NotOwner);
  s_profiler.possibleTransition(Directory_State_M, Directory_Event_GETX_Owner);
  s_profiler.possibleTransition(Directory_State_M, Directory_Event_PUTX_Owner);
}

void Directory_Controller::print(ostream& out) const { out << "[Directory_Controller " << m_chip_ptr->getID() << " " << m_version << "]"; }

// Actions

/** \brief Add requestor to list of sharers*/
void Directory_Controller::a_addRequestorToSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).add((L2CacheMachIDToChipID(((*in_msg_ptr)).m_RequestorMachId))));
    ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Add = ((*in_msg_ptr)).m_Address;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:302: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers);
;
  }
}

/** \brief Send data to requestor*/
void Directory_Controller::b_dataToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      if (((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETX) || (((*in_msg_ptr)).m_Type == CoherenceRequestType_PREFX))) {
        DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:315: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers);
;
        DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:316: ", ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).count()));
;
        (out_msg).m_NumPendingExtAcks = ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).count());
        if ((((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).count()) != (0))) {
          (out_msg).m_prevSharers = (getMultiStaticL2BankNetDest(addr, ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers));
        }
      } else {
        (out_msg).m_NumPendingExtAcks = (0);
      }
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_RequestorMachId));
      (out_msg).m_DataBlk = ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_DataBlk;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:326: ", (out_msg).m_Address);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:327: ", (out_msg).m_DataBlk);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:328: ", (out_msg).m_NumPendingExtAcks);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:329: ", (out_msg).m_Destination);
;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_Directory_responseFromDir_vec[m_version]))).enqueue(out_msg, MEMORY_LATENCY);
    }
  }
}

/** \brief Forward request to owner*/
void Directory_Controller::d_forwardRequestToOwner(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = ((*in_msg_ptr)).m_Type;
      (out_msg).m_RequestorMachId = ((*in_msg_ptr)).m_RequestorMachId;
      (((out_msg).m_Destination).add((map_L2ChipId_to_L2Cache((out_msg).m_Address, ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner))));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:345: ", (out_msg).m_Destination);
;
      if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETX)) {
        (out_msg).m_NumPendingExtAcks = ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).count());
      } else {
        (out_msg).m_NumPendingExtAcks = (0);
      }
      (out_msg).m_MessageSize = MessageSizeType_Control;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:353: ", (out_msg).m_Address);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:354: ", (out_msg).m_NumPendingExtAcks);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:355: ", (out_msg).m_Destination);
;
      ((*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version]))).enqueue(out_msg, DIRECTORY_LATENCY);
    }
  }
}

/** \brief Set owner equal to requestor*/
void Directory_Controller::f_setOwnerToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner = (L2CacheMachIDToChipID(((*in_msg_ptr)).m_RequestorMachId));
    ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_DirOwner = (false);
    ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Add = ((*in_msg_ptr)).m_Address;
  }
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:366: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner);
;
}

/** \brief Clear list of sharers*/
void Directory_Controller::g_clearSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).clear());
}

/** \brief Send INVs to all sharers*/
void Directory_Controller::h_invToSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:377: ", ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).count()));
;
    if ((((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).count()) != (0))) {
      {
        RequestMsg out_msg;
        (out_msg).m_Address = addr;
        (out_msg).m_Type = CoherenceRequestType_INV;
        (out_msg).m_RequestorMachId = ((*in_msg_ptr)).m_RequestorMachId;
        DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:383: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers);
;
        (out_msg).m_Destination = (getMultiStaticL2BankNetDest(addr, ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers));
        (out_msg).m_MessageSize = MessageSizeType_Control;
        ((*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version]))).enqueue(out_msg, DIRECTORY_LATENCY);
      }
    }
  }
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:390: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers);
;
}

/** \brief Pop incoming request queue*/
void Directory_Controller::j_popIncomingRequestQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((1), (((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Write PUTX/DWN data to memory*/
void Directory_Controller::l_writeRequestDataToMemory(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:401: ", ((*in_msg_ptr)).m_Address);
;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:402: ", ((*in_msg_ptr)).m_DataBlk);
;
  }
}

/** \brief Send WB_ack to requestor*/
void Directory_Controller::n_writebackAckToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_WB_ACK;
      (out_msg).m_RequestorMachId = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_RequestorMachId));
      (out_msg).m_MessageSize = MessageSizeType_Control;
      ((*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version]))).enqueue(out_msg, DIRECTORY_LATENCY);
    }
  }
}

/** \brief Send EXE_ack to requestor*/
void Directory_Controller::m_forwardExclusiveRequestToOwner(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_EXE_ACK;
      (out_msg).m_RequestorMachId = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_RequestorMachId));
      (out_msg).m_MessageSize = MessageSizeType_Control;
      ((*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version]))).enqueue(out_msg, DIRECTORY_LATENCY);
    }
  }
}

/** \brief Profile this transition.*/
void Directory_Controller::uu_profile(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (profile_request(((*in_msg_ptr)).m_L1CacheStateStr, ((*in_msg_ptr)).m_L2CacheStateStr, (Directory_getDirStateStr(addr)), (Directory_getRequestTypeStr(((*in_msg_ptr)).m_Type))));
  }
}

/** \brief Clear owner*/
void Directory_Controller::p_clearOwner(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_DirOwner = (true);
}

/** \brief Add owner to list of sharers*/
void Directory_Controller::r_addOwnerToSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:443: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner);
;
  ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).add(((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner));
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:445: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers);
;
}

/** \brief Remove owner from list of sharers*/
void Directory_Controller::t_removeOwnerFromSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:449: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner);
;
  ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).remove(((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner));
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:451: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers);
;
}

/** \brief Remove requestor from list of sharers*/
void Directory_Controller::u_removeRequestorFromSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:456: ", ((*in_msg_ptr)).m_RequestorMachId);
;
    ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).remove((L2CacheMachIDToChipID(((*in_msg_ptr)).m_RequestorMachId))));
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:458: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers);
;
  }
}

/** \brief */
void Directory_Controller::x_recycleRequest(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      out_msg = (*in_msg_ptr);
      ((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).enqueue(out_msg, RECYCLE_LATENCY);
    }
  }
}

/** \brief */
void Directory_Controller::hh_popFinalAckQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((4), (((*(m_chip_ptr->m_Directory_finalAckToDir_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief */
void Directory_Controller::z_stall(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
}

/** \brief Add requestor to list of sharers*/
void Directory_Controller::jja_addRequestorToSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).add((L2CacheMachIDToChipID(((*in_msg_ptr)).m_RequestorMachId))));
    ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Add = ((*in_msg_ptr)).m_Address;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:486: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers);
;
  }
}

/** \brief Send prefetched data to requestor*/
void Directory_Controller::jjb_dataToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_Directory_dramToDirPrefQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (out_msg).m_NumPendingExtAcks = (0);
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_RequestorMachId));
      (out_msg).m_DataBlk = ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_DataBlk;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:503: ", (out_msg).m_Address);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:504: ", (out_msg).m_DataBlk);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:505: ", (out_msg).m_NumPendingExtAcks);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:506: ", (out_msg).m_Destination);
;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_Directory_prefResponseFromDir_vec[m_version]))).enqueue(out_msg, 1);
    }
  }
}

/** \brief Forward request to owner*/
void Directory_Controller::jjd_forwardRequestToOwner(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = ((*in_msg_ptr)).m_Type;
      (out_msg).m_RequestorMachId = ((*in_msg_ptr)).m_RequestorMachId;
      (((out_msg).m_Destination).add((map_L2ChipId_to_L2Cache((out_msg).m_Address, ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner))));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:522: ", (out_msg).m_Destination);
;
      if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETX)) {
        (out_msg).m_NumPendingExtAcks = ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).count());
      } else {
        (out_msg).m_NumPendingExtAcks = (0);
      }
      (out_msg).m_MessageSize = MessageSizeType_Control;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:530: ", (out_msg).m_Address);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:531: ", (out_msg).m_NumPendingExtAcks);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:532: ", (out_msg).m_Destination);
;
      ((*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version]))).enqueue(out_msg, DIRECTORY_LATENCY);
    }
  }
}

/** \brief Set owner equal to requestor*/
void Directory_Controller::jjf_setOwnerToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner = (L2CacheMachIDToChipID(((*in_msg_ptr)).m_RequestorMachId));
    ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_DirOwner = (false);
    ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Add = ((*in_msg_ptr)).m_Address;
  }
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:543: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner);
;
}

/** \brief Clear list of sharers*/
void Directory_Controller::jjg_clearSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).clear());
}

/** \brief Send INVs to all sharers*/
void Directory_Controller::jjh_invToSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:554: ", ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).count()));
;
    if ((((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).count()) != (0))) {
      {
        RequestMsg out_msg;
        (out_msg).m_Address = addr;
        (out_msg).m_Type = CoherenceRequestType_INV;
        (out_msg).m_RequestorMachId = ((*in_msg_ptr)).m_RequestorMachId;
        DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:560: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers);
;
        (out_msg).m_Destination = (getMultiStaticL2BankNetDest(addr, ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers));
        (out_msg).m_MessageSize = MessageSizeType_Control;
        ((*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version]))).enqueue(out_msg, DIRECTORY_LATENCY);
      }
    }
  }
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:567: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers);
;
}

/** \brief Pop incoming request queue*/
void Directory_Controller::jjj_popIncomingRequestQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((5), (((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Write PUTX/DWN data to memory*/
void Directory_Controller::jjl_writeRequestDataToMemory(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(((*in_msg_ptr)).m_Address))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:578: ", ((*in_msg_ptr)).m_Address);
;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:579: ", ((*in_msg_ptr)).m_DataBlk);
;
  }
}

/** \brief Send WB_ack to requestor*/
void Directory_Controller::jjn_writebackAckToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_WB_ACK;
      (out_msg).m_RequestorMachId = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_RequestorMachId));
      (out_msg).m_MessageSize = MessageSizeType_Control;
      ((*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version]))).enqueue(out_msg, DIRECTORY_LATENCY);
    }
  }
}

/** \brief Send EXE_ack to requestor*/
void Directory_Controller::jjm_forwardExclusiveRequestToOwner(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_EXE_ACK;
      (out_msg).m_RequestorMachId = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_RequestorMachId));
      (out_msg).m_MessageSize = MessageSizeType_Control;
      ((*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version]))).enqueue(out_msg, DIRECTORY_LATENCY);
    }
  }
}

/** \brief Profile this transition.*/
void Directory_Controller::jjuu_profile(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (profile_request(((*in_msg_ptr)).m_L1CacheStateStr, ((*in_msg_ptr)).m_L2CacheStateStr, (Directory_getDirStateStr(addr)), (Directory_getRequestTypeStr(((*in_msg_ptr)).m_Type))));
  }
}

/** \brief Clear owner*/
void Directory_Controller::jjp_clearOwner(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_DirOwner = (true);
}

/** \brief Add owner to list of sharers*/
void Directory_Controller::jjr_addOwnerToSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:620: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner);
;
  ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).add(((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner));
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:622: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers);
;
}

/** \brief Remove owner from list of sharers*/
void Directory_Controller::jjt_removeOwnerFromSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:626: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner);
;
  ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).remove(((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_ProcOwner));
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:628: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers);
;
}

/** \brief Remove requestor from list of sharers*/
void Directory_Controller::jju_removeRequestorFromSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:633: ", ((*in_msg_ptr)).m_RequestorMachId);
;
    ((((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers).remove((L2CacheMachIDToChipID(((*in_msg_ptr)).m_RequestorMachId))));
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:635: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Sharers);
;
  }
}

/** \brief */
void Directory_Controller::jjx_recycleRequest(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      out_msg = (*in_msg_ptr);
      ((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).enqueue(out_msg, RECYCLE_LATENCY);
    }
  }
}

/** \brief */
void Directory_Controller::jjhh_popFinalAckQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((4), (((*(m_chip_ptr->m_Directory_finalAckToDir_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief */
void Directory_Controller::j_popDramResponseQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((3), (((*(m_chip_ptr->m_Directory_dramToDirQueue_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief */
void Directory_Controller::jp_popDramResponseQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((5), (((*(m_chip_ptr->m_Directory_dramToDirPrefQueue_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Send data to requestor*/
void Directory_Controller::bb_dataToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_Directory_dramToDirQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
            if (ASSERT_FLAG && !((addr == ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_Add))) {
        cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-dir.sm:666, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

      }
;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (out_msg).m_NumPendingExtAcks = (0);
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_RequestorMachId));
      (out_msg).m_DataBlk = ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(addr))).m_DataBlk;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:673: ", (out_msg).m_Address);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:674: ", (out_msg).m_DataBlk);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:675: ", (out_msg).m_NumPendingExtAcks);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-dir.sm:676: ", (out_msg).m_Destination);
;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_Directory_responseFromDir_vec[m_version]))).enqueue(out_msg, 1);
    }
  }
}

/** \brief */
void Directory_Controller::jp_requestToDram(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_prefRequestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
  }
}

/** \brief */
void Directory_Controller::jp_ugPrefToDram(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
  }
}

/** \brief */
void Directory_Controller::p_requestToDram(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_Directory_requestToDir_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETX)) {
    } else {
    }
  }
}

