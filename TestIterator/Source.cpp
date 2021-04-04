#include <iostream>
#include "Queue.h"
#include "IIterator.h"

using namespace std;

bool predicate(int number)
{
	return number > 5;
}

bool isEven(int number)
{
	return number % 2 == 0;
}

int main(int argc, char* args[])
{
	Queue<int> queue;
	for (int i = 0; i <= 10; i++)
	{
		queue.Enqueue(i);
	}

	IIterator<int>* defIter = queue.getIterator();
	IIterator<int>* iteratorPredicate = new IterateByPredicate<int>(defIter, predicate);
	IIterator<int>* iteratorEvenAndBiggerFive = new IterateByPredicate<int>(iteratorPredicate, isEven);
	while (iteratorEvenAndBiggerFive->moveNext())
	{
		cout << iteratorEvenAndBiggerFive->getCurrent() << endl;
	}

	delete iteratorPredicate;
	return 0;
}