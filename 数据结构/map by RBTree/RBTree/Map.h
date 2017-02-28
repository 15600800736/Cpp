
//ºìºÚÊ÷Àà

//RBTree.h

//--------------

#pragma once

#include "RBNode.h"
#include "Iterator.h"

//Declare Class CMap
//CMap
//CMap is a kv data structure.It realize with RBTree.The data is visited by key(include inserting,removing and searching)
//CMap has two forms to pass the information to insert the node,one is combining key and data in CPair,the other is offering them partly.
//CMap offers a interface to loop through with an external function

template < class K, class D >class CMap
{
public:

	//iterator
	typedef typename CMapIterator<K, D> iterator;

	//basic function
	//Insert a node in the tree,the position is depend on the key

	//overloading:insert a node in the tree
	//Insert a node by being offerd key and data partly
	//It will create a node object as a parameter to call another version
	//It will return a CPair contains a iterator pointing to the new node and a boolean variable to show if the insertion successful
	CPair<iterator, bool> Insert(K k, D d)
	{
		CRBNode<K, D> n(k,d);
		return Insert(n);
	}

	//Insert a node by being offerd a pair contains a key and data partly
	//It will create a node object as a parameter to call another version
	//It will return a CPair contains a iterator pointing to the new node and a boolean variable to show if the insertion successful
	CPair<iterator, bool> Insert(CPair<K, D> pair)
	{
		CRBNode<K, D> n(pair);
		return Insert(n);
	}

	//
	CPair<Node(K,D),bool> Erase(K);//return success of fail and the succeed
	CPair<iterator,bool> Find(K);
	template<class VST>void Travel(VST visit);//visit every node with the function
	int Clear();//delete all the nodes


	//Only Read
	iterator GetBegin()const{ return *m_begin; }
	iterator GetEnd()const{ return *m_end; }
	Node(K, D) GetRoot()const{ return m_root; }
	int GetSize()const{ return m_size; }
	bool IsEmpty()const{ return !m_size; }//empty or not,if it's empty , return true.if not, return the begin and false

	//operator overloading
	const D& operator[](K);

	//constructor
	CMap():m_root(NULL),m_begin(NULL),m_end(NULL),m_size(0),m_height(0){};//empty tree
	explicit CMap(D data) :m_size(1)
	{
		m_root = new CRBNode<K, D>(data);
		m_root->SetColor(Black);
		m_root->SetHeight(1);
		m_begin = new CMapIterator<K, D>(m_root);
		m_end = new CMapIterator<K, D>(m_root);
		m_height = m_root->GetHeight();
	}
	explicit CMap(K key, D data) :m_size(1)
	{
		m_root = new CRBNode<K, D>(data, key);
		m_root->SetColor(Black);
		m_root->SetHeight(1);
		m_begin = new CMapIterator<K, D>(m_root);
		m_end = new CMapIterator<K, D>(m_root);
	}
	explicit CMap(Node(K, D) r) :m_root(r), m_size(1)
	{ 
		m_root->SetColor(Black);//to promise the color of root is black}//empty tree with only a root
		m_root->SetHeight(1);
		m_begin = new CMapIterator<K, D>(m_root);
		m_end = new CMapIterator<K, D>(m_root);
		m_height = m_root->GetHeight();
	}
	explicit CMap(D*,int);//construct by array of D

	virtual ~CMap();
protected:
	//functions
	void UpdateSize(Node(K, D));//update the size of node over the node
	CPair<Node(K, D), Node(K, D)> Remove(Node(K, D));//return the actual node removed and its succ
	void Release(Node(K, D));
	void DoubleRed(Node(K, D));
	void DoubleBlack(Node(K, D),Node(K,D));
	void UpdateHeight(Node(K, D));
	Node(K,D) ConnectThreeFour(Node(K, D));
	Node(K, D) ConnectThreeFour(Node(K, D), Node(K, D), Node(K, D),
		Node(K, D), Node(K, D), Node(K, D), Node(K, D));
	CPair<iterator, bool>InsertAsRoot(CRBNode<K,D>);
	CPair<iterator, bool> Insert(CRBNode<K, D>);
	int Clear(Node(K, D));//overload: delete the tree below the node

	//variables
	Node(K,D) m_root;//node of root
	iterator* m_begin;
	iterator* m_end;
	int m_size;
	int m_height;//the black height of whole tree
};


//Def
template<class K, class D>
CPair<CMapIterator<K,D>, bool> CMap<K, D>::Find(K key)
{
	Node(K, D) target = m_root;
	bool success = true;
	while (target->GetKey() != key)
	{
		if (target->GetKey() > key)//aseert 'key' has order
		{
			if (target->GetLC() == NULL)
			{
				success = false;
				break;
			}
			else target = target->GetLC();//turn to left child
		}
		else
		{
			if (target->GetRC() == NULL)
			{
				success = false;
				break;
			}
			else target = target->GetRC();//turn to right child
		}
	}
	iterator it(target);
	CPair<iterator, bool> pair(it, success);
	return pair;
}

template<class K,class D>
CPair<CMapIterator<K, D>, bool> CMap<K, D>::Insert(CRBNode<K,D> n)
{
	if (IsEmpty())
	{
		m_size++; return InsertAsRoot(n);
	}
	else
	{
		Node(K, D) node = new CRBNode<K, D>(n);
		CPair<iterator, bool> f = Find(node->GetKey());
		if (f.second)
		{
			f.second = false;//if key  already exits,It means insert fail,return the iterator to the node
			return f;
		}
		node->SetParent(*f.first);
		if (node->GetKey() > (*f.first)->GetKey())
		{
			(*f.first)->SetRC(node);
		}
		else
		{
			(*f.first)->SetLC(node);
		}
		DoubleRed(node);//sovle the double red problem
		f.first = iterator(node);
		f.second = true;
		m_size++;
		if (node->GetKey() < m_begin->GetNode()->GetKey())
		{
			delete m_begin;
			m_begin = new CMapIterator<K, D>(f.first);
		}
		else if (node->GetKey() > m_end->GetNode()->GetKey())
		{
			delete m_end;
			m_end = new CMapIterator<K, D>(f.first);
		}
		return f;
	}
}

template<class K,class D>
void CMap<K, D>::DoubleRed(Node(K, D) node)
{
	if (node == m_root)
	{
		node->SetColor(Black);
		m_root->SetHeight(m_root->GetHeight() + 1);
		m_height = m_root->GetHeight();
	}
	else
	{
		Node(K, D) parent = node->GetParent();
		Node(K, D) grand = parent->GetParent();

		//case 1:
		//the color of father is black
		if (parent->GetColor() == Black) return;
		//case 2:
		//the color of father is red and the color of uncle is red
		else if (parent->GetColor() == Red)
		{
			Node(K, D) uncle = UNCLE(node);
			if (uncle->GetColor() == Red)
			{
				parent->SetColor(Black); parent->SetHeight(parent->GetHeight() + 1);
				uncle->SetColor(Black); uncle->SetHeight(uncle->GetHeight() + 1);
				grand->SetColor(Red);
				//UpdateAboveHeight(node);
				DoubleRed(grand);
			}
			else if (uncle->GetColor() == Black)
			{
				Node(K, D) root = ConnectThreeFour(node);
				root->SetColor(Black); root->SetHeight(root->GetHeight() + 1);
				if(!ISRED(root->GetLC()))
					root->GetLC()->SetHeight(root->GetLC()->GetHeight() - 1); 
				root->GetLC()->SetColor(Red);
				if (!ISRED(root->GetRC()))
					root->GetRC()->SetHeight(root->GetRC()->GetHeight() - 1);
				root->GetRC()->SetColor(Red);
			}
		}
	}
}

template<class K,class D>
CMap<K, D>::CMap(D* Array,int n)
{
	int tmp = 0;
	m_root = new CRBNode<K, D>(Array[0], static_cast<K>(tmp));
	m_root->SetColor(Black);
	m_root->SetHeight(1);
	m_begin = new CMapIterator<K, D>(m_root);
	m_end = new CMapIterator<K, D>(m_root);
	for (int i = 1; i < n; i++)
	{
		Insert(static_cast<K>(i), Array[i]);
	}
	m_size = n;
	m_height = m_root->GetHeight();
}

//code refactoring!!!!!!!!
template<class K,class D>
Node(K, D) CMap<K, D>::ConnectThreeFour(Node(K, D) a, Node(K, D) b, Node(K, D) c,
	Node(K, D) ta_l, Node(K, D) ta_r, Node(K, D) tc_l, Node(K, D) tc_r)
{
	b->SetLC(a);
	a->SetParent(b);

	b->SetRC(c);
	c->SetParent(b);

	a->SetLC(ta_l);
	if (ta_l)ta_l->SetParent(a);

	a->SetRC(ta_r);
	if (ta_r)ta_r->SetParent(a);

	c->SetLC(tc_l);
	if (tc_l)tc_l->SetParent(c);

	c->SetRC(tc_r);
	if (tc_r)tc_r->SetParent(c);

	return b;
}
template<class K,class D>
Node(K, D) CMap<K, D>::ConnectThreeFour(Node(K, D) x)
{
	//get three nodes and four trees
	Node(K, D) p = x->GetParent();
	Node(K, D) g = p->GetParent();
	Node(K, D) tree1 = BROTHER(p);
	Node(K, D) tree2 = BROTHER(x);
	Node(K, D) tree3 = SAMESIDECHILD(x);
	Node(K, D) tree4 = DIFFSIDECHILD(x);
	//if x and p on the same side.
	if (ISLC(x) && ISLC(p))
	{
		p->SetParent(g->GetParent());
		if (g == m_root)m_root = p;
		else REPLACE(g, p);
		return  ConnectThreeFour(x, p, g, tree3, tree4, tree2, tree1);
	}
	else if (ISRC(x) && ISRC(p))
	{
		p->SetParent(g->GetParent());
		if (g == m_root)m_root = p;
		else REPLACE(g, p);
		return ConnectThreeFour(g, p, x, tree1, tree2, tree4, tree3);
	}
	//if x and p on the different side
	else if (ISRC(x) && ISLC(p))
	{
		x->SetParent(g->GetParent());
		if (g == m_root)m_root = x;
		else REPLACE(g, p);
		return ConnectThreeFour(p, x, g, tree2, tree4, tree3, tree1);
	}
	else if (ISLC(x) && ISRC(p))
	{
		x->SetParent(g->GetParent());
		if (g == m_root)m_root = x;
		else REPLACE(g, p);
		return ConnectThreeFour(g, x, p, tree1, tree3, tree4, tree2);
	}
	else return x;
}

template<class K, class D>template<class VST>
void CMap<K, D>::Travel(VST visit)
{
	Node(K, D) x = m_root;
	//Go to the most left
	while (HAVELC(x))
		x = x->GetLC();
	while (x)
	{
		visit(x);
		x = x->GetSucc();
	}
}

template<class K, class D>
void CMap<K, D>::Release(Node(K, D) node)
{
	node->SetParent(NULL);
	node->SetLC(NULL);
	node->SetRC(NULL);
	node->SetKey(NULL);
	node->SetData(NULL);
	node->SetColor(Red);
	node->SetHeight(0);
	delete node;
}

template<class K, class D>
CPair<Node(K, D), bool> CMap<K, D>::Erase(K key)//return the father of actual node removed and its succ
{
	CPair<iterator, bool> f = Find(key);
	CPair<Node(K, D), bool> result(NULL, false);
	if (!f.second)
	{
		return result;
	}
	result.second = true;
	Node(K, D) node = *(f.first);
	CPair<Node(K, D), Node(K, D)> pair = Remove(node);
	if (IsEmpty())return result;
	Node(K, D) a_parent = pair.first;
	Node(K, D) replace = pair.second;
	result.first = replace;
	if (!a_parent)//this means the node has been removed is the root
	{
		if (ISRED(m_root))
		{
			m_root->SetColor(Black);
			//HEIGHT?
		}
		return result;
	}
	if (BALANCE(a_parent))
		return result;
	if (replace && ISRED(replace))
	{
		replace->SetColor(Black);
		replace->SetHeight(replace->GetHeight() + 1);
		return result;
	}
	DoubleBlack(replace,a_parent);

	//Can Clear(node) repalce it?
	Release(node);
	return result;
}

template<class k,class d>CMap<k,d>::~CMap()
{
	if (m_root)
	{
		Clear();
		m_root = NULL;
		m_begin = NULL;
		m_end = NULL;
		m_size = 0;
		m_height = 0;
	}
	else
		return;
}

template<class K, class D>
CPair<Node(K, D), Node(K, D)> CMap<K, D>::Remove(Node(K, D) node)
{
	Node(K, D) replace = NULL;
	Node(K, D) a_parent = node->GetParent();

	if (node == **m_begin)
	{
		delete m_begin;
		m_begin = new CMapIterator<K, D>(node->GetSucc());
	}
	if (node == **m_end)
	{
		delete m_end;
		m_end = new CMapIterator<K, D>(node->GetFore());
	}
	//remove
	if (!HAVELC(node) && HAVERC(node))
	{
		replace = node->GetRC();
		//swap
		replace->SetParent(node->GetParent());
		if (node == m_root) m_root = replace;
		else 		REPLACE(node, replace);
	}
	else if (!HAVERC(node) && HAVELC(node))
	{
		replace = node->GetLC();
		//swap
		replace->SetParent(node->GetParent());
		if (node == m_root) m_root = replace;
		else 		REPLACE(node, replace);
	}
	else if (ISLEAF(node) && !ISROOT(node))
		REPLACE(node, NULL);
	else if (ISLEAF(node) && ISROOT(node))
		m_root = NULL;
	//update m_begin & m_end;
	else
	{
		Node(K,D) succ = node->GetSucc();
		Node(K, D) actual_deleted = succ;

		//if node's succ's parent,then node is the actual node deleted
		if (succ->GetParent() == node)
		{
			actual_deleted = node;
		}

		//record information
		replace = actual_deleted->GetRC();
		a_parent = actual_deleted->GetParent();

		//swap and remove
		//from child
		succ->SetLC(node->GetLC());
		node->GetLC()->SetParent(succ);
		if (succ->GetParent() != node)
		{
			succ->SetRC(node->GetRC());
			node->GetRC()->SetParent(succ);

			a_parent->SetLC(replace);
			replace->SetParent(a_parent);
		}

		//from parent
		succ->SetParent(node->GetParent());
		if (node == m_root)m_root = succ;
		else REPLACE(node, succ);
	}
	m_size--;
	CPair<Node(K, D), Node(K, D)> result(a_parent, replace);
	return result;
}

template<class K, class D>int CMap<K, D>::Clear()
{
	return Clear(m_root);
}
template<class K, class D>int CMap<K, D>::Clear(Node(K, D) node)
{
	if (!node) return 0;
	Node(K, D) lc = node->GetLC();
	Node(K, D) rc = node->GetRC();
	delete node;
	Clear(lc);
	Clear(rc);
}
template<class K,class D>
CPair<CMapIterator<K,D>, bool> CMap<K, D>::InsertAsRoot(CRBNode<K,D> n)
{
	m_root = new CRBNode<K, D>(n);
	m_root->SetColor(Black);
	m_root->SetHeight(1);
	m_begin = new CMapIterator<K, D>(m_root);
	m_end = new CMapIterator<K, D>(m_root);
	m_size = 1;
	m_height = m_root->GetHeight();
	iterator it(m_root);
	CPair<iterator, bool> ret(it, true);
	return ret;
}
template<class K,class D>
void CMap<K, D>::DoubleBlack(Node(K, D) replace,Node(K,D) a_parent)
{
	if (a_parent)
	{
		Node(K, D) brother = BROTHER(replace);
		if (!ISRED(brother))
		{
			Node(K, D) nephew = GETREDCHILD(brother);
			if (nephew)
			{
				Node(K, D) grand = a_parent->GetParent();
				Color oldcolor = a_parent->GetColor();
				Node(K, D) new_parent = ConnectThreeFour(nephew);
				grand ? (REPLACE(a_parent, new_parent)) : (m_root = new_parent);
				new_parent->SetColor(oldcolor);
				if (HAVELC(new_parent))
					new_parent->GetLC()->SetColor(Black);
				if (HAVERC(new_parent))
					new_parent->GetRC()->SetColor(Black);
				/*UpdateHeight(new_parent);*/
			}
			else
			{
				nephew->SetColor(Red);
				if (ISRED(a_parent))
					a_parent->SetColor(Black);
				else
				{
					a_parent->SetHeight(a_parent->GetHeight() - 1);
					DoubleBlack(a_parent, a_parent->GetParent());
				}

			}
		}
		else
		{
			brother->SetColor(Black);
			a_parent->SetColor(Red);
			brother->SetParent(a_parent->GetParent());
			a_parent->SetParent(brother);
			if (ISLC(brother))
			{
				brother->SetRC(a_parent);

				a_parent->SetLC(brother->GetRC());
				if (brother->GetRC()) brother->GetRC()->SetParent(a_parent);
			}
			else
			{
				brother->SetLC(a_parent);

				a_parent->SetRC(brother->GetLC());
				if (brother->GetLC())brother->GetLC()->SetParent(a_parent);
			}
			DoubleBlack(replace,a_parent);
		}
	}

}
template<class K,class D>
void CMap<K, D>::UpdateHeight(Node(K, D) node)
{
	if (!node) return;
	node->SetHeight(ISRED(node) ?
		max(HEIGHT(node->GetLC()->GetHeight()), HEIGHT(node->GetRC()->GetHeight())) : 
		max(HEIGHT(node->GetLC()->GetHeight()), HEIGHT(node->GetRC()->GetHeight())) + 1);
	Node(K, D) p = node->GetParent();
	UpdateHeight(p);
}
template<class K,class D>
void CMap<K, D>::UpdateSize(Node(K, D) node)
{

}