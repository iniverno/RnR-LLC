/** \file AccessPermission.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef AccessPermission_H
#define AccessPermission_H

#include "Global.h"

/** \enum AccessPermission
  * \brief ...
  */
enum AccessPermission {
  AccessPermission_FIRST,
  AccessPermission_Busy = AccessPermission_FIRST,  /**< No Read or Write */
  AccessPermission_Read_Only,  /**< Read Only */
  AccessPermission_Read_Write,  /**< Read/Write */
  AccessPermission_Invalid,  /**< Invalid */
  AccessPermission_NotPresent,  /**< NotPresent */
  AccessPermission_OnHold,  /**< Holding a place in dnuca cache */
  AccessPermission_ReadUpgradingToWrite,  /**< Read only, but trying to get Read/Write */
  AccessPermission_Stale,  /**< local L1 has a modified copy, assume L2 copy is stale data */
  AccessPermission_NUM
};
AccessPermission string_to_AccessPermission(const string& str);
string AccessPermission_to_string(const AccessPermission& obj);
AccessPermission &operator++( AccessPermission &e);
ostream& operator<<(ostream& out, const AccessPermission& obj);

#endif // AccessPermission_H
