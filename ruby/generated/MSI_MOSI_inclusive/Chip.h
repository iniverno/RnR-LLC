/** \file Chip.h 
  * Auto generated C++ code started by symbols/SymbolTable.C:238
  */ 

#ifndef CHIP_H
#define CHIP_H

#include "Global.h"
#include "Types.h"
#include "AbstractChip.h"
class Network;

class L1Cache_Controller;
class L2Cache_Controller;
class Directory_Controller;
class Chip : public AbstractChip {
public:

  // Constructors
  Chip(NodeID chip_number, Network* net_ptr);

  // Destructor
  ~Chip();

  // Public Methods
  void recordCacheContents(CacheRecorder& tr) const;
  void dumpCaches(ostream& out) const;
  void dumpCacheData(ostream& out) const;
  static void printStats(ostream& out);
  static void clearStats();
  void printConfig(ostream& out);
  void print(ostream& out) const;
#ifdef CHECK_COHERENCE
  bool isBlockShared(const Address& addr) const;
  bool isBlockExclusive(const Address& addr) const;
#endif /* CHECK_COHERENCE */

private:
  // Private copy constructor and assignment operator
  Chip(const Chip& obj);
  Chip& operator=(const Chip& obj);
    void printTemp() const;
    void resetTemp() const;
    void printReuse() const;
    void resetReuse() const;

public: // FIXME - these should not be public
  // Data Members (m_ prefix)

  Chip* m_chip_ptr;

  // SLICC object variables

  Vector < MessageBuffer* >  m_L1Cache_requestFromL1Cache_vec;
  Vector < MessageBuffer* >  m_L1Cache_responseFromL1Cache_vec;
  Vector < MessageBuffer* >  m_L1Cache_requestToL1Cache_vec;
  Vector < MessageBuffer* >  m_L1Cache_responseToL1Cache_vec;
  Vector < TBETable<L1Cache_TBE>* >  m_L1Cache_L1_TBEs_vec;
  Vector < MessageBuffer* >  m_L2Cache_L1RequestFromL2Cache_vec;
  Vector < MessageBuffer* >  m_L2Cache_responseFromL2Cache_vec;
  Vector < MessageBuffer* >  m_L2Cache_finalAckFromL2Cache_vec;
  Vector < MessageBuffer* >  m_L2Cache_L1RequestToL2Cache_vec;
  Vector < MessageBuffer* >  m_L2Cache_forwardedRequestToL2Cache_vec;
  Vector < MessageBuffer* >  m_L2Cache_responseToL2Cache_vec;
  Vector < TBETable<L2Cache_TBE>* >  m_L2Cache_L2_TBEs_vec;
  Vector < TBETable<L2Cache_TBE>* >  m_L2Cache_Pref_TBEs_vec;
  Vector < CacheMemory<L2Cache_Entry>* >  m_L2Cache_L2cacheMemory_vec;
  Vector < MessageBuffer* >  m_Directory_forwardedRequestFromDir_vec;
  Vector < MessageBuffer* >  m_Directory_responseFromDir_vec;
  Vector < MessageBuffer* >  m_Directory_requestToDir_vec;
  Vector < MessageBuffer* >  m_Directory_finalAckToDir_vec;
  Vector < MessageBuffer* >  m_Directory_prefRequestToDir_vec;
  Vector < MessageBuffer* >  m_Directory_prefResponseFromDir_vec;
  Vector < DirectoryMemory* >  m_Directory_directory_vec;

  // SLICC machine/controller variables
  Vector < L1Cache_Controller* > m_L1Cache_Controller_vec;
  Vector < L2Cache_Controller* > m_L2Cache_Controller_vec;
  Vector < Directory_Controller* > m_Directory_Controller_vec;

  // machine external SLICC function decls
  GenericRequestType convertToGenericType(CoherenceRequestType param_type);
};

#endif // CHIP_H
