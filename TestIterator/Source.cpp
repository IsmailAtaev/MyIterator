#include <iostream>
#include "Queue.h"
#include "IIterator.h"
#include "Person.h";
#include <string>

using namespace std;




bool isEven(int number)
{
	return number % 2 == 0;
}

Person convert(int age)
{
	Person p(age, "Jack");
	return p;
}

int main(int argc, char* args[])
{
	Queue<int> queue;
	for (int i = 0; i <= 20; i++)
	{
		queue.Enqueue(i);
	}

	

	IIterator<int>* queueIterator = queue.getIterator();
	IIterator<int>* where = new Where<int>(queueIterator, isEven);
	IIterator<int>* skip = new Skip<int>(where, 3);
	IIterator<int>* take = new Take<int>(skip, 4);

	IIterator<Person>* select = new Select<int, Person>(take, convert);

	while (select->moveNext())
	{
		cout << "Name: " << select->getCurrent().getName() << "   Age: " <<
			select->getCurrent().getAge() << endl;
	}

	delete queueIterator;
	delete where;
	delete skip;
	delete take;


	return 0;
}