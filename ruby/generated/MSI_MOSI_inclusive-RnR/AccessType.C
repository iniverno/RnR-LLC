/** \file AccessType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "AccessType.h"

ostream& operator<<(ostream& out, const AccessType& obj)
{
  out << AccessType_to_string(obj);
  out << flush;
  return out;
}

string AccessType_to_string(const AccessType& obj)
{
  switch(obj) {
  case AccessType_Read:
    return "Read";
  case AccessType_Write:
    return "Write";
  default:
    ERROR_MSG("Invalid range for type AccessType");
    return "";
  }
}

AccessType string_to_AccessType(const string& str)
{
  if (false) {
  } else if (str == "Read") {
    return AccessType_Read;
  } else if (str == "Write") {
    return AccessType_Write;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type AccessType");
  }
}

AccessType& operator++( AccessType& e) {
  assert(e < AccessType_NUM);
  return e = AccessType(e+1);
}
