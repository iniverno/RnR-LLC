/** \file MemoryRequestType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef MemoryRequestType_H
#define MemoryRequestType_H

#include "Global.h"

/** \enum MemoryRequestType
  * \brief ...
  */
enum MemoryRequestType {
  MemoryRequestType_FIRST,
  MemoryRequestType_MEMORY_READ = MemoryRequestType_FIRST,  /**< Read request to memory */
  MemoryRequestType_MEMORY_WB,  /**< Write back data to memory */
  MemoryRequestType_MEMORY_DATA,  /**< Data read from memory */
  MemoryRequestType_MEMORY_ACK,  /**< Write to memory acknowledgement */
  MemoryRequestType_NUM
};
MemoryRequestType string_to_MemoryRequestType(const string& str);
string MemoryRequestType_to_string(const MemoryRequestType& obj);
MemoryRequestType &operator++( MemoryRequestType &e);
ostream& operator<<(ostream& out, const MemoryRequestType& obj);

#endif // MemoryRequestType_H
