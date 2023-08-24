#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) : rel(r)
{
	this->cap = 2;
	this->length = 0;
	this->nodes = new Node[this->cap];
	for (int i = 0; i < this->cap - 1; i++)
	{
		this->nodes[i] = Node{ TElem(NULL_TKEY, NULL_TVALUE) };
		this->nodes[i].next = i + 1;
	}
	this->nodes[this->cap - 1] = Node{ TElem(NULL_TKEY, NULL_TVALUE) };
	this->nodes[this->cap - 1].next = -1;
	this->head = -1;
	this->firstFree = 0;
}

// Best case: we do not need to resize -> theta(1)
// Worst case: we need to resize -> theta(new capacity)
int SortedMap::allocateP()
{
	if (this->firstFree == -1)
	{
		int newCap = this->cap * 2;
		Node* aux = new Node[newCap];
		for (int i = 0; i < this->cap; i++)
			aux[i] = this->nodes[i];
		for (int i = this->cap; i < newCap - 1; i++)
		{
			aux[i] = Node{ TElem(NULL_TKEY, NULL_TVALUE) };
			aux[i].next = i + 1;
		}
		aux[newCap - 1] = Node{ TElem(NULL_TKEY, NULL_TVALUE) };
		aux[newCap - 1].next = -1;
		this->firstFree = this->cap;
		delete[] this->nodes;
		this->nodes = aux;
		this->cap = newCap;
	}

	int newFreePos = this->firstFree;
	this->firstFree = this->nodes[firstFree].next;
	return newFreePos;
}

void SortedMap::freeP(int i)
{
	this->nodes[i].elem = TElem(NULL_TKEY, NULL_TVALUE);
	this->nodes[i].next = this->firstFree;
	this->firstFree = i;
}

// Best case: the key of the element is already in the map (search is
//				theta(1)), and it's the head of the slla 
//				 -> theta(1)
// Worst case: the key of the element already exists in the map and 
//				is at the end -> O(length)
// Average case: if we assume that the probability of the key already
//				existing in the map are the same as the probability
//				of not existing in the map, it is still 
// ->O(length) + O(length) = O(length)
TValue SortedMap::add(TKey k, TValue v)
{
	TValue searchResult = this->search(k);
	if (searchResult != NULL_TVALUE)
		this->remove(k);
	
	int i = this->allocateP();
	Node& freeNode = this->nodes[i];
	int currentPos = this->head, previousPos = -1;
	while (currentPos != -1 && this->nodes[currentPos].elem != TElem(NULL_TKEY, NULL_TVALUE)
		&& this->rel(this->nodes[currentPos].elem.first, k))
	{
		previousPos = currentPos;
		currentPos = this->nodes[currentPos].next;
	}

	if (previousPos == -1)
		this->head = i;
	else
		this->nodes[previousPos].next = i;
	freeNode.next = currentPos;
	freeNode.elem = TElem(k, v);

	this->length++;

	return searchResult;
}

// Best case: the key is from the first element
//				-> theta(1)
// Worst case: the key is from the last element -> theta(length)
// Average case: -> O(length)
TValue SortedMap::search(TKey k) const
{
	int currentPos = this->head;
	while (currentPos != -1 && this->nodes[currentPos].elem != TElem(NULL_TKEY, NULL_TVALUE))
	{
		Node& currentNode = this->nodes[currentPos];
		if (currentNode.elem.first == k)
			return currentNode.elem.second;
		currentPos = currentNode.next;
	}
	return NULL_TVALUE;
}

// Best case: the key is from the first element
//				-> theta(1)
// Worst case: the key is from the last element -> O(length)
// Average case: O(length)
TValue SortedMap::remove(TKey k)
{
	int currentPos = this->head, previousPos = -1;
	while (currentPos != -1)
	{
		Node& currentNode = this->nodes[currentPos];
		if (currentNode.elem.first == k)
		{
			if (previousPos == -1)
				this->head = currentNode.next;
			else
				this->nodes[previousPos].next = currentNode.next;
			TValue returnVal = currentNode.elem.second;
			this->freeP(currentPos);
			this->length--;
			return returnVal;
		}
		previousPos = currentPos;
		currentPos = currentNode.next;
	}

	return NULL_TVALUE;
}

//Theta(1)
int SortedMap::size() const
{
	return this->length;
}

//Theta(1)
bool SortedMap::isEmpty() const
{
	return this->length == 0;
}

SMIterator SortedMap::iterator() const
{
	return SMIterator(*this);
}

SortedMap::~SortedMap()
{
	delete[] this->nodes;
}
