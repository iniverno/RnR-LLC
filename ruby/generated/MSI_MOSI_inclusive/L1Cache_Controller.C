/** \file L1Cache.C
  * 
  * Auto generated C++ code started by symbols/StateMachine.C:327
  * Created by slicc definition of Module "MSI Directory L1 Cache CMP"
  */

#include "Global.h"
#include "RubySlicc_includes.h"
#include "L1Cache_Controller.h"
#include "L1Cache_State.h"
#include "L1Cache_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

stringstream L1Cache_transitionComment;
#define APPEND_TRANSITION_COMMENT(str) (L1Cache_transitionComment << str)
/** \brief static profiler defn */
L1Cache_Profiler L1Cache_Controller::s_profiler;

/** \brief constructor */
L1Cache_Controller::L1Cache_Controller(Chip* chip_ptr, int version)
{
  m_chip_ptr = chip_ptr;
  m_id = m_chip_ptr->getID();
  m_version = version;
  m_machineID.type = MachineType_L1Cache;
  m_machineID.num = m_id*RubyConfig::numberOfL1CachePerChip()+m_version;
  (*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L1Cache_requestToL1Cache_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version])).setConsumer(this);

  (*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", L1Cache, responseIntraChipL1Network_in]");
  (*(m_chip_ptr->m_L1Cache_requestToL1Cache_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", L1Cache, requestIntraChipL1Network_in]");
  (*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", L1Cache, mandatoryQueue_in]");

  s_profiler.possibleTransition(L1Cache_State_NP, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_NP, L1Cache_Event_L1_WriteBack);
  s_profiler.possibleTransition(L1Cache_State_L1_I, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_L1_I, L1Cache_Event_L1_WriteBack);
  s_profiler.possibleTransition(L1Cache_State_NP, L1Cache_Event_L15_Replacement);
  s_profiler.possibleTransition(L1Cache_State_L1_I, L1Cache_Event_L15_Replacement);
  s_profiler.possibleTransition(L1Cache_State_NP, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_L1_I, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_NP, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_L1_I, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_NP, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_L1_I, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_L1_S, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_L1_S, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_L1_S, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_L1_S, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_L1_S, L1Cache_Event_L1_WriteBack);
  s_profiler.possibleTransition(L1Cache_State_L1_S, L1Cache_Event_L15_Replacement);
  s_profiler.possibleTransition(L1Cache_State_L1_S, L1Cache_Event_L1_INV_S);
  s_profiler.possibleTransition(L1Cache_State_L1_S, L1Cache_Event_L1_INV_S_P);
  s_profiler.possibleTransition(L1Cache_State_L1_M, L1Cache_Event_Load);
  s_profiler.possibleTransition(L1Cache_State_L1_M, L1Cache_Event_Ifetch);
  s_profiler.possibleTransition(L1Cache_State_L1_M, L1Cache_Event_Store);
  s_profiler.possibleTransition(L1Cache_State_L1_M, L1Cache_Event_L1_Replacement);
  s_profiler.possibleTransition(L1Cache_State_L1_M, L1Cache_Event_L1_WriteBack);
  s_profiler.possibleTransition(L1Cache_State_L1_M, L1Cache_Event_L15_Replacement);
  s_profiler.possibleTransition(L1Cache_State_L1_M, L1Cache_Event_L1_INV);
  s_profiler.possibleTransition(L1Cache_State_L1_M, L1Cache_Event_L1_INV_P);
  s_profiler.possibleTransition(L1Cache_State_L1_M, L1Cache_Event_L1_DownGrade);
  s_profiler.possibleTransition(L1Cache_State_L1_IS, L1Cache_Event_L1_INV_S);
  s_profiler.possibleTransition(L1Cache_State_L1_IS, L1Cache_Event_L1_INV_S_P);
  s_profiler.possibleTransition(L1Cache_State_L1_IS, L1Cache_Event_L1_Data);
  s_profiler.possibleTransition(L1Cache_State_L1_IS, L1Cache_Event_L1_Data_I);
  s_profiler.possibleTransition(L1Cache_State_L1_ISI, L1Cache_Event_L1_Data);
  s_profiler.possibleTransition(L1Cache_State_L1_IM, L1Cache_Event_L1_INV);
  s_profiler.possibleTransition(L1Cache_State_L1_IM, L1Cache_Event_L1_INV_S);
  s_profiler.possibleTransition(L1Cache_State_L1_IM, L1Cache_Event_L1_INV_P);
  s_profiler.possibleTransition(L1Cache_State_L1_IM, L1Cache_Event_L1_INV_S_P);
  s_profiler.possibleTransition(L1Cache_State_L1_IM, L1Cache_Event_L1_DownGrade);
  s_profiler.possibleTransition(L1Cache_State_L1_IM, L1Cache_Event_L1_Data);
  s_profiler.possibleTransition(L1Cache_State_L1_IM, L1Cache_Event_L1_Data_S);
  s_profiler.possibleTransition(L1Cache_State_L1_IM, L1Cache_Event_L1_Data_I);
  s_profiler.possibleTransition(L1Cache_State_L1_IMI, L1Cache_Event_L1_Data);
  s_profiler.possibleTransition(L1Cache_State_L1_IMS, L1Cache_Event_L1_Data);
  s_profiler.possibleTransition(L1Cache_State_L1_IMS, L1Cache_Event_L1_INV_S);
  s_profiler.possibleTransition(L1Cache_State_L1_IMS, L1Cache_Event_L1_INV_S_P);
  s_profiler.possibleTransition(L1Cache_State_L1_IMSI, L1Cache_Event_L1_Data);
  s_profiler.possibleTransition(L1Cache_State_L1_SI, L1Cache_Event_L1_INV_S);
  s_profiler.possibleTransition(L1Cache_State_L1_SI, L1Cache_Event_L1_INV_S_P);
  s_profiler.possibleTransition(L1Cache_State_L1_SI, L1Cache_Event_L1_PutAck);
  s_profiler.possibleTransition(L1Cache_State_L1_MI, L1Cache_Event_L1_INV);
  s_profiler.possibleTransition(L1Cache_State_L1_MI, L1Cache_Event_L1_INV_P);
  s_profiler.possibleTransition(L1Cache_State_L1_MI, L1Cache_Event_L1_DownGrade);
  s_profiler.possibleTransition(L1Cache_State_L1_MI, L1Cache_Event_L1_PutAck);
}

void L1Cache_Controller::print(ostream& out) const { out << "[L1Cache_Controller " << m_chip_ptr->getID() << " " << m_version << "]"; }

// Actions

/** \brief Issue GETS*/
void L1Cache_Controller::a_issueGETS(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_GETS;
      (out_msg).m_RequestorMachId = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:459: ", addr);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:460: ", (out_msg).m_Destination);
;
      (out_msg).m_MessageSize = MessageSizeType_Control;
      (out_msg).m_L1CacheStateStr = (L1Cache_getStateStr(addr));
      (out_msg).m_Prefetch = ((*in_msg_ptr)).m_Prefetch;
      (out_msg).m_AccessMode = ((*in_msg_ptr)).m_AccessMode;
      (out_msg).m_ProgramCounter = ((*in_msg_ptr)).m_ProgramCounter;
      ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L15_REQUEST_LATENCY);
    }
  }
}

/** \brief Issue GETX*/
void L1Cache_Controller::b_issueGETX(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_GETX;
      (out_msg).m_RequestorMachId = m_machineID;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:477: ", m_machineID);
;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:479: ", addr);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:480: ", (out_msg).m_Destination);
;
      (out_msg).m_MessageSize = MessageSizeType_Control;
      (out_msg).m_L1CacheStateStr = (L1Cache_getStateStr(addr));
      (out_msg).m_Prefetch = ((*in_msg_ptr)).m_Prefetch;
      (out_msg).m_AccessMode = ((*in_msg_ptr)).m_AccessMode;
      (out_msg).m_ProgramCounter = ((*in_msg_ptr)).m_ProgramCounter;
      ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L15_REQUEST_LATENCY);
    }
  }
}

/** \brief Issue GETX*/
void L1Cache_Controller::c_issueUPGRADE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_UPGRADE;
      (out_msg).m_RequestorMachId = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:498: ", addr);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:499: ", (out_msg).m_Destination);
;
      (out_msg).m_MessageSize = MessageSizeType_Control;
      (out_msg).m_L1CacheStateStr = (L1Cache_getStateStr(addr));
      (out_msg).m_Prefetch = ((*in_msg_ptr)).m_Prefetch;
      (out_msg).m_AccessMode = ((*in_msg_ptr)).m_AccessMode;
      ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L15_REQUEST_LATENCY);
    }
  }
}

/** \brief Issue GETINSTR*/
void L1Cache_Controller::f_issueGETINSTR(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceRequestType_GET_INSTR;
      (out_msg).m_RequestorMachId = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:515: ", addr);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:516: ", (out_msg).m_Destination);
;
      (out_msg).m_MessageSize = MessageSizeType_Control;
      (out_msg).m_L1CacheStateStr = (L1Cache_getStateStr(addr));
      (out_msg).m_Prefetch = ((*in_msg_ptr)).m_Prefetch;
      (out_msg).m_AccessMode = ((*in_msg_ptr)).m_AccessMode;
      (out_msg).m_ProgramCounter = ((*in_msg_ptr)).m_ProgramCounter;
      ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L15_REQUEST_LATENCY);
    }
  }
}

/** \brief Issue PUTX*/
void L1Cache_Controller::d_issuePUTX(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    RequestMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceRequestType_PUTX;
    (out_msg).m_RequestorMachId = m_machineID;
    (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:533: ", addr);
;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:534: ", (out_msg).m_Destination);
;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:535: ", (out_msg).m_DataBlk);
;
    (out_msg).m_MessageSize = MessageSizeType_Data;
    (out_msg).m_L1CacheStateStr = (L1Cache_getStateStr(addr));
    ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L15_REQUEST_LATENCY);
  }
}

/** \brief Issue PUTS*/
void L1Cache_Controller::q_issuePUTS(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    RequestMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceRequestType_PUTS;
    (out_msg).m_RequestorMachId = m_machineID;
    (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:569: ", addr);
;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:570: ", (out_msg).m_Destination);
;
    (out_msg).m_MessageSize = MessageSizeType_Data;
    (out_msg).m_L1CacheStateStr = (L1Cache_getStateStr(addr));
    ((*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version]))).enqueue(out_msg, L15_REQUEST_LATENCY);
  }
}

/** \brief Send data from L1 cache to L2 Cache*/
void L1Cache_Controller::e_dataFromL1CacheToL2Cache(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_DATA;
    (out_msg).m_SenderMachId = m_machineID;
    (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:610: ", addr);
;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:611: ", (out_msg).m_Destination);
;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:612: ", (out_msg).m_DataBlk);
;
    (out_msg).m_MessageSize = MessageSizeType_Data;
    ((*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version]))).enqueue(out_msg, L15_REQUEST_LATENCY);
  }
}

/** \brief Send data from L1_TBE to L2 Cache*/
void L1Cache_Controller::f_dataFromTBEToL2Cache(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L1Cache_requestToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:648: ", addr);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:649: ", (out_msg).m_Destination);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:650: ", (out_msg).m_DataBlk);
;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version]))).enqueue(out_msg, L15_REQUEST_LATENCY);
    }
  }
}

/** \brief Send Invadiation ack to L2 Cache*/
void L1Cache_Controller::t_sendInvAckToL2Cache(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    ResponseMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceResponseType_INV_ACK;
    (out_msg).m_SenderMachId = m_machineID;
    (((out_msg).m_Destination).add((map_L1CacheMachId_to_L2Cache(addr, m_machineID))));
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:663: ", addr);
;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:664: ", (out_msg).m_Destination);
;
    (out_msg).m_MessageSize = MessageSizeType_Control;
    ((*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version]))).enqueue(out_msg, L15_REQUEST_LATENCY+L1_INV_LATENCY);
  }
}

/** \brief If not prefetch, notify sequencer the load completed.*/
void L1Cache_Controller::h_load_hit(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:712: ", ((L1Cache_getL1CacheEntry(addr))).m_DataBlk);
;
  ((*(dynamic_cast<Sequencer*>(m_chip_ptr->getSequencer(m_version)))).readCallback(addr));
}

/** \brief If not prefetch, notify sequencer that store completed.*/
void L1Cache_Controller::hh_store_hit(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:719: ", ((L1Cache_getL1CacheEntry(addr))).m_DataBlk);
;
  ((*(dynamic_cast<Sequencer*>(m_chip_ptr->getSequencer(m_version)))).writeCallback(addr));
}

/** \brief Allocate TBE (isPrefetch=0, number of invalidates=0)*/
void L1Cache_Controller::i_allocateTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).allocate(addr));
  ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_isPrefetch = (false);
}

/** \brief Pop mandatory queue.*/
void L1Cache_Controller::k_popMandatoryQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).dequeue());
}

/** \brief Pop incoming request queue and profile the delay within this virtual network*/
void L1Cache_Controller::l_popRequestQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((2), (((*(m_chip_ptr->m_L1Cache_requestToL1Cache_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Pop Incoming Response queue and profile the delay within this virtual network*/
void L1Cache_Controller::o_popIncomingResponseQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((3), (((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Deallocate TBE*/
void L1Cache_Controller::s_deallocateTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).deallocate(addr));
}

/** \brief Write data to cache*/
void L1Cache_Controller::u_writeDataToL1Cache(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L1Cache_responseToL1Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((L1Cache_getL1CacheEntry(addr))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
    ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).lookup(addr))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:751: ", addr);
;
  }
}

/** \brief Copy data from cache to TBE*/
void L1Cache_Controller::x_copyDataFromL1CacheToTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(addr))).m_reusedL1 = (0);
}

/** \brief Stall*/
void L1Cache_Controller::z_stall(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
}

/** \brief Deallocate L1 cache block.  Sets the cache to not present, allowing a replacement in parallel with a fetch.*/
void L1Cache_Controller::ff_deallocateL1CacheBlock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:775: ", addr);
;
  if ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(addr))) {
    (((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).deallocate(addr));
  } else {
    (((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).deallocate(addr));
  }
  ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).lookup(addr))).m_incl = (0);
}

/** \brief Deallocate L15 cache block.  Sets the cache to not present, allowing a replacement in parallel with a fetch.*/
void L1Cache_Controller::fff_deallocateL15CacheBlock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:795: ", addr);
;
  if ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).isTagPresent(addr))) {
    (((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).deallocate(addr));
  }
  if ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(addr))) {
    (((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).deallocate(addr));
  }
  if ((((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).isTagPresent(addr))) {
    (((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).deallocate(addr));
  }
}

/** \brief Set L1 D-cache tag equal to tag of block B.*/
void L1Cache_Controller::oo_allocateL1DCacheBlock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:811: ", addr);
;
  if (((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(addr)) == (false))) {
    (((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).allocate(addr));
    ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).lookup(addr))).m_reused = (false);
  }
}

/** \brief Set L1 I-cache tag equal to tag of block B.*/
void L1Cache_Controller::pp_allocateL1ICacheBlock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:820: ", addr);
;
  if (((((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).isTagPresent(addr)) == (false))) {
    (((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).allocate(addr));
    ((((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).lookup(addr))).m_reused = (false);
  }
}

/** \brief Set L15cache tag equal to tag of block B.*/
void L1Cache_Controller::ppp_allocateL15CacheBlockI(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:828: ", addr);
;
  if (((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).isTagPresent(addr)) == (false))) {
    (((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).allocate(addr));
  }
  ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).lookup(addr))).m_incl = (1);
}

/** \brief Set L15cache tag equal to tag of block B.*/
void L1Cache_Controller::ppp_allocateL15CacheBlockD(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:837: ", addr);
;
  if (((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).isTagPresent(addr)) == (false))) {
    (((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).allocate(addr));
  }
  ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).lookup(addr))).m_incl = (2);
}

/** \brief */
void L1Cache_Controller::jj_profilePrefInv(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:846: ", addr);
;
  if ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(addr))) {
    (profilePrefInv(m_machineID, (false)));
  } else {
    if ((((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).isTagPresent(addr))) {
      (profilePrefInv(m_machineID, (true)));
    }
  }
}

/** \brief Profile the demand miss*/
void L1Cache_Controller::uu_profileL15Miss(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:855: ", addr);
;
  {
    const CacheMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const CacheMsg*>(((*(m_chip_ptr->m_L1Cache_mandatoryQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (profile_L15Cache_miss((*in_msg_ptr), (machineIDToNodeID(m_machineID))));
  }
}

/** \brief Si el bloque no est‡ en la L1D, se pone*/
void L1Cache_Controller::ooo_compruebaPresenciaL1D(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:870: ", addr);
;
  if (((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(addr)) == (false))) {
    (((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).allocate(addr));
    ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).lookup(addr))).m_CacheState = ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).lookup(addr))).m_CacheState;
    (((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).changePermission(addr, (((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).getPermission(addr))));
  }
}

/** \brief Si el bloque no est‡ en la L1I, se pone*/
void L1Cache_Controller::oop_compruebaPresenciaL1I(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:881: ", addr);
;
  if (((((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).isTagPresent(addr)) == (false))) {
    (((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).allocate(addr));
    ((((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).lookup(addr))).m_CacheState = ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).lookup(addr))).m_CacheState;
    (((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).changePermission(addr, (((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).getPermission(addr))));
  }
}

/** \brief Marca el bit de reuso en L1 o L15*/
void L1Cache_Controller::jjj_actualizaReuso(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-L115cache.sm:892: ", addr);
;
}

