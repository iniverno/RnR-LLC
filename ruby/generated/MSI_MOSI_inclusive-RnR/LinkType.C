/** \file LinkType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "LinkType.h"

ostream& operator<<(ostream& out, const LinkType& obj)
{
  out << LinkType_to_string(obj);
  out << flush;
  return out;
}

string LinkType_to_string(const LinkType& obj)
{
  switch(obj) {
  case LinkType_RC_1500UM:
    return "RC_1500UM";
  case LinkType_RC_2500UM:
    return "RC_2500UM";
  case LinkType_TL_9000UM:
    return "TL_9000UM";
  case LinkType_TL_11000UM:
    return "TL_11000UM";
  case LinkType_TL_13000UM:
    return "TL_13000UM";
  case LinkType_NO_ENERGY:
    return "NO_ENERGY";
  case LinkType_NULL:
    return "NULL";
  default:
    ERROR_MSG("Invalid range for type LinkType");
    return "";
  }
}

LinkType string_to_LinkType(const string& str)
{
  if (false) {
  } else if (str == "RC_1500UM") {
    return LinkType_RC_1500UM;
  } else if (str == "RC_2500UM") {
    return LinkType_RC_2500UM;
  } else if (str == "TL_9000UM") {
    return LinkType_TL_9000UM;
  } else if (str == "TL_11000UM") {
    return LinkType_TL_11000UM;
  } else if (str == "TL_13000UM") {
    return LinkType_TL_13000UM;
  } else if (str == "NO_ENERGY") {
    return LinkType_NO_ENERGY;
  } else if (str == "NULL") {
    return LinkType_NULL;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type LinkType");
  }
}

LinkType& operator++( LinkType& e) {
  assert(e < LinkType_NUM);
  return e = LinkType(e+1);
}
