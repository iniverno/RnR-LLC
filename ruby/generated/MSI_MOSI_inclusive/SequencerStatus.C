/** \file SequencerStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "SequencerStatus.h"

ostream& operator<<(ostream& out, const SequencerStatus& obj)
{
  out << SequencerStatus_to_string(obj);
  out << flush;
  return out;
}

string SequencerStatus_to_string(const SequencerStatus& obj)
{
  switch(obj) {
  case SequencerStatus_Idle:
    return "Idle";
  case SequencerStatus_Pending:
    return "Pending";
  default:
    ERROR_MSG("Invalid range for type SequencerStatus");
    return "";
  }
}

SequencerStatus string_to_SequencerStatus(const string& str)
{
  if (false) {
  } else if (str == "Idle") {
    return SequencerStatus_Idle;
  } else if (str == "Pending") {
    return SequencerStatus_Pending;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type SequencerStatus");
  }
}

SequencerStatus& operator++( SequencerStatus& e) {
  assert(e < SequencerStatus_NUM);
  return e = SequencerStatus(e+1);
}
