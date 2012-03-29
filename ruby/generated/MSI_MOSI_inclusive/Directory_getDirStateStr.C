/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "Directory_Controller.h"

string Directory_Controller::Directory_getDirStateStr(Address param_addr)
{
  return (Directory_State_to_string((Directory_getState(param_addr))));
}

