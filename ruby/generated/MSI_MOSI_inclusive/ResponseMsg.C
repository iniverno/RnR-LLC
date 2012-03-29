/** \file ResponseMsg.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "ResponseMsg.h"

Allocator<ResponseMsg>* ResponseMsg::s_allocator_ptr = NULL;
/** \brief Print the state of this object */
void ResponseMsg::print(ostream& out) const
{
  out << "[ResponseMsg: ";
  out << "Address=" << m_Address << " ";
  out << "Type=" << m_Type << " ";
  out << "SenderMachId=" << m_SenderMachId << " ";
  out << "Destination=" << m_Destination << " ";
  out << "DataBlk=" << m_DataBlk << " ";
  out << "NumPendingExtAcks=" << m_NumPendingExtAcks << " ";
  out << "MessageSize=" << m_MessageSize << " ";
  out << "prefDWG=" << m_prefDWG << " ";
  out << "prevSharers=" << m_prevSharers << " ";
  out << "RequestorMachId=" << m_RequestorMachId << " ";
  out << "reuse=" << m_reuse << " ";
  out << "Time=" << getTime() << " ";
  out << "]";
}
