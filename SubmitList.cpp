#include "SubmitList.h"

SubmitList::SubmitList()
{
	submitData = new Heap<Submit>(20);
}
void SubmitList::add(Submit& sub)
{
	submitData->push(sub);
}
Submit& SubmitList::nextTask()
{
	return submitData->minData();
}
void SubmitList::remove()
{
	submitData->pop();
}
bool SubmitList::empty()
{
	return submitData->isEmpty();
}

