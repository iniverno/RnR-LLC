/** \file SearchMechanism.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef SearchMechanism_H
#define SearchMechanism_H

#include "Global.h"

/** \enum SearchMechanism
  * \brief ...
  */
enum SearchMechanism {
  SearchMechanism_FIRST,
  SearchMechanism_Perfect = SearchMechanism_FIRST,  /**<  */
  SearchMechanism_PartialTag,  /**<  */
  SearchMechanism_BloomFilter,  /**<  */
  SearchMechanism_Random,  /**<  */
  SearchMechanism_None,  /**<  */
  SearchMechanism_NUM
};
SearchMechanism string_to_SearchMechanism(const string& str);
string SearchMechanism_to_string(const SearchMechanism& obj);
SearchMechanism &operator++( SearchMechanism &e);
ostream& operator<<(ostream& out, const SearchMechanism& obj);

#endif // SearchMechanism_H
