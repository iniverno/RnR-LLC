/** \file Protocol.h
  * 
  * Auto generated C++ code started by symbols/Type.C:227
  */

#ifndef Protocol_H
#define Protocol_H

#include "Global.h"
#include "Allocator.h"
#include "AbstractProtocol.h"
class Protocol :  public AbstractProtocol {
public:
  Protocol() 
  : AbstractProtocol()
  {
  }
  ~Protocol() { };
  void print(ostream& out) const;
//private:
  static const bool m_TwoLevelCache = (true) ;
  static const bool m_CMP = (true) ;
};
// Output operator declaration
ostream& operator<<(ostream& out, const Protocol& obj);

// Output operator definition
extern inline
ostream& operator<<(ostream& out, const Protocol& obj)
{
  obj.print(out);
  out << flush;
  return out;
}

#endif // Protocol_H
