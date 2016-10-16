


//	RelationFactory.h
namespace huger
{
template<typename RelationType>
class RelationFactory
{
	typedef typename RelationType::firstType firstType;
	typedef typename RelationType::secondType secondType;
	typedef typename RelationType::valueType valueType;
public:
	bool createRelationBetween(firstType* firstObject, secondType* secondObject,valueType value)
	{

	}
};
}