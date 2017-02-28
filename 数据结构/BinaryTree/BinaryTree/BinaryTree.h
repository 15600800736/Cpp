
#pragma once
#include "Node.h"
#include "..\ջ\ջ\Stack.h"
#define max(a,b) ((a)>=(b) ? (a):(b))
#define min(a,b)  ((a) < (b) ? (a):(b))
#define HEIGHT(x) ((x) ? x->GetHeight() : -1)//�߶�ͳһ��������NULL�ĸ߶�Ϊ-1
#define SIZE(x) ((x) ? x->GetSize() : 0)//��ģͳһ��������NULL�Ĺ�ģΪ0
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
	template<class VST>void PreTravel(VST&);//�������
	template<class VST>void MidTravel(VST&);//�������
	template<class VST>void PosTravel(VST&);//�������
	T InsertAsLc(NodePos(T),const T);//���Ӳ���
	T insertAsRc(NodePos(T), const T);//�Һ��Ӳ���
	T InsertRoot(const T d);//������ڵ�
	NodePos(T) InsertAsLt(NodePos(T),CBinaryTree*);//����������
	NodePos(T) InsertAsRt(NodePos(T),CBinaryTree*);//����������
	int Remove(NodePos(T));//ɾ���ڵ㼰�ڵ��µ������������ڣ� �����ر�ɾ�����Ĺ�ģ
	CBinaryTree<T>* DivideTree(NodePos(T));//��xΪ�������һ������
	NodePos(T) Search(const T);//����
	void UpdateNodeHeight(NodePos(T));//����x������������
	void UpdateNodeSize(NodePos(T));//����x�������Ͻڵ��ģ
	T Release(NodePos(T));//�ͷŽڵ�
	NodePos(T) succ(NodePos(T));//��λֱ�Ӻ��
	bool empty()const{ return m_size; }

	//ֻ��
	inline int GetHeight()const{ return m_height; }
	inline int GetSize()const{ return m_size; }
	inline NodePos(T) GetRoot()const{ return m_root; }
	//��д
	inline void SetHeight(int h){ m_height = h; }
	inline void SetSize(int s){ m_size = s; }
	inline void SetRoot(NodePos(T) r){ m_root = r; }
private:
	NodePos(T) m_root;//���ڵ�
	int m_height;//ȫ����
	int m_size;//��ģ
	//---------------------------------------
	template<class VST>void VisittoLL_RCStack(NodePos(T),VST&,CStack<NodePos(T)>&);//һ·����Ҷ�ӣ������ҽڵ���ջ
	template<class VST>void GotoLL_Stack(NodePos(T), CStack<NodePos(T)>&);//һ·����Ҷ�ӣ�����;���ڵ���ջ
	template<class VST>void GotoLRL_StackRCStack(NodePos(T), CStack<NodePos(T)>&);//һ·���󣬲����Ѳ����ң����ѱ�����Һ�����ջ
};

//------------------------------------------------------------------ʵ��
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
		stack->push(x->GetRc());//�Һ�����ջ
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
template<class T>CBinaryTree<T>::CBinaryTree(int h, int s) :m_height(h), m_size(s)//��Ϊ��0��
{
	m_root = new CNode<T>();
}
template<class T>CBinaryTree<T>::~CBinaryTree()//�ͷŸ����ڵ㣨������
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
	return m_root;//������Ҫ����
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
	return m_root;//������Ҫ����
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
		x->SetSize(x->GetLc()->GetSize() + x->GetRc()->GetSize() + 1);//x�Ĺ�ģΪ���Һ��ӹ�ģ��+1
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
	NodePos(T) p = x->GetParent();//��¼���ڵ㣬�Ա�߶ȸ���
	CBinaryTree<T>* childtree = DivideTree(x);//��������
	int size = childtree->GetSize();
	delete childtree;//�ͷ�����
	return size;
}
template<class T>CBinaryTree<T>* CBinaryTree<T>::DivideTree(NodePos(T) x)
{
	FROMPARENTTOONESELF(x) = NULL;
	UpdateNodeHeight(x->GetParent());//�ڵ�߶ȸ���
	UpdateNodeSize(x->GetParent());//�ڵ��ģ����
	m_height = m_root->GetHeight();//ȫ���߶ȸ���
	m_size = m_root->GetSize();//ȫ����ģ����
	x->SetParent(NULL);
	//��������
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

