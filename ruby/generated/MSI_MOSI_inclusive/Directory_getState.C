/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "Directory_Controller.h"

Directory_State Directory_Controller::Directory_getState(Address param_addr)
{
  if ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).isPresent(param_addr))) {
    return ((((*(m_chip_ptr->m_Directory_directory_vec[m_version]))).lookup(param_addr))).m_DirectoryState;
  }
  return Directory_State_NP;
}

