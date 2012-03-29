/** \file L2Cache_Entry.C
  * 
  * Auto generated C++ code started by symbols/Type.C:479
  */

#include "L2Cache_Entry.h"

/** \brief Print the state of this object */
void L2Cache_Entry::print(ostream& out) const
{
  out << "[L2Cache_Entry: ";
  out << "CacheState=" << m_CacheState << " ";
  out << "Sharers=" << m_Sharers << " ";
  out << "DataBlk=" << m_DataBlk << " ";
  out << "prefetch=" << m_prefetch << " ";
  out << "PC=" << m_PC << " ";
  out << "ZeroBit=" << m_ZeroBit << " ";
  out << "reused=" << m_reused << " ";
  out << "reused2=" << m_reused2 << " ";
  out << "reused3=" << m_reused3 << " ";
  out << "prefDWG=" << m_prefDWG << " ";
  out << "PrevLocalCacheState=" << m_PrevLocalCacheState << " ";
  out << "PrevRemoteCacheState=" << m_PrevRemoteCacheState << " ";
  out << "prevOwner=" << m_prevOwner << " ";
  out << "owner=" << m_owner << " ";
  out << "prevSharers=" << m_prevSharers << " ";
  out << "prefTypeRepl=" << m_prefTypeRepl << " ";
  out << "epoch=" << m_epoch << " ";
  out << "uses=" << m_uses << " ";
  out << "timeLoad=" << m_timeLoad << " ";
  out << "timeLast=" << m_timeLast << " ";
  out << "timeRepl=" << m_timeRepl << " ";
  out << "reuseL1=" << m_reuseL1 << " ";
  out << "instr=" << m_instr << " ";
  out << "RRPV=" << m_RRPV << " ";
  out << "NRU=" << m_NRU << " ";
  out << "sign=" << m_sign << " ";
  out << "]";
}
