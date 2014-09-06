#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <memory>
using namespace std;

typedef  __int64 int64 ;

const int MAXN  =1000005;


#define L(x) (st[(x)].ch[0])
#define R(x) (st[(x)].ch[1])
#define F(x) (st[(x)].father)

struct Node
{ 
    int ch[2],father; // 左右儿子，父亲 
    int size; //子树节点数
    int IsReversal;  //翻转标记 //1 是 / 0 否
    __int64 value ;  // 这个结点的值
	Node(){};
	Node(int f,__int64 v,int s=1,int r=0,int ch0=0,int ch1=0)
	{
		ch[0] = ch0;
		ch[1]= ch1;
		father = f;
		size = s;
		IsReversal  = r;
		value =v;
	}
}st[MAXN];


int root;
int cur ;

void Init()
{
	memset(st,0,sizeof(st));
	cur= 1;
	root =-1;
}

inline void Update(int x)
{
    st[x].size=st[L(x)].size+st[R(x)].size+1;
}


inline void Rotate(int x,int c) // 0,左旋 1，右旋
{
    int y=F(x);
    st[F(x)].ch[!c]=st[x].ch[c];
    if(st[x].ch[c]) F(st[x].ch[c])=y;
    F(x)=F(y);
    if(F(y)) st[F(y)].ch[R(F(y))==y] =x;
    st[x].ch[c]=y; F(y)=x;
    Update(y);
    Update(x);
}

inline void Splay (int x,int f) //把X结点旋到f结点下面  //传入X,F的指针
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
    if(f==0)
        root=x;
}

inline void PushDown(int node)
{
    swap(L(node) ,R(node) );
    st[node].IsReversal  ^=1;
    st[L(node)].IsReversal  ^=1;
    st[R(node)].IsReversal  ^=1;

}

int Find(int node,int x)//返回第X大关键字的下标
{
    int t=x;
    while(1)
    {
        if(st[node].IsReversal  )
            PushDown(node);
        if(st[L(node)].size>=t)
            node=L(node);
        else if((st[L(node)].size+1)==t)
        {
			Splay(node,0);
			  return node;
		}
        else 
        {
            t=t-(st[L(node)].size+1);
            node=R(node);
        }
    }
}

void AddNode(Node x,int IsRight)  //增加一个结点， 传入一个结点和他的父亲的指针,和他是否是他父亲的右儿子
{
	st[cur]=x;
	st[F(cur)].ch[IsRight]= cur;
	Splay(cur,0);
	cur++;
}

void Add(int node,int x)
{
	if(node==-1) 
		AddNode(Node(0,x),1);
	else
	{
		int index = node ;
		while(1)
		{
			if(st[index].value >x)
			{
				if(L(index)==NULL) 
				{
					AddNode(Node(index,x),0);
					break;
				}
				else
					index =L(index);
			}
			else
			{
				if(R(index)==NULL)
				{
					AddNode(Node(index,x),1);
			    	break;
				}
				else 
					index = R(index );
			}
		}
	}
}


int OutPutKMax(int node,int k)
{
	int index= Find(root,cur-k);
//	return st[index].value;
	printf("%I64d\n",st[index].value );
	return 0;
}

void Problem()
{
	int n,k;
	while(scanf("%d%d",&n,&k)!=EOF)
	{
		Init();
		for(int i=0;i<n;i++)
		{
			char op[5];
			__int64 x;
			scanf("%s",op);
			if(strcmp(op,"I")==0)
			{
					scanf("%I64d",&x);
					Add(root,x);
			}
			else
				OutPutKMax(root,k);
		}
	}
}


int main()
{
	//			clock_t start,end;
	//			start = clock();
	freopen("in.txt","r",stdin);
	//	  freopen("c:\\in.txt","w+",stdout);
	Problem();
	//			end = clock();
	//			printf("%lfs\n",(double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}
