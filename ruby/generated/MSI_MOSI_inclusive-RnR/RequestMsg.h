/** \file RequestMsg.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef RequestMsg_H
#define RequestMsg_H

#include "Global.h"
#include "Allocator.h"
#include "Address.h"
#include "CoherenceRequestType.h"
#include "AccessModeType.h"
#include "MachineID.h"
#include "NetDest.h"
#include "DataBlock.h"
#include "MessageSizeType.h"
#include "PrefetchBit.h"
#include "Address.h"
#include "CoherenceRequestType.h"
#include "MachineID.h"
#include "NetworkMessage.h"
class RequestMsg :  public NetworkMessage {
public:
  RequestMsg() 
  : NetworkMessage()
  {
    // m_Address has no default
    m_Type = CoherenceRequestType_NUM; // default value of CoherenceRequestType
    m_AccessMode = AccessModeType_UserMode; // default value of AccessModeType
    // m_RequestorMachId has no default
    // m_Destination has no default
    // m_DataBlk has no default
    m_NumPendingExtAcks = 0; // default value of int
    m_MessageSize = MessageSizeType_Undefined; // default value of MessageSizeType
    // m_L1CacheStateStr has no default
    // m_L2CacheStateStr has no default
    m_Prefetch = PrefetchBit_No; // default value of PrefetchBit
    // m_ProgramCounter has no default
    m_prefDWG = false; // default value of bool
    m_Type_UG_PREFETCH = CoherenceRequestType_NUM; // default value of CoherenceRequestType
    // m_coreID has no default
    m_epoch = 0; // default value of int
    m_reuse = 0; // default value of int
  }
  ~RequestMsg() { };
  RequestMsg(const Address& local_Address, const CoherenceRequestType& local_Type, const AccessModeType& local_AccessMode, const MachineID& local_RequestorMachId, const NetDest& local_Destination, const DataBlock& local_DataBlk, const int& local_NumPendingExtAcks, const MessageSizeType& local_MessageSize, const string& local_L1CacheStateStr, const string& local_L2CacheStateStr, const PrefetchBit& local_Prefetch, const Address& local_ProgramCounter, const bool& local_prefDWG, const CoherenceRequestType& local_Type_UG_PREFETCH, const MachineID& local_coreID, const int& local_epoch, const int& local_reuse)
  : NetworkMessage()
  {
    m_Address = local_Address;
    m_Type = local_Type;
    m_AccessMode = local_AccessMode;
    m_RequestorMachId = local_RequestorMachId;
    m_Destination = local_Destination;
    m_DataBlk = local_DataBlk;
    m_NumPendingExtAcks = local_NumPendingExtAcks;
    m_MessageSize = local_MessageSize;
    m_L1CacheStateStr = local_L1CacheStateStr;
    m_L2CacheStateStr = local_L2CacheStateStr;
    m_Prefetch = local_Prefetch;
    m_ProgramCounter = local_ProgramCounter;
    m_prefDWG = local_prefDWG;
    m_Type_UG_PREFETCH = local_Type_UG_PREFETCH;
    m_coreID = local_coreID;
    m_epoch = local_epoch;
    m_reuse = local_reuse;
  }
  Message* clone() const { checkAllocator(); return s_allocator_ptr->allocate(*this); }
  void destroy() { checkAllocator(); s_allocator_ptr->deallocate(this); }
  static Allocator<RequestMsg>* s_allocator_ptr;
  static void checkAllocator() { if (s_allocator_ptr == NULL) { s_allocator_ptr = new Allocator<RequestMsg>; }}
  // Const accessors methods for each field
/** \brief Const accessor method for Address field.
  * \return Address field
  */
  const Address& getAddress() const { return m_Address; }
/** \brief Const accessor method for Type field.
  * \return Type field
  */
  const CoherenceRequestType& getType() const { return m_Type; }
/** \brief Const accessor method for AccessMode field.
  * \return AccessMode field
  */
  const AccessModeType& getAccessMode() const { return m_AccessMode; }
/** \brief Const accessor method for RequestorMachId field.
  * \return RequestorMachId field
  */
  const MachineID& getRequestorMachId() const { return m_RequestorMachId; }
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
/** \brief Const accessor method for L1CacheStateStr field.
  * \return L1CacheStateStr field
  */
  const string& getL1CacheStateStr() const { return m_L1CacheStateStr; }
/** \brief Const accessor method for L2CacheStateStr field.
  * \return L2CacheStateStr field
  */
  const string& getL2CacheStateStr() const { return m_L2CacheStateStr; }
/** \brief Const accessor method for Prefetch field.
  * \return Prefetch field
  */
  const PrefetchBit& getPrefetch() const { return m_Prefetch; }
/** \brief Const accessor method for ProgramCounter field.
  * \return ProgramCounter field
  */
  const Address& getProgramCounter() const { return m_ProgramCounter; }
/** \brief Const accessor method for prefDWG field.
  * \return prefDWG field
  */
  const bool& getprefDWG() const { return m_prefDWG; }
/** \brief Const accessor method for Type_UG_PREFETCH field.
  * \return Type_UG_PREFETCH field
  */
  const CoherenceRequestType& getType_UG_PREFETCH() const { return m_Type_UG_PREFETCH; }
/** \brief Const accessor method for coreID field.
  * \return coreID field
  */
  const MachineID& getcoreID() const { return m_coreID; }
/** \brief Const accessor method for epoch field.
  * \return epoch field
  */
  const int& getepoch() const { return m_epoch; }
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
  CoherenceRequestType& getType() { return m_Type; }
/** \brief Non-const accessor method for AccessMode field.
  * \return AccessMode field
  */
  AccessModeType& getAccessMode() { return m_AccessMode; }
/** \brief Non-const accessor method for RequestorMachId field.
  * \return RequestorMachId field
  */
  MachineID& getRequestorMachId() { return m_RequestorMachId; }
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
/** \brief Non-const accessor method for L1CacheStateStr field.
  * \return L1CacheStateStr field
  */
  string& getL1CacheStateStr() { return m_L1CacheStateStr; }
/** \brief Non-const accessor method for L2CacheStateStr field.
  * \return L2CacheStateStr field
  */
  string& getL2CacheStateStr() { return m_L2CacheStateStr; }
/** \brief Non-const accessor method for Prefetch field.
  * \return Prefetch field
  */
  PrefetchBit& getPrefetch() { return m_Prefetch; }
/** \brief Non-const accessor method for ProgramCounter field.
  * \return ProgramCounter field
  */
  Address& getProgramCounter() { return m_ProgramCounter; }
/** \brief Non-const accessor method for prefDWG field.
  * \return prefDWG field
  */
  bool& getprefDWG() { return m_prefDWG; }
/** \brief Non-const accessor method for Type_UG_PREFETCH field.
  * \return Type_UG_PREFETCH field
  */
  CoherenceRequestType& getType_UG_PREFETCH() { return m_Type_UG_PREFETCH; }
/** \brief Non-const accessor method for coreID field.
  * \return coreID field
  */
  MachineID& getcoreID() { return m_coreID; }
/** \brief Non-const accessor method for epoch field.
  * \return epoch field
  */
  int& getepoch() { return m_epoch; }
/** \brief Non-const accessor method for reuse field.
  * \return reuse field
  */
  int& getreuse() { return m_reuse; }

  // Mutator methods for each field
/** \brief Mutator method for Address field */
  void setAddress(const Address& local_Address) { m_Address = local_Address; }
/** \brief Mutator method for Type field */
  void setType(const CoherenceRequestType& local_Type) { m_Type = local_Type; }
/** \brief Mutator method for AccessMode field */
  void setAccessMode(const AccessModeType& local_AccessMode) { m_AccessMode = local_AccessMode; }
/** \brief Mutator method for RequestorMachId field */
  void setRequestorMachId(const MachineID& local_RequestorMachId) { m_RequestorMachId = local_RequestorMachId; }
/** \brief Mutator method for Destination field */
  void setDestination(const NetDest& local_Destination) { m_Destination = local_Destination; }
/** \brief Mutator method for DataBlk field */
  void setDataBlk(const DataBlock& local_DataBlk) { m_DataBlk = local_DataBlk; }
/** \brief Mutator method for NumPendingExtAcks field */
  void setNumPendingExtAcks(const int& local_NumPendingExtAcks) { m_NumPendingExtAcks = local_NumPendingExtAcks; }
/** \brief Mutator method for MessageSize field */
  void setMessageSize(const MessageSizeType& local_MessageSize) { m_MessageSize = local_MessageSize; }
/** \brief Mutator method for L1CacheStateStr field */
  void setL1CacheStateStr(const string& local_L1CacheStateStr) { m_L1CacheStateStr = local_L1CacheStateStr; }
/** \brief Mutator method for L2CacheStateStr field */
  void setL2CacheStateStr(const string& local_L2CacheStateStr) { m_L2CacheStateStr = local_L2CacheStateStr; }
/** \brief Mutator method for Prefetch field */
  void setPrefetch(const PrefetchBit& local_Prefetch) { m_Prefetch = local_Prefetch; }
/** \brief Mutator method for ProgramCounter field */
  void setProgramCounter(const Address& local_ProgramCounter) { m_ProgramCounter = local_ProgramCounter; }
/** \brief Mutator method for prefDWG field */
  void setprefDWG(const bool& local_prefDWG) { m_prefDWG = local_prefDWG; }
/** \brief Mutator method for Type_UG_PREFETCH field */
  void setType_UG_PREFETCH(const CoherenceRequestType& local_Type_UG_PREFETCH) { m_Type_UG_PREFETCH = local_Type_UG_PREFETCH; }
/** \brief Mutator method for coreID field */
  void setcoreID(const MachineID& local_coreID) { m_coreID = local_coreID; }
/** \brief Mutator method for epoch field */
  void setepoch(const int& local_epoch) { m_epoch = local_epoch; }
/** \brief Mutator method for reuse field */
  void setreuse(const int& local_reuse) { m_reuse = local_reuse; }

  void print(ostream& out) const;
//private:
  Address m_Address; /**< Physical address for this request*/
  CoherenceRequestType m_Type; /**< Type of request (GetS, GetX, PutX, etc)*/
  AccessModeType m_AccessMode; /**< user/supervisor access type*/
  MachineID m_RequestorMachId; /**< What component request*/
  NetDest m_Destination; /**< What components receive the request, includes MachineType and num*/
  DataBlock m_DataBlk; /**< Data for the cache line (if PUTX)*/
  int m_NumPendingExtAcks; /**< Number of acks to wait for*/
  MessageSizeType m_MessageSize; /**< size category of the message*/
  string m_L1CacheStateStr; /**< describes L1 cache block state*/
  string m_L2CacheStateStr; /**< describes L2 cache block state*/
  PrefetchBit m_Prefetch; /**< Is this a prefetch request*/
  Address m_ProgramCounter; /**< el PC de la instrucci—n de memoria*/
  bool m_prefDWG; /**< marca si el bloque fue degradado*/
  CoherenceRequestType m_Type_UG_PREFETCH; /**< Type of request has caused de prefetch upgrade*/
  MachineID m_coreID; /**< What core request*/
  int m_epoch; /**< epoch the block has been requested*/
  int m_reuse; /**< info about reuse in L1+L15*/
};
// Output operator declaration
ostream& operator<<(ostream& out, const RequestMsg& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const RequestMsg& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // RequestMsg_H
