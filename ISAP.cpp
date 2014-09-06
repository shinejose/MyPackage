#include <cstdio>
#include <iostream>
#include <cmath>
#include <memory>
#include <cstdlib>
#include <algorithm>
//#include <map>
#include <cstring>
#include <string>
using namespace std;
const double Precision=1e-7;
template<class T>
T Max(T a,T b)
{
    if(a>b) 
        return a;
    else 
        return b;
}
template<class T>
T Min(T a, T b)
{
    if(a<b) 
        return a;
    else 
        return b;
}
template<class T>
T Max3(T a,T b,T c)
{
    T z;
    if(a>b)
		
        z=a;
    else 
        z=b;
    if(c>z)
        return c;
    else 
        return z;
}
template<class T>
T Min3(T a,T b,T c)
{ 
    T z;
    if(a<b)
        z=a;
    else 
        z=b;
    if(c<z)
        return c;
    else 
        return z;
}
template<class T>
void Swap(T &a,T &b)
{
    T temp;
    temp=a;
    a=b;
    b=temp;
}
template<class T>
T Abs(T x)
{
    if(x<0)
        return -x;
    else 
        return x;
}
template<class T>
int Filtration(T x)
{
    if(Abs(x)<Precision)
        return 0;
    else if(x>0)
        return 1;
    else 
        return -1;
}

const int Infinity=1e8;
const double Pi=3.14159265358979323846;
//const double e=2.71828182845904523536028747135266249775724709369995957;

#define L(x) ((x)+(x))
#define R(x) (((x)+(x))+1)
#define F(x) ((x)/2)

const int maxn =   205 ;
const int maxm =30 ;
const int maxc  = 51;
const int maxarc =30;
const int maxq =205;
const int mod=662883;
int  n,m,ans,counting=0,cur,root;
int r[maxn][maxn];
int pre[maxn];
int d[maxn];
int gap[maxn];

int q[maxq],rear,front;
int s,t;
void InitD()
{
	for(int i=1;i<=n;i++)
		d[i]=Infinity;
	memset(gap,0,sizeof(gap));
	memset(pre,-1,sizeof(pre));
	front=rear=0;
	d[t]=0;
	gap[0]=1;
	q[rear++]=t ;
	while(front!=rear)
	{
		int u=q[front++];
		for(int i=1;i<=n;i++)
		{
			if(d[i]==Infinity&&r[i][u]>0)
			{
				d[i]=d[u]+1;
				gap[d[i]]++;
				q[rear++]=i;
			}
		}
	}
}
int HaveAllowArc(int u,int &v)
{
	for(int i=1;i<=n;i++)
	{
		if(r[u][i]>0&&d[u]==d[i]+1)
		{
			v=i;
			return 1;
		}
	}
	return 0;
}
int  Adjust()
{
	int min=Infinity;
				for(int j=t;j!=s;j=pre[j])
					min=Min(min,r[pre[j]][j]);
				for(int k=t;k!=s;k=pre[k])
				{
					r[pre[k]][k]-=min;
					r[k][pre[k]]+=min;
				}
				return min;
}
int Relable(int u)
{
	int min=Infinity;
	for(int l=1;l<=n;l++)
		if(r[u][l]>0 &&min>d[l])
			min=d[l];
		if(min==Infinity)
			return 2*n;
		else
			return min+1;
}
int ISAP()
{
	InitD();
	int flow=0;
	int u=s,v;
         pre[s]=s;
	while(d[s]<n)
	{
		if(HaveAllowArc(u,v))
		{
			pre[v]=u;
			u=v;
			if(v==t)
			{
				flow+=Adjust();
				u=s;
			}
		}
		else
		{
			int temp=Relable(u);
			gap[temp]++;
			gap[d[u]]--;
			if(gap[d[u]]==0)
				break;
			d[u]=temp;
			u=pre[u];
		}
	}
	return flow;
}
void Initialization()
{
    cur=1;
    root=1;
    ans=0;
	s=1;
	t=n;
	memset(r,0,sizeof(r));
}

void Input()
{
	int i,x,y,z;
	t=n;
	for(i=0;i<m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		r[x][y]+=z;
	}
}

void Output()
{
	printf("Case %d: %d\n",++counting,ISAP());
}
int main()
{
    freopen("c:\\in.txt","r",stdin);
    //freopen("c:\\out2.txt","w+",stdout);
    int cases;
	//	Initialization();
			for(scanf("%d",&cases);cases;cases--)
	//while(scanf("%d%d",&n,&m)!=EOF)
    {
		scanf("%d%d",&n,&m);
		Initialization();
		Input();
		Output();
    }	
    return 0;
}