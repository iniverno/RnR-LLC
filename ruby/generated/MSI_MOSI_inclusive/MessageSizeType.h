/** \file MessageSizeType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef MessageSizeType_H
#define MessageSizeType_H

#include "Global.h"

/** \enum MessageSizeType
  * \brief ...
  */
enum MessageSizeType {
  MessageSizeType_FIRST,
  MessageSizeType_Undefined = MessageSizeType_FIRST,  /**< Undefined */
  MessageSizeType_Control,  /**< Control Message */
  MessageSizeType_Data,  /**< Data Message */
  MessageSizeType_Request_Control,  /**< Request */
  MessageSizeType_Reissue_Control,  /**< Reissued request */
  MessageSizeType_Response_Data,  /**< data response */
  MessageSizeType_ResponseL2hit_Data,  /**< data response */
  MessageSizeType_ResponseLocal_Data,  /**< data response */
  MessageSizeType_Response_Control,  /**< non-data response */
  MessageSizeType_Writeback_Data,  /**< Writeback data */
  MessageSizeType_Writeback_Control,  /**< Writeback control */
  MessageSizeType_Forwarded_Control,  /**< Forwarded control */
  MessageSizeType_Invalidate_Control,  /**< Invalidate control */
  MessageSizeType_Unblock_Control,  /**< Unblock control */
  MessageSizeType_Persistent_Control,  /**< Persistent request activation messages */
  MessageSizeType_Completion_Control,  /**< Completion messages */
  MessageSizeType_NUM
};
MessageSizeType string_to_MessageSizeType(const string& str);
string MessageSizeType_to_string(const MessageSizeType& obj);
MessageSizeType &operator++( MessageSizeType &e);
ostream& operator<<(ostream& out, const MessageSizeType& obj);

#endif // MessageSizeType_H
