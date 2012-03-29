
#ifndef PseudoLRUPolicy2_H
#define PseudoLRUPolicy2_H

#include "AbstractReplacementPolicy.h"

/**
 * Implementation of tree-based pseudo-LRU replacement
 *
 * Works for any associativity between 1 and 128.  
 *
 * Also implements associativities that are not a power of 2 by
 * ignoring paths that lead to a larger index (i.e. truncating the
 * tree).  Note that when this occurs, the algorithm becomes less
 * fair, as it will favor indicies in the larger (by index) half of
 * the associative set. This is most unfair when the nearest power of
 * 2 is one below the associativy, and most fair when it is one above.
 */

class PseudoLRUPolicy2 : public AbstractReplacementPolicy {
 public:

  PseudoLRUPolicy2(Index num_sets, Index assoc);
  ~PseudoLRUPolicy2();

  void touch(Index set, Index way, Time time, uint proc);
  Index getVictim(Index set, uint proc) const;
  void replacementLower(Index set, Index way) const;
  void printStats(ostream& out) const;
 private:
  unsigned int m_effective_assoc;    /** nearest (to ceiling) power of 2 */
  unsigned int m_num_levels;         /** number of levels in the tree */
  uint64* m_trees;                   /** bit representation of the trees, one for each set */
  

};


inline void PseudoLRUPolicy2::replacementLower(Index set, Index way) const {}


inline
PseudoLRUPolicy2::PseudoLRUPolicy2(Index num_sets, Index assoc)
  : AbstractReplacementPolicy(num_sets, assoc)
{  
  int num_tree_nodes;

  // associativity cannot exceed capacity of tree representation
  assert(num_sets > 0 && assoc > 1 && assoc <= (Index) sizeof(uint64)*4);

  m_trees = NULL;
  m_num_levels = 0;

  m_effective_assoc = 1;
  while(m_effective_assoc < assoc){
    m_effective_assoc <<= 1;  // effective associativity is ceiling power of 2
  }
  assoc = m_effective_assoc;
  while(true){
    assoc /= 2;
    if(!assoc) break;
    m_num_levels++;
  }
  assert(m_num_levels < sizeof(unsigned int)*4);
  num_tree_nodes = ((int)pow(2, m_num_levels))-1;
  m_trees = new uint64[m_num_sets];
  for(unsigned int i=0; i< m_num_sets; i++){
    m_trees[i] = 0;
  }
}

inline
PseudoLRUPolicy2::~PseudoLRUPolicy2()
{
  if(m_trees != NULL)
    delete[] m_trees;
}

inline 
void PseudoLRUPolicy2::touch(Index set, Index index, Time time, uint proc){
  assert(index >= 0 && index < m_assoc);
  assert(set >= 0 && set < m_num_sets);

  int tree_index = 0;
  int node_val;
  for(int i=m_num_levels -1; i>=0; i--){
    node_val = (index >> i)&1;
    if(node_val)
      m_trees[set] |= node_val << tree_index;
    else
      m_trees[set] &= ~(1 << tree_index);
    tree_index = node_val ? (tree_index*2)+2 : (tree_index*2)+1;
  }
  if(time) m_last_ref_ptr[set][index] = time;
  else m_last_ref_ptr[set][index] = g_eventQueue_ptr->getTime();
  
}

inline
Index PseudoLRUPolicy2::getVictim(Index set, uint proc) const {
  //  assert(m_assoc != 0);

  Index index = 0;
  
  int tree_index = 0;
  int node_val;
  for(unsigned int i=0;i<m_num_levels;i++){
    node_val = (m_trees[set]>>tree_index)&1;
    index += node_val?0:(m_effective_assoc >> (i+1));
    tree_index = node_val? (tree_index*2)+1 : (tree_index*2)+2;
  }
  assert(index >= 0 && index < m_effective_assoc);

  /* return either the found index or the max possible index */
  /* NOTE: this is not a fair replacement when assoc is not a power of 2 */
  return (index > (m_assoc-1)) ? m_assoc-1:index; 
}

inline
void PseudoLRUPolicy2::printStats(ostream& out) const
{
  //out << "select: " << select[0] << "\t"  << select[1] << "\t"  << select[2] << endl; 

}
#endif // PseudoLRUPolicy2_H
