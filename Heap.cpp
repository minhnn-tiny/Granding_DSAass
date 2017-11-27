#include "Heap.h"

template<class DataType>
Heap<DataType>::Heap(int cap)
{
	if (cap <= 0)
		throw std::exception("Capacity invalid!");
	this->capacity = cap;
	heapSize = 0;
	data = new DataType[cap];
}
template<class DataType>
DataType& Heap<DataType>::pop()
{
	if (this->heapSize == 0)
		throw std::exception("Heap underflow");

	data[0] = data[heapSize - 1];
	reheapDown(0);
	--heapSize;
}
template<class DataType>
void Heap<DataType>::push(DataType&& dat)
{
	data[heapSize] = std::move(dat);
	reheapUp(heapSize);
	++heapSize;
	if (heapSize > capacity / 2)
		increaseSize();
}
template<class DataType>
void Heap<DataType>::push(const DataType& dat)
{
	data[heapSize] = dat;
	reheapUp(heapSize);
	++heapSize;
	if (heapSize > capacity / 2)
		increaseSize();
}
template<class DataType>
bool Heap<DataType>::isEmpty()
{
	return (heapSize == 0);
}
template<class DataType>
void Heap<DataType>::increaseSize()
{
	DataType* tmpData = new DataType[heapSize];
	memcpy(tmpData, data, sizeof(DataType)*heapSize);
	delete[] data;
	data = new DataType[capacity * 2];
	memcpy(data, tmpData, sizeof(DataType)*heapSize);
	capacity *= 2;
}
template<class DataType>
void Heap<DataType>::decreaseSize()
{
	capacity = capacity / 2 + ((capacity % 2) == 0 ? 0 : 1);
	DataType* tmpData = new DataType[heapSize];
	memcpy(tmpData, data, sizeof(DataType)*heapSize);
	delete[] data;
	data = new DataType[capacity];
	memcpy(data, tmpData, sizeof(DataType)*heapSize);
}
template<class DataType>
void Heap<DataType>::reheapUp(int index)
{
	DataType tmpData = data[index];
	while (index > 0 && tmpData < data[parent(index)])
	{
		data[index] = data[parent(index)];
		index = parent(index);
	}
	data[index] = tmpData;
}
template<class DataType>
void Heap<DataType>::reheapDown(int index)
{
	DataType tmpData = data[index];

	while ((left(index) < heapSize && data[left(index)] < tmpData) ||
		(right(index) < heapSize && data[right(index)] < tmpData))
	{
		DataType minData = data[left(index)];
		int minIndex = left(index);
		if (right(index) < heapSize)
		{
			if (data[right(index)] < minData)
			{
				minData = data[right(index)];
				minIndex = right(index);
			}
		}
		data[index] = minData;
		index = minIndex;
	}
	data[index] = tmpData;
}
template<class DataType>
int Heap<DataType>::left(int index)
{
	return 2 * index + 1;
}
template<class DataType>
int Heap<DataType>::right(int index)
{
	return 2 * index + 2;
}
template<class DataType>
int Heap<DataType>::parent(int index)
{
	return index / 2 + ((index % 2) == 0 ? -1 : 0);
}
template<class DataType>
DataType& Heap<DataType>::minData()
{
	if (heapSize == 0)
		throw std::exception("Heap underflow!");
	return data[0];
}
template<class DataType>
bool Heap<DataType>::test()
{
	for (int i = 0; i < heapSize / 2 + 1; ++i)
	{
		if (left(i) < heapSize)
			if (data[left(i)] < data[i])
				return false;
		if (right(i) < heapSize)
			if (data[(right(i))] < data[i])
				return false;
	}
	return true;
}
template Heap<int>;
template Heap<Submit>;
