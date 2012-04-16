/** \file GenericMachineType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef GenericMachineType_H
#define GenericMachineType_H

#include "Global.h"

/** \enum GenericMachineType
  * \brief ...
  */
enum GenericMachineType {
  GenericMachineType_FIRST,
  GenericMachineType_L1Cache = GenericMachineType_FIRST,  /**< L1 Cache Mach */
  GenericMachineType_L2Cache,  /**< L2 Cache Mach */
  GenericMachineType_L3Cache,  /**< L3 Cache Mach */
  GenericMachineType_Directory,  /**< Directory Mach */
  GenericMachineType_Collector,  /**< Collector Mach */
  GenericMachineType_L1Cache_wCC,  /**< L1 Cache Mach with Cache Coherence (used for miss latency profile) */
  GenericMachineType_L2Cache_wCC,  /**< L1 Cache Mach with Cache Coherence (used for miss latency profile) */
  GenericMachineType_VCache,  /**< Victim Cache */
  GenericMachineType_Dram,  /**< una dram */
  GenericMachineType_NULL,  /**< null mach type */
  GenericMachineType_NUM
};
GenericMachineType string_to_GenericMachineType(const string& str);
string GenericMachineType_to_string(const GenericMachineType& obj);
GenericMachineType &operator++( GenericMachineType &e);
ostream& operator<<(ostream& out, const GenericMachineType& obj);

#endif // GenericMachineType_H
