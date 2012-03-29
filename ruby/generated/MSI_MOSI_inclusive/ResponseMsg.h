/** \file ResponseMsg.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef ResponseMsg_H
#define ResponseMsg_H

#include "Global.h"
#include "Allocator.h"
#include "Address.h"
#include "CoherenceResponseType.h"
#include "MachineID.h"
#include "NetDest.h"
#include "DataBlock.h"
#include "MessageSizeType.h"
#include "NetDest.h"
#include "MachineID.h"
#include "NetworkMessage.h"
class ResponseMsg :  public NetworkMessage {
public:
  ResponseMsg() 
  : NetworkMessage()
  {
    // m_Address has no default
    m_Type = CoherenceResponseType_NUM; // default value of CoherenceResponseType
    // m_SenderMachId has no default
    // m_Destination has no default
    // m_DataBlk has no default
    m_NumPendingExtAcks = 0; // default value of int
    m_MessageSize = MessageSizeType_Undefined; // default value of MessageSizeType
    m_prefDWG = false; // default value of bool
    // m_prevSharers has no default
    // m_RequestorMachId has no default
    m_reuse = 0; // default value of int
  }
  ~ResponseMsg() { };
  ResponseMsg(const Address& local_Address, const CoherenceResponseType& local_Type, const MachineID& local_SenderMachId, const NetDest& local_Destination, const DataBlock& local_DataBlk, const int& local_NumPendingExtAcks, const MessageSizeType& local_MessageSize, const bool& local_prefDWG, const NetDest& local_prevSharers, const MachineID& local_RequestorMachId, const int& local_reuse)
  : NetworkMessage()
  {
    m_Address = local_Address;
    m_Type = local_Type;
    m_SenderMachId = local_SenderMachId;
    m_Destination = local_Destination;
    m_DataBlk = local_DataBlk;
    m_NumPendingExtAcks = local_NumPendingExtAcks;
    m_MessageSize = local_MessageSize;
    m_prefDWG = local_prefDWG;
    m_prevSharers = local_prevSharers;
    m_RequestorMachId = local_RequestorMachId;
    m_reuse = local_reuse;
  }
  Message* clone() const { checkAllocator(); return s_allocator_ptr->allocate(*this); }
  void destroy() { checkAllocator(); s_allocator_ptr->deallocate(this); }
  static Allocator<ResponseMsg>* s_allocator_ptr;
  static void checkAllocator() { if (s_allocator_ptr == NULL) { s_allocator_ptr = new Allocator<ResponseMsg>; }}
  // Const accessors methods for each field
/** \brief Const accessor method for Address field.
  * \return Address field
  */
  const Address& getAddress() const { return m_Address; }
/** \brief Const accessor method for Type field.
  * \return Type field
  */
  const CoherenceResponseType& getType() const { return m_Type; }
/** \brief Const accessor method for SenderMachId field.
  * \return SenderMachId field
  */
  const MachineID& getSenderMachId() const { return m_SenderMachId; }
/** \brief Const accessor method for Destination field.
  * \return Destination field
  */
  const NetDest& getDestination() const { return m_Destination; }
/** \brief Const accessor method for DataBlk field.
  * \return DataBlk field
  */
  const DataBlock& getDataBlk() const { return m_DataBlk; }
/** \brief Const accessor method for NumPendingExtAcks field.
  * \return NumPendingExtAcks field
  */
  const int& getNumPendingExtAcks() const { return m_NumPendingExtAcks; }
/** \brief Const accessor method for MessageSize field.
  * \return MessageSize field
  */
  const MessageSizeType& getMessageSize() const { return m_MessageSize; }
/** \brief Const accessor method for prefDWG field.
  * \return prefDWG field
  */
  const bool& getprefDWG() const { return m_prefDWG; }
/** \brief Const accessor method for prevSharers field.
  * \return prevSharers field
  */
  const NetDest& getprevSharers() const { return m_prevSharers; }
/** \brief Const accessor method for RequestorMachId field.
  * \return RequestorMachId field
  */
  const MachineID& getRequestorMachId() const { return m_RequestorMachId; }
/** \brief Const accessor method for reuse field.
  * \return reuse field
  */
  const int& getreuse() const { return m_reuse; }

  // Non const Accessors methods for each field
/** \brief Non-const accessor method for Address field.
  * \return Address field
  */
  Address& getAddress() { return m_Address; }
/** \brief Non-const accessor method for Type field.
  * \return Type field
  */
  CoherenceResponseType& getType() { return m_Type; }
/** \brief Non-const accessor method for SenderMachId field.
  * \return SenderMachId field
  */
  MachineID& getSenderMachId() { return m_SenderMachId; }
/** \brief Non-const accessor method for Destination field.
  * \return Destination field
  */
  NetDest& getDestination() { return m_Destination; }
/** \brief Non-const accessor method for DataBlk field.
  * \return DataBlk field
  */
  DataBlock& getDataBlk() { return m_DataBlk; }
/** \brief Non-const accessor method for NumPendingExtAcks field.
  * \return NumPendingExtAcks field
  */
  int& getNumPendingExtAcks() { return m_NumPendingExtAcks; }
/** \brief Non-const accessor method for MessageSize field.
  * \return MessageSize field
  */
  MessageSizeType& getMessageSize() { return m_MessageSize; }
/** \brief Non-const accessor method for prefDWG field.
  * \return prefDWG field
  */
  bool& getprefDWG() { return m_prefDWG; }
/** \brief Non-const accessor method for prevSharers field.
  * \return prevSharers field
  */
  NetDest& getprevSharers() { return m_prevSharers; }
/** \brief Non-const accessor method for RequestorMachId field.
  * \return RequestorMachId field
  */
  MachineID& getRequestorMachId() { return m_RequestorMachId; }
/** \brief Non-const accessor method for reuse field.
  * \return reuse field
  */
  int& getreuse() { return m_reuse; }

  // Mutator methods for each field
/** \brief Mutator method for Address field */
  void setAddress(const Address& local_Address) { m_Address = local_Address; }
/** \brief Mutator method for Type field */
  void setType(const CoherenceResponseType& local_Type) { m_Type = local_Type; }
/** \brief Mutator method for SenderMachId field */
  void setSenderMachId(const MachineID& local_SenderMachId) { m_SenderMachId = local_SenderMachId; }
/** \brief Mutator method for Destination field */
  void setDestination(const NetDest& local_Destination) { m_Destination = local_Destination; }
/** \brief Mutator method for DataBlk field */
  void setDataBlk(const DataBlock& local_DataBlk) { m_DataBlk = local_DataBlk; }
/** \brief Mutator method for NumPendingExtAcks field */
  void setNumPendingExtAcks(const int& local_NumPendingExtAcks) { m_NumPendingExtAcks = local_NumPendingExtAcks; }
/** \brief Mutator method for MessageSize field */
  void setMessageSize(const MessageSizeType& local_MessageSize) { m_MessageSize = local_MessageSize; }
/** \brief Mutator method for prefDWG field */
  void setprefDWG(const bool& local_prefDWG) { m_prefDWG = local_prefDWG; }
/** \brief Mutator method for prevSharers field */
  void setprevSharers(const NetDest& local_prevSharers) { m_prevSharers = local_prevSharers; }
/** \brief Mutator method for RequestorMachId field */
  void setRequestorMachId(const MachineID& local_RequestorMachId) { m_RequestorMachId = local_RequestorMachId; }
/** \brief Mutator method for reuse field */
  void setreuse(const int& local_reuse) { m_reuse = local_reuse; }

  void print(ostream& out) const;
//private:
  Address m_Address; /**< Physical address for this request*/
  CoherenceResponseType m_Type; /**< Type of response (Ack, Data, etc)*/
  MachineID m_SenderMachId; /**< What component sent the data*/
  NetDest m_Destination; /**< Node to whom the data is sent*/
  DataBlock m_DataBlk; /**< data for the cache line*/
  int m_NumPendingExtAcks; /**< Number of acks to wait for*/
  MessageSizeType m_MessageSize; /**< size category of the message*/
  bool m_prefDWG; /**< marca si el bloque fue degradado*/
  NetDest m_prevSharers; /**< ids de los sharers del bloque*/
  MachineID m_RequestorMachId; /**< What component request*/
  int m_reuse; /**< info about reuse in L1+L15*/
};
// Output operator declaration
ostream& operator<<(ostream& out, const ResponseMsg& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const ResponseMsg& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // ResponseMsg_H
