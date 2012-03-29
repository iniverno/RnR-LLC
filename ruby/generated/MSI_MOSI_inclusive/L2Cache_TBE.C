/** \file L2Cache_TBE.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "L2Cache_TBE.h"

/** \brief Print the state of this object */
void L2Cache_TBE::print(ostream& out) const
{
  out << "[L2Cache_TBE: ";
  out << "Address=" << m_Address << " ";
  out << "TBEState=" << m_TBEState << " ";
  out << "DataBlk=" << m_DataBlk << " ";
  out << "NumPendingExtAcks=" << m_NumPendingExtAcks << " ";
  out << "NumPendingIntAcks=" << m_NumPendingIntAcks << " ";
  out << "Forward_GetS_IDs=" << m_Forward_GetS_IDs << " ";
  out << "L1_GetS_IDs=" << m_L1_GetS_IDs << " ";
  out << "Forward_GetX_ID=" << m_Forward_GetX_ID << " ";
  out << "L1_GetX_ID=" << m_L1_GetX_ID << " ";
  out << "InvalidatorID=" << m_InvalidatorID << " ";
  out << "ForwardGetX_AckCount=" << m_ForwardGetX_AckCount << " ";
  out << "isPrefetch=" << m_isPrefetch << " ";
  out << "isThreeHop=" << m_isThreeHop << " ";
  out << "validForwardedGetXId=" << m_validForwardedGetXId << " ";
  out << "validInvalidator=" << m_validInvalidator << " ";
  out << "isInternalRequestOnly=" << m_isInternalRequestOnly << " ";
  out << "prefetch=" << m_prefetch << " ";
  out << "usado=" << m_usado << " ";
  out << "owner=" << m_owner << " ";
  out << "epoch=" << m_epoch << " ";
  out << "]";
}
