/** \file Directory_Entry.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef Directory_Entry_H
#define Directory_Entry_H

#include "Global.h"
#include "Allocator.h"
#include "Directory_State.h"
#include "Set.h"
#include "NodeID.h"
#include "DataBlock.h"
#include "Address.h"
class Directory_Entry {
public:
  Directory_Entry() 
  {
    m_DirectoryState = Directory_State_NP; // default value of Directory_State
    // m_Sharers has no default
    m_DirOwner = true; // default for this field 
    m_ProcOwner = 0; // default for this field 
    // m_DataBlk has no default
    m_time = 0; // default value of Time
    // m_Add has no default
  }
  ~Directory_Entry() { };
  Directory_Entry(const Directory_State& local_DirectoryState, const Set& local_Sharers, const bool& local_DirOwner, const NodeID& local_ProcOwner, const DataBlock& local_DataBlk, const Time& local_time, const Address& local_Add)
  {
    m_DirectoryState = local_DirectoryState;
    m_Sharers = local_Sharers;
    m_DirOwner = local_DirOwner;
    m_ProcOwner = local_ProcOwner;
    m_DataBlk = local_DataBlk;
    m_time = local_time;
    m_Add = local_Add;
  }
  // Const accessors methods for each field
/** \brief Const accessor method for DirectoryState field.
  * \return DirectoryState field
  */
  const Directory_State& getDirectoryState() const { return m_DirectoryState; }
/** \brief Const accessor method for Sharers field.
  * \return Sharers field
  */
  const Set& getSharers() const { return m_Sharers; }
/** \brief Const accessor method for DirOwner field.
  * \return DirOwner field
  */
  const bool& getDirOwner() const { return m_DirOwner; }
/** \brief Const accessor method for ProcOwner field.
  * \return ProcOwner field
  */
  const NodeID& getProcOwner() const { return m_ProcOwner; }
/** \brief Const accessor method for DataBlk field.
  * \return DataBlk field
  */
  const DataBlock& getDataBlk() const { return m_DataBlk; }
/** \brief Const accessor method for time field.
  * \return time field
  */
  const Time& gettime() const { return m_time; }
/** \brief Const accessor method for Add field.
  * \return Add field
  */
  const Address& getAdd() const { return m_Add; }

  // Non const Accessors methods for each field
/** \brief Non-const accessor method for DirectoryState field.
  * \return DirectoryState field
  */
  Directory_State& getDirectoryState() { return m_DirectoryState; }
/** \brief Non-const accessor method for Sharers field.
  * \return Sharers field
  */
  Set& getSharers() { return m_Sharers; }
/** \brief Non-const accessor method for DirOwner field.
  * \return DirOwner field
  */
  bool& getDirOwner() { return m_DirOwner; }
/** \brief Non-const accessor method for ProcOwner field.
  * \return ProcOwner field
  */
  NodeID& getProcOwner() { return m_ProcOwner; }
/** \brief Non-const accessor method for DataBlk field.
  * \return DataBlk field
  */
  DataBlock& getDataBlk() { return m_DataBlk; }
/** \brief Non-const accessor method for time field.
  * \return time field
  */
  Time& gettime() { return m_time; }
/** \brief Non-const accessor method for Add field.
  * \return Add field
  */
  Address& getAdd() { return m_Add; }

  // Mutator methods for each field
/** \brief Mutator method for DirectoryState field */
  void setDirectoryState(const Directory_State& local_DirectoryState) { m_DirectoryState = local_DirectoryState; }
/** \brief Mutator method for Sharers field */
  void setSharers(const Set& local_Sharers) { m_Sharers = local_Sharers; }
/** \brief Mutator method for DirOwner field */
  void setDirOwner(const bool& local_DirOwner) { m_DirOwner = local_DirOwner; }
/** \brief Mutator method for ProcOwner field */
  void setProcOwner(const NodeID& local_ProcOwner) { m_ProcOwner = local_ProcOwner; }
/** \brief Mutator method for DataBlk field */
  void setDataBlk(const DataBlock& local_DataBlk) { m_DataBlk = local_DataBlk; }
/** \brief Mutator method for time field */
  void settime(const Time& local_time) { m_time = local_time; }
/** \brief Mutator method for Add field */
  void setAdd(const Address& local_Add) { m_Add = local_Add; }

  void print(ostream& out) const;
//private:
  Directory_State m_DirectoryState; /**< Directory state*/
  Set m_Sharers; /**< Set of sharers - must be L2 caches*/
  bool m_DirOwner; /**< Is dir owner?*/
  NodeID m_ProcOwner; /**< Processor owner*/
  DataBlock m_DataBlk; /**< data for the block*/
  Time m_time; /**< */
  Address m_Add; /**< */
};
// Output operator declaration
ostream& operator<<(ostream& out, const Directory_Entry& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const Directory_Entry& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // Directory_Entry_H
