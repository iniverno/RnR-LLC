/** \file L2Cache_Event.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "L2Cache_Event.h"

ostream& operator<<(ostream& out, const L2Cache_Event& obj)
{
  out << L2Cache_Event_to_string(obj);
  out << flush;
  return out;
}

string L2Cache_Event_to_string(const L2Cache_Event& obj)
{
  switch(obj) {
  case L2Cache_Event_L1_GET_INSTR:
    return "L1_GET_INSTR";
  case L2Cache_Event_L1_GETS:
    return "L1_GETS";
  case L2Cache_Event_L1_GETX:
    return "L1_GETX";
  case L2Cache_Event_L1_UPGRADE:
    return "L1_UPGRADE";
  case L2Cache_Event_L1_UPGRADE_no_others:
    return "L1_UPGRADE_no_others";
  case L2Cache_Event_L1_PUTX:
    return "L1_PUTX";
  case L2Cache_Event_L1_PUTX_last:
    return "L1_PUTX_last";
  case L2Cache_Event_L1_PUTX_old:
    return "L1_PUTX_old";
  case L2Cache_Event_L1_PUTS:
    return "L1_PUTS";
  case L2Cache_Event_L1_PUTS_last:
    return "L1_PUTS_last";
  case L2Cache_Event_L1_PUTS_old:
    return "L1_PUTS_old";
  case L2Cache_Event_PrefetchS:
    return "PrefetchS";
  case L2Cache_Event_PrefetchX:
    return "PrefetchX";
  case L2Cache_Event_Proc_int_ack:
    return "Proc_int_ack";
  case L2Cache_Event_Proc_last_int_ack:
    return "Proc_last_int_ack";
  case L2Cache_Event_Data_int_ack:
    return "Data_int_ack";
  case L2Cache_Event_Forwarded_GETS:
    return "Forwarded_GETS";
  case L2Cache_Event_Forwarded_GET_INSTR:
    return "Forwarded_GET_INSTR";
  case L2Cache_Event_Forwarded_GETX:
    return "Forwarded_GETX";
  case L2Cache_Event_L2_INV:
    return "L2_INV";
  case L2Cache_Event_Forwarded_PREFS:
    return "Forwarded_PREFS";
  case L2Cache_Event_Forwarded_PREFX:
    return "Forwarded_PREFX";
  case L2Cache_Event_L2_PrefetchS_Replacement:
    return "L2_PrefetchS_Replacement";
  case L2Cache_Event_L2_PrefetchX_Replacement:
    return "L2_PrefetchX_Replacement";
  case L2Cache_Event_L2_Replacement:
    return "L2_Replacement";
  case L2Cache_Event_Proc_ext_ack:
    return "Proc_ext_ack";
  case L2Cache_Event_Proc_last_ext_ack:
    return "Proc_last_ext_ack";
  case L2Cache_Event_Data_ext_ack_0:
    return "Data_ext_ack_0";
  case L2Cache_Event_PrefData_ext_ack_0:
    return "PrefData_ext_ack_0";
  case L2Cache_Event_Data_ext_ack_not_0:
    return "Data_ext_ack_not_0";
  case L2Cache_Event_Data_ext_ack_not_0_last:
    return "Data_ext_ack_not_0_last";
  case L2Cache_Event_Dir_WB_ack:
    return "Dir_WB_ack";
  case L2Cache_Event_Dir_exe_ack:
    return "Dir_exe_ack";
  case L2Cache_Event_Data_replacement:
    return "Data_replacement";
  default:
    ERROR_MSG("Invalid range for type L2Cache_Event");
    return "";
  }
}

L2Cache_Event string_to_L2Cache_Event(const string& str)
{
  if (false) {
  } else if (str == "L1_GET_INSTR") {
    return L2Cache_Event_L1_GET_INSTR;
  } else if (str == "L1_GETS") {
    return L2Cache_Event_L1_GETS;
  } else if (str == "L1_GETX") {
    return L2Cache_Event_L1_GETX;
  } else if (str == "L1_UPGRADE") {
    return L2Cache_Event_L1_UPGRADE;
  } else if (str == "L1_UPGRADE_no_others") {
    return L2Cache_Event_L1_UPGRADE_no_others;
  } else if (str == "L1_PUTX") {
    return L2Cache_Event_L1_PUTX;
  } else if (str == "L1_PUTX_last") {
    return L2Cache_Event_L1_PUTX_last;
  } else if (str == "L1_PUTX_old") {
    return L2Cache_Event_L1_PUTX_old;
  } else if (str == "L1_PUTS") {
    return L2Cache_Event_L1_PUTS;
  } else if (str == "L1_PUTS_last") {
    return L2Cache_Event_L1_PUTS_last;
  } else if (str == "L1_PUTS_old") {
    return L2Cache_Event_L1_PUTS_old;
  } else if (str == "PrefetchS") {
    return L2Cache_Event_PrefetchS;
  } else if (str == "PrefetchX") {
    return L2Cache_Event_PrefetchX;
  } else if (str == "Proc_int_ack") {
    return L2Cache_Event_Proc_int_ack;
  } else if (str == "Proc_last_int_ack") {
    return L2Cache_Event_Proc_last_int_ack;
  } else if (str == "Data_int_ack") {
    return L2Cache_Event_Data_int_ack;
  } else if (str == "Forwarded_GETS") {
    return L2Cache_Event_Forwarded_GETS;
  } else if (str == "Forwarded_GET_INSTR") {
    return L2Cache_Event_Forwarded_GET_INSTR;
  } else if (str == "Forwarded_GETX") {
    return L2Cache_Event_Forwarded_GETX;
  } else if (str == "L2_INV") {
    return L2Cache_Event_L2_INV;
  } else if (str == "Forwarded_PREFS") {
    return L2Cache_Event_Forwarded_PREFS;
  } else if (str == "Forwarded_PREFX") {
    return L2Cache_Event_Forwarded_PREFX;
  } else if (str == "L2_PrefetchS_Replacement") {
    return L2Cache_Event_L2_PrefetchS_Replacement;
  } else if (str == "L2_PrefetchX_Replacement") {
    return L2Cache_Event_L2_PrefetchX_Replacement;
  } else if (str == "L2_Replacement") {
    return L2Cache_Event_L2_Replacement;
  } else if (str == "Proc_ext_ack") {
    return L2Cache_Event_Proc_ext_ack;
  } else if (str == "Proc_last_ext_ack") {
    return L2Cache_Event_Proc_last_ext_ack;
  } else if (str == "Data_ext_ack_0") {
    return L2Cache_Event_Data_ext_ack_0;
  } else if (str == "PrefData_ext_ack_0") {
    return L2Cache_Event_PrefData_ext_ack_0;
  } else if (str == "Data_ext_ack_not_0") {
    return L2Cache_Event_Data_ext_ack_not_0;
  } else if (str == "Data_ext_ack_not_0_last") {
    return L2Cache_Event_Data_ext_ack_not_0_last;
  } else if (str == "Dir_WB_ack") {
    return L2Cache_Event_Dir_WB_ack;
  } else if (str == "Dir_exe_ack") {
    return L2Cache_Event_Dir_exe_ack;
  } else if (str == "Data_replacement") {
    return L2Cache_Event_Data_replacement;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type L2Cache_Event");
  }
}

L2Cache_Event& operator++( L2Cache_Event& e) {
  assert(e < L2Cache_Event_NUM);
  return e = L2Cache_Event(e+1);
}
