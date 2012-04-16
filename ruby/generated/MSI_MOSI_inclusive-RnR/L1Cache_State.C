/** \file L1Cache_State.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "L1Cache_State.h"

ostream& operator<<(ostream& out, const L1Cache_State& obj)
{
  out << L1Cache_State_to_string(obj);
  out << flush;
  return out;
}

string L1Cache_State_to_string(const L1Cache_State& obj)
{
  switch(obj) {
  case L1Cache_State_NP:
    return "NP";
  case L1Cache_State_L1_I:
    return "L1_I";
  case L1Cache_State_L1_S:
    return "L1_S";
  case L1Cache_State_L1_M:
    return "L1_M";
  case L1Cache_State_L1_IS:
    return "L1_IS";
  case L1Cache_State_L1_ISI:
    return "L1_ISI";
  case L1Cache_State_L1_IM:
    return "L1_IM";
  case L1Cache_State_L1_IMI:
    return "L1_IMI";
  case L1Cache_State_L1_IMS:
    return "L1_IMS";
  case L1Cache_State_L1_IMSI:
    return "L1_IMSI";
  case L1Cache_State_L1_SI:
    return "L1_SI";
  case L1Cache_State_L1_MI:
    return "L1_MI";
  default:
    ERROR_MSG("Invalid range for type L1Cache_State");
    return "";
  }
}

L1Cache_State string_to_L1Cache_State(const string& str)
{
  if (false) {
  } else if (str == "NP") {
    return L1Cache_State_NP;
  } else if (str == "L1_I") {
    return L1Cache_State_L1_I;
  } else if (str == "L1_S") {
    return L1Cache_State_L1_S;
  } else if (str == "L1_M") {
    return L1Cache_State_L1_M;
  } else if (str == "L1_IS") {
    return L1Cache_State_L1_IS;
  } else if (str == "L1_ISI") {
    return L1Cache_State_L1_ISI;
  } else if (str == "L1_IM") {
    return L1Cache_State_L1_IM;
  } else if (str == "L1_IMI") {
    return L1Cache_State_L1_IMI;
  } else if (str == "L1_IMS") {
    return L1Cache_State_L1_IMS;
  } else if (str == "L1_IMSI") {
    return L1Cache_State_L1_IMSI;
  } else if (str == "L1_SI") {
    return L1Cache_State_L1_SI;
  } else if (str == "L1_MI") {
    return L1Cache_State_L1_MI;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type L1Cache_State");
  }
}

L1Cache_State& operator++( L1Cache_State& e) {
  assert(e < L1Cache_State_NUM);
  return e = L1Cache_State(e+1);
}
