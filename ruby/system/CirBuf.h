#ifndef CIRBUF_H
#define CIRBUF_H

#include "AbstractChip.h"

class AbstractChip;


struct NodeCirBuf {
	Address addr;
	bool valid;
	bool reused;
};	

class CirBuf{
	int first, next,size, top, m_TAM;
	int m_version;
	AbstractChip* m_chip_ptr;
	Vector <NodeCirBuf> array; 
	Histogram  *m_histoFIFOReuse;
	
public:
	bool isPresent(Address a);
	CirBuf (AbstractChip* ac, int tam, int version);
	bool empty ();
	bool full () ;
	uint insert (Address addr);
	void remove (Address addr);
	void remove (uint pos);
	void setReuse (Address addr);
	void setReuse (uint pos);
	Address getData(uint pos);
	Address getData(Address addr);
	void printStats();
};

#endif //CIRBUF_H
