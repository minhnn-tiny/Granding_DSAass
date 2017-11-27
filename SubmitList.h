#ifndef SUBMITLIST_H
#define SUBMITLIST_H

#include "Heap.h"
#include "Submit.h"

class SubmitList
{
private:
	Heap<Submit> *submitData;
public:
	SubmitList();
	void add(Submit&);
	Submit& nextTask();
	void remove();
	bool empty();
};

#endif SUBMITLIST_H