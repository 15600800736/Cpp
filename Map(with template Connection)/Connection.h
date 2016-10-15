

//Connection.h
#ifndef CONNECTION_H
#define CONNECTION_H
#include "Relation.h"

namespace huger
{
template<typename Object>
class Connection :public Relation<Object,int>
{
public:
	typedef Relation::dataType dataType;
	typedef Relation::object object;


protected:
	
};
}
#endif
