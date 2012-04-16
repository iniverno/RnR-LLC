/** \file AccessModeType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "AccessModeType.h"

ostream& operator<<(ostream& out, const AccessModeType& obj)
{
  out << AccessModeType_to_string(obj);
  out << flush;
  return out;
}

string AccessModeType_to_string(const AccessModeType& obj)
{
  switch(obj) {
  case AccessModeType_SupervisorMode:
    return "SupervisorMode";
  case AccessModeType_UserMode:
    return "UserMode";
  default:
    ERROR_MSG("Invalid range for type AccessModeType");
    return "";
  }
}

AccessModeType string_to_AccessModeType(const string& str)
{
  if (false) {
  } else if (str == "SupervisorMode") {
    return AccessModeType_SupervisorMode;
  } else if (str == "UserMode") {
    return AccessModeType_UserMode;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type AccessModeType");
  }
}

AccessModeType& operator++( AccessModeType& e) {
  assert(e < AccessModeType_NUM);
  return e = AccessModeType(e+1);
}
