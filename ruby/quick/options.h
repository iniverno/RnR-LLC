#ifndef OPTIONS_H
#define OPTIoNS_H

/********************************************************************************
** Parameter for Re-Reference Interval Prediction (RRIP) [ISCA'2010]:
** ===================================================================
** 
** Change macro maxRPV below to simulate one of the following policies:
**
**     (a)  maxRPV=1 simulates Not Recently Used (NRU) replacement.
**          NRU is the policy commonly used in microprocessors today.
**
**     (b)  maxRPV=3 simulates Static RRIP (SRRIP) with max prediction of 3
**
**     (c)  maxRPV=7 simulates Static RRIP (SRRIP) with max prediction of 7
**
**
** Dynamic Insertion Policy (DIP) [ISCA'07 and PACT'08]:
** ======================================================
** 
** Change macro USE_INSERTION_POLICY below to choose one of the following policies:
**
**     (a)  USE_INSERTION_POLICY=0 simulates baseline policy where all newly
**          inserted blocks are moved to head of RRIP chain (i.e. MRU position)
**
**     (b)  USE_INSERTION_POLICY=1 simulates DIP where newly inserted blocks
**          are inserted either at head of RRIP chain or tail of RRIP chain. In
**          a shared cache, the policy decision is thread-unaware [ISCA'07]
**
**     (c)  USE_INSERTION_POLICY=2 simulates TADIP where newly inserted blocks
**          are inserted either at head of RRIP chain or tail of RRIP chain on a
**          per-thread basis. The policy decisions are thread-aware [PACT'08]
**
** Other DIP Parameters:
** =====================
**     
**     (a) USE_PSELwidth: The number of bits in the Policy Selection (PSEL) counter
**
**     (b) USE_SDMsize:   The number of sets sampled in a Set Dueling Monitor (SDM)
**
** IMPORTANT NOTES:
** =====================
**
** NOTE 1:  The DIP and TADIP papers illustrated a mechanism for using the 
** cache set index to identify SDMs.  To provide a generalized framework 
** where SDMs can be selected for any cache configuration, this source code release
** selects SDMs at random and store the SDM type in a separate data structure.
** However, note that this extra data structure is NOT required as described in the
** DIP and TADIP papers.
**
** NOTE 2:  DRRIP policy configuration is maxRPV > 1 and USE_INSERTION_POLICY=2 (TADIP)
**
********************************************************************************/

#define maxRPV                3     // Use SRRIP replacement

#define USE_INSERTION_POLICY  2     // Use TADIP
#define USE_PSELwidth         10    // Width of the PSEL counter
#define USE_SDMsize           32    // Use 32 sets per SDM

#endif
