/** \file L2Cache_TBE.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef L2Cache_TBE_H
#define L2Cache_TBE_H

#include "Global.h"
#include "Allocator.h"
#include "Address.h"
#include "L2Cache_State.h"
#include "DataBlock.h"
#include "NetDest.h"
#include "NetDest.h"
#include "MachineID.h"
#include "MachineID.h"
#include "MachineID.h"
#include "PrefetchBit.h"
#include "MachineID.h"
class L2Cache_TBE {
public:
  L2Cache_TBE() 
  {
    // m_Address has no default
    m_TBEState = L2Cache_State_L2_NP; // default value of L2Cache_State
    // m_DataBlk has no default
    m_NumPendingExtAcks = 0; // default value of int
    m_NumPendingIntAcks = 0; // default value of int
    // m_Forward_GetS_IDs has no default
    // m_L1_GetS_IDs has no default
    // m_Forward_GetX_ID has no default
    // m_L1_GetX_ID has no default
    // m_InvalidatorID has no default
    m_ForwardGetX_AckCount = 0; // default value of int
    m_isPrefetch = false; // default value of bool
    m_isThreeHop = false; // default value of bool
    m_validForwardedGetXId = false; // default value of bool
    m_validInvalidator = false; // default value of bool
    m_isInternalRequestOnly = false; // default value of bool
    m_prefetch = PrefetchBit_No; // default value of PrefetchBit
    m_usado = false; // default value of bool
    // m_owner has no default
    m_epoch = 0; // default value of int
  }
  ~L2Cache_TBE() { };
  L2Cache_TBE(const Address& local_Address, const L2Cache_State& local_TBEState, const DataBlock& local_DataBlk, const int& local_NumPendingExtAcks, const int& local_NumPendingIntAcks, const NetDest& local_Forward_GetS_IDs, const NetDest& local_L1_GetS_IDs, const MachineID& local_Forward_GetX_ID, const MachineID& local_L1_GetX_ID, const MachineID& local_InvalidatorID, const int& local_ForwardGetX_AckCount, const bool& local_isPrefetch, const bool& local_isThreeHop, const bool& local_validForwardedGetXId, const bool& local_validInvalidator, const bool& local_isInternalRequestOnly, const PrefetchBit& local_prefetch, const bool& local_usado, const MachineID& local_owner, const int& local_epoch)
  {
    m_Address = local_Address;
    m_TBEState = local_TBEState;
    m_DataBlk = local_DataBlk;
    m_NumPendingExtAcks = local_NumPendingExtAcks;
    m_NumPendingIntAcks = local_NumPendingIntAcks;
    m_Forward_GetS_IDs = local_Forward_GetS_IDs;
    m_L1_GetS_IDs = local_L1_GetS_IDs;
    m_Forward_GetX_ID = local_Forward_GetX_ID;
    m_L1_GetX_ID = local_L1_GetX_ID;
    m_InvalidatorID = local_InvalidatorID;
    m_ForwardGetX_AckCount = local_ForwardGetX_AckCount;
    m_isPrefetch = local_isPrefetch;
    m_isThreeHop = local_isThreeHop;
    m_validForwardedGetXId = local_validForwardedGetXId;
    m_validInvalidator = local_validInvalidator;
    m_isInternalRequestOnly = local_isInternalRequestOnly;
    m_prefetch = local_prefetch;
    m_usado = local_usado;
    m_owner = local_owner;
    m_epoch = local_epoch;
  }
  // Const accessors methods for each field
/** \brief Const accessor method for Address field.
  * \return Address field
  */
  const Address& getAddress() const { return m_Address; }
/** \brief Const accessor method for TBEState field.
  * \return TBEState field
  */
  const L2Cache_State& getTBEState() const { return m_TBEState; }
/** \brief Const accessor method for DataBlk field.
  * \return DataBlk field
  */
  const DataBlock& getDataBlk() const { return m_DataBlk; }
/** \brief Const accessor method for NumPendingExtAcks field.
  * \return NumPendingExtAcks field
  */
  const int& getNumPendingExtAcks() const { return m_NumPendingExtAcks; }
/** \brief Const accessor method for NumPendingIntAcks field.
  * \return NumPendingIntAcks field
  */
  const int& getNumPendingIntAcks() const { return m_NumPendingIntAcks; }
/** \brief Const accessor method for Forward_GetS_IDs field.
  * \return Forward_GetS_IDs field
  */
  const NetDest& getForward_GetS_IDs() const { return m_Forward_GetS_IDs; }
/** \brief Const accessor method for L1_GetS_IDs field.
  * \return L1_GetS_IDs field
  */
  const NetDest& getL1_GetS_IDs() const { return m_L1_GetS_IDs; }
/** \brief Const accessor method for Forward_GetX_ID field.
  * \return Forward_GetX_ID field
  */
  const MachineID& getForward_GetX_ID() const { return m_Forward_GetX_ID; }
/** \brief Const accessor method for L1_GetX_ID field.
  * \return L1_GetX_ID field
  */
  const MachineID& getL1_GetX_ID() const { return m_L1_GetX_ID; }
/** \brief Const accessor method for InvalidatorID field.
  * \return InvalidatorID field
  */
  const MachineID& getInvalidatorID() const { return m_InvalidatorID; }
/** \brief Const accessor method for ForwardGetX_AckCount field.
  * \return ForwardGetX_AckCount field
  */
  const int& getForwardGetX_AckCount() const { return m_ForwardGetX_AckCount; }
/** \brief Const accessor method for isPrefetch field.
  * \return isPrefetch field
  */
  const bool& getisPrefetch() const { return m_isPrefetch; }
/** \brief Const accessor method for isThreeHop field.
  * \return isThreeHop field
  */
  const bool& getisThreeHop() const { return m_isThreeHop; }
/** \brief Const accessor method for validForwardedGetXId field.
  * \return validForwardedGetXId field
  */
  const bool& getvalidForwardedGetXId() const { return m_validForwardedGetXId; }
/** \brief Const accessor method for validInvalidator field.
  * \return validInvalidator field
  */
  const bool& getvalidInvalidator() const { return m_validInvalidator; }
/** \brief Const accessor method for isInternalRequestOnly field.
  * \return isInternalRequestOnly field
  */
  const bool& getisInternalRequestOnly() const { return m_isInternalRequestOnly; }
/** \brief Const accessor method for prefetch field.
  * \return prefetch field
  */
  const PrefetchBit& getprefetch() const { return m_prefetch; }
/** \brief Const accessor method for usado field.
  * \return usado field
  */
  const bool& getusado() const { return m_usado; }
/** \brief Const accessor method for owner field.
  * \return owner field
  */
  const MachineID& getowner() const { return m_owner; }
/** \brief Const accessor method for epoch field.
  * \return epoch field
  */
  const int& getepoch() const { return m_epoch; }

  // Non const Accessors methods for each field
/** \brief Non-const accessor method for Address field.
  * \return Address field
  */
  Address& getAddress() { return m_Address; }
/** \brief Non-const accessor method for TBEState field.
  * \return TBEState field
  */
  L2Cache_State& getTBEState() { return m_TBEState; }
/** \brief Non-const accessor method for DataBlk field.
  * \return DataBlk field
  */
  DataBlock& getDataBlk() { return m_DataBlk; }
/** \brief Non-const accessor method for NumPendingExtAcks field.
  * \return NumPendingExtAcks field
  */
  int& getNumPendingExtAcks() { return m_NumPendingExtAcks; }
/** \brief Non-const accessor method for NumPendingIntAcks field.
  * \return NumPendingIntAcks field
  */
  int& getNumPendingIntAcks() { return m_NumPendingIntAcks; }
/** \brief Non-const accessor method for Forward_GetS_IDs field.
  * \return Forward_GetS_IDs field
  */
  NetDest& getForward_GetS_IDs() { return m_Forward_GetS_IDs; }
/** \brief Non-const accessor method for L1_GetS_IDs field.
  * \return L1_GetS_IDs field
  */
  NetDest& getL1_GetS_IDs() { return m_L1_GetS_IDs; }
/** \brief Non-const accessor method for Forward_GetX_ID field.
  * \return Forward_GetX_ID field
  */
  MachineID& getForward_GetX_ID() { return m_Forward_GetX_ID; }
/** \brief Non-const accessor method for L1_GetX_ID field.
  * \return L1_GetX_ID field
  */
  MachineID& getL1_GetX_ID() { return m_L1_GetX_ID; }
/** \brief Non-const accessor method for InvalidatorID field.
  * \return InvalidatorID field
  */
  MachineID& getInvalidatorID() { return m_InvalidatorID; }
/** \brief Non-const accessor method for ForwardGetX_AckCount field.
  * \return ForwardGetX_AckCount field
  */
  int& getForwardGetX_AckCount() { return m_ForwardGetX_AckCount; }
/** \brief Non-const accessor method for isPrefetch field.
  * \return isPrefetch field
  */
  bool& getisPrefetch() { return m_isPrefetch; }
/** \brief Non-const accessor method for isThreeHop field.
  * \return isThreeHop field
  */
  bool& getisThreeHop() { return m_isThreeHop; }
/** \brief Non-const accessor method for validForwardedGetXId field.
  * \return validForwardedGetXId field
  */
  bool& getvalidForwardedGetXId() { return m_validForwardedGetXId; }
/** \brief Non-const accessor method for validInvalidator field.
  * \return validInvalidator field
  */
  bool& getvalidInvalidator() { return m_validInvalidator; }
/** \brief Non-const accessor method for isInternalRequestOnly field.
  * \return isInternalRequestOnly field
  */
  bool& getisInternalRequestOnly() { return m_isInternalRequestOnly; }
/** \brief Non-const accessor method for prefetch field.
  * \return prefetch field
  */
  PrefetchBit& getprefetch() { return m_prefetch; }
/** \brief Non-const accessor method for usado field.
  * \return usado field
  */
  bool& getusado() { return m_usado; }
/** \brief Non-const accessor method for owner field.
  * \return owner field
  */
  MachineID& getowner() { return m_owner; }
/** \brief Non-const accessor method for epoch field.
  * \return epoch field
  */
  int& getepoch() { return m_epoch; }

  // Mutator methods for each field
/** \brief Mutator method for Address field */
  void setAddress(const Address& local_Address) { m_Address = local_Address; }
/** \brief Mutator method for TBEState field */
  void setTBEState(const L2Cache_State& local_TBEState) { m_TBEState = local_TBEState; }
/** \brief Mutator method for DataBlk field */
  void setDataBlk(const DataBlock& local_DataBlk) { m_DataBlk = local_DataBlk; }
/** \brief Mutator method for NumPendingExtAcks field */
  void setNumPendingExtAcks(const int& local_NumPendingExtAcks) { m_NumPendingExtAcks = local_NumPendingExtAcks; }
/** \brief Mutator method for NumPendingIntAcks field */
  void setNumPendingIntAcks(const int& local_NumPendingIntAcks) { m_NumPendingIntAcks = local_NumPendingIntAcks; }
/** \brief Mutator method for Forward_GetS_IDs field */
  void setForward_GetS_IDs(const NetDest& local_Forward_GetS_IDs) { m_Forward_GetS_IDs = local_Forward_GetS_IDs; }
/** \brief Mutator method for L1_GetS_IDs field */
  void setL1_GetS_IDs(const NetDest& local_L1_GetS_IDs) { m_L1_GetS_IDs = local_L1_GetS_IDs; }
/** \brief Mutator method for Forward_GetX_ID field */
  void setForward_GetX_ID(const MachineID& local_Forward_GetX_ID) { m_Forward_GetX_ID = local_Forward_GetX_ID; }
/** \brief Mutator method for L1_GetX_ID field */
  void setL1_GetX_ID(const MachineID& local_L1_GetX_ID) { m_L1_GetX_ID = local_L1_GetX_ID; }
/** \brief Mutator method for InvalidatorID field */
  void setInvalidatorID(const MachineID& local_InvalidatorID) { m_InvalidatorID = local_InvalidatorID; }
/** \brief Mutator method for ForwardGetX_AckCount field */
  void setForwardGetX_AckCount(const int& local_ForwardGetX_AckCount) { m_ForwardGetX_AckCount = local_ForwardGetX_AckCount; }
/** \brief Mutator method for isPrefetch field */
  void setisPrefetch(const bool& local_isPrefetch) { m_isPrefetch = local_isPrefetch; }
/** \brief Mutator method for isThreeHop field */
  void setisThreeHop(const bool& local_isThreeHop) { m_isThreeHop = local_isThreeHop; }
/** \brief Mutator method for validForwardedGetXId field */
  void setvalidForwardedGetXId(const bool& local_validForwardedGetXId) { m_validForwardedGetXId = local_validForwardedGetXId; }
/** \brief Mutator method for validInvalidator field */
  void setvalidInvalidator(const bool& local_validInvalidator) { m_validInvalidator = local_validInvalidator; }
/** \brief Mutator method for isInternalRequestOnly field */
  void setisInternalRequestOnly(const bool& local_isInternalRequestOnly) { m_isInternalRequestOnly = local_isInternalRequestOnly; }
/** \brief Mutator method for prefetch field */
  void setprefetch(const PrefetchBit& local_prefetch) { m_prefetch = local_prefetch; }
/** \brief Mutator method for usado field */
  void setusado(const bool& local_usado) { m_usado = local_usado; }
/** \brief Mutator method for owner field */
  void setowner(const MachineID& local_owner) { m_owner = local_owner; }
/** \brief Mutator method for epoch field */
  void setepoch(const int& local_epoch) { m_epoch = local_epoch; }

  void print(ostream& out) const;
//private:
  Address m_Address; /**< Physical address for this TBE*/
  L2Cache_State m_TBEState; /**< Transient state*/
  DataBlock m_DataBlk; /**< Buffer for the data block*/
  int m_NumPendingExtAcks; /**< Number of ext acks that this L2 bank is waiting for*/
  int m_NumPendingIntAcks; /**< Number of int acks that this L2 bank is waiting for*/
  NetDest m_Forward_GetS_IDs; /**< Set of the external processors to forward the block*/
  NetDest m_L1_GetS_IDs; /**< Set of the internal processors that want the block in shared state*/
  MachineID m_Forward_GetX_ID; /**< ID of the L2 cache to forward the block*/
  MachineID m_L1_GetX_ID; /**< ID of the L1 cache to forward the block to once we get a response*/
  MachineID m_InvalidatorID; /**< ID of the L2 cache (needed for L2_SS -> L2_I)*/
  int m_ForwardGetX_AckCount; /**< Number of acks the GetX we are forwarded needs*/
  bool m_isPrefetch; /**< Set if this was caused by a prefetch*/
  bool m_isThreeHop; /**< is this request a three hop*/
  bool m_validForwardedGetXId; /**< Indicate whether a forwarded GetX ID is valid*/
  bool m_validInvalidator; /**< Indicate whether an invalidator is valid*/
  bool m_isInternalRequestOnly; /**< Is internal request only, i.e. only L1s*/
  PrefetchBit m_prefetch; /**< bit prebuscado*/
  bool m_usado; /**< marcamos si el bloque ha sido usado o no*/
  MachineID m_owner; /**< el procesador que trajo el bloque por prefetch*/
  int m_epoch; /**< epoch the block has been requested*/
};
// Output operator declaration
ostream& operator<<(ostream& out, const L2Cache_TBE& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const L2Cache_TBE& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // L2Cache_TBE_H
