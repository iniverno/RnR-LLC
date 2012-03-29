/** \file L1Cache_State.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef L1Cache_State_H
#define L1Cache_State_H

#include "Global.h"

/** \enum L1Cache_State
  * \brief Cache states
  */
enum L1Cache_State {
  L1Cache_State_FIRST,
  L1Cache_State_NP = L1Cache_State_FIRST,  /**< Not present in either cache */
  L1Cache_State_L1_I,  /**< a L1 cache entry Idle */
  L1Cache_State_L1_S,  /**< a L1 cache entry Shared */
  L1Cache_State_L1_M,  /**< a L1 cache entry Modified */
  L1Cache_State_L1_IS,  /**< L1 idle, issued GETS, have not seen response yet */
  L1Cache_State_L1_ISI,  /**< L1 idle, issued GETS, saw INV, still waiting for data */
  L1Cache_State_L1_IM,  /**< L1 idle, issued GETX, have not seen response yet */
  L1Cache_State_L1_IMI,  /**< L1 idle, issued GETX, saw INV, still waiting for data */
  L1Cache_State_L1_IMS,  /**< L1 idle, issued GETX, saw DownGrade, still waiting for data */
  L1Cache_State_L1_IMSI,  /**< L1 idle, issued GETX, saw DownGrade, saw INV, still waiting for data */
  L1Cache_State_L1_SI,  /**< issued PUTS, waiting for response */
  L1Cache_State_L1_MI,  /**< issued PUTX, waiting for response */
  L1Cache_State_NUM
};
L1Cache_State string_to_L1Cache_State(const string& str);
string L1Cache_State_to_string(const L1Cache_State& obj);
L1Cache_State &operator++( L1Cache_State &e);
ostream& operator<<(ostream& out, const L1Cache_State& obj);

#endif // L1Cache_State_H
