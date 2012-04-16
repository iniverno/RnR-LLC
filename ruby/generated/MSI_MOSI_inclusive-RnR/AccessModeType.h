/** \file AccessModeType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef AccessModeType_H
#define AccessModeType_H

#include "Global.h"

/** \enum AccessModeType
  * \brief ...
  */
enum AccessModeType {
  AccessModeType_FIRST,
  AccessModeType_SupervisorMode = AccessModeType_FIRST,  /**< Supervisor mode */
  AccessModeType_UserMode,  /**< User mode */
  AccessModeType_NUM
};
AccessModeType string_to_AccessModeType(const string& str);
string AccessModeType_to_string(const AccessModeType& obj);
AccessModeType &operator++( AccessModeType &e);
ostream& operator<<(ostream& out, const AccessModeType& obj);

#endif // AccessModeType_H
