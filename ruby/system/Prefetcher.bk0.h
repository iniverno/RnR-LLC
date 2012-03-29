
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
 * $Id: Sequencer.h 1.70 2006/09/27 14:56:41-05:00 bobba@s1-01.cs.wisc.edu $
 *
 * Description: 
 *
 */

#ifndef PREFETCHER_H
#define PREFETCHER_H

#include "Global.h"
#include "RubyConfig.h"
#include "Consumer.h"
#include "CacheRequestType.h"
#include "AccessModeType.h"
#include "GenericMachineType.h"
#include "PrefetchBit.h"
#include "Map.h"

class DataBlock;
class AbstractChip;
class CacheMsg;
class Address;
class MachineID;

#define PDFCM_HT_bits (14)
#define PDFCM_HT_size (1 << PDFCM_HT_bits)
#define PDFCM_HT_mask (PDFCM_HT_size - 1)
#define PDFCM_DT_bits (9)
#define PDFCM_DT_size (1 << PDFCM_DT_bits)
#define PDFCM_DT_mask (PDFCM_DT_size - 1)


   typedef struct PDFCM_HT_entry PDFCM_HT_entry;
    struct PDFCM_HT_entry { 
      Address PC;		// address of the memory access instruction
      Address last_addr;		// last address that missed the cache
      unsigned short history;		// hashed history of deltas
      char count;			// Confidence counter
      char tipo;
      char proc;
   };
   	//
   
   typedef struct PDFCM_DT_entry PDFCM_DT_entry;
    struct PDFCM_DT_entry {
      short delta;			// delta between consecutive addresses	
   };   

class Bufcir {
    public:

      Vector <Address> array;
  
      int first, next,size;

		bool esta(Address a) {
			for(int i=0;i<32;i++) if(array[i]==a) return true;
			return false;
		}
      Bufcir () {
          array.setSize (32);
          first = 0;
          next = 0;
          size=0;
      }

      bool empty () {
        return first == next && size==0;
      }
      
      bool full () {
        return first == next && size==32;
      }
      
      void insert (Address node) {
        if(++next >= 32) next=0;
        array[next] = node;
        size++;       
    }
	
     Address remove () {
      
         if(++first >= 32) first=0;
         size--;
        return array[first];
    } 
};


class Prefetcher : public Consumer {
public:
  // Constructors
  Prefetcher(AbstractChip* chip_ptr, int version);

  // Destructor
  ~Prefetcher();
  
  // Public Methods
  void wakeup(); // Used only for deadlock detection 

  void firstUse(Address addr, Address addr, int tipo);
  void miss(Address addr, Address addr, int tipo, MachineID node);
  void stats(int t);
  void printStats();
  void print(ostream& out) const;
  static void printConfig(ostream& out);
  
  

private:
  // Private Methods
 

  // Private copy constructor and assignment operator
 // Prefetcher(const Prefetcher& obj);
  //Prefetcher& operator=(const Prefetcher& obj);
  
  // Data Members (m_ prefix)
  AbstractChip* m_chip_ptr;

  Consumer* m_consumer_ptr;

  // indicates what processor on the chip this sequencer is associated with
  int m_version;

   long int numOfHits, numOfMisses;
      
   int m_metodo;
   int degrees[13];
   int degree_index;
   int degree_incr;
   long int next_stop;
   long int inst_ant_par;
   long int inst_ant_tot;
   
// SEQT Degree Automaton (SDA)
   Address m_last_addr;
   int m_stride;
   int m_st_degree;
   int m_st_base_degree;
   Address m_last_pc;
   
   //PDCFM
   // PDFCM Degree Automaton (PDA)
   unsigned short m_gen_history, m_pref_history;
   Address m_old_addr;
   Address m_gen_last_addr, m_pref_last_addr;
   
   int m_PDA_degree;
   int  m_PDA_base_degree;
   int m_flag_cabeza;
   MachineID m_node; //core que hace la petici—n
   
   PDFCM_HT_entry * PDFCM_HT; 	
   PDFCM_DT_entry * PDFCM_DT; 	
    
    
    //PDMFC methods
    
  unsigned short PDFCM_hash (unsigned short old_history, short delta);
  Address PDFCM_predict_next ();
  int PDFCM_update_and_predict ();
  
  //##########################
  // stats
  
  long m_sent_prefetches;
  
  long m_harmful_prefetches;
  long m_harmless_prefetches;
  
  long m_useful_prefetches;
  long m_useless_prefetches;
  
  long m_ext_harmful_prefetches;
  
  // array de contadores para la clasificaci—n de las prebœsquedas
  Vector <int64> cont;
  Bufcir buffer;
  
  int m_tipo;
};

// Output operator declaration
ostream& operator<<(ostream& out, const Prefetcher& obj);

// ******************* Definitions *******************

// Output operator definition
extern inline 
ostream& operator<<(ostream& out, const Prefetcher& obj)
{
  obj.print(out);
  out << flush;
  return out;
}



#endif //PREFETCHER_H

