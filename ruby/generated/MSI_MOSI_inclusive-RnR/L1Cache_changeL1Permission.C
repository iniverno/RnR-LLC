/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L1Cache_Controller.h"

void L1Cache_Controller::L1Cache_changeL1Permission(Address param_addr, AccessPermission param_permission)
{
  if ((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(param_addr))) {
    (((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).changePermission(param_addr, param_permission));
    ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).lookup(param_addr))).m_incl = (2);
    return (((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).changePermission(param_addr, param_permission));
  } else {
    if ((((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).isTagPresent(param_addr))) {
      (((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).changePermission(param_addr, param_permission));
      ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).lookup(param_addr))).m_incl = (1);
      return (((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).changePermission(param_addr, param_permission));
    } else {
      ((((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).lookup(param_addr))).m_incl = (0);
      return (((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).changePermission(param_addr, param_permission));
    }
  }
}

