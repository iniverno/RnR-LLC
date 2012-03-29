/** \file DetermInvGeneratorStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "DetermInvGeneratorStatus.h"

ostream& operator<<(ostream& out, const DetermInvGeneratorStatus& obj)
{
  out << DetermInvGeneratorStatus_to_string(obj);
  out << flush;
  return out;
}

string DetermInvGeneratorStatus_to_string(const DetermInvGeneratorStatus& obj)
{
  switch(obj) {
  case DetermInvGeneratorStatus_Thinking:
    return "Thinking";
  case DetermInvGeneratorStatus_Store_Pending:
    return "Store_Pending";
  case DetermInvGeneratorStatus_Load_Complete:
    return "Load_Complete";
  case DetermInvGeneratorStatus_Load_Pending:
    return "Load_Pending";
  case DetermInvGeneratorStatus_Done:
    return "Done";
  default:
    ERROR_MSG("Invalid range for type DetermInvGeneratorStatus");
    return "";
  }
}

DetermInvGeneratorStatus string_to_DetermInvGeneratorStatus(const string& str)
{
  if (false) {
  } else if (str == "Thinking") {
    return DetermInvGeneratorStatus_Thinking;
  } else if (str == "Store_Pending") {
    return DetermInvGeneratorStatus_Store_Pending;
  } else if (str == "Load_Complete") {
    return DetermInvGeneratorStatus_Load_Complete;
  } else if (str == "Load_Pending") {
    return DetermInvGeneratorStatus_Load_Pending;
  } else if (str == "Done") {
    return DetermInvGeneratorStatus_Done;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type DetermInvGeneratorStatus");
  }
}

DetermInvGeneratorStatus& operator++( DetermInvGeneratorStatus& e) {
  assert(e < DetermInvGeneratorStatus_NUM);
  return e = DetermInvGeneratorStatus(e+1);
}
