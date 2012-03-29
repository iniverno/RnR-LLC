#ifndef PageTableQuick_H
#define PageTableQuick_H

#include "Address.h"

class PageEntryQuick  {
public:
	Address m_Address;
	int m_confidence;
	uint m_counter;
	Time m_lastTouch;
	bool m_shadow [64];
	uint m_proc;
	
	PageEntryQuick() {
		m_confidence = -1;
		m_counter = 0;
		m_Address = Address(0);
		m_lastTouch = 0;
		for(uint i=0; i<64; i++)m_shadow[i] = false;
		m_proc= 0;
	}
	PageEntryQuick(Address a) {
		m_confidence = -1;
		m_counter = 1;
		m_Address = a;
		m_lastTouch = 0;
		for(uint i=0; i<64; i++)m_shadow[i] = false;
		m_proc=0;
	}
};


class PageTableQuick {
	//Map <Address, PageEntryQuick> m_table;
	PageEntryQuick** m_table;

	mutable uint m_hit_in_hit;
	mutable uint m_miss_in_hit;
	
	mutable uint m_hit_in_whatToDo;
	mutable uint m_miss_in_whatToDo;
	
	mutable uint m_0;
	mutable uint m_1;

	mutable uint m_hit_in_replaced;
	mutable uint m_miss_in_replaced;
	
	mutable uint m_true_isOnShadow;
	mutable uint m_false_isOnShadow;
public:

	PageTableQuick();
	
	void hit(Address address, uint proc);
	uint whatToDo(Address address, uint proc) const;
	void replaced(Address address, uint proc) const;
	
	bool isOnShadow(Address address, uint set, uint loc) const;
	
	uint pageToTableSet(Address address) const ;

	uint findTagInTableSet(Address address, uint set) const;

	uint findTagInTable(Address address) const;

	uint insertInSet(Address address, uint set, bool hit, uint proc) const;
	
	void printStats(ostream& out, char* name)  ;

};

#endif //