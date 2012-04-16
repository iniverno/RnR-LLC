/** \file L2Cache.h
  * 
  * Auto generated C++ code started by symbols/StateMachine.C:252
  * Created by slicc definition of Module "MOSI Directory L2 Cache CMP"
  */

#ifndef L2Cache_CONTROLLER_H
#define L2Cache_CONTROLLER_H

#include "Global.h"
#include "Consumer.h"
#include "TransitionResult.h"
#include "Types.h"
#include "L2Cache_Profiler.h"

extern stringstream L2Cache_transitionComment;
class L2Cache_Controller : public Consumer {
#ifdef CHECK_COHERENCE
  friend class Chip;
#endif /* CHECK_COHERENCE */
public:
  L2Cache_Controller(Chip* chip_ptr, int version);
  void print(ostream& out) const;
  void wakeup();
  static void dumpStats(ostream& out) { s_profiler.dumpStats(out); }
  static void clearStats() { s_profiler.clearStats(); }
private:
  TransitionResult doTransition(L2Cache_Event event, L2Cache_State state, const Address& addr);  // in L2Cache_Transitions.C
  TransitionResult doTransitionWorker(L2Cache_Event event, L2Cache_State state, L2Cache_State& next_state, const Address& addr);  // in L2Cache_Transitions.C
  Chip* m_chip_ptr;
  NodeID m_id;
  NodeID m_version;
  MachineID m_machineID;
  static L2Cache_Profiler s_profiler;
  // Internal functions
  L2Cache_Entry& L2Cache_getL2CacheEntry(Address param_addr);
  void L2Cache_changeL2Permission(Address param_addr, AccessPermission param_permission);
  string L2Cache_getCoherenceRequestTypeStr(CoherenceRequestType param_type);
  bool L2Cache_isL2CacheTagPresent(Address param_addr);
  bool L2Cache_isOneSharerLeft(Address param_addr, MachineID param_requestor);
  bool L2Cache_isSharer(Address param_addr, MachineID param_requestor);
  void L2Cache_addSharer(Address param_addr, MachineID param_requestor);
  L2Cache_State L2Cache_getState(Address param_addr);
  string L2Cache_getStateStr(Address param_addr);
  void L2Cache_setState(Address param_addr, L2Cache_State param_state);
  L2Cache_Event L2Cache_L1Cache_request_type_to_event(CoherenceRequestType param_type, Address param_addr, MachineID param_requestor);
  // Actions
/** \brief Issue prefetch*/
  void ja_issuePREFETCH(const Address& addr);
/** \brief send upgrade prefetch*/
  void t_sendUpgradePrefetch(const Address& addr);
/** \brief Issue GETS*/
  void a_issueGETS(const Address& addr);
/** \brief Issue GETX*/
  void b_issueGETX(const Address& addr);
/** \brief Issue GETINSTR*/
  void f_issueGETINSTR(const Address& addr);
/** \brief Issue PUTX*/
  void d_issuePUTX(const Address& addr);
/** \brief Send FinalAck to dir if this is response to 3-hop xfer*/
  void c_finalAckToDirIfNeeded(const Address& addr);
/** \brief */
  void n_sendFinalAckIfThreeHop(const Address& addr);
/** \brief */
  void mm_rememberIfFinalAckNeeded(const Address& addr);
/** \brief If not prefetch, notify sequencer the load completed.*/
  void h_issueLoadHit(const Address& addr);
/** \brief If not prefetch, notify sequencer the load completed.*/
  void oo_issueLoadHitInv(const Address& addr);
/** \brief If not prefetch, issue store hit message to local L1 requestor*/
  void hh_issueStoreHit(const Address& addr);
/** \brief If not prefetch, issue store hit message to local L1 requestor*/
  void pp_issueStoreHitInv(const Address& addr);
/** \brief If not prefetch, issue store hit message to local L1 requestor*/
  void cc_issueStoreHitDG(const Address& addr);
/** \brief send acknowledgement of an L1 replacement*/
  void w_sendPutAckToL1Cache(const Address& addr);
/** \brief Send data from cache to all GetS IDs*/
  void ee_dataFromL2CacheToGetSIDs(const Address& addr);
/** \brief Send data from cache to GetS ForwardIDs*/
  void bb_dataFromL2CacheToGetSForwardIDs(const Address& addr);
/** \brief Send data from cache to GetS ForwardIDs*/
  void bb_dataFromL2CacheToGetSForwardIDsPref(const Address& addr);
/** \brief Send data from cache to GetX ForwardID*/
  void gg_dataFromL2CacheToGetXForwardID(const Address& addr);
/** \brief Send data from cache to GetX ForwardID*/
  void gg_dataFromL2CacheToGetXForwardIDPref(const Address& addr);
/** \brief Send data from cache to requestor*/
  void e_dataFromL2CacheToL2Requestor(const Address& addr);
/** \brief Send data from cache to L1 requestor*/
  void k_dataFromL2CacheToL1Requestor(const Address& addr);
/** \brief Allocate TBE for internal/external request(isPrefetch=0, number of invalidates=0)*/
  void i_allocateTBE(const Address& addr);
/** \brief Allocate Pref TBE for internal/external request(isPrefetch=0, number of invalidates=0)*/
  void i_allocatePrefTBE(const Address& addr);
/** \brief marca en el bloque de cache  que no nos expuls— una prebusqueda*/
  void ji_marcaRepl(const Address& addr);
/** \brief marca en el bloque de cache  que nos expuls— una preb en lectura*/
  void jis_marcaRepl(const Address& addr);
/** \brief marca en el bloque de cache  que nos expuls— una preb en escritura*/
  void jix_marcaRepl(const Address& addr);
/** \brief Deallocate external TBE*/
  void s_deallocateTBE(const Address& addr);
/** \brief Deallocate external PrefTBE*/
  void s_deallocatePrefTBE(const Address& addr);
/** \brief */
  void jj_deactiveBloom(const Address& addr);
/** \brief Pop incoming L1 request queue*/
  void jj_popL1RequestQueue2(const Address& addr);
/** \brief Pop incoming L1 request queue*/
  void jj_popL1RequestQueue(const Address& addr);
/** \brief Pop incoming forwarded request queue*/
  void l_popForwardedRequestQueue(const Address& addr);
/** \brief Pop Incoming Response queue*/
  void o_popIncomingResponseQueue(const Address& addr);
/** \brief Pop Incoming pref Response queue*/
  void jo_popIncomingPrefResponseQueue(const Address& addr);
/** \brief Pop prefetch request queue*/
  void jjj_popPrefetchQueue(const Address& addr);
/** \brief Pop prefetch request queue*/
  void jjj_popResponeDramQueue(const Address& addr);
/** \brief Add number of pending acks to TBE*/
  void p_addNumberOfPendingExtAcks(const Address& addr);
/** \brief Decrement number of pending ext invalidations by one*/
  void q_decrementNumberOfPendingExtAcks(const Address& addr);
/** \brief Decrement number of pending int invalidations by one*/
  void r_decrementNumberOfPendingIntAcks(const Address& addr);
/** \brief Decrement number of pending int invalidations by one*/
  void r_decrementNumberOfPendingIntAcksPrefTBE(const Address& addr);
/** \brief Send ack to invalidator*/
  void t_sendAckToInvalidator(const Address& addr);
/** \brief Write data from response queue to cache*/
  void ju_writePrefetchDataFromResponseQueueToL2Cache(const Address& addr);
/** \brief Write data from response queue to cache*/
  void u_writeDataFromResponseQueueToL2Cache(const Address& addr);
/** \brief Write data from response queue to cache*/
  void jm_writeDataFromResponseQueueToL2Cache(const Address& addr);
/** \brief Write data from response queue to cache*/
  void m_writeDataFromRequestQueueToL2Cache(const Address& addr);
/** \brief Copy data from cache to TBE*/
  void x_copyDataFromL2CacheToTBE(const Address& addr);
/** \brief Copy data from cache to Pref TBE*/
  void x_copyDataFromL2CacheToPrefTBE(const Address& addr);
/** \brief Send data from TBE to requestor*/
  void y_dataFromTBEToRequestor(const Address& addr);
/** \brief Send ack to invalidator*/
  void zz_sendAckToQueuedInvalidator(const Address& addr);
/** \brief Stall*/
  void z_stall(const Address& addr);
/** \brief Record Invalidator for future response*/
  void yy_recordInvalidatorID(const Address& addr);
/** \brief Record forwarded GetS for future forwarding*/
  void dd_recordGetSForwardID(const Address& addr);
/** \brief Record forwarded L1 GetS for load response*/
  void ss_recordGetSL1ID(const Address& addr);
/** \brief Record forwarded GetX and ack count for future forwarding*/
  void ii_recordGetXForwardID(const Address& addr);
/** \brief Record L1 GetX for store response*/
  void xx_recordGetXL1ID(const Address& addr);
/** \brief set the MRU entry*/
  void set_setMRU(const Address& addr);
/** \brief set the last touch*/
  void setTimeLast(const Address& addr);
/** \brief Set number of pending acks equal to number of sharers*/
  void bbb_setPendingIntAcksToSharers(const Address& addr);
/** \brief Set number of pending acks equal to number of sharers*/
  void bbb_setPendingIntAcksToSharersPref(const Address& addr);
/** \brief Set number of pending acks equal to one*/
  void ddd_setPendingIntAcksToOne(const Address& addr);
/** \brief Set number of pending acks equal to number of sharers minus one*/
  void ccc_setPendingIntAcksMinusOne(const Address& addr);
/** \brief Set L2 cache tag equal to tag of block B.*/
  void qq_allocateL2CacheBlock(const Address& addr);
/** \brief Deallocate L2 cache block.  Sets the cache to not present, allowing a replacement in parallel with a fetch.*/
  void rr_deallocateL2CacheBlock(const Address& addr);
/** \brief Profile the demand miss*/
  void uu_profileMiss(const Address& addr);
/** \brief Profile an access*/
  void uu_profileAccess(const Address& addr);
/** \brief Profile this transition at the L2 because Dir won't see the request*/
  void ww_profileMissNoDir(const Address& addr);
/** \brief invalidate the L1 M copy*/
  void v_issueInvalidateIntL1copyRequest(const Address& addr);
/** \brief invalidate all L1 S copies*/
  void tt_issueSharedInvalidateIntL1copiesRequest(const Address& addr);
/** \brief invalidate the L1 M copy*/
  void v_issueInvalidatePIntL1copyRequest(const Address& addr);
/** \brief invalidate all L1 S copies*/
  void tt_issueSharedInvalidatePIntL1copiesRequest(const Address& addr);
/** \brief invalidate other L1 copies not the local requestor*/
  void vv_issueInvalidateOtherIntL1copiesRequest(const Address& addr);
/** \brief DownGrade L1 copy*/
  void g_issueDownGradeIntL1copiesRequest(const Address& addr);
/** \brief Add L1 sharer to list*/
  void nn_addSharer(const Address& addr);
/** \brief Remove L1 Request sharer from list*/
  void kk_removeRequestSharer(const Address& addr);
/** \brief Remove L1 Response sharer from list*/
  void aa_removeResponseSharer(const Address& addr);
/** \brief Remove all L1 sharers from list*/
  void ll_clearSharers(const Address& addr);
/** \brief mandamos al prefetcher la direcci—n del fallo*/
  void jaa_missToPrefetch(const Address& addr);
/** \brief Marcamos como usado (y mandamos al prefetcher la direcci—n del fallo)*/
  void jab_firstUseToPrefetcherS(const Address& addr);
/** \brief Marcamos como usado (y mandamos al prefetcher la direcci—n del fallo)*/
  void jab_firstUseToPrefetcherX(const Address& addr);
/** \brief preb UTIL*/
  void jjj_statsPrefetchLocal(const Address& addr);
/** \brief preb UTIL de cada core*/
  void jjj_statsPrefetchLocalS(const Address& addr);
/** \brief preb INUTIL*/
  void jjj_statsPrefetchLocal2(const Address& addr);
/** \brief preb INUTIL de cada core*/
  void jjj_statsPrefetchLocalS2(const Address& addr);
/** \brief */
  void jjj_statsPrefetchLocal3(const Address& addr);
/** \brief */
  void jjj_statsPrefetchLocal4(const Address& addr);
/** \brief */
  void jjj_statsPrefetchLocal5(const Address& addr);
/** \brief */
  void jjj_statsPrefetchLocal6(const Address& addr);
/** \brief */
  void jjj_statsPrefetchLocal7(const Address& addr);
/** \brief */
  void jjj_statsPrefetchLocal8(const Address& addr);
/** \brief anotamos que hemos hecho Downgrade por una prebœsqueda externa*/
  void jjj_noteDWG(const Address& addr);
/** \brief comprobamos si fuimos degradados por una prebusqueda cuando fallamos en escritura*/
  void jjj_checkDWG(const Address& addr);
/** \brief Record coreID that made the prefetch*/
  void jjj_recordCoreID(const Address& addr);
/** \brief */
  void jx_recycleRequest(const Address& addr);
/** \brief */
  void jj_addAccess(const Address& addr);
/** \brief */
  void jj_removeAccess(const Address& addr);
/** \brief */
  void jjj_prefetchPC(const Address& addr);
/** \brief */
  void jjj_hitOnPrefetchedWay0(const Address& addr);
/** \brief */
  void jjj_keepReuseL1(const Address& addr);
/** \brief */
  void jjj_keepReuseL1a(const Address& addr);
/** \brief set the reused bit*/
  void jsr_setReused(const Address& addr);
/** \brief set the MRU entry in replacement if flag is set*/
  void j_set_setMRU(const Address& addr);
/** \brief store the PC of the instruction that load the line*/
  void jjpc_savePC(const Address& addr);
/** \brief */
  void jjit_initialTouch(const Address& addr);
/** \brief */
  void fjj_insertionDataArray(const Address& addr);
/** \brief */
  void fjjb_insertionDataArrayFromRepl(const Address& addr);
/** \brief */
  void fjj_removeDataArray(const Address& addr);
/** \brief Pop incoming data replacement request queue*/
  void fl_popDataReplQueue(const Address& addr);
};
#endif // L2Cache_CONTROLLER_H
