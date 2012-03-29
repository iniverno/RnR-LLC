/** \file Directory_Entry.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "Directory_Entry.h"

/** \brief Print the state of this object */
void Directory_Entry::print(ostream& out) const
{
  out << "[Directory_Entry: ";
  out << "DirectoryState=" << m_DirectoryState << " ";
  out << "Sharers=" << m_Sharers << " ";
  out << "DirOwner=" << m_DirOwner << " ";
  out << "ProcOwner=" << m_ProcOwner << " ";
  out << "DataBlk=" << m_DataBlk << " ";
  out << "time=" << m_time << " ";
  out << "Add=" << m_Add << " ";
  out << "]";
}
