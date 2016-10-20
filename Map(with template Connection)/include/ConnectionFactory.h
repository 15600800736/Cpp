

//ConnectionFactory.h
#include "Relation.h"
#include "Connection.h"
namespace graphic
{
class ConnectionFactory
{
public:
	enum connectionType{ simpleConnection };
	static Relation* RelationcreateConnection(connectionType type)
	{
		Relation* relation;
		switch (type)
		{
		case simpleConnection:
			relation = new Connection()
		}
	}
};
}