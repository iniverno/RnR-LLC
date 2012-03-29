// Auto generated C++ code started by symbols/StateMachine.C:673
// L2Cache: MOSI Directory L2 Cache CMP

#ifndef L2Cache_PROFILER_H
#define L2Cache_PROFILER_H

#include "Global.h"
#include "L2Cache_State.h"
#include "L2Cache_Event.h"

class L2Cache_Profiler {
public:
  L2Cache_Profiler();
  void countTransition(L2Cache_State state, L2Cache_Event event);
  void possibleTransition(L2Cache_State state, L2Cache_Event event);
  void dumpStats(ostream& out) const;
  void clearStats();
private:
  int m_counters[L2Cache_State_NUM][L2Cache_Event_NUM];
  int m_event_counters[L2Cache_Event_NUM];
  bool m_possible[L2Cache_State_NUM][L2Cache_Event_NUM];
};
#endif // L2Cache_PROFILER_H
