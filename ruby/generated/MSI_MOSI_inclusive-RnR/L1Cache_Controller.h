/** \file L1Cache.h
  * 
  * Auto generated C++ code started by symbols/StateMachine.C:252
  * Created by slicc definition of Module "MSI Directory L1 Cache CMP"
  */

#ifndef L1Cache_CONTROLLER_H
#define L1Cache_CONTROLLER_H

#include "Global.h"
#include "Consumer.h"
#include "TransitionResult.h"
#include "Types.h"
#include "L1Cache_Profiler.h"

extern stringstream L1Cache_transitionComment;
class L1Cache_Controller : public Consumer {
#ifdef CHECK_COHERENCE
  friend class Chip;
#endif /* CHECK_COHERENCE */
public:
  L1Cache_Controller(Chip* chip_ptr, int version);
  void print(ostream& out) const;
  void wakeup();
  static void dumpStats(ostream& out) { s_profiler.dumpStats(out); }
  static void clearStats() { s_profiler.clearStats(); }
private:
  TransitionResult doTransition(L1Cache_Event event, L1Cache_State state, const Address& addr);  // in L1Cache_Transitions.C
  TransitionResult doTransitionWorker(L1Cache_Event event, L1Cache_State state, L1Cache_State& next_state, const Address& addr);  // in L1Cache_Transitions.C
  Chip* m_chip_ptr;
  NodeID m_id;
  NodeID m_version;
  MachineID m_machineID;
  static L1Cache_Profiler s_profiler;
  // Internal functions
  L1Cache_Entry& L1Cache_getL1CacheEntry(Address param_addr);
  void L1Cache_changeL1Permission(Address param_addr, AccessPermission param_permission);
  bool L1Cache_isL1CacheTagPresent(Address param_addr);
  L1Cache_State L1Cache_getState(Address param_addr);
  string L1Cache_getStateStr(Address param_addr);
  void L1Cache_setState(Address param_addr, L1Cache_State param_state);
  L1Cache_Event L1Cache_mandatory_request_type_to_event(CacheRequestType param_type);
  // Actions
/** \brief Issue GETS*/
  void a_issueGETS(const Address& addr);
/** \brief Issue GETX*/
  void b_issueGETX(const Address& addr);
/** \brief Issue GETX*/
  void c_issueUPGRADE(const Address& addr);
/** \brief Issue GETINSTR*/
  void f_issueGETINSTR(const Address& addr);
/** \brief Issue PUTX*/
  void d_issuePUTX(const Address& addr);
/** \brief Issue PUTS*/
  void q_issuePUTS(const Address& addr);
/** \brief Send data from L1 cache to L2 Cache*/
  void e_dataFromL1CacheToL2Cache(const Address& addr);
/** \brief Send data from L1_TBE to L2 Cache*/
  void f_dataFromTBEToL2Cache(const Address& addr);
/** \brief Send Invadiation ack to L2 Cache*/
  void t_sendInvAckToL2Cache(const Address& addr);
/** \brief If not prefetch, notify sequencer the load completed.*/
  void h_load_hit(const Address& addr);
/** \brief If not prefetch, notify sequencer that store completed.*/
  void hh_store_hit(const Address& addr);
/** \brief Allocate TBE (isPrefetch=0, number of invalidates=0)*/
  void i_allocateTBE(const Address& addr);
/** \brief Pop mandatory queue.*/
  void k_popMandatoryQueue(const Address& addr);
/** \brief Pop incoming request queue and profile the delay within this virtual network*/
  void l_popRequestQueue(const Address& addr);
/** \brief Pop Incoming Response queue and profile the delay within this virtual network*/
  void o_popIncomingResponseQueue(const Address& addr);
/** \brief Deallocate TBE*/
  void s_deallocateTBE(const Address& addr);
/** \brief Write data to cache*/
  void u_writeDataToL1Cache(const Address& addr);
/** \brief Copy data from cache to TBE*/
  void x_copyDataFromL1CacheToTBE(const Address& addr);
/** \brief Stall*/
  void z_stall(const Address& addr);
/** \brief Deallocate L1 cache block.  Sets the cache to not present, allowing a replacement in parallel with a fetch.*/
  void ff_deallocateL1CacheBlock(const Address& addr);
/** \brief Deallocate L15 cache block.  Sets the cache to not present, allowing a replacement in parallel with a fetch.*/
  void fff_deallocateL15CacheBlock(const Address& addr);
/** \brief Set L1 D-cache tag equal to tag of block B.*/
  void oo_allocateL1DCacheBlock(const Address& addr);
/** \brief Set L1 I-cache tag equal to tag of block B.*/
  void pp_allocateL1ICacheBlock(const Address& addr);
/** \brief Set L15cache tag equal to tag of block B.*/
  void ppp_allocateL15CacheBlockI(const Address& addr);
/** \brief Set L15cache tag equal to tag of block B.*/
  void ppp_allocateL15CacheBlockD(const Address& addr);
/** \brief */
  void jj_profilePrefInv(const Address& addr);
/** \brief Profile the demand miss*/
  void uu_profileL15Miss(const Address& addr);
/** \brief Si el bloque no est‡ en la L1D, se pone*/
  void ooo_compruebaPresenciaL1D(const Address& addr);
/** \brief Si el bloque no est‡ en la L1I, se pone*/
  void oop_compruebaPresenciaL1I(const Address& addr);
/** \brief Marca el bit de reuso en L1 o L15*/
  void jjj_actualizaReuso(const Address& addr);
};
#endif // L1Cache_CONTROLLER_H
