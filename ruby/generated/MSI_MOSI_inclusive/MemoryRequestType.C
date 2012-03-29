/** \file MemoryRequestType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "MemoryRequestType.h"

ostream& operator<<(ostream& out, const MemoryRequestType& obj)
{
  out << MemoryRequestType_to_string(obj);
  out << flush;
  return out;
}

string MemoryRequestType_to_string(const MemoryRequestType& obj)
{
  switch(obj) {
  case MemoryRequestType_MEMORY_READ:
    return "MEMORY_READ";
  case MemoryRequestType_MEMORY_WB:
    return "MEMORY_WB";
  case MemoryRequestType_MEMORY_DATA:
    return "MEMORY_DATA";
  case MemoryRequestType_MEMORY_ACK:
    return "MEMORY_ACK";
  default:
    ERROR_MSG("Invalid range for type MemoryRequestType");
    return "";
  }
}

MemoryRequestType string_to_MemoryRequestType(const string& str)
{
  if (false) {
  } else if (str == "MEMORY_READ") {
    return MemoryRequestType_MEMORY_READ;
  } else if (str == "MEMORY_WB") {
    return MemoryRequestType_MEMORY_WB;
  } else if (str == "MEMORY_DATA") {
    return MemoryRequestType_MEMORY_DATA;
  } else if (str == "MEMORY_ACK") {
    return MemoryRequestType_MEMORY_ACK;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type MemoryRequestType");
  }
}

MemoryRequestType& operator++( MemoryRequestType& e) {
  assert(e < MemoryRequestType_NUM);
  return e = MemoryRequestType(e+1);
}
