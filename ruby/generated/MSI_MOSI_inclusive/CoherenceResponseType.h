/** \file CoherenceResponseType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef CoherenceResponseType_H
#define CoherenceResponseType_H

#include "Global.h"

/** \enum CoherenceResponseType
  * \brief ...
  */
enum CoherenceResponseType {
  CoherenceResponseType_FIRST,
  CoherenceResponseType_ACK = CoherenceResponseType_FIRST,  /**< ACKnowledgment */
  CoherenceResponseType_INV_ACK,  /**< INValidation ACKnowledgment */
  CoherenceResponseType_DG_ACK,  /**< DownGrade ACKnowledgment */
  CoherenceResponseType_NACK,  /**< Negative ACKnowledgment */
  CoherenceResponseType_DATA,  /**< Data */
  CoherenceResponseType_DATA_S,  /**< Data to L1 cache, then imediately go to shared state */
  CoherenceResponseType_DATA_I,  /**< Data to L1 cache, then imediately go to inv state */
  CoherenceResponseType_FINALACK,  /**<  */
  CoherenceResponseType_NUM
};
CoherenceResponseType string_to_CoherenceResponseType(const string& str);
string CoherenceResponseType_to_string(const CoherenceResponseType& obj);
CoherenceResponseType &operator++( CoherenceResponseType &e);
ostream& operator<<(ostream& out, const CoherenceResponseType& obj);

#endif // CoherenceResponseType_H
