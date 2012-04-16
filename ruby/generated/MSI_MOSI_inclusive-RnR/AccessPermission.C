/** \file AccessPermission.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "AccessPermission.h"

ostream& operator<<(ostream& out, const AccessPermission& obj)
{
  out << AccessPermission_to_string(obj);
  out << flush;
  return out;
}

string AccessPermission_to_string(const AccessPermission& obj)
{
  switch(obj) {
  case AccessPermission_Busy:
    return "Busy";
  case AccessPermission_Read_Only:
    return "Read_Only";
  case AccessPermission_Read_Write:
    return "Read_Write";
  case AccessPermission_Invalid:
    return "Invalid";
  case AccessPermission_NotPresent:
    return "NotPresent";
  case AccessPermission_OnHold:
    return "OnHold";
  case AccessPermission_ReadUpgradingToWrite:
    return "ReadUpgradingToWrite";
  case AccessPermission_Stale:
    return "Stale";
  default:
    ERROR_MSG("Invalid range for type AccessPermission");
    return "";
  }
}

AccessPermission string_to_AccessPermission(const string& str)
{
  if (false) {
  } else if (str == "Busy") {
    return AccessPermission_Busy;
  } else if (str == "Read_Only") {
    return AccessPermission_Read_Only;
  } else if (str == "Read_Write") {
    return AccessPermission_Read_Write;
  } else if (str == "Invalid") {
    return AccessPermission_Invalid;
  } else if (str == "NotPresent") {
    return AccessPermission_NotPresent;
  } else if (str == "OnHold") {
    return AccessPermission_OnHold;
  } else if (str == "ReadUpgradingToWrite") {
    return AccessPermission_ReadUpgradingToWrite;
  } else if (str == "Stale") {
    return AccessPermission_Stale;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type AccessPermission");
  }
}

AccessPermission& operator++( AccessPermission& e) {
  assert(e < AccessPermission_NUM);
  return e = AccessPermission(e+1);
}
