#include <iostream>
#include "circular_queue.h"

typedef CircularQueue::QueueItem QueueItem;
const QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue() {
	//create circular queue (c-queue) of cap 16
	items_ = new QueueItem[16];
	//set head to index 0
	head_ = 0;
	//set tail to index 0
	tail_ = 0;
	//set capacity to 16
	capacity_ = 16;
	//set size to 0
	size_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity) {
	//create c-queue 
	items_ = new QueueItem[capacity];
	//set head to index 0
	head_ = 0;
	//set tail to index 0
	tail_ = 0;
	//set capacity to capacity_
	capacity_ = capacity;
	//set size to 0
	size_ = 0;
}

CircularQueue::~CircularQueue() {
	//free dynamically allocated memory
	delete [] items_;
}

int CircularQueue::size() const {  
	//return size of c-queue 
	return size_;
}

bool CircularQueue::empty() const {    
	//check if c-queue is empty
	return size_ == 0;
}

bool CircularQueue::full() const {
	//check if c-queue is full
	return size_ == capacity_;
}

void CircularQueue::print() const {
	//check if queue wraps around
	if (empty()){
		std::cout << "Empty queue." << std::endl; 
	} else if (tail_ <= head_){ 
		//print from head to capacity
		for(int i = head_; i < capacity_; i++){
			std::cout << items_[i] <<std::endl;
		}
		//print from 0 to 1 index less than tail 
		for (int i = 0; i < tail_; i++){
			std::cout << items_[i] <<std::endl;
		}
	} else {
		//print from head to tail
		for(int i = head_; i < tail_; i++){
			std::cout << items_[i] <<std::endl;
		}
	}
}

QueueItem CircularQueue::peek() const {
	//check to see if c-queue is empty
	if (empty()) return EMPTY_QUEUE;
	//return value at head of c-queue 
	return items_[head_];
}

bool CircularQueue::enqueue(QueueItem value) {
	//check to see if c-queue is full
	if (full()) return false;
	//enqueue value at c-queue tail position
	items_[tail_] = value;
	//change tail index
	tail_ = (tail_+1)%capacity_;
	//increase size
	size_++;
	return true; 
}

QueueItem CircularQueue::dequeue() {
	//check  to see if empty c-queue 
	if(empty()) return EMPTY_QUEUE;
	//create temp value to store value at head of c-queue 
	QueueItem tmpVal = items_[head_];
	//change head index; dequeued item in don't care state
	head_ = (head_ + 1)%capacity_;	
	//decrease size
	size_--; 
	return tmpVal;
}
