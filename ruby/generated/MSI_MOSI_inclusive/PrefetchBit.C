/** \file PrefetchBit.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "PrefetchBit.h"

ostream& operator<<(ostream& out, const PrefetchBit& obj)
{
  out << PrefetchBit_to_string(obj);
  out << flush;
  return out;
}

string PrefetchBit_to_string(const PrefetchBit& obj)
{
  switch(obj) {
  case PrefetchBit_No:
    return "No";
  case PrefetchBit_Yes:
    return "Yes";
  case PrefetchBit_L1_HW:
    return "L1_HW";
  case PrefetchBit_L2_HW:
    return "L2_HW";
  default:
    ERROR_MSG("Invalid range for type PrefetchBit");
    return "";
  }
}

PrefetchBit string_to_PrefetchBit(const string& str)
{
  if (false) {
  } else if (str == "No") {
    return PrefetchBit_No;
  } else if (str == "Yes") {
    return PrefetchBit_Yes;
  } else if (str == "L1_HW") {
    return PrefetchBit_L1_HW;
  } else if (str == "L2_HW") {
    return PrefetchBit_L2_HW;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type PrefetchBit");
  }
}

PrefetchBit& operator++( PrefetchBit& e) {
  assert(e < PrefetchBit_NUM);
  return e = PrefetchBit(e+1);
}
