/** \file L1Cache_Event.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "L1Cache_Event.h"

ostream& operator<<(ostream& out, const L1Cache_Event& obj)
{
  out << L1Cache_Event_to_string(obj);
  out << flush;
  return out;
}

string L1Cache_Event_to_string(const L1Cache_Event& obj)
{
  switch(obj) {
  case L1Cache_Event_Load:
    return "Load";
  case L1Cache_Event_Ifetch:
    return "Ifetch";
  case L1Cache_Event_Store:
    return "Store";
  case L1Cache_Event_L1_INV:
    return "L1_INV";
  case L1Cache_Event_L1_INV_S:
    return "L1_INV_S";
  case L1Cache_Event_L1_INV_P:
    return "L1_INV_P";
  case L1Cache_Event_L1_INV_S_P:
    return "L1_INV_S_P";
  case L1Cache_Event_L1_DownGrade:
    return "L1_DownGrade";
  case L1Cache_Event_L1_Data:
    return "L1_Data";
  case L1Cache_Event_L1_Data_S:
    return "L1_Data_S";
  case L1Cache_Event_L1_Data_I:
    return "L1_Data_I";
  case L1Cache_Event_L1_PutAck:
    return "L1_PutAck";
  case L1Cache_Event_L1_Replacement:
    return "L1_Replacement";
  case L1Cache_Event_L15_Replacement:
    return "L15_Replacement";
  case L1Cache_Event_L1_WriteBack:
    return "L1_WriteBack";
  default:
    ERROR_MSG("Invalid range for type L1Cache_Event");
    return "";
  }
}

L1Cache_Event string_to_L1Cache_Event(const string& str)
{
  if (false) {
  } else if (str == "Load") {
    return L1Cache_Event_Load;
  } else if (str == "Ifetch") {
    return L1Cache_Event_Ifetch;
  } else if (str == "Store") {
    return L1Cache_Event_Store;
  } else if (str == "L1_INV") {
    return L1Cache_Event_L1_INV;
  } else if (str == "L1_INV_S") {
    return L1Cache_Event_L1_INV_S;
  } else if (str == "L1_INV_P") {
    return L1Cache_Event_L1_INV_P;
  } else if (str == "L1_INV_S_P") {
    return L1Cache_Event_L1_INV_S_P;
  } else if (str == "L1_DownGrade") {
    return L1Cache_Event_L1_DownGrade;
  } else if (str == "L1_Data") {
    return L1Cache_Event_L1_Data;
  } else if (str == "L1_Data_S") {
    return L1Cache_Event_L1_Data_S;
  } else if (str == "L1_Data_I") {
    return L1Cache_Event_L1_Data_I;
  } else if (str == "L1_PutAck") {
    return L1Cache_Event_L1_PutAck;
  } else if (str == "L1_Replacement") {
    return L1Cache_Event_L1_Replacement;
  } else if (str == "L15_Replacement") {
    return L1Cache_Event_L15_Replacement;
  } else if (str == "L1_WriteBack") {
    return L1Cache_Event_L1_WriteBack;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type L1Cache_Event");
  }
}

L1Cache_Event& operator++( L1Cache_Event& e) {
  assert(e < L1Cache_Event_NUM);
  return e = L1Cache_Event(e+1);
}
