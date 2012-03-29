/** \file TransientRequestType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef TransientRequestType_H
#define TransientRequestType_H

#include "Global.h"

/** \enum TransientRequestType
  * \brief ...
  */
enum TransientRequestType {
  TransientRequestType_FIRST,
  TransientRequestType_Undefined = TransientRequestType_FIRST,  /**<  */
  TransientRequestType_OffChip,  /**<  */
  TransientRequestType_OnChip,  /**<  */
  TransientRequestType_LocalTransient,  /**<  */
  TransientRequestType_NUM
};
TransientRequestType string_to_TransientRequestType(const string& str);
string TransientRequestType_to_string(const TransientRequestType& obj);
TransientRequestType &operator++( TransientRequestType &e);
ostream& operator<<(ostream& out, const TransientRequestType& obj);

#endif // TransientRequestType_H
