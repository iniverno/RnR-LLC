/** \file AllocationStrategy.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "AllocationStrategy.h"

ostream& operator<<(ostream& out, const AllocationStrategy& obj)
{
  out << AllocationStrategy_to_string(obj);
  out << flush;
  return out;
}

string AllocationStrategy_to_string(const AllocationStrategy& obj)
{
  switch(obj) {
  case AllocationStrategy_InMiddle:
    return "InMiddle";
  case AllocationStrategy_InInvCorners:
    return "InInvCorners";
  case AllocationStrategy_InSharedSides:
    return "InSharedSides";
  case AllocationStrategy_StaticDist:
    return "StaticDist";
  case AllocationStrategy_RandomBank:
    return "RandomBank";
  case AllocationStrategy_FrequencyBank:
    return "FrequencyBank";
  case AllocationStrategy_FrequencyBlock:
    return "FrequencyBlock";
  case AllocationStrategy_LRUBlock:
    return "LRUBlock";
  default:
    ERROR_MSG("Invalid range for type AllocationStrategy");
    return "";
  }
}

AllocationStrategy string_to_AllocationStrategy(const string& str)
{
  if (false) {
  } else if (str == "InMiddle") {
    return AllocationStrategy_InMiddle;
  } else if (str == "InInvCorners") {
    return AllocationStrategy_InInvCorners;
  } else if (str == "InSharedSides") {
    return AllocationStrategy_InSharedSides;
  } else if (str == "StaticDist") {
    return AllocationStrategy_StaticDist;
  } else if (str == "RandomBank") {
    return AllocationStrategy_RandomBank;
  } else if (str == "FrequencyBank") {
    return AllocationStrategy_FrequencyBank;
  } else if (str == "FrequencyBlock") {
    return AllocationStrategy_FrequencyBlock;
  } else if (str == "LRUBlock") {
    return AllocationStrategy_LRUBlock;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type AllocationStrategy");
  }
}

AllocationStrategy& operator++( AllocationStrategy& e) {
  assert(e < AllocationStrategy_NUM);
  return e = AllocationStrategy(e+1);
}
