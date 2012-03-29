/** \file LinkType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef LinkType_H
#define LinkType_H

#include "Global.h"

/** \enum LinkType
  * \brief ...
  */
enum LinkType {
  LinkType_FIRST,
  LinkType_RC_1500UM = LinkType_FIRST,  /**<  */
  LinkType_RC_2500UM,  /**<  */
  LinkType_TL_9000UM,  /**<  */
  LinkType_TL_11000UM,  /**<  */
  LinkType_TL_13000UM,  /**<  */
  LinkType_NO_ENERGY,  /**<  */
  LinkType_NULL,  /**<  */
  LinkType_NUM
};
LinkType string_to_LinkType(const string& str);
string LinkType_to_string(const LinkType& obj);
LinkType &operator++( LinkType &e);
ostream& operator<<(ostream& out, const LinkType& obj);

#endif // LinkType_H
