/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"
#include "L1Cache_Controller.h"

string L1Cache_Controller::L1Cache_getStateStr(Address param_addr)
{
  return (L1Cache_State_to_string((L1Cache_getState(param_addr))));
}

