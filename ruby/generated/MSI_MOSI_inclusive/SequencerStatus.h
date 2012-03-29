/** \file SequencerStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef SequencerStatus_H
#define SequencerStatus_H

#include "Global.h"

/** \enum SequencerStatus
  * \brief ...
  */
enum SequencerStatus {
  SequencerStatus_FIRST,
  SequencerStatus_Idle = SequencerStatus_FIRST,  /**< Idle */
  SequencerStatus_Pending,  /**< Pending */
  SequencerStatus_NUM
};
SequencerStatus string_to_SequencerStatus(const string& str);
string SequencerStatus_to_string(const SequencerStatus& obj);
SequencerStatus &operator++( SequencerStatus &e);
ostream& operator<<(ostream& out, const SequencerStatus& obj);

#endif // SequencerStatus_H
