/** Auto generated C++ code started by symbols/Func.C:125 */

#include "Types.h"
#include "Chip.h"

GenericRequestType Chip::convertToGenericType(CoherenceRequestType param_type)
{
  if ((param_type == CoherenceRequestType_PUTX)) {
    return GenericRequestType_PUTX;
  } else {
    if ((param_type == CoherenceRequestType_GETS)) {
      return GenericRequestType_GETS;
    } else {
      if ((param_type == CoherenceRequestType_GET_INSTR)) {
        return GenericRequestType_GET_INSTR;
      } else {
        if ((param_type == CoherenceRequestType_GETX)) {
          return GenericRequestType_GETX;
        } else {
          if ((param_type == CoherenceRequestType_UPGRADE)) {
            return GenericRequestType_UPGRADE;
          } else {
            if ((param_type == CoherenceRequestType_PUTS)) {
              return GenericRequestType_PUTS;
            } else {
              if ((param_type == CoherenceRequestType_INV)) {
                return GenericRequestType_INV;
              } else {
                if ((param_type == CoherenceRequestType_INV_S)) {
                  return GenericRequestType_INV_S;
                } else {
                  if ((param_type == CoherenceRequestType_L1_DG)) {
                    return GenericRequestType_DOWNGRADE;
                  } else {
                    if ((param_type == CoherenceRequestType_WB_ACK)) {
                      return GenericRequestType_WB_ACK;
                    } else {
                      if ((param_type == CoherenceRequestType_EXE_ACK)) {
                        return GenericRequestType_EXE_ACK;
                      } else {
                        DEBUG_SLICC(MedPrio, "../protocols/MSI_MOSI_inclusive-msg.sm:154: ", param_type);
;
                                                cerr << "Runtime Error at ../protocols/MSI_MOSI_inclusive-msg.sm:155, Ruby Time: " << g_eventQueue_ptr->getTime() << ": " << ("invalid CoherenceRequestType") << ", PID: " << getpid() << endl;
char c; cerr << "press return to continue." << endl; cin.get(c); abort();

;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

