/** \file Directory_Event.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "Directory_Event.h"

ostream& operator<<(ostream& out, const Directory_Event& obj)
{
  out << Directory_Event_to_string(obj);
  out << flush;
  return out;
}

string Directory_Event_to_string(const Directory_Event& obj)
{
  switch(obj) {
  case Directory_Event_GETS:
    return "GETS";
  case Directory_Event_GET_INSTR:
    return "GET_INSTR";
  case Directory_Event_GETX_Owner:
    return "GETX_Owner";
  case Directory_Event_GETX_NotOwner:
    return "GETX_NotOwner";
  case Directory_Event_PUTX_Owner:
    return "PUTX_Owner";
  case Directory_Event_PUTX_NotOwner:
    return "PUTX_NotOwner";
  case Directory_Event_FinalAck:
    return "FinalAck";
  case Directory_Event_PREFS:
    return "PREFS";
  case Directory_Event_PREFX:
    return "PREFX";
  case Directory_Event_DATA:
    return "DATA";
  case Directory_Event_DATA_P:
    return "DATA_P";
  case Directory_Event_UG_PREFETCH:
    return "UG_PREFETCH";
  default:
    ERROR_MSG("Invalid range for type Directory_Event");
    return "";
  }
}

Directory_Event string_to_Directory_Event(const string& str)
{
  if (false) {
  } else if (str == "GETS") {
    return Directory_Event_GETS;
  } else if (str == "GET_INSTR") {
    return Directory_Event_GET_INSTR;
  } else if (str == "GETX_Owner") {
    return Directory_Event_GETX_Owner;
  } else if (str == "GETX_NotOwner") {
    return Directory_Event_GETX_NotOwner;
  } else if (str == "PUTX_Owner") {
    return Directory_Event_PUTX_Owner;
  } else if (str == "PUTX_NotOwner") {
    return Directory_Event_PUTX_NotOwner;
  } else if (str == "FinalAck") {
    return Directory_Event_FinalAck;
  } else if (str == "PREFS") {
    return Directory_Event_PREFS;
  } else if (str == "PREFX") {
    return Directory_Event_PREFX;
  } else if (str == "DATA") {
    return Directory_Event_DATA;
  } else if (str == "DATA_P") {
    return Directory_Event_DATA_P;
  } else if (str == "UG_PREFETCH") {
    return Directory_Event_UG_PREFETCH;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type Directory_Event");
  }
}

Directory_Event& operator++( Directory_Event& e) {
  assert(e < Directory_Event_NUM);
  return e = Directory_Event(e+1);
}
