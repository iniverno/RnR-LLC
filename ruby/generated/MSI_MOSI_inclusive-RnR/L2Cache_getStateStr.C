/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L2Cache_Controller.h"

string L2Cache_Controller::L2Cache_getStateStr(Address param_addr)
{
  return (L2Cache_State_to_string((L2Cache_getState(param_addr))));
}

