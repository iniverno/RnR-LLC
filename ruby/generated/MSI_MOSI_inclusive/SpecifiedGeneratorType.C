/** \file SpecifiedGeneratorType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "SpecifiedGeneratorType.h"

ostream& operator<<(ostream& out, const SpecifiedGeneratorType& obj)
{
  out << SpecifiedGeneratorType_to_string(obj);
  out << flush;
  return out;
}

string SpecifiedGeneratorType_to_string(const SpecifiedGeneratorType& obj)
{
  switch(obj) {
  case SpecifiedGeneratorType_DetermGETXGenerator:
    return "DetermGETXGenerator";
  case SpecifiedGeneratorType_DetermInvGenerator:
    return "DetermInvGenerator";
  case SpecifiedGeneratorType_DetermSeriesGETSGenerator:
    return "DetermSeriesGETSGenerator";
  default:
    ERROR_MSG("Invalid range for type SpecifiedGeneratorType");
    return "";
  }
}

SpecifiedGeneratorType string_to_SpecifiedGeneratorType(const string& str)
{
  if (false) {
  } else if (str == "DetermGETXGenerator") {
    return SpecifiedGeneratorType_DetermGETXGenerator;
  } else if (str == "DetermInvGenerator") {
    return SpecifiedGeneratorType_DetermInvGenerator;
  } else if (str == "DetermSeriesGETSGenerator") {
    return SpecifiedGeneratorType_DetermSeriesGETSGenerator;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type SpecifiedGeneratorType");
  }
}

SpecifiedGeneratorType& operator++( SpecifiedGeneratorType& e) {
  assert(e < SpecifiedGeneratorType_NUM);
  return e = SpecifiedGeneratorType(e+1);
}
