/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L2Cache_Controller.h"

L2Cache_State L2Cache_Controller::L2Cache_getState(Address param_addr)
{
  if ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).isPresent(param_addr))) {
    return ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(param_addr))).m_TBEState;
  } else {
    if ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).isPresent(param_addr))) {
      return ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(param_addr))).m_TBEState;
    } else {
      if ((L2Cache_isL2CacheTagPresent(param_addr))) {
        return ((L2Cache_getL2CacheEntry(param_addr))).m_CacheState;
      }
    }
  }
  return L2Cache_State_L2_NP;
}

