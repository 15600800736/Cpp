

//NodeIterator.h

#ifndef LOCAL_ITERATOR_H
#define LOCAL_ITERATOR_H
namespace huger
{
template < class nodeType >
class NodeIterator
{
	typedef typename nodeType::localIterator localIterator;
public:
	NodeIterator() :_iterator(NULL)
	{
	}
	NodeIterator(localIterator ptrIterator) :_iterator(ptrIterator)
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
	bool operator==(localIterator& otherLoc)
	{
		return _iterator == otherLoc;
	}
	bool operator!=(localIterator& otherLoc)
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
	NodeIterator& operator=(const localIterator& otherLoc)
	{
		_iterator = otherLoc;
		return *this;
	}
	localIterator operator++()
	{
		return _iterator++;
	}
	localIterator operator++(int)
	{
		return ++_iterator;
	}
	localIterator operator--()
	{
		return _iterator--;
	}
	localIterator operator--(int)
	{
		return --_iterator;
	}
protected:
	localIterator _iterator;
};
}

#endif