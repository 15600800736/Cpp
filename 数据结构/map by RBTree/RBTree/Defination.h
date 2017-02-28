
//Defination.h
#pragma once
#include <iostream>
using namespace std;



#define Node(K,D) CRBNode<K,D>*
#define HEIGHT(x) ((x) ? (x)->GetHeight() : 0)
#define max(a,b) ((a) > (b) ? (a) : (b))
#define ISROOT(x) (!((x)->GetParent()))
#define ISLC(x) ((x) == (x)->GetParent()->GetLC())
#define ISRC(x) ((x) == (x)->GetParent()->GetRC())
#define HAVELC(x) (x->GetLC() ? 1 : 0)
#define HAVERC(x) (x->GetRC() ? 1 : 0)
#define HAVECHILD(x) (HAVELC(x) || HAVERC(x))
#define FROMPARENT(x) (ISLC(x) ? x->GetParent()->GetLC() : x->GetParent()->GetRC())
#define BROTHER(x) (ISLC(x) ? x->GetParent()->GetRC() : x->GetParent()->GetLC())
#define UNCLE(x) (BROTHER((x)->GetParent()))
#define ISLEAF(x) (!HAVECHILD(x))
//return the same side child
#define SAMESIDECHILD(x) (ISLC(x) ? x->GetLC() : x->GetRC())
#define DIFFSIDECHILD(x) (ISLC(x) ? x->GetRC() : x->GetLC())
//from parent replace x with y
#define REPLACE(x,y) (ISLC(x) ? x->GetParent()->SetLC(y) : x->GetParent()->SetRC(y))
#define ISRED(x) ((x)->GetColor() == Red)
#define BALANCE(x) (HEIGHT((x)->GetLC()) == HEIGHT((x)->GetRC()) && \
	HEIGHT(x) == ISRED(x) ? HEIGHT((x)->GetLC()) : HEIGHT((x)->GetLC()) + 1)
//Get node's red child ,the left child first
#define GETREDCHILD(x) (ISRED((x)->GetLC()) ? (x)->GetLC() : \
(ISRED((x)->GetRC()) ? (x)->GetRC() : NULL))
//Get node's black child,the left child first
//#define GETBLACKCHILD(x) ((!ISRED((x)->GetLC())) ? (x)->GetLC() : \
//((!ISRED((x)->GetRC())) ? (x)->GetRC() : NULL)
enum Color{ Red, Black };