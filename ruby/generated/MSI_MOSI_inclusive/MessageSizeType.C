/** \file MessageSizeType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "MessageSizeType.h"

ostream& operator<<(ostream& out, const MessageSizeType& obj)
{
  out << MessageSizeType_to_string(obj);
  out << flush;
  return out;
}

string MessageSizeType_to_string(const MessageSizeType& obj)
{
  switch(obj) {
  case MessageSizeType_Undefined:
    return "Undefined";
  case MessageSizeType_Control:
    return "Control";
  case MessageSizeType_Data:
    return "Data";
  case MessageSizeType_Request_Control:
    return "Request_Control";
  case MessageSizeType_Reissue_Control:
    return "Reissue_Control";
  case MessageSizeType_Response_Data:
    return "Response_Data";
  case MessageSizeType_ResponseL2hit_Data:
    return "ResponseL2hit_Data";
  case MessageSizeType_ResponseLocal_Data:
    return "ResponseLocal_Data";
  case MessageSizeType_Response_Control:
    return "Response_Control";
  case MessageSizeType_Writeback_Data:
    return "Writeback_Data";
  case MessageSizeType_Writeback_Control:
    return "Writeback_Control";
  case MessageSizeType_Forwarded_Control:
    return "Forwarded_Control";
  case MessageSizeType_Invalidate_Control:
    return "Invalidate_Control";
  case MessageSizeType_Unblock_Control:
    return "Unblock_Control";
  case MessageSizeType_Persistent_Control:
    return "Persistent_Control";
  case MessageSizeType_Completion_Control:
    return "Completion_Control";
  default:
    ERROR_MSG("Invalid range for type MessageSizeType");
    return "";
  }
}

MessageSizeType string_to_MessageSizeType(const string& str)
{
  if (false) {
  } else if (str == "Undefined") {
    return MessageSizeType_Undefined;
  } else if (str == "Control") {
    return MessageSizeType_Control;
  } else if (str == "Data") {
    return MessageSizeType_Data;
  } else if (str == "Request_Control") {
    return MessageSizeType_Request_Control;
  } else if (str == "Reissue_Control") {
    return MessageSizeType_Reissue_Control;
  } else if (str == "Response_Data") {
    return MessageSizeType_Response_Data;
  } else if (str == "ResponseL2hit_Data") {
    return MessageSizeType_ResponseL2hit_Data;
  } else if (str == "ResponseLocal_Data") {
    return MessageSizeType_ResponseLocal_Data;
  } else if (str == "Response_Control") {
    return MessageSizeType_Response_Control;
  } else if (str == "Writeback_Data") {
    return MessageSizeType_Writeback_Data;
  } else if (str == "Writeback_Control") {
    return MessageSizeType_Writeback_Control;
  } else if (str == "Forwarded_Control") {
    return MessageSizeType_Forwarded_Control;
  } else if (str == "Invalidate_Control") {
    return MessageSizeType_Invalidate_Control;
  } else if (str == "Unblock_Control") {
    return MessageSizeType_Unblock_Control;
  } else if (str == "Persistent_Control") {
    return MessageSizeType_Persistent_Control;
  } else if (str == "Completion_Control") {
    return MessageSizeType_Completion_Control;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type MessageSizeType");
  }
}

MessageSizeType& operator++( MessageSizeType& e) {
  assert(e < MessageSizeType_NUM);
  return e = MessageSizeType(e+1);
}
