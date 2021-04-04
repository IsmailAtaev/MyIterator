#pragma once
/// <summary>
/// ///set ups
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class Queue;

template<typename T>
class IIterator
{
public:
	virtual void reset() = 0;

	virtual T getCurrent() = 0;

	virtual bool moveNext() = 0;

	~IIterator() { }
};


template<typename T>
class IIterable
{
public:
	virtual IIterator<T>* getIterator() = 0;
};



// Custom Iterator
template<typename T>
class CustomIterator : public IIterator<T>
{
private:
	int _reset = -1;
	Queue<T>* _queue;
	T _current;
public:
	CustomIterator(Queue<T>* queue)
	{
		this->_queue = queue;
	}

	void reset() override
	{
		this->_reset = -1;
	}

	bool moveNext() override
	{
		this->_reset++;
		if (this->_reset > this->_queue->GetSize() - 1)
		{
			return false;
		}

		this->_current = (*_queue)[this->_reset];
	}

	T getCurrent() override
	{
		return this->_current;
	}
};













// IterateByPredicate

template<typename T>
class IterateByPredicate : public IIterator<T>
{
private:
	IIterator<T>* _iterator;
	bool (*_predicate)(T);
	T current;
public:
	IterateByPredicate(IIterable<T>* iterable, bool (*predicate)(T))
	{
		this->_iterator = iterable->getIterator();
		this->_predicate = predicate;
	}

	bool moveNext() override
	{
		bool passed = this->_iterator->moveNext();
		if (!passed)
		{
			return passed;
		}

		while (!this->_predicate(this->_iterator->getCurrent()))
		{
			passed = this->_iterator->moveNext();
			if (!passed)
			{
				return passed;
			}
		}

		this->current = this->_iterator->getCurrent();
		return true;
	}

	T getCurrent() override
	{
		return this->current;
	}

	void reset() override
	{
		this->_iterator->reset();
	}

	~IterateByPredicate()
	{
		delete this->_iterator;
	}
};
