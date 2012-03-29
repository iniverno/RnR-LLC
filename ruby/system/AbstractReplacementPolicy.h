
#ifndef ABSTRACTREPLACEMENTPOLICY_H
#define ABSTRACTREPLACEMENTPOLICY_H

#include "Global.h"
#include "L1Cache_Entry.h"
#include "L2Cache_Entry.h"

class AbstractReplacementPolicy {

public:

  AbstractReplacementPolicy(Index num_sets, Index assoc);
  virtual ~AbstractReplacementPolicy();

  /* touch a block. a.k.a. update timestamp */
  virtual void touch(Index set, Index way, Time time, uint proc) = 0; 

  /* returns the way to replace */
  virtual Index getVictim(Index set, uint proc) const = 0;
  virtual void replacementLower(Index set, Index way) const = 0;

  virtual void printStats(ostream& out)  const = 0;
  
  

  /* get the time of the last access */
  Time getLastAccess(Index set, Index way);
  
    mutable Histogram  m_histoSpace[2];
	  unsigned char *m_nReused;

	uint whatSubSet(L2Cache_Entry *a) const;
	uint whatSubSet(L1Cache_Entry *a) const;
	


 protected:
  unsigned int m_num_sets;       /** total number of sets */
  unsigned int m_assoc;          /** set associativity */
  Time **m_last_ref_ptr;         /** timestamp of last reference */
  
   //stats
  uint64 m_select[3];

};
 

inline 
AbstractReplacementPolicy::AbstractReplacementPolicy(Index num_sets, Index assoc)
{
  m_num_sets = num_sets;
  m_assoc = assoc;
  m_last_ref_ptr = new Time*[m_num_sets];
  m_nReused = new unsigned char[m_num_sets];
  for(unsigned int i = 0; i < m_num_sets; i++){
    m_nReused[i]=0;
    m_last_ref_ptr[i] = new Time[m_assoc];
    for(unsigned int j = 0; j < m_assoc; j++){
      m_last_ref_ptr[i][j] = 0;
    }
  }
}

inline
AbstractReplacementPolicy::~AbstractReplacementPolicy()
{
  if(m_last_ref_ptr != NULL){
    for(unsigned int i = 0; i < m_num_sets; i++){
      if(m_last_ref_ptr[i] != NULL){
        delete[] m_last_ref_ptr[i];
      }
    }
    delete[] m_last_ref_ptr;
  }
}

inline
Time AbstractReplacementPolicy::getLastAccess(Index set, Index way)
{
  return m_last_ref_ptr[set][way];
}

inline
uint AbstractReplacementPolicy::whatSubSet(L2Cache_Entry *a) const
{
  if(a->m_Sharers.count()==0 && !a->m_reused) return 0;
  if(a->m_Sharers.count()==0 && a->m_reused) return 1;
  if(a->m_Sharers.count()!=0) return 2;
  
  assert(0);
  return -1;
}

inline
uint AbstractReplacementPolicy::whatSubSet(L1Cache_Entry *a) const
{

  return -1;
}
#endif // ABSTRACTREPLACEMENTPOLICY_H
