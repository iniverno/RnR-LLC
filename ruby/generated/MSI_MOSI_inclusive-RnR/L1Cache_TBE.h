/** \file L1Cache_TBE.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef L1Cache_TBE_H
#define L1Cache_TBE_H

#include "Global.h"
#include "Allocator.h"
#include "Address.h"
#include "L1Cache_State.h"
#include "DataBlock.h"
class L1Cache_TBE {
public:
  L1Cache_TBE() 
  {
    // m_Address has no default
    m_TBEState = L1Cache_State_L1_I; // default value of L1Cache_State
    // m_DataBlk has no default
    m_isPrefetch = false; // default value of bool
    m_reused = false; // default value of bool
    m_reusedL1 = 0; // default value of int
  }
  ~L1Cache_TBE() { };
  L1Cache_TBE(const Address& local_Address, const L1Cache_State& local_TBEState, const DataBlock& local_DataBlk, const bool& local_isPrefetch, const bool& local_reused, const int& local_reusedL1)
  {
    m_Address = local_Address;
    m_TBEState = local_TBEState;
    m_DataBlk = local_DataBlk;
    m_isPrefetch = local_isPrefetch;
    m_reused = local_reused;
    m_reusedL1 = local_reusedL1;
  }
  // Const accessors methods for each field
/** \brief Const accessor method for Address field.
  * \return Address field
  */
  const Address& getAddress() const { return m_Address; }
/** \brief Const accessor method for TBEState field.
  * \return TBEState field
  */
  const L1Cache_State& getTBEState() const { return m_TBEState; }
/** \brief Const accessor method for DataBlk field.
  * \return DataBlk field
  */
  const DataBlock& getDataBlk() const { return m_DataBlk; }
/** \brief Const accessor method for isPrefetch field.
  * \return isPrefetch field
  */
  const bool& getisPrefetch() const { return m_isPrefetch; }
/** \brief Const accessor method for reused field.
  * \return reused field
  */
  const bool& getreused() const { return m_reused; }
/** \brief Const accessor method for reusedL1 field.
  * \return reusedL1 field
  */
  const int& getreusedL1() const { return m_reusedL1; }

  // Non const Accessors methods for each field
/** \brief Non-const accessor method for Address field.
  * \return Address field
  */
  Address& getAddress() { return m_Address; }
/** \brief Non-const accessor method for TBEState field.
  * \return TBEState field
  */
  L1Cache_State& getTBEState() { return m_TBEState; }
/** \brief Non-const accessor method for DataBlk field.
  * \return DataBlk field
  */
  DataBlock& getDataBlk() { return m_DataBlk; }
/** \brief Non-const accessor method for isPrefetch field.
  * \return isPrefetch field
  */
  bool& getisPrefetch() { return m_isPrefetch; }
/** \brief Non-const accessor method for reused field.
  * \return reused field
  */
  bool& getreused() { return m_reused; }
/** \brief Non-const accessor method for reusedL1 field.
  * \return reusedL1 field
  */
  int& getreusedL1() { return m_reusedL1; }

  // Mutator methods for each field
/** \brief Mutator method for Address field */
  void setAddress(const Address& local_Address) { m_Address = local_Address; }
/** \brief Mutator method for TBEState field */
  void setTBEState(const L1Cache_State& local_TBEState) { m_TBEState = local_TBEState; }
/** \brief Mutator method for DataBlk field */
  void setDataBlk(const DataBlock& local_DataBlk) { m_DataBlk = local_DataBlk; }
/** \brief Mutator method for isPrefetch field */
  void setisPrefetch(const bool& local_isPrefetch) { m_isPrefetch = local_isPrefetch; }
/** \brief Mutator method for reused field */
  void setreused(const bool& local_reused) { m_reused = local_reused; }
/** \brief Mutator method for reusedL1 field */
  void setreusedL1(const int& local_reusedL1) { m_reusedL1 = local_reusedL1; }

  void print(ostream& out) const;
//private:
  Address m_Address; /**< Physical address for this TBE*/
  L1Cache_State m_TBEState; /**< Transient state*/
  DataBlock m_DataBlk; /**< Buffer for the data block*/
  bool m_isPrefetch; /**< Set if this was caused by a prefetch*/
  bool m_reused; /**< la L1 o la L15 marca si el bloque ha sido usado o no*/
  int m_reusedL1; /**< La L15 almacena el uso que tuvo en la L1*/
};
// Output operator declaration
ostream& operator<<(ostream& out, const L1Cache_TBE& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const L1Cache_TBE& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // L1Cache_TBE_H
