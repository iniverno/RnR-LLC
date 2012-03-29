/** \file CoherenceRequestType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "CoherenceRequestType.h"

ostream& operator<<(ostream& out, const CoherenceRequestType& obj)
{
  out << CoherenceRequestType_to_string(obj);
  out << flush;
  return out;
}

string CoherenceRequestType_to_string(const CoherenceRequestType& obj)
{
  switch(obj) {
  case CoherenceRequestType_GETX:
    return "GETX";
  case CoherenceRequestType_UPGRADE:
    return "UPGRADE";
  case CoherenceRequestType_GETS:
    return "GETS";
  case CoherenceRequestType_GET_INSTR:
    return "GET_INSTR";
  case CoherenceRequestType_PUTX:
    return "PUTX";
  case CoherenceRequestType_PUTS:
    return "PUTS";
  case CoherenceRequestType_INV:
    return "INV";
  case CoherenceRequestType_INV_S:
    return "INV_S";
  case CoherenceRequestType_INV_P:
    return "INV_P";
  case CoherenceRequestType_INV_S_P:
    return "INV_S_P";
  case CoherenceRequestType_L1_DG:
    return "L1_DG";
  case CoherenceRequestType_WB_ACK:
    return "WB_ACK";
  case CoherenceRequestType_EXE_ACK:
    return "EXE_ACK";
  case CoherenceRequestType_PREFS:
    return "PREFS";
  case CoherenceRequestType_PREFX:
    return "PREFX";
  default:
    ERROR_MSG("Invalid range for type CoherenceRequestType");
    return "";
  }
}

CoherenceRequestType string_to_CoherenceRequestType(const string& str)
{
  if (false) {
  } else if (str == "GETX") {
    return CoherenceRequestType_GETX;
  } else if (str == "UPGRADE") {
    return CoherenceRequestType_UPGRADE;
  } else if (str == "GETS") {
    return CoherenceRequestType_GETS;
  } else if (str == "GET_INSTR") {
    return CoherenceRequestType_GET_INSTR;
  } else if (str == "PUTX") {
    return CoherenceRequestType_PUTX;
  } else if (str == "PUTS") {
    return CoherenceRequestType_PUTS;
  } else if (str == "INV") {
    return CoherenceRequestType_INV;
  } else if (str == "INV_S") {
    return CoherenceRequestType_INV_S;
  } else if (str == "INV_P") {
    return CoherenceRequestType_INV_P;
  } else if (str == "INV_S_P") {
    return CoherenceRequestType_INV_S_P;
  } else if (str == "L1_DG") {
    return CoherenceRequestType_L1_DG;
  } else if (str == "WB_ACK") {
    return CoherenceRequestType_WB_ACK;
  } else if (str == "EXE_ACK") {
    return CoherenceRequestType_EXE_ACK;
  } else if (str == "PREFS") {
    return CoherenceRequestType_PREFS;
  } else if (str == "PREFX") {
    return CoherenceRequestType_PREFX;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type CoherenceRequestType");
  }
}

CoherenceRequestType& operator++( CoherenceRequestType& e) {
  assert(e < CoherenceRequestType_NUM);
  return e = CoherenceRequestType(e+1);
}
