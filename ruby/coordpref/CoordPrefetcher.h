/*
    Copyright (C) 1999-2008 by Mark D. Hill and David A. Wood for the
    Wisconsin Multifacet Project.  Contact: gems@cs.wisc.edu
    http://www.cs.wisc.edu/gems/

    --------------------------------------------------------------------

    This file is part of the Ruby Multiprocessor Memory System Simulator, 
    a component of the Multifacet GEMS (General Execution-driven 
    Multiprocessor Simulator) software toolset originally developed at 
    the University of Wisconsin-Madison.

    Ruby was originally developed primarily by Milo Martin and Daniel
    Sorin with contributions from Ross Dickson, Carl Mauer, and Manoj
    Plakal.

    Substantial further development of Multifacet GEMS at the
    University of Wisconsin was performed by Alaa Alameldeen, Brad
    Beckmann, Jayaram Bobba, Ross Dickson, Dan Gibson, Pacia Harper,
    Derek Hower, Milo Martin, Michael Marty, Carl Mauer, Michelle Moravan,
    Kevin Moore, Andrew Phelps, Manoj Plakal, Daniel Sorin, Haris Volos, 
    Min Xu, and Luke Yen.
    --------------------------------------------------------------------

    If your use of this software contributes to a published paper, we
    request that you (1) cite our summary paper that appears on our
    website (http://www.cs.wisc.edu/gems/) and (2) e-mail a citation
    for your published paper to gems@cs.wisc.edu.

    If you redistribute derivatives of this software, we request that
    you notify us and either (1) ask people to register with us at our
    website (http://www.cs.wisc.edu/gems/) or (2) collect registration
    information and periodically send it to us.

    --------------------------------------------------------------------

    Multifacet GEMS is free software; you can redistribute it and/or
    modify it under the terms of version 2 of the GNU General Public
    License as published by the Free Software Foundation.

    Multifacet GEMS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the Multifacet GEMS; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307, USA

    The GNU General Public License is contained in the file LICENSE.

### END HEADER ###
*/

/*
   This file has been modified by Kevin Moore and Dan Nussbaum of the
   Scalable Systems Research Group at Sun Microsystems Laboratories
   (http://research.sun.com/scalable/) to support the Adaptive
   Transactional Memory Test Platform (ATMTP).

   Please send email to atmtp-interest@sun.com with feedback, questions, or
   to request future announcements about ATMTP.

   ----------------------------------------------------------------------

   File modification date: 2008-02-23

   ----------------------------------------------------------------------
*/

/*
 * Profiler.h
 * 
 * Description: 
 *
 * $Id$
 *
 */

#ifndef COORDPREFETCHER_H
#define COORDPREFETCHER_H

#include "Address.h"
#include "Global.h"
#include "GenericMachineType.h"
#include "RubyConfig.h"
#include "Histogram.h"
#include "Consumer.h"
#include "AccessModeType.h"
#include "AccessType.h"
#include "NodeID.h"
#include "MachineID.h"
#include "PrefetchBit.h"
#include "Address.h"
#include "Set.h"
#include "CacheRequestType.h"
#include "GenericRequestType.h"
#include "XactProfiler.h"
#include "Address.h"

#define NPROC 16

struct bloomFilterEntry
 { unsigned char bit;
   MachineID proc;
   bool valid;
 };
 
class CoordPrefetcher : public Consumer {
public:
  // Constructors
  CoordPrefetcher();

  // Destructor
  ~CoordPrefetcher();  
  
  // Public Methods
  void wakeup();
  void miss(Address addr, Address pc, int tipo, MachineID node, int firstUse);
  void print(ostream& out) const;
  void printStats(ostream& out);

  void bloom(int t, Address a, MachineID core, MachineID owner);

private:
  // Private Methods
  uint64 missesGlobalThisEpoch;
   
  //mecanismo Patt 
  bloomFilterEntry bloomFilter[NPROC][4096];
  
  Vector <int> BWC;
  Vector <int> BWNO;
  uint m_pol_this_epoch[NPROC];
  uint dec[NPROC];
  double ACC[NPROC];
  
  int bloomBitAddress(Address adrr);
  void evaluateMetrics();
  

};

// Output operator declaration
ostream& operator<<(ostream& out, const CoordPrefetcher& obj);

// ******************* Definitions *******************

// Output operator definition
extern inline 
ostream& operator<<(ostream& out, const CoordPrefetcher& obj)
{
 // obj.print(out);
  out << flush;
  return out;
}


#endif //PROFILER_H


