/** \file CacheRequestType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "CacheRequestTypeQuick.h"

ostream& operator<<(ostream& out, const CacheRequestTypeQuick& obj)
{
  out << CacheRequestTypeQuick_to_string(obj);
  out << flush;
  return out;
}

string CacheRequestTypeQuick_to_string(const CacheRequestTypeQuick& obj)
{
  switch(obj) {
  case CacheRequestTypeQuick_LD:
    return "LD";
  case CacheRequestTypeQuick_ST:
    return "ST";
  case CacheRequestTypeQuick_ATOMIC:
    return "ATOMIC";
  case CacheRequestTypeQuick_IFETCH:
    return "IFETCH";
  case CacheRequestTypeQuick_IO:
    return "IO";
  case CacheRequestTypeQuick_REPLACEMENT:
    return "REPLACEMENT";
  case CacheRequestTypeQuick_COMMIT:
    return "COMMIT";
  case CacheRequestTypeQuick_LD_XACT:
    return "LD_XACT";
  case CacheRequestTypeQuick_LDX_XACT:
    return "LDX_XACT";
  case CacheRequestTypeQuick_ST_XACT:
    return "ST_XACT";
  case CacheRequestTypeQuick_BEGIN_XACT:
    return "BEGIN_XACT";
  case CacheRequestTypeQuick_COMMIT_XACT:
    return "COMMIT_XACT";
  case CacheRequestTypeQuick_ABORT_XACT:
    return "ABORT_XACT";
  case CacheRequestTypeQuick_NULL:
    return "NULL";
  case CacheRequestTypeQuick_PREFETCH:
    return "PREFETCH";
  default:
    ERROR_MSG("Invalid range for type CacheRequestTypeQuick");
    return "";
  }
}

CacheRequestTypeQuick string_to_CacheRequestTypeQuick(const string& str)
{
  if (false) {
  } else if (str == "LD") {
    return CacheRequestTypeQuick_LD;
  } else if (str == "ST") {
    return CacheRequestTypeQuick_ST;
  } else if (str == "ATOMIC") {
    return CacheRequestTypeQuick_ATOMIC;
  } else if (str == "IFETCH") {
    return CacheRequestTypeQuick_IFETCH;
  } else if (str == "IO") {
    return CacheRequestTypeQuick_IO;
  } else if (str == "REPLACEMENT") {
    return CacheRequestTypeQuick_REPLACEMENT;
  } else if (str == "COMMIT") {
    return CacheRequestTypeQuick_COMMIT;
  } else if (str == "LD_XACT") {
    return CacheRequestTypeQuick_LD_XACT;
  } else if (str == "LDX_XACT") {
    return CacheRequestTypeQuick_LDX_XACT;
  } else if (str == "ST_XACT") {
    return CacheRequestTypeQuick_ST_XACT;
  } else if (str == "BEGIN_XACT") {
    return CacheRequestTypeQuick_BEGIN_XACT;
  } else if (str == "COMMIT_XACT") {
    return CacheRequestTypeQuick_COMMIT_XACT;
  } else if (str == "ABORT_XACT") {
    return CacheRequestTypeQuick_ABORT_XACT;
  } else if (str == "NULL") {
    return CacheRequestTypeQuick_NULL;
  } else if (str == "PREFETCH") {
    return CacheRequestTypeQuick_PREFETCH;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type CacheRequestTypeQuick");
  }
}

CacheRequestTypeQuick& operator++( CacheRequestTypeQuick& e) {
  assert(e < CacheRequestTypeQuick_NUM);
  return e = CacheRequestTypeQuick(e+1);
}
