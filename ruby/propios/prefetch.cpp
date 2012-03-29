// *******************************************************************************
// Multi-level PDFCM Adaptive Prefetching
// based on Performance Gradient Tracking
// DELUXE RELEASE
// Ramos, Briz, Ibanez, Vinals
// *******************************************************************************
#include "interface.h"  // Do NOT edit interface .h
#include "sample_prefetcher.h"

//
//  Function to initialize the prefetchers.  DO NOT change the prototype of this
//  function.  You can change the body of the function by calling your necessary
//  initialization functions.
//

    void InitPrefetchers() // DO NOT CHANGE THE PROTOTYPE
   {
    // INSERT YOUR CHANGES IN HERE
   
      PDFCM_ini();
      MSHR_ini();
   }


//
//  Function that is called every cycle to issue prefetches should the
//  prefetcher want to.  The arguments to the function are the current cycle,
//  the demand requests to L1 and L2 cache.  Again, DO NOT change the prototype of this
//  function.  You can change the body of the function by calling your necessary
//  routines to invoke your prefetcher.
//

// DO NOT CHANGE THE PROTOTYPE
    void IssuePrefetches( COUNTER cycle, PrefetchData_t *L1Data, PrefetchData_t * L2Data )
   {    
   
    // INSERT YOUR CHANGES IN HERE
     
      MSHR_cycle(cycle);
      AD_cycle(cycle, L1Data);
      SEQTL1_cycle(cycle, L1Data);
      PDFCM_cycle(cycle, L2Data);
      SEQT_cycle(cycle, L2Data);
   
   }


// *******************************************************************************
//			PDFCM (L2 Prefetcher)
// *******************************************************************************

    void PDFCM_ini (void){
      PDFCM_HT=(PDFCM_HT_entry *) calloc(PDFCM_HT_size, sizeof(PDFCM_HT_entry));
      PDFCM_DT=(PDFCM_DT_entry *) calloc(PDFCM_DT_size, sizeof(PDFCM_DT_entry));               
   }

#define MASK_16b (0xffff)
    ADDRINT PDFCM_update_and_predict (ADDRINT pc, ADDRINT addr, unsigned short *history){
      unsigned short new_last_addr;
      unsigned short new_history;
      short actual_delta, predicted_delta;
   
      // read PDFCM_HT entry
      unsigned int index = pc & PDFCM_HT_mask;
      unsigned short old_last_addr = PDFCM_HT[index].last_addr; 
      unsigned short old_history = PDFCM_HT[index].history; 
      char count = PDFCM_HT[index].count;
   
     
      if (PDFCM_HT[index].PC!=((pc>>PDFCM_HT_bits) & MASK_16b)){
         // if it's a new PC replace the entry
         PDFCM_HT[index].PC=((pc>>PDFCM_HT_bits) & MASK_16b);
         PDFCM_HT[index].history=0; 
         PDFCM_HT[index].last_addr=addr & MASK_16b; 
         PDFCM_HT[index].count=0;
         return 0;
      }
   
      // compute deltas & update confidence counter
      predicted_delta=PDFCM_DT[old_history].delta;
      actual_delta = (addr-old_last_addr) & MASK_16b;
      if (actual_delta==predicted_delta){
         if (count<3) count++;
      }
      else{ 
         if (count>0) count--;
      }
   
      // compute new history
      new_last_addr = addr & MASK_16b;
      *history   = new_history   = PDFCM_hash(old_history, actual_delta);
   
      // write PDFCM_HT entry
      PDFCM_HT[index].last_addr = new_last_addr;
      PDFCM_HT[index].history   = new_history;
      PDFCM_HT[index].count=count;
   
      // update PDFCM_DT entry
      PDFCM_DT[old_history].delta = actual_delta;
   
      // predict a new delta using the new history 
      if (count<2) 
         return 0;
      else 
         return addr + PDFCM_DT[new_history].delta;
   }

    ADDRINT PDFCM_predict_next (ADDRINT addr, unsigned short *history, unsigned short old_last_addr){
      short delta;
       
      // compute delta 
      delta = (addr-old_last_addr) & MASK_16b;
   
      // compute new history
      *history=PDFCM_hash(*history, delta);
   
      // predict a new delta using the new history         
      return addr + PDFCM_DT[*history].delta;
   }

    unsigned short PDFCM_hash (unsigned short old_history, short delta){
    // R5-->  R(16, 16, 16)  F(t, t, t)  S(10, 5, 0) ; (number of entries of PDFCM_DT = 2^t)
   
      unsigned short select, folded, shift;
      select = delta;
   
      for(folded=0; select;) {
         folded ^= select & PDFCM_DT_mask;  // fold t bits
         select= select >> PDFCM_DT_bits;
      }
      shift = (old_history << 5) & PDFCM_DT_mask;     // shift 5 bits   
      return shift ^ folded;
   }
 
    void PDFCM_cycle(COUNTER cycle, PrefetchData_t *L2Data){
   
      ADDRINT predicted_address;
      unsigned short history=PDA_history;
   
      // miss or "1st use" in L2? (considering only demand references)
      if (cycle == L2Data->LastRequestCycle && !L2Data->LastRequestPrefetch && ((L2Data->hit == 0  && !MSHR_lookup(MSHRD2, cycle, L2Data->DataAddr)) || GetPrefetchBit(1, L2Data->DataAddr)==1)  ){
      
      	 // update PDFCM tables, predict next missing address and get the new history
         predicted_address = PDFCM_update_and_predict(L2Data->LastRequestAddr, L2Data->DataAddr, &history); 
      
         if (AD_degree){
            // issue prefetch (if not filtered)
            if (predicted_address && predicted_address!=L2Data->DataAddr && GetPrefetchBit(1, predicted_address)==-1 ){
               if (!MSHR_lookup(PMAF2, cycle,predicted_address & 0xffff) && !MSHR_lookup(MSHRD2, cycle,predicted_address)){
                  IssueL2Prefetch(cycle,predicted_address);
                  MSHR_insert(PMAF2, cycle,predicted_address & 0xffff);
               }
            }
         
            if (predicted_address){
               // program PDA
               PDA_history=history;
               PDA_last_addr=L2Data->DataAddr & MASK_16b;
               PDA_addr=predicted_address;
               PDA_degree=AD_degree-1; 
            }
         }
      
      // else the PDA generates 1 prefetch per cycle
      } 
      else if (PDA_degree && PDA_history){
      
      	 // predict next missing address and get the new history
         predicted_address = PDFCM_predict_next(PDA_addr, &PDA_history, PDA_last_addr); 
      
      	 // issue prefetch (if not filtered)
         if (predicted_address && predicted_address!=PDA_addr && GetPrefetchBit(1, predicted_address)==-1 ){
            if (!MSHR_lookup(PMAF2, cycle,predicted_address & 0xffff) && !MSHR_lookup(MSHRD2, cycle,predicted_address)){
               IssueL2Prefetch(cycle,predicted_address);
               MSHR_insert(PMAF2, cycle,predicted_address & 0xffff);
            }
         }
      	 // program PDA
         PDA_last_addr=PDA_addr & MASK_16b;
         PDA_addr=predicted_address;
         PDA_degree--;
      }
   }

// *******************************************************************************
//			SEQT (L2 Prefetcher)
// *******************************************************************************

    void SEQT_cycle(COUNTER cycle, PrefetchData_t *L2Data){
     
      // miss or "1st use" in L2? (considering demand and prefetch references)
      if (cycle == L2Data->LastRequestCycle && ((L2Data->hit == 0  && !MSHR_lookup(MSHRD2, cycle, L2Data->DataAddr)) || GetPrefetchBit(1, L2Data->DataAddr)==1)  ){
      
         if (L2Data->hit == 0)
            MSHR_insert(MSHRD2, cycle, L2Data->DataAddr);
         else 
            UnSetPrefetchBit(1, L2Data->DataAddr);
      
         if (AD_degree){
            // program SDA
            SDA_last_addr=L2Data->DataAddr;
            SDA_degree=AD_degree; 
         }
      }
   
      // the SDA generates 1 prefetch per cycle
      if (SDA_degree){
         ADDRINT predicted_address= SDA_last_addr+0x40; 
      
      	 // issue prefetch (if not filtered)
         if (GetPrefetchBit(1, predicted_address)==-1){
            if (!MSHR_lookup(PMAF2, cycle,predicted_address & 0xffff) && !MSHR_lookup(MSHRD2, cycle,predicted_address)){
               IssueL2Prefetch(cycle,predicted_address);
               MSHR_insert(PMAF2, cycle,predicted_address & 0xffff);
            }
         }
      	 // program SDA
         SDA_last_addr=predicted_address;
         SDA_degree--;
      }
   }

// *******************************************************************************
//			SEQTL1 (L1 Prefetcher)
// *******************************************************************************
    void SEQTL1_cycle(COUNTER cycle, PrefetchData_t *L1Data){
      int i;
      
      for (i=0; i<4; i++){
         // miss or "1st use" in L1?
         if (cycle == L1Data[i].LastRequestCycle && (L1Data[i].hit == 0 || GetPrefetchBit(0, L1Data[i].DataAddr)==1) ){
         
            if (L1Data[i].hit == 1){
               UnSetPrefetchBit(0, L1Data[i].DataAddr);
            }                                                       
         
            // program SDA1
            SDA1_last_addr=L1Data[i].DataAddr;
            SDA1_degree=(L1Data[i].hit == 0 ? 1 : 4 ); 
         } //end if
      } //end for
   
      // the SDA1 generates 1 prefetch per cycle
      if (SDA1_degree){
         ADDRINT predicted_address= SDA1_last_addr+0x40; 
         
      	 // issue prefetch (if not filtered)
         if (GetPrefetchBit(0, predicted_address)==-1){
            if (!MSHR_lookup(PMAF1, cycle,predicted_address & 0xffff)){       
               if (IssueL1Prefetch(cycle,predicted_address)==0){;
                  MSHR_insert(PMAF1, cycle,predicted_address & 0xffff);		 
               }
            }	 
         }
      	 // program next prefetch for the next cycle
         SDA1_last_addr=predicted_address;
         SDA1_degree--;
      }
   }


// *******************************************************************************
//			MSHR
// *******************************************************************************

    void MSHR_ini (void){
      PMAF1=(MSHR *) calloc(1, sizeof(MSHR));
      PMAF1->size=32;
      MSHRD2=(MSHR *) calloc(1, sizeof(MSHR));
      MSHRD2->size=16;
      PMAF2=(MSHR *) calloc(1, sizeof(MSHR));
      PMAF2->size=32;
   }
    int MSHR_lookup (MSHR * MSHR, COUNTER cycle, ADDRINT addr){
      int i;
      ADDRINT MASK = 0x3f; 
   
      if (!MSHR->size || !MSHR->num)
         return 0;
   
      for (i=0; i < MSHR->size; i++){
         if (MSHR->entry[i].valid && (MSHR->entry[i].addr == (addr & ~MASK)) ){
            return 1;
         }
      }
      return 0;
   }
    void MSHR_insert (MSHR * MSHR, COUNTER cycle, ADDRINT addr){
      ADDRINT MASK = 0x3f; 
   
      if (!MSHR->size || !addr)
         return;
   
      MSHR->entry[MSHR->tail].valid=1;
      MSHR->entry[MSHR->tail].addr= (addr & ~MASK);
      MSHR->tail=(MSHR->tail+1)%MSHR->size;
   
      if (MSHR->num<MSHR->size)
         MSHR->num++;
      else
         MSHR->head=MSHR->tail;
   }

    void MSHR_cycle (COUNTER cycle){
   
      if (PMAF1->num && (GetPrefetchBit(0, PMAF1->entry[PMAF1->head].addr)!= -1) ){
         PMAF1->num--;
         PMAF1->entry[PMAF1->head].valid=0;
         PMAF1->head=(PMAF1->head+1)%PMAF1->size;
      }
   
      if (MSHRD2->num && (GetPrefetchBit(1, MSHRD2->entry[MSHRD2->head].addr)!= -1) ){
         MSHRD2->num--;
         MSHRD2->entry[MSHRD2->head].valid=0;
         MSHRD2->head=(MSHRD2->head+1)%MSHRD2->size;
      }
   
      if (PMAF2->num && (GetPrefetchBit(0, PMAF2->entry[PMAF2->head].addr)!= -1) ){
         PMAF2->num--;
         PMAF2->entry[PMAF2->head].valid=0;
         PMAF2->head=(PMAF2->head+1)%PMAF2->size;
      }
   }

// *******************************************************************************
//			ADAPTIVE DEGREE (L2)
// *******************************************************************************

    void AD_cycle(COUNTER cycle, PrefetchData_t *L1Data){
      int i;
   
      AD_cycles++;
      for(i = 0; i < 4; i++) {
         if(cycle == L1Data[i].LastRequestCycle) 
            AD_L1_accesses++;
      }
      
      if (AD_cycles>AD_interval){
         AD_cycles=0;
         if (AD_L1_accesses<AD_last_L1_accesses){
            AD_state=!AD_state;
         }
         if (!AD_state) {
            if (AD_deg_index<AD_MAX_INDEX-1) AD_deg_index++; 
         } 
         else {
            if (AD_deg_index>0) AD_deg_index--; 
         }
         AD_degree=AD_degs[AD_deg_index];
         AD_last_L1_accesses=AD_L1_accesses;
         AD_L1_accesses=0;
      }
   }
