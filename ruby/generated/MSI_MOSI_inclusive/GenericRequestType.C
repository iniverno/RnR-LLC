/** \file GenericRequestType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "GenericRequestType.h"

ostream& operator<<(ostream& out, const GenericRequestType& obj)
{
  out << GenericRequestType_to_string(obj);
  out << flush;
  return out;
}

string GenericRequestType_to_string(const GenericRequestType& obj)
{
  switch(obj) {
  case GenericRequestType_GETS:
    return "GETS";
  case GenericRequestType_GET_INSTR:
    return "GET_INSTR";
  case GenericRequestType_GETX:
    return "GETX";
  case GenericRequestType_UPGRADE:
    return "UPGRADE";
  case GenericRequestType_DOWNGRADE:
    return "DOWNGRADE";
  case GenericRequestType_INV:
    return "INV";
  case GenericRequestType_INV_S:
    return "INV_S";
  case GenericRequestType_PUTS:
    return "PUTS";
  case GenericRequestType_PUTO:
    return "PUTO";
  case GenericRequestType_PUTX:
    return "PUTX";
  case GenericRequestType_L2_PF:
    return "L2_PF";
  case GenericRequestType_LD:
    return "LD";
  case GenericRequestType_ST:
    return "ST";
  case GenericRequestType_ATOMIC:
    return "ATOMIC";
  case GenericRequestType_IFETCH:
    return "IFETCH";
  case GenericRequestType_IO:
    return "IO";
  case GenericRequestType_NACK:
    return "NACK";
  case GenericRequestType_REPLACEMENT:
    return "REPLACEMENT";
  case GenericRequestType_WB_ACK:
    return "WB_ACK";
  case GenericRequestType_EXE_ACK:
    return "EXE_ACK";
  case GenericRequestType_COMMIT:
    return "COMMIT";
  case GenericRequestType_LD_XACT:
    return "LD_XACT";
  case GenericRequestType_LDX_XACT:
    return "LDX_XACT";
  case GenericRequestType_ST_XACT:
    return "ST_XACT";
  case GenericRequestType_BEGIN_XACT:
    return "BEGIN_XACT";
  case GenericRequestType_COMMIT_XACT:
    return "COMMIT_XACT";
  case GenericRequestType_ABORT_XACT:
    return "ABORT_XACT";
  case GenericRequestType_NULL:
    return "NULL";
  default:
    ERROR_MSG("Invalid range for type GenericRequestType");
    return "";
  }
}

GenericRequestType string_to_GenericRequestType(const string& str)
{
  if (false) {
  } else if (str == "GETS") {
    return GenericRequestType_GETS;
  } else if (str == "GET_INSTR") {
    return GenericRequestType_GET_INSTR;
  } else if (str == "GETX") {
    return GenericRequestType_GETX;
  } else if (str == "UPGRADE") {
    return GenericRequestType_UPGRADE;
  } else if (str == "DOWNGRADE") {
    return GenericRequestType_DOWNGRADE;
  } else if (str == "INV") {
    return GenericRequestType_INV;
  } else if (str == "INV_S") {
    return GenericRequestType_INV_S;
  } else if (str == "PUTS") {
    return GenericRequestType_PUTS;
  } else if (str == "PUTO") {
    return GenericRequestType_PUTO;
  } else if (str == "PUTX") {
    return GenericRequestType_PUTX;
  } else if (str == "L2_PF") {
    return GenericRequestType_L2_PF;
  } else if (str == "LD") {
    return GenericRequestType_LD;
  } else if (str == "ST") {
    return GenericRequestType_ST;
  } else if (str == "ATOMIC") {
    return GenericRequestType_ATOMIC;
  } else if (str == "IFETCH") {
    return GenericRequestType_IFETCH;
  } else if (str == "IO") {
    return GenericRequestType_IO;
  } else if (str == "NACK") {
    return GenericRequestType_NACK;
  } else if (str == "REPLACEMENT") {
    return GenericRequestType_REPLACEMENT;
  } else if (str == "WB_ACK") {
    return GenericRequestType_WB_ACK;
  } else if (str == "EXE_ACK") {
    return GenericRequestType_EXE_ACK;
  } else if (str == "COMMIT") {
    return GenericRequestType_COMMIT;
  } else if (str == "LD_XACT") {
    return GenericRequestType_LD_XACT;
  } else if (str == "LDX_XACT") {
    return GenericRequestType_LDX_XACT;
  } else if (str == "ST_XACT") {
    return GenericRequestType_ST_XACT;
  } else if (str == "BEGIN_XACT") {
    return GenericRequestType_BEGIN_XACT;
  } else if (str == "COMMIT_XACT") {
    return GenericRequestType_COMMIT_XACT;
  } else if (str == "ABORT_XACT") {
    return GenericRequestType_ABORT_XACT;
  } else if (str == "NULL") {
    return GenericRequestType_NULL;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type GenericRequestType");
  }
}

GenericRequestType& operator++( GenericRequestType& e) {
  assert(e < GenericRequestType_NUM);
  return e = GenericRequestType(e+1);
}
