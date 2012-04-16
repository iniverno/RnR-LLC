/** \file TesterStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "TesterStatus.h"

ostream& operator<<(ostream& out, const TesterStatus& obj)
{
  out << TesterStatus_to_string(obj);
  out << flush;
  return out;
}

string TesterStatus_to_string(const TesterStatus& obj)
{
  switch(obj) {
  case TesterStatus_Idle:
    return "Idle";
  case TesterStatus_Action_Pending:
    return "Action_Pending";
  case TesterStatus_Ready:
    return "Ready";
  case TesterStatus_Check_Pending:
    return "Check_Pending";
  default:
    ERROR_MSG("Invalid range for type TesterStatus");
    return "";
  }
}

TesterStatus string_to_TesterStatus(const string& str)
{
  if (false) {
  } else if (str == "Idle") {
    return TesterStatus_Idle;
  } else if (str == "Action_Pending") {
    return TesterStatus_Action_Pending;
  } else if (str == "Ready") {
    return TesterStatus_Ready;
  } else if (str == "Check_Pending") {
    return TesterStatus_Check_Pending;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type TesterStatus");
  }
}

TesterStatus& operator++( TesterStatus& e) {
  assert(e < TesterStatus_NUM);
  return e = TesterStatus(e+1);
}
