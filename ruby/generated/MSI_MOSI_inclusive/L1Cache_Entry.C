/** \file L1Cache_Entry.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "L1Cache_Entry.h"

/** \brief Print the state of this object */
void L1Cache_Entry::print(ostream& out) const
{
  out << "[L1Cache_Entry: ";
  out << "CacheState=" << m_CacheState << " ";
  out << "DataBlk=" << m_DataBlk << " ";
  out << "prefDWG=" << m_prefDWG << " ";
  out << "PrevLocalCacheState=" << m_PrevLocalCacheState << " ";
  out << "PrevRemoteCacheState=" << m_PrevRemoteCacheState << " ";
  out << "prevOwner=" << m_prevOwner << " ";
  out << "prevSharers=" << m_prevSharers << " ";
  out << "prefTypeRepl=" << m_prefTypeRepl << " ";
  out << "inst=" << m_inst << " ";
  out << "incl=" << m_incl << " ";
  out << "timeLoad=" << m_timeLoad << " ";
  out << "timeLast=" << m_timeLast << " ";
  out << "timeRepl=" << m_timeRepl << " ";
  out << "reused=" << m_reused << " ";
  out << "reusedL1=" << m_reusedL1 << " ";
  out << "uses=" << m_uses << " ";
  out << "owner=" << m_owner << " ";
  out << "NRU=" << m_NRU << " ";
  out << "]";
}
