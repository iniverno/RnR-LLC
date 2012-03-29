/** \file Directory_Event.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef Directory_Event_H
#define Directory_Event_H

#include "Global.h"

/** \enum Directory_Event
  * \brief Directory events
  */
enum Directory_Event {
  Directory_Event_FIRST,
  Directory_Event_GETS = Directory_Event_FIRST,  /**< A GETS arrives */
  Directory_Event_GET_INSTR,  /**<  */
  Directory_Event_GETX_Owner,  /**< A GETX arrives, requestor is owner */
  Directory_Event_GETX_NotOwner,  /**< A GETX arrives, requestor is not owner */
  Directory_Event_PUTX_Owner,  /**< A PUTX arrives, requestor is owner */
  Directory_Event_PUTX_NotOwner,  /**< A PUTX arrives, requestor is not owner */
  Directory_Event_FinalAck,  /**<  */
  Directory_Event_PREFS,  /**<  */
  Directory_Event_PREFX,  /**<  */
  Directory_Event_DATA,  /**<  */
  Directory_Event_DATA_P,  /**<  */
  Directory_Event_UG_PREFETCH,  /**<  */
  Directory_Event_NUM
};
Directory_Event string_to_Directory_Event(const string& str);
string Directory_Event_to_string(const Directory_Event& obj);
Directory_Event &operator++( Directory_Event &e);
ostream& operator<<(ostream& out, const Directory_Event& obj);

#endif // Directory_Event_H
