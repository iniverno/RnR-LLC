// *******************************************************************************
// Multi-level PDFCM Adaptive Prefetching
// based on Performance Gradient Tracking
// DELUXE RELEASE
// Ramos, Briz, Ibanez, Vinals
// *******************************************************************************
#ifndef SAMPLE_PREFETCHER_H
#define SAMPLE_PREFETCHER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// *******************************************************************************
//			PDFCM (L2 Prefetcher)
// *******************************************************************************
// History Table (HT) and Delta Table (DT)
#define PDFCM_HT_bits (8)
#define PDFCM_HT_size (1 << PDFCM_HT_bits)
#define PDFCM_HT_mask (PDFCM_HT_size - 1)
#define PDFCM_DT_bits (9)
#define PDFCM_DT_size (1 << PDFCM_DT_bits)
#define PDFCM_DT_mask (PDFCM_DT_size - 1)

   typedef struct PDFCM_HT_entry PDFCM_HT_entry;
    struct PDFCM_HT_entry { 
      unsigned short PC;		// address of the memory access instruction			(16 bits)
      unsigned short last_addr;		// last address that missed the cache				(16 bits)
      unsigned short history;		// hashed history of deltas					(9 bits)
      char count;			// Confidence counter						(2 bits)
   };
   PDFCM_HT_entry * PDFCM_HT; 		//								(256 * 43 = 10,75 Kbits)

   typedef struct PDFCM_DT_entry PDFCM_DT_entry;
    struct PDFCM_DT_entry {
      short delta;			// delta between consecutive addresses				(16 bits)
   };
   PDFCM_DT_entry * PDFCM_DT; 		//								(512 * 16 = 8 Kbits)

   void PDFCM_ini (void);
   ADDRINT PDFCM_update_and_predict (ADDRINT pc, ADDRINT addr, unsigned short *history);		// updates HT & DT and predicts the next address that is going to miss
   ADDRINT PDFCM_predict_next (ADDRINT addr, unsigned short *history, unsigned short last_addr);	// used by the PDA to predict the next addresses
   unsigned short PDFCM_hash (unsigned short old_history, short delta);					// calculates the new hashed history of deltas
   void PDFCM_cycle(COUNTER cycle, PrefetchData_t *L2Data);
     
// PDFCM Degree Automaton (PDA)
   unsigned short PDA_history;
   ADDRINT PDA_addr;
   unsigned short PDA_last_addr;
   char PDA_degree=0;


// *******************************************************************************
//			SEQT (L2 Prefetcher)
// *******************************************************************************
   void SEQT_cycle(COUNTER cycle, PrefetchData_t *L2Data);
      
// SEQT Degree Automaton (SDA)
   ADDRINT SDA_last_addr;
   char SDA_degree=0;
      

// *******************************************************************************
//			SEQTL1 (L1 Prefetcher)
// *******************************************************************************
   void SEQTL1_cycle(COUNTER cycle, PrefetchData_t *L1Data);

// SEQT L1 Degree Automaton (SDA1)
   ADDRINT SDA1_last_addr;
   char SDA1_degree=0;

// *******************************************************************************
//			MSHRs
// *******************************************************************************
   typedef struct MSHR_entry MSHR_entry;
    struct MSHR_entry {
      ADDRINT addr;
      char valid;
   };
   typedef struct MSHR MSHR;
    struct MSHR{
      int size;
      int tail;
      int num;
      int head;
      MSHR_entry entry[32];
   };
   MSHR * PMAF1;
   MSHR * MSHRD2;
   MSHR * PMAF2;

   void MSHR_ini (void);
   int MSHR_lookup (MSHR * MSHR, COUNTER cycle, ADDRINT addr); 	// if hit it returns 1
   void MSHR_insert (MSHR * MSHR, COUNTER cycle, ADDRINT addr);	// if full, the oldest entry is deleted
   void MSHR_cycle (COUNTER cycle);				// it deletes the oldest entry if it hits on the cache (using GetPrefetchBit)

// *******************************************************************************
//			ADAPTIVE DEGREE (L2)
// *******************************************************************************
   unsigned int AD_cycles=0;
   COUNTER AD_L1_accesses=0;
   COUNTER AD_last_L1_accesses=0;
#define AD_interval (64*1024)
#define AD_MAX_INDEX (13) 	// number of different degrees
   int AD_degs[AD_MAX_INDEX]={0,1,2,3,4,6,8,12,16,24,32,48,64};
   int AD_deg_index=4;
   int AD_degree=4;
   char AD_state=0; // 0: increasing degree;  1: decreasing degree

   void AD_cycle(COUNTER cycle, PrefetchData_t *L1Data);

#endif


