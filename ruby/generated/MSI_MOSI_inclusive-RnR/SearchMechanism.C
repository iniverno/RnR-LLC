/** \file SearchMechanism.h
  * 
  * Auto generated C++ code started by symbols/Type.C:601
  */

#include "SearchMechanism.h"

ostream& operator<<(ostream& out, const SearchMechanism& obj)
{
  out << SearchMechanism_to_string(obj);
  out << flush;
  return out;
}

string SearchMechanism_to_string(const SearchMechanism& obj)
{
  switch(obj) {
  case SearchMechanism_Perfect:
    return "Perfect";
  case SearchMechanism_PartialTag:
    return "PartialTag";
  case SearchMechanism_BloomFilter:
    return "BloomFilter";
  case SearchMechanism_Random:
    return "Random";
  case SearchMechanism_None:
    return "None";
  default:
    ERROR_MSG("Invalid range for type SearchMechanism");
    return "";
  }
}

SearchMechanism string_to_SearchMechanism(const string& str)
{
  if (false) {
  } else if (str == "Perfect") {
    return SearchMechanism_Perfect;
  } else if (str == "PartialTag") {
    return SearchMechanism_PartialTag;
  } else if (str == "BloomFilter") {
    return SearchMechanism_BloomFilter;
  } else if (str == "Random") {
    return SearchMechanism_Random;
  } else if (str == "None") {
    return SearchMechanism_None;
  } else {
    WARN_EXPR(str);
    ERROR_MSG("Invalid string conversion for type SearchMechanism");
  }
}

SearchMechanism& operator++( SearchMechanism& e) {
  assert(e < SearchMechanism_NUM);
  return e = SearchMechanism(e+1);
}
