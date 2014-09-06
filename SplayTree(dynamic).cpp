#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <cstdlib>
#include <vector>
#include <memory>
using namespace std;


#define L(x) (st[(x)].ch[0])
#define R(x) (st[(x)].ch[1])
#define F(x) (st[(x)].father)

struct Node 
{ 
	int ch[2],father; // 左右儿子的指针，父亲的指针 
	int size; //子树节点数
	int reversal;  //翻转标记 //1 是 / 0 否
	int key;  // 这个结点的值
	int sorce;
	int maxsorce;
	Node() {};
	Node(int ikey,int ireversal=0)
	{
		key=ikey;
	}
	Node(int isorce,int ikey,int ifather,int icl,int icr,int isize=1,int ireversal=0)
	{
		key = ikey;
		father = ifather;
		ch[0] = icl;
		ch[1] = icr;
		size = isize ;
		reversal  = ireversal;
		sorce = isorce;
		maxsorce = sorce;
	}
};

struct SplayTree
{
	const static int nil = -1;
	vector<Node> st;
	int root;
	SplayTree()
	{
		st.clear();
	}
	void Init()
	{
		st.clear();
	}
	int Add(int father,Node x,int c)
	{
		if(father==nil)
			st.push_back(Node(x.sorce,x.key,father,nil,nil));
		else
	   {
		   st[father].ch[c]=st.size();
		   st.push_back(Node(x.sorce,x.key,father,nil,nil));
		}
		return st.size()-1;
	}
	void Push(Node x)
	{
		if(Empty())
		{
			Add(nil,x,1);
			root=0;
		}
		else
		{
			int node =root;
			while(1)
			{
				if(x.key>=st[node].key)
				{
					if(R(node)=nil)
					{
						Splay(Add(node,x,1),nil);
						break;
					}
					else
						node=R(node);
				}
				else 
				{
					if(L(node)==nil)
					{
						Splay(Add(node,x,0),nil);
						break;
					}
					else
						node=L(node);
				}
			}
		}
	}
	bool Empty()
	{
		return st.size() ==0;
	}
	void Update(int x)
	{
		if(L(x) == nil && R(x) == nil)
		{
			st[x].size=1;
			st[x].maxsorce= st[x].sorce;
		}
		else if(L(x) == nil)
		{
			st[x].size = st[R(x)].size+1;
			st[x].maxsorce = max(st[x].sorce,st[R(x)].maxsorce);
		}
		else if(R(x) == nil)
		{
			st[x].size = st[L(x)].size+1;
			st[x].maxsorce = max(st[x].sorce,st[L(x)].maxsorce);
		}
		else
		{
			st[x].size=st[L(x)].size+st[R(x)].size+1;
			st[x].maxsorce=max(max(st[L(x)].maxsorce,st[R(x)].maxsorce),st[x].sorce);
		}
	}
	void Rotate(int x,int c) // 0,左旋 1，右旋  //其中x是指针
	{
		int y=F(x);
		st[F(x)].ch[!c]=st[x].ch[c];
		if(st[x].ch[c]!=nil) F(st[x].ch[c])=y;
		F(x)=F(y);
		if(F(y)!=nil) st[F(y)].ch[R(F(y))==y] =x;
		st[x].ch[c]=y; F(y)=x;
		Update(y);
		Update(x);
	}
	void Splay (int x,int f) //把X结点旋到f结点下面 //x,f 都是指针
	{
		while(F(x)!=f)
		{
			if(F(F(x))==f)
				Rotate(x,L(F(x))==x);  //单旋
			else
			{
				int c1=(L(F(F(x)))==F(x));
				int c2=(L(F(x))==x);
				if(c1==c2)
					Rotate(F(x),c1),Rotate(x,c2);   //一字型旋转
				else
					Rotate(x,c2),Rotate(x,c1);  // 之字型旋转
			}
		}
		if(f==nil)
			root=x;
	}
	void PushDown(int node)
	{
		swap(L(node) ,R(node) );
		st[node].reversal^=1;
		st[L(node)].reversal^=1;
		st[R(node)].reversal^=1;
	}
	void Delete()
	{
	}
	void InorderTraval(int node)
	{
		if(node==nil)
			return;
		InorderTraval(L(node));
		printf("%d ",st[node].key);
		InorderTraval(R(node));
	}
	int GetMax(int l,int r)
	{
		Splay(l-1,nil);
		Splay(r+1,l-1);
		return st[L(R(root))].maxsorce;
	}
	int Search(Node x)
	{
		int node =root;
	    while(1)
		{
			if(node==nil)
				return nil;
			if(st[node].key == x.key)
			{
				Splay(node,nil);
				return node;
			}
			else if(x.key>st[node].key)
				node= R(node);
			else 
				node=L(node);
		}
	}
	void Edit(Node x)
	{
	    int index =Search(x);
		if( index == nil)
			return ;
		else 
		{
			st[index].sorce=x.sorce;
			Splay(index,nil);
		}
	}
};

SplayTree test;


void Problem()
{
	  int n ,m;
	  while(scanf("%d%d",&n,&m)!=EOF)
	  {
		  test.Init();
		  Node t;
		  t.sorce = -1;
		  t.key=0;
		  test.Push(t);
		  for(int i=1;i<=n;i++)
		  {
			  scanf("%d",&t.sorce);
			  t.key=i;
			  test.Push(t);
		  }
		  t.key = n+1;
		  test.Push(t);
		  char op[3];
		  for(int i=0;i<m;i++)
		  {
			  int a,b;
			  scanf("%s%d%d",op,&a,&b); 
			  if(op[0]=='Q') 
				  printf("%d\n",test.GetMax(a,b));
			  else 
			  {
				  t.sorce=b;
				  t.key=a;
				  test.Edit(t);
			  }
		  }
	  }
}
int main()
{
	clock_t start,end;
	start = clock();
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w+",stdout);
	end = clock();
	Problem();
	//	printf("%lfs\n",(double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <cstdlib>
#include <vector>
#include <memory>
using namespace std;


struct Node 
{ 
	Node* ch[2];// 左右儿子的指针
	Node* father;// ，父亲的指针 
	int size; //子树节点数
	int reversal;  //翻转标记 //1 是 / 0 否
	int key;  // 这个结点的值
	int sorce;
	int maxsorce;
	Node() {};
	Node(int ikey,int ireversal=0)
	{
		key=ikey;
	}
	Node(int isorce,int ikey,int ifather,int icl,int icr,int isize=1,int ireversal=0)
	{
		key = ikey;
		father = ifather;
		ch[0] = icl;
		ch[1] = icr;
		size = isize ;
		reversal  = ireversal;
		sorce = isorce;
		maxsorce = sorce;
	}
	bool operator <(Node x)
	{
	    return key<x.key;
	}
	bool operator ==(Node x)
	{
		return key == x.key;
	}
	bool operator >(Node x)
	{
		return key >x.key;
	}
};

struct SplayTree
{
    Node *root;
	int size;
	SplayTree()
	{
		root= NULL;
		size=0;
	}
	void Clear(Node* node)
	{
		 if(node->ch[0]!=NULL)
			 Clear(node->ch[0]);
		 else if( node->ch[1]!=NULL)
			 Clear(node->ch[1]);
		 delete(node);
	}
	bool Empty()
	{
		return size == 0;
	}
	void Update(int x)
	{
	}
	void Rotate(int x,int c)
	{
		int y  = F(x);
		st[y].ch[!c]=st[x].ch[c];
		F(st[x].ch[c]) = y;
		F(x) = F(y);
		F(y) = x;
		Update(y);
		Update(x);
	}
	int Splay(int x)
	{
		while(x!=root)
		{
			int y =F(x);
			if(y==root)
			{
				if(L(y)==x) 
					Rotate(x,1);
				else 
					Rotate(x,0);
			}
			else
			{
			   int z=F(F(x));
			   if(y==L(z) && x==L(y))
			   {
				   Rotate(y,1);
				   Rotate(x,1);
			   }
			   else if( y==R(z) && x == R(y) ) 
			   {
				   Rotate(y,0);
				   Rotate(y,0);
			   }
			   else if( y==R(z) && x==L(y) )
			   {
				   Rotate(x,0);
				   Rotate(x,1);
			   }
			   else 
			   {
				   Rotate(x,1);
				   Rotate(x,0);
			   }
			}
		}
	}
	int Find(Node x)
	{
		int node =root;
		int lastnode=root;
		while(node != nil )
		{
			lastnode = node;
			if(x<st[L(node)])
				node = L(node);
			else if(x==st[node])
			{
				Splay(node);
				return node;
			}
			else 
				node =R(node);
		}
		if(lastnode!=nil)
		  Splay(lastnode);
		return -1;
	}
	Node* FindMax(Node* x)
	{
		 Node* node=x;
		 while(1)
		 {
			 if(node->ch[1]!=NULL)
				 node=node->ch[0];
			 else
				 break;
		 }
		 return node;
	}
	Node* FindMin(Node* x)
	{
		 Node* node=x;
		 while(1)
		 {
			 if(node->ch[0]!=NULL)
				 node=node->ch[0];
			 else
				 break;
		 }
		 return node;
	}
	void Join(SplayTree x)
	{
		FindMax(root);
		
	}
	void Split()
	{
	}
	void Insert(Node x)
	{
	}
	void Delete()
	{
	}
};

SplayTree test;
void Problem()
{
	  int n ,m;
	  while(scanf("%d%d",&n,&m)!=EOF)
	  {
		  test.Clear();
		  Node t;
		  t.sorce = -1;
		  t.key=0;
		  test.Insert(t);
		  for(int i=1;i<=n;i++)
		  {
			  scanf("%d",&t.sorce);
			  t.key=i;
			  test.Insert(t);
		  }
		  t.key = n+1;
		  test.Insert(t);
		  char op[3];
		  for(int i=0;i<m;i++)
		  {
			  int a,b;
			  scanf("%s%d%d",op,&a,&b); 
			  if(op[0]=='Q') 
				  printf("%d\n",test.GetMax(a,b));
			  else 
			  {
				  t.sorce=b;
				  t.key=a;
				  test.Edit(t);
			  }
		  }
	  }
}
int main()
{
	clock_t start,end;
	start = clock();
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w+",stdout);
	end = clock();
	Problem();
	//	printf("%lfs\n",(double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}