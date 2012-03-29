/** \file MaskPredictorIndex.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef MaskPredictorIndex_H
#define MaskPredictorIndex_H

#include "Global.h"

/** \enum MaskPredictorIndex
  * \brief ...
  */
enum MaskPredictorIndex {
  MaskPredictorIndex_FIRST,
  MaskPredictorIndex_Undefined = MaskPredictorIndex_FIRST,  /**< Undefined */
  MaskPredictorIndex_DataBlock,  /**< Data Block */
  MaskPredictorIndex_PC,  /**< Program Counter */
  MaskPredictorIndex_NUM
};
MaskPredictorIndex string_to_MaskPredictorIndex(const string& str);
string MaskPredictorIndex_to_string(const MaskPredictorIndex& obj);
MaskPredictorIndex &operator++( MaskPredictorIndex &e);
ostream& operator<<(ostream& out, const MaskPredictorIndex& obj);

#endif // MaskPredictorIndex_H
