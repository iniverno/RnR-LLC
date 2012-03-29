/** \file L1Cache_Entry.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "CacheEntryQuick.h"

/** \brief Print the state of this object */
void CacheEntryQuick::print(ostream& out) const
{
  out << "[CacheEntryQuick: ";
  out << "Address=" << m_Address << " ";
//  out << "timeLoad=" << m_timeLoad << " ";
//  out << "timeLast=" << m_timeLast << " ";
//  out << "timeRepl=" << m_timeRepl << " ";
  out << "reused=" << m_reused << " ";
  out << "sharers=" << m_Sharers <<" ";
  out << "]";
}
