
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
 * CacheProfiler.C
 * 
 * Description: See CacheProfiler.h
 *
 * $Id$
 *
 */

#include "CacheProfiler.h"
#include "AccessTraceForAddress.h"
#include "PrioHeap.h"
#include "System.h"
#include "Profiler.h"
#include "Vector.h"

CacheProfiler::CacheProfiler(string description)
  : m_requestSize(-1)
{
  m_description = description;
  m_requestTypeVec_ptr = new Vector<int>;
  m_requestTypeVec_ptr->setSize(int(GenericRequestType_NUM));

//  m_misses=new vector<int64>;
 // m_misses_ratio=new vector <double>;
  //misses_per_instruction= new vector <double>;
  misses_per_instruction.setSize(RubyConfig::numberOfProcessors());
  // m_demand_misses= new vector <int64> ; 
  m_demand_misses.setSize(RubyConfig::numberOfProcessors());
  //m_prefetches= new vector <int64>; 
  m_prefetches.setSize(RubyConfig::numberOfProcessors());
  //m_sw_prefetches= new vector <int64>; 
  m_sw_prefetches.setSize(RubyConfig::numberOfProcessors());
  //m_hw_prefetches= new vector <int64>; 
  m_hw_prefetches.setSize(RubyConfig::numberOfProcessors());

//JORGE  
   //m_accesos_user= new vector <int64>; 
   m_accesos_user.setSize(RubyConfig::numberOfProcessors());
   
  //m_accesos_super= new vector <int64>; 
  m_accesos_super.setSize(RubyConfig::numberOfProcessors());
  m_misses_super.setSize(RubyConfig::numberOfProcessors());
  m_misses_user.setSize(RubyConfig::numberOfProcessors());
  
  //m_total_accesos= new vector <int64>; 
  m_total_accesos.setSize(RubyConfig::numberOfProcessors());
  
  m_l2_total_accesos.setSize(RubyConfig::numberOfProcessors());
  m_l15_total_accesos.setSize(RubyConfig::numberOfProcessors());
  
  //m_l2_accesos_user= new vector <int64>; 
  m_l15_accesos_user.setSize(RubyConfig::numberOfProcessors());
  m_l2_accesos_user.setSize(RubyConfig::numberOfProcessors());
  //m_l2_accesos_super= new vector <int64>; 
  m_l15_accesos_super.setSize(RubyConfig::numberOfProcessors());
  m_l2_accesos_super.setSize(RubyConfig::numberOfProcessors());
  //m_accesos_user_ratio= new vector <double>; 
  m_accesos_user_ratio.setSize(RubyConfig::numberOfProcessors());
  m_l15_accesos_user_ratio.setSize(RubyConfig::numberOfProcessors());
  m_l2_accesos_user_ratio.setSize(RubyConfig::numberOfProcessors());
  //m_accesos_super_ratio= new vector <double>; 
  m_accesos_super_ratio.setSize(RubyConfig::numberOfProcessors());
    m_l15_accesos_super_ratio.setSize(RubyConfig::numberOfProcessors());
    m_l2_accesos_super_ratio.setSize(RubyConfig::numberOfProcessors());
  
  m_loads_user.setSize(RubyConfig::numberOfProcessors());
  m_loads_super.setSize(RubyConfig::numberOfProcessors());
  m_stores_user.setSize(RubyConfig::numberOfProcessors()); 
  m_stores_super.setSize(RubyConfig::numberOfProcessors());
  
  m_pref_inv.setSize(RubyConfig::numberOfProcessors());
  
  m_misses_ratio.setSize(RubyConfig::numberOfProcessors());
  m_l15_misses_ratio.setSize(RubyConfig::numberOfProcessors());
  m_l2_misses_ratio.setSize(RubyConfig::numberOfProcessors());
  m_misses_user.setSize(RubyConfig::numberOfProcessors());
  m_misses_super.setSize(RubyConfig::numberOfProcessors());
  m_miss_user_ratio.setSize(RubyConfig::numberOfProcessors());
   m_miss_super_ratio.setSize(RubyConfig::numberOfProcessors());
  
 m_misses.setSize(RubyConfig::numberOfProcessors());

   m_l2_misses_user.setSize(RubyConfig::numberOfProcessors());
   m_l2_misses_super.setSize(RubyConfig::numberOfProcessors());
   m_l2_miss_user_ratio.setSize(RubyConfig::numberOfProcessors());
   m_l2_miss_super_ratio.setSize(RubyConfig::numberOfProcessors());
 m_l2_total_accesos.setSize(RubyConfig::numberOfProcessors());
  
  m_l15_misses_user.setSize(RubyConfig::numberOfProcessors());
  m_l15_misses_super.setSize(RubyConfig::numberOfProcessors());
   m_l15_miss_user_ratio.setSize(RubyConfig::numberOfProcessors());
   m_l15_miss_super_ratio.setSize(RubyConfig::numberOfProcessors());
 m_l15_total_accesos.setSize(RubyConfig::numberOfProcessors());
  clearStats();

}

CacheProfiler::~CacheProfiler()
{
  delete m_requestTypeVec_ptr;
}

void CacheProfiler::printStats(ostream& out) const
{
 

  out << m_description << " cache stats: " << endl;
  string description = "  " + m_description;



//calcula_ratios();
  out << description << "_total_accesos: " << m_total_accesos << endl;
  out << description << "_accesos_super:  " << m_accesos_super << endl;
   out << description << "_accesos_user:  " << m_accesos_user << endl;
  out << description << "_total_accesos_user_ratio: " << m_accesos_user_ratio  << endl;
  out << description << "_total_accesos_super_ratio: " << m_accesos_super_ratio << endl;

  out << description << "_total_misses: " << m_misses << endl;
  //calcula_ratios();
  out << description << "_total_miss_ratio: " << m_misses_ratio << endl;
  out << description << "_total_demand_misses: " << m_demand_misses << endl;
 
  //calcula_tipos_acceso(); 
 // out << description << "_miss_ratio_" << (AccessModeType) 0 << ":   " << (100.0 * m_accessModeTypeHistogram[0]) / m_accesos_super << "%" << endl;
   
 //out << description << "_miss_ratio_" << (AccessModeType) 1 << ":   " << (100.0 * m_accessModeTypeHistogram[1]) / m_accesos_user << "%" << endl;
     out << description << "_miss_ratio_" << (AccessModeType) 0 << ":   " << m_miss_super_ratio << "%" << endl;  
  out << description << "_miss_ratio_" << (AccessModeType) 1 << ":   " << m_miss_user_ratio << "%" << endl;  

 
 
 double trans_executed = double(g_system_ptr->getProfiler()->getTotalTransactionsExecuted());
  double inst_executed = double(g_system_ptr->getProfiler()->getTotalInstructionsExecuted());

//calcula_ratios();
  //out << description << "_misses_per_transaction: " <<  << endl;
  out << description << "_misses_per_instruction: " << misses_per_instruction << endl;
  out << description << "_pref_inv: " << m_pref_inv << endl;
  
 /* out << description << "_instructions_per_misses: ";
  if (m_misses > 0) {
    out << inst_executed / double(m_misses) << endl;
  } else {
    out << "NaN" << endl;
  }
  out << endl;
*/
  int requests = 0;

  for(int i=0; i<int(GenericRequestType_NUM); i++) {
    requests += m_requestTypeVec_ptr->ref(i);
  }
  
  assert(m_misses.sum() == requests);

/*
  if (requests > 0) {
    for(int i=0; i<int(GenericRequestType_NUM); i++){
      if (m_requestTypeVec_ptr->ref(i) > 0) {
        out << description << "_request_type_" << GenericRequestType_to_string(GenericRequestType(i)) << ":   "
            << (100.0 * double((m_requestTypeVec_ptr->ref(i)))) / double(requests)
            << "%" << endl;
      }
    }
    
    out << endl;
    
    for(int i=0; i<AccessModeType_NUM; i++){
      if (m_accessModeTypeHistogram[i] > 0) {
        out << description << "_access_mode_type_" << (AccessModeType) i << ":   " << m_accessModeTypeHistogram[i] 
            << "    " << (100.0 * m_accessModeTypeHistogram[i]) / requests << "%" << endl;
      }
    }
  }
*/

  out << endl;
 
 
  
}

void CacheProfiler::printStats15(ostream& out) const
{
 out << m_description << " cache stats: " << endl;
  string description = "  " + m_description;
 

//aux=m_l2_accesos_user + m_l2_accesos_super ;
  out << "Estadisticas de la L15: " << endl;
  out << description << "_total_accesos2:  " << m_l15_total_accesos << " @: "<< this << endl;
  out << description << "_accesos_super2:  " << m_l15_accesos_super << endl;
   out << description << "_accesos_user2:  " << m_l15_accesos_user << endl;
   out << description << "_misses:  " << m_misses << endl;
    //calcula_ratios();
    out << description << "_total_accesos_user_ratio2: " <<  m_l15_accesos_user_ratio << endl;
  out << description << "_total_accesos_super_ratio2: " <<  m_l15_accesos_super_ratio << endl;
  out << description << "_total_miss_ratio2: " << m_l15_misses_ratio << endl;
    //calcula_ratios();
//out << description << "_miss_ratio_" << (AccessModeType) 0 << ":   " << (100.0 * m_accessModeTypeHistogram[0]) / m_l2_accesos_super << "%" << endl;  
//  out << description << "_miss_ratio_" << (AccessModeType) 1 << ":   " << (100.0 * m_accessModeTypeHistogram[1]) / m_l2_accesos_user << "%" << endl;
   out << description << "_miss_ratio_" << (AccessModeType) 0 << "2:   " << m_l15_miss_super_ratio << "%" << endl;  
  out << description << "_miss_ratio_" << (AccessModeType) 1 << "2:   " << m_l15_miss_user_ratio << "%" << endl;  

  out << description << "_request_size: " << m_requestSize << endl;
  
}


void CacheProfiler::printStats2(ostream& out) const
{
 out << m_description << " cache stats: " << endl;
  string description = "  " + m_description;
 

//aux=m_l2_accesos_user + m_l2_accesos_super ;
  out << "Estadisticas de la L2: " << endl;
  out << description << "_total_accesos2:  " << m_l2_total_accesos << " @: "<< this << endl;
  out << description << "_accesos_super2:  " << m_l2_accesos_super << endl;
   out << description << "_accesos_user2:  " << m_l2_accesos_user << endl;
    //calcula_ratios();
    out << description << "_total_accesos_user_ratio2: " <<  m_l2_accesos_user_ratio << endl;
  out << description << "_total_accesos_super_ratio2: " <<  m_l2_accesos_super_ratio << endl;
  out << description << "_total_miss_ratio2: " << m_l2_misses_ratio << endl;
    //calcula_ratios();
//out << description << "_miss_ratio_" << (AccessModeType) 0 << ":   " << (100.0 * m_accessModeTypeHistogram[0]) / m_l2_accesos_super << "%" << endl;  
//  out << description << "_miss_ratio_" << (AccessModeType) 1 << ":   " << (100.0 * m_accessModeTypeHistogram[1]) / m_l2_accesos_user << "%" << endl;
   out << description << "_miss_ratio_" << (AccessModeType) 0 << "2:   " << m_l2_miss_super_ratio << "%" << endl;  
  out << description << "_miss_ratio_" << (AccessModeType) 1 << "2:   " << m_l2_miss_user_ratio << "%" << endl; 
  
  Vector <float> MPKI;
  Vector <float> HPKI;
  MPKI.setSize(RubyConfig::numberOfProcessors());
  HPKI.setSize(RubyConfig::numberOfProcessors());

  for(int i=0; i<RubyConfig::numberOfProcessors(); i++) { 
    MPKI[i] = (double)m_misses[i] / g_system_ptr->getProfiler()->getTotalInstructionsExecuted(i) * 1000.0;
    HPKI[i] = (float)(m_l2_total_accesos[i] - m_misses[i]) / g_system_ptr->getProfiler()->getTotalInstructionsExecuted(i) * 1000.0;
  }
  
  out << description << "_MPKI"  << "2:   " << MPKI << endl;
  out << description << "_HPKI"  << "2:   " << HPKI  << endl;

  out << description << "_request_size: " << m_requestSize << endl;

if(g_PREFETCHER)
{
  out << "======================================" << endl << "PREFETCH STATS" << endl;
  for(int i=0; i<RubyConfig::numberOfL2CachePerChip(); i++)
    g_system_ptr->getPrefetcher(i)->printStats(out);
  out << endl;
}  
  
  out << "======================================" << endl<< "DRAM STATS" << endl;
  //para cada modulo de DRAM
  for(int i=0; i<RubyConfig::numberOfMemories(); i++)
     g_system_ptr->getDram(i)->printStats(out);
}

void CacheProfiler::calculaRatios()
{
int i;

cout << "procesors: " << RubyConfig::numberOfProcessors() << endl;
  for(i=0;  i<RubyConfig::numberOfProcessors(); i++)
  {
    m_l2_total_accesos[i]=  m_l2_accesos_user[i] +  m_l2_accesos_super[i];
    m_l15_total_accesos[i]=  m_l15_accesos_user[i] +  m_l15_accesos_super[i];
  
    m_total_accesos[i]=  m_accesos_user[i] +  m_accesos_super[i];
    
    if(m_l2_total_accesos[i]!=0)
    {
    m_l2_accesos_user_ratio[i]= (double)m_l2_accesos_user[i]/m_l2_total_accesos[i];
    }
    
    if(m_l15_total_accesos[i]!=0)
    {
    m_l15_accesos_user_ratio[i]= (double)m_l15_accesos_user[i]/m_l15_total_accesos[i];
    }
    
     if(m_total_accesos[i]!=0)
    m_accesos_user_ratio[i]= (double)m_accesos_user[i]/m_total_accesos[i];
    
     if(m_total_accesos[i]!=0)
    m_accesos_super_ratio[i]= (double)m_accesos_super[i]/m_total_accesos[i];
    
     if(m_l15_total_accesos[i]!=0)
    m_l15_accesos_super_ratio[i]= (double)m_l15_accesos_super[i]/m_l15_total_accesos[i];
    
     if(m_l2_total_accesos[i]!=0)
    m_l2_accesos_super_ratio[i]= (double)m_l2_accesos_super[i]/m_l2_total_accesos[i];
    
    
    if(m_total_accesos[i]!=0)
    m_misses_ratio[i]= (double)m_misses[i]/m_total_accesos[i];
    
    
    if(m_l15_total_accesos[i])
    m_l15_misses_ratio[i]= (double)m_misses[i]/m_l15_total_accesos[i];
    
    if(m_l2_total_accesos[i])
    m_l2_misses_ratio[i]= (double)m_misses[i]/m_l2_total_accesos[i];
    
    if(m_accesos_user[i]!=0)
      m_miss_user_ratio[i]=(double)m_misses_user[i]/m_accesos_user[i];
    if(m_accesos_super[i]!=0)
      m_miss_super_ratio[i]=(double)m_misses_super[i]/m_accesos_super[i];
    
    if(m_l15_accesos_user[i]!=0)
      m_l15_miss_user_ratio[i]=(double)m_misses_user[i]/m_l15_accesos_user[i];
    if(m_l15_accesos_super[i]!=0)
      m_l15_miss_super_ratio[i]=(double)m_misses_super[i]/m_l15_accesos_super[i];
      
      if(m_l2_accesos_user[i]!=0)
      m_l2_miss_user_ratio[i]=(double)m_misses_user[i]/m_l2_accesos_user[i];
    if(m_l2_accesos_super[i]!=0)
      m_l2_miss_super_ratio[i]=(double)m_misses_super[i]/m_l2_accesos_super[i];
  }
}
void CacheProfiler::clearStats()
{
  for(int i=0; i<int(GenericRequestType_NUM); i++) {
    m_requestTypeVec_ptr->ref(i) = 0;
  }
 

for(int i=0; i<RubyConfig::numberOfProcessors(); i++)
{
 misses_per_instruction[i]=0;
 
 m_misses[i] = 0;
 
  m_demand_misses[i] = 0;
 
  m_prefetches[i] = 0;
 
  m_sw_prefetches [i]= 0;
 
  m_hw_prefetches[i] = 0;
 
  m_accesos_user[i]=0;
 
  m_accesos_super[i]=0;
 
  m_misses_ratio[i]=0;
 
   m_total_accesos[i]=0;
   m_l15_total_accesos[i]=0;
    m_l2_total_accesos[i]=0;
 
 m_l15_accesos_user[i]=0;
 m_l2_accesos_user[i]=0;
 
m_l15_accesos_super[i]=0;
m_l2_accesos_super[i]=0;

m_loads_user[i]=0;
m_loads_super[i]=0;
m_stores_user[i]=0;
m_stores_super[i]=0;

m_pref_inv[i]=0;

m_misses_super[i]=0;
m_misses_user[i]=0;

m_l15_misses_super[i]=0;
m_l15_misses_user[i]=0;

m_l2_misses_super[i]=0;
m_l2_misses_user[i]=0;


}
for(int i=0; i<RubyConfig::numberOfL2CachePerChip(); i++)
  if(g_PREFETCHER)
    if(g_system_ptr)
      if(g_system_ptr->getPrefetcher(i))
        if(i<RubyConfig::numberOfL2CachePerChip()) g_system_ptr->getPrefetcher(i)->clearStats();

 //JORGE
  //limpiamos los datos en el prebuscador

  for(int i=0; i<AccessModeType_NUM; i++){
    m_accessModeTypeHistogram[i] = 0;
  }
}

void CacheProfiler::addStatSample(GenericRequestType requestType, AccessModeType type, int msgSize, PrefetchBit pfBit, NodeID id)
{
  m_misses[id]++;
  
  if(type==AccessModeType_SupervisorMode)
    m_misses_super[id]++;
  else if(type==AccessModeType_UserMode)
    m_misses_user[id]++;
    
  m_requestTypeVec_ptr->ref(requestType)++;

  m_accessModeTypeHistogram[type]++;
  m_requestSize.add(msgSize);
  if (pfBit == PrefetchBit_No) {
    m_demand_misses[id]++;
  } else if (pfBit == PrefetchBit_Yes) {
    m_prefetches[id]++;
    m_sw_prefetches[id]++;
  } else { // must be L1_HW || L2_HW prefetch
    m_prefetches[id]++;
    m_hw_prefetches[id]++;
  } 
}

//******************************************************
//Son llamadas por add*Acceso de la clase Profiler para cada acceso a la cache
//******************************************************

void CacheProfiler::addAcceso(GenericRequestType requestType, AccessModeType type, int msgSize, PrefetchBit pfBit, NodeID id, bool cache15)
{
	if(!cache15)
	{
	  if (type == AccessModeType_SupervisorMode) {
		m_accesos_super[id]++;
		if(requestType==GenericRequestType_ST)
		  m_stores_super[id]++;
		else if(requestType==GenericRequestType_LD)
		  m_loads_super[id]++;
		  
	  } else {
	   m_accesos_user[id]++;
	   if(requestType==GenericRequestType_ST)
		  m_stores_user[id]++;
		else if(requestType==GenericRequestType_LD)
		  m_loads_user[id]++;
	   }
	 } 
	 else
	{
	  /*if (type == AccessModeType_SupervisorMode) {
		m_l15_accesos_super[id]++;
		if(requestType==GenericRequestType_ST)
		  m_l15_stores_super[id]++;
		else if(requestType==GenericRequestType_LD)
		  m_l15_loads_super[id]++;
		  
	  } else {
	   m_l15_accesos_user[id]++;
	   if(requestType==GenericRequestType_ST)
		  m_l15_stores_user[id]++;
		else if(requestType==GenericRequestType_LD)
		  m_l15_loads_user[id]++;
	   }*/
	   
	   if (type == AccessModeType_SupervisorMode) {
		m_l15_accesos_super[id]++;
		
		  
	  } else {
	   m_l15_accesos_user[id]++;
	   }
	   
	 }
}

void CacheProfiler::addL2Acceso(AccessModeType access_mode, NodeID id)
{ 
  if (access_mode == AccessModeType_SupervisorMode) {
 // cout << "ids: " << id << endl;
    m_l2_accesos_super[id]++;
  } else {
   // cout << "idu: " << id << endl;
     m_l2_accesos_user[id]++;
  }
}

void CacheProfiler::addPrefInv(int id)
{ 
  m_pref_inv[id]++;
}

int64 CacheProfiler::getAccesos()
{
  long int aux=0;
 // cout << "oi: " << m_accesos_user[0] << endl;
  for(int i=0; i<RubyConfig::numberOfProcessors(); i++)
  {
    
    aux+=m_l2_accesos_user[i] + m_l2_accesos_super[i];
  }
  
  return aux;
}