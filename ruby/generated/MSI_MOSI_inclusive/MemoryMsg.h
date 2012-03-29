/** \file MemoryMsg.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef MemoryMsg_H
#define MemoryMsg_H

#include "Global.h"
#include "Allocator.h"
#include "Address.h"
#include "MemoryRequestType.h"
#include "MachineID.h"
#include "MachineID.h"
#include "DataBlock.h"
#include "MessageSizeType.h"
#include "PrefetchBit.h"
#include "Message.h"
class MemoryMsg :  public Message {
public:
  MemoryMsg() 
  : Message()
  {
    // m_Address has no default
    m_Type = MemoryRequestType_NUM; // default value of MemoryRequestType
    // m_Sender has no default
    // m_OriginalRequestorMachId has no default
    // m_DataBlk has no default
    m_MessageSize = MessageSizeType_Undefined; // default value of MessageSizeType
    m_Prefetch = PrefetchBit_No; // default value of PrefetchBit
    m_ReadX = false; // default value of bool
    m_Acks = 0; // default value of int
  }
  ~MemoryMsg() { };
  MemoryMsg(const Address& local_Address, const MemoryRequestType& local_Type, const MachineID& local_Sender, const MachineID& local_OriginalRequestorMachId, const DataBlock& local_DataBlk, const MessageSizeType& local_MessageSize, const PrefetchBit& local_Prefetch, const bool& local_ReadX, const int& local_Acks)
  : Message()
  {
    m_Address = local_Address;
    m_Type = local_Type;
    m_Sender = local_Sender;
    m_OriginalRequestorMachId = local_OriginalRequestorMachId;
    m_DataBlk = local_DataBlk;
    m_MessageSize = local_MessageSize;
    m_Prefetch = local_Prefetch;
    m_ReadX = local_ReadX;
    m_Acks = local_Acks;
  }
  Message* clone() const { checkAllocator(); return s_allocator_ptr->allocate(*this); }
  void destroy() { checkAllocator(); s_allocator_ptr->deallocate(this); }
  static Allocator<MemoryMsg>* s_allocator_ptr;
  static void checkAllocator() { if (s_allocator_ptr == NULL) { s_allocator_ptr = new Allocator<MemoryMsg>; }}
  // Const accessors methods for each field
/** \brief Const accessor method for Address field.
  * \return Address field
  */
  const Address& getAddress() const { return m_Address; }
/** \brief Const accessor method for Type field.
  * \return Type field
  */
  const MemoryRequestType& getType() const { return m_Type; }
/** \brief Const accessor method for Sender field.
  * \return Sender field
  */
  const MachineID& getSender() const { return m_Sender; }
/** \brief Const accessor method for OriginalRequestorMachId field.
  * \return OriginalRequestorMachId field
  */
  const MachineID& getOriginalRequestorMachId() const { return m_OriginalRequestorMachId; }
/** \brief Const accessor method for DataBlk field.
  * \return DataBlk field
  */
  const DataBlock& getDataBlk() const { return m_DataBlk; }
/** \brief Const accessor method for MessageSize field.
  * \return MessageSize field
  */
  const MessageSizeType& getMessageSize() const { return m_MessageSize; }
/** \brief Const accessor method for Prefetch field.
  * \return Prefetch field
  */
  const PrefetchBit& getPrefetch() const { return m_Prefetch; }
/** \brief Const accessor method for ReadX field.
  * \return ReadX field
  */
  const bool& getReadX() const { return m_ReadX; }
/** \brief Const accessor method for Acks field.
  * \return Acks field
  */
  const int& getAcks() const { return m_Acks; }

  // Non const Accessors methods for each field
/** \brief Non-const accessor method for Address field.
  * \return Address field
  */
  Address& getAddress() { return m_Address; }
/** \brief Non-const accessor method for Type field.
  * \return Type field
  */
  MemoryRequestType& getType() { return m_Type; }
/** \brief Non-const accessor method for Sender field.
  * \return Sender field
  */
  MachineID& getSender() { return m_Sender; }
/** \brief Non-const accessor method for OriginalRequestorMachId field.
  * \return OriginalRequestorMachId field
  */
  MachineID& getOriginalRequestorMachId() { return m_OriginalRequestorMachId; }
/** \brief Non-const accessor method for DataBlk field.
  * \return DataBlk field
  */
  DataBlock& getDataBlk() { return m_DataBlk; }
/** \brief Non-const accessor method for MessageSize field.
  * \return MessageSize field
  */
  MessageSizeType& getMessageSize() { return m_MessageSize; }
/** \brief Non-const accessor method for Prefetch field.
  * \return Prefetch field
  */
  PrefetchBit& getPrefetch() { return m_Prefetch; }
/** \brief Non-const accessor method for ReadX field.
  * \return ReadX field
  */
  bool& getReadX() { return m_ReadX; }
/** \brief Non-const accessor method for Acks field.
  * \return Acks field
  */
  int& getAcks() { return m_Acks; }

  // Mutator methods for each field
/** \brief Mutator method for Address field */
  void setAddress(const Address& local_Address) { m_Address = local_Address; }
/** \brief Mutator method for Type field */
  void setType(const MemoryRequestType& local_Type) { m_Type = local_Type; }
/** \brief Mutator method for Sender field */
  void setSender(const MachineID& local_Sender) { m_Sender = local_Sender; }
/** \brief Mutator method for OriginalRequestorMachId field */
  void setOriginalRequestorMachId(const MachineID& local_OriginalRequestorMachId) { m_OriginalRequestorMachId = local_OriginalRequestorMachId; }
/** \brief Mutator method for DataBlk field */
  void setDataBlk(const DataBlock& local_DataBlk) { m_DataBlk = local_DataBlk; }
/** \brief Mutator method for MessageSize field */
  void setMessageSize(const MessageSizeType& local_MessageSize) { m_MessageSize = local_MessageSize; }
/** \brief Mutator method for Prefetch field */
  void setPrefetch(const PrefetchBit& local_Prefetch) { m_Prefetch = local_Prefetch; }
/** \brief Mutator method for ReadX field */
  void setReadX(const bool& local_ReadX) { m_ReadX = local_ReadX; }
/** \brief Mutator method for Acks field */
  void setAcks(const int& local_Acks) { m_Acks = local_Acks; }

  void print(ostream& out) const;
//private:
  Address m_Address; /**< Physical address for this request*/
  MemoryRequestType m_Type; /**< Type of memory request (MEMORY_READ or MEMORY_WB)*/
  MachineID m_Sender; /**< What component sent the data*/
  MachineID m_OriginalRequestorMachId; /**< What component originally requested*/
  DataBlock m_DataBlk; /**< Data to writeback*/
  MessageSizeType m_MessageSize; /**< size category of the message*/
  PrefetchBit m_Prefetch; /**< Is this a prefetch request*/
  bool m_ReadX; /**< Exclusive*/
  int m_Acks; /**< How many acks to expect*/
};
// Output operator declaration
ostream& operator<<(ostream& out, const MemoryMsg& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const MemoryMsg& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // MemoryMsg_H
