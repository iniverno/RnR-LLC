/*
    Copyright (C) 1999-2008 by Mark D. Hill and David A. Wood for the
    Wisconsin Multifacet Project.  Contact: gems@cs.wisc.edu
    http://www.cs.wisc.edu/gems/

    --------------------------------------------------------------------

    This file is part of the Opal Timing-First Microarchitectural
    Simulator, a component of the Multifacet GEMS (General 
    Execution-driven Multiprocessor Simulator) software toolset 
    originally developed at the University of Wisconsin-Madison.

    Opal was originally developed by Carl Mauer based upon code by
    Craig Zilles.

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
 * FileName:  cache.C
 * Synopsis:  
 * Author:    zilles
 * Version:   $Id: cache.C 1.47 05/08/14 17:07:09-05:00 lyen@opus.cs.wisc.edu $
 */

/*------------------------------------------------------------------------*/
/* Includes                                                               */
/*------------------------------------------------------------------------*/

#include "hfa.h"
// need scheduler for timing reasons --> needs dynamic inst ...
#include "hfacore.h"
#include "bitlib.h"
#include "confio.h"
#include "cache.h"

/*------------------------------------------------------------------------*/
/* Macro declarations                                                     */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/* Variable declarations                                                  */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/* Forward declarations                                                   */
/*------------------------------------------------------------------------*/

// C++ Template: explicit instantiation
template class generic_cache_template<generic_cache_block_t>;

/*------------------------------------------------------------------------*/
/* Generic Cache                                                          */
/*------------------------------------------------------------------------*/

//**************************************************************************
cache_t::cache_t(const char *n, mshr_t *m, scheduler_t *eventQueue) {
  name = n;
  mshr = m;
  m_eventQueue = eventQueue;

  /* initialize stats to zeros */
  reads = 0;
  read_hit = 0;
  read_miss = 0;
  writes = 0;
  write_hit = 0;
  write_miss = 0;
  write_prefetches = 0;
  replacements = 0;
  writebacks = 0;
}

//**************************************************************************
void cache_t::printStats( pseq_t *pseq )
{
  pseq->out_info("\n" );
  pseq->out_info("  %s %-50.50s: %8llu\n", name,
                 "total number of reads:", reads );
  pseq->out_info("  %s %-50.50s: %8llu\n", name,
                 "total number of read hits:", read_hit );
  pseq->out_info("  %s %-50.50s: %8llu\n", name,
                 "total number of read misses:", read_miss );
  
  pseq->out_info("  %s %-50.50s: %8llu\n", name,
                 "total number of writes:", writes );
  pseq->out_info("  %s %-50.50s: %8llu\n", name,
                 "total number of write hits:", write_hit );
  pseq->out_info("  %s %-50.50s: %8llu\n", name,
                 "total number of write misses:", write_miss );
  
  pseq->out_info("  %s %-50.50s: %8llu\n", name,
                 "number of write prefetches:", write_prefetches);
  pseq->out_info("  %s %-50.50s: %8llu\n", name,
                 "total number of replacements:", replacements );
  pseq->out_info("  %s %-50.50s: %8llu\n", name,
                 "total number of writebacks:", writebacks );

  for(uint k=0; k <  CONFIG_LOGICAL_PER_PHY_PROC; ++k){
    pseq->out_info("  %s %-50.50s: %8.2f\n", name,
                 "demand miss per 1000 retired instructions [logical proc %d]:",
                 1000.0 * (read_miss+write_miss) / pseq->m_stat_committed[k],k );
  }
}

/*------------------------------------------------------------------------*/
/* LN cache                                                               */
/*------------------------------------------------------------------------*/

//**************************************************************************
#if 0
template <class BlockType>
generic_cache_template<BlockType>::generic_cache_template(const char *n, mshr_t *m,
    scheduler_t *eventQueue, uint32 _set_bits, uint32 assoc,
    uint32 _block_bits, bool ideal) :
  cache_t (n, m, eventQueue) {

  n_sets = (1 << _set_bits);
  set_bits = _set_bits;
  set_mask = n_sets - 1;
  block_size = (1 << _block_bits);
  block_bits = _block_bits;
  block_mask = block_size - 1;
  m_assoc = assoc;

  DEBUG_OUT("Ln constructor: block size: %dB, %dx assoc, %d sets.  %dB total\n",
            block_size, m_assoc, n_sets,
            block_size * m_assoc * n_sets );
#ifdef DEBUG_CACHE
  DEBUG_OUT("memop linesize %d 0x%0llx\n", 1 << DL1_BLOCK_BITS, MEMOP_BLOCK_MASK);
  DEBUG_OUT("%s: set_bits: %d (mask 0x%0x) block_bits: %d (mask 0x%0x)\n",
         name, set_bits, set_mask, block_bits, block_mask );
#endif

  /* allocate cache blocks and initialize all entries to zeroes */
  cache = (BlockType *) malloc( sizeof(BlockType) * n_sets * m_assoc );
  /* tag == 0, last_access == 0, prefetched == false, user_data == NULL */
  bzero((void *)cache, sizeof(BlockType) * n_sets * m_assoc);

  m_ideal = ideal;
}
#endif


/*------------------------------------------------------------------------*/
/* Accessor(s) / mutator(s)                                               */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/* Private methods                                                        */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/* Static methods                                                         */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/* Global functions                                                       */
/*------------------------------------------------------------------------*/
