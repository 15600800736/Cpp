#pragma once

enum BColor{B_RED,B_BLACK};
#define NULL 0;
#define Hei(p) p?p->height:-1;
#define BinNodeRe(T) CBinNode<T>*
#define IsRoot(x) !(x.parent) 
#define IsLc(x) !IsRoot(x) && (&x == x.parent->lc)
#define IsRc(x) !IsRoot(x) && (&x == x.parent->rc)
#define HasLc(x) x.lc
#define HasRc(x) x.rc
#define HasChild(x) HasLc(x)||HasRc(x)
#define HasBothChild(x) HasLc(x)&&HasRc(x)
#define IsLeaf(x) !HasChild(x)
#define Brother(p) (IsLc(*p)) ? p->parent->rc:p->parent->rc
#define Uncle(p) (!IsRoot(*p)) ?¡¡(IsLc(x)?£ð->parent->parent->rc:p->parent->parent->lc):-1
#define FromParent(x) IsRoot(x)?_root:(IsLc(x) ? x.parent->lc:x.parent->rc)
