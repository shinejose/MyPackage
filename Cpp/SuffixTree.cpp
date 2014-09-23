#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <cmath>
#include <map>

using namespace std;

template<class T>
T Abs(T x)
{
	return x>0?x:-x;
}


const int MAXN= 305;
const int MAXARC =10005;
const int INFINITY = 10000000;
int n,m,q;
int counting=0;
int cur;


char str[MAXN];

int SA[MAXN];
int Rank[MAXN];
int Rank2[MAXN];
int j;
int len;

bool cmp(const int  &a,const int  &b)
{
	return str[a]<str[b];
}
bool cmp2(const int &a,const int &b)
{
	if(Rank[a]==Rank[b])
	{
			return Rank[a+j]<Rank[b+j];
	}
	return Rank[a]<Rank[b];
}
void FromSuffixArray() // O( n*log(n)*log(n) )
{
     len =strlen ( str);
	 for(int i=0;i<=len;i++)
		 SA[i]=i;
	sort(SA,SA+len+1,cmp);
	Rank[SA[0]]=0;
	for(int i=1;i<=len;i++)
	{
		if(str[SA[i]]==str[SA[i-1]])
			Rank[SA[i]]=Rank[SA[i-1]];
		else
			Rank[SA[i]]=Rank[SA[i-1]]+1;
	}
	for(j=1;j<=len;j<<=1)
	{
		sort(SA,SA+len+1,cmp2);
			Rank2[SA[0]]=0;
		for(int i=1;i<=len;i++)
		{
			if(Rank[SA[i]]==Rank[SA[i-1]] && Rank[SA[i]+j] == Rank[SA[i-1]+j] )  // i or j 's length <j ,judge for the one bool expression
				Rank2[SA[i]]=Rank2[SA[i-1]];
			else
				Rank2[SA[i]]=Rank2[SA[i-1]]+1;
		}
		for(int k=0;k<=len;k++)
			Rank[k]=Rank2[k];
	}
}
int height[MAX];
void calheight(char *r,int *sa,int n)
{
     int i,j,k=0;
     for(i=1;i<=n;i++) Rank[sa[i]]=i;
     for(i=0;i<n;height[Rank[i++]]=k)
         for(k?k--:0,j=SA[Rank[i]-1];r[i+k]==r[j+k];k++);
         return;
}
void Pre()
{

}
int hlen;
int len;
void Init()
{

}
void Input()
{
	scanf("%s",&tempstr);
}
void Output()
{
	 len= strlen(str);
	int templen = strlen(tempstr);
	str[len]=1;
	for(int i=0;i<templen;i++)
	{
		str[i+len+1]=tempstr[i];
	}
	str[templen+len+1]=0;
	hlen= len +templen;
	int ans=-1;
	for(int i=1;i<templen+len +1 ;i++)
	{
		if( (SA[i]<len &&SA[i-1]>len ) ||(SA[i]>len &&SA[i-1]<len )
		{
			if( height[i]> ans)
				ans =height[i];
		}
	}
	printf("%d\n",ans);
}

int Problem1003()
{
	freopen("c:\\in.txt","r",stdin);
//		freopen("c:\\out.txt","w+",stdout);
	int cases;
	Pre();
	//	for(scanf("%d",&cases);cases;cases--)
	while(scanf("%s",&str) !=EOF)
	{
 		Init();
		Input();
		FromSuffixArray();
		calheight(str,SA,hlen)
		Output();
	}
	return 0;
}