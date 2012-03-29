/** \file LockStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "LockStatus.h"

ostream& operator<<(ostream& out, const LockStatus& obj)
{
  out << LockStatus_to_string(obj);
  out << flush;
  return out;
}

string LockStatus_to_string(const LockStatus& obj)
{
  switch(obj) {
  case LockStatus_Unlocked:
    return "Unlocked";
  case LockStatus_Locked:
    return "Locked";
  default:
    ERROR_MSG("Invalid range for type LockStatus");
    return "";
  }
}

LockStatus string_to_LockStatus(const string& str)
{
  if (false) {
  } else if (str == "Unlocked") {
    return LockStatus_Unlocked;
  } else if (str == "Locked") {
    return LockStatus_Locked;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type LockStatus");
  }
}

LockStatus& operator++( LockStatus& e) {
  assert(e < LockStatus_NUM);
  return e = LockStatus(e+1);
}
