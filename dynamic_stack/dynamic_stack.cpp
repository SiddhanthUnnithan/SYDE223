#include <iostream>
#include "dynamic_stack.h"

typedef DynamicStack::StackItem StackItem; 
const StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack() {
	//create dynamic array of size 16
	items_ = new StackItem[16];
	//set size_ = 0 
	size_ = 0; 
	//set capacity to 16
	capacity_ = 16;
	//set initial capacity to 16
	init_capacity_ = 16;
}

DynamicStack::DynamicStack(unsigned int capacity) {
	//create new dynamic array of size capacity
	items_ = new StackItem[capacity];
	//initialize size 
	size_ = 0;
	//set capacity_ and init_capacity_ to capacity
	capacity_ = capacity;
	init_capacity_ = capacity;
}

DynamicStack::~DynamicStack() {
	//delete allocated stack
	delete [] items_;
}

int DynamicStack::size() const {
	//return size 
	return size_; 
}

bool DynamicStack::empty() const {
	//check if stack size is equal to zero
	return size() == 0;
}

void DynamicStack::print() const {
	if (empty()) std::cout << "Empty stack." <<std::endl; 
	//iterate through array in reverse
	for (int i = size() - 1; i >= 0; i--){
		std::cout << items_[i] <<std::endl; 
	}
}

StackItem DynamicStack::peek() const {
	//return value at top of stack 
	if (empty()) return EMPTY_STACK;
	return items_[size()-1];
}

/*
//optional accessor methods available for use
int DynamicStack::capacity() const{
	return capacity_;
}

int DynamicStack::init_capacity() const {
	return init_capacity_;
}
*/

void DynamicStack::push(StackItem value) {
	//check if stack is full 
	if (size() == capacity_){
		//create new array with double capacity
		StackItem* new_arr = new StackItem[capacity_*2];
		//assign values of previous stack to new stack
		for (int i = 0; i < size(); i++){
			new_arr[i] = items_[i];
		}    
		//delete previous stack
		delete [] items_;
		//assign items_ to new_arr
		items_ = new_arr;
		//change capacity (init_capacity_ remains the same)
		capacity_ = capacity_*2;
	} 
	//push item into stack
	items_[size()] = value;
	//increment size
	size_++;
}

StackItem DynamicStack::pop() {
	//check for empty stack
	if (empty()) return EMPTY_STACK;
	//popped item within don't care state; decrease size
	size_--;
	//check to see if array must be resized
	if (size() <= capacity_/4 && capacity_/2 >= init_capacity_){ 	
		//create new array with half capacity
		StackItem* new_arr = new StackItem[capacity_/2];
		//assign values of previous stack to new stack 
		for (int i = 0; i <= size_+1; i++){ 
			new_arr[i] = items_[i];  
		}
		//delete previous stack
		delete [] items_;
		//assign items_ to new_arr
		items_ = new_arr;
		//change capacity 
		capacity_ = capacity_/2;
	} 
	//return popped item
	return items_[size()];
}
