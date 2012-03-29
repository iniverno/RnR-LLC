/** \file L1Cache_Entry.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "CacheEntryStatic.h"

/** \brief Print the state of this object */
void CacheEntryStatic::print(ostream& out) const
{
  out << "[CacheEntryStatic: ";
  out << "timeLoad=" << m_timeLoad << " ";
  out << "timeLast=" << m_timeLast << " ";
  out << "timeRepl=" << m_timeRepl << " ";
  out << "reused=" << m_reused << " ";
  out << "]";
}
