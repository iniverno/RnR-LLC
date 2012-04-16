/** \file SpecifiedGeneratorType.h
  * 
  * Auto generated C++ code started by symbols/Type.C:520
  */
#ifndef SpecifiedGeneratorType_H
#define SpecifiedGeneratorType_H

#include "Global.h"

/** \enum SpecifiedGeneratorType
  * \brief ...
  */
enum SpecifiedGeneratorType {
  SpecifiedGeneratorType_FIRST,
  SpecifiedGeneratorType_DetermGETXGenerator = SpecifiedGeneratorType_FIRST,  /**< deterministic GETX Tester */
  SpecifiedGeneratorType_DetermInvGenerator,  /**< deterministic all shared then invalidate Tester */
  SpecifiedGeneratorType_DetermSeriesGETSGenerator,  /**< deterministic Series of GETSs Tester for prefetcher tuning */
  SpecifiedGeneratorType_NUM
};
SpecifiedGeneratorType string_to_SpecifiedGeneratorType(const string& str);
string SpecifiedGeneratorType_to_string(const SpecifiedGeneratorType& obj);
SpecifiedGeneratorType &operator++( SpecifiedGeneratorType &e);
ostream& operator<<(ostream& out, const SpecifiedGeneratorType& obj);

#endif // SpecifiedGeneratorType_H
