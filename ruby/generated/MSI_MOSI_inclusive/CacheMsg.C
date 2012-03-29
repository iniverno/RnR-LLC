/** \file CacheMsg.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "CacheMsg.h"

Allocator<CacheMsg>* CacheMsg::s_allocator_ptr = NULL;
/** \brief Print the state of this object */
void CacheMsg::print(ostream& out) const
{
  out << "[CacheMsg: ";
  out << "Address=" << m_Address << " ";
  out << "PhysicalAddress=" << m_PhysicalAddress << " ";
  out << "Type=" << m_Type << " ";
  out << "ProgramCounter=" << m_ProgramCounter << " ";
  out << "AccessMode=" << m_AccessMode << " ";
  out << "Size=" << m_Size << " ";
  out << "Prefetch=" << m_Prefetch << " ";
  out << "Version=" << m_Version << " ";
  out << "LogicalAddress=" << m_LogicalAddress << " ";
  out << "ThreadID=" << m_ThreadID << " ";
  out << "Timestamp=" << m_Timestamp << " ";
  out << "ExposedAction=" << m_ExposedAction << " ";
  out << "Time=" << getTime() << " ";
  out << "]";
}
