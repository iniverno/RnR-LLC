/** \file L2Cache.C
  * 
  * Auto generated C++ code started by symbols/StateMachine.C:327
  * Created by slicc definition of Module "MOSI Directory L2 Cache CMP"
  */

#include "Global.h"
#include "RubySlicc_includes.h"
#include "L2Cache_Controller.h"
#include "L2Cache_State.h"
#include "L2Cache_Event.h"
#include "Types.h"
#include "System.h"
#include "Chip.h"

stringstream L2Cache_transitionComment;
#define APPEND_TRANSITION_COMMENT(str) (L2Cache_transitionComment << str)
/** \brief static profiler defn */
L2Cache_Profiler L2Cache_Controller::s_profiler;

/** \brief constructor */
L2Cache_Controller::L2Cache_Controller(Chip* chip_ptr, int version)
{
  m_chip_ptr = chip_ptr;
  m_id = m_chip_ptr->getID();
  m_version = version;
  m_machineID.type = MachineType_L2Cache;
  m_machineID.num = m_id*RubyConfig::numberOfL2CachePerChip()+m_version;
  (*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L2Cache_dataArrayReplQueue_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L2Cache_responseToL2CacheQueue_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L2Cache_prefResponseToL2CacheQueue_vec[m_version])).setConsumer(this);
  (*(m_chip_ptr->m_L2Cache_prefetchQueue_vec[m_version])).setConsumer(this);

  (*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", L2Cache, responseIntraChipL2Network_in]");
  (*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", L2Cache, forwardedRequestIntraChipL2Network_in]");
  (*(m_chip_ptr->m_L2Cache_dataArrayReplQueue_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", L2Cache, dataArrayReplQueueNetwork_in]");
  (*(m_chip_ptr->m_L2Cache_responseToL2CacheQueue_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", L2Cache, responseDram_in]");
  (*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", L2Cache, L1RequestIntraChipL2Network_in]");
  (*(m_chip_ptr->m_L2Cache_prefResponseToL2CacheQueue_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", L2Cache, prefResponseDram_in]");
  (*(m_chip_ptr->m_L2Cache_prefetchQueue_vec[m_version])).setDescription("[Chip " + int_to_string(m_chip_ptr->getID()) + " " + int_to_string(m_version) + ", L2Cache, prefetch_in]");

  s_profiler.possibleTransition(L2Cache_State_L2_NP, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_L2_NP, L2Cache_Event_L1_PUTS_old);
  s_profiler.possibleTransition(L2Cache_State_L2_I, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_L2_I, L2Cache_Event_L1_PUTS_old);
  s_profiler.possibleTransition(L2Cache_State_L2_S, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_L2_S, L2Cache_Event_L1_PUTS_old);
  s_profiler.possibleTransition(L2Cache_State_L2_SS, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_L2_SS, L2Cache_Event_L1_PUTS_old);
  s_profiler.possibleTransition(L2Cache_State_L2_M, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_L2_M, L2Cache_Event_L1_PUTS_old);
  s_profiler.possibleTransition(L2Cache_State_L2_MT, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_L2_MT, L2Cache_Event_L1_PUTS_old);
  s_profiler.possibleTransition(L2Cache_State_L2_O, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_L2_O, L2Cache_Event_L1_PUTS_old);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L1_PUTX_old);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L1_PUTS_old);
  s_profiler.possibleTransition(L2Cache_State_L2_NP, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_NP, L2Cache_Event_L2_PrefetchS_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_NP, L2Cache_Event_L2_PrefetchX_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_I, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_I, L2Cache_Event_L2_PrefetchS_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_I, L2Cache_Event_L2_PrefetchX_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_NP, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_I, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_NP, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_NP, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_I, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_I, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_NP, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_L2_NP, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_L2_NP, L2Cache_Event_L1_UPGRADE_no_others);
  s_profiler.possibleTransition(L2Cache_State_L2_I, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_L2_I, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_L2_I, L2Cache_Event_L1_UPGRADE_no_others);
  s_profiler.possibleTransition(L2Cache_State_L2_IS, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_IS, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IS, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_IS, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_ISI, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_ISI, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_IMV, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_IMV, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IMV, L2Cache_Event_Data_ext_ack_not_0_last);
  s_profiler.possibleTransition(L2Cache_State_L2_IMV, L2Cache_Event_Data_ext_ack_not_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IMV, L2Cache_Event_Proc_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_IMV, L2Cache_Event_Proc_last_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_MV, L2Cache_Event_Proc_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_MV, L2Cache_Event_Proc_last_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_IM, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_IM, L2Cache_Event_Forwarded_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_IM, L2Cache_Event_Forwarded_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_IM, L2Cache_Event_Forwarded_PREFS);
  s_profiler.possibleTransition(L2Cache_State_L2_IM, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_IM, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_IM, L2Cache_Event_Forwarded_GETX);
  s_profiler.possibleTransition(L2Cache_State_L2_IM, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IM, L2Cache_Event_Data_ext_ack_not_0_last);
  s_profiler.possibleTransition(L2Cache_State_L2_IM, L2Cache_Event_Data_ext_ack_not_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IMO, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_IMO, L2Cache_Event_Forwarded_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_IMO, L2Cache_Event_Forwarded_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_IMO, L2Cache_Event_Forwarded_PREFS);
  s_profiler.possibleTransition(L2Cache_State_L2_IMO, L2Cache_Event_Forwarded_GETX);
  s_profiler.possibleTransition(L2Cache_State_L2_IMO, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_IMO, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_IMO, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IMO, L2Cache_Event_Data_ext_ack_not_0_last);
  s_profiler.possibleTransition(L2Cache_State_L2_IMO, L2Cache_Event_Data_ext_ack_not_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IMI, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IMI, L2Cache_Event_Data_ext_ack_not_0_last);
  s_profiler.possibleTransition(L2Cache_State_L2_IMI, L2Cache_Event_Data_ext_ack_not_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IMZ, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IMZ, L2Cache_Event_Data_ext_ack_not_0_last);
  s_profiler.possibleTransition(L2Cache_State_L2_IMZ, L2Cache_Event_Data_ext_ack_not_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IMZ, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_IMOI, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IMOI, L2Cache_Event_Data_ext_ack_not_0_last);
  s_profiler.possibleTransition(L2Cache_State_L2_IMOI, L2Cache_Event_Data_ext_ack_not_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IMOI, L2Cache_Event_PrefetchS);
  s_profiler.possibleTransition(L2Cache_State_L2_IMOZ, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_IMOZ, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_IMOZ, L2Cache_Event_Data_ext_ack_not_0_last);
  s_profiler.possibleTransition(L2Cache_State_L2_IMOZ, L2Cache_Event_Data_ext_ack_not_0);
  s_profiler.possibleTransition(L2Cache_State_L2_S, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_S, L2Cache_Event_L2_PrefetchS_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_S, L2Cache_Event_L2_PrefetchX_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_S, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_S, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_S, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_S, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_L2_S, L2Cache_Event_Data_replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_SM, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_SM, L2Cache_Event_Data_ext_ack_not_0_last);
  s_profiler.possibleTransition(L2Cache_State_L2_SM, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_SM, L2Cache_Event_Data_ext_ack_not_0);
  s_profiler.possibleTransition(L2Cache_State_L2_SSM, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_SSM, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_SSM, L2Cache_Event_Data_ext_ack_not_0_last);
  s_profiler.possibleTransition(L2Cache_State_L2_SSM, L2Cache_Event_Data_ext_ack_not_0);
  s_profiler.possibleTransition(L2Cache_State_L2_SSM, L2Cache_Event_Proc_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_SSM, L2Cache_Event_Proc_last_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_SSMV, L2Cache_Event_Proc_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_SSMV, L2Cache_Event_Proc_last_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_SS, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_SS, L2Cache_Event_L2_PrefetchS_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_SS, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_SS, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_SS, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_SS, L2Cache_Event_L1_UPGRADE_no_others);
  s_profiler.possibleTransition(L2Cache_State_L2_SS, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_L2_SS, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_L2_SS, L2Cache_Event_L1_PUTS);
  s_profiler.possibleTransition(L2Cache_State_L2_SS, L2Cache_Event_L1_PUTS_last);
  s_profiler.possibleTransition(L2Cache_State_L2_SS, L2Cache_Event_Data_replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_SIC, L2Cache_Event_Proc_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_SIC, L2Cache_Event_Proc_last_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_SIC, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_SIV, L2Cache_Event_Proc_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_SIV, L2Cache_Event_Proc_last_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_PSIV, L2Cache_Event_Proc_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_PSIV, L2Cache_Event_Proc_last_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_M, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_M, L2Cache_Event_L2_PrefetchS_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_M, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_M, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_M, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_L2_M, L2Cache_Event_Data_replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_MT, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_MT, L2Cache_Event_L2_PrefetchS_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_MT, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_MT, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_MT, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_L2_MT, L2Cache_Event_L1_PUTX_last);
  s_profiler.possibleTransition(L2Cache_State_L2_MT, L2Cache_Event_Data_replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_MIV, L2Cache_Event_Data_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_PMIV, L2Cache_Event_Data_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_MIC, L2Cache_Event_Data_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_MIT, L2Cache_Event_Data_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_MO, L2Cache_Event_Data_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_MO, L2Cache_Event_Forwarded_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_MO, L2Cache_Event_Forwarded_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_MO, L2Cache_Event_Forwarded_PREFS);
  s_profiler.possibleTransition(L2Cache_State_L2_MO, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_MO, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_MOIC, L2Cache_Event_Data_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_MOICR, L2Cache_Event_Data_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_MOZ, L2Cache_Event_Data_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_O, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_O, L2Cache_Event_L2_PrefetchS_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_O, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_O, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_O, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_L2_O, L2Cache_Event_Data_replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L2_PrefetchS_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L2_PrefetchX_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L1_UPGRADE_no_others);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L1_PUTS);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L1_PUTX);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L1_PUTS_last);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_L1_PUTX_last);
  s_profiler.possibleTransition(L2Cache_State_L2_SO, L2Cache_Event_Data_replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_OIV, L2Cache_Event_Proc_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_OIV, L2Cache_Event_Proc_last_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_POIV, L2Cache_Event_Proc_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_POIV, L2Cache_Event_Proc_last_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_OIC, L2Cache_Event_Proc_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_OIC, L2Cache_Event_Proc_last_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_OMV, L2Cache_Event_Proc_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_OMV, L2Cache_Event_Proc_last_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_NRSS, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_NRSS, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_NRSS, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_NRSS, L2Cache_Event_L1_UPGRADE_no_others);
  s_profiler.possibleTransition(L2Cache_State_L2_NRSS, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_L2_NRSS, L2Cache_Event_L1_UPGRADE);
  s_profiler.possibleTransition(L2Cache_State_L2_NRSS, L2Cache_Event_L1_PUTS);
  s_profiler.possibleTransition(L2Cache_State_L2_NRSS, L2Cache_Event_L1_PUTS_last);
  s_profiler.possibleTransition(L2Cache_State_L2_NRSIV, L2Cache_Event_Proc_last_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_NRS, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_NRS, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_NRS, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_NRS, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_L2_INRS, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_INRS, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_INRS, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_INRS, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_INRSZ, L2Cache_Event_L2_INV);
  s_profiler.possibleTransition(L2Cache_State_L2_INRSZ, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_INRM, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_INRM, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_INRM, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_INRM, L2Cache_Event_Data_ext_ack_not_0_last);
  s_profiler.possibleTransition(L2Cache_State_L2_INRM, L2Cache_Event_Data_ext_ack_not_0);
  s_profiler.possibleTransition(L2Cache_State_L2_INRMZ, L2Cache_Event_Data_ext_ack_0);
  s_profiler.possibleTransition(L2Cache_State_L2_INRMZ, L2Cache_Event_Data_ext_ack_not_0_last);
  s_profiler.possibleTransition(L2Cache_State_L2_INRMZ, L2Cache_Event_Data_ext_ack_not_0);
  s_profiler.possibleTransition(L2Cache_State_L2_NRMT, L2Cache_Event_L2_Replacement);
  s_profiler.possibleTransition(L2Cache_State_L2_NRMT, L2Cache_Event_L1_GETS);
  s_profiler.possibleTransition(L2Cache_State_L2_NRMT, L2Cache_Event_L1_GET_INSTR);
  s_profiler.possibleTransition(L2Cache_State_L2_NRMT, L2Cache_Event_L1_GETX);
  s_profiler.possibleTransition(L2Cache_State_L2_NRMT, L2Cache_Event_L1_PUTX_last);
  s_profiler.possibleTransition(L2Cache_State_L2_NRMIT, L2Cache_Event_Data_int_ack);
  s_profiler.possibleTransition(L2Cache_State_L2_NRMIV, L2Cache_Event_Data_int_ack);
}

void L2Cache_Controller::print(ostream& out) const { out << "[L2Cache_Controller " << m_chip_ptr->getID() << " " << m_version << "]"; }

// Actions

/** \brief Issue prefetch*/
void L2Cache_Controller::ja_issuePREFETCH(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_prefetchQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_owner = ((*in_msg_ptr)).m_RequestorMachId;
    (((*(m_chip_ptr->m_L2Cache_dram_vec[m_version]))).i_request(addr, (3), ((*in_msg_ptr)).m_RequestorMachId, ((*in_msg_ptr)).m_RequestorMachId));
  }
}

/** \brief send upgrade prefetch*/
void L2Cache_Controller::t_sendUpgradePrefetch(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_owner = ((*in_msg_ptr)).m_RequestorMachId;
    (((*(m_chip_ptr->m_L2Cache_dram_vec[m_version]))).i_request(addr, (5), ((*in_msg_ptr)).m_RequestorMachId, ((*in_msg_ptr)).m_RequestorMachId));
  }
}

/** \brief Issue GETS*/
void L2Cache_Controller::a_issueGETS(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_owner = ((*in_msg_ptr)).m_RequestorMachId;
    (((*(m_chip_ptr->m_L2Cache_dram_vec[m_version]))).i_request(addr, (1), ((*in_msg_ptr)).m_RequestorMachId, ((*in_msg_ptr)).m_RequestorMachId));
  }
}

/** \brief Issue GETX*/
void L2Cache_Controller::b_issueGETX(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_owner = ((*in_msg_ptr)).m_RequestorMachId;
    (((*(m_chip_ptr->m_L2Cache_dram_vec[m_version]))).i_request(addr, (1), ((*in_msg_ptr)).m_RequestorMachId, ((*in_msg_ptr)).m_RequestorMachId));
  }
}

/** \brief Issue GETINSTR*/
void L2Cache_Controller::f_issueGETINSTR(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_owner = ((*in_msg_ptr)).m_RequestorMachId;
    (((*(m_chip_ptr->m_L2Cache_dram_vec[m_version]))).i_request(addr, (1), ((*in_msg_ptr)).m_RequestorMachId, ((*in_msg_ptr)).m_RequestorMachId));
  }
}

/** \brief Issue PUTX*/
void L2Cache_Controller::d_issuePUTX(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_dram_vec[m_version]))).i_request(addr, (2), m_machineID, m_machineID));
}

/** \brief Send FinalAck to dir if this is response to 3-hop xfer*/
void L2Cache_Controller::c_finalAckToDirIfNeeded(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:802: ", (*in_msg_ptr));
;
    if (((machineIDToMachineType(((*in_msg_ptr)).m_SenderMachId)) == MachineType_L2Cache)) {
      {
        ResponseMsg out_msg;
        (out_msg).m_Address = addr;
        (out_msg).m_Type = CoherenceResponseType_FINALACK;
        (out_msg).m_SenderMachId = m_machineID;
        (((out_msg).m_Destination).add((map_Address_to_Directory(addr))));
        (out_msg).m_MessageSize = MessageSizeType_Control;
        DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:810: ", out_msg);
;
        ((*(m_chip_ptr->m_L2Cache_finalAckFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
      }
    }
  }
}

/** \brief */
void L2Cache_Controller::n_sendFinalAckIfThreeHop(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:819: ", (*in_msg_ptr));
;
    if ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_isThreeHop == (true))) {
      {
        ResponseMsg out_msg;
        (out_msg).m_Address = addr;
        (out_msg).m_Type = CoherenceResponseType_FINALACK;
        (out_msg).m_SenderMachId = m_machineID;
        (((out_msg).m_Destination).add((map_Address_to_Directory(addr))));
        (out_msg).m_MessageSize = MessageSizeType_Control;
        DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:827: ", out_msg);
;
        ((*(m_chip_ptr->m_L2Cache_finalAckFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
      }
    }
  }
}

/** \brief */
void L2Cache_Controller::mm_rememberIfFinalAckNeeded(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if (((machineIDToMachineType(((*in_msg_ptr)).m_SenderMachId)) == MachineType_L2Cache)) {
      ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_isThreeHop = (true);
    }
  }
}

/** \brief If not prefetch, notify sequencer the load completed.*/
void L2Cache_Controller::h_issueLoadHit(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:847: ", ((L2Cache_getL2CacheEntry(addr))).m_DataBlk);
;
  if ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).isPresent(addr)) == (false)) || (((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_isPrefetch == (false)))) {
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:855: ", (out_msg).m_Destination);
;
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  } else {
  }
}

/** \brief If not prefetch, notify sequencer the load completed.*/
void L2Cache_Controller::oo_issueLoadHitInv(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:865: ", ((L2Cache_getL2CacheEntry(addr))).m_DataBlk);
;
  if ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).isPresent(addr)) == (false)) || (((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_isPrefetch == (false)))) {
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA_I;
      (out_msg).m_SenderMachId = m_machineID;
      (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:873: ", (out_msg).m_Destination);
;
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  } else {
  }
}

/** \brief If not prefetch, issue store hit message to local L1 requestor*/
void L2Cache_Controller::hh_issueStoreHit(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:884: ", ((L2Cache_getL2CacheEntry(addr))).m_DataBlk);
;
  if ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).isPresent(addr)) == (false)) || (((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_isPrefetch == (false)))) {
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (((out_msg).m_Destination).add(((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetX_ID));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:892: ", (out_msg).m_Destination);
;
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  } else {
  }
}

/** \brief If not prefetch, issue store hit message to local L1 requestor*/
void L2Cache_Controller::pp_issueStoreHitInv(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:902: ", ((L2Cache_getL2CacheEntry(addr))).m_DataBlk);
;
  if ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).isPresent(addr)) == (false)) || (((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_isPrefetch == (false)))) {
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA_I;
      (out_msg).m_SenderMachId = m_machineID;
      (((out_msg).m_Destination).add(((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetX_ID));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:910: ", (out_msg).m_Destination);
;
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  } else {
  }
}

/** \brief If not prefetch, issue store hit message to local L1 requestor*/
void L2Cache_Controller::cc_issueStoreHitDG(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:920: ", ((L2Cache_getL2CacheEntry(addr))).m_DataBlk);
;
  if ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).isPresent(addr)) == (false)) || (((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_isPrefetch == (false)))) {
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA_S;
      (out_msg).m_SenderMachId = m_machineID;
      (((out_msg).m_Destination).add(((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetX_ID));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:928: ", (out_msg).m_Destination);
;
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  } else {
  }
}

/** \brief send acknowledgement of an L1 replacement*/
void L2Cache_Controller::w_sendPutAckToL1Cache(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_ACK;
      (out_msg).m_SenderMachId = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_RequestorMachId));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:944: ", (out_msg).m_Destination);
;
      (out_msg).m_MessageSize = MessageSizeType_Control;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  }
}

/** \brief Send data from cache to all GetS IDs*/
void L2Cache_Controller::ee_dataFromL2CacheToGetSIDs(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if ((((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Forward_GetS_IDs).count()) > (0))) {
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Forward_GetS_IDs;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:961: ", (out_msg).m_Destination);
;
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_NumPendingExtAcks = (0);
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:964: ", (out_msg).m_Address);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:965: ", (out_msg).m_Destination);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:966: ", (out_msg).m_DataBlk);
;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  }
  if ((((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).count()) > (0))) {
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:977: ", (out_msg).m_Destination);
;
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  }
}

/** \brief Send data from cache to GetS ForwardIDs*/
void L2Cache_Controller::bb_dataFromL2CacheToGetSForwardIDs(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if (((((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Forward_GetS_IDs).count()) > (0)) || (((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).count()) > (0)))) {
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Forward_GetS_IDs;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:993: ", (out_msg).m_Destination);
;
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_NumPendingExtAcks = (0);
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  }
}

/** \brief Send data from cache to GetS ForwardIDs*/
void L2Cache_Controller::bb_dataFromL2CacheToGetSForwardIDsPref(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if (((((((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_Forward_GetS_IDs).count()) > (0)) || (((((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).count()) > (0)))) {
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_Forward_GetS_IDs;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1010: ", (out_msg).m_Destination);
;
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_NumPendingExtAcks = (0);
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  }
}

/** \brief Send data from cache to GetX ForwardID*/
void L2Cache_Controller::gg_dataFromL2CacheToGetXForwardID(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if (((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_validForwardedGetXId) {
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (((out_msg).m_Destination).add(((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Forward_GetX_ID));
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_NumPendingExtAcks = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_ForwardGetX_AckCount;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1029: ", (out_msg).m_Address);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1030: ", (out_msg).m_Destination);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1031: ", (out_msg).m_DataBlk);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1032: ", (out_msg).m_NumPendingExtAcks);
;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      (out_msg).m_prefDWG = (((L2Cache_getL2CacheEntry(addr))).m_CacheState == L2Cache_State_L2_MIC);
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  }
}

/** \brief Send data from cache to GetX ForwardID*/
void L2Cache_Controller::gg_dataFromL2CacheToGetXForwardIDPref(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if (((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_validForwardedGetXId) {
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (((out_msg).m_Destination).add(((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_Forward_GetX_ID));
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_NumPendingExtAcks = ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_ForwardGetX_AckCount;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1049: ", (out_msg).m_Address);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1050: ", (out_msg).m_Destination);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1051: ", (out_msg).m_DataBlk);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1052: ", (out_msg).m_NumPendingExtAcks);
;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      (out_msg).m_prefDWG = (((L2Cache_getL2CacheEntry(addr))).m_CacheState == L2Cache_State_L2_MIC);
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  }
}

/** \brief Send data from cache to requestor*/
void L2Cache_Controller::e_dataFromL2CacheToL2Requestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (out_msg).m_NumPendingExtAcks = ((*in_msg_ptr)).m_NumPendingExtAcks;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_RequestorMachId));
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1070: ", (out_msg).m_Address);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1071: ", (out_msg).m_Destination);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1072: ", (out_msg).m_DataBlk);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1073: ", (out_msg).m_NumPendingExtAcks);
;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      (out_msg).m_prefDWG = ((((L2Cache_getL2CacheEntry(addr))).m_CacheState == L2Cache_State_L2_M) || (((L2Cache_getL2CacheEntry(addr))).m_CacheState == L2Cache_State_L2_MT));
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  }
}

/** \brief Send data from cache to L1 requestor*/
void L2Cache_Controller::k_dataFromL2CacheToL1Requestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_RequestorMachId));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1089: ", (out_msg).m_Destination);
;
      (out_msg).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  }
}

/** \brief Allocate TBE for internal/external request(isPrefetch=0, number of invalidates=0)*/
void L2Cache_Controller::i_allocateTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).allocate(addr));
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingIntAcks = (0);
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks = (0);
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_isPrefetch = (false);
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_isThreeHop = (false);
  ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Forward_GetS_IDs).clear());
  ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).clear());
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_validInvalidator = (false);
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_validForwardedGetXId = (false);
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_isInternalRequestOnly = (false);
}

/** \brief Allocate Pref TBE for internal/external request(isPrefetch=0, number of invalidates=0)*/
void L2Cache_Controller::i_allocatePrefTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).allocate(addr));
  ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingIntAcks = (0);
  ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks = (0);
  ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_isPrefetch = (false);
  ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_prefetch = PrefetchBit_No;
  ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_isThreeHop = (false);
  ((((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_Forward_GetS_IDs).clear());
  ((((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).clear());
  ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_validInvalidator = (false);
  ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_validForwardedGetXId = (false);
  ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_isInternalRequestOnly = (false);
}

/** \brief marca en el bloque de cache  que no nos expuls— una prebusqueda*/
void L2Cache_Controller::ji_marcaRepl(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefTypeRepl = (0);
}

/** \brief marca en el bloque de cache  que nos expuls— una preb en lectura*/
void L2Cache_Controller::jis_marcaRepl(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefTypeRepl = (1);
}

/** \brief marca en el bloque de cache  que nos expuls— una preb en escritura*/
void L2Cache_Controller::jix_marcaRepl(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefTypeRepl = (2);
}

/** \brief Deallocate external TBE*/
void L2Cache_Controller::s_deallocateTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).statsLat((2), addr));
  (((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).deallocate(addr));
}

/** \brief Deallocate external PrefTBE*/
void L2Cache_Controller::s_deallocatePrefTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).statsLat((3), addr));
  (((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).deallocate(addr));
}

/** \brief */
void L2Cache_Controller::jj_deactiveBloom(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if ((((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_prefetch == PrefetchBit_L2_HW)) {
    (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).bloomG((0), addr, m_machineID, ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_owner));
    (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).bloomL((0), addr, ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_owner));
  }
}

/** \brief Pop incoming L1 request queue*/
void L2Cache_Controller::jj_popL1RequestQueue2(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((0), (((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Pop incoming L1 request queue*/
void L2Cache_Controller::jj_popL1RequestQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((0), (((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Pop incoming forwarded request queue*/
void L2Cache_Controller::l_popForwardedRequestQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((2), (((*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Pop Incoming Response queue*/
void L2Cache_Controller::o_popIncomingResponseQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((3), (((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Pop Incoming pref Response queue*/
void L2Cache_Controller::jo_popIncomingPrefResponseQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((5), (((*(m_chip_ptr->m_L2Cache_prefResponseToL2CacheQueue_vec[m_version]))).dequeue_getDelayCycles())));
}

/** \brief Pop prefetch request queue*/
void L2Cache_Controller::jjj_popPrefetchQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_prefetchQueue_vec[m_version]))).dequeue());
}

/** \brief Pop prefetch request queue*/
void L2Cache_Controller::jjj_popResponeDramQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_responseToL2CacheQueue_vec[m_version]))).dequeue());
}

/** \brief Add number of pending acks to TBE*/
void L2Cache_Controller::p_addNumberOfPendingExtAcks(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1200: ", ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks);
;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks = (((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks + ((*in_msg_ptr)).m_NumPendingExtAcks);
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1202: ", ((*in_msg_ptr)).m_NumPendingExtAcks);
;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1203: ", ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks);
;
  }
}

/** \brief Decrement number of pending ext invalidations by one*/
void L2Cache_Controller::q_decrementNumberOfPendingExtAcks(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1208: ", ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks);
;
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks = (((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks - (1));
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1210: ", ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks);
;
}

/** \brief Decrement number of pending int invalidations by one*/
void L2Cache_Controller::r_decrementNumberOfPendingIntAcks(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1214: ", ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks);
;
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingIntAcks = (((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingIntAcks - (1));
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1216: ", ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks);
;
}

/** \brief Decrement number of pending int invalidations by one*/
void L2Cache_Controller::r_decrementNumberOfPendingIntAcksPrefTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1220: ", ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks);
;
  ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingIntAcks = (((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingIntAcks - (1));
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1222: ", ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingExtAcks);
;
}

/** \brief Send ack to invalidator*/
void L2Cache_Controller::t_sendAckToInvalidator(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_ACK;
      (out_msg).m_SenderMachId = m_machineID;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_RequestorMachId));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1232: ", (out_msg).m_Destination);
;
      (out_msg).m_NumPendingExtAcks = (0);
      (out_msg).m_MessageSize = MessageSizeType_Control;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  }
}

/** \brief Write data from response queue to cache*/
void L2Cache_Controller::ju_writePrefetchDataFromResponseQueueToL2Cache(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_prefResponseToL2CacheQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((L2Cache_getL2CacheEntry(addr))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
    ((L2Cache_getL2CacheEntry(addr))).m_prefetch = PrefetchBit_L2_HW;
    ((L2Cache_getL2CacheEntry(addr))).m_prefDWG = ((*in_msg_ptr)).m_prefDWG;
    if (((*in_msg_ptr)).m_prefDWG) {
      ((L2Cache_getL2CacheEntry(addr))).m_prevOwner = ((*in_msg_ptr)).m_SenderMachId;
    }
    ((L2Cache_getL2CacheEntry(addr))).m_prevSharers = ((*in_msg_ptr)).m_prevSharers;
    ((L2Cache_getL2CacheEntry(addr))).m_epoch = ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_epoch;
  }
}

/** \brief Write data from response queue to cache*/
void L2Cache_Controller::u_writeDataFromResponseQueueToL2Cache(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2CacheQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((L2Cache_getL2CacheEntry(addr))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
    ((L2Cache_getL2CacheEntry(addr))).m_prefetch = PrefetchBit_No;
    ((L2Cache_getL2CacheEntry(addr))).m_prefDWG = (false);
  }
}

/** \brief Write data from response queue to cache*/
void L2Cache_Controller::jm_writeDataFromResponseQueueToL2Cache(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((L2Cache_getL2CacheEntry(addr))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
  }
}

/** \brief Write data from response queue to cache*/
void L2Cache_Controller::m_writeDataFromRequestQueueToL2Cache(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((L2Cache_getL2CacheEntry(addr))).m_DataBlk = ((*in_msg_ptr)).m_DataBlk;
  }
}

/** \brief Copy data from cache to TBE*/
void L2Cache_Controller::x_copyDataFromL2CacheToTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
}

/** \brief Copy data from cache to Pref TBE*/
void L2Cache_Controller::x_copyDataFromL2CacheToPrefTBE(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk = ((L2Cache_getL2CacheEntry(addr))).m_DataBlk;
}

/** \brief Send data from TBE to requestor*/
void L2Cache_Controller::y_dataFromTBEToRequestor(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_DATA;
      (out_msg).m_SenderMachId = m_machineID;
      (out_msg).m_NumPendingExtAcks = ((*in_msg_ptr)).m_NumPendingExtAcks;
      (((out_msg).m_Destination).add(((*in_msg_ptr)).m_RequestorMachId));
      (out_msg).m_DataBlk = ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_DataBlk;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1294: ", (out_msg).m_Address);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1295: ", (out_msg).m_Destination);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1296: ", (out_msg).m_DataBlk);
;
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1297: ", (out_msg).m_NumPendingExtAcks);
;
      (out_msg).m_MessageSize = MessageSizeType_Data;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  }
}

/** \brief Send ack to invalidator*/
void L2Cache_Controller::zz_sendAckToQueuedInvalidator(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if (((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_validInvalidator) {
    {
      ResponseMsg out_msg;
      (out_msg).m_Address = addr;
      (out_msg).m_Type = CoherenceResponseType_ACK;
      (out_msg).m_SenderMachId = m_machineID;
      (((out_msg).m_Destination).add(((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_InvalidatorID));
      DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1310: ", (out_msg).m_Destination);
;
      (out_msg).m_NumPendingExtAcks = (0);
      (out_msg).m_MessageSize = MessageSizeType_Control;
      ((*(m_chip_ptr->m_L2Cache_responseFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_RESPONSE_LATENCY);
    }
  }
}

/** \brief Stall*/
void L2Cache_Controller::z_stall(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
}

/** \brief Record Invalidator for future response*/
void L2Cache_Controller::yy_recordInvalidatorID(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_InvalidatorID = ((*in_msg_ptr)).m_RequestorMachId;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_validInvalidator = (true);
  }
}

/** \brief Record forwarded GetS for future forwarding*/
void L2Cache_Controller::dd_recordGetSForwardID(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Forward_GetS_IDs).add(((*in_msg_ptr)).m_RequestorMachId));
  }
}

/** \brief Record forwarded L1 GetS for load response*/
void L2Cache_Controller::ss_recordGetSL1ID(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetS_IDs).add(((*in_msg_ptr)).m_RequestorMachId));
  }
}

/** \brief Record forwarded GetX and ack count for future forwarding*/
void L2Cache_Controller::ii_recordGetXForwardID(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_Forward_GetX_ID = ((*in_msg_ptr)).m_RequestorMachId;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_ForwardGetX_AckCount = ((*in_msg_ptr)).m_NumPendingExtAcks;
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_validForwardedGetXId = (true);
  }
}

/** \brief Record L1 GetX for store response*/
void L2Cache_Controller::xx_recordGetXL1ID(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_L1_GetX_ID = ((*in_msg_ptr)).m_RequestorMachId;
  }
}

/** \brief set the MRU entry*/
void L2Cache_Controller::set_setMRU(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).setMRU(addr, (L1CacheMachIDToProcessorNum(((*in_msg_ptr)).m_RequestorMachId))));
  }
}

/** \brief set the last touch*/
void L2Cache_Controller::setTimeLast(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).setTimeLast(addr));
}

/** \brief Set number of pending acks equal to number of sharers*/
void L2Cache_Controller::bbb_setPendingIntAcksToSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingIntAcks = ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers).count());
}

/** \brief Set number of pending acks equal to number of sharers*/
void L2Cache_Controller::bbb_setPendingIntAcksToSharersPref(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingIntAcks = ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers).count());
}

/** \brief Set number of pending acks equal to one*/
void L2Cache_Controller::ddd_setPendingIntAcksToOne(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingIntAcks = (1);
}

/** \brief Set number of pending acks equal to number of sharers minus one*/
void L2Cache_Controller::ccc_setPendingIntAcksMinusOne(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(addr))).m_NumPendingIntAcks = (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers).count()) - (1));
}

/** \brief Set L2 cache tag equal to tag of block B.*/
void L2Cache_Controller::qq_allocateL2CacheBlock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).isTagPresent(addr)) == (false))) {
      (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).allocateL2(addr));
    }
    if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GET_INSTR)) {
      ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_instr = (true);
    } else {
      ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_instr = (false);
    }
  }
}

/** \brief Deallocate L2 cache block.  Sets the cache to not present, allowing a replacement in parallel with a fetch.*/
void L2Cache_Controller::rr_deallocateL2CacheBlock(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_PrevLocalCacheState = ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_CacheState;
  (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).deallocate(addr));
}

/** \brief Profile the demand miss*/
void L2Cache_Controller::uu_profileMiss(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (profile_L2Cache_miss((m_chip_ptr->convertToGenericType(((*in_msg_ptr)).m_Type)), ((*in_msg_ptr)).m_AccessMode, (MessageSizeTypeToInt(((*in_msg_ptr)).m_MessageSize)), ((*in_msg_ptr)).m_Prefetch, (L1CacheMachIDToProcessorNum(((*in_msg_ptr)).m_RequestorMachId))));
  }
}

/** \brief Profile an access*/
void L2Cache_Controller::uu_profileAccess(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (profile_accessL3(((*in_msg_ptr)).m_AccessMode, (L1CacheMachIDToProcessorNum(((*in_msg_ptr)).m_RequestorMachId))));
  }
}

/** \brief Profile this transition at the L2 because Dir won't see the request*/
void L2Cache_Controller::ww_profileMissNoDir(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (profile_request(((*in_msg_ptr)).m_L1CacheStateStr, (L2Cache_getStateStr(addr)), ("NA"), (L2Cache_getCoherenceRequestTypeStr(((*in_msg_ptr)).m_Type))));
  }
}

/** \brief invalidate the L1 M copy*/
void L2Cache_Controller::v_issueInvalidateIntL1copyRequest(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    RequestMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceRequestType_INV;
    (out_msg).m_RequestorMachId = m_machineID;
    (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers;
    (out_msg).m_MessageSize = MessageSizeType_Control;
    ((*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_REQUEST_LATENCY);
  }
}

/** \brief invalidate all L1 S copies*/
void L2Cache_Controller::tt_issueSharedInvalidateIntL1copiesRequest(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    RequestMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceRequestType_INV_S;
    (out_msg).m_RequestorMachId = m_machineID;
    (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers;
    (out_msg).m_MessageSize = MessageSizeType_Control;
    ((*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_REQUEST_LATENCY);
  }
}

/** \brief invalidate the L1 M copy*/
void L2Cache_Controller::v_issueInvalidatePIntL1copyRequest(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    RequestMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceRequestType_INV_P;
    (out_msg).m_RequestorMachId = m_machineID;
    (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers;
    (out_msg).m_MessageSize = MessageSizeType_Control;
    ((*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_REQUEST_LATENCY);
  }
}

/** \brief invalidate all L1 S copies*/
void L2Cache_Controller::tt_issueSharedInvalidatePIntL1copiesRequest(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    RequestMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceRequestType_INV_S_P;
    (out_msg).m_RequestorMachId = m_machineID;
    (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers;
    (out_msg).m_MessageSize = MessageSizeType_Control;
    ((*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_REQUEST_LATENCY);
  }
}

/** \brief invalidate other L1 copies not the local requestor*/
void L2Cache_Controller::vv_issueInvalidateOtherIntL1copiesRequest(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if (((((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers).count()) > (1)) || (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers).isElement(((*in_msg_ptr)).m_RequestorMachId)) != (true)))) {
      {
        RequestMsg out_msg;
        (out_msg).m_Address = addr;
        (out_msg).m_Type = CoherenceRequestType_INV_S;
        (out_msg).m_RequestorMachId = m_machineID;
        (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers;
        (((out_msg).m_Destination).remove(((*in_msg_ptr)).m_RequestorMachId));
        (out_msg).m_MessageSize = MessageSizeType_Control;
        ((*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_REQUEST_LATENCY);
      }
    }
  }
}

/** \brief DownGrade L1 copy*/
void L2Cache_Controller::g_issueDownGradeIntL1copiesRequest(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    RequestMsg out_msg;
    (out_msg).m_Address = addr;
    (out_msg).m_Type = CoherenceRequestType_L1_DG;
    (out_msg).m_RequestorMachId = m_machineID;
    (out_msg).m_Destination = ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers;
    (out_msg).m_MessageSize = MessageSizeType_Control;
    ((*(m_chip_ptr->m_L2Cache_L1RequestFromL2Cache_vec[m_version]))).enqueue(out_msg, L2_REQUEST_LATENCY);
  }
}

/** \brief Add L1 sharer to list*/
void L2Cache_Controller::nn_addSharer(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (L2Cache_addSharer(addr, ((*in_msg_ptr)).m_RequestorMachId));
  }
}

/** \brief Remove L1 Request sharer from list*/
void L2Cache_Controller::kk_removeRequestSharer(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers).remove(((*in_msg_ptr)).m_RequestorMachId));
  }
}

/** \brief Remove L1 Response sharer from list*/
void L2Cache_Controller::aa_removeResponseSharer(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const ResponseMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers).remove(((*in_msg_ptr)).m_SenderMachId));
  }
}

/** \brief Remove all L1 sharers from list*/
void L2Cache_Controller::ll_clearSharers(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_Sharers).clear());
}

/** \brief mandamos al prefetcher la direcci—n del fallo*/
void L2Cache_Controller::jaa_missToPrefetch(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if (((isPrefetcher()) == (1))) {
      if (((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS) || (((*in_msg_ptr)).m_Type == CoherenceRequestType_GET_INSTR))) {
        (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).miss(addr, ((*in_msg_ptr)).m_ProgramCounter, (1), ((*in_msg_ptr)).m_RequestorMachId, (0)));
      } else {
        (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).miss(addr, ((*in_msg_ptr)).m_ProgramCounter, (2), ((*in_msg_ptr)).m_RequestorMachId, (0)));
      }
    }
  }
}

/** \brief Marcamos como usado (y mandamos al prefetcher la direcci—n del fallo)*/
void L2Cache_Controller::jab_firstUseToPrefetcherS(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((isPrefetcher()) == (1)) && (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefetch == PrefetchBit_L2_HW))) {
      ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefetch = PrefetchBit_No;
      if (((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS) || (((*in_msg_ptr)).m_Type == CoherenceRequestType_GET_INSTR))) {
        (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).miss(addr, ((*in_msg_ptr)).m_ProgramCounter, (1), ((*in_msg_ptr)).m_RequestorMachId, (1)));
      } else {
        (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).miss(addr, ((*in_msg_ptr)).m_ProgramCounter, (2), ((*in_msg_ptr)).m_RequestorMachId, (1)));
      }
    }
  }
}

/** \brief Marcamos como usado (y mandamos al prefetcher la direcci—n del fallo)*/
void L2Cache_Controller::jab_firstUseToPrefetcherX(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((isPrefetcher()) == (1)) && (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefetch == PrefetchBit_L2_HW))) {
      if (((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS) || (((*in_msg_ptr)).m_Type == CoherenceRequestType_GET_INSTR))) {
        (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).miss(addr, ((*in_msg_ptr)).m_ProgramCounter, (2), ((*in_msg_ptr)).m_RequestorMachId, (1)));
      } else {
        (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).miss(addr, ((*in_msg_ptr)).m_ProgramCounter, (2), ((*in_msg_ptr)).m_RequestorMachId, (1)));
      }
    }
  }
}

/** \brief preb UTIL*/
void L2Cache_Controller::jjj_statsPrefetchLocal(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefetch == PrefetchBit_L2_HW)) {
      if (((((*in_msg_ptr)).m_Type == CoherenceRequestType_GET_INSTR) || (((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS))) {
        (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((1)));
      } else {
        if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETX)) {
          (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((2)));
        }
      }
    }
  }
}

/** \brief preb UTIL de cada core*/
void L2Cache_Controller::jjj_statsPrefetchLocalS(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefetch == PrefetchBit_L2_HW)) {
      if (((((*in_msg_ptr)).m_Type == CoherenceRequestType_GET_INSTR) || (((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS))) {
        (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats2((1), ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_owner, ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_epoch));
      } else {
        if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETX)) {
          (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats2((2), ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_owner, ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_epoch));
        }
      }
    }
  }
}

/** \brief preb INUTIL*/
void L2Cache_Controller::jjj_statsPrefetchLocal2(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefetch == PrefetchBit_L2_HW)) {
    (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((3)));
  }
}

/** \brief preb INUTIL de cada core*/
void L2Cache_Controller::jjj_statsPrefetchLocalS2(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefetch == PrefetchBit_L2_HW)) {
    (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats2((3), ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_owner, (0)));
  }
}

/** \brief */
void L2Cache_Controller::jjj_statsPrefetchLocal3(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).wasTagPresent(addr))) {
      if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_prefetch == PrefetchBit_L2_HW)) {
        if (((((*in_msg_ptr)).m_Type == CoherenceRequestType_GET_INSTR) || (((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS))) {
          if (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_M) || (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_MT))) {
            if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_prefTypeRepl == (1))) {
              (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((4)));
            } else {
              if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_prefTypeRepl == (2))) {
                (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((18)));
              }
            }
          } else {
            if (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_S) || (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_SS))) {
              if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_prefTypeRepl == (1))) {
                (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((5)));
              } else {
                if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_prefTypeRepl == (2))) {
                  (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((19)));
                }
              }
            }
          }
        } else {
          if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETX)) {
            if (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_M) || (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_MT))) {
              if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_prefTypeRepl == (1))) {
                (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((6)));
              } else {
                if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_prefTypeRepl == (2))) {
                  (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((20)));
                }
              }
            } else {
              if (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_S) || (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_SS))) {
                if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_prefTypeRepl == (1))) {
                  (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((7)));
                } else {
                  if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_prefTypeRepl == (2))) {
                    (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((21)));
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

/** \brief */
void L2Cache_Controller::jjj_statsPrefetchLocal4(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefetch == PrefetchBit_L2_HW)) {
      if (((((*in_msg_ptr)).m_Type == CoherenceRequestType_GET_INSTR) || (((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS))) {
        (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((11)));
      } else {
        if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETX)) {
          (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((12)));
        }
      }
    }
  }
}

/** \brief */
void L2Cache_Controller::jjj_statsPrefetchLocal5(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefetch == PrefetchBit_L2_HW)) {
      if (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prevSharers).isElement(((*in_msg_ptr)).m_RequestorMachId))) {
        (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((13)));
      } else {
        (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((14)));
      }
    }
  }
}

/** \brief */
void L2Cache_Controller::jjj_statsPrefetchLocal6(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefetch == PrefetchBit_L2_HW)) {
      if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefDWG && (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prevOwner == ((*in_msg_ptr)).m_RequestorMachId))) {
        (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((15)));
      } else {
        (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((16)));
      }
    }
  }
}

/** \brief */
void L2Cache_Controller::jjj_statsPrefetchLocal7(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefetch == PrefetchBit_L2_HW)) {
    (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((17)));
  }
}

/** \brief */
void L2Cache_Controller::jjj_statsPrefetchLocal8(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).wasTagPresent(addr))) {
      if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_prefetch == PrefetchBit_L2_HW)) {
        if (((((*in_msg_ptr)).m_Type == CoherenceRequestType_GET_INSTR) || (((*in_msg_ptr)).m_Type == CoherenceRequestType_GETS))) {
          if (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_M) || (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_MT))) {
            (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((18)));
          } else {
            if (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_S) || (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_SS))) {
              (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((19)));
            }
          }
        } else {
          if ((((*in_msg_ptr)).m_Type == CoherenceRequestType_GETX)) {
            if (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_M) || (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_MT))) {
              (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((20)));
            } else {
              if (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_S) || (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookupPast(addr))).m_PrevLocalCacheState == L2Cache_State_L2_SS))) {
                (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((21)));
              }
            }
          }
        }
      }
    }
  }
}

/** \brief anotamos que hemos hecho Downgrade por una prebœsqueda externa*/
void L2Cache_Controller::jjj_noteDWG(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefDWG = (true);
  }
}

/** \brief comprobamos si fuimos degradados por una prebusqueda cuando fallamos en escritura*/
void L2Cache_Controller::jjj_checkDWG(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_forwardedRequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefetch == PrefetchBit_L2_HW)) {
      if (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefDWG) {
        if ((((*in_msg_ptr)).m_RequestorMachId == ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prevOwner)) {
          (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((8)));
        } else {
          (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).stats((9)));
        }
      }
    }
  }
}

/** \brief Record coreID that made the prefetch*/
void L2Cache_Controller::jjj_recordCoreID(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_prefetchQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_owner = ((*in_msg_ptr)).m_coreID;
    ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_epoch = ((*in_msg_ptr)).m_epoch;
    ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(addr))).m_prefetch = PrefetchBit_L2_HW;
  }
}

/** \brief */
void L2Cache_Controller::jx_recycleRequest(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    {
      RequestMsg out_msg;
      out_msg = (*in_msg_ptr);
      ((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).enqueue(out_msg, RECYCLE_LATENCY);
    }
  }
}

/** \brief */
void L2Cache_Controller::jj_addAccess(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
}

/** \brief */
void L2Cache_Controller::jj_removeAccess(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
}

/** \brief */
void L2Cache_Controller::jjj_prefetchPC(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_prefetchQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).getWay(addr)) == (0))) {
      ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_PC = ((*in_msg_ptr)).m_ProgramCounter;
      ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_ZeroBit = (false);
      ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_prefetch = PrefetchBit_L2_HW;
      (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).issued(((*in_msg_ptr)).m_ProgramCounter));
    }
  }
}

/** \brief */
void L2Cache_Controller::jjj_hitOnPrefetchedWay0(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    if (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).getWay(addr)) == (0))) {
      (((*(m_chip_ptr->m_L2Cache_prefetcher_vec[m_version]))).hitOnPref(((*in_msg_ptr)).m_ProgramCounter));
    }
  }
}

/** \brief */
void L2Cache_Controller::jjj_keepReuseL1(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_reuseL1 == (0))) {
    {
      const RequestMsg* in_msg_ptr;
      in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
      assert(in_msg_ptr != NULL);
      ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_reuseL1 = ((*in_msg_ptr)).m_reuse;
    }
  }
}

/** \brief */
void L2Cache_Controller::jjj_keepReuseL1a(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_reuseL1 == (0))) {
    {
      const ResponseMsg* in_msg_ptr;
      in_msg_ptr = dynamic_cast<const ResponseMsg*>(((*(m_chip_ptr->m_L2Cache_responseToL2Cache_vec[m_version]))).peek());
      assert(in_msg_ptr != NULL);
      ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_reuseL1 = ((*in_msg_ptr)).m_reuse;
    }
  }
}

/** \brief set the reused bit*/
void L2Cache_Controller::jsr_setReused(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if (((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_reused) {
    ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_reused2 = (true);
  } else {
    ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_reused = (true);
    (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).addReused(addr));
  }
}

/** \brief set the MRU entry in replacement if flag is set*/
void L2Cache_Controller::j_set_setMRU(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  if (((mruInRepl()) == (1))) {
  }
}

/** \brief store the PC of the instruction that load the line*/
void L2Cache_Controller::jjpc_savePC(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_PC = ((*in_msg_ptr)).m_ProgramCounter;
  }
}

/** \brief */
void L2Cache_Controller::jjit_initialTouch(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).initialTouch(addr, (L1CacheMachIDToProcessorNum(((*in_msg_ptr)).m_RequestorMachId))));
  }
}

/** \brief */
void L2Cache_Controller::fjj_insertionDataArray(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_L1RequestToL2Cache_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_posFIFO = (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).insertionFIFO(addr));
  }
}

/** \brief */
void L2Cache_Controller::fjjb_insertionDataArrayFromRepl(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  {
    const RequestMsg* in_msg_ptr;
    in_msg_ptr = dynamic_cast<const RequestMsg*>(((*(m_chip_ptr->m_L2Cache_dataArrayReplQueue_vec[m_version]))).peek());
    assert(in_msg_ptr != NULL);
    ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(addr))).m_posFIFO = (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).insertionFIFO(addr));
  }
}

/** \brief */
void L2Cache_Controller::fjj_removeDataArray(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1900: ", addr);
;
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1901: ", m_chip_ptr->getID());
;
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:1902: ", (L2Cache_getState(addr)));
;
  (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).evictFIFO(addr));
}

/** \brief Pop incoming data replacement request queue*/
void L2Cache_Controller::fl_popDataReplQueue(const Address& addr)
{
  DEBUG_MSG(GENERATED_COMP, HighPrio,"executing");
  (profileMsgDelay((2), (((*(m_chip_ptr->m_L2Cache_dataArrayReplQueue_vec[m_version]))).dequeue_getDelayCycles())));
}

