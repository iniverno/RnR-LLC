/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L2Cache_Controller.h"

void L2Cache_Controller::L2Cache_setState(Address param_addr, L2Cache_State param_state)
{
  if ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).isPresent(param_addr))) {
    ((((*(m_chip_ptr->m_L2Cache_L2_TBEs_vec[m_version]))).lookup(param_addr))).m_TBEState = param_state;
  }
  if ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).isPresent(param_addr))) {
    ((((*(m_chip_ptr->m_L2Cache_Pref_TBEs_vec[m_version]))).lookup(param_addr))).m_TBEState = param_state;
  }
  if ((L2Cache_isL2CacheTagPresent(param_addr))) {
    ((L2Cache_getL2CacheEntry(param_addr))).m_CacheState = param_state;
    if ((((((((((((((((param_state == L2Cache_State_L2_I) || (param_state == L2Cache_State_L2_SIC)) || (param_state == L2Cache_State_L2_SIV)) || (param_state == L2Cache_State_L2_PSIV)) || (param_state == L2Cache_State_L2_MIV)) || (param_state == L2Cache_State_L2_PMIV)) || (param_state == L2Cache_State_L2_MIN)) || (param_state == L2Cache_State_L2_PMIN)) || (param_state == L2Cache_State_L2_MIC)) || (param_state == L2Cache_State_L2_MIT)) || (param_state == L2Cache_State_L2_OIV)) || (param_state == L2Cache_State_L2_OIN)) || (param_state == L2Cache_State_L2_POIV)) || (param_state == L2Cache_State_L2_POIN)) || (param_state == L2Cache_State_L2_OIC))) {
      (L2Cache_changeL2Permission(param_addr, AccessPermission_Invalid));
    } else {
      if (((((param_state == L2Cache_State_L2_S) || (param_state == L2Cache_State_L2_O)) || (param_state == L2Cache_State_L2_SS)) || (param_state == L2Cache_State_L2_SO))) {
        (L2Cache_changeL2Permission(param_addr, AccessPermission_Read_Only));
      } else {
        if (((param_state == L2Cache_State_L2_OM) || (param_state == L2Cache_State_L2_OMV))) {
          (L2Cache_changeL2Permission(param_addr, AccessPermission_ReadUpgradingToWrite));
        } else {
          if ((param_state == L2Cache_State_L2_M)) {
            (L2Cache_changeL2Permission(param_addr, AccessPermission_Read_Write));
          } else {
            if ((param_state == L2Cache_State_L2_MT)) {
              (L2Cache_changeL2Permission(param_addr, AccessPermission_Stale));
            } else {
              (L2Cache_changeL2Permission(param_addr, AccessPermission_Busy));
            }
          }
        }
      }
    }
  }
}

