

//NodeIterator.h

/*
 *
 *	This class is the iterator for Node.
 *	It redefines the passed iterator's operator* and operator->
 *	to make the iterator which points to the address of elements points
 *	to the elements.
 *	In addition to these two operator,all the other operating like++ and-- will be on the original iterator.
 *	Class overloads operator= to make an NodeIterator obeject can be assigned by it's member-the original object.
 *
 */
#ifndef LOCAL_ITERATOR_H
#define LOCAL_ITERATOR_H
namespace huger
{
template <typename nodeType,typename iteratorType>
class NodeIterator
{
public:
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-NodeIterator constructor
	//	-Create a empty NodeIterator
	NodeIterator() :_iterator(NULL)
	{
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-NodeIterator constructor
	//	-Create a NodeIterator with a list<T*>::iterator
	NodeIterator(iteratorType iterator) :_iterator(iterator)
	{
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-overload operator*
	//	-return value of the address in list
	nodeType operator*()
	{
		return *(*_iterator);
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-overload operator->
	//	-return the address in list
	nodeType* operator->()
	{
		return *_iterator;
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-overload operator==
	//	-return if this iterator equals another one
	//	@parameter other - other iterator
	bool operator==(NodeIterator& other)
	{
		return _iterator == other._iterator;
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-overload operator!=
	//	-return if this iterator doesn't	equal another one
	//	@parameter other - other iterator
	bool operator!=(NodeIterator& other)
	{
		return _iterator != other._iterator;
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-overload operator==
	//	-return if the list::iterator member equals the other list::iterator
	//	@parameter other - other list::iterator
	bool operator==(iteratorType& otherLoc)
	{
		return _iterator == otherLoc;
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-overload operator!=
	//	-return if the list::iterator member doesn't equal the other list::iterator
	//	@parameter other - other list::iterator
	bool operator!=(iteratorType& other)
	{
		return _iterator != other;
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-overload operator=
	//	-assinged by another NodeIterator
	//	@parameter other - source
	NodeIterator& operator=(const NodeIterator& other)
	{
		if (other == *this)
		{
			return *this;
		}
		_iterator = other._iterator;
		return *this;
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-overload operator=
	//	-assinged by another list::iterator
	//	@parameter other - source
	NodeIterator& operator=(const iteratorType& other)
	{
		_iterator = other;
		return *this;
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-overload operator++
	//	-return this iterator and make iterator point to next one
	NodeIterator operator++()
	{
		++_iterator;
		return *this;
	}	
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-overload operator++
	//	-return next iterator
	NodeIterator operator++(int)
	{
		NodeIterator result = _iterator++;
		return result;
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-overload operator++
	//	-return this iterator and make iterator point to last one
	NodeIterator operator--()
	{
		--_iterator;
		return *this;
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//	-overload operator++
	//	-return last iterator
	NodeIterator operator--(int)
	{
		NodeIterator result = _iterator--;
		return result;
	}
protected:
	iteratorType _iterator;
};
}

#endif
