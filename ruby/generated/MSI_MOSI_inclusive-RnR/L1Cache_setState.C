/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L1Cache_Controller.h"

void L1Cache_Controller::L1Cache_setState(Address param_addr, L1Cache_State param_state)
{
  if ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).isPresent(param_addr))) {
    ((((*(m_chip_ptr->m_L1Cache_L1_TBEs_vec[m_version]))).lookup(param_addr))).m_TBEState = param_state;
  }
  if ((L1Cache_isL1CacheTagPresent(param_addr))) {
    ((L1Cache_getL1CacheEntry(param_addr))).m_CacheState = param_state;
    ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).lookup(param_addr))).m_CacheState = param_state;
    if ((((param_state == L1Cache_State_L1_I) || (param_state == L1Cache_State_L1_SI)) || (param_state == L1Cache_State_L1_MI))) {
      (L1Cache_changeL1Permission(param_addr, AccessPermission_Invalid));
    } else {
      if ((param_state == L1Cache_State_L1_S)) {
        (L1Cache_changeL1Permission(param_addr, AccessPermission_Read_Only));
      } else {
        if ((param_state == L1Cache_State_L1_M)) {
          (L1Cache_changeL1Permission(param_addr, AccessPermission_Read_Write));
        } else {
          (L1Cache_changeL1Permission(param_addr, AccessPermission_Busy));
        }
      }
    }
  }
}

