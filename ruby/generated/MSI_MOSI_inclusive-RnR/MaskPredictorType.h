/** \file MaskPredictorType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef MaskPredictorType_H
#define MaskPredictorType_H

#include "Global.h"

/** \enum MaskPredictorType
  * \brief ...
  */
enum MaskPredictorType {
  MaskPredictorType_FIRST,
  MaskPredictorType_Undefined = MaskPredictorType_FIRST,  /**< Undefined */
  MaskPredictorType_AlwaysUnicast,  /**< AlwaysUnicast */
  MaskPredictorType_TokenD,  /**< TokenD */
  MaskPredictorType_AlwaysBroadcast,  /**< AlwaysBroadcast */
  MaskPredictorType_TokenB,  /**< TokenB */
  MaskPredictorType_TokenNull,  /**< TokenNull */
  MaskPredictorType_Random,  /**< Random */
  MaskPredictorType_Pairwise,  /**< Pairwise */
  MaskPredictorType_Owner,  /**< Owner */
  MaskPredictorType_BroadcastIfShared,  /**< Broadcast-If-Shared */
  MaskPredictorType_BroadcastCounter,  /**< Broadcast Counter */
  MaskPredictorType_Group,  /**< Group */
  MaskPredictorType_Counter,  /**< Counter */
  MaskPredictorType_StickySpatial,  /**< StickySpatial */
  MaskPredictorType_OwnerBroadcast,  /**< Owner/Broadcast Hybrid */
  MaskPredictorType_OwnerGroup,  /**< Owner/Group Hybrid */
  MaskPredictorType_OwnerBroadcastMod,  /**< Owner/Broadcast Hybrid-Mod */
  MaskPredictorType_OwnerGroupMod,  /**< Owner/Group Hybrid-Mod */
  MaskPredictorType_LastNMasks,  /**< Last N Masks */
  MaskPredictorType_BandwidthAdaptive,  /**< Bandwidth Adaptive */
  MaskPredictorType_NUM
};
MaskPredictorType string_to_MaskPredictorType(const string& str);
string MaskPredictorType_to_string(const MaskPredictorType& obj);
MaskPredictorType &operator++( MaskPredictorType &e);
ostream& operator<<(ostream& out, const MaskPredictorType& obj);

#endif // MaskPredictorType_H
