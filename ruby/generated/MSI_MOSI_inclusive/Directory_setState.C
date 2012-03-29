/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "Directory_Controller.h"

void Directory_Controller::Directory_setState(Address param_addr, Directory_State param_state)
{
  if ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).isPresent(param_addr))) {
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-dir.sm:147: ", param_addr);
;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-dir.sm:148: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(param_addr))).m_DirectoryState);
;
    ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(param_addr))).m_DirectoryState = param_state;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-dir.sm:150: ", ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(param_addr))).m_DirectoryState);
;
    DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-dir.sm:151: ", param_state);
;
  }
}

