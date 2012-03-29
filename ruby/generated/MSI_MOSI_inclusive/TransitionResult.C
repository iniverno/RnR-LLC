/** \file TransitionResult.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "TransitionResult.h"

ostream& operator<<(ostream& out, const TransitionResult& obj)
{
  out << TransitionResult_to_string(obj);
  out << flush;
  return out;
}

string TransitionResult_to_string(const TransitionResult& obj)
{
  switch(obj) {
  case TransitionResult_Valid:
    return "Valid";
  case TransitionResult_ResourceStall:
    return "ResourceStall";
  case TransitionResult_ProtocolStall:
    return "ProtocolStall";
  default:
    ERROR_MSG("Invalid range for type TransitionResult");
    return "";
  }
}

TransitionResult string_to_TransitionResult(const string& str)
{
  if (false) {
  } else if (str == "Valid") {
    return TransitionResult_Valid;
  } else if (str == "ResourceStall") {
    return TransitionResult_ResourceStall;
  } else if (str == "ProtocolStall") {
    return TransitionResult_ProtocolStall;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type TransitionResult");
  }
}

TransitionResult& operator++( TransitionResult& e) {
  assert(e < TransitionResult_NUM);
  return e = TransitionResult(e+1);
}
