/** \file L2Cache_State.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef L2Cache_State_H
#define L2Cache_State_H

#include "Global.h"

/** \enum L2Cache_State
  * \brief L2 Cache states
  */
enum L2Cache_State {
  L2Cache_State_FIRST,
  L2Cache_State_L2_NP = L2Cache_State_FIRST,  /**< Not present in either cache */
  L2Cache_State_L2_I,  /**< L2 cache entry Idle */
  L2Cache_State_L2_S,  /**< L2 cache entry Shared, not present in any local L1s */
  L2Cache_State_L2_O,  /**< L2 cache entry Owned, not present in any local L1s */
  L2Cache_State_L2_M,  /**< L2 cache entry Modified, not present in any L1s */
  L2Cache_State_L2_SS,  /**< L2 cache entry Shared, also present in one or more L1s */
  L2Cache_State_L2_SO,  /**< L2 cache entry Owned, also present in one or more L1s or ext L2s */
  L2Cache_State_L2_MT,  /**< L2 cache entry Modified in a local L1, assume L2 copy stale */
  L2Cache_State_L2_IS,  /**< L2 idle, issued GETS, have not seen response yet */
  L2Cache_State_L2_IPS,  /**< L2 idle, issued read prefetch, have not seen response yet */
  L2Cache_State_L2_IPX,  /**< L2 idle, issued write prefetch, have not seen response yet */
  L2Cache_State_L2_IPXZ,  /**< L2 idle, issued write prefetch, saw a L1_GETX, have not seen data for PREFETCH yet */
  L2Cache_State_L2_ISZ,  /**< L2 idle, issued GETS, saw a L1_GETX, have not seen data for GETS yet */
  L2Cache_State_L2_ISI,  /**< L2 idle, issued GETS, saw INV, have not seen data for GETS yet */
  L2Cache_State_L2_IMV,  /**< L2 idle, issued GETX, valid int L1, have not seen response(s) yet */
  L2Cache_State_L2_MV,  /**< L2 modified, a valid old L1 copy exist, external world gave write permission */
  L2Cache_State_L2_IM,  /**< L2 idle, issued GETX, no valid int L1, have not seen response(s) yet */
  L2Cache_State_L2_IMO,  /**< L2 idle, issued GETX, saw forwarded GETS */
  L2Cache_State_L2_IMI,  /**< L2 idle, issued GETX, saw forwarded GETX */
  L2Cache_State_L2_IMZ,  /**< L2 idle, issued GETX, saw another L1_GETX */
  L2Cache_State_L2_IMOI,  /**< L2 idle, issued GETX, saw GETS, saw forwarded GETX */
  L2Cache_State_L2_IMOZ,  /**< L2 idle, issued GETX, saw GETS, then a L1_GETX */
  L2Cache_State_L2_SIC,  /**< L2 shared, L2_INV, valid L1 copies exist, issued invalidates, have not seen responses yet */
  L2Cache_State_L2_SIV,  /**< L2 shared, L2_Replacement, valid L1 copies exist, issued invalidates, have not seen responses yet */
  L2Cache_State_L2_PSIV,  /**< L2 shared, L2_Replacement, valid L1 copies exist, issued invalidates, have not seen responses yet */
  L2Cache_State_L2_MIV,  /**< L2 modified, a valid L1 copy exist, issued forced writeback, have not seen the response yet */
  L2Cache_State_L2_PMIV,  /**< L2 modified, a valid L1 copy exist, issued forced writeback, have not seen the response yet */
  L2Cache_State_L2_MIN,  /**< L2 modified, no valid L1 copies, issued PUTX, have not seen response yet */
  L2Cache_State_L2_PMIN,  /**< L2 modified, no valid L1 copies, issued PUTX, have not seen response yet */
  L2Cache_State_L2_MIC,  /**< L2 modified, a valid L1 copy exist, issued forced writeback, have not seen the response yet */
  L2Cache_State_L2_MIT,  /**< L2 modified, a valid L1 copy exist, saw L1_GETX, issued INV, have not seen the response yet */
  L2Cache_State_L2_MO,  /**< L2 modified, a valid L1 copy exist, issued downgrade request, have not seen response yet */
  L2Cache_State_L2_MOIC,  /**< L2 modified, a valid L1 copy exist, issued downgrade request, saw INV, have not seen response yet */
  L2Cache_State_L2_MOICR,  /**< L2 modified, a valid L1 copy exist, issued invalidate request, saw INV, have not seen response yet */
  L2Cache_State_L2_MOZ,  /**< L2 modified, a valid L1 copy exist, issued downgrade request, saw L1_GETX, have not seen response yet */
  L2Cache_State_L2_OIV,  /**< L2 owned, valid L1 copies exist, issued invalidates, have not seen responses yet from L1s */
  L2Cache_State_L2_POIV,  /**< L2 owned, valid L1 copies exist, issued invalidates, have not seen responses yet from L1s */
  L2Cache_State_L2_OIN,  /**< L2 owned, no valid L1 copies, issued PUTX, have not seen response yet from dir */
  L2Cache_State_L2_POIN,  /**< L2 owned, no valid L1 copies, issued PUTX, have not seen response yet from dir */
  L2Cache_State_L2_OIC,  /**< L2 owned, valid L1 copies exist, issued invalidates, have not seen responses yet from L1s */
  L2Cache_State_L2_OMV,  /**< L2 owned and valid L1 copies, issued GETX and invalidates, have not seen responses yet */
  L2Cache_State_L2_OM,  /**< L2 owned and no valid L1 copies, issued GETX, have not seen response yet */
  L2Cache_State_L2_SM,  /**< Desde S habiendo recibido una prebœsqueda en escritura */
  L2Cache_State_L2_SSM,  /**< Desde SS habiendo recibido una preb en escritura */
  L2Cache_State_L2_SSMV,  /**< Desde SS habiendo recibido una preb en escritura */
  L2Cache_State_L2_IPI,  /**< Desde SS habiendo recibido una preb en escritura */
  L2Cache_State_L2_IPSS,  /**< Desde L2_IPS habiendo recibido una petici—n de L1 */
  L2Cache_State_L2_INRM,  /**<  */
  L2Cache_State_L2_INRMZ,  /**<  */
  L2Cache_State_L2_NRMIT,  /**<  */
  L2Cache_State_L2_NRMIV,  /**<  */
  L2Cache_State_L2_INRS,  /**<  */
  L2Cache_State_L2_INRSZ,  /**<  */
  L2Cache_State_L2_INRSI,  /**<  */
  L2Cache_State_L2_NRSIV,  /**<  */
  L2Cache_State_L2_NRS,  /**<  */
  L2Cache_State_L2_NRSS,  /**<  */
  L2Cache_State_L2_NRMT,  /**<  */
  L2Cache_State_NUM
};
L2Cache_State string_to_L2Cache_State(const string& str);
string L2Cache_State_to_string(const L2Cache_State& obj);
L2Cache_State &operator++( L2Cache_State &e);
ostream& operator<<(ostream& out, const L2Cache_State& obj);

#endif // L2Cache_State_H
