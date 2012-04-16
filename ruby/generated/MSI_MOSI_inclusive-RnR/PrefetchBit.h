/** \file PrefetchBit.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef PrefetchBit_H
#define PrefetchBit_H

#include "Global.h"

/** \enum PrefetchBit
  * \brief ...
  */
enum PrefetchBit {
  PrefetchBit_FIRST,
  PrefetchBit_No = PrefetchBit_FIRST,  /**< No, not a prefetch */
  PrefetchBit_Yes,  /**< Yes, a prefetch */
  PrefetchBit_L1_HW,  /**< This is a L1 hardware prefetch */
  PrefetchBit_L2_HW,  /**< This is a L2 hardware prefetch */
  PrefetchBit_NUM
};
PrefetchBit string_to_PrefetchBit(const string& str);
string PrefetchBit_to_string(const PrefetchBit& obj);
PrefetchBit &operator++( PrefetchBit &e);
ostream& operator<<(ostream& out, const PrefetchBit& obj);

#endif // PrefetchBit_H
