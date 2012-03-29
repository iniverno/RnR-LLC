/** \file MachineType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "MachineType.h"

ostream& operator<<(ostream& out, const MachineType& obj)
{
  out << MachineType_to_string(obj);
  out << flush;
  return out;
}

string MachineType_to_string(const MachineType& obj)
{
  switch(obj) {
  case MachineType_L1Cache:
    return "L1Cache";
  case MachineType_L2Cache:
    return "L2Cache";
  case MachineType_Directory:
    return "Directory";
  default:
    ERROR_MSG("Invalid range for type MachineType");
    return "";
  }
}

MachineType string_to_MachineType(const string& str)
{
  if (false) {
  } else if (str == "L1Cache") {
    return MachineType_L1Cache;
  } else if (str == "L2Cache") {
    return MachineType_L2Cache;
  } else if (str == "Directory") {
    return MachineType_Directory;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type MachineType");
  }
}

MachineType& operator++( MachineType& e) {
  assert(e < MachineType_NUM);
  return e = MachineType(e+1);
}

/** \brief returns the base vector index for each machine type to be used by NetDest 
  * 
  * \return the base vector index for each machine type to be used by NetDest
  * \see NetDest.h
  */
int MachineType_base_level(const MachineType& obj)
{
  switch(obj) {
  case MachineType_L1Cache:
    return 0;
  case MachineType_L2Cache:
    return 1;
  case MachineType_Directory:
    return 2;
  case MachineType_NUM:
    return 3;
  default:
    ERROR_MSG("Invalid range for type MachineType");
    return -1;
  }
}

/** \brief The return value indicates the number of components created
  * before a particular machine's components
  * 
  * \return the base number of components for each machine
  */
int MachineType_base_number(const MachineType& obj)
{
  switch(obj) {
  case MachineType_L1Cache:
    return 0;
  case MachineType_L2Cache:
    return 0+RubyConfig::numberOfL1Cache();
  case MachineType_Directory:
    return 0+RubyConfig::numberOfL1Cache()+RubyConfig::numberOfL2Cache();
  case MachineType_NUM:
    return 0+RubyConfig::numberOfL1Cache()+RubyConfig::numberOfL2Cache()+RubyConfig::numberOfDirectory();
  default:
    ERROR_MSG("Invalid range for type MachineType");
    return -1;
  }
}

/** \brief returns the total number of components for each machine
  * \return the total number of components for each machine
  */
int MachineType_base_count(const MachineType& obj)
{
  switch(obj) {
  case MachineType_L1Cache:
    return RubyConfig::numberOfL1Cache();
  case MachineType_L2Cache:
    return RubyConfig::numberOfL2Cache();
  case MachineType_Directory:
    return RubyConfig::numberOfDirectory();
  case MachineType_NUM:
  default:
    ERROR_MSG("Invalid range for type MachineType");
    return -1;
  }
}

/** \brief returns the total number of components for each machine
  * \return the total number of components for each machine
  */
int MachineType_chip_count(const MachineType& obj, NodeID chipID)
{
  switch(obj) {
  case MachineType_L1Cache:
    return RubyConfig::numberOfL1CachePerChip(chipID);
  case MachineType_L2Cache:
    return RubyConfig::numberOfL2CachePerChip(chipID);
  case MachineType_Directory:
    return RubyConfig::numberOfDirectoryPerChip(chipID);
  case MachineType_NUM:
  default:
    ERROR_MSG("Invalid range for type MachineType");
    return -1;
  }
}
