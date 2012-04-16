/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L2Cache_Controller.h"

void L2Cache_Controller::L2Cache_addSharer(Address param_addr, MachineID param_requestor)
{
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:372: ", m_machineID);
;
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:373: ", param_requestor);
;
  DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:374: ", param_addr);
;
    if (ASSERT_FLAG && !(((map_L1CacheMachId_to_L2Cache(param_addr, param_requestor)) == m_machineID))) {
    cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-RnR-L2cache.sm:375, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << "assert failure" << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

  }
;
  ((((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[m_version]))).lookup(param_addr))).m_Sharers).add(param_requestor));
}

