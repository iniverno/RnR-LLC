/** \file LockStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef LockStatus_H
#define LockStatus_H

#include "Global.h"

/** \enum LockStatus
  * \brief ...
  */
enum LockStatus {
  LockStatus_FIRST,
  LockStatus_Unlocked = LockStatus_FIRST,  /**< Lock is not held */
  LockStatus_Locked,  /**< Lock is held */
  LockStatus_NUM
};
LockStatus string_to_LockStatus(const string& str);
string LockStatus_to_string(const LockStatus& obj);
LockStatus &operator++( LockStatus &e);
ostream& operator<<(ostream& out, const LockStatus& obj);

#endif // LockStatus_H
