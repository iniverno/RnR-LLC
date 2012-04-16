/** \file MemoryMsg.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "MemoryMsg.h"

Allocator<MemoryMsg>* MemoryMsg::s_allocator_ptr = NULL;
/** \brief Print the state of this object */
void MemoryMsg::print(ostream& out) const
{
  out << "[MemoryMsg: ";
  out << "Address=" << m_Address << " ";
  out << "Type=" << m_Type << " ";
  out << "Sender=" << m_Sender << " ";
  out << "OriginalRequestorMachId=" << m_OriginalRequestorMachId << " ";
  out << "DataBlk=" << m_DataBlk << " ";
  out << "MessageSize=" << m_MessageSize << " ";
  out << "Prefetch=" << m_Prefetch << " ";
  out << "ReadX=" << m_ReadX << " ";
  out << "Acks=" << m_Acks << " ";
  out << "Time=" << getTime() << " ";
  out << "]";
}
