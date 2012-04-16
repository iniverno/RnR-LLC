/** \file DetermGETXGeneratorStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "DetermGETXGeneratorStatus.h"

ostream& operator<<(ostream& out, const DetermGETXGeneratorStatus& obj)
{
  out << DetermGETXGeneratorStatus_to_string(obj);
  out << flush;
  return out;
}

string DetermGETXGeneratorStatus_to_string(const DetermGETXGeneratorStatus& obj)
{
  switch(obj) {
  case DetermGETXGeneratorStatus_Thinking:
    return "Thinking";
  case DetermGETXGeneratorStatus_Store_Pending:
    return "Store_Pending";
  case DetermGETXGeneratorStatus_Done:
    return "Done";
  default:
    ERROR_MSG("Invalid range for type DetermGETXGeneratorStatus");
    return "";
  }
}

DetermGETXGeneratorStatus string_to_DetermGETXGeneratorStatus(const string& str)
{
  if (false) {
  } else if (str == "Thinking") {
    return DetermGETXGeneratorStatus_Thinking;
  } else if (str == "Store_Pending") {
    return DetermGETXGeneratorStatus_Store_Pending;
  } else if (str == "Done") {
    return DetermGETXGeneratorStatus_Done;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type DetermGETXGeneratorStatus");
  }
}

DetermGETXGeneratorStatus& operator++( DetermGETXGeneratorStatus& e) {
  assert(e < DetermGETXGeneratorStatus_NUM);
  return e = DetermGETXGeneratorStatus(e+1);
}
