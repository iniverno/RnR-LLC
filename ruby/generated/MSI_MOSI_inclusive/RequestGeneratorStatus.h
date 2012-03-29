/** \file RequestGeneratorStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef RequestGeneratorStatus_H
#define RequestGeneratorStatus_H

#include "Global.h"

/** \enum RequestGeneratorStatus
  * \brief ...
  */
enum RequestGeneratorStatus {
  RequestGeneratorStatus_FIRST,
  RequestGeneratorStatus_Thinking = RequestGeneratorStatus_FIRST,  /**< Doing work between release and next acquire */
  RequestGeneratorStatus_Test_Pending,  /**< Test pending */
  RequestGeneratorStatus_Before_Swap,  /**< We're about to perform the swap */
  RequestGeneratorStatus_Swap_Pending,  /**< The swap used for test-and-send is pending */
  RequestGeneratorStatus_Holding,  /**< We are holding the lock performing the critical section */
  RequestGeneratorStatus_Release_Pending,  /**< The write for the release is pending */
  RequestGeneratorStatus_Done,  /**< Done, waiting for end of run */
  RequestGeneratorStatus_NUM
};
RequestGeneratorStatus string_to_RequestGeneratorStatus(const string& str);
string RequestGeneratorStatus_to_string(const RequestGeneratorStatus& obj);
RequestGeneratorStatus &operator++( RequestGeneratorStatus &e);
ostream& operator<<(ostream& out, const RequestGeneratorStatus& obj);

#endif // RequestGeneratorStatus_H
