#ifndef PageEntryQuick_H
#define PageEntryQuick_H

class PageEntryQuick  {
	Address m_Address;
	uint m_confidence;
	uint m_counter;

public:
	PageEntryQuick() {
		m_confidence = 0;
		m_counter = 0;
		m_Address = Address(0);
	}
	
	void hit(Address address);
	uint whatToDo(Address address);
};

#endif //