// Auto generated C++ code started by symbols/StateMachine.C:700
// Directory: MOSI Directory Optimized

#include "Directory_Profiler.h"

Directory_Profiler::Directory_Profiler()
{
  for (int state = 0; state < Directory_State_NUM; state++) {
    for (int event = 0; event < Directory_Event_NUM; event++) {
      m_possible[state][event] = false;
      m_counters[state][event] = 0;
    }
  }
  for (int event = 0; event < Directory_Event_NUM; event++) {
    m_event_counters[event] = 0;
  }
}
void Directory_Profiler::clearStats()
{
  for (int state = 0; state < Directory_State_NUM; state++) {
    for (int event = 0; event < Directory_Event_NUM; event++) {
      m_counters[state][event] = 0;
    }
  }
  for (int event = 0; event < Directory_Event_NUM; event++) {
    m_event_counters[event] = 0;
  }
}
void Directory_Profiler::countTransition(Directory_State state, Directory_Event event)
{
  assert(m_possible[state][event]);
  m_counters[state][event]++;
  m_event_counters[event]++;
}
void Directory_Profiler::possibleTransition(Directory_State state, Directory_Event event)
{
  m_possible[state][event] = true;
}
void Directory_Profiler::dumpStats(ostream& out) const
{
  out << " --- Directory ---" << endl;
  out << " - Event Counts -" << endl;
  for (int event = 0; event < Directory_Event_NUM; event++) {
    int count = m_event_counters[event];
    out << (Directory_Event) event << "  " << count << endl;
  }
  out << endl;
  out << " - Transitions -" << endl;
  for (int state = 0; state < Directory_State_NUM; state++) {
    for (int event = 0; event < Directory_Event_NUM; event++) {
      if (m_possible[state][event]) {
        int count = m_counters[state][event];
        out << (Directory_State) state << "  " << (Directory_Event) event << "  " << count;
        if (count == 0) {
            out << " <-- ";
        }
        out << endl;
      }
    }
    out << endl;
  }
}
