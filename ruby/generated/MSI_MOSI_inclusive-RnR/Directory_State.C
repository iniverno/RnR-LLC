/** \file Directory_State.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "Directory_State.h"

ostream& operator<<(ostream& out, const Directory_State& obj)
{
  out << Directory_State_to_string(obj);
  out << flush;
  return out;
}

string Directory_State_to_string(const Directory_State& obj)
{
  switch(obj) {
  case Directory_State_NP:
    return "NP";
  case Directory_State_I:
    return "I";
  case Directory_State_S:
    return "S";
  case Directory_State_O:
    return "O";
  case Directory_State_M:
    return "M";
  case Directory_State_OO:
    return "OO";
  case Directory_State_OM:
    return "OM";
  case Directory_State_MO:
    return "MO";
  case Directory_State_MM:
    return "MM";
  case Directory_State_MD:
    return "MD";
  case Directory_State_SD:
    return "SD";
  case Directory_State_MPD:
    return "MPD";
  case Directory_State_SPD:
    return "SPD";
  default:
    ERROR_MSG("Invalid range for type Directory_State");
    return "";
  }
}

Directory_State string_to_Directory_State(const string& str)
{
  if (false) {
  } else if (str == "NP") {
    return Directory_State_NP;
  } else if (str == "I") {
    return Directory_State_I;
  } else if (str == "S") {
    return Directory_State_S;
  } else if (str == "O") {
    return Directory_State_O;
  } else if (str == "M") {
    return Directory_State_M;
  } else if (str == "OO") {
    return Directory_State_OO;
  } else if (str == "OM") {
    return Directory_State_OM;
  } else if (str == "MO") {
    return Directory_State_MO;
  } else if (str == "MM") {
    return Directory_State_MM;
  } else if (str == "MD") {
    return Directory_State_MD;
  } else if (str == "SD") {
    return Directory_State_SD;
  } else if (str == "MPD") {
    return Directory_State_MPD;
  } else if (str == "SPD") {
    return Directory_State_SPD;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type Directory_State");
  }
}

Directory_State& operator++( Directory_State& e) {
  assert(e < Directory_State_NUM);
  return e = Directory_State(e+1);
}
