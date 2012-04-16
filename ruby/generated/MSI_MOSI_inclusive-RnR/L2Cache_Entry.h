/** \file L2Cache_Entry.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef L2Cache_Entry_H
#define L2Cache_Entry_H

#include "Global.h"
#include "Allocator.h"
#include "L2Cache_State.h"
#include "NetDest.h"
#include "DataBlock.h"
#include "PrefetchBit.h"
#include "Address.h"
#include "L2Cache_State.h"
#include "L2Cache_State.h"
#include "MachineID.h"
#include "MachineID.h"
#include "NetDest.h"
#include "AbstractCacheEntry.h"
class L2Cache_Entry :  public AbstractCacheEntry {
public:
  L2Cache_Entry() 
  : AbstractCacheEntry()
  {
    m_CacheState = L2Cache_State_L2_NP; // default value of L2Cache_State
    // m_Sharers has no default
    // m_DataBlk has no default
    m_prefetch = PrefetchBit_No; // default value of PrefetchBit
    // m_PC has no default
    m_ZeroBit = false; // default value of bool
    m_reused = false; // default value of bool
    m_reused2 = false; // default value of bool
    m_reused3 = false; // default value of bool
    m_prefDWG = false; // default value of bool
    m_PrevLocalCacheState = L2Cache_State_L2_NP; // default value of L2Cache_State
    m_PrevRemoteCacheState = L2Cache_State_L2_NP; // default value of L2Cache_State
    // m_prevOwner has no default
    // m_owner has no default
    // m_prevSharers has no default
    m_prefTypeRepl = 0; // default value of int
    m_epoch = 0; // default value of int
    m_uses = 0; // default value of int
    m_timeLoad = 0; // default value of Time
    m_timeLast = 0; // default value of Time
    m_timeRepl = 0; // default value of Time
    m_reuseL1 = 0; // default value of int
    m_instr = false; // default value of bool
    m_RRPV = 0; // default value of int
    m_NRU = false; // default value of bool
    m_sign = 0; // default value of int
    m_posFIFO = 0; // default value of int
  }
  ~L2Cache_Entry() { };
  L2Cache_Entry(const L2Cache_State& local_CacheState, const NetDest& local_Sharers, const DataBlock& local_DataBlk, const PrefetchBit& local_prefetch, const Address& local_PC, const bool& local_ZeroBit, const bool& local_reused, const bool& local_reused2, const bool& local_reused3, const bool& local_prefDWG, const L2Cache_State& local_PrevLocalCacheState, const L2Cache_State& local_PrevRemoteCacheState, const MachineID& local_prevOwner, const MachineID& local_owner, const NetDest& local_prevSharers, const int& local_prefTypeRepl, const int& local_epoch, const int& local_uses, const Time& local_timeLoad, const Time& local_timeLast, const Time& local_timeRepl, const int& local_reuseL1, const bool& local_instr, const int& local_RRPV, const bool& local_NRU, const int& local_sign, const int& local_posFIFO)
  : AbstractCacheEntry()
  {
    m_CacheState = local_CacheState;
    m_Sharers = local_Sharers;
    m_DataBlk = local_DataBlk;
    m_prefetch = local_prefetch;
    m_PC = local_PC;
    m_ZeroBit = local_ZeroBit;
    m_reused = local_reused;
    m_reused2 = local_reused2;
    m_reused3 = local_reused3;
    m_prefDWG = local_prefDWG;
    m_PrevLocalCacheState = local_PrevLocalCacheState;
    m_PrevRemoteCacheState = local_PrevRemoteCacheState;
    m_prevOwner = local_prevOwner;
    m_owner = local_owner;
    m_prevSharers = local_prevSharers;
    m_prefTypeRepl = local_prefTypeRepl;
    m_epoch = local_epoch;
    m_uses = local_uses;
    m_timeLoad = local_timeLoad;
    m_timeLast = local_timeLast;
    m_timeRepl = local_timeRepl;
    m_reuseL1 = local_reuseL1;
    m_instr = local_instr;
    m_RRPV = local_RRPV;
    m_NRU = local_NRU;
    m_sign = local_sign;
    m_posFIFO = local_posFIFO;
  }
  // Const accessors methods for each field
/** \brief Const accessor method for CacheState field.
  * \return CacheState field
  */
  const L2Cache_State& getCacheState() const { return m_CacheState; }
/** \brief Const accessor method for Sharers field.
  * \return Sharers field
  */
  const NetDest& getSharers() const { return m_Sharers; }
/** \brief Const accessor method for DataBlk field.
  * \return DataBlk field
  */
  const DataBlock& getDataBlk() const { return m_DataBlk; }
/** \brief Const accessor method for prefetch field.
  * \return prefetch field
  */
  const PrefetchBit& getprefetch() const { return m_prefetch; }
/** \brief Const accessor method for PC field.
  * \return PC field
  */
  const Address& getPC() const { return m_PC; }
/** \brief Const accessor method for ZeroBit field.
  * \return ZeroBit field
  */
  const bool& getZeroBit() const { return m_ZeroBit; }
/** \brief Const accessor method for reused field.
  * \return reused field
  */
  const bool& getreused() const { return m_reused; }
/** \brief Const accessor method for reused2 field.
  * \return reused2 field
  */
  const bool& getreused2() const { return m_reused2; }
/** \brief Const accessor method for reused3 field.
  * \return reused3 field
  */
  const bool& getreused3() const { return m_reused3; }
/** \brief Const accessor method for prefDWG field.
  * \return prefDWG field
  */
  const bool& getprefDWG() const { return m_prefDWG; }
/** \brief Const accessor method for PrevLocalCacheState field.
  * \return PrevLocalCacheState field
  */
  const L2Cache_State& getPrevLocalCacheState() const { return m_PrevLocalCacheState; }
/** \brief Const accessor method for PrevRemoteCacheState field.
  * \return PrevRemoteCacheState field
  */
  const L2Cache_State& getPrevRemoteCacheState() const { return m_PrevRemoteCacheState; }
/** \brief Const accessor method for prevOwner field.
  * \return prevOwner field
  */
  const MachineID& getprevOwner() const { return m_prevOwner; }
/** \brief Const accessor method for owner field.
  * \return owner field
  */
  const MachineID& getowner() const { return m_owner; }
/** \brief Const accessor method for prevSharers field.
  * \return prevSharers field
  */
  const NetDest& getprevSharers() const { return m_prevSharers; }
/** \brief Const accessor method for prefTypeRepl field.
  * \return prefTypeRepl field
  */
  const int& getprefTypeRepl() const { return m_prefTypeRepl; }
/** \brief Const accessor method for epoch field.
  * \return epoch field
  */
  const int& getepoch() const { return m_epoch; }
/** \brief Const accessor method for uses field.
  * \return uses field
  */
  const int& getuses() const { return m_uses; }
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
/** \brief Const accessor method for reuseL1 field.
  * \return reuseL1 field
  */
  const int& getreuseL1() const { return m_reuseL1; }
/** \brief Const accessor method for instr field.
  * \return instr field
  */
  const bool& getinstr() const { return m_instr; }
/** \brief Const accessor method for RRPV field.
  * \return RRPV field
  */
  const int& getRRPV() const { return m_RRPV; }
/** \brief Const accessor method for NRU field.
  * \return NRU field
  */
  const bool& getNRU() const { return m_NRU; }
/** \brief Const accessor method for sign field.
  * \return sign field
  */
  const int& getsign() const { return m_sign; }
/** \brief Const accessor method for posFIFO field.
  * \return posFIFO field
  */
  const int& getposFIFO() const { return m_posFIFO; }

  // Non const Accessors methods for each field
/** \brief Non-const accessor method for CacheState field.
  * \return CacheState field
  */
  L2Cache_State& getCacheState() { return m_CacheState; }
/** \brief Non-const accessor method for Sharers field.
  * \return Sharers field
  */
  NetDest& getSharers() { return m_Sharers; }
/** \brief Non-const accessor method for DataBlk field.
  * \return DataBlk field
  */
  DataBlock& getDataBlk() { return m_DataBlk; }
/** \brief Non-const accessor method for prefetch field.
  * \return prefetch field
  */
  PrefetchBit& getprefetch() { return m_prefetch; }
/** \brief Non-const accessor method for PC field.
  * \return PC field
  */
  Address& getPC() { return m_PC; }
/** \brief Non-const accessor method for ZeroBit field.
  * \return ZeroBit field
  */
  bool& getZeroBit() { return m_ZeroBit; }
/** \brief Non-const accessor method for reused field.
  * \return reused field
  */
  bool& getreused() { return m_reused; }
/** \brief Non-const accessor method for reused2 field.
  * \return reused2 field
  */
  bool& getreused2() { return m_reused2; }
/** \brief Non-const accessor method for reused3 field.
  * \return reused3 field
  */
  bool& getreused3() { return m_reused3; }
/** \brief Non-const accessor method for prefDWG field.
  * \return prefDWG field
  */
  bool& getprefDWG() { return m_prefDWG; }
/** \brief Non-const accessor method for PrevLocalCacheState field.
  * \return PrevLocalCacheState field
  */
  L2Cache_State& getPrevLocalCacheState() { return m_PrevLocalCacheState; }
/** \brief Non-const accessor method for PrevRemoteCacheState field.
  * \return PrevRemoteCacheState field
  */
  L2Cache_State& getPrevRemoteCacheState() { return m_PrevRemoteCacheState; }
/** \brief Non-const accessor method for prevOwner field.
  * \return prevOwner field
  */
  MachineID& getprevOwner() { return m_prevOwner; }
/** \brief Non-const accessor method for owner field.
  * \return owner field
  */
  MachineID& getowner() { return m_owner; }
/** \brief Non-const accessor method for prevSharers field.
  * \return prevSharers field
  */
  NetDest& getprevSharers() { return m_prevSharers; }
/** \brief Non-const accessor method for prefTypeRepl field.
  * \return prefTypeRepl field
  */
  int& getprefTypeRepl() { return m_prefTypeRepl; }
/** \brief Non-const accessor method for epoch field.
  * \return epoch field
  */
  int& getepoch() { return m_epoch; }
/** \brief Non-const accessor method for uses field.
  * \return uses field
  */
  int& getuses() { return m_uses; }
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
/** \brief Non-const accessor method for reuseL1 field.
  * \return reuseL1 field
  */
  int& getreuseL1() { return m_reuseL1; }
/** \brief Non-const accessor method for instr field.
  * \return instr field
  */
  bool& getinstr() { return m_instr; }
/** \brief Non-const accessor method for RRPV field.
  * \return RRPV field
  */
  int& getRRPV() { return m_RRPV; }
/** \brief Non-const accessor method for NRU field.
  * \return NRU field
  */
  bool& getNRU() { return m_NRU; }
/** \brief Non-const accessor method for sign field.
  * \return sign field
  */
  int& getsign() { return m_sign; }
/** \brief Non-const accessor method for posFIFO field.
  * \return posFIFO field
  */
  int& getposFIFO() { return m_posFIFO; }

  // Mutator methods for each field
/** \brief Mutator method for CacheState field */
  void setCacheState(const L2Cache_State& local_CacheState) { m_CacheState = local_CacheState; }
/** \brief Mutator method for Sharers field */
  void setSharers(const NetDest& local_Sharers) { m_Sharers = local_Sharers; }
/** \brief Mutator method for DataBlk field */
  void setDataBlk(const DataBlock& local_DataBlk) { m_DataBlk = local_DataBlk; }
/** \brief Mutator method for prefetch field */
  void setprefetch(const PrefetchBit& local_prefetch) { m_prefetch = local_prefetch; }
/** \brief Mutator method for PC field */
  void setPC(const Address& local_PC) { m_PC = local_PC; }
/** \brief Mutator method for ZeroBit field */
  void setZeroBit(const bool& local_ZeroBit) { m_ZeroBit = local_ZeroBit; }
/** \brief Mutator method for reused field */
  void setreused(const bool& local_reused) { m_reused = local_reused; }
/** \brief Mutator method for reused2 field */
  void setreused2(const bool& local_reused2) { m_reused2 = local_reused2; }
/** \brief Mutator method for reused3 field */
  void setreused3(const bool& local_reused3) { m_reused3 = local_reused3; }
/** \brief Mutator method for prefDWG field */
  void setprefDWG(const bool& local_prefDWG) { m_prefDWG = local_prefDWG; }
/** \brief Mutator method for PrevLocalCacheState field */
  void setPrevLocalCacheState(const L2Cache_State& local_PrevLocalCacheState) { m_PrevLocalCacheState = local_PrevLocalCacheState; }
/** \brief Mutator method for PrevRemoteCacheState field */
  void setPrevRemoteCacheState(const L2Cache_State& local_PrevRemoteCacheState) { m_PrevRemoteCacheState = local_PrevRemoteCacheState; }
/** \brief Mutator method for prevOwner field */
  void setprevOwner(const MachineID& local_prevOwner) { m_prevOwner = local_prevOwner; }
/** \brief Mutator method for owner field */
  void setowner(const MachineID& local_owner) { m_owner = local_owner; }
/** \brief Mutator method for prevSharers field */
  void setprevSharers(const NetDest& local_prevSharers) { m_prevSharers = local_prevSharers; }
/** \brief Mutator method for prefTypeRepl field */
  void setprefTypeRepl(const int& local_prefTypeRepl) { m_prefTypeRepl = local_prefTypeRepl; }
/** \brief Mutator method for epoch field */
  void setepoch(const int& local_epoch) { m_epoch = local_epoch; }
/** \brief Mutator method for uses field */
  void setuses(const int& local_uses) { m_uses = local_uses; }
/** \brief Mutator method for timeLoad field */
  void settimeLoad(const Time& local_timeLoad) { m_timeLoad = local_timeLoad; }
/** \brief Mutator method for timeLast field */
  void settimeLast(const Time& local_timeLast) { m_timeLast = local_timeLast; }
/** \brief Mutator method for timeRepl field */
  void settimeRepl(const Time& local_timeRepl) { m_timeRepl = local_timeRepl; }
/** \brief Mutator method for reuseL1 field */
  void setreuseL1(const int& local_reuseL1) { m_reuseL1 = local_reuseL1; }
/** \brief Mutator method for instr field */
  void setinstr(const bool& local_instr) { m_instr = local_instr; }
/** \brief Mutator method for RRPV field */
  void setRRPV(const int& local_RRPV) { m_RRPV = local_RRPV; }
/** \brief Mutator method for NRU field */
  void setNRU(const bool& local_NRU) { m_NRU = local_NRU; }
/** \brief Mutator method for sign field */
  void setsign(const int& local_sign) { m_sign = local_sign; }
/** \brief Mutator method for posFIFO field */
  void setposFIFO(const int& local_posFIFO) { m_posFIFO = local_posFIFO; }

  void print(ostream& out) const;
//private:
  L2Cache_State m_CacheState; /**< cache state*/
  NetDest m_Sharers; /**< tracks the L1 shares on-chip*/
  DataBlock m_DataBlk; /**< data for the block*/
  PrefetchBit m_prefetch; /**< bit prebuscado*/
  Address m_PC; /**< PC de la instruccion que o trajo*/
  bool m_ZeroBit;
  bool m_reused; /**< marcamos si el bloque ha sido usado o no*/
  bool m_reused2; /**< marcamos si el bloque ha sido usado o no*/
  bool m_reused3; /**< marcamos si el bloque ha sido usado o no*/
  bool m_prefDWG; /**< marca si nos degradado una prebœsqueda externa*/
  L2Cache_State m_PrevLocalCacheState; /**< previous local cache state*/
  L2Cache_State m_PrevRemoteCacheState; /**< previous remote cache state*/
  MachineID m_prevOwner; /**< previous owner*/
  MachineID m_owner; /**< el procesador que trajo el bloque por prefetch*/
  NetDest m_prevSharers; /**< previous sharers*/
  int m_prefTypeRepl; /**< repl por preb, 1=prefS, 2 =prefX*/
  int m_epoch; /**< epoch the block arrived*/
  int m_uses; /**< number of uses*/
  Time m_timeLoad; /**< */
  Time m_timeLast; /**< */
  Time m_timeRepl; /**< */
  int m_reuseL1; /**< */
  bool m_instr; /**< if it is a instruction or not */
  int m_RRPV; /**< interval prediction for RRIP algorithm*/
  bool m_NRU; /**< */
  int m_sign; /**< sign for the SHiP algorithm*/
  int m_posFIFO; /**< Position of the data in the FIFO data array */
};
// Output operator declaration
ostream& operator<<(ostream& out, const L2Cache_Entry& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const L2Cache_Entry& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // L2Cache_Entry_H
