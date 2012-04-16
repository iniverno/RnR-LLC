/** \file CacheRequestType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "CacheRequestType.h"

ostream& operator<<(ostream& out, const CacheRequestType& obj)
{
  out << CacheRequestType_to_string(obj);
  out << flush;
  return out;
}

string CacheRequestType_to_string(const CacheRequestType& obj)
{
  switch(obj) {
  case CacheRequestType_LD:
    return "LD";
  case CacheRequestType_ST:
    return "ST";
  case CacheRequestType_ATOMIC:
    return "ATOMIC";
  case CacheRequestType_IFETCH:
    return "IFETCH";
  case CacheRequestType_IO:
    return "IO";
  case CacheRequestType_REPLACEMENT:
    return "REPLACEMENT";
  case CacheRequestType_COMMIT:
    return "COMMIT";
  case CacheRequestType_LD_XACT:
    return "LD_XACT";
  case CacheRequestType_LDX_XACT:
    return "LDX_XACT";
  case CacheRequestType_ST_XACT:
    return "ST_XACT";
  case CacheRequestType_BEGIN_XACT:
    return "BEGIN_XACT";
  case CacheRequestType_COMMIT_XACT:
    return "COMMIT_XACT";
  case CacheRequestType_ABORT_XACT:
    return "ABORT_XACT";
  case CacheRequestType_NULL:
    return "NULL";
  default:
    ERROR_MSG("Invalid range for type CacheRequestType");
    return "";
  }
}

CacheRequestType string_to_CacheRequestType(const string& str)
{
  if (false) {
  } else if (str == "LD") {
    return CacheRequestType_LD;
  } else if (str == "ST") {
    return CacheRequestType_ST;
  } else if (str == "ATOMIC") {
    return CacheRequestType_ATOMIC;
  } else if (str == "IFETCH") {
    return CacheRequestType_IFETCH;
  } else if (str == "IO") {
    return CacheRequestType_IO;
  } else if (str == "REPLACEMENT") {
    return CacheRequestType_REPLACEMENT;
  } else if (str == "COMMIT") {
    return CacheRequestType_COMMIT;
  } else if (str == "LD_XACT") {
    return CacheRequestType_LD_XACT;
  } else if (str == "LDX_XACT") {
    return CacheRequestType_LDX_XACT;
  } else if (str == "ST_XACT") {
    return CacheRequestType_ST_XACT;
  } else if (str == "BEGIN_XACT") {
    return CacheRequestType_BEGIN_XACT;
  } else if (str == "COMMIT_XACT") {
    return CacheRequestType_COMMIT_XACT;
  } else if (str == "ABORT_XACT") {
    return CacheRequestType_ABORT_XACT;
  } else if (str == "NULL") {
    return CacheRequestType_NULL;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type CacheRequestType");
  }
}

CacheRequestType& operator++( CacheRequestType& e) {
  assert(e < CacheRequestType_NUM);
  return e = CacheRequestType(e+1);
}
