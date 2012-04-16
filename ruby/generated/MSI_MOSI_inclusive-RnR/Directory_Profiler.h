// Auto generated C++ code started by symbols/StateMachine.C:673
// Directory: MOSI Directory Optimized

#ifndef Directory_PROFILER_H
#define Directory_PROFILER_H

#include "Global.h"
#include "Directory_State.h"
#include "Directory_Event.h"

class Directory_Profiler {
public:
  Directory_Profiler();
  void countTransition(Directory_State state, Directory_Event event);
  void possibleTransition(Directory_State state, Directory_Event event);
  void dumpStats(ostream& out) const;
  void clearStats();
private:
  int m_counters[Directory_State_NUM][Directory_Event_NUM];
  int m_event_counters[Directory_Event_NUM];
  bool m_possible[Directory_State_NUM][Directory_Event_NUM];
};
#endif // Directory_PROFILER_H
