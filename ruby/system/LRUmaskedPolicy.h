
#ifndef LRUmaskedPolicy_H
#define LRUmaskedPolicy_H

#include "AbstractReplacementPolicy.h"

/* Simple true LRU replacement policy */

class LRUmaskedPolicy : public AbstractReplacementPolicy {
	unsigned int** m_matrix;
	bool* m_mask;
 public:

  LRUmaskedPolicy(Index num_sets, Index assoc);
  ~LRUmaskedPolicy();

  void touch(Index set, Index way, Time time);
  Index getVictim(Index set) const;
};

inline
LRUmaskedPolicy::LRUmaskedPolicy(Index num_sets, Index assoc)
  : AbstractReplacementPolicy(num_sets, assoc)
{
	
	matrix=new int*[sets]
	for(int i=0;i<sets;i++)
		matrix[i]=new int[assoc];
		for(int j=0; j<assoc; j++)
			matrix[i][j]=0;
}

inline
LRUmaskedPolicy::~LRUmaskedPolicy()
{
}

inline 
void LRUmaskedPolicy::touch(Index set, Index index, Time time){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  //ponemos fila a 1 y la columna a 0  
  matrix[set][index]=0xffffffff;
  int aux=0xffffffff^(1<<index);
  for(int j=0; j<assoc; j++)  	
    matrix[set][j]&=aux;
}

inline
Index LRUmaskedPolicy::getVictim(Index set) const {
  //  assert(m_assoc != 0);
  Time time, smallest_time;
  Index smallest_index;

  smallest_index = 0;
  smallest_time = m_last_ref_ptr[set][0];

  for (unsigned int i=0; i < m_assoc; i++) {
    time = m_last_ref_ptr[set][i];
    //assert(m_cache[cacheSet][i].m_Permission != AccessPermission_NotPresent);

    if (time < smallest_time){
      smallest_index = i;
      smallest_time = time;
    }
  }

  //  DEBUG_EXPR(CACHE_COMP, MedPrio, cacheSet);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, smallest_index);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, m_cache[cacheSet][smallest_index]);
  //  DEBUG_EXPR(CACHE_COMP, MedPrio, *this);

  return smallest_index;
}

#endif // PSEUDOLRUBITS_H
