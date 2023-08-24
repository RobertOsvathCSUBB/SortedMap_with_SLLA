#include "ExtendedTest.h"
#include "ShortTest.h"

#include "SortedMap.h"
#include "SMIterator.h"
#include <crtdbg.h>
#include <exception>
#include <assert.h>
#include <iostream>
using namespace std;

bool relatie(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testIteratorPrevious()
{
	cout << "Test iterator previous" << endl;
	SortedMap sm(relatie);
	for (int i = 1; i <= 50; i++)
		sm.add(i, i);

	SMIterator it = sm.iterator();
	try
	{
		it.previous();
		assert(false);
	}
	catch (exception& e)
	{
		assert(true);
	}

	it.next();
	int i = 1;
	while (it.valid())
	{
		it.previous();
		assert(it.getCurrent() == TElem(i, i));
		it.next();
		it.next();
		i++;
	}
}


int main() {
	testAll();
	testIteratorPrevious();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	_CrtDumpMemoryLeaks();
	return 0;
}


