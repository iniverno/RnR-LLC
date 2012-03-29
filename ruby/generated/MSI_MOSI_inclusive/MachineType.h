/** \file MachineType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef MachineType_H
#define MachineType_H

#include "Global.h"
#include "RubyConfig.h"


/** \enum MachineType
  * \brief No description avaliable
  */
enum MachineType {
  MachineType_FIRST,
  MachineType_L1Cache = MachineType_FIRST,  /**< No description avaliable */
  MachineType_L2Cache,  /**< No description avaliable */
  MachineType_Directory,  /**< No description avaliable */
  MachineType_NUM
};
MachineType string_to_MachineType(const string& str);
string MachineType_to_string(const MachineType& obj);
MachineType &operator++( MachineType &e);
int MachineType_base_level(const MachineType& obj);
int MachineType_base_number(const MachineType& obj);
int MachineType_base_count(const MachineType& obj);
int MachineType_chip_count(const MachineType& obj, NodeID chipID);
#define MACHINETYPE_L1Cache 1
#define MACHINETYPE_L2Cache 1
#define MACHINETYPE_Directory 1
ostream& operator<<(ostream& out, const MachineType& obj);

#endif // MachineType_H
