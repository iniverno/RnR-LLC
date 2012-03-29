// Auto generated C++ code started by symbols/StateMachine.C:473
// Directory: MOSI Directory Optimized

#include "Global.h"
#include "Directory_Controller.h"
#include "Directory_State.h"
#include "Directory_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

#define HASH_FUN(state, event)  ((int(state)*Directory_Event_NUM)+int(event))

#define GET_TRANSITION_COMMENT() (Directory_transitionComment.str())
#define CLEAR_TRANSITION_COMMENT() (Directory_transitionComment.str(""))

TransitionResult Directory_Controller::doTransition(Directory_Event event, Directory_State state, const Address& addr
)
{
  Directory_State next_state = state;

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
      g_system_ptr->getProfiler()->profileTransition("Directory", m_chip_ptr->getID(), m_version, addr, 
        Directory_State_to_string(state), 
        Directory_Event_to_string(event), 
        Directory_State_to_string(next_state), GET_TRANSITION_COMMENT());
    }
    CLEAR_TRANSITION_COMMENT();
    Directory_setState(addr, next_state);
    
  } else if (result == TransitionResult_ResourceStall) {
    if (PROTOCOL_DEBUG_TRACE) {
      g_system_ptr->getProfiler()->profileTransition("Directory", m_chip_ptr->getID(), m_version, addr, 
        Directory_State_to_string(state), 
        Directory_Event_to_string(event), 
        Directory_State_to_string(next_state), 
        "Resource Stall");
    }
  } else if (result == TransitionResult_ProtocolStall) {
    DEBUG_MSG(GENERATED_COMP,HighPrio,"stalling");
    DEBUG_NEWLINE(GENERATED_COMP, MedPrio);
    if (PROTOCOL_DEBUG_TRACE) {
      g_system_ptr->getProfiler()->profileTransition("Directory", m_chip_ptr->getID(), m_version, addr, 
        Directory_State_to_string(state), 
        Directory_Event_to_string(event), 
        Directory_State_to_string(next_state), 
        "Protocol Stall");
    }
  }
  return result;
}

TransitionResult Directory_Controller::doTransitionWorker(Directory_Event event, Directory_State state, Directory_State& next_state, const Address& addr
)
{

  switch(HASH_FUN(state, event)) {
  case HASH_FUN(Directory_State_OM, Directory_Event_FinalAck):
  case HASH_FUN(Directory_State_MM, Directory_Event_FinalAck):
  {
    next_state = Directory_State_M;
    hh_popFinalAckQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_OO, Directory_Event_FinalAck):
  case HASH_FUN(Directory_State_MO, Directory_Event_FinalAck):
  {
    next_state = Directory_State_O;
    hh_popFinalAckQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_OO, Directory_Event_GETS):
  case HASH_FUN(Directory_State_OO, Directory_Event_GET_INSTR):
  case HASH_FUN(Directory_State_OO, Directory_Event_GETX_Owner):
  case HASH_FUN(Directory_State_OO, Directory_Event_GETX_NotOwner):
  case HASH_FUN(Directory_State_OO, Directory_Event_PUTX_Owner):
  case HASH_FUN(Directory_State_OM, Directory_Event_GETS):
  case HASH_FUN(Directory_State_OM, Directory_Event_GET_INSTR):
  case HASH_FUN(Directory_State_OM, Directory_Event_GETX_Owner):
  case HASH_FUN(Directory_State_OM, Directory_Event_GETX_NotOwner):
  case HASH_FUN(Directory_State_OM, Directory_Event_PUTX_Owner):
  case HASH_FUN(Directory_State_MO, Directory_Event_GETS):
  case HASH_FUN(Directory_State_MO, Directory_Event_GET_INSTR):
  case HASH_FUN(Directory_State_MO, Directory_Event_GETX_Owner):
  case HASH_FUN(Directory_State_MO, Directory_Event_GETX_NotOwner):
  case HASH_FUN(Directory_State_MO, Directory_Event_PUTX_Owner):
  case HASH_FUN(Directory_State_MM, Directory_Event_GETS):
  case HASH_FUN(Directory_State_MM, Directory_Event_GET_INSTR):
  case HASH_FUN(Directory_State_MM, Directory_Event_GETX_Owner):
  case HASH_FUN(Directory_State_MM, Directory_Event_GETX_NotOwner):
  case HASH_FUN(Directory_State_MM, Directory_Event_PUTX_Owner):
  case HASH_FUN(Directory_State_OO, Directory_Event_PREFS):
  case HASH_FUN(Directory_State_OO, Directory_Event_PREFX):
  case HASH_FUN(Directory_State_OM, Directory_Event_PREFS):
  case HASH_FUN(Directory_State_OM, Directory_Event_PREFX):
  case HASH_FUN(Directory_State_MO, Directory_Event_PREFS):
  case HASH_FUN(Directory_State_MO, Directory_Event_PREFX):
  case HASH_FUN(Directory_State_MM, Directory_Event_PREFS):
  case HASH_FUN(Directory_State_MM, Directory_Event_PREFX):
  {
    return TransitionResult_ProtocolStall;
  }
  case HASH_FUN(Directory_State_NP, Directory_Event_PUTX_NotOwner):
  case HASH_FUN(Directory_State_S, Directory_Event_PUTX_NotOwner):
  case HASH_FUN(Directory_State_M, Directory_Event_PUTX_NotOwner):
  case HASH_FUN(Directory_State_O, Directory_Event_PUTX_NotOwner):
  case HASH_FUN(Directory_State_OO, Directory_Event_PUTX_NotOwner):
  case HASH_FUN(Directory_State_OM, Directory_Event_PUTX_NotOwner):
  case HASH_FUN(Directory_State_MO, Directory_Event_PUTX_NotOwner):
  case HASH_FUN(Directory_State_MM, Directory_Event_PUTX_NotOwner):
  {
    next_state = Directory_State_I;
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profile(addr);
    l_writeRequestDataToMemory(addr);
    n_writebackAckToRequestor(addr);
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_I, Directory_Event_PUTX_NotOwner):
  {
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profile(addr);
    l_writeRequestDataToMemory(addr);
    n_writebackAckToRequestor(addr);
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_NP, Directory_Event_GETS):
  case HASH_FUN(Directory_State_NP, Directory_Event_GET_INSTR):
  case HASH_FUN(Directory_State_I, Directory_Event_GETS):
  case HASH_FUN(Directory_State_I, Directory_Event_GET_INSTR):
  case HASH_FUN(Directory_State_S, Directory_Event_GETS):
  case HASH_FUN(Directory_State_S, Directory_Event_GET_INSTR):
  {
    next_state = Directory_State_SD;
    uu_profile(addr);
    a_addRequestorToSharers(addr);
    p_requestToDram(addr);
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_NP, Directory_Event_PREFS):
  case HASH_FUN(Directory_State_I, Directory_Event_PREFS):
  case HASH_FUN(Directory_State_S, Directory_Event_PREFS):
  {
    next_state = Directory_State_SPD;
    jjuu_profile(addr);
    jja_addRequestorToSharers(addr);
    jp_requestToDram(addr);
    jjj_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_NP, Directory_Event_PREFX):
  case HASH_FUN(Directory_State_I, Directory_Event_PREFX):
  {
    next_state = Directory_State_MPD;
    jjuu_profile(addr);
    jjf_setOwnerToRequestor(addr);
    jp_requestToDram(addr);
    jjj_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_NP, Directory_Event_GETX_NotOwner):
  case HASH_FUN(Directory_State_I, Directory_Event_GETX_NotOwner):
  {
    next_state = Directory_State_MD;
    uu_profile(addr);
    f_setOwnerToRequestor(addr);
    p_requestToDram(addr);
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_NP, Directory_Event_UG_PREFETCH):
  case HASH_FUN(Directory_State_I, Directory_Event_UG_PREFETCH):
  {
    uu_profile(addr);
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_S, Directory_Event_PREFX):
  {
    next_state = Directory_State_MPD;
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    jjuu_profile(addr);
    jju_removeRequestorFromSharers(addr);
    jjf_setOwnerToRequestor(addr);
    jjh_invToSharers(addr);
    jjg_clearSharers(addr);
    jp_requestToDram(addr);
    jjj_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_S, Directory_Event_GETX_NotOwner):
  {
    next_state = Directory_State_MD;
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profile(addr);
    u_removeRequestorFromSharers(addr);
    f_setOwnerToRequestor(addr);
    h_invToSharers(addr);
    g_clearSharers(addr);
    p_requestToDram(addr);
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_S, Directory_Event_UG_PREFETCH):
  {
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_SD, Directory_Event_DATA):
  case HASH_FUN(Directory_State_SPD, Directory_Event_DATA):
  {
    next_state = Directory_State_S;
    if (!(*(m_chip_ptr->m_Directory_responseFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    bb_dataToRequestor(addr);
    j_popDramResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_SPD, Directory_Event_DATA_P):
  {
    next_state = Directory_State_S;
    if (!(*(m_chip_ptr->m_Directory_prefResponseFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    jjb_dataToRequestor(addr);
    jp_popDramResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_SD, Directory_Event_PREFS):
  case HASH_FUN(Directory_State_MD, Directory_Event_PREFS):
  {
    jjj_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_SPD, Directory_Event_UG_PREFETCH):
  {
    uu_profile(addr);
    jp_ugPrefToDram(addr);
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_MD, Directory_Event_DATA):
  case HASH_FUN(Directory_State_MPD, Directory_Event_DATA):
  {
    next_state = Directory_State_M;
    if (!(*(m_chip_ptr->m_Directory_responseFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    bb_dataToRequestor(addr);
    j_popDramResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_O, Directory_Event_GETS):
  case HASH_FUN(Directory_State_O, Directory_Event_GET_INSTR):
  {
    next_state = Directory_State_OO;
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profile(addr);
    a_addRequestorToSharers(addr);
    d_forwardRequestToOwner(addr);
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_O, Directory_Event_PREFS):
  {
    next_state = Directory_State_OO;
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    jjuu_profile(addr);
    jja_addRequestorToSharers(addr);
    jjd_forwardRequestToOwner(addr);
    jjj_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_O, Directory_Event_PREFX):
  {
    next_state = Directory_State_OM;
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(2)) {
      return TransitionResult_ResourceStall;
    }
    jjuu_profile(addr);
    jju_removeRequestorFromSharers(addr);
    jjt_removeOwnerFromSharers(addr);
    jjd_forwardRequestToOwner(addr);
    jjf_setOwnerToRequestor(addr);
    jjh_invToSharers(addr);
    jjg_clearSharers(addr);
    jjj_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_O, Directory_Event_GETX_NotOwner):
  case HASH_FUN(Directory_State_O, Directory_Event_GETX_Owner):
  {
    next_state = Directory_State_OM;
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(2)) {
      return TransitionResult_ResourceStall;
    }
    uu_profile(addr);
    u_removeRequestorFromSharers(addr);
    t_removeOwnerFromSharers(addr);
    d_forwardRequestToOwner(addr);
    f_setOwnerToRequestor(addr);
    h_invToSharers(addr);
    g_clearSharers(addr);
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_O, Directory_Event_PUTX_Owner):
  {
    next_state = Directory_State_S;
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profile(addr);
    u_removeRequestorFromSharers(addr);
    l_writeRequestDataToMemory(addr);
    n_writebackAckToRequestor(addr);
    p_clearOwner(addr);
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_M, Directory_Event_GETS):
  case HASH_FUN(Directory_State_M, Directory_Event_GET_INSTR):
  {
    next_state = Directory_State_MO;
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profile(addr);
    a_addRequestorToSharers(addr);
    r_addOwnerToSharers(addr);
    d_forwardRequestToOwner(addr);
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_M, Directory_Event_PREFS):
  {
    next_state = Directory_State_MO;
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    jjuu_profile(addr);
    jja_addRequestorToSharers(addr);
    jjr_addOwnerToSharers(addr);
    jjd_forwardRequestToOwner(addr);
    jjj_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_M, Directory_Event_PREFX):
  {
    next_state = Directory_State_MM;
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    jjuu_profile(addr);
    jjd_forwardRequestToOwner(addr);
    jjf_setOwnerToRequestor(addr);
    jjj_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_M, Directory_Event_GETX_NotOwner):
  {
    next_state = Directory_State_MM;
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profile(addr);
    d_forwardRequestToOwner(addr);
    f_setOwnerToRequestor(addr);
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_M, Directory_Event_GETX_Owner):
  {
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profile(addr);
    m_forwardExclusiveRequestToOwner(addr);
    j_popIncomingRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(Directory_State_M, Directory_Event_PUTX_Owner):
  {
    next_state = Directory_State_I;
    if (!(*(m_chip_ptr->m_Directory_forwardedRequestFromDir_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profile(addr);
    l_writeRequestDataToMemory(addr);
    n_writebackAckToRequestor(addr);
    p_clearOwner(addr);
    j_popIncomingRequestQueue(addr);
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
