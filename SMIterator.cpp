#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m)
{
	this->first();
}

void SMIterator::first()
{
	this->currentPos = this->map.head;
}

void SMIterator::next()
{
	if (this->valid())
		this->currentPos = this->map.nodes[currentPos].next;
	else
		throw exception();
}

// Best case: the current element is the head of the map
//			-> theta(1)
// Worst case: the current element is the last element in the map
//			-> theta(length of the map)
// Average case: -> O(length of the map)
void SMIterator::previous()
{
	int pos = this->map.head;
	while (pos != -1 && this->map.nodes[pos].next != this->currentPos)
		pos = this->map.nodes[pos].next;

	if (pos == -1)
		throw exception();

	this->currentPos = pos;
}

bool SMIterator::valid() const
{
	return this->currentPos != -1;
}

TElem SMIterator::getCurrent() const
{
	if (this->valid())
		return this->map.nodes[this->currentPos].elem;
	else
		throw exception();
}


