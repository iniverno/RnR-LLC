#include "PageTableQuick.h"

#include "EventQueue.h"


#define NUMBER_REUSED_PAGES 64
#define ASSOC_REUSED_PAGES 4
#define BITS_SETS_REUSED_PAGES 4
#define NUM_SETS_REUSED_PAGES (1 << BITS_SETS_REUSED_PAGES)


PageTableQuick::PageTableQuick() {
	//m_table.setSize(1024);
	m_table = new PageEntryQuick* [NUM_SETS_REUSED_PAGES];
	for(uint i=0; i<NUM_SETS_REUSED_PAGES;i++)
		m_table[i]=new PageEntryQuick [ASSOC_REUSED_PAGES];
	
	m_hit_in_hit = 0;
	m_miss_in_hit = 0;
	
	m_hit_in_whatToDo = 0;
	m_miss_in_whatToDo = 0;
	
	m_0 = 0;
	m_1 = 0;
	
	m_hit_in_replaced = 0;
	m_miss_in_replaced = 0;
	
	m_true_isOnShadow = 0;
	m_false_isOnShadow = 0;
}

void PageTableQuick::hit(Address address, uint proc) {
	Address aux=Address(address);
	aux.onlyPageAddress();

	uint set = pageToTableSet(aux);
	uint loc = findTagInTableSet(aux, set);
	if(loc != -1) {
		m_hit_in_hit++;
		//m_table[set][loc].m_counter = (m_table[set][loc].m_counter > 3) ?  7 : m_table[set][loc].m_counter + 4;
		for(uint i=0;i<NUM_SETS_REUSED_PAGES; i++)
			for(uint j=0;j<ASSOC_REUSED_PAGES; j++) {
				PageEntryQuick &aa= m_table[i][j];
				if(m_table[set][loc].m_proc == aa.m_proc)
					aa.m_counter = (aa.m_counter > 3) ?  7 : aa.m_counter + 4;
			}
	} 
	else {
		m_miss_in_hit++;
		insertInSet(aux, set, true, proc);
	}
}


//Recibe @ completa
uint PageTableQuick::whatToDo(Address address, uint proc) const {
	Address aux=Address(address);
	aux.onlyPageAddress();

	uint set = pageToTableSet(aux);
	uint loc = findTagInTableSet(aux, set);
	if(loc != -1) {
		
		if(g_SHADOW_ON && isOnShadow(address, set, loc)) {
			//m_table[set][loc].m_counter = 7;
			//m_table[set][loc].m_counter = (m_table[set][loc].m_counter > 5) ?  7 : m_table[set][loc].m_counter + 2;
			for(uint i=0;i<NUM_SETS_REUSED_PAGES; i++)
				for(uint j=0;j<ASSOC_REUSED_PAGES; j++) {
					PageEntryQuick &aa= m_table[i][j];
					if(m_table[set][loc].m_proc == aa.m_proc)
						aa.m_counter = (aa.m_counter > 5) ?  7 : aa.m_counter + 2;
				}
			
		}
		else  {  //Decrementamos		
			//m_table[set][loc].m_counter = m_table[set][loc].m_counter > 0 ? m_table[set][loc].m_counter - 1 : 0;
			for(uint i=0;i<NUM_SETS_REUSED_PAGES; i++)
				for(uint j=0;j<ASSOC_REUSED_PAGES; j++) {
					PageEntryQuick &aa= m_table[i][j];
					if(m_table[set][loc].m_proc == aa.m_proc)
						aa.m_counter = (aa.m_counter > 0) ?  aa.m_counter - 1 : 0;
				}
		}
		
		uint result = m_table[set][loc].m_counter >= 4 ? 1 : 0;
		
		//stats
		m_hit_in_whatToDo++;
		if(result) m_1++; 
		else m_0++;
		
		return result;
	} 
	else {
		m_miss_in_whatToDo++;
		insertInSet(aux, set, false, proc);
		return 1;
	}
}


bool PageTableQuick::isOnShadow(Address address, uint set, uint loc) const {

	uint pos= (0x3f & (address.getAddress() >> g_DATA_BLOCK_BITS));
	assert(pos < 64);
	
	if(m_table[set][loc].m_shadow[pos]) {
		//bit off with a xor
		//cerr << "voy a poner a cero la pos " << pos << " " << hex << m_table[set][loc].m_shadow << endl;
		
		//m_table[set][loc].m_shadow ^= (1 << pos);
		m_table[set][loc].m_shadow[pos] = false;
		
		//cerr << "apagada la pos " << pos << " " << hex << m_table[set][loc].m_shadow <<endl;
		
		m_true_isOnShadow++;
		return true;
	} else {
		m_false_isOnShadow++;
		return false;
	}
}

void PageTableQuick::replaced(Address address, uint proc) const{
	Address aux=Address(address);
	aux.onlyPageAddress();

	uint set = pageToTableSet(aux);
	uint loc = findTagInTableSet(aux, set);
	
	uint pos= (0x3f & (address.getAddress() >> g_DATA_BLOCK_BITS));
	
	if(loc != -1) {
		//assert(!isOnShadow(address, set, loc));
		m_hit_in_replaced++;
		
		//cerr << "voy a encender la pos " << pos << " " << hex << m_table[set][loc].m_shadow << endl;
		
		//m_table[set][loc].m_shadow |= (1 << pos);
		
		m_table[set][loc].m_shadow[pos] = true;
		
		//cerr << "encendida la pos " << pos << " " << hex << m_table[set][loc].m_shadow <<endl;

	} else {
		m_miss_in_replaced++;
		insertInSet(aux, set, false, proc);
		uint loc = findTagInTableSet(aux, set);
		m_table[set][loc].m_shadow[pos] = true;
	}

}

uint PageTableQuick::pageToTableSet(Address address) const {
	
	uint res = (address.getAddress() >> 2) & ((1 << BITS_SETS_REUSED_PAGES) - 1);
	//cerr << "(address.getAddress(): " << address << " a2:" << (address.getAddress() >> 2) << " aux: " << aux << endl;
	return res;
}

uint PageTableQuick::findTagInTableSet(Address address, uint set) const {
	for(uint i=0; i<ASSOC_REUSED_PAGES; i++) {
		if(m_table[set][i].m_Address == address) return i;
	}
	return -1;
}

uint PageTableQuick::findTagInTable(Address address) const {
	uint set=(address.getAddress() >> 2) & ((1 << BITS_SETS_REUSED_PAGES) - 1);
	
	for(uint i=0; i<ASSOC_REUSED_PAGES; i++) {
		if(m_table[set][i].m_Address == address) return i;
	}
	return -1;
}

uint PageTableQuick::insertInSet(Address address, uint set, bool hit, uint proc) const {
	int index = -1;
	//we look for an invalid entry
	for(uint i=0; i<ASSOC_REUSED_PAGES; i++) {
		if(m_table[set][i].m_confidence == -1) { index = i; break; }
	}
	if(index == -1) {
		index = 0;
		Time oldest = m_table[set][0].m_lastTouch;
		for(uint i=1; i < ASSOC_REUSED_PAGES; i++) {
			if(m_table[set][i].m_lastTouch < oldest) { 
				oldest = m_table[set][i].m_lastTouch;
				index = i;
			}
		}
	}
	m_table[set][index].m_lastTouch = g_eventQueue_ptr->getTime();
	m_table[set][index].m_Address = address;
	m_table[set][index].m_confidence = 0;
	m_table[set][index].m_counter = 4 + hit*2;
	m_table[set][index].m_proc = proc;
	
	return index;
}




void PageTableQuick::printStats(ostream& out, char* name)  
{ 
	out << name << "_m_hit_in_hit: " << m_hit_in_hit << endl;
	out << name << "_m_miss_in_hit: " << m_miss_in_hit << endl;
	out << name << "_m_hit: " << m_miss_in_hit << endl << endl;
	
	out << name << "_m_hit_in_whatToDo: " << m_hit_in_whatToDo << endl;
	out << name << "_m_miss_in_whatToDo: " << m_miss_in_whatToDo << endl;
	out << name << "_m_whatToDo: " << m_miss_in_whatToDo + m_hit_in_whatToDo << endl << endl;
	
	out << name << "_m_hit_in_replaced: " << m_hit_in_replaced << endl;
	out << name << "_m_miss_in_replaced: " << m_miss_in_replaced << endl;
	out << name << "_m_replaced: " << m_miss_in_replaced + m_hit_in_replaced << endl<< endl;
	
	out << name << "_m_true_isOnShadow: " << m_true_isOnShadow << endl;
	out << name << "_m_false_isOnShadow: " << m_false_isOnShadow << endl;
	out << name << "_m_isOnShadow: " << m_false_isOnShadow + m_true_isOnShadow << endl << endl;
	
	
	out << name << "_m_0: " << m_0 << endl;
	out << name << "_m_1: " << m_1 << endl;
}