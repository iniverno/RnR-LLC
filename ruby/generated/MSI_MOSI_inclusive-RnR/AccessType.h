/** \file AccessType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef AccessType_H
#define AccessType_H

#include "Global.h"

/** \enum AccessType
  * \brief ...
  */
enum AccessType {
  AccessType_FIRST,
  AccessType_Read = AccessType_FIRST,  /**< Reading from cache */
  AccessType_Write,  /**< Writing to cache */
  AccessType_NUM
};
AccessType string_to_AccessType(const string& str);
string AccessType_to_string(const AccessType& obj);
AccessType &operator++( AccessType &e);
ostream& operator<<(ostream& out, const AccessType& obj);

#endif // AccessType_H
