/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L2Cache_Controller.h"

bool L2Cache_Controller::L2Cache_isOneSharerLeft(Address param_addr, MachineID param_requestor)
{
    if (ASSERT_FLAG && !(((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(param_addr))).m_Sharers).isElement(param_requestor)))) {
    cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:359, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
  return (((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(param_addr))).m_Sharers).count()) == (1));
}

