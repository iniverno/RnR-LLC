/** \file CoherenceResponseType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "CoherenceResponseType.h"

ostream& operator<<(ostream& out, const CoherenceResponseType& obj)
{
  out << CoherenceResponseType_to_string(obj);
  out << flush;
  return out;
}

string CoherenceResponseType_to_string(const CoherenceResponseType& obj)
{
  switch(obj) {
  case CoherenceResponseType_ACK:
    return "ACK";
  case CoherenceResponseType_INV_ACK:
    return "INV_ACK";
  case CoherenceResponseType_DG_ACK:
    return "DG_ACK";
  case CoherenceResponseType_NACK:
    return "NACK";
  case CoherenceResponseType_DATA:
    return "DATA";
  case CoherenceResponseType_DATA_S:
    return "DATA_S";
  case CoherenceResponseType_DATA_I:
    return "DATA_I";
  case CoherenceResponseType_FINALACK:
    return "FINALACK";
  default:
    ERROR_MSG("Invalid range for type CoherenceResponseType");
    return "";
  }
}

CoherenceResponseType string_to_CoherenceResponseType(const string& str)
{
  if (false) {
  } else if (str == "ACK") {
    return CoherenceResponseType_ACK;
  } else if (str == "INV_ACK") {
    return CoherenceResponseType_INV_ACK;
  } else if (str == "DG_ACK") {
    return CoherenceResponseType_DG_ACK;
  } else if (str == "NACK") {
    return CoherenceResponseType_NACK;
  } else if (str == "DATA") {
    return CoherenceResponseType_DATA;
  } else if (str == "DATA_S") {
    return CoherenceResponseType_DATA_S;
  } else if (str == "DATA_I") {
    return CoherenceResponseType_DATA_I;
  } else if (str == "FINALACK") {
    return CoherenceResponseType_FINALACK;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type CoherenceResponseType");
  }
}

CoherenceResponseType& operator++( CoherenceResponseType& e) {
  assert(e < CoherenceResponseType_NUM);
  return e = CoherenceResponseType(e+1);
}
