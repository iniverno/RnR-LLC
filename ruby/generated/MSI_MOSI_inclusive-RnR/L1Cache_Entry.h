/** \file L1Cache_Entry.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef L1Cache_Entry_H
#define L1Cache_Entry_H

#include "Global.h"
#include "Allocator.h"
#include "L1Cache_State.h"
#include "DataBlock.h"
#include "L1Cache_State.h"
#include "L1Cache_State.h"
#include "MachineID.h"
#include "NetDest.h"
#include "MachineID.h"
#include "AbstractCacheEntry.h"
class L1Cache_Entry :  public AbstractCacheEntry {
public:
  L1Cache_Entry() 
  : AbstractCacheEntry()
  {
    m_CacheState = L1Cache_State_L1_I; // default value of L1Cache_State
    // m_DataBlk has no default
    m_prefDWG = false; // default value of bool
    m_PrevLocalCacheState = L1Cache_State_L1_I; // default value of L1Cache_State
    m_PrevRemoteCacheState = L1Cache_State_L1_I; // default value of L1Cache_State
    // m_prevOwner has no default
    // m_prevSharers has no default
    m_prefTypeRepl = 0; // default value of int
    m_inst = false; // default value of bool
    m_incl = 0; // default value of int
    m_timeLoad = 0; // default value of Time
    m_timeLast = 0; // default value of Time
    m_timeRepl = 0; // default value of Time
    m_reused = false; // default value of bool
    m_reusedL1 = 0; // default value of int
    m_uses = 0; // default value of int
    // m_owner has no default
    m_NRU = false; // default value of bool
  }
  ~L1Cache_Entry() { };
  L1Cache_Entry(const L1Cache_State& local_CacheState, const DataBlock& local_DataBlk, const bool& local_prefDWG, const L1Cache_State& local_PrevLocalCacheState, const L1Cache_State& local_PrevRemoteCacheState, const MachineID& local_prevOwner, const NetDest& local_prevSharers, const int& local_prefTypeRepl, const bool& local_inst, const int& local_incl, const Time& local_timeLoad, const Time& local_timeLast, const Time& local_timeRepl, const bool& local_reused, const int& local_reusedL1, const int& local_uses, const MachineID& local_owner, const bool& local_NRU)
  : AbstractCacheEntry()
  {
    m_CacheState = local_CacheState;
    m_DataBlk = local_DataBlk;
    m_prefDWG = local_prefDWG;
    m_PrevLocalCacheState = local_PrevLocalCacheState;
    m_PrevRemoteCacheState = local_PrevRemoteCacheState;
    m_prevOwner = local_prevOwner;
    m_prevSharers = local_prevSharers;
    m_prefTypeRepl = local_prefTypeRepl;
    m_inst = local_inst;
    m_incl = local_incl;
    m_timeLoad = local_timeLoad;
    m_timeLast = local_timeLast;
    m_timeRepl = local_timeRepl;
    m_reused = local_reused;
    m_reusedL1 = local_reusedL1;
    m_uses = local_uses;
    m_owner = local_owner;
    m_NRU = local_NRU;
  }
  // Const accessors methods for each field
/** \brief Const accessor method for CacheState field.
  * \return CacheState field
  */
  const L1Cache_State& getCacheState() const { return m_CacheState; }
/** \brief Const accessor method for DataBlk field.
  * \return DataBlk field
  */
  const DataBlock& getDataBlk() const { return m_DataBlk; }
/** \brief Const accessor method for prefDWG field.
  * \return prefDWG field
  */
  const bool& getprefDWG() const { return m_prefDWG; }
/** \brief Const accessor method for PrevLocalCacheState field.
  * \return PrevLocalCacheState field
  */
  const L1Cache_State& getPrevLocalCacheState() const { return m_PrevLocalCacheState; }
/** \brief Const accessor method for PrevRemoteCacheState field.
  * \return PrevRemoteCacheState field
  */
  const L1Cache_State& getPrevRemoteCacheState() const { return m_PrevRemoteCacheState; }
/** \brief Const accessor method for prevOwner field.
  * \return prevOwner field
  */
  const MachineID& getprevOwner() const { return m_prevOwner; }
/** \brief Const accessor method for prevSharers field.
  * \return prevSharers field
  */
  const NetDest& getprevSharers() const { return m_prevSharers; }
/** \brief Const accessor method for prefTypeRepl field.
  * \return prefTypeRepl field
  */
  const int& getprefTypeRepl() const { return m_prefTypeRepl; }
/** \brief Const accessor method for inst field.
  * \return inst field
  */
  const bool& getinst() const { return m_inst; }
/** \brief Const accessor method for incl field.
  * \return incl field
  */
  const int& getincl() const { return m_incl; }
/** \brief Const accessor method for timeLoad field.
  * \return timeLoad field
  */
  const Time& gettimeLoad() const { return m_timeLoad; }
/** \brief Const accessor method for timeLast field.
  * \return timeLast field
  */
  const Time& gettimeLast() const { return m_timeLast; }
/** \brief Const accessor method for timeRepl field.
  * \return timeRepl field
  */
  const Time& gettimeRepl() const { return m_timeRepl; }
/** \brief Const accessor method for reused field.
  * \return reused field
  */
  const bool& getreused() const { return m_reused; }
/** \brief Const accessor method for reusedL1 field.
  * \return reusedL1 field
  */
  const int& getreusedL1() const { return m_reusedL1; }
/** \brief Const accessor method for uses field.
  * \return uses field
  */
  const int& getuses() const { return m_uses; }
/** \brief Const accessor method for owner field.
  * \return owner field
  */
  const MachineID& getowner() const { return m_owner; }
/** \brief Const accessor method for NRU field.
  * \return NRU field
  */
  const bool& getNRU() const { return m_NRU; }

  // Non const Accessors methods for each field
/** \brief Non-const accessor method for CacheState field.
  * \return CacheState field
  */
  L1Cache_State& getCacheState() { return m_CacheState; }
/** \brief Non-const accessor method for DataBlk field.
  * \return DataBlk field
  */
  DataBlock& getDataBlk() { return m_DataBlk; }
/** \brief Non-const accessor method for prefDWG field.
  * \return prefDWG field
  */
  bool& getprefDWG() { return m_prefDWG; }
/** \brief Non-const accessor method for PrevLocalCacheState field.
  * \return PrevLocalCacheState field
  */
  L1Cache_State& getPrevLocalCacheState() { return m_PrevLocalCacheState; }
/** \brief Non-const accessor method for PrevRemoteCacheState field.
  * \return PrevRemoteCacheState field
  */
  L1Cache_State& getPrevRemoteCacheState() { return m_PrevRemoteCacheState; }
/** \brief Non-const accessor method for prevOwner field.
  * \return prevOwner field
  */
  MachineID& getprevOwner() { return m_prevOwner; }
/** \brief Non-const accessor method for prevSharers field.
  * \return prevSharers field
  */
  NetDest& getprevSharers() { return m_prevSharers; }
/** \brief Non-const accessor method for prefTypeRepl field.
  * \return prefTypeRepl field
  */
  int& getprefTypeRepl() { return m_prefTypeRepl; }
/** \brief Non-const accessor method for inst field.
  * \return inst field
  */
  bool& getinst() { return m_inst; }
/** \brief Non-const accessor method for incl field.
  * \return incl field
  */
  int& getincl() { return m_incl; }
/** \brief Non-const accessor method for timeLoad field.
  * \return timeLoad field
  */
  Time& gettimeLoad() { return m_timeLoad; }
/** \brief Non-const accessor method for timeLast field.
  * \return timeLast field
  */
  Time& gettimeLast() { return m_timeLast; }
/** \brief Non-const accessor method for timeRepl field.
  * \return timeRepl field
  */
  Time& gettimeRepl() { return m_timeRepl; }
/** \brief Non-const accessor method for reused field.
  * \return reused field
  */
  bool& getreused() { return m_reused; }
/** \brief Non-const accessor method for reusedL1 field.
  * \return reusedL1 field
  */
  int& getreusedL1() { return m_reusedL1; }
/** \brief Non-const accessor method for uses field.
  * \return uses field
  */
  int& getuses() { return m_uses; }
/** \brief Non-const accessor method for owner field.
  * \return owner field
  */
  MachineID& getowner() { return m_owner; }
/** \brief Non-const accessor method for NRU field.
  * \return NRU field
  */
  bool& getNRU() { return m_NRU; }

  // Mutator methods for each field
/** \brief Mutator method for CacheState field */
  void setCacheState(const L1Cache_State& local_CacheState) { m_CacheState = local_CacheState; }
/** \brief Mutator method for DataBlk field */
  void setDataBlk(const DataBlock& local_DataBlk) { m_DataBlk = local_DataBlk; }
/** \brief Mutator method for prefDWG field */
  void setprefDWG(const bool& local_prefDWG) { m_prefDWG = local_prefDWG; }
/** \brief Mutator method for PrevLocalCacheState field */
  void setPrevLocalCacheState(const L1Cache_State& local_PrevLocalCacheState) { m_PrevLocalCacheState = local_PrevLocalCacheState; }
/** \brief Mutator method for PrevRemoteCacheState field */
  void setPrevRemoteCacheState(const L1Cache_State& local_PrevRemoteCacheState) { m_PrevRemoteCacheState = local_PrevRemoteCacheState; }
/** \brief Mutator method for prevOwner field */
  void setprevOwner(const MachineID& local_prevOwner) { m_prevOwner = local_prevOwner; }
/** \brief Mutator method for prevSharers field */
  void setprevSharers(const NetDest& local_prevSharers) { m_prevSharers = local_prevSharers; }
/** \brief Mutator method for prefTypeRepl field */
  void setprefTypeRepl(const int& local_prefTypeRepl) { m_prefTypeRepl = local_prefTypeRepl; }
/** \brief Mutator method for inst field */
  void setinst(const bool& local_inst) { m_inst = local_inst; }
/** \brief Mutator method for incl field */
  void setincl(const int& local_incl) { m_incl = local_incl; }
/** \brief Mutator method for timeLoad field */
  void settimeLoad(const Time& local_timeLoad) { m_timeLoad = local_timeLoad; }
/** \brief Mutator method for timeLast field */
  void settimeLast(const Time& local_timeLast) { m_timeLast = local_timeLast; }
/** \brief Mutator method for timeRepl field */
  void settimeRepl(const Time& local_timeRepl) { m_timeRepl = local_timeRepl; }
/** \brief Mutator method for reused field */
  void setreused(const bool& local_reused) { m_reused = local_reused; }
/** \brief Mutator method for reusedL1 field */
  void setreusedL1(const int& local_reusedL1) { m_reusedL1 = local_reusedL1; }
/** \brief Mutator method for uses field */
  void setuses(const int& local_uses) { m_uses = local_uses; }
/** \brief Mutator method for owner field */
  void setowner(const MachineID& local_owner) { m_owner = local_owner; }
/** \brief Mutator method for NRU field */
  void setNRU(const bool& local_NRU) { m_NRU = local_NRU; }

  void print(ostream& out) const;
//private:
  L1Cache_State m_CacheState; /**< cache state*/
  DataBlock m_DataBlk; /**< data for the block*/
  bool m_prefDWG; /**< marca si nos degradado una prebœsqueda externa*/
  L1Cache_State m_PrevLocalCacheState; /**< previous local cache state*/
  L1Cache_State m_PrevRemoteCacheState; /**< previous remote cache state*/
  MachineID m_prevOwner; /**< previous owner*/
  NetDest m_prevSharers; /**< previous sharers*/
  int m_prefTypeRepl; /**< repl por preb, 1=prefS, 2 =prefX*/
  bool m_inst; /**< cacheI o cacheD*/
  int m_incl; /**< only for the L15, says if there is a copy on L1*/
  Time m_timeLoad; /**< */
  Time m_timeLast; /**< */
  Time m_timeRepl; /**< */
  bool m_reused; /**< la L1 o la L15 marca si el bloque ha sido usado o no*/
  int m_reusedL1; /**< La L15 almacena el uso que tuvo en la L1*/
  int m_uses; /**< */
  MachineID m_owner; /**< */
  bool m_NRU; /**< */
};
// Output operator declaration
ostream& operator<<(ostream& out, const L1Cache_Entry& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const L1Cache_Entry& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // L1Cache_Entry_H
