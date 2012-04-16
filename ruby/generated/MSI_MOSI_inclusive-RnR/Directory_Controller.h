/** \file Directory.h
  * 
  * Auto generated C++ code started by symbols/StateMachine.C:252
  * Created by slicc definition of Module "MOSI Directory Optimized"
  */

#ifndef Directory_CONTROLLER_H
#define Directory_CONTROLLER_H

#include "Global.h"
#include "Consumer.h"
#include "TransitionResult.h"
#include "Types.h"
#include "Directory_Profiler.h"

extern stringstream Directory_transitionComment;
class Directory_Controller : public Consumer {
#ifdef CHECK_COHERENCE
  friend class Chip;
#endif /* CHECK_COHERENCE */
public:
  Directory_Controller(Chip* chip_ptr, int version);
  void print(ostream& out) const;
  void wakeup();
  static void dumpStats(ostream& out) { s_profiler.dumpStats(out); }
  static void clearStats() { s_profiler.clearStats(); }
private:
  TransitionResult doTransition(Directory_Event event, Directory_State state, const Address& addr);  // in Directory_Transitions.C
  TransitionResult doTransitionWorker(Directory_Event event, Directory_State state, Directory_State& next_state, const Address& addr);  // in Directory_Transitions.C
  Chip* m_chip_ptr;
  NodeID m_id;
  NodeID m_version;
  MachineID m_machineID;
  static Directory_Profiler s_profiler;
  // Internal functions
  Directory_State Directory_getState(Address param_addr);
  string Directory_getDirStateStr(Address param_addr);
  string Directory_getRequestTypeStr(CoherenceRequestType param_type);
  void Directory_setState(Address param_addr, Directory_State param_state);
  // Actions
/** \brief Add requestor to list of sharers*/
  void a_addRequestorToSharers(const Address& addr);
/** \brief Send data to requestor*/
  void b_dataToRequestor(const Address& addr);
/** \brief Forward request to owner*/
  void d_forwardRequestToOwner(const Address& addr);
/** \brief Set owner equal to requestor*/
  void f_setOwnerToRequestor(const Address& addr);
/** \brief Clear list of sharers*/
  void g_clearSharers(const Address& addr);
/** \brief Send INVs to all sharers*/
  void h_invToSharers(const Address& addr);
/** \brief Pop incoming request queue*/
  void j_popIncomingRequestQueue(const Address& addr);
/** \brief Write PUTX/DWN data to memory*/
  void l_writeRequestDataToMemory(const Address& addr);
/** \brief Send WB_ack to requestor*/
  void n_writebackAckToRequestor(const Address& addr);
/** \brief Send EXE_ack to requestor*/
  void m_forwardExclusiveRequestToOwner(const Address& addr);
/** \brief Profile this transition.*/
  void uu_profile(const Address& addr);
/** \brief Clear owner*/
  void p_clearOwner(const Address& addr);
/** \brief Add owner to list of sharers*/
  void r_addOwnerToSharers(const Address& addr);
/** \brief Remove owner from list of sharers*/
  void t_removeOwnerFromSharers(const Address& addr);
/** \brief Remove requestor from list of sharers*/
  void u_removeRequestorFromSharers(const Address& addr);
/** \brief */
  void x_recycleRequest(const Address& addr);
/** \brief */
  void hh_popFinalAckQueue(const Address& addr);
/** \brief */
  void z_stall(const Address& addr);
/** \brief Add requestor to list of sharers*/
  void jja_addRequestorToSharers(const Address& addr);
/** \brief Send prefetched data to requestor*/
  void jjb_dataToRequestor(const Address& addr);
/** \brief Forward request to owner*/
  void jjd_forwardRequestToOwner(const Address& addr);
/** \brief Set owner equal to requestor*/
  void jjf_setOwnerToRequestor(const Address& addr);
/** \brief Clear list of sharers*/
  void jjg_clearSharers(const Address& addr);
/** \brief Send INVs to all sharers*/
  void jjh_invToSharers(const Address& addr);
/** \brief Pop incoming request queue*/
  void jjj_popIncomingRequestQueue(const Address& addr);
/** \brief Write PUTX/DWN data to memory*/
  void jjl_writeRequestDataToMemory(const Address& addr);
/** \brief Send WB_ack to requestor*/
  void jjn_writebackAckToRequestor(const Address& addr);
/** \brief Send EXE_ack to requestor*/
  void jjm_forwardExclusiveRequestToOwner(const Address& addr);
/** \brief Profile this transition.*/
  void jjuu_profile(const Address& addr);
/** \brief Clear owner*/
  void jjp_clearOwner(const Address& addr);
/** \brief Add owner to list of sharers*/
  void jjr_addOwnerToSharers(const Address& addr);
/** \brief Remove owner from list of sharers*/
  void jjt_removeOwnerFromSharers(const Address& addr);
/** \brief Remove requestor from list of sharers*/
  void jju_removeRequestorFromSharers(const Address& addr);
/** \brief */
  void jjx_recycleRequest(const Address& addr);
/** \brief */
  void jjhh_popFinalAckQueue(const Address& addr);
/** \brief */
  void j_popDramResponseQueue(const Address& addr);
/** \brief */
  void jp_popDramResponseQueue(const Address& addr);
/** \brief Send data to requestor*/
  void bb_dataToRequestor(const Address& addr);
/** \brief */
  void jp_requestToDram(const Address& addr);
/** \brief */
  void jp_ugPrefToDram(const Address& addr);
/** \brief */
  void p_requestToDram(const Address& addr);
};
#endif // Directory_CONTROLLER_H
