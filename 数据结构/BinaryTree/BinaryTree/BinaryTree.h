
#pragma once
#include "Node.h"
#include "..\栈\栈\Stack.h"
#define max(a,b) ((a)>=(b) ? (a):(b))
#define min(a,b)  ((a) < (b) ? (a):(b))
#define HEIGHT(x) ((x) ? x->GetHeight() : -1)//高度统一化，定义NULL的高度为-1
#define SIZE(x) ((x) ? x->GetSize() : 0)//规模统一化，定义NULL的规模为0
//--------------------------------------------------------------
#define HAVELC(x) (x->GetLc())
#define HAVERC(x) (x->GetRc())
#define HAVEBOTHCHILD(x) (HAVELC(x)&&HAVERC(x))
#define HAVECHILD(x) (HAVELC(x) || HAVERC(x))
#define ISLC(x) (!ISROOT(x) && (x == x->GetParent()->GetLc()))
#define ISRC(x) (!ISROOT(x) && (x == x->GetParent()->GetRc()))
#define ISLEAF(x) (!HAVECHILD(x))
#define ISROOT(x) !(x->GetParent())
#define BROTHER(x) (ISLC(x) ? x->GetParent()->GetRc() : x->GetParent()->GetLc())
#define GRAND(x) (x->GetParent()->GetParent())
#define UNCLE(x) (BROTHER(x->GetParent()))
#define FROMPARENTTOONESELF(x) (ISLC(x) ? x->GetParent()->GetLc() : x->GetParent()->GetRc())
template<class T>class CBinaryTree
{
public:
	CBinaryTree(int h = 0, int s = 1);
	~CBinaryTree();
	template<class VST>void PreTravel(VST&);//先序遍历
	template<class VST>void MidTravel(VST&);//中序遍历
	template<class VST>void PosTravel(VST&);//后序遍历
	T InsertAsLc(NodePos(T),const T);//左孩子插入
	T insertAsRc(NodePos(T), const T);//右孩子插入
	T InsertRoot(const T d);//插入根节点
	NodePos(T) InsertAsLt(NodePos(T),CBinaryTree*);//左子树接入
	NodePos(T) InsertAsRt(NodePos(T),CBinaryTree*);//右子树接入
	int Remove(NodePos(T));//删除节点及节点下得子树（若存在） 并返回被删子树的规模
	CBinaryTree<T>* DivideTree(NodePos(T));//以x为根分离出一棵子树
	NodePos(T) Search(const T);//搜索
	void UpdateNodeHeight(NodePos(T));//更新x及其以上树高
	void UpdateNodeSize(NodePos(T));//更新x及其以上节点规模
	T Release(NodePos(T));//释放节点
	NodePos(T) succ(NodePos(T));//定位直接后继
	bool empty()const{ return m_size; }

	//只读
	inline int GetHeight()const{ return m_height; }
	inline int GetSize()const{ return m_size; }
	inline NodePos(T) GetRoot()const{ return m_root; }
	//可写
	inline void SetHeight(int h){ m_height = h; }
	inline void SetSize(int s){ m_size = s; }
	inline void SetRoot(NodePos(T) r){ m_root = r; }
private:
	NodePos(T) m_root;//根节点
	int m_height;//全树高
	int m_size;//规模
	//---------------------------------------
	template<class VST>void VisittoLL_RCStack(NodePos(T),VST&,CStack<NodePos(T)>&);//一路向左到叶子，并把右节点入栈
	template<class VST>void GotoLL_Stack(NodePos(T), CStack<NodePos(T)>&);//一路向左到叶子，并把途径节点入栈
	template<class VST>void GotoLRL_StackRCStack(NodePos(T), CStack<NodePos(T)>&);//一路向左，不得已才向右，并把本身和右孩子入栈
};

//------------------------------------------------------------------实现
template<class T>template<class VST>void CBinaryTree<T>::GotoLL_Stack(NodePos(T) x, CStack <NodePos(T)>& stack)
{
	while (x)
	{
		stack.push(x);
		x = x->GetLc();
	}
}
template<class T>template<class VST>void CBinaryTree<T>::VisittoLL_RCStack(NodePos(T) x, VST& visit, CStack<NodePos(T)>& stack)
{
	while (x)
	{
		visit(x);//x? x->GetData?
		stack->push(x->GetRc());//右孩子入栈
		x = x->GetLc();
	}
}
template<class T>template<class VST>void CBinaryTree<T>::GotoLRL_StackRCStack(NodePos(T) x, CStack<NodePos(T)>& stack)
{
	while (1)
	{
		stack.push(x);
		if (HAVELC(x))
		{
			if (HAVERC(x)) stack.push(x->GetRc());
			x = x->GetLc();
		}
		else if (HAVERC(x) && (!HAVELC(x)))
		{
			x = x->GetRc();
		}
		else break;
	}

}
template<class T>CBinaryTree<T>::CBinaryTree(int h, int s) :m_height(h), m_size(s)//根为第0层
{
	m_root = new CNode<T>();
}
template<class T>CBinaryTree<T>::~CBinaryTree()//释放各个节点（遍历）
{

}
template<class T>T CBinaryTree<T>::InsertAsLc(NodePos(T) x, const T d)
{
	NodePos(T) lc = new CNode<T>(d, x);
	x->SetLc(lc);
	m_size++;
	UpdateNodeHeight(x);
	UpdateNodeSize(x);
	m_height = m_root->GetHeight();
	return d;
}
template<class T>T CBinaryTree<T>::insertAsRc(NodePos(T) x, const T d)
{
	NodePos(T) rc = new CNode<T>(d, x);
	x->SetRc(rc);
	m_size++;
	UpdateNodeHeight(x);
	UpdateNodeSize(x);
	m_height = m_root->GetHeight();
	return d;
}
template<class T>NodePos(T) CBinaryTree<T>::InsertAsLt(NodePos(T) x, CBinaryTree* tree)
{
	x->SetLc(tree->GetRoot());
	tree->GetRoot()->SetParent(x);
	m_size += tree->GetSize();
	UpdateNodeHeight(x);
	UpdateNodeSize(x);
	m_height = m_root->GetHeight();
	return m_root;//根据需要调整
}
template<class T>NodePos(T) CBinaryTree<T>::InsertAsRt(NodePos(T) x, CBinaryTree* tree)
{
	x->SetRc(tree->GetRoot());
	tree->GetRoot()->SetParent(x);
	m_size += tree - GetSize();
	x->m_height = 0;
	UpdateNodeHeight(x);
	UpdateNodeSize(x);
	m_height = m_root->GetHeight();
	return m_root;//根据需要调整
}
template<class T>void CBinaryTree<T>::UpdateNodeHeight(NodePos(T) x)
{
	while (x != m_root->GetParent())
	{
		x->SetHeight(max(HEIGHT(x->m_lc), HEIGHT(x->m_rc)) + 1);
		x = x->GetParent();
	}
	return;
}
template<class T>void CBinaryTree<T>::UpdateNodeSize(NodePos(T) x)
{
	while (x != m_root->GetParent())
	{
		x->SetSize(x->GetLc()->GetSize() + x->GetRc()->GetSize() + 1);//x的规模为左右孩子规模数+1
		x = x->GetParent();
	}
}
template<class T>T CBinaryTree<T>::Release(NodePos(T) x)
{
	x->SetData(NULL);
	x->SetHeight(-1);
	x->SetParent(NULL);
	x->SetLc(NULL);
	x->SetRc(NULL);
	delete x;
}
template<class T>int CBinaryTree<T>::Remove(NodePos(T) x)
{
	NodePos(T) p = x->GetParent();//记录父节点，以便高度更新
	CBinaryTree<T>* childtree = DivideTree(x);//分离子树
	int size = childtree->GetSize();
	delete childtree;//释放子树
	return size;
}
template<class T>CBinaryTree<T>* CBinaryTree<T>::DivideTree(NodePos(T) x)
{
	FROMPARENTTOONESELF(x) = NULL;
	UpdateNodeHeight(x->GetParent());//节点高度更新
	UpdateNodeSize(x->GetParent());//节点规模更新
	m_height = m_root->GetHeight();//全树高度更新
	m_size = m_root->GetSize();//全树规模更新
	x->SetParent(NULL);
	//构建新树
	CBinaryTree<T>* newtree = new CBinaryTree<T>();
	newtree->SetRoot(x);
	newtree->SetSize(x->GetSize());
	newtree->SetHeight(x->GetHeight());
	return newtree;
}

template<class T>template<class VST>void CBinaryTree<T>::PreTravel(VST& visit)
{
	CStack<NodePos(T)> stack;
	NodePos(T) x = m_root;
	while (1)
	{
		VisittoLL_RCStack(x, visit, stack);
		if (stack.empty())break;
		x = stack->pop();
	}
}
template<class T>template<class VST>void CBinaryTree<T>::MidTravel(VST& visit)
{
	CStack<NodePos(T)> stack;
	NodePos(T) x = m_root;
	while (1)
	{
		GotoLL_Stack(x, stack);
		if (stack.empty())break;
		x = stack.pop();
		visit(x);
		x = x->GetRc();
	}
}
template<class T>template<class VST>void CBinaryTree<T>::PosTravel(VST& visit)
{
	CStack<T> stack;
	NodePos(T) x = m_root;
	stack.push(x);
	while (!stack.empty())
	0
	{
		if (stack.top() != x->GetParent())
		{
			x = stack.pop();
			GotoLRL_StackRCStack(x, stack);
		}
		x = stack.pop();
		visit(x);
	} 
}

