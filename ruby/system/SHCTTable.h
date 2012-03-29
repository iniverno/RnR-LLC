#ifndef SHCT_H
#define SHCT_H

#include "Address.h"

class SHCTEntry  {
public:
	Address m_Address;
	uint m_counter;
	bool m_valid;
	
	SHCTEntry() {
		m_counter = 0;
		m_Address = Address(0);
		m_valid = false;
	}
	SHCTEntry(Address a) {
		m_counter = 1;
		m_Address = a;
	}
};


class SHCTTable {
	//Map <Address, PageEntryQuick> m_table;
	SHCTEntry** m_table;

	mutable uint m_hit_in_hit;
	mutable uint m_miss_in_hit;
	
	mutable uint m_hit_in_cnt;
	mutable uint m_miss_in_cnt;
	
	mutable uint m_0;
	mutable uint m_1;

	mutable uint m_hit_in_exp;
	mutable uint m_miss_in_exp;

public:

	SHCTTable();
	
	void hit(Address address);
	SHCTEntry* lookup(Address address);
	void victim(Address address, bool reused);
	int counter(Address address);
	bool present(Address address);
	void printStats(ostream& out, char* name);
	
	//void printStats(ostream& out, char* name)  ;


};

#endif //
