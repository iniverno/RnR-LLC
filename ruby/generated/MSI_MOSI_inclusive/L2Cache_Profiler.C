// Auto generated C++ code started by symbols/StateMachine.C:700
// L2Cache: MOSI Directory L2 Cache CMP

#include "L2Cache_Profiler.h"

L2Cache_Profiler::L2Cache_Profiler()
{
  for (int state = 0; state < L2Cache_State_NUM; state++) {
    for (int event = 0; event < L2Cache_Event_NUM; event++) {
      m_possible[state][event] = false;
      m_counters[state][event] = 0;
    }
  }
  for (int event = 0; event < L2Cache_Event_NUM; event++) {
    m_event_counters[event] = 0;
  }
}
void L2Cache_Profiler::clearStats()
{
  for (int state = 0; state < L2Cache_State_NUM; state++) {
    for (int event = 0; event < L2Cache_Event_NUM; event++) {
      m_counters[state][event] = 0;
    }
  }
  for (int event = 0; event < L2Cache_Event_NUM; event++) {
    m_event_counters[event] = 0;
  }
}
void L2Cache_Profiler::countTransition(L2Cache_State state, L2Cache_Event event)
{
  assert(m_possible[state][event]);
  m_counters[state][event]++;
  m_event_counters[event]++;
}
void L2Cache_Profiler::possibleTransition(L2Cache_State state, L2Cache_Event event)
{
  m_possible[state][event] = true;
}
void L2Cache_Profiler::dumpStats(ostream& out) const
{
  out << " --- L2Cache ---" << endl;
  out << " - Event Counts -" << endl;
  for (int event = 0; event < L2Cache_Event_NUM; event++) {
    int count = m_event_counters[event];
    out << (L2Cache_Event) event << "  " << count << endl;
  }
  out << endl;
  out << " - Transitions -" << endl;
  for (int state = 0; state < L2Cache_State_NUM; state++) {
    for (int event = 0; event < L2Cache_Event_NUM; event++) {
      if (m_possible[state][event]) {
        int count = m_counters[state][event];
        out << (L2Cache_State) state << "  " << (L2Cache_Event) event << "  " << count;
        if (count == 0) {
            out << " <-- ";
        }
        out << endl;
      }
    }
    out << endl;
  }
}
