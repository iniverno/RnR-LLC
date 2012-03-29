/** \file TesterStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef TesterStatus_H
#define TesterStatus_H

#include "Global.h"

/** \enum TesterStatus
  * \brief ...
  */
enum TesterStatus {
  TesterStatus_FIRST,
  TesterStatus_Idle = TesterStatus_FIRST,  /**< Idle */
  TesterStatus_Action_Pending,  /**< Action Pending */
  TesterStatus_Ready,  /**< Ready */
  TesterStatus_Check_Pending,  /**< Check Pending */
  TesterStatus_NUM
};
TesterStatus string_to_TesterStatus(const string& str);
string TesterStatus_to_string(const TesterStatus& obj);
TesterStatus &operator++( TesterStatus &e);
ostream& operator<<(ostream& out, const TesterStatus& obj);

#endif // TesterStatus_H
