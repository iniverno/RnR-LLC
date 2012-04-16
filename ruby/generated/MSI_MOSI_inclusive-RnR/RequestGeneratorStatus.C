/** \file RequestGeneratorStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "RequestGeneratorStatus.h"

ostream& operator<<(ostream& out, const RequestGeneratorStatus& obj)
{
  out << RequestGeneratorStatus_to_string(obj);
  out << flush;
  return out;
}

string RequestGeneratorStatus_to_string(const RequestGeneratorStatus& obj)
{
  switch(obj) {
  case RequestGeneratorStatus_Thinking:
    return "Thinking";
  case RequestGeneratorStatus_Test_Pending:
    return "Test_Pending";
  case RequestGeneratorStatus_Before_Swap:
    return "Before_Swap";
  case RequestGeneratorStatus_Swap_Pending:
    return "Swap_Pending";
  case RequestGeneratorStatus_Holding:
    return "Holding";
  case RequestGeneratorStatus_Release_Pending:
    return "Release_Pending";
  case RequestGeneratorStatus_Done:
    return "Done";
  default:
    ERROR_MSG("Invalid range for type RequestGeneratorStatus");
    return "";
  }
}

RequestGeneratorStatus string_to_RequestGeneratorStatus(const string& str)
{
  if (false) {
  } else if (str == "Thinking") {
    return RequestGeneratorStatus_Thinking;
  } else if (str == "Test_Pending") {
    return RequestGeneratorStatus_Test_Pending;
  } else if (str == "Before_Swap") {
    return RequestGeneratorStatus_Before_Swap;
  } else if (str == "Swap_Pending") {
    return RequestGeneratorStatus_Swap_Pending;
  } else if (str == "Holding") {
    return RequestGeneratorStatus_Holding;
  } else if (str == "Release_Pending") {
    return RequestGeneratorStatus_Release_Pending;
  } else if (str == "Done") {
    return RequestGeneratorStatus_Done;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type RequestGeneratorStatus");
  }
}

RequestGeneratorStatus& operator++( RequestGeneratorStatus& e) {
  assert(e < RequestGeneratorStatus_NUM);
  return e = RequestGeneratorStatus(e+1);
}
