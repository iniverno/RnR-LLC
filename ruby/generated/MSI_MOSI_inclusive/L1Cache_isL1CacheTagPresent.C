/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L1Cache_Controller.h"

bool L1Cache_Controller::L1Cache_isL1CacheTagPresent(Address param_addr)
{
  return (((((*(m_chip_ptr->m_L1Cache_L1DcacheMemory_vec[m_version]))).isTagPresent(param_addr)) || (((*(m_chip_ptr->m_L1Cache_L1IcacheMemory_vec[m_version]))).isTagPresent(param_addr))) || (((*(m_chip_ptr->m_L1Cache_L15cacheMemory_vec[m_version]))).isTagPresent(param_addr)));
}

