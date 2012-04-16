/** \file Directory_State.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef Directory_State_H
#define Directory_State_H

#include "Global.h"

/** \enum Directory_State
  * \brief Directory states
  */
enum Directory_State {
  Directory_State_FIRST,
  Directory_State_NP = Directory_State_FIRST,  /**< Not present */
  Directory_State_I,  /**< Idle */
  Directory_State_S,  /**< Shared */
  Directory_State_O,  /**< Owned */
  Directory_State_M,  /**< Modified */
  Directory_State_OO,  /**< transient state of O->GetS/GetInstr->O */
  Directory_State_OM,  /**< transient state of O->GetX->M */
  Directory_State_MO,  /**< transient state of M->GetS/GetInstr->O */
  Directory_State_MM,  /**< transient state of M->GetX->M */
  Directory_State_MD,  /**<  */
  Directory_State_SD,  /**<  */
  Directory_State_MPD,  /**<  */
  Directory_State_SPD,  /**<  */
  Directory_State_NUM
};
Directory_State string_to_Directory_State(const string& str);
string Directory_State_to_string(const Directory_State& obj);
Directory_State &operator++( Directory_State &e);
ostream& operator<<(ostream& out, const Directory_State& obj);

#endif // Directory_State_H
