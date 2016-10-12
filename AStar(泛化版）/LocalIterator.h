

//LocalIterator.h

#ifndef LOCAL_ITERATOR_H
#define LOCAL_ITERATOR_H
namespace huger
{
template < class nodeType >
class LocalIterator
{
	typedef typename nodeType::localIterator localIterator;
	nodeType operator*()
	{
		return **(*ptrIterator);
	}
	nodeType* operator->()
	{
		return *(*ptrIterator);
	}
	bool operator==(LocalIterator& other)
	{
		return *ptrIterator == other.ptrIterator;
	}
	bool operator!=(LocalIterator& other)
	{
		return *ptrIterator != other.ptrIterator;
	}
	LocalIterator operator++()
	{
		(*ptrIterator)++;
	}
	LocalIterator operator++(int)
	{
		++(*ptrIterator);
	}
	LocalIterator operator--()
	{
		(*ptrIterator)--;
	}
	LocalIterator operator--(int)
	{
		--(*ptrIterator);
	}
protected:
	LocalIterator* ptrIterator;
};
}

#endif