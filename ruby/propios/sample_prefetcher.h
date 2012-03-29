#ifndef SAMPLE_PREFETCHER_H
#define SAMPLE_PREFETCHER_H

#include <stdio.h>

#include <map>
#include <fstream>
#include <iomanip>
#include <iostream>
#
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Basic Classes and Templates
///////////////////////////////////////////////////////////////////////////////

/// Nodes in the LRU-like queues
template<class ItemType>
class _List_Node
{
  public:
    ItemType _item;
    _List_Node* _next;
    _List_Node* _prev;
    
    _List_Node(ItemType item = ItemType())
        :_item(item), 
         _next(0), 
         _prev(0)
    {}

    _List_Node(_List_Node& node)
        :_item(node._item), 
         _next(0), 
         _prev(0)
    {}

    ~_List_Node(){}
};

/// template class for any LRU-like queues.
/// The queue is implemented in a form of double-linked list.
/// The template provides constructor/destructor, and a "bring to head" method.
/// Inherite from LRUList<ItemType> to create your new queue class,
/// where ItemType is the class of queue items. 
/// Requirement of ItemType:
/// 	o. It should provide default/copy constructors.
///		o. It should provide a Dump() routine for dumpping out its content to stdout. This is useful in debugging.
template<class ItemType>
class LRUList{
  public:
    typedef _List_Node<ItemType> Node;
  protected:
    Node* mListHead;
    Node* mListTail;
    UINT32 mListLength;

    /// Brings the node to the head of the queue.
    /// This makes it Most Recently Used
    void BringsToHead(Node* ptr){

        if( ptr->_prev != NULL ) 
        {
            // Pull the entry out chain previous and next elements
            // to each other
            ptr->_prev->_next = ptr->_next;
            if( ptr->_next ) 
            {
                ptr->_next->_prev = ptr->_prev;
            }
            else 
            {
                // If tail is being removed, set the tail to the
                // previous guy in the link-list
                mListTail = ptr->_prev;
            }

            // Since we are bringing this to the head, next
            // element is going to be the current head.  
            ptr->_next        = mListHead;
            ptr->_prev        = NULL;
                
            // set current head's previous to this
            mListHead->_prev   = ptr;
                
            // This is now the current head
            mListHead          = ptr;
        }
    }

    /// Brings the node to the tail of the queue.
    /// This makes it Least Recently Used
    void BringsToTail(Node* ptr){
        if( ptr->_next != NULL ) 
        {
            // Pull the entry out chain previous and next elements
            // to each other
            ptr->_next->_prev = ptr->_prev;
            if( ptr->_prev ) 
            {
                ptr->_prev->_next = ptr->_next;
            }
            else 
            {
                // If head is being removed, set the head to the
                // next guy in the link-list
                mListHead        = ptr->_next;
            }

            // Since we are bringing this to the tail, next
            // element is going to be the current tail.  
            ptr->_prev        = mListTail;
            ptr->_next        = NULL;

            mListTail->_next   = ptr;

            // This is now the current tail
            mListTail          = ptr;
        }
    }

  public:
    /// Create the list with specified length.
    LRUList(UINT32 listLength): 
        mListHead(0), 
        mListTail(0), 
        mListLength(listLength) 
    {
        Node* prevNode = 0;
        for (UINT32 i=0; i<listLength; i++){
            Node* node = new Node();
            if (mListHead == 0) mListHead = node;
            node->_prev = prevNode;
            if (prevNode) prevNode->_next = node;
            prevNode = node;
        }
        mListTail = prevNode;
    }

    ~LRUList()
    {
        while (mListHead)
        {
            Node* node = mListHead->_next;
            delete mListHead;
            mListHead = node;
        }
    }

    /// Utillity routine for debugging in gdb. Dump out the list.
    void Dump()
    {
        Node* node=mListHead;
        for (UINT32 i=0; i<mListLength; i++, node=node->_next)
        {
            cout<<i<<": ";
            if (node) node->_item.Dump();
            cout<<endl;
        }
    }
};

///////////////////////////////////////////////////////////////////////////////
// Stride Prefetching
///////////////////////////////////////////////////////////////////////////////

class MemLogEntry{
  public:
    ADDRINT ip; // IP of the mem instruction
    ADDRINT last_mem_addr; // the last mem addr
    INT32   stride; // stride detected
    UINT32  count; // the mem addr is accessed in stride for "count" times
    bool    trained;
    
    /// default constructor
    MemLogEntry(ADDRINT ip = 0)
        :last_mem_addr(0),
         stride(0),
         count(0),
         trained(0)
    { 
        this->ip = ip; 
    }

    /// copy constructor
    MemLogEntry(const MemLogEntry& ent)
        :ip(ent.ip), 
         last_mem_addr(ent.last_mem_addr), 
         stride(ent.stride), 
         count(ent.count),
         trained(ent.trained)
    {
        // Nothing
    }

    ~MemLogEntry()
    {
        // Nothing
    }

    /// Dump routine
    void Dump(){
        cout << hex << ip << "," << last_mem_addr << "," << dec <<stride << "," << count;
    }
};

class StridePrefetchTable
    : public LRUList<MemLogEntry> 
{
  private:
    map<ADDRINT, Node*> PClist;
    map<ADDRINT, Node*>::iterator iter;

  public:
    static const UINT32 DEFAULT_STRIDE_PREFETCH_TABLE_SIZE = 256;

    StridePrefetchTable(UINT32 tableSize=DEFAULT_STRIDE_PREFETCH_TABLE_SIZE)
        : LRUList<MemLogEntry>(tableSize){}

    ~StridePrefetchTable(){}

    /// Look-up in the prefetch table. This leeds to a subsequent LRU update in the table.
    /// Returns the entry if hit.
    MemLogEntry* AccessEntry(UINT32 threadId, ADDRINT ip, ADDRINT memAddr){

        // find the ip log in the table
        Node* node = mListHead;
        while (node && node->_item.ip!=ip) node=node->_next;

        MemLogEntry* entry;
        if ( node == NULL ) { 
            /// Replace tail
            node = mListTail;

            entry = &(node->_item);

            DelFrmPClist( entry->ip );
            entry->ip = ip;
            entry->last_mem_addr = memAddr;
            entry->stride = 0;
            entry->trained = false;
            AddToPClist( ip, node );
        }
        else         /// update
        {
            entry = &(node->_item);

//         cout <<"Found IP: "<<hex<<ip
//              <<" Last Mem Addr: "<<entry->last_mem_addr
//              <<" Curr Mem Addr: "<<memAddr<<dec<<endl;

            INT32 newstride      = memAddr - entry->last_mem_addr;
            entry->last_mem_addr = memAddr;

            if (newstride && (newstride == entry->stride)) {
                ++(entry->count); 
                if( entry->count >= 1 ) 
                {
                  if(!(entry->trained))
                    entry->trained = true;
                }
            }
            else { 
                entry->count = 0; 
                entry->stride = newstride;
                entry->trained = false;
            }
        }

        BringsToHead(node);

        return entry;
    }


    Node* FindPC( ADDRINT ip )
    {
        iter = PClist.find(ip);
        if( iter != PClist.end() ) 
        {
            return iter->second;
        }

        return NULL;
    }

    inline void AddToPClist( ADDRINT ip, Node *tmp ) 
    {
        PClist[ ip ] = tmp;
    }

    inline void DelFrmPClist( ADDRINT ip ) 
    {
            PClist.erase( ip );
    }

};

class SamplePrefetcher : public StridePrefetchTable
{
  private:

    
  public:
    
    SamplePrefetcher() : StridePrefetchTable()
    {
    }
    
    ~SamplePrefetcher()
    {
    }
};

#endif
