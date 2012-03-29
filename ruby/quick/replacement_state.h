#ifndef REPL_STATE_H
#define REPL_STATE_H

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This file is distributed as part of the Cache Replacement Championship     //
// workshop held in conjunction with ISCA'2010.                               //
//                                                                            //
//                                                                            //
// Everyone is granted permission to copy, modify, and/or re-distribute       //
// this software.                                                             //
//                                                                            //
// Please contact Aamer Jaleel <ajaleel@gmail.com> should you have any        //
// questions                                                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


#include "Address.h"
#include "dip.h"


// Replacement State Per Cache Line
typedef struct
{
    unsigned int  LRUstackposition;

    // CONTESTANTS: Add extra state per cache line here
    unsigned int  RPV;

} LINE_STATE;

// The implementation for the cache replacement policy
class CACHE_REPLACEMENT_STATE
{

  private:
    unsigned int numsets;
    unsigned int assoc;
    unsigned int replPolicy;
    
    LINE_STATE   **repl;

    unsigned long int mytimer;  // tracks # of references to the cache

    // CONTESTANTS:  Add extra state for cache here
    DIP *rrip;

  public:

    // The constructor CAN NOT be changed
    CACHE_REPLACEMENT_STATE( unsigned int _sets, unsigned int _assoc, unsigned int _pol );

    int  GetVictimInSet( unsigned int setIndex );
    void   UpdateReplacementState( unsigned int setIndex, int updateWayID );

    void   SetReplacementPolicy( unsigned int _pol ) { replPolicy = _pol; } 
    void   IncrementTimer() { mytimer++; } 

    void   UpdateReplacementState( unsigned int setIndex, int updateWayID, 
                                   unsigned int tid, bool cacheHit );

    ostream&   PrintStats( ostream &out);

  private:
    
    void   InitReplacementState();

    int  Get_RRIP_Victim( unsigned int setIndex );
    void   UpdateRRIP( unsigned int tid, unsigned int setIndex, int updateWayID, bool cacheHit );


};

#endif
