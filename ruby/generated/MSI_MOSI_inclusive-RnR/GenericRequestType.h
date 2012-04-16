/** \file GenericRequestType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef GenericRequestType_H
#define GenericRequestType_H

#include "Global.h"

/** \enum GenericRequestType
  * \brief ...
  */
enum GenericRequestType {
  GenericRequestType_FIRST,
  GenericRequestType_GETS = GenericRequestType_FIRST,  /**< gets request */
  GenericRequestType_GET_INSTR,  /**< get instr request */
  GenericRequestType_GETX,  /**< getx request */
  GenericRequestType_UPGRADE,  /**< upgrade request */
  GenericRequestType_DOWNGRADE,  /**< downgrade request */
  GenericRequestType_INV,  /**< invalidate request */
  GenericRequestType_INV_S,  /**< invalidate shared copy request */
  GenericRequestType_PUTS,  /**< puts request */
  GenericRequestType_PUTO,  /**< puto request */
  GenericRequestType_PUTX,  /**< putx request */
  GenericRequestType_L2_PF,  /**< L2 prefetch */
  GenericRequestType_LD,  /**< Load */
  GenericRequestType_ST,  /**< Store */
  GenericRequestType_ATOMIC,  /**< Atomic Load/Store */
  GenericRequestType_IFETCH,  /**< Instruction fetch */
  GenericRequestType_IO,  /**< I/O */
  GenericRequestType_NACK,  /**< Nack */
  GenericRequestType_REPLACEMENT,  /**< Replacement */
  GenericRequestType_WB_ACK,  /**< WriteBack ack */
  GenericRequestType_EXE_ACK,  /**< Execlusive ack */
  GenericRequestType_COMMIT,  /**< Commit version */
  GenericRequestType_LD_XACT,  /**< Transactional Load */
  GenericRequestType_LDX_XACT,  /**< Transactional Load-Intend-Modify */
  GenericRequestType_ST_XACT,  /**< Transactional Store */
  GenericRequestType_BEGIN_XACT,  /**< Begin Transaction */
  GenericRequestType_COMMIT_XACT,  /**< Commit Transaction */
  GenericRequestType_ABORT_XACT,  /**< Abort Transaction */
  GenericRequestType_NULL,  /**< null request type */
  GenericRequestType_NUM
};
GenericRequestType string_to_GenericRequestType(const string& str);
string GenericRequestType_to_string(const GenericRequestType& obj);
GenericRequestType &operator++( GenericRequestType &e);
ostream& operator<<(ostream& out, const GenericRequestType& obj);

#endif // GenericRequestType_H
