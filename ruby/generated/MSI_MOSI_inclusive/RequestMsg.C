/** \file RequestMsg.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "RequestMsg.h"

Allocator<RequestMsg>* RequestMsg::s_allocator_ptr = NULL;
/** \brief Print the state of this object */
void RequestMsg::print(ostream& out) const
{
  out << "[RequestMsg: ";
  out << "Address=" << m_Address << " ";
  out << "Type=" << m_Type << " ";
  out << "AccessMode=" << m_AccessMode << " ";
  out << "RequestorMachId=" << m_RequestorMachId << " ";
  out << "Destination=" << m_Destination << " ";
  out << "DataBlk=" << m_DataBlk << " ";
  out << "NumPendingExtAcks=" << m_NumPendingExtAcks << " ";
  out << "MessageSize=" << m_MessageSize << " ";
  out << "L1CacheStateStr=" << m_L1CacheStateStr << " ";
  out << "L2CacheStateStr=" << m_L2CacheStateStr << " ";
  out << "Prefetch=" << m_Prefetch << " ";
  out << "ProgramCounter=" << m_ProgramCounter << " ";
  out << "prefDWG=" << m_prefDWG << " ";
  out << "Type_UG_PREFETCH=" << m_Type_UG_PREFETCH << " ";
  out << "coreID=" << m_coreID << " ";
  out << "epoch=" << m_epoch << " ";
  out << "reuse=" << m_reuse << " ";
  out << "Time=" << getTime() << " ";
  out << "]";
}
