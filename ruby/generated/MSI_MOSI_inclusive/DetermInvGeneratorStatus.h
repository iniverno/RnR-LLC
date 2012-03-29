/** \file DetermInvGeneratorStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef DetermInvGeneratorStatus_H
#define DetermInvGeneratorStatus_H

#include "Global.h"

/** \enum DetermInvGeneratorStatus
  * \brief ...
  */
enum DetermInvGeneratorStatus {
  DetermInvGeneratorStatus_FIRST,
  DetermInvGeneratorStatus_Thinking = DetermInvGeneratorStatus_FIRST,  /**< Doing work before next action */
  DetermInvGeneratorStatus_Store_Pending,  /**< Store pending */
  DetermInvGeneratorStatus_Load_Complete,  /**< Load complete */
  DetermInvGeneratorStatus_Load_Pending,  /**< Load pending */
  DetermInvGeneratorStatus_Done,  /**< Done, waiting for end of run */
  DetermInvGeneratorStatus_NUM
};
DetermInvGeneratorStatus string_to_DetermInvGeneratorStatus(const string& str);
string DetermInvGeneratorStatus_to_string(const DetermInvGeneratorStatus& obj);
DetermInvGeneratorStatus &operator++( DetermInvGeneratorStatus &e);
ostream& operator<<(ostream& out, const DetermInvGeneratorStatus& obj);

#endif // DetermInvGeneratorStatus_H
