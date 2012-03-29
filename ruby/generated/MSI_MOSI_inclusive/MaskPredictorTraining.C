/** \file MaskPredictorTraining.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "MaskPredictorTraining.h"

ostream& operator<<(ostream& out, const MaskPredictorTraining& obj)
{
  out << MaskPredictorTraining_to_string(obj);
  out << flush;
  return out;
}

string MaskPredictorTraining_to_string(const MaskPredictorTraining& obj)
{
  switch(obj) {
  case MaskPredictorTraining_Undefined:
    return "Undefined";
  case MaskPredictorTraining_None:
    return "None";
  case MaskPredictorTraining_Implicit:
    return "Implicit";
  case MaskPredictorTraining_Explicit:
    return "Explicit";
  case MaskPredictorTraining_Both:
    return "Both";
  default:
    ERROR_MSG("Invalid range for type MaskPredictorTraining");
    return "";
  }
}

MaskPredictorTraining string_to_MaskPredictorTraining(const string& str)
{
  if (false) {
  } else if (str == "Undefined") {
    return MaskPredictorTraining_Undefined;
  } else if (str == "None") {
    return MaskPredictorTraining_None;
  } else if (str == "Implicit") {
    return MaskPredictorTraining_Implicit;
  } else if (str == "Explicit") {
    return MaskPredictorTraining_Explicit;
  } else if (str == "Both") {
    return MaskPredictorTraining_Both;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type MaskPredictorTraining");
  }
}

MaskPredictorTraining& operator++( MaskPredictorTraining& e) {
  assert(e < MaskPredictorTraining_NUM);
  return e = MaskPredictorTraining(e+1);
}
