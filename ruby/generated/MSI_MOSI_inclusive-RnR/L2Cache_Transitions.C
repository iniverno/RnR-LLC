// Auto generated C++ code started by symbols/StateMachine.C:473
// L2Cache: MOSI Directory L2 Cache CMP

#include "Global.h"
#include "L2Cache_Controller.h"
#include "L2Cache_State.h"
#include "L2Cache_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

#define HASH_FUN(state, event)  ((int(state)*L2Cache_Event_NUM)+int(event))

#define GET_TRANSITION_COMMENT() (L2Cache_transitionComment.str())
#define CLEAR_TRANSITION_COMMENT() (L2Cache_transitionComment.str(""))

TransitionResult L2Cache_Controller::doTransition(L2Cache_Event event, L2Cache_State state, const Address& addr
)
{
  L2Cache_State next_state = state;

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
      g_system_ptr->getProfiler()->profileTransition("L2Cache", m_chip_ptr->getID(), m_version, addr, 
        L2Cache_State_to_string(state), 
        L2Cache_Event_to_string(event), 
        L2Cache_State_to_string(next_state), GET_TRANSITION_COMMENT());
    }
    CLEAR_TRANSITION_COMMENT();
    L2Cache_setState(addr, next_state);
    
  } else if (result == TransitionResult_ResourceStall) {
    if (PROTOCOL_DEBUG_TRACE) {
      g_system_ptr->getProfiler()->profileTransition("L2Cache", m_chip_ptr->getID(), m_version, addr, 
        L2Cache_State_to_string(state), 
        L2Cache_Event_to_string(event), 
        L2Cache_State_to_string(next_state), 
        "Resource Stall");
    }
  } else if (result == TransitionResult_ProtocolStall) {
    DEBUG_MSG(GENERATED_COMP,HighPrio,"stalling");
    DEBUG_NEWLINE(GENERATED_COMP, MedPrio);
    if (PROTOCOL_DEBUG_TRACE) {
      g_system_ptr->getProfiler()->profileTransition("L2Cache", m_chip_ptr->getID(), m_version, addr, 
        L2Cache_State_to_string(state), 
        L2Cache_Event_to_string(event), 
        L2Cache_State_to_string(next_state), 
        "Protocol Stall");
    }
  }
  return result;
}

TransitionResult L2Cache_Controller::doTransitionWorker(L2Cache_Event event, L2Cache_State state, L2Cache_State& next_state, const Address& addr
)
{

  switch(HASH_FUN(state, event)) {
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_IPS, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_IPS, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_IPS, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_IPS, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_IPS, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_IPS, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_IPS, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_IPS, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_IPS, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_IPS, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_IPX, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_IPX, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_IPX, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_IPX, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_IPX, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_IPX, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_IPX, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_IPX, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_IPX, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_IPX, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_IPXZ, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_IPXZ, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_IPXZ, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_IPXZ, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_IPXZ, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_IPXZ, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_IPXZ, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_IPXZ, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_IPXZ, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_IPXZ, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_ISZ, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_ISZ, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_ISZ, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_ISZ, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_ISZ, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_ISZ, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_ISZ, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_ISZ, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_ISZ, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_ISZ, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_MIN, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_MIN, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_MIN, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_MIN, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_MIN, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_MIN, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_MIN, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_MIN, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_MIN, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_MIN, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_PMIN, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_PMIN, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_PMIN, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_PMIN, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_PMIN, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_PMIN, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_PMIN, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_PMIN, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_PMIN, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_PMIN, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_INRSI, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_INRSI, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_INRSI, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_INRSI, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_INRSI, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_INRSI, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_INRSI, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_INRSI, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_INRSI, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_INRSI, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_INRMZ, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_INRMZ, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_INRMZ, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_INRMZ, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_INRMZ, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_INRMZ, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_INRMZ, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_INRMZ, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_INRMZ, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_INRMZ, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_L1_PUTX_last):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_Forwarded_GETS):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_Forwarded_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_Forwarded_GETX):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_Forwarded_PREFS):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_Forwarded_PREFX):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_Forwarded_GETS):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_Forwarded_PREFS):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_Forwarded_PREFX):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_Forwarded_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_Forwarded_GETX):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_Forwarded_GETS):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_Forwarded_PREFS):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_Forwarded_PREFX):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_Forwarded_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_Forwarded_GETX):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_Forwarded_GETS):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_Forwarded_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_Forwarded_PREFS):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_Forwarded_PREFX):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_Forwarded_GETX):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_Forwarded_GETS):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_Forwarded_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_Forwarded_GETX):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_Forwarded_PREFS):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_Forwarded_PREFX):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L2_INV):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L2_INV):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_MIN, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_MIN, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_MIN, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_PMIN, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_PMIN, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_PMIN, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_Forwarded_PREFX):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_Forwarded_GETS):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_Forwarded_PREFS):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_Forwarded_PREFX):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_Forwarded_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_Forwarded_GETX):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_Forwarded_GETS):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_Forwarded_PREFS):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_Forwarded_PREFX):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_Forwarded_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_Forwarded_GETX):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_OIN, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_POIN, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_OM, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_Forwarded_GETS):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_Forwarded_PREFS):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_Forwarded_PREFX):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_Forwarded_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_Forwarded_GETX):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_L1_GETX):
  {
    return TransitionResult_ProtocolStall;
  }
  case HASH_FUN(L2Cache_State_L2_NP, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_NP, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_I, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_I, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_S, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_S, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_SS, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_SS, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_M, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_M, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_MT, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_MT, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_O, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_O, L2Cache_Event_L1_PUTS_old):
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L1_PUTX_old):
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L1_PUTS_old):
  {
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    w_sendPutAckToL1Cache(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NP, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_NP, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_NP, L2Cache_Event_L2_PrefetchX_Replacement):
  case HASH_FUN(L2Cache_State_L2_I, L2Cache_Event_L2_Replacement):
  case HASH_FUN(L2Cache_State_L2_I, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_I, L2Cache_Event_L2_PrefetchX_Replacement):
  {
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NP, L2Cache_Event_L2_INV):
  case HASH_FUN(L2Cache_State_L2_I, L2Cache_Event_L2_INV):
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_L2_INV):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_L2_INV):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_L2_INV):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_L2_INV):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_L2_INV):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_L2_INV):
  {
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    t_sendAckToInvalidator(addr);
    l_popForwardedRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NP, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_NP, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_I, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_I, L2Cache_Event_L1_GET_INSTR):
  {
    next_state = L2Cache_State_L2_INRS;
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jjj_statsPrefetchLocal3(addr);
    qq_allocateL2CacheBlock(addr);
    jjpc_savePC(addr);
    jjit_initialTouch(addr);
    ll_clearSharers(addr);
    nn_addSharer(addr);
    i_allocateTBE(addr);
    ss_recordGetSL1ID(addr);
    a_issueGETS(addr);
    jaa_missToPrefetch(addr);
    uu_profileMiss(addr);
    jjpc_savePC(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NP, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_NP, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_NP, L2Cache_Event_L1_UPGRADE_no_others):
  case HASH_FUN(L2Cache_State_L2_I, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_I, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_I, L2Cache_Event_L1_UPGRADE_no_others):
  {
    next_state = L2Cache_State_L2_INRM;
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    qq_allocateL2CacheBlock(addr);
    jjpc_savePC(addr);
    jjit_initialTouch(addr);
    ll_clearSharers(addr);
    nn_addSharer(addr);
    i_allocateTBE(addr);
    xx_recordGetXL1ID(addr);
    b_issueGETX(addr);
    jaa_missToPrefetch(addr);
    jjj_statsPrefetchLocal3(addr);
    uu_profileMiss(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_L2_INV):
  {
    next_state = L2Cache_State_L2_ISI;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    t_sendAckToInvalidator(addr);
    l_popForwardedRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_Data_ext_ack_0):
  {
    next_state = L2Cache_State_L2_SS;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    u_writeDataFromResponseQueueToL2Cache(addr);
    h_issueLoadHit(addr);
    s_deallocateTBE(addr);
    jjj_popResponeDramQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_L1_GET_INSTR):
  {
    ww_profileMissNoDir(addr);
    set_setMRU(addr);
    nn_addSharer(addr);
    setTimeLast(addr);
    ss_recordGetSL1ID(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IS, L2Cache_Event_L1_GETX):
  {
    next_state = L2Cache_State_L2_ISZ;
    return TransitionResult_ProtocolStall;
  }
  case HASH_FUN(L2Cache_State_L2_ISI, L2Cache_Event_Data_ext_ack_0):
  {
    next_state = L2Cache_State_L2_I;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    u_writeDataFromResponseQueueToL2Cache(addr);
    oo_issueLoadHitInv(addr);
    s_deallocateTBE(addr);
    jjj_popResponeDramQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_L2_INV):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_L2_INV):
  {
    yy_recordInvalidatorID(addr);
    l_popForwardedRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_Data_ext_ack_0):
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_Data_ext_ack_not_0_last):
  {
    next_state = L2Cache_State_L2_MV;
    u_writeDataFromResponseQueueToL2Cache(addr);
    jjj_popResponeDramQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_Data_ext_ack_not_0):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_Data_ext_ack_not_0):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_Data_ext_ack_not_0):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_Data_ext_ack_not_0):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_Data_ext_ack_not_0):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_Data_ext_ack_not_0):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_Data_ext_ack_not_0):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_Data_ext_ack_not_0):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_Data_ext_ack_not_0):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_Data_ext_ack_not_0):
  case HASH_FUN(L2Cache_State_L2_INRMZ, L2Cache_Event_Data_ext_ack_not_0):
  {
    u_writeDataFromResponseQueueToL2Cache(addr);
    p_addNumberOfPendingExtAcks(addr);
    mm_rememberIfFinalAckNeeded(addr);
    jjj_popResponeDramQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_Proc_int_ack):
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_Proc_int_ack):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_Proc_int_ack):
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_Proc_int_ack):
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_Proc_int_ack):
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_Proc_int_ack):
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_Proc_int_ack):
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_Proc_int_ack):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_Proc_int_ack):
  {
    aa_removeResponseSharer(addr);
    r_decrementNumberOfPendingIntAcks(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IMV, L2Cache_Event_Proc_last_int_ack):
  {
    next_state = L2Cache_State_L2_IM;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    aa_removeResponseSharer(addr);
    r_decrementNumberOfPendingIntAcks(addr);
    o_popIncomingResponseQueue(addr);
    zz_sendAckToQueuedInvalidator(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MV, L2Cache_Event_Proc_last_int_ack):
  case HASH_FUN(L2Cache_State_L2_OMV, L2Cache_Event_Proc_last_int_ack):
  {
    next_state = L2Cache_State_L2_MT;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    aa_removeResponseSharer(addr);
    r_decrementNumberOfPendingIntAcks(addr);
    hh_issueStoreHit(addr);
    s_deallocateTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_Forwarded_GETS):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_Forwarded_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_Forwarded_PREFS):
  {
    next_state = L2Cache_State_L2_IMO;
    dd_recordGetSForwardID(addr);
    l_popForwardedRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_L1_GET_INSTR):
  {
    next_state = L2Cache_State_L2_IMO;
    ww_profileMissNoDir(addr);
    set_setMRU(addr);
    nn_addSharer(addr);
    setTimeLast(addr);
    ss_recordGetSL1ID(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_Forwarded_GETX):
  {
    next_state = L2Cache_State_L2_IMI;
    ii_recordGetXForwardID(addr);
    l_popForwardedRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_Forwarded_PREFX):
  {
    next_state = L2Cache_State_L2_IMZ;
    return TransitionResult_ProtocolStall;
  }
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_Data_ext_ack_0):
  case HASH_FUN(L2Cache_State_L2_IM, L2Cache_Event_Data_ext_ack_not_0_last):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_Data_ext_ack_0):
  case HASH_FUN(L2Cache_State_L2_IMZ, L2Cache_Event_Data_ext_ack_not_0_last):
  {
    next_state = L2Cache_State_L2_MT;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    u_writeDataFromResponseQueueToL2Cache(addr);
    hh_issueStoreHit(addr);
    s_deallocateTBE(addr);
    jjj_popResponeDramQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_Forwarded_GETS):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_Forwarded_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_Forwarded_PREFS):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_Forwarded_GETS):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_Forwarded_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_Forwarded_PREFS):
  {
    dd_recordGetSForwardID(addr);
    l_popForwardedRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_Forwarded_GETX):
  {
    next_state = L2Cache_State_L2_IMOI;
    ii_recordGetXForwardID(addr);
    l_popForwardedRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_Forwarded_PREFX):
  {
    next_state = L2Cache_State_L2_IMOI;
    return TransitionResult_ProtocolStall;
  }
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_L1_GETX):
  {
    next_state = L2Cache_State_L2_IMOZ;
    return TransitionResult_ProtocolStall;
  }
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_Data_ext_ack_0):
  case HASH_FUN(L2Cache_State_L2_IMO, L2Cache_Event_Data_ext_ack_not_0_last):
  {
    next_state = L2Cache_State_L2_MO;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    u_writeDataFromResponseQueueToL2Cache(addr);
    cc_issueStoreHitDG(addr);
    ddd_setPendingIntAcksToOne(addr);
    jjj_popResponeDramQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_Data_ext_ack_0):
  case HASH_FUN(L2Cache_State_L2_IMI, L2Cache_Event_Data_ext_ack_not_0_last):
  {
    next_state = L2Cache_State_L2_MIC;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    u_writeDataFromResponseQueueToL2Cache(addr);
    pp_issueStoreHitInv(addr);
    ddd_setPendingIntAcksToOne(addr);
    jjj_popResponeDramQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_Data_ext_ack_0):
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_Data_ext_ack_not_0_last):
  {
    next_state = L2Cache_State_L2_MOICR;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    u_writeDataFromResponseQueueToL2Cache(addr);
    pp_issueStoreHitInv(addr);
    ddd_setPendingIntAcksToOne(addr);
    jjj_popResponeDramQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IMOI, L2Cache_Event_PrefetchS):
  {
    jjj_popPrefetchQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_Data_ext_ack_0):
  case HASH_FUN(L2Cache_State_L2_IMOZ, L2Cache_Event_Data_ext_ack_not_0_last):
  {
    next_state = L2Cache_State_L2_MOZ;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    u_writeDataFromResponseQueueToL2Cache(addr);
    cc_issueStoreHitDG(addr);
    ddd_setPendingIntAcksToOne(addr);
    jjj_popResponeDramQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_S, L2Cache_Event_L2_Replacement):
  {
    next_state = L2Cache_State_L2_I;
    jjj_statsPrefetchLocal2(addr);
    jjj_statsPrefetchLocalS2(addr);
    ji_marcaRepl(addr);
    fjj_removeDataArray(addr);
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_S, L2Cache_Event_L2_PrefetchS_Replacement):
  {
    next_state = L2Cache_State_L2_I;
    jjj_statsPrefetchLocal2(addr);
    jjj_statsPrefetchLocalS2(addr);
    jis_marcaRepl(addr);
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_S, L2Cache_Event_L2_PrefetchX_Replacement):
  {
    next_state = L2Cache_State_L2_I;
    jjj_statsPrefetchLocal2(addr);
    jjj_statsPrefetchLocalS2(addr);
    jix_marcaRepl(addr);
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_S, L2Cache_Event_L2_INV):
  {
    next_state = L2Cache_State_L2_I;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    jjj_checkDWG(addr);
    t_sendAckToInvalidator(addr);
    l_popForwardedRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_S, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_S, L2Cache_Event_L1_GET_INSTR):
  {
    next_state = L2Cache_State_L2_SS;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    jjj_statsPrefetchLocal(addr);
    jjj_statsPrefetchLocalS(addr);
    ww_profileMissNoDir(addr);
    set_setMRU(addr);
    nn_addSharer(addr);
    setTimeLast(addr);
    k_dataFromL2CacheToL1Requestor(addr);
    jab_firstUseToPrefetcherS(addr);
    jjj_hitOnPrefetchedWay0(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_S, L2Cache_Event_L1_GETX):
  {
    next_state = L2Cache_State_L2_MT;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    jjj_statsPrefetchLocal(addr);
    jjj_statsPrefetchLocalS(addr);
    set_setMRU(addr);
    nn_addSharer(addr);
    setTimeLast(addr);
    k_dataFromL2CacheToL1Requestor(addr);
    jab_firstUseToPrefetcherS(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_S, L2Cache_Event_Data_replacement):
  {
    next_state = L2Cache_State_L2_NRS;
    fl_popDataReplQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_Data_ext_ack_0):
  case HASH_FUN(L2Cache_State_L2_SM, L2Cache_Event_Data_ext_ack_not_0_last):
  {
    next_state = L2Cache_State_L2_M;
    u_writeDataFromResponseQueueToL2Cache(addr);
    s_deallocateTBE(addr);
    jjj_popResponeDramQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_Data_ext_ack_0):
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_Data_ext_ack_not_0_last):
  {
    next_state = L2Cache_State_L2_SSMV;
    u_writeDataFromResponseQueueToL2Cache(addr);
    jjj_popResponeDramQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SSM, L2Cache_Event_Proc_last_int_ack):
  {
    next_state = L2Cache_State_L2_SM;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    aa_removeResponseSharer(addr);
    r_decrementNumberOfPendingIntAcks(addr);
    o_popIncomingResponseQueue(addr);
    zz_sendAckToQueuedInvalidator(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SSMV, L2Cache_Event_Proc_last_int_ack):
  {
    next_state = L2Cache_State_L2_M;
    aa_removeResponseSharer(addr);
    r_decrementNumberOfPendingIntAcks(addr);
    s_deallocateTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SS, L2Cache_Event_L2_Replacement):
  {
    next_state = L2Cache_State_L2_SIV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    i_allocateTBE(addr);
    ji_marcaRepl(addr);
    fjj_removeDataArray(addr);
    bbb_setPendingIntAcksToSharers(addr);
    tt_issueSharedInvalidateIntL1copiesRequest(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SS, L2Cache_Event_L2_PrefetchS_Replacement):
  {
    next_state = L2Cache_State_L2_PSIV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    i_allocatePrefTBE(addr);
    jis_marcaRepl(addr);
    bbb_setPendingIntAcksToSharersPref(addr);
    tt_issueSharedInvalidatePIntL1copiesRequest(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SS, L2Cache_Event_L2_INV):
  {
    next_state = L2Cache_State_L2_SIC;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    i_allocateTBE(addr);
    yy_recordInvalidatorID(addr);
    bbb_setPendingIntAcksToSharersPref(addr);
    tt_issueSharedInvalidateIntL1copiesRequest(addr);
    l_popForwardedRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SS, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_SS, L2Cache_Event_L1_GET_INSTR):
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L1_GET_INSTR):
  {
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    ww_profileMissNoDir(addr);
    set_setMRU(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    k_dataFromL2CacheToL1Requestor(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SS, L2Cache_Event_L1_UPGRADE_no_others):
  {
    next_state = L2Cache_State_L2_MT;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    setTimeLast(addr);
    jsr_setReused(addr);
    set_setMRU(addr);
    k_dataFromL2CacheToL1Requestor(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SS, L2Cache_Event_L1_UPGRADE):
  {
    next_state = L2Cache_State_L2_MV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    setTimeLast(addr);
    jsr_setReused(addr);
    i_allocateTBE(addr);
    set_setMRU(addr);
    xx_recordGetXL1ID(addr);
    ccc_setPendingIntAcksMinusOne(addr);
    vv_issueInvalidateOtherIntL1copiesRequest(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SS, L2Cache_Event_L1_GETX):
  {
    next_state = L2Cache_State_L2_MV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    i_allocateTBE(addr);
    xx_recordGetXL1ID(addr);
    bbb_setPendingIntAcksToSharers(addr);
    vv_issueInvalidateOtherIntL1copiesRequest(addr);
    set_setMRU(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SS, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L1_PUTS):
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L1_PUTX):
  case HASH_FUN(L2Cache_State_L2_NRSS, L2Cache_Event_L1_PUTS):
  {
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    ww_profileMissNoDir(addr);
    w_sendPutAckToL1Cache(addr);
    kk_removeRequestSharer(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SS, L2Cache_Event_L1_PUTS_last):
  {
    next_state = L2Cache_State_L2_S;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    ww_profileMissNoDir(addr);
    w_sendPutAckToL1Cache(addr);
    kk_removeRequestSharer(addr);
    j_set_setMRU(addr);
    jjj_keepReuseL1(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SS, L2Cache_Event_Data_replacement):
  {
    next_state = L2Cache_State_L2_NRSS;
    fl_popDataReplQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_Proc_last_int_ack):
  {
    next_state = L2Cache_State_L2_I;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    aa_removeResponseSharer(addr);
    r_decrementNumberOfPendingIntAcks(addr);
    o_popIncomingResponseQueue(addr);
    zz_sendAckToQueuedInvalidator(addr);
    s_deallocateTBE(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SIC, L2Cache_Event_L2_INV):
  {
    l_popForwardedRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SIV, L2Cache_Event_Proc_last_int_ack):
  case HASH_FUN(L2Cache_State_L2_NRSIV, L2Cache_Event_Proc_last_int_ack):
  {
    next_state = L2Cache_State_L2_I;
    aa_removeResponseSharer(addr);
    r_decrementNumberOfPendingIntAcks(addr);
    jjj_keepReuseL1a(addr);
    o_popIncomingResponseQueue(addr);
    s_deallocateTBE(addr);
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_Proc_int_ack):
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_Proc_int_ack):
  {
    aa_removeResponseSharer(addr);
    r_decrementNumberOfPendingIntAcksPrefTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_PSIV, L2Cache_Event_Proc_last_int_ack):
  {
    next_state = L2Cache_State_L2_I;
    aa_removeResponseSharer(addr);
    r_decrementNumberOfPendingIntAcksPrefTBE(addr);
    o_popIncomingResponseQueue(addr);
    s_deallocatePrefTBE(addr);
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_M, L2Cache_Event_L2_Replacement):
  {
    next_state = L2Cache_State_L2_I;
    fjj_removeDataArray(addr);
    ji_marcaRepl(addr);
    d_issuePUTX(addr);
    jjj_statsPrefetchLocal7(addr);
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_M, L2Cache_Event_L2_PrefetchS_Replacement):
  case HASH_FUN(L2Cache_State_L2_O, L2Cache_Event_L2_PrefetchS_Replacement):
  {
    next_state = L2Cache_State_L2_I;
    jis_marcaRepl(addr);
    d_issuePUTX(addr);
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_M, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_M, L2Cache_Event_L1_GET_INSTR):
  {
    next_state = L2Cache_State_L2_SO;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    ww_profileMissNoDir(addr);
    set_setMRU(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    k_dataFromL2CacheToL1Requestor(addr);
    jjj_statsPrefetchLocal4(addr);
    jab_firstUseToPrefetcherX(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_M, L2Cache_Event_L1_GETX):
  {
    next_state = L2Cache_State_L2_MT;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    ww_profileMissNoDir(addr);
    set_setMRU(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    k_dataFromL2CacheToL1Requestor(addr);
    jjj_statsPrefetchLocal4(addr);
    jab_firstUseToPrefetcherX(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_M, L2Cache_Event_Data_replacement):
  case HASH_FUN(L2Cache_State_L2_O, L2Cache_Event_Data_replacement):
  {
    next_state = L2Cache_State_L2_NRS;
    d_issuePUTX(addr);
    fl_popDataReplQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MT, L2Cache_Event_L2_Replacement):
  {
    next_state = L2Cache_State_L2_MIV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    i_allocateTBE(addr);
    ji_marcaRepl(addr);
    fjj_removeDataArray(addr);
    bbb_setPendingIntAcksToSharers(addr);
    v_issueInvalidateIntL1copyRequest(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MT, L2Cache_Event_L2_PrefetchS_Replacement):
  {
    next_state = L2Cache_State_L2_PMIV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    i_allocatePrefTBE(addr);
    jis_marcaRepl(addr);
    bbb_setPendingIntAcksToSharersPref(addr);
    v_issueInvalidatePIntL1copyRequest(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MT, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_MT, L2Cache_Event_L1_GET_INSTR):
  {
    next_state = L2Cache_State_L2_MO;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    ww_profileMissNoDir(addr);
    i_allocateTBE(addr);
    bbb_setPendingIntAcksToSharers(addr);
    g_issueDownGradeIntL1copiesRequest(addr);
    ss_recordGetSL1ID(addr);
    set_setMRU(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MT, L2Cache_Event_L1_GETX):
  {
    next_state = L2Cache_State_L2_MIT;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    ww_profileMissNoDir(addr);
    i_allocateTBE(addr);
    bbb_setPendingIntAcksToSharers(addr);
    v_issueInvalidateIntL1copyRequest(addr);
    set_setMRU(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    xx_recordGetXL1ID(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MT, L2Cache_Event_L1_PUTX_last):
  {
    next_state = L2Cache_State_L2_M;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    ww_profileMissNoDir(addr);
    w_sendPutAckToL1Cache(addr);
    kk_removeRequestSharer(addr);
    m_writeDataFromRequestQueueToL2Cache(addr);
    j_set_setMRU(addr);
    setTimeLast(addr);
    jjj_keepReuseL1(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MT, L2Cache_Event_Data_replacement):
  {
    next_state = L2Cache_State_L2_NRMT;
    fl_popDataReplQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MIV, L2Cache_Event_Data_int_ack):
  case HASH_FUN(L2Cache_State_L2_NRMIV, L2Cache_Event_Data_int_ack):
  {
    next_state = L2Cache_State_L2_I;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(2)) {
      return TransitionResult_ResourceStall;
    }
    aa_removeResponseSharer(addr);
    jm_writeDataFromResponseQueueToL2Cache(addr);
    bb_dataFromL2CacheToGetSForwardIDs(addr);
    gg_dataFromL2CacheToGetXForwardID(addr);
    d_issuePUTX(addr);
    x_copyDataFromL2CacheToTBE(addr);
    jjj_keepReuseL1a(addr);
    rr_deallocateL2CacheBlock(addr);
    s_deallocateTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_PMIV, L2Cache_Event_Data_int_ack):
  {
    next_state = L2Cache_State_L2_I;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(2)) {
      return TransitionResult_ResourceStall;
    }
    aa_removeResponseSharer(addr);
    jm_writeDataFromResponseQueueToL2Cache(addr);
    bb_dataFromL2CacheToGetSForwardIDsPref(addr);
    gg_dataFromL2CacheToGetXForwardIDPref(addr);
    d_issuePUTX(addr);
    x_copyDataFromL2CacheToPrefTBE(addr);
    rr_deallocateL2CacheBlock(addr);
    jj_deactiveBloom(addr);
    s_deallocatePrefTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MIC, L2Cache_Event_Data_int_ack):
  {
    next_state = L2Cache_State_L2_I;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    aa_removeResponseSharer(addr);
    jm_writeDataFromResponseQueueToL2Cache(addr);
    gg_dataFromL2CacheToGetXForwardID(addr);
    s_deallocateTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MIT, L2Cache_Event_Data_int_ack):
  {
    next_state = L2Cache_State_L2_MT;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    aa_removeResponseSharer(addr);
    jm_writeDataFromResponseQueueToL2Cache(addr);
    hh_issueStoreHit(addr);
    s_deallocateTBE(addr);
    jjj_keepReuseL1a(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_Data_int_ack):
  case HASH_FUN(L2Cache_State_L2_MOZ, L2Cache_Event_Data_int_ack):
  {
    next_state = L2Cache_State_L2_SO;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(2)) {
      return TransitionResult_ResourceStall;
    }
    jm_writeDataFromResponseQueueToL2Cache(addr);
    ee_dataFromL2CacheToGetSIDs(addr);
    s_deallocateTBE(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L1_GET_INSTR):
  {
    jsr_setReused(addr);
    ww_profileMissNoDir(addr);
    set_setMRU(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    ss_recordGetSL1ID(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L1_GETX):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L1_UPGRADE):
  case HASH_FUN(L2Cache_State_L2_MO, L2Cache_Event_L1_UPGRADE_no_others):
  {
    next_state = L2Cache_State_L2_MOZ;
    return TransitionResult_ProtocolStall;
  }
  case HASH_FUN(L2Cache_State_L2_MOIC, L2Cache_Event_Data_int_ack):
  {
    next_state = L2Cache_State_L2_OIC;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(2)) {
      return TransitionResult_ResourceStall;
    }
    jm_writeDataFromResponseQueueToL2Cache(addr);
    ee_dataFromL2CacheToGetSIDs(addr);
    bbb_setPendingIntAcksToSharers(addr);
    tt_issueSharedInvalidateIntL1copiesRequest(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_MOICR, L2Cache_Event_Data_int_ack):
  {
    next_state = L2Cache_State_L2_OIC;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(2)) {
      return TransitionResult_ResourceStall;
    }
    aa_removeResponseSharer(addr);
    jm_writeDataFromResponseQueueToL2Cache(addr);
    ee_dataFromL2CacheToGetSIDs(addr);
    bbb_setPendingIntAcksToSharers(addr);
    tt_issueSharedInvalidateIntL1copiesRequest(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_O, L2Cache_Event_L2_Replacement):
  {
    next_state = L2Cache_State_L2_I;
    ji_marcaRepl(addr);
    fjj_removeDataArray(addr);
    d_issuePUTX(addr);
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_O, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_O, L2Cache_Event_L1_GET_INSTR):
  {
    next_state = L2Cache_State_L2_SO;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    ww_profileMissNoDir(addr);
    set_setMRU(addr);
    nn_addSharer(addr);
    setTimeLast(addr);
    k_dataFromL2CacheToL1Requestor(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_O, L2Cache_Event_L1_GETX):
  {
    next_state = L2Cache_State_L2_MT;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    set_setMRU(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    k_dataFromL2CacheToL1Requestor(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L2_Replacement):
  {
    next_state = L2Cache_State_L2_OIV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    i_allocateTBE(addr);
    ji_marcaRepl(addr);
    fjj_removeDataArray(addr);
    x_copyDataFromL2CacheToTBE(addr);
    bbb_setPendingIntAcksToSharers(addr);
    tt_issueSharedInvalidateIntL1copiesRequest(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L2_PrefetchS_Replacement):
  {
    next_state = L2Cache_State_L2_POIV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    i_allocatePrefTBE(addr);
    jis_marcaRepl(addr);
    x_copyDataFromL2CacheToPrefTBE(addr);
    bbb_setPendingIntAcksToSharersPref(addr);
    tt_issueSharedInvalidatePIntL1copiesRequest(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L2_PrefetchX_Replacement):
  {
    next_state = L2Cache_State_L2_POIV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    i_allocatePrefTBE(addr);
    jix_marcaRepl(addr);
    x_copyDataFromL2CacheToPrefTBE(addr);
    bbb_setPendingIntAcksToSharersPref(addr);
    tt_issueSharedInvalidatePIntL1copiesRequest(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L1_UPGRADE):
  {
    next_state = L2Cache_State_L2_OMV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    set_setMRU(addr);
    nn_addSharer(addr);
    setTimeLast(addr);
    i_allocateTBE(addr);
    xx_recordGetXL1ID(addr);
    ccc_setPendingIntAcksMinusOne(addr);
    vv_issueInvalidateOtherIntL1copiesRequest(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L1_UPGRADE_no_others):
  {
    next_state = L2Cache_State_L2_MT;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    jsr_setReused(addr);
    uu_profileAccess(addr);
    set_setMRU(addr);
    setTimeLast(addr);
    k_dataFromL2CacheToL1Requestor(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L1_GETX):
  {
    next_state = L2Cache_State_L2_OMV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    i_allocateTBE(addr);
    xx_recordGetXL1ID(addr);
    bbb_setPendingIntAcksToSharers(addr);
    vv_issueInvalidateOtherIntL1copiesRequest(addr);
    set_setMRU(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L1_PUTS_last):
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_L1_PUTX_last):
  {
    next_state = L2Cache_State_L2_O;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    ww_profileMissNoDir(addr);
    w_sendPutAckToL1Cache(addr);
    kk_removeRequestSharer(addr);
    j_set_setMRU(addr);
    jjj_keepReuseL1(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_SO, L2Cache_Event_Data_replacement):
  {
    fjjb_insertionDataArrayFromRepl(addr);
    fl_popDataReplQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_OIV, L2Cache_Event_Proc_last_int_ack):
  {
    next_state = L2Cache_State_L2_I;
    aa_removeResponseSharer(addr);
    r_decrementNumberOfPendingIntAcks(addr);
    jjj_keepReuseL1a(addr);
    o_popIncomingResponseQueue(addr);
    d_issuePUTX(addr);
    s_deallocateTBE(addr);
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_POIV, L2Cache_Event_Proc_last_int_ack):
  {
    next_state = L2Cache_State_L2_POIN;
    aa_removeResponseSharer(addr);
    r_decrementNumberOfPendingIntAcksPrefTBE(addr);
    o_popIncomingResponseQueue(addr);
    d_issuePUTX(addr);
    s_deallocatePrefTBE(addr);
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_OIC, L2Cache_Event_Proc_last_int_ack):
  {
    next_state = L2Cache_State_L2_I;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    aa_removeResponseSharer(addr);
    r_decrementNumberOfPendingIntAcks(addr);
    gg_dataFromL2CacheToGetXForwardID(addr);
    s_deallocateTBE(addr);
    jjj_keepReuseL1a(addr);
    o_popIncomingResponseQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRSS, L2Cache_Event_L2_Replacement):
  {
    next_state = L2Cache_State_L2_NRSIV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    i_allocateTBE(addr);
    ji_marcaRepl(addr);
    bbb_setPendingIntAcksToSharers(addr);
    tt_issueSharedInvalidateIntL1copiesRequest(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRSS, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_NRSS, L2Cache_Event_L1_GET_INSTR):
  {
    next_state = L2Cache_State_L2_SS;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    k_dataFromL2CacheToL1Requestor(addr);
    jsr_setReused(addr);
    fjj_insertionDataArray(addr);
    ww_profileMissNoDir(addr);
    set_setMRU(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRSS, L2Cache_Event_L1_UPGRADE_no_others):
  {
    next_state = L2Cache_State_L2_NRMT;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    setTimeLast(addr);
    jsr_setReused(addr);
    set_setMRU(addr);
    k_dataFromL2CacheToL1Requestor(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRSS, L2Cache_Event_L1_GETX):
  {
    next_state = L2Cache_State_L2_MV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    i_allocateTBE(addr);
    xx_recordGetXL1ID(addr);
    bbb_setPendingIntAcksToSharers(addr);
    vv_issueInvalidateOtherIntL1copiesRequest(addr);
    set_setMRU(addr);
    fjj_insertionDataArray(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRSS, L2Cache_Event_L1_UPGRADE):
  {
    next_state = L2Cache_State_L2_MV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    i_allocateTBE(addr);
    xx_recordGetXL1ID(addr);
    ccc_setPendingIntAcksMinusOne(addr);
    vv_issueInvalidateOtherIntL1copiesRequest(addr);
    set_setMRU(addr);
    fjj_insertionDataArray(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRSS, L2Cache_Event_L1_PUTS_last):
  {
    next_state = L2Cache_State_L2_NRS;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    ww_profileMissNoDir(addr);
    w_sendPutAckToL1Cache(addr);
    kk_removeRequestSharer(addr);
    j_set_setMRU(addr);
    jjj_keepReuseL1(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRS, L2Cache_Event_L2_Replacement):
  {
    next_state = L2Cache_State_L2_I;
    jjj_statsPrefetchLocal2(addr);
    jjj_statsPrefetchLocalS2(addr);
    ji_marcaRepl(addr);
    rr_deallocateL2CacheBlock(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRS, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_NRS, L2Cache_Event_L1_GET_INSTR):
  {
    next_state = L2Cache_State_L2_IS;
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    i_allocateTBE(addr);
    a_issueGETS(addr);
    ss_recordGetSL1ID(addr);
    jsr_setReused(addr);
    fjj_insertionDataArray(addr);
    jjj_statsPrefetchLocal(addr);
    jjj_statsPrefetchLocalS(addr);
    ww_profileMissNoDir(addr);
    set_setMRU(addr);
    nn_addSharer(addr);
    setTimeLast(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRS, L2Cache_Event_L1_GETX):
  {
    next_state = L2Cache_State_L2_IM;
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    jjj_statsPrefetchLocal(addr);
    jjj_statsPrefetchLocalS(addr);
    set_setMRU(addr);
    fjj_insertionDataArray(addr);
    nn_addSharer(addr);
    setTimeLast(addr);
    i_allocateTBE(addr);
    xx_recordGetXL1ID(addr);
    b_issueGETX(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_INRS, L2Cache_Event_L2_INV):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_L2_INV):
  {
    next_state = L2Cache_State_L2_INRSI;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    t_sendAckToInvalidator(addr);
    l_popForwardedRequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_INRS, L2Cache_Event_Data_ext_ack_0):
  case HASH_FUN(L2Cache_State_L2_INRSZ, L2Cache_Event_Data_ext_ack_0):
  {
    next_state = L2Cache_State_L2_NRSS;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    h_issueLoadHit(addr);
    s_deallocateTBE(addr);
    jjj_popResponeDramQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_INRS, L2Cache_Event_L1_GETX):
  {
    next_state = L2Cache_State_L2_INRSZ;
    return TransitionResult_ProtocolStall;
  }
  case HASH_FUN(L2Cache_State_L2_INRS, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_INRS, L2Cache_Event_L1_GET_INSTR):
  {
    next_state = L2Cache_State_L2_IS;
    ww_profileMissNoDir(addr);
    set_setMRU(addr);
    nn_addSharer(addr);
    setTimeLast(addr);
    ss_recordGetSL1ID(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_L1_GETX):
  {
    next_state = L2Cache_State_L2_INRMZ;
    return TransitionResult_ProtocolStall;
  }
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_Data_ext_ack_0):
  case HASH_FUN(L2Cache_State_L2_INRM, L2Cache_Event_Data_ext_ack_not_0_last):
  case HASH_FUN(L2Cache_State_L2_INRMZ, L2Cache_Event_Data_ext_ack_0):
  case HASH_FUN(L2Cache_State_L2_INRMZ, L2Cache_Event_Data_ext_ack_not_0_last):
  {
    next_state = L2Cache_State_L2_NRMT;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    u_writeDataFromResponseQueueToL2Cache(addr);
    hh_issueStoreHit(addr);
    s_deallocateTBE(addr);
    jjj_popResponeDramQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRMT, L2Cache_Event_L2_Replacement):
  {
    next_state = L2Cache_State_L2_NRMIV;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    i_allocateTBE(addr);
    ji_marcaRepl(addr);
    bbb_setPendingIntAcksToSharers(addr);
    v_issueInvalidateIntL1copyRequest(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRMT, L2Cache_Event_L1_GETS):
  case HASH_FUN(L2Cache_State_L2_NRMT, L2Cache_Event_L1_GET_INSTR):
  {
    next_state = L2Cache_State_L2_MO;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    ww_profileMissNoDir(addr);
    i_allocateTBE(addr);
    bbb_setPendingIntAcksToSharers(addr);
    g_issueDownGradeIntL1copiesRequest(addr);
    ss_recordGetSL1ID(addr);
    set_setMRU(addr);
    fjj_insertionDataArray(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRMT, L2Cache_Event_L1_GETX):
  {
    next_state = L2Cache_State_L2_MIT;
    if (!(*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    if (!(*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    uu_profileAccess(addr);
    jsr_setReused(addr);
    ww_profileMissNoDir(addr);
    i_allocateTBE(addr);
    bbb_setPendingIntAcksToSharers(addr);
    v_issueInvalidateIntL1copyRequest(addr);
    set_setMRU(addr);
    fjj_insertionDataArray(addr);
    setTimeLast(addr);
    nn_addSharer(addr);
    xx_recordGetXL1ID(addr);
    jj_popL1RequestQueue2(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRMT, L2Cache_Event_L1_PUTX_last):
  {
    next_state = L2Cache_State_L2_NRS;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    w_sendPutAckToL1Cache(addr);
    kk_removeRequestSharer(addr);
    m_writeDataFromRequestQueueToL2Cache(addr);
    d_issuePUTX(addr);
    jj_popL1RequestQueue(addr);
    return TransitionResult_Valid;
  }
  case HASH_FUN(L2Cache_State_L2_NRMIT, L2Cache_Event_Data_int_ack):
  {
    next_state = L2Cache_State_L2_NRMT;
    if (!(*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version])).areNSlotsAvailable(1)) {
      return TransitionResult_ResourceStall;
    }
    aa_removeResponseSharer(addr);
    jm_writeDataFromResponseQueueToL2Cache(addr);
    hh_issueStoreHit(addr);
    s_deallocateTBE(addr);
    jjj_keepReuseL1a(addr);
    o_popIncomingResponseQueue(addr);
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
