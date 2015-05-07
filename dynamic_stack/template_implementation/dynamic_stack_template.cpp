#define ASSERT_TRUE(T) if(!(T)) return false; 
#define ASSERT_FALSE(T) if((T)) return false;

#include <iostream>
#include <string>
#include "dynamic_stack_template.h"

template<>
const int DynamicStack<int>::EMPTY_STACK = -999;

template<>
const char DynamicStack<char>::EMPTY_STACK = NULL;

template<>
const std::string DynamicStack<std::string>::EMPTY_STACK = "";

template <class T>
DynamicStack<T>::DynamicStack() {
	//create dynamic array of size 16
	items_ = new T[16];
	//set size_ = 0 
	size_ = 0; 
	//set capacity to 16
	capacity_ = 16;
	//set initial capacity to 16
	init_capacity_ = 16;
}

template <class T>
DynamicStack<T>::DynamicStack(unsigned int capacity) {
	//create new dynamic array of size capacity
	items_ = new T[capacity];
	//initialize size 
	size_ = 0;
	//set capacity_ and init_capacity_ to capacity
	capacity_ = capacity;
	init_capacity_ = capacity;
}

template <class T>
DynamicStack<T>::~DynamicStack() {
	//delete allocated stack
	delete [] items_;
}

template <class T>
int DynamicStack<T>::size() const {
	//return size 
	return size_; 
}

template <class T>
bool DynamicStack<T>::empty() const {
	//check if stack size is equal to zero
	return size() == 0;
}

template <class T>
void DynamicStack<T>::print() const {
	if (empty()) std::cout << "Empty stack." <<std::endl; 
	//iterate through array in reverse
	for (int i = size() - 1; i >= 0; i--){
		std::cout << items_[i] <<std::endl; 
	}
}

template <class T>
T DynamicStack<T>::peek() const {
	//return value at top of stack 
	if (empty()) return EMPTY_STACK;
	return items_[size()-1];
}

template <class T>
int DynamicStack<T>::capacity() const{
	return capacity_;
}

template <class T>
int DynamicStack<T>::init_capacity() const {
	return init_capacity_;
}

template <class T>
void DynamicStack<T>::push(T value) {
	//check if stack is full 
	if (size() == capacity_){
		//create new array with double capacity
		T* new_arr = new T[capacity_*2];
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
		//push item into stack
		items_[size()] = value;
		//increment size
		size_++;
	} else {
		//push item into stack
		items_[size()] = value;
		//increment size
		size_++;
	}
}

template <class T> 
T DynamicStack<T>::pop() {
	//check for empty stack
	if (empty()) return EMPTY_STACK;
	//decrement size
	size_--;
	//check to see if array must be resized
	if (size()-1 <= capacity_/4 && capacity_/2 >= init_capacity_){ 	
		//create new array with half capacity
		T* new_arr = new T[capacity_/2];
		//assign values of previous stack to new stack 
		for (int i = 0; i < size(); i++){ 
			new_arr[i] = items_[i];  
		}
		//delete previous stack
		delete [] items_;
		//assign items_ to new_arr
		items_ = new_arr;
		//change capacity 
		capacity_ = capacity_/2;
	} 
	return items_[size()];
}

/*
	- three public test functions will be written 
	- all three public test functions will have 
	full coverage of methods in the class 
	- only difference between the three functions 
	will be control flow checks, object instantiations 
	and dynamic stack types
*/

class DynamicStackTemplateTest {
	public: 
		bool test1()
		{
			//instantiate char_stack object 
			DynamicStack<char> char_stack;
			//check for empty stack 
			ASSERT_TRUE(char_stack.empty() == true);
			//check for 0 stack size 
			ASSERT_TRUE(char_stack.size() == 0);
			//check capacity 
			ASSERT_TRUE(char_stack.capacity() == 16);
			//check initial capacity 
			ASSERT_TRUE(char_stack.init_capacity() == 16);
			//push items into char stack 
			for (int i = 0; i < 16; i++){ 
				char_stack.push('t');
			}
			//check for full stack 
			ASSERT_TRUE(char_stack.size() == 16);
			//insert additional element to double stack size
			char_stack.push('s');
			//check last stack item
			ASSERT_TRUE(char_stack.peek() == 's');
			//check stack size and capacity 
			ASSERT_TRUE(char_stack.size() == 17);
			ASSERT_TRUE(char_stack.capacity() == 32);
			//check initial capacity 
			ASSERT_TRUE(char_stack.init_capacity() == 16);
			//remove items such that stack size <= 1/4 capacity
			for (int i = 0; i < 9; i++){
				char_stack.pop();
			} 
			//check stack size
			ASSERT_TRUE(char_stack.size() == 8);
			//check for halved capacity 
			ASSERT_TRUE(char_stack.capacity() == 16);
			//insert stack item 
			char_stack.push('t');
			//check for recently inserted stack item
			ASSERT_TRUE(char_stack.pop() == 't');
			return true;
		}
		
		bool test2() {
			//instantiate string_stack object 
			DynamicStack<std::string> string_stack;
			//check for empty stack 
			ASSERT_TRUE(string_stack.empty() == true);
			//check for 0 stack size 
			ASSERT_TRUE(string_stack.size() == 0);
			//check capacity 
			ASSERT_TRUE(string_stack.capacity() == 16);
			//check initial capacity 
			ASSERT_TRUE(string_stack.init_capacity() == 16);
			//push items into char stack 
			for (int i = 0; i < 16; i++){ 
				string_stack.push("hello_world");
			}
			//check for full stack 
			ASSERT_TRUE(string_stack.size() == 16);
			//insert additional element to double stack size
			string_stack.push("dlrow_olleh");
			//check last stack item
			ASSERT_TRUE(string_stack.peek() == "dlrow_olleh");
			//check stack size and capacity 
			ASSERT_TRUE(string_stack.size() == 17);
			ASSERT_TRUE(string_stack.capacity() == 32);
			//check initial capacity 
			ASSERT_TRUE(string_stack.init_capacity() == 16);
			//remove items such that stack size <= 3/4 capacity
			for (int i = 0; i < 9; i++){
				string_stack.pop();
			} 
			//check stack size
			ASSERT_TRUE(string_stack.size() == 8);
			//check for halved capacity 
			ASSERT_TRUE(string_stack.capacity() == 16);
			//insert stack item 
			string_stack.push("test_item");
			//check for recently inserted stack item 
			ASSERT_TRUE(string_stack.pop() == "test_item");
			return true;
		}
		
		bool test3() { 
			//instantiate int_stack object 
			DynamicStack<int> int_stack;
			//check for empty stack 
			ASSERT_TRUE(int_stack.empty() == true);
			//check for 0 stack size 
			ASSERT_TRUE(int_stack.size() == 0);
			//check capacity 
			ASSERT_TRUE(int_stack.capacity() == 16);
			//check initial capacity 
			ASSERT_TRUE(int_stack.init_capacity() == 16);
			//push items into char stack 
			for (int i = 0; i < 16; i++){ 
				int_stack.push(i);
			}
			//check for full stack 
			ASSERT_TRUE(int_stack.size() == 16);
			//insert additional element to double stack size
			int_stack.push(16);
			//check last stack item
			ASSERT_TRUE(int_stack.peek() == 16);
			//check stack size and capacity 
			ASSERT_TRUE(int_stack.size() == 17);
			ASSERT_TRUE(int_stack.capacity() == 32);
			//check initial capacity 
			ASSERT_TRUE(int_stack.init_capacity() == 16);
			//remove items such that stack size <= 3/4 capacity
			for (int i = 0; i < 9; i++){
				int_stack.pop();
			} 
			//check stack size
			ASSERT_TRUE(int_stack.size() == 8);
			//check for halved capacity 
			ASSERT_TRUE(int_stack.capacity() == 16);
			//insert stack item 
			int_stack.push(7);
			//check for recently inserted stack item 
			ASSERT_TRUE(int_stack.pop() == 7);
			return true;
		}
};

std::string get_status_str(bool status){
	return status ? "Pass" : "Fail";
} 

int main(){
	DynamicStackTemplateTest stack_test;
	
	bool stack_test1_passed = stack_test.test1();
	bool stack_test2_passed = stack_test.test2();
	bool stack_test3_passed = stack_test.test3();
	
	std::cout << "---Dynamic Stack Template Tests---" << std::endl;
	std::cout << "Test1: " << get_status_str(stack_test1_passed) << std::endl;
	std::cout << "Test2: " << get_status_str(stack_test2_passed) << std::endl; 
	std::cout << "Test3: " << get_status_str(stack_test3_passed) << std::endl;
	
	system("pause");
}
