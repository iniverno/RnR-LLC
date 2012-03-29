
#ifndef AbstractReplacementPolicyQuick_H
#define AbstractReplacementPolicyQuick_H

#include "Global.h"
#include "CacheMemoryQuick.h"
#include "CacheEntryQuick.h"

class CacheMemoryQuick;
class CacheEntryQuick;
class AbstractReplacementPolicyQuick {

public:

  AbstractReplacementPolicyQuick(Index num_sets, Index assoc);
  virtual ~AbstractReplacementPolicyQuick();

  /* touch a block. a.k.a. update timestamp */
  virtual void touch(Index set, Index way, Time time, uint proc) = 0; 
  
  /* returns the way to replace */
  virtual Index getVictim(Index set, uint proc) const = 0;

  virtual void replacementLower(Index set, Index way) =0;
  
	virtual void printStats(ostream& out,  char* name) =0;
	virtual void printStats(ostream& out) =0;
	virtual void clearStats() =0;

   uint whatSubSet(CacheEntryQuick *a) const ;


  /* get the time of the last access */
  Time getLastAccess(Index set, Index way);
   
  void putCache(CacheMemoryQuick* c);
  
  Histogram  m_histoSpace[2];
  unsigned char *m_nReused;
   Index m_wayOut;

  bool reusedL1;
  
  int m_in, m_out;
  uint **m_LRU1stReuse;  			// LRU position of the first reuse of that block
  
  int insideAsoc;
  int overAssoc;
  Address overAssocAddress;
  
protected:
  unsigned int m_num_sets;       /** total number of sets */
  unsigned int m_assoc;          /** set associativity */
  Time **m_last_ref_ptr;         /** timestamp of last reference */
  
   //stats
  uint64 m_select[3];
  CacheMemoryQuick* m_cache;
};



inline 
AbstractReplacementPolicyQuick::AbstractReplacementPolicyQuick(Index num_sets, Index assoc)
{
  m_num_sets = num_sets;
  m_assoc = assoc;
  m_last_ref_ptr = new Time*[m_num_sets];
  m_nReused = new unsigned char[m_num_sets];
  for(unsigned int i = 0; i < m_num_sets; i++){
    m_last_ref_ptr[i] = new Time[m_assoc];
    m_nReused[i] = 0;
    for(unsigned int j = 0; j < m_assoc; j++){
      m_last_ref_ptr[i][j] = 0;
    }
  }
}

inline
AbstractReplacementPolicyQuick::~AbstractReplacementPolicyQuick()
{
  if(m_last_ref_ptr != NULL){
    for(unsigned int i = 0; i < m_num_sets; i++){
      if(m_last_ref_ptr[i] != NULL){
        delete[] m_last_ref_ptr[i];
      }
    }
    
    delete[] m_last_ref_ptr;
  }
  if(m_nReused != NULL) delete [] m_nReused;
}

inline
Time AbstractReplacementPolicyQuick::getLastAccess(Index set, Index way)
{
  return m_last_ref_ptr[set][way];
}

inline
void AbstractReplacementPolicyQuick::putCache(CacheMemoryQuick* c)
{
  m_cache= c;  
}

inline
uint AbstractReplacementPolicyQuick::whatSubSet(CacheEntryQuick *a) const
{
  if(a->m_Sharers.count()==0 && !a->m_reused) return 0;
  if(a->m_Sharers.count()==0 && a->m_reused) return 1;
  if(a->m_Sharers.count()!=0) return 2;
  
  assert(0);
  return -1;
}

#endif // AbstractReplacementPolicyQuick_H
