/** \file L2Cache_Event.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef L2Cache_Event_H
#define L2Cache_Event_H

#include "Global.h"

/** \enum L2Cache_Event
  * \brief L2 Cache events
  */
enum L2Cache_Event {
  L2Cache_Event_FIRST,
  L2Cache_Event_L1_GET_INSTR = L2Cache_Event_FIRST,  /**< a L1I GET INSTR request for a block maped to us */
  L2Cache_Event_L1_GETS,  /**< a L1D GETS request for a block maped to us */
  L2Cache_Event_L1_GETX,  /**< a L1D GETX request for a block maped to us */
  L2Cache_Event_L1_UPGRADE,  /**< a L1D UPGRADE request for a block maped to us */
  L2Cache_Event_L1_UPGRADE_no_others,  /**< a L1D UPGRADE request for a block maped to us, requestor is the only on-chip sharer */
  L2Cache_Event_L1_PUTX,  /**< a L1D PUTX request for a block maped to us (L1 replacement of a modified block) */
  L2Cache_Event_L1_PUTX_last,  /**< a L1D PUTX request for a block maped to us (L1 replacement of a modified block) last sharer */
  L2Cache_Event_L1_PUTX_old,  /**< an old L1D PUTX request for a block maped to us (L1 replacement of a modified block) */
  L2Cache_Event_L1_PUTS,  /**< a L1 replacement of a shared block */
  L2Cache_Event_L1_PUTS_last,  /**< a L1 replacement of the last local L1 shared block */
  L2Cache_Event_L1_PUTS_old,  /**< an old L1 replacement of a shared block */
  L2Cache_Event_PrefetchS,  /**< Una prebœsqueda de lectura */
  L2Cache_Event_PrefetchX,  /**< Una prebœsqueda de escritura */
  L2Cache_Event_Proc_int_ack,  /**< Ack from on-chip L1 Cache */
  L2Cache_Event_Proc_last_int_ack,  /**< Last on-chip L1 Cache ack */
  L2Cache_Event_Data_int_ack,  /**< Received modified data from L1 now proceed in handling miss */
  L2Cache_Event_Forwarded_GETS,  /**< Directory forwards Inter-chip GETS to us */
  L2Cache_Event_Forwarded_GET_INSTR,  /**< Inter-chip Forwarded GETINSTR */
  L2Cache_Event_Forwarded_GETX,  /**< Directory forwards Inter-chip GETX to us */
  L2Cache_Event_L2_INV,  /**< L2 Invalidation initiated from other L2 */
  L2Cache_Event_Forwarded_PREFS,  /**< Directory forwards Inter-L2 read PREF to us */
  L2Cache_Event_Forwarded_PREFX,  /**< Directory forwards Inter-L2 read PREF to us */
  L2Cache_Event_L2_PrefetchS_Replacement,  /**< L2 read prefetch that forces a Replacement */
  L2Cache_Event_L2_PrefetchX_Replacement,  /**< L2 write prefetch that forces a Replacement */
  L2Cache_Event_L2_Replacement,  /**< L2 Replacement */
  L2Cache_Event_Proc_ext_ack,  /**< Ack from off-chip */
  L2Cache_Event_Proc_last_ext_ack,  /**< Last off-chip ack */
  L2Cache_Event_Data_ext_ack_0,  /**< Data with ack count = 0 */
  L2Cache_Event_PrefData_ext_ack_0,  /**< Data with ack count = 0 */
  L2Cache_Event_Data_ext_ack_not_0,  /**< Data with ack count != 0 (but haven't seen all acks first */
  L2Cache_Event_Data_ext_ack_not_0_last,  /**< Data with ack count != 0 after having received all acks */
  L2Cache_Event_Dir_WB_ack,  /**< Writeback ack from dir */
  L2Cache_Event_Dir_exe_ack,  /**< Directory tells us we already have exclusive permission, go directly to MT state */
  L2Cache_Event_NUM
};
L2Cache_Event string_to_L2Cache_Event(const string& str);
string L2Cache_Event_to_string(const L2Cache_Event& obj);
L2Cache_Event &operator++( L2Cache_Event &e);
ostream& operator<<(ostream& out, const L2Cache_Event& obj);

#endif // L2Cache_Event_H
