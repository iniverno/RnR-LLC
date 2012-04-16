/** \file TransitionResult.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef TransitionResult_H
#define TransitionResult_H

#include "Global.h"

/** \enum TransitionResult
  * \brief ...
  */
enum TransitionResult {
  TransitionResult_FIRST,
  TransitionResult_Valid = TransitionResult_FIRST,  /**< Valid transition */
  TransitionResult_ResourceStall,  /**< Stalled due to insufficient resources */
  TransitionResult_ProtocolStall,  /**< Protocol specified stall */
  TransitionResult_NUM
};
TransitionResult string_to_TransitionResult(const string& str);
string TransitionResult_to_string(const TransitionResult& obj);
TransitionResult &operator++( TransitionResult &e);
ostream& operator<<(ostream& out, const TransitionResult& obj);

#endif // TransitionResult_H
