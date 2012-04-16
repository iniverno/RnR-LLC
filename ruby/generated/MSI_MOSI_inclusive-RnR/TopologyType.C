/** \file TopologyType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "TopologyType.h"

ostream& operator<<(ostream& out, const TopologyType& obj)
{
  out << TopologyType_to_string(obj);
  out << flush;
  return out;
}

string TopologyType_to_string(const TopologyType& obj)
{
  switch(obj) {
  case TopologyType_CROSSBAR:
    return "CROSSBAR";
  case TopologyType_HIERARCHICAL_SWITCH:
    return "HIERARCHICAL_SWITCH";
  case TopologyType_TORUS_2D:
    return "TORUS_2D";
  case TopologyType_PT_TO_PT:
    return "PT_TO_PT";
  case TopologyType_FILE_SPECIFIED:
    return "FILE_SPECIFIED";
  default:
    ERROR_MSG("Invalid range for type TopologyType");
    return "";
  }
}

TopologyType string_to_TopologyType(const string& str)
{
  if (false) {
  } else if (str == "CROSSBAR") {
    return TopologyType_CROSSBAR;
  } else if (str == "HIERARCHICAL_SWITCH") {
    return TopologyType_HIERARCHICAL_SWITCH;
  } else if (str == "TORUS_2D") {
    return TopologyType_TORUS_2D;
  } else if (str == "PT_TO_PT") {
    return TopologyType_PT_TO_PT;
  } else if (str == "FILE_SPECIFIED") {
    return TopologyType_FILE_SPECIFIED;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type TopologyType");
  }
}

TopologyType& operator++( TopologyType& e) {
  assert(e < TopologyType_NUM);
  return e = TopologyType(e+1);
}
