/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L2Cache_Controller.h"

bool L2Cache_Controller::L2Cache_isL2CacheTagPresent(Address param_addr)
{
  return (((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).isTagPresent(param_addr));
}

