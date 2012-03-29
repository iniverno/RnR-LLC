/** \file DetermGETXGeneratorStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef DetermGETXGeneratorStatus_H
#define DetermGETXGeneratorStatus_H

#include "Global.h"

/** \enum DetermGETXGeneratorStatus
  * \brief ...
  */
enum DetermGETXGeneratorStatus {
  DetermGETXGeneratorStatus_FIRST,
  DetermGETXGeneratorStatus_Thinking = DetermGETXGeneratorStatus_FIRST,  /**< Doing work before next action */
  DetermGETXGeneratorStatus_Store_Pending,  /**< Store pending */
  DetermGETXGeneratorStatus_Done,  /**< Done, waiting for end of run */
  DetermGETXGeneratorStatus_NUM
};
DetermGETXGeneratorStatus string_to_DetermGETXGeneratorStatus(const string& str);
string DetermGETXGeneratorStatus_to_string(const DetermGETXGeneratorStatus& obj);
DetermGETXGeneratorStatus &operator++( DetermGETXGeneratorStatus &e);
ostream& operator<<(ostream& out, const DetermGETXGeneratorStatus& obj);

#endif // DetermGETXGeneratorStatus_H
