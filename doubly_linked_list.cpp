@@ -0,0 +1,223 @@
#include <iostream>
#include "a1_doubly_linked_list.hpp"

// returns pointer to node at a given index
DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const{
	int node_count = 0;
	Node* currentNode = head_; 
	// check to see whether count = index, and whether node has next
	while (node_count != index && currentNode->next!=NULL){
		currentNode = currentNode->next;
		node_count++; 
	}
	return currentNode;
}

// constructor 
DoublyLinkedList::DoublyLinkedList(){
	size_ = 0; 
	head_ = NULL;
	tail_ = NULL;
	std::cout << head_ <<std::endl;
	std::cout << tail_ <<std::endl;
	std::cout <<std::endl;
}

DoublyLinkedList::Node::Node(DoublyLinkedList::DataType data){
	value = data;
}

// destructor 
DoublyLinkedList::~DoublyLinkedList(){
	// destructor logic; destory dynamic variables 
	
}

// ACCESSORS
// return size of linked_list
unsigned int DoublyLinkedList::size() const{
	return size_;
}


// return capacity of linked_list
unsigned int DoublyLinkedList::capacity() const{
	return CAPACITY;
}

// determine whether linked_list is empty
bool DoublyLinkedList::empty() const{
	if(size() == 0) return true; 
	return false;
}

// determine whether linked_list is full
bool DoublyLinkedList::full() const{
	if(size() == capacity()) return true;
	return false; 
}


// returns value at given index in linked_list
DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const{
	if(index >= size()){
		return getNode(size()-1)->value;
	} 
	return getNode(index)->value;
}

// searches for value in linked_list; returns first index if found
unsigned int DoublyLinkedList::search(DataType val) const{
	int count = 0;
	for(Node* node = head_; node != NULL; node = node->next){
		if(node->value == val){
			return count;
		}
		count++;
	}
	return size(); 
}

// prints out all node values within linked_list
void DoublyLinkedList::print() const{
	for(Node* node = head_; node!=NULL; node = node->next){
		std::cout << node->value << std::endl;
	}
}

// MUTATORS
// inserts value at given index 
bool DoublyLinkedList::insert(DataType val, unsigned int index){
	if (index == 0){
		return insert_front(val);
	} else if (index == size()){
		return insert_back(val);
	} else if (index > size()){
		return false; 
	}else {
		Node* insertNode = new Node(val);
		Node* node = getNode(index); 
		Node* prevNode = node->prev; 
		prevNode->next = insertNode;
		node->prev = insertNode;
		insertNode->prev = prevNode;
		insertNode->next = node;
		size_++;
		return true;
	}
}

// insert value at beginning of list index[0]
bool DoublyLinkedList::insert_front(DoublyLinkedList::DataType val){
	Node* insertNode = new Node(val);
	insertNode->prev = NULL; //no prev node
	if(size() == capacity()){
		return false;
	} 
	if(head_ == NULL) { //empty list
		head_ = insertNode; 
		tail_ = insertNode;
		insertNode->next = NULL;
		size_++;
		return true;
	}
	Node* node = head_; 
	node->prev = insertNode;
	insertNode->next = node;
	head_ = insertNode;
	//increment size_
	size_++;
	return true;
}

// insert value at end of list index[-1]
bool DoublyLinkedList::insert_back(DoublyLinkedList::DataType val){
	Node* insertNode = new Node(val);
	insertNode->next = NULL; //no next node
	if (size() == capacity()){
		return false; 
	} 
	if (size() == 0){
		return insert_front(val);
	} 
	Node* node = tail_;
	node->next = insertNode;
	insertNode->prev = node;
	tail_ = insertNode;
	size_++;
	return true;
}

// remove value at given index (delete node) 
bool DoublyLinkedList::remove(unsigned int index){
	if(index >= size() || index > capacity() || index < 0){
		return false;
		return remove_front();
	} else if (index == (size()-1)){
		return remove_back(); 
	} else if (index >= size()){
		return false; 
	} else {
		Node* node = getNode(index);
		Node* prevNode = node->prev;
		Node* nextNode = node->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		delete node;
		size_--;
	}
}
// remove node from front of list (index[0])
bool DoublyLinkedList::remove_front(){
	// empty list
	if(head_ == NULL){
		return false; 
	} else if (head_->next == NULL){ // one item in list
		Node* node = head_;
		delete node; 
		head_ = NULL;
		tail_ = NULL;
		size_--;
		return true;
	}else { // remove node which head_ is pointed to
		Node* node = head_; 
		Node* nextNode = node->next;
		head_ = nextNode;
		nextNode->prev = NULL; 
		delete node;
		size_--;
		return true;
	}
}

bool DoublyLinkedList::remove_back(){
	if(head_ == NULL){ // empty list 
		return false; 
	} else if (head_->next == NULL){ //one item in list
		Node* node = head_; 
		delete node;
		head_ = NULL;
		tail_ = NULL;
		// decrement size 
		size_--;
		return true; 
	} else { // remove node which tail_is pointed to 
		Node* node = tail_;
		Node* prevNode = node->prev; 
		tail_ = prevNode;
		prevNode->next = NULL; 
		delete node; 
		// decrement size
		size_--;
		return true;
	}
}

bool DoublyLinkedList::replace(unsigned int index, DataType val){
	// error-check: index >= size() 
	if(index >= size() || index > capacity() || index < 0){
		return false; 
	} 
	Node* node = getNode(index);
	node->value = val;
}
