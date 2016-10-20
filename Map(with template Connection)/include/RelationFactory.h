

//ConnectionFactory.h
#include "Relation.h"
#include "Connection.h"
namespace graphic
{
/*
 *	
 *	Create an empty relation
 *	you should 
 */
class RelationFactory
{
public:
	enum relationType{ simpleConnection };
	static Relation* createRelation(relationType type)
	{
		Relation* relation;
		switch (type)
		{
		case simpleConnection:
			relation = new Connection();
			break;
		default:
			relation =  NULL;
			break;
		}
		return relation;
	}
	static void destroyRelation(Relation* relation)
	{
		if (relation != NULL)
		{
			delete relation;
		}
	}
};
}