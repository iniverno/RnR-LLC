/** \file MaskPredictorIndex.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "MaskPredictorIndex.h"

ostream& operator<<(ostream& out, const MaskPredictorIndex& obj)
{
  out << MaskPredictorIndex_to_string(obj);
  out << flush;
  return out;
}

string MaskPredictorIndex_to_string(const MaskPredictorIndex& obj)
{
  switch(obj) {
  case MaskPredictorIndex_Undefined:
    return "Undefined";
  case MaskPredictorIndex_DataBlock:
    return "DataBlock";
  case MaskPredictorIndex_PC:
    return "PC";
  default:
    ERROR_MSG("Invalid range for type MaskPredictorIndex");
    return "";
  }
}

MaskPredictorIndex string_to_MaskPredictorIndex(const string& str)
{
  if (false) {
  } else if (str == "Undefined") {
    return MaskPredictorIndex_Undefined;
  } else if (str == "DataBlock") {
    return MaskPredictorIndex_DataBlock;
  } else if (str == "PC") {
    return MaskPredictorIndex_PC;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type MaskPredictorIndex");
  }
}

MaskPredictorIndex& operator++( MaskPredictorIndex& e) {
  assert(e < MaskPredictorIndex_NUM);
  return e = MaskPredictorIndex(e+1);
}
