/** \file L1Cache_Event.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef L1Cache_Event_H
#define L1Cache_Event_H

#include "Global.h"

/** \enum L1Cache_Event
  * \brief Cache events
  */
enum L1Cache_Event {
  L1Cache_Event_FIRST,
  L1Cache_Event_Load = L1Cache_Event_FIRST,  /**< Load request from the home processor */
  L1Cache_Event_Ifetch,  /**< I-fetch request from the home processor */
  L1Cache_Event_Store,  /**< Store request from the home processor */
  L1Cache_Event_L1_INV,  /**< L1 Invalidation of M data */
  L1Cache_Event_L1_INV_S,  /**< L1 Invalidation of S data */
  L1Cache_Event_L1_INV_P,  /**< L1 Invalidation of M data */
  L1Cache_Event_L1_INV_S_P,  /**< L1 Invalidation of S data */
  L1Cache_Event_L1_DownGrade,  /**< L2 cache forces an L1 cache in M to downgrade to S and writeback result */
  L1Cache_Event_L1_Data,  /**< Data in response to an L1 request, transistion to M or S depending on request */
  L1Cache_Event_L1_Data_S,  /**< Data in response to an L1 request, write data then transistion to S */
  L1Cache_Event_L1_Data_I,  /**< Data in response to an L1 request, write data then transistion to I */
  L1Cache_Event_L1_PutAck,  /**< PutS or PutX ack from L2 */
  L1Cache_Event_L1_Replacement,  /**< L1 Replacement */
  L1Cache_Event_L15_Replacement,  /**< L15 Replacement */
  L1Cache_Event_L1_WriteBack,  /**< on-chip L1 cache must write back to shared L2 */
  L1Cache_Event_NUM
};
L1Cache_Event string_to_L1Cache_Event(const string& str);
string L1Cache_Event_to_string(const L1Cache_Event& obj);
L1Cache_Event &operator++( L1Cache_Event &e);
ostream& operator<<(ostream& out, const L1Cache_Event& obj);

#endif // L1Cache_Event_H
