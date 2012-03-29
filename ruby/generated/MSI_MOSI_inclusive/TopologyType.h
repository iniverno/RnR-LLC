/** \file TopologyType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef TopologyType_H
#define TopologyType_H

#include "Global.h"

/** \enum TopologyType
  * \brief ...
  */
enum TopologyType {
  TopologyType_FIRST,
  TopologyType_CROSSBAR = TopologyType_FIRST,  /**< One node per chip, single switch crossbar */
  TopologyType_HIERARCHICAL_SWITCH,  /**< One node per chip, totally ordered hierarchical tree switched network */
  TopologyType_TORUS_2D,  /**< One node per chip, 2D torus */
  TopologyType_PT_TO_PT,  /**< One node per chip, Point to Point Network */
  TopologyType_FILE_SPECIFIED,  /**< described by the file NETWORK_FILE */
  TopologyType_NUM
};
TopologyType string_to_TopologyType(const string& str);
string TopologyType_to_string(const TopologyType& obj);
TopologyType &operator++( TopologyType &e);
ostream& operator<<(ostream& out, const TopologyType& obj);

#endif // TopologyType_H
