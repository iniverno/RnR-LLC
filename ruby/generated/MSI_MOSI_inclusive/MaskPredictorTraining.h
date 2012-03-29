/** \file MaskPredictorTraining.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef MaskPredictorTraining_H
#define MaskPredictorTraining_H

#include "Global.h"

/** \enum MaskPredictorTraining
  * \brief ...
  */
enum MaskPredictorTraining {
  MaskPredictorTraining_FIRST,
  MaskPredictorTraining_Undefined = MaskPredictorTraining_FIRST,  /**< Undefined */
  MaskPredictorTraining_None,  /**< None */
  MaskPredictorTraining_Implicit,  /**< Implicit */
  MaskPredictorTraining_Explicit,  /**< Explicit */
  MaskPredictorTraining_Both,  /**< Both */
  MaskPredictorTraining_NUM
};
MaskPredictorTraining string_to_MaskPredictorTraining(const string& str);
string MaskPredictorTraining_to_string(const MaskPredictorTraining& obj);
MaskPredictorTraining &operator++( MaskPredictorTraining &e);
ostream& operator<<(ostream& out, const MaskPredictorTraining& obj);

#endif // MaskPredictorTraining_H
