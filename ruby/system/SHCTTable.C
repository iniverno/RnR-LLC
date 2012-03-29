#include "SHCTTable.h"

//#include "EventQueue.h"


#define NUMBER_ENTRIES 16384
#define BITS_NUMBER_ENTRIES 14
#define SIGN_MASK ((1 << BITS_NUMBER_ENTRIES) - 1)

#define SIGN(a) (a & SIGN_MASK)

SHCTTable::SHCTTable() {
	//m_table.setSize(1024);
	m_table = new  SHCTEntry* [NUMBER_ENTRIES];
	for(uint i=0; i<NUMBER_ENTRIES;i++)
		m_table[i]=new SHCTEntry();
	
	m_hit_in_hit = 0;
	m_miss_in_hit = 0;
	
	m_hit_in_exp = 0;
	m_miss_in_exp = 0;
	
	m_0 = 0;
	m_1 = 0;
	
	m_hit_in_cnt = 0;
	m_miss_in_cnt = 0;
	
}

void SHCTTable::hit(Address address) {

	if(present(address)) {
		m_hit_in_hit++;
		
		SHCTEntry *aux = lookup(address);
		aux->m_counter+= (aux->m_counter < 7) ? 1 : 0;
	} 
	else {
		m_miss_in_hit++;
	}
}

SHCTEntry* SHCTTable::lookup(Address address) {
	//assert(present(address));
		//cerr << "address: "  <<  address << "  index: " << SIGN(address.getAddress()) << endl;

	return m_table[SIGN(address.getAddress())];
}


void SHCTTable::victim(Address address, bool reused) {
	//cerr << "victim" << endl;
	if(present(address)) {
		m_hit_in_exp++;
		
		if(!reused) {
			SHCTEntry *aux = lookup(address);
			aux->m_counter-= (aux->m_counter > 0) ? 1 : 0;
		}
	}
	else {
		m_miss_in_exp++;
	}
}

int SHCTTable::counter(Address address) {
	//cerr << "counter" << endl;

	if(present(address)) {
		m_hit_in_cnt++;
		
		if (lookup(address)->m_counter > 0) return 1;
		else return 0;
	} 
	else {
		m_miss_in_cnt++;
		//insertamos
		SHCTEntry *aux = lookup(address);
		aux->m_Address = address;
		aux->m_counter = 0;
		aux->m_valid = true;
		return 1;
	}
}


bool SHCTTable::present(Address address) {
	return lookup(address)->m_valid;
	//SHCT does not store a TAG
	//return lookup(address)->m_Address == address;
}



void SHCTTable::printStats(ostream& out, char* name)  
{ 
	out << name << "_m_hit_in_hit: " << m_hit_in_hit << endl;
	out << name << "_m_miss_in_hit: " << m_miss_in_hit << endl;
	
	out << name << "_m_hit_in_exp: " << m_hit_in_exp << endl;
	out << name << "_m_miss_in_exp: " << m_miss_in_exp << endl;
	//out << name << "_m_whatToDo: " << m_miss_in_whatToDo + m_hit_in_whatToDo << endl << endl;
	
	out << name << "_m_hit_in_replaced: " << m_hit_in_cnt << endl;
	out << name << "_m_miss_in_replaced: " << m_miss_in_cnt << endl;
	//out << name << "_m_replaced: " << m_miss_in_replaced + m_hit_in_replaced << endl<< endl;
	
	//out << name << "_m_true_isOnShadow: " << m_true_isOnShadow << endl;
	//out << name << "_m_false_isOnShadow: " << m_false_isOnShadow << endl;
	//out << name << "_m_isOnShadow: " << m_false_isOnShadow + m_true_isOnShadow << endl << endl;
	
	
	//out << name << "_m_0: " << m_0 << endl;
	//out << name << "_m_1: " << m_1 << endl;
}