#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator {
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap&);

	int currentPos;

public:
	void first();
	void next();
	void previous();
	bool valid() const;
	TElem getCurrent() const;
};

