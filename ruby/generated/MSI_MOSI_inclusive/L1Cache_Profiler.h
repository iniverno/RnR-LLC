// Auto generated C++ code started by symbols/StateMachine.C:673
// L1Cache: MSI Directory L1 Cache CMP

#ifndef L1Cache_PROFILER_H
#define L1Cache_PROFILER_H

#include "Global.h"
#include "L1Cache_State.h"
#include "L1Cache_Event.h"

class L1Cache_Profiler {
public:
  L1Cache_Profiler();
  void countTransition(L1Cache_State state, L1Cache_Event event);
  void possibleTransition(L1Cache_State state, L1Cache_Event event);
  void dumpStats(ostream& out) const;
  void clearStats();
private:
  int m_counters[L1Cache_State_NUM][L1Cache_Event_NUM];
  int m_event_counters[L1Cache_Event_NUM];
  bool m_possible[L1Cache_State_NUM][L1Cache_Event_NUM];
};
#endif // L1Cache_PROFILER_H
