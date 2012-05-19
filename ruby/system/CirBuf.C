#include "RequestMsg.h"
#include "CirBuf.h"
#include "MessageBuffer.h"


CirBuf::CirBuf (AbstractChip* ac, int tam, int version) {
	array.setSize(tam);
	
	m_TAM = tam;
	m_version = version;
	first = 0;
	next = 0;
	size=0;
	top=0;
	
	m_chip_ptr = ac;
	
	for(int i=0; i < tam; i++) {
		array[i].valid = false;
		array[i].reused = false;
	}
	
	m_histoFIFOReuse = new Histogram(1,100);
	
	cerr << "Fuera de CirBuf::CirBuf" << endl;
}

bool CirBuf::isPresent(Address a) {
	for(int i=0;i<m_TAM;i++) if(array[i].addr==a) return true;  
	return false;
}

bool CirBuf::empty () {
	return size==0;
	return first == next && size==0;
}

bool CirBuf::full () {
	return size==m_TAM;
	return first == next && size==m_TAM;
}

uint CirBuf::insert (Address addr) {

// 	if(isPresent(addr)) {
// 		cerr << addr << endl;
// 		assert(0);
// 	}
	
	int reused=-1; //to control de number of "free-lookups", We are looking up the replacement state of the line
	//without accounting its cost

// Version that skips lines with the replacement policy NRR bit set	
/*	do {
		top = top+1<m_TAM ? top+1 : 0;  // (top++) mod TAMBUF 
		reused++;
	} while(array[top].valid && reused!=g_BLOCKS_FIFO && (m_chip_ptr->isBlockNRU(array[top].addr))  ); //while((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[l2]))).lookup(array[top].addr)).m_NRU && array[top].valid);
*/

// Version that skips lines with the FIFO reused bit set	
	bool auxReused;
	do {
		top = top+1<m_TAM ? top+1 : 0;  // (top++) mod TAMBUF 
		reused++;						//count how many have been skipped
		auxReused = array[top].reused;  //keep the result for the loop condition
		array[top].reused = false;		
	} while(array[top].valid && auxReused && reused!=g_BLOCKS_FIFO ); //while((((*(m_chip_ptr->m_L2Cache_L2cacheMemory_vec[l2]))).lookup(array[top].addr)).m_NRU && array[top].valid);

	m_histoFIFOReuse->add(reused);
	
	//if(reused>0) cerr << "we have looked up " << reused << " lines for free" << endl;
	
	//  replacement notification to the L3 controller, the protocol has to change to a "without-data" state 
	if(array[top].valid) {
		
		RequestMsg out_msg;      
		(out_msg).m_Address = array[top].addr;
		(out_msg).m_Type = CoherenceRequestType_DATA_REPL;
		m_chip_ptr->m_L2Cache_dataArrayReplQueue_vec[m_version]->enqueue(out_msg); 
	} else {
		array[top].valid =  true;
		size++;
	}
	
	array[top].addr = addr;
	array[top].reused = false;
		
	return top;
}



void CirBuf::remove (Address addr) {
	for(int i=0;i<m_TAM;i++) if(array[i].addr == addr) array[i].valid = false;
	size--;
} 

void CirBuf::remove (uint pos) {
	array[pos].valid = false;
	size--;
}

void CirBuf::setReuse (Address addr){
	for(int i=0;i<m_TAM;i++) if(array[i].addr == addr) array[i].reused = true;
}

void CirBuf::setReuse (uint pos){
	//cerr << "Un puto acierto" << endl;
	array[pos].reused = true;
}

Address CirBuf::getData(uint pos) {
	assert(array[pos].valid);
	return array[pos].addr;
} 

Address CirBuf::getData(Address addr) {
	for(int i=0;i<m_TAM;i++) 
		if(array[i].addr == addr) {
			assert(array[i].valid);
			return array[i].addr;
		}
} 

void CirBuf::printStats() {
	cerr << "FIFO reuse: " << *m_histoFIFOReuse << endl;
}