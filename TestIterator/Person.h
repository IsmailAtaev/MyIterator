#pragma once
#include <string>

using namespace std;

class Person
{
private :
	int Age;
	string Name;
public:
	Person() : Age(0), Name("")
	{
	}

	Person(const Person& person) 
	{ 
		Age = person.Age;
		Name = person.Name;
	}

	Person(int age, string name)
	{
		this->Age = age;
		this->Name = name;
	}

	string getName()
	{
		return this->Name;
	}

	int getAge()
	{
		return this->Age;
	}
};

