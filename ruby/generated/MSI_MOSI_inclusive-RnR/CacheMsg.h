/** \file CacheMsg.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef CacheMsg_H
#define CacheMsg_H

#include "Global.h"
#include "Allocator.h"
#include "Address.h"
#include "Address.h"
#include "CacheRequestType.h"
#include "Address.h"
#include "AccessModeType.h"
#include "PrefetchBit.h"
#include "Address.h"
#include "Message.h"
class CacheMsg :  public Message {
public:
  CacheMsg() 
  : Message()
  {
    // m_Address has no default
    // m_PhysicalAddress has no default
    m_Type = CacheRequestType_NULL; // default value of CacheRequestType
    // m_ProgramCounter has no default
    m_AccessMode = AccessModeType_UserMode; // default value of AccessModeType
    m_Size = 0; // default value of int
    m_Prefetch = PrefetchBit_No; // default value of PrefetchBit
    m_Version = 0; // default value of int
    // m_LogicalAddress has no default
    m_ThreadID = 0; // default value of int
    // m_Timestamp has no default
    m_ExposedAction = false; // default value of bool
  }
  ~CacheMsg() { };
  CacheMsg(const Address& local_Address, const Address& local_PhysicalAddress, const CacheRequestType& local_Type, const Address& local_ProgramCounter, const AccessModeType& local_AccessMode, const int& local_Size, const PrefetchBit& local_Prefetch, const int& local_Version, const Address& local_LogicalAddress, const int& local_ThreadID, const uint64& local_Timestamp, const bool& local_ExposedAction)
  : Message()
  {
    m_Address = local_Address;
    m_PhysicalAddress = local_PhysicalAddress;
    m_Type = local_Type;
    m_ProgramCounter = local_ProgramCounter;
    m_AccessMode = local_AccessMode;
    m_Size = local_Size;
    m_Prefetch = local_Prefetch;
    m_Version = local_Version;
    m_LogicalAddress = local_LogicalAddress;
    m_ThreadID = local_ThreadID;
    m_Timestamp = local_Timestamp;
    m_ExposedAction = local_ExposedAction;
  }
  Message* clone() const { checkAllocator(); return s_allocator_ptr->allocate(*this); }
  void destroy() { checkAllocator(); s_allocator_ptr->deallocate(this); }
  static Allocator<CacheMsg>* s_allocator_ptr;
  static void checkAllocator() { if (s_allocator_ptr == NULL) { s_allocator_ptr = new Allocator<CacheMsg>; }}
  // Const accessors methods for each field
/** \brief Const accessor method for Address field.
  * \return Address field
  */
  const Address& getAddress() const { return m_Address; }
/** \brief Const accessor method for PhysicalAddress field.
  * \return PhysicalAddress field
  */
  const Address& getPhysicalAddress() const { return m_PhysicalAddress; }
/** \brief Const accessor method for Type field.
  * \return Type field
  */
  const CacheRequestType& getType() const { return m_Type; }
/** \brief Const accessor method for ProgramCounter field.
  * \return ProgramCounter field
  */
  const Address& getProgramCounter() const { return m_ProgramCounter; }
/** \brief Const accessor method for AccessMode field.
  * \return AccessMode field
  */
  const AccessModeType& getAccessMode() const { return m_AccessMode; }
/** \brief Const accessor method for Size field.
  * \return Size field
  */
  const int& getSize() const { return m_Size; }
/** \brief Const accessor method for Prefetch field.
  * \return Prefetch field
  */
  const PrefetchBit& getPrefetch() const { return m_Prefetch; }
/** \brief Const accessor method for Version field.
  * \return Version field
  */
  const int& getVersion() const { return m_Version; }
/** \brief Const accessor method for LogicalAddress field.
  * \return LogicalAddress field
  */
  const Address& getLogicalAddress() const { return m_LogicalAddress; }
/** \brief Const accessor method for ThreadID field.
  * \return ThreadID field
  */
  const int& getThreadID() const { return m_ThreadID; }
/** \brief Const accessor method for Timestamp field.
  * \return Timestamp field
  */
  const uint64& getTimestamp() const { return m_Timestamp; }
/** \brief Const accessor method for ExposedAction field.
  * \return ExposedAction field
  */
  const bool& getExposedAction() const { return m_ExposedAction; }

  // Non const Accessors methods for each field
/** \brief Non-const accessor method for Address field.
  * \return Address field
  */
  Address& getAddress() { return m_Address; }
/** \brief Non-const accessor method for PhysicalAddress field.
  * \return PhysicalAddress field
  */
  Address& getPhysicalAddress() { return m_PhysicalAddress; }
/** \brief Non-const accessor method for Type field.
  * \return Type field
  */
  CacheRequestType& getType() { return m_Type; }
/** \brief Non-const accessor method for ProgramCounter field.
  * \return ProgramCounter field
  */
  Address& getProgramCounter() { return m_ProgramCounter; }
/** \brief Non-const accessor method for AccessMode field.
  * \return AccessMode field
  */
  AccessModeType& getAccessMode() { return m_AccessMode; }
/** \brief Non-const accessor method for Size field.
  * \return Size field
  */
  int& getSize() { return m_Size; }
/** \brief Non-const accessor method for Prefetch field.
  * \return Prefetch field
  */
  PrefetchBit& getPrefetch() { return m_Prefetch; }
/** \brief Non-const accessor method for Version field.
  * \return Version field
  */
  int& getVersion() { return m_Version; }
/** \brief Non-const accessor method for LogicalAddress field.
  * \return LogicalAddress field
  */
  Address& getLogicalAddress() { return m_LogicalAddress; }
/** \brief Non-const accessor method for ThreadID field.
  * \return ThreadID field
  */
  int& getThreadID() { return m_ThreadID; }
/** \brief Non-const accessor method for Timestamp field.
  * \return Timestamp field
  */
  uint64& getTimestamp() { return m_Timestamp; }
/** \brief Non-const accessor method for ExposedAction field.
  * \return ExposedAction field
  */
  bool& getExposedAction() { return m_ExposedAction; }

  // Mutator methods for each field
/** \brief Mutator method for Address field */
  void setAddress(const Address& local_Address) { m_Address = local_Address; }
/** \brief Mutator method for PhysicalAddress field */
  void setPhysicalAddress(const Address& local_PhysicalAddress) { m_PhysicalAddress = local_PhysicalAddress; }
/** \brief Mutator method for Type field */
  void setType(const CacheRequestType& local_Type) { m_Type = local_Type; }
/** \brief Mutator method for ProgramCounter field */
  void setProgramCounter(const Address& local_ProgramCounter) { m_ProgramCounter = local_ProgramCounter; }
/** \brief Mutator method for AccessMode field */
  void setAccessMode(const AccessModeType& local_AccessMode) { m_AccessMode = local_AccessMode; }
/** \brief Mutator method for Size field */
  void setSize(const int& local_Size) { m_Size = local_Size; }
/** \brief Mutator method for Prefetch field */
  void setPrefetch(const PrefetchBit& local_Prefetch) { m_Prefetch = local_Prefetch; }
/** \brief Mutator method for Version field */
  void setVersion(const int& local_Version) { m_Version = local_Version; }
/** \brief Mutator method for LogicalAddress field */
  void setLogicalAddress(const Address& local_LogicalAddress) { m_LogicalAddress = local_LogicalAddress; }
/** \brief Mutator method for ThreadID field */
  void setThreadID(const int& local_ThreadID) { m_ThreadID = local_ThreadID; }
/** \brief Mutator method for Timestamp field */
  void setTimestamp(const uint64& local_Timestamp) { m_Timestamp = local_Timestamp; }
/** \brief Mutator method for ExposedAction field */
  void setExposedAction(const bool& local_ExposedAction) { m_ExposedAction = local_ExposedAction; }

  void print(ostream& out) const;
//private:
  Address m_Address; /**< Line address for this request*/
  Address m_PhysicalAddress; /**< Physical address for this request*/
  CacheRequestType m_Type; /**< Type of request (LD, ST, etc)*/
  Address m_ProgramCounter; /**< Program counter of the instruction that caused the miss*/
  AccessModeType m_AccessMode; /**< user/supervisor access type*/
  int m_Size; /**< size in bytes of access*/
  PrefetchBit m_Prefetch; /**< Is this a prefetch request*/
  int m_Version; /**< Version associated with this request*/
  Address m_LogicalAddress; /**< Virtual address for this request*/
  int m_ThreadID; /**< The SMT thread that initiated this request*/
  uint64 m_Timestamp; /**< The transaction timestamp of this request. Last commit time if request is non-transactional*/
  bool m_ExposedAction; /**< Is this request part of an exposed action*/
};
// Output operator declaration
ostream& operator<<(ostream& out, const CacheMsg& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const CacheMsg& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // CacheMsg_H
