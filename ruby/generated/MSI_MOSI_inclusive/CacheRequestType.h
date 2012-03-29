/** \file CacheRequestType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef CacheRequestType_H
#define CacheRequestType_H

#include "Global.h"

/** \enum CacheRequestType
  * \brief ...
  */
enum CacheRequestType {
  CacheRequestType_FIRST,
  CacheRequestType_LD = CacheRequestType_FIRST,  /**< Load */
  CacheRequestType_ST,  /**< Store */
  CacheRequestType_ATOMIC,  /**< Atomic Load/Store */
  CacheRequestType_IFETCH,  /**< Instruction fetch */
  CacheRequestType_IO,  /**< I/O */
  CacheRequestType_REPLACEMENT,  /**< Replacement */
  CacheRequestType_COMMIT,  /**< Commit version */
  CacheRequestType_LD_XACT,  /**< Transactional Load */
  CacheRequestType_LDX_XACT,  /**< Transactional Load-Intend-To-Modify */
  CacheRequestType_ST_XACT,  /**< Transactional Store */
  CacheRequestType_BEGIN_XACT,  /**< Begin Transaction */
  CacheRequestType_COMMIT_XACT,  /**< Commit Transaction */
  CacheRequestType_ABORT_XACT,  /**< Abort Transaction */
  CacheRequestType_NULL,  /**< Invalid request type */
  CacheRequestType_NUM
};
CacheRequestType string_to_CacheRequestType(const string& str);
string CacheRequestType_to_string(const CacheRequestType& obj);
CacheRequestType &operator++( CacheRequestType &e);
ostream& operator<<(ostream& out, const CacheRequestType& obj);

#endif // CacheRequestType_H
