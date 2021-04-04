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
		if (this->_reset >= this->_queue->GetSize())
			return false;
		this->_reset++;
		if (this->_reset >= this->_queue->GetSize())
		{
			return false;
		}

		this->_current = (*_queue)[this->_reset];

		return true;
	}

	T getCurrent() override
	{
		return this->_current;
	}
};



// Where
template<typename T>
class Where : public IIterator<T>
{
private:
	IIterator<T>* _iterator;
	bool (*_predicate)(T);
	T current;
public:
	Where(IIterator<T>* iterator, bool (*predicate)(T))
	{
		this->_iterator = iterator;
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

	~Where()
	{
	}
};

// Skip
template<typename T>
class Skip : public IIterator<T>
{
private:
	IIterator<T>* _iterator;
	bool _passed = false;
	int _countConst = 0;
	T current;
public:
	Skip(IIterator<T>* iterator, int count)
	{
		this->_iterator = iterator;
		this->_countConst = count;
	}

	bool moveNext() override
	{
		if (_passed)
		{
			if (this->_iterator->moveNext())
			{
				this->current = this->_iterator->getCurrent();
				return true;
			}
			else
			{
				return false;
			}
		}

		for (int i = 0; i <= _countConst; i++)
		{
			if (!this->_iterator->moveNext())
			{
				return false;
			}
		}

		_passed = true;
		this->current = this->_iterator->getCurrent();
		return true;
	}

	T getCurrent() override
	{
		return this->current;
	}

	void reset() override
	{
		_passed = false;
		this->_iterator->reset();
	}

	~Skip()
	{
	}
};


// Take

template<typename T>
class Take : public IIterator<T>
{
private:
	IIterator<T>* _iterator;
	int _count = 0;
	int _countConst = 0;
	T current;
public:
	Take(IIterator<T>* iterator, int count)
	{
		this->_iterator = iterator;
		this->_countConst = count;
	}

	bool moveNext() override
	{
		if (_count >= _countConst)
			return false;

		if (this->_iterator->moveNext())
		{
			_count++;
			this->current = this->_iterator->getCurrent();
		}
	}

	T getCurrent() override
	{
		return this->current;
	}

	void reset() override
	{
		this->_count = 0;
		this->_iterator->reset();
	}

	~Take()
	{
	}
};


// Select
template<typename TIn, typename TOut>
class Select : public IIterator<TOut>
{
private:
	IIterator<TIn>* _iterator;
	TOut _current;
	TOut(*_converter)(TIn);
public:
	Select(IIterator<TIn>* iterator, TOut (*converter)(TIn))
	{
		this->_iterator = iterator;
		this->_converter = converter;
	}

	void reset() override
	{
		this->_iterator->reset();
	}

	bool moveNext() override
	{
		if (this->_iterator->moveNext())
		{
			this->_current = this->_converter(this->_iterator->getCurrent());
			return true;
		}
		else
		{
			return false;
		}
	}

	TOut getCurrent() override
	{
		return this->_current;
	}
};

