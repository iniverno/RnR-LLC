/** \file TransientRequestType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "TransientRequestType.h"

ostream& operator<<(ostream& out, const TransientRequestType& obj)
{
  out << TransientRequestType_to_string(obj);
  out << flush;
  return out;
}

string TransientRequestType_to_string(const TransientRequestType& obj)
{
  switch(obj) {
  case TransientRequestType_Undefined:
    return "Undefined";
  case TransientRequestType_OffChip:
    return "OffChip";
  case TransientRequestType_OnChip:
    return "OnChip";
  case TransientRequestType_LocalTransient:
    return "LocalTransient";
  default:
    ERROR_MSG("Invalid range for type TransientRequestType");
    return "";
  }
}

TransientRequestType string_to_TransientRequestType(const string& str)
{
  if (false) {
  } else if (str == "Undefined") {
    return TransientRequestType_Undefined;
  } else if (str == "OffChip") {
    return TransientRequestType_OffChip;
  } else if (str == "OnChip") {
    return TransientRequestType_OnChip;
  } else if (str == "LocalTransient") {
    return TransientRequestType_LocalTransient;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type TransientRequestType");
  }
}

TransientRequestType& operator++( TransientRequestType& e) {
  assert(e < TransientRequestType_NUM);
  return e = TransientRequestType(e+1);
}
