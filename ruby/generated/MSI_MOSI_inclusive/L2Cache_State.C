/** \file L2Cache_State.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "L2Cache_State.h"

ostream& operator<<(ostream& out, const L2Cache_State& obj)
{
  out << L2Cache_State_to_string(obj);
  out << flush;
  return out;
}

string L2Cache_State_to_string(const L2Cache_State& obj)
{
  switch(obj) {
  case L2Cache_State_L2_NP:
    return "L2_NP";
  case L2Cache_State_L2_I:
    return "L2_I";
  case L2Cache_State_L2_S:
    return "L2_S";
  case L2Cache_State_L2_O:
    return "L2_O";
  case L2Cache_State_L2_M:
    return "L2_M";
  case L2Cache_State_L2_SS:
    return "L2_SS";
  case L2Cache_State_L2_SO:
    return "L2_SO";
  case L2Cache_State_L2_MT:
    return "L2_MT";
  case L2Cache_State_L2_IS:
    return "L2_IS";
  case L2Cache_State_L2_IPS:
    return "L2_IPS";
  case L2Cache_State_L2_IPX:
    return "L2_IPX";
  case L2Cache_State_L2_IPXZ:
    return "L2_IPXZ";
  case L2Cache_State_L2_ISZ:
    return "L2_ISZ";
  case L2Cache_State_L2_ISI:
    return "L2_ISI";
  case L2Cache_State_L2_IMV:
    return "L2_IMV";
  case L2Cache_State_L2_MV:
    return "L2_MV";
  case L2Cache_State_L2_IM:
    return "L2_IM";
  case L2Cache_State_L2_IMO:
    return "L2_IMO";
  case L2Cache_State_L2_IMI:
    return "L2_IMI";
  case L2Cache_State_L2_IMZ:
    return "L2_IMZ";
  case L2Cache_State_L2_IMOI:
    return "L2_IMOI";
  case L2Cache_State_L2_IMOZ:
    return "L2_IMOZ";
  case L2Cache_State_L2_SIC:
    return "L2_SIC";
  case L2Cache_State_L2_SIV:
    return "L2_SIV";
  case L2Cache_State_L2_PSIV:
    return "L2_PSIV";
  case L2Cache_State_L2_MIV:
    return "L2_MIV";
  case L2Cache_State_L2_PMIV:
    return "L2_PMIV";
  case L2Cache_State_L2_MIN:
    return "L2_MIN";
  case L2Cache_State_L2_PMIN:
    return "L2_PMIN";
  case L2Cache_State_L2_MIC:
    return "L2_MIC";
  case L2Cache_State_L2_MIT:
    return "L2_MIT";
  case L2Cache_State_L2_MO:
    return "L2_MO";
  case L2Cache_State_L2_MOIC:
    return "L2_MOIC";
  case L2Cache_State_L2_MOICR:
    return "L2_MOICR";
  case L2Cache_State_L2_MOZ:
    return "L2_MOZ";
  case L2Cache_State_L2_OIV:
    return "L2_OIV";
  case L2Cache_State_L2_POIV:
    return "L2_POIV";
  case L2Cache_State_L2_OIN:
    return "L2_OIN";
  case L2Cache_State_L2_POIN:
    return "L2_POIN";
  case L2Cache_State_L2_OIC:
    return "L2_OIC";
  case L2Cache_State_L2_OMV:
    return "L2_OMV";
  case L2Cache_State_L2_OM:
    return "L2_OM";
  case L2Cache_State_L2_SM:
    return "L2_SM";
  case L2Cache_State_L2_SSM:
    return "L2_SSM";
  case L2Cache_State_L2_SSMV:
    return "L2_SSMV";
  case L2Cache_State_L2_IPI:
    return "L2_IPI";
  case L2Cache_State_L2_IPSS:
    return "L2_IPSS";
  default:
    ERROR_MSG("Invalid range for type L2Cache_State");
    return "";
  }
}

L2Cache_State string_to_L2Cache_State(const string& str)
{
  if (false) {
  } else if (str == "L2_NP") {
    return L2Cache_State_L2_NP;
  } else if (str == "L2_I") {
    return L2Cache_State_L2_I;
  } else if (str == "L2_S") {
    return L2Cache_State_L2_S;
  } else if (str == "L2_O") {
    return L2Cache_State_L2_O;
  } else if (str == "L2_M") {
    return L2Cache_State_L2_M;
  } else if (str == "L2_SS") {
    return L2Cache_State_L2_SS;
  } else if (str == "L2_SO") {
    return L2Cache_State_L2_SO;
  } else if (str == "L2_MT") {
    return L2Cache_State_L2_MT;
  } else if (str == "L2_IS") {
    return L2Cache_State_L2_IS;
  } else if (str == "L2_IPS") {
    return L2Cache_State_L2_IPS;
  } else if (str == "L2_IPX") {
    return L2Cache_State_L2_IPX;
  } else if (str == "L2_IPXZ") {
    return L2Cache_State_L2_IPXZ;
  } else if (str == "L2_ISZ") {
    return L2Cache_State_L2_ISZ;
  } else if (str == "L2_ISI") {
    return L2Cache_State_L2_ISI;
  } else if (str == "L2_IMV") {
    return L2Cache_State_L2_IMV;
  } else if (str == "L2_MV") {
    return L2Cache_State_L2_MV;
  } else if (str == "L2_IM") {
    return L2Cache_State_L2_IM;
  } else if (str == "L2_IMO") {
    return L2Cache_State_L2_IMO;
  } else if (str == "L2_IMI") {
    return L2Cache_State_L2_IMI;
  } else if (str == "L2_IMZ") {
    return L2Cache_State_L2_IMZ;
  } else if (str == "L2_IMOI") {
    return L2Cache_State_L2_IMOI;
  } else if (str == "L2_IMOZ") {
    return L2Cache_State_L2_IMOZ;
  } else if (str == "L2_SIC") {
    return L2Cache_State_L2_SIC;
  } else if (str == "L2_SIV") {
    return L2Cache_State_L2_SIV;
  } else if (str == "L2_PSIV") {
    return L2Cache_State_L2_PSIV;
  } else if (str == "L2_MIV") {
    return L2Cache_State_L2_MIV;
  } else if (str == "L2_PMIV") {
    return L2Cache_State_L2_PMIV;
  } else if (str == "L2_MIN") {
    return L2Cache_State_L2_MIN;
  } else if (str == "L2_PMIN") {
    return L2Cache_State_L2_PMIN;
  } else if (str == "L2_MIC") {
    return L2Cache_State_L2_MIC;
  } else if (str == "L2_MIT") {
    return L2Cache_State_L2_MIT;
  } else if (str == "L2_MO") {
    return L2Cache_State_L2_MO;
  } else if (str == "L2_MOIC") {
    return L2Cache_State_L2_MOIC;
  } else if (str == "L2_MOICR") {
    return L2Cache_State_L2_MOICR;
  } else if (str == "L2_MOZ") {
    return L2Cache_State_L2_MOZ;
  } else if (str == "L2_OIV") {
    return L2Cache_State_L2_OIV;
  } else if (str == "L2_POIV") {
    return L2Cache_State_L2_POIV;
  } else if (str == "L2_OIN") {
    return L2Cache_State_L2_OIN;
  } else if (str == "L2_POIN") {
    return L2Cache_State_L2_POIN;
  } else if (str == "L2_OIC") {
    return L2Cache_State_L2_OIC;
  } else if (str == "L2_OMV") {
    return L2Cache_State_L2_OMV;
  } else if (str == "L2_OM") {
    return L2Cache_State_L2_OM;
  } else if (str == "L2_SM") {
    return L2Cache_State_L2_SM;
  } else if (str == "L2_SSM") {
    return L2Cache_State_L2_SSM;
  } else if (str == "L2_SSMV") {
    return L2Cache_State_L2_SSMV;
  } else if (str == "L2_IPI") {
    return L2Cache_State_L2_IPI;
  } else if (str == "L2_IPSS") {
    return L2Cache_State_L2_IPSS;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type L2Cache_State");
  }
}

L2Cache_State& operator++( L2Cache_State& e) {
  assert(e < L2Cache_State_NUM);
  return e = L2Cache_State(e+1);
}
