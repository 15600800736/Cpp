

//LocalIter.h


namespace huger
{

template<class nodeType>
class LocalIterator
{
	typedef typename nodeType::orderType orderType;
	typedef typename nodeType::distanceType distanceType;
	typedef typename nodeType valueType;
	typedef typename nodeType* pointerType;
	typedef typename nodeType& referenceType;
	typedef LocalIterator category;

	LocalIterator(pointerType node);
	LocalIterator(const LocalIterator& otherIterator);

	category operator++();
	category operator++(int);
	category operator--();
	category operator--(int);
	bool operator==(const LocalIterator& otherIterator);
	bool operator!=(const LocalIterator& otherIterator);
protected:
	pointerType _node;
};
}