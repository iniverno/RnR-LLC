/** \file CacheRequestType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef CacheRequestTypeQuick_H
#define CacheRequestTypeQuick_H

#include "Global.h"

/** \enum CacheRequestType
  * \brief ...
  */
enum CacheRequestTypeQuick {
  CacheRequestTypeQuick_FIRST,
  CacheRequestTypeQuick_LD = CacheRequestTypeQuick_FIRST,  /**< Load */
  CacheRequestTypeQuick_ST,  /**< Store */
  CacheRequestTypeQuick_ATOMIC,  /**< Atomic Load/Store */
  CacheRequestTypeQuick_IFETCH,  /**< Instruction fetch */
  CacheRequestTypeQuick_IO,  /**< I/O */
  CacheRequestTypeQuick_REPLACEMENT,  /**< Replacement */
  CacheRequestTypeQuick_COMMIT,  /**< Commit version */
  CacheRequestTypeQuick_LD_XACT,  /**< Transactional Load */
  CacheRequestTypeQuick_LDX_XACT,  /**< Transactional Load-Intend-To-Modify */
  CacheRequestTypeQuick_ST_XACT,  /**< Transactional Store */
  CacheRequestTypeQuick_BEGIN_XACT,  /**< Begin Transaction */
  CacheRequestTypeQuick_COMMIT_XACT,  /**< Commit Transaction */
  CacheRequestTypeQuick_ABORT_XACT,  /**< Abort Transaction */
  CacheRequestTypeQuick_PREFETCH,  /**< Invalid request type */
  CacheRequestTypeQuick_NULL,  /**< Invalid request type */  CacheRequestTypeQuick_NUM
};
CacheRequestTypeQuick string_to_CacheRequestTypeQuick(const string& str);
string CacheRequestTypeQuick_to_string(const CacheRequestTypeQuick& obj);
CacheRequestTypeQuick &operator++( CacheRequestTypeQuick &e);
ostream& operator<<(ostream& out, const CacheRequestTypeQuick& obj);

#endif // CacheRequestType_H
