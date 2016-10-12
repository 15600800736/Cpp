

//NodeIterator.h

#ifndef LOCAL_ITERATOR_H
#define LOCAL_ITERATOR_H
namespace huger
{
template <typename nodeType,typename iteratorType>
class NodeIterator
{
public:
	NodeIterator() :_iterator(NULL)
	{
	}
	NodeIterator(iteratorType ptrIterator) :_iterator(ptrIterator)
	{
	}
	nodeType operator*()
	{
		return *(*_iterator);
	}
	nodeType* operator->()
	{
		return *_iterator;
	}
	bool operator==(NodeIterator& other)
	{
		return _iterator == other._iterator;
	}
	bool operator!=(NodeIterator& other)
	{
		return _iterator != other._iterator;
	}
	bool operator==(iteratorType& otherLoc)
	{
		return _iterator == otherLoc;
	}
	bool operator!=(iteratorType& otherLoc)
	{
		return _iterator != otherLoc;
	}
	NodeIterator& operator=(const NodeIterator& other)
	{
		if (other == *this)
		{
			return *this;
		}
		_iterator = other._iterator;
		return *this;
	}
	NodeIterator& operator=(const iteratorType& otherLoc)
	{
		_iterator = otherLoc;
		return *this;
	}
	iteratorType operator++()
	{
		return _iterator++;
	}
	iteratorType operator++(int)
	{
		return ++_iterator;
	}
	iteratorType operator--()
	{
		return _iterator--;
	}
	iteratorType operator--(int)
	{
		return --_iterator;
	}
protected:
	iteratorType _iterator;
};
}

#endif
