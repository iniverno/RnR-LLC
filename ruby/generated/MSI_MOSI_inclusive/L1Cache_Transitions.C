// Auto generated C++ code started by symbols/StateMachine.C:473
// L1Cache: MSI Directory L1 Cache CMP

#include "Global.h"
#include "L1Cache_Controller.h"
#include "L1Cache_State.h"
#include "L1Cache_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

#define HASH_FUN(state, event)  ((int(state)*L1Cache_Event_NUM)+int(event))

#define GET_TRANSITION_COMMENT() (L1Cache_transitionComment.str())
#define CLEAR_TRANSITION_COMMENT() (L1Cache_transitionComment.str(""))

TransitionResult L1Cache_Controller::doTransition(L1Cache_Event event, L1Cache_State state, const Address& addr
)
{
  L1Cache_State next_state = state;

  DEBUG_NEWLINE(GENERATED_COMP, MedPrio);
  DEBUG_MSG(GENERATED_COMP, MedPrio,*this);
  DEBUG_EXPR(GENERATED_COMP, MedPrio,g_eventQueue_ptr->getTime());
  DEBUG_EXPR(GENERATED_COMP, MedPrio,state);
  DEBUG_EXPR(GENERATED_COMP, MedPrio,event);
  DEBUG_EXPR(GENERATED_COMP, MedPrio,addr);

  TransitionResult result = doTransitionWorker(event, state, next_state, addr);

  if (result == TransitionResult_Valid) {
    DEBUG_EXPR(GENERATED_COMP, MedPrio, next_state);
    DEBUG_NEWLINE(GENERATED_COMP, MedPrio);
    s_profiler.countTransition(state, event);
    if (PROTOCOL_DEBUG_TRACE) {
      g_system_ptr->getProfiler()->profileTransition("L1Cache", m_chip_ptr->getID(), m_version, addr, 
        L1Cache_State_to_string(state), 
        L1Cache_Event_to_string(event), 
        L1Cache_State_to_string(next_state), GET_TRANSITION_COMMENT());
    }
    CLEAR_TRANSITION_COMMENT();
    L1Cache_setState(addr, next_state);
    
  } else if (result == TransitionResult_ResourceStall) {
    if (PROTOCOL_DEBUG_TRACE) {
      g_system_ptr->getProfiler()->profileTransition("L1Cache", m_chip_ptr->getID(), m_version, addr, 
        L1Cache_State_to_string(state), 
        L1Cache_Event_to_string(event), 
        L1Cache_State_to_string(next_state), 
        "Resource Stall");
    }
  } else if (result == TransitionResult_ProtocolStall) {
    DEBUG_MSG(GENERATED_COMP,HighPrio,"stalling");
    DEBUG_NEWLINE(GENERATED_COMP, MedPrio);
    if (PROTOCOL_DEBUG_TRACE) {
      g_system_ptr->getProfiler()->profileTransition("L1Cache", m_chip_ptr->getID(), m_version, addr, 
        L1Cache_State_to_string(state), 
        L1Cache_Event_to_string(event), 
        L1Cache_State_to_string(next_state), 
        "Protocol Stall");
    }
  }
  return result;
}

TransitionResult L1Cache_Controller::doTransitionWorker(L1Cache_Event event, L1Cache_State state, L1Cache_State& next_state, const Address& addr
)
{

  switch(HASH_FUN(state, event)) {
  case HASH_FUN(L1Cache_State_L1_IS, L1Cache_Event_Load):
  case HASH_FUN(L1Cache_State_L1_IS, L1Cache_Event_Ifetch):
  case HASH_FUN(L1Cache_State_L1_IS, L1Cache_Event_Store):
  case HASH_FUN(L1Cache_State_L1_IS, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_L1_IS, L1Cache_Event_L15_Replacement):
  case HASH_FUN(L1Cache_State_L1_IS, L1Cache_Event_L1_WriteBack):
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_Load):
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_Ifetch):
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_Store):
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_L15_Replacement):
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_L1_WriteBack):
  case HASH_FUN(L1Cache_State_L1_ISI, L1Cache_Event_Load):
  case HASH_FUN(L1Cache_State_L1_ISI, L1Cache_Event_Ifetch):
  case HASH_FUN(L1Cache_State_L1_ISI, L1Cache_Event_Store):
  case HASH_FUN(L1Cache_State_L1_ISI, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_L1_ISI, L1Cache_Event_L15_Replacement):
  case HASH_FUN(L1Cache_State_L1_ISI, L1Cache_Event_L1_WriteBack):
  case HASH_FUN(L1Cache_State_L1_IMI, L1Cache_Event_Load):
  case HASH_FUN(L1Cache_State_L1_IMI, L1Cache_Event_Ifetch):
  case HASH_FUN(L1Cache_State_L1_IMI, L1Cache_Event_Store):
  case HASH_FUN(L1Cache_State_L1_IMI, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_L1_IMI, L1Cache_Event_L15_Replacement):
  case HASH_FUN(L1Cache_State_L1_IMI, L1Cache_Event_L1_WriteBack):
  case HASH_FUN(L1Cache_State_L1_IMS, L1Cache_Event_Load):
  case HASH_FUN(L1Cache_State_L1_IMS, L1Cache_Event_Ifetch):
  case HASH_FUN(L1Cache_State_L1_IMS, L1Cache_Event_Store):
  case HASH_FUN(L1Cache_State_L1_IMS, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_L1_IMS, L1Cache_Event_L15_Replacement):
  case HASH_FUN(L1Cache_State_L1_IMS, L1Cache_Event_L1_WriteBack):
  case HASH_FUN(L1Cache_State_L1_IMSI, L1Cache_Event_Load):
  case HASH_FUN(L1Cache_State_L1_IMSI, L1Cache_Event_Ifetch):
  case HASH_FUN(L1Cache_State_L1_IMSI, L1Cache_Event_Store):
  case HASH_FUN(L1Cache_State_L1_IMSI, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_L1_IMSI, L1Cache_Event_L15_Replacement):
  case HASH_FUN(L1Cache_State_L1_IMSI, L1Cache_Event_L1_WriteBack):
  case HASH_FUN(L1Cache_State_L1_SI, L1Cache_Event_Load):
  case HASH_FUN(L1Cache_State_L1_SI, L1Cache_Event_Ifetch):
  case HASH_FUN(L1Cache_State_L1_SI, L1Cache_Event_Store):
  case HASH_FUN(L1Cache_State_L1_SI, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_L1_SI, L1Cache_Event_L15_Replacement):
  case HASH_FUN(L1Cache_State_L1_SI, L1Cache_Event_L1_WriteBack):
  case HASH_FUN(L1Cache_State_L1_MI, L1Cache_Event_Load):
  case HASH_FUN(L1Cache_State_L1_MI, L1Cache_Event_Ifetch):
  case HASH_FUN(L1Cache_State_L1_MI, L1Cache_Event_Store):
  case HASH_FUN(L1Cache_State_L1_MI, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_L1_MI, L1Cache_Event_L15_Replacement):
  case HASH_FUN(L1Cache_State_L1_MI, L1Cache_Event_L1_WriteBack):
  {
    return TransitionResult_ProtocolStall;
  }
  case HASH_FUN(L1Cache_State_NP, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_NP, L1Cache_Event_L1_WriteBack):
  case HASH_FUN(L1Cache_State_L1_I, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_L1_I, L1Cache_Event_L1_WriteBack):
  case HASH_FUN(L1Cache_State_L1_S, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_L1_S, L1Cache_Event_L1_WriteBack):
  case HASH_FUN(L1Cache_State_L1_M, L1Cache_Event_L1_Replacement):
  case HASH_FUN(L1Cache_State_L1_M, L1Cache_Event_L1_WriteBack):
  {
    ff_deallocateL1CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_NP, L1Cache_Event_L15_Replacement):
  case HASH_FUN(L1Cache_State_L1_I, L1Cache_Event_L15_Replacement):
  {
    fff_deallocateL15CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_NP, L1Cache_Event_Load):
  case HASH_FUN(L1Cache_State_L1_I, L1Cache_Event_Load):
  {
    next_state = L1Cache_State_L1_IS;
    if (!(*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    oo_allocateL1DCacheBlock(addr);
    ppp_allocateL15CacheBlockD(addr);
    i_allocateTBE(addr);
    uu_profileL15Miss(addr);
    a_issueGETS(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_NP, L1Cache_Event_Ifetch):
  case HASH_FUN(L1Cache_State_L1_I, L1Cache_Event_Ifetch):
  {
    next_state = L1Cache_State_L1_IS;
    if (!(*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    pp_allocateL1ICacheBlock(addr);
    ppp_allocateL15CacheBlockI(addr);
    i_allocateTBE(addr);
    uu_profileL15Miss(addr);
    f_issueGETINSTR(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_NP, L1Cache_Event_Store):
  case HASH_FUN(L1Cache_State_L1_I, L1Cache_Event_Store):
  {
    next_state = L1Cache_State_L1_IM;
    if (!(*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    oo_allocateL1DCacheBlock(addr);
    ppp_allocateL15CacheBlockD(addr);
    i_allocateTBE(addr);
    b_issueGETX(addr);
    uu_profileL15Miss(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_S, L1Cache_Event_Load):
  case HASH_FUN(L1Cache_State_L1_M, L1Cache_Event_Load):
  {
    jjj_actualizaReuso(addr);
    ooo_compruebaPresenciaL1D(addr);
    h_load_hit(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_S, L1Cache_Event_Ifetch):
  case HASH_FUN(L1Cache_State_L1_M, L1Cache_Event_Ifetch):
  {
    jjj_actualizaReuso(addr);
    oop_compruebaPresenciaL1I(addr);
    h_load_hit(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_S, L1Cache_Event_Store):
  {
    next_state = L1Cache_State_L1_IM;
    if (!(*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    i_allocateTBE(addr);
    jjj_actualizaReuso(addr);
    ooo_compruebaPresenciaL1D(addr);
    c_issueUPGRADE(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_S, L1Cache_Event_L15_Replacement):
  {
    next_state = L1Cache_State_L1_SI;
    if (!(*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    i_allocateTBE(addr);
    q_issuePUTS(addr);
    x_copyDataFromL1CacheToTBE(addr);
    fff_deallocateL15CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_S, L1Cache_Event_L1_INV_S):
  {
    next_state = L1Cache_State_L1_I;
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    t_sendInvAckToL2Cache(addr);
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_S, L1Cache_Event_L1_INV_S_P):
  {
    next_state = L1Cache_State_L1_I;
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    t_sendInvAckToL2Cache(addr);
    jj_profilePrefInv(addr);
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_M, L1Cache_Event_Store):
  {
    jjj_actualizaReuso(addr);
    ooo_compruebaPresenciaL1D(addr);
    hh_store_hit(addr);
    k_popMandatoryQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_M, L1Cache_Event_L15_Replacement):
  {
    next_state = L1Cache_State_L1_MI;
    if (!(*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L1Cache_requestFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    i_allocateTBE(addr);
    d_issuePUTX(addr);
    x_copyDataFromL1CacheToTBE(addr);
    fff_deallocateL15CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_M, L1Cache_Event_L1_INV):
  {
    next_state = L1Cache_State_L1_I;
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    e_dataFromL1CacheToL2Cache(addr);
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_M, L1Cache_Event_L1_INV_P):
  {
    next_state = L1Cache_State_L1_I;
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    e_dataFromL1CacheToL2Cache(addr);
    jj_profilePrefInv(addr);
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_M, L1Cache_Event_L1_DownGrade):
  {
    next_state = L1Cache_State_L1_S;
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    e_dataFromL1CacheToL2Cache(addr);
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_IS, L1Cache_Event_L1_INV_S):
  {
    next_state = L1Cache_State_L1_ISI;
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    t_sendInvAckToL2Cache(addr);
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_IS, L1Cache_Event_L1_INV_S_P):
  {
    next_state = L1Cache_State_L1_ISI;
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    t_sendInvAckToL2Cache(addr);
    jj_profilePrefInv(addr);
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_IS, L1Cache_Event_L1_Data):
  {
    next_state = L1Cache_State_L1_S;
    h_load_hit(addr);
    s_deallocateTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_IS, L1Cache_Event_L1_Data_I):
  case HASH_FUN(L1Cache_State_L1_ISI, L1Cache_Event_L1_Data):
  {
    next_state = L1Cache_State_L1_I;
    h_load_hit(addr);
    s_deallocateTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_L1_INV):
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_L1_INV_P):
  {
    next_state = L1Cache_State_L1_IMI;
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_L1_INV_S):
  case HASH_FUN(L1Cache_State_L1_SI, L1Cache_Event_L1_INV_S):
  {
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    t_sendInvAckToL2Cache(addr);
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_L1_INV_S_P):
  case HASH_FUN(L1Cache_State_L1_SI, L1Cache_Event_L1_INV_S_P):
  {
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    t_sendInvAckToL2Cache(addr);
    jj_profilePrefInv(addr);
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_L1_DownGrade):
  {
    next_state = L1Cache_State_L1_IMS;
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_L1_Data):
  {
    next_state = L1Cache_State_L1_M;
    hh_store_hit(addr);
    s_deallocateTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_L1_Data_S):
  case HASH_FUN(L1Cache_State_L1_IMS, L1Cache_Event_L1_Data):
  {
    next_state = L1Cache_State_L1_S;
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    hh_store_hit(addr);
    s_deallocateTBE(addr);
    e_dataFromL1CacheToL2Cache(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_IM, L1Cache_Event_L1_Data_I):
  case HASH_FUN(L1Cache_State_L1_IMI, L1Cache_Event_L1_Data):
  case HASH_FUN(L1Cache_State_L1_IMSI, L1Cache_Event_L1_Data):
  {
    next_state = L1Cache_State_L1_I;
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    hh_store_hit(addr);
    s_deallocateTBE(addr);
    e_dataFromL1CacheToL2Cache(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_IMS, L1Cache_Event_L1_INV_S):
  case HASH_FUN(L1Cache_State_L1_IMS, L1Cache_Event_L1_INV_S_P):
  {
    next_state = L1Cache_State_L1_IMSI;
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_SI, L1Cache_Event_L1_PutAck):
  case HASH_FUN(L1Cache_State_L1_MI, L1Cache_Event_L1_PutAck):
  {
    next_state = L1Cache_State_L1_I;
    s_deallocateTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_MI, L1Cache_Event_L1_INV):
  {
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    f_dataFromTBEToL2Cache(addr);
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_MI, L1Cache_Event_L1_INV_P):
  {
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    f_dataFromTBEToL2Cache(addr);
    jj_profilePrefInv(addr);
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L1Cache_State_L1_MI, L1Cache_Event_L1_DownGrade):
  {
    next_state = L1Cache_State_L1_SI;
    if (!(*(m_chip_ptr->m_L1Cache_responseFromL1Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    f_dataFromTBEToL2Cache(addr);
    l_popRequestQueue(addr);
    return TransitionResult_Valid;
  }
  default:
    WARN_EXPR(m_id);
    WARN_EXPR(m_version);
    WARN_EXPR(g_eventQueue_ptr->getTime());
    WARN_EXPR(addr);
    WARN_EXPR(event);
    WARN_EXPR(state);
    ERROR_MSG("Invalid transition");
  }
  return TransitionResult_Valid;
}
