/** \file GenericMachineType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "GenericMachineType.h"

ostream& operator<<(ostream& out, const GenericMachineType& obj)
{
  out << GenericMachineType_to_string(obj);
  out << flush;
  return out;
}

string GenericMachineType_to_string(const GenericMachineType& obj)
{
  switch(obj) {
  case GenericMachineType_L1Cache:
    return "L1Cache";
  case GenericMachineType_L2Cache:
    return "L2Cache";
  case GenericMachineType_L3Cache:
    return "L3Cache";
  case GenericMachineType_Directory:
    return "Directory";
  case GenericMachineType_Collector:
    return "Collector";
  case GenericMachineType_L1Cache_wCC:
    return "L1Cache_wCC";
  case GenericMachineType_L2Cache_wCC:
    return "L2Cache_wCC";
  case GenericMachineType_VCache:
    return "VCache";
  case GenericMachineType_Dram:
    return "Dram";
  case GenericMachineType_NULL:
    return "NULL";
  default:
    ERROR_MSG("Invalid range for type GenericMachineType");
    return "";
  }
}

GenericMachineType string_to_GenericMachineType(const string& str)
{
  if (false) {
  } else if (str == "L1Cache") {
    return GenericMachineType_L1Cache;
  } else if (str == "L2Cache") {
    return GenericMachineType_L2Cache;
  } else if (str == "L3Cache") {
    return GenericMachineType_L3Cache;
  } else if (str == "Directory") {
    return GenericMachineType_Directory;
  } else if (str == "Collector") {
    return GenericMachineType_Collector;
  } else if (str == "L1Cache_wCC") {
    return GenericMachineType_L1Cache_wCC;
  } else if (str == "L2Cache_wCC") {
    return GenericMachineType_L2Cache_wCC;
  } else if (str == "VCache") {
    return GenericMachineType_VCache;
  } else if (str == "Dram") {
    return GenericMachineType_Dram;
  } else if (str == "NULL") {
    return GenericMachineType_NULL;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type GenericMachineType");
  }
}

GenericMachineType& operator++( GenericMachineType& e) {
  assert(e < GenericMachineType_NUM);
  return e = GenericMachineType(e+1);
}
