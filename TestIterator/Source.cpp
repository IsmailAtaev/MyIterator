#include <iostream>
#include "Queue.h"
#include "IIterator.h"

using namespace std;

bool predicate(int number)
{
	return number > 5;
}

int main(int argc, char* args[])
{
	Queue<int> queue;
	for (int i = 0; i <= 10; i++)
	{
		queue.Enqueue(i);
	}

	IIterator<int>* iteratorPredicate = new IterateByPredicate<int>(&queue, predicate);

	while (iteratorPredicate->moveNext())
	{
		cout << iteratorPredicate->getCurrent() << endl;
	}

	delete iteratorPredicate;
	return 0;
}