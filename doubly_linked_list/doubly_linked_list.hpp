#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP
class DoublyLinkedList {
public:
	//seen outside as DoublyLinkedList::DataType
	typedef int DataType;
	
private: 
	//grant variable access to tests and polynomial
	friend class DoublyLinkedListTest;
	friend class Polynomial;
	
	//arbitrary capacity 
	static const unsigned int CAPACITY = 65536;
	
	//node struct
	struct Node{
		Node(DataType value);
		DataType value;
		Node* next;
		Node* prev;
	}; 
	
	//private method to get node at index
	Node* getNode(unsigned int index) const;
	
	//MEMBER VARS
	//pointer to list head node
	Node* head_;
	//pointer to list tail node
	Node* tail_;
	//number of elements in list
	unsigned int size_;
	
	//copy constructor 
	DoublyLinkedList(const DoublyLinkedList& rhs);
	//assignment operator
	DoublyLinkedList& operator=(const DoublyLinkedList& rhs);
	
public: 
	//constructor/destructor
	DoublyLinkedList();
	~DoublyLinkedList();
	
	//ACCESSORS
	//return number of elements in list 
	unsigned int size() const;
	//return max number of elements list can hold 
	unsigned int capacity() const; 
	//return true if list is empty, false otherwise
	bool empty() const;
	//return true if list is at capacity, false otherwise
	bool full() const;
	//return value at given index in list. If invalid index
	//return value of last element
	DataType select(unsigned int index) const;
	//searches for given value, returns index of value if found 
	//return size of list otherwise
	unsigned int search(DataType val) const;
	//print all elements in list
	void print() const;
	
	//MUTATATORS
	//insert val into list at given index
	bool insert(DataType val, unsigned int index);
	//insert val at beginning of list 
	bool insert_front(DataType val);
	//insert val at end of list 
	bool insert_back(DataType val);
	//delete val from list at given index
	bool remove(unsigned int index);
	//delete val from beginning of list 
	bool remove_front();
	//delete val at end of list 
	bool remove_back();
	//replace val at given index with given value 
	bool replace(unsigned int index, DataType val);
};
#endif
