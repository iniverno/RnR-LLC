/** \file DetermSeriesGETSGeneratorStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "DetermSeriesGETSGeneratorStatus.h"

ostream& operator<<(ostream& out, const DetermSeriesGETSGeneratorStatus& obj)
{
  out << DetermSeriesGETSGeneratorStatus_to_string(obj);
  out << flush;
  return out;
}

string DetermSeriesGETSGeneratorStatus_to_string(const DetermSeriesGETSGeneratorStatus& obj)
{
  switch(obj) {
  case DetermSeriesGETSGeneratorStatus_Thinking:
    return "Thinking";
  case DetermSeriesGETSGeneratorStatus_Load_Pending:
    return "Load_Pending";
  case DetermSeriesGETSGeneratorStatus_Done:
    return "Done";
  default:
    ERROR_MSG("Invalid range for type DetermSeriesGETSGeneratorStatus");
    return "";
  }
}

DetermSeriesGETSGeneratorStatus string_to_DetermSeriesGETSGeneratorStatus(const string& str)
{
  if (false) {
  } else if (str == "Thinking") {
    return DetermSeriesGETSGeneratorStatus_Thinking;
  } else if (str == "Load_Pending") {
    return DetermSeriesGETSGeneratorStatus_Load_Pending;
  } else if (str == "Done") {
    return DetermSeriesGETSGeneratorStatus_Done;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type DetermSeriesGETSGeneratorStatus");
  }
}

DetermSeriesGETSGeneratorStatus& operator++( DetermSeriesGETSGeneratorStatus& e) {
  assert(e < DetermSeriesGETSGeneratorStatus_NUM);
  return e = DetermSeriesGETSGeneratorStatus(e+1);
}
