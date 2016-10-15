

//Relation.h

namespace huger
{
template<typename Object,typename DataType>
class Relation
{
public:
	typedef typename DataType dataType;
	typedef typename Object object;
	Relation(Object firstOjbect, 
		Object secondOjbect,
		dataType data) :
		_firstOjbect(firstOjbect), 
		_secondObject(secondOjbect),
		_data(data)
	{
	}
	virtual dataType getData()const = 0;
	virtual void setData(dataType data) = 0;
	virtual ~Relation()
	{
	}
protected:
	object _firstObject;
	object _secondObject;
	dataType _data;
};
}