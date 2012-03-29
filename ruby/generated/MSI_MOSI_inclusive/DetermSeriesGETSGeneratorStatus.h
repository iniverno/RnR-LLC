/** \file DetermSeriesGETSGeneratorStatus.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef DetermSeriesGETSGeneratorStatus_H
#define DetermSeriesGETSGeneratorStatus_H

#include "Global.h"

/** \enum DetermSeriesGETSGeneratorStatus
  * \brief ...
  */
enum DetermSeriesGETSGeneratorStatus {
  DetermSeriesGETSGeneratorStatus_FIRST,
  DetermSeriesGETSGeneratorStatus_Thinking = DetermSeriesGETSGeneratorStatus_FIRST,  /**< Doing work before next action */
  DetermSeriesGETSGeneratorStatus_Load_Pending,  /**< Load pending */
  DetermSeriesGETSGeneratorStatus_Done,  /**< Done, waiting for end of run */
  DetermSeriesGETSGeneratorStatus_NUM
};
DetermSeriesGETSGeneratorStatus string_to_DetermSeriesGETSGeneratorStatus(const string& str);
string DetermSeriesGETSGeneratorStatus_to_string(const DetermSeriesGETSGeneratorStatus& obj);
DetermSeriesGETSGeneratorStatus &operator++( DetermSeriesGETSGeneratorStatus &e);
ostream& operator<<(ostream& out, const DetermSeriesGETSGeneratorStatus& obj);

#endif // DetermSeriesGETSGeneratorStatus_H
