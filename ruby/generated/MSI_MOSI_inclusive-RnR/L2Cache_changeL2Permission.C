/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L2Cache_Controller.h"

void L2Cache_Controller::L2Cache_changeL2Permission(Address param_addr, AccessPermission param_permission)
{
  if ((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).isTagPresent(param_addr))) {
    return (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).changePermission(param_addr, param_permission));
  }
}

