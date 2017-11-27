#ifndef HEAP_H
#define HEAP_H

#include <memory>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

#include "Submit.h"

template<class DataType>
class Heap
{
public:
	Heap(int = 10);
	DataType& pop();
	DataType& minData();
	void push(DataType&&);
	void push(const DataType&);
	bool test();
	bool isEmpty();
private:
	int heapSize;
	int capacity;
	DataType* data;
	void increaseSize();
	void decreaseSize();
	void reheapUp(int index);
	void reheapDown(int index);
	int left(int index);
	int right(int index);
	int parent(int index);
};

#endif

