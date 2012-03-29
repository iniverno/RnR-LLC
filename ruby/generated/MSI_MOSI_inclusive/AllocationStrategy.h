/** \file AllocationStrategy.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef AllocationStrategy_H
#define AllocationStrategy_H

#include "Global.h"

/** \enum AllocationStrategy
  * \brief ...
  */
enum AllocationStrategy {
  AllocationStrategy_FIRST,
  AllocationStrategy_InMiddle = AllocationStrategy_FIRST,  /**<  */
  AllocationStrategy_InInvCorners,  /**<  */
  AllocationStrategy_InSharedSides,  /**<  */
  AllocationStrategy_StaticDist,  /**<  */
  AllocationStrategy_RandomBank,  /**<  */
  AllocationStrategy_FrequencyBank,  /**<  */
  AllocationStrategy_FrequencyBlock,  /**<  */
  AllocationStrategy_LRUBlock,  /**<  */
  AllocationStrategy_NUM
};
AllocationStrategy string_to_AllocationStrategy(const string& str);
string AllocationStrategy_to_string(const AllocationStrategy& obj);
AllocationStrategy &operator++( AllocationStrategy &e);
ostream& operator<<(ostream& out, const AllocationStrategy& obj);

#endif // AllocationStrategy_H
