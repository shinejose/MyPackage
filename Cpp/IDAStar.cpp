#include <cstdio>
#include <iostream>
#include <cmath>
#include <memory>
#include <ctime>
#include <cstdlib>
#include <cstdlib>
#include <algorithm>
//#include <map>
#include <cstring>
#include <stack>
#include <string>
#include <stack>
using namespace std;

const int MAXN= 7;
const int MAXP =20;
int elem[MAXN];

struct State
{
	int m[MAXN][MAXN];
	int g;
	char Path[MAXP+2];
	void Init()
	{
		g=0;
		memset(m,0,sizeof(m));
	}
	State Transform(int i)
	{
		State temp;
		temp.g=g+1;
		for(int i=0;i<7;i++)
			for(int j=0;j<7;j++)
				temp.m[i][j] = m[i][j];
		for(int i=0;i<g;i++)
			temp.Path[i]=Path[i];
		switch(i)
		{
		case 0:
			{
				for(int i=0;i<6;i++)
				{
					temp.m[i][2]=m[i+1][2];
				}
				temp.m[6][2]=m[0][2];
				temp.Path[g]='A';
				temp.Path[g+1]=0;
				break;
			}
		case 1:
			{
				for(int i=0;i<6;i++)
				{
					temp.m[i][4]=m[i+1][4];
				}
				temp.m[6][4]=m[0][4];
				temp.Path[g]='B';
				temp.Path[g+1]=0;
				break;
			}
		case 2:
			{
				for(int i=1;i<7;i++)
				{
					temp.m[2][i]=m[2][i-1];
				}
				temp.m[2][0]=m[2][6];
				temp.Path[g]='C';
				temp.Path[g+1]=0;
				break;
			}
		case 3:
			{
				for(int i=1;i<7;i++)
				{
					temp.m[4][i]=m[4][i-1];
				}
				temp.m[4][0]=m[4][6];
				temp.Path[g]='D';
				temp.Path[g+1]=0;
				break;
			}
		case 4:
			{
				for(int i=1;i<7;i++)
				{
					temp.m[i][4]=m[i-1][4];
				}
				temp.m[0][4]=m[6][4];
				temp.Path[g]='E';
				temp.Path[g+1]=0;
				break;
			}
		case 5:
			{
				for(int i=1;i<7;i++)
				{
					temp.m[i][2]=m[i-1][2];
				}
				temp.m[0][2]=m[6][2];
				temp.Path[g]='F';
				temp.Path[g+1]=0;
				break;
			}
		case 6:
			{
				for(int i=0;i<6;i++)
				{
					temp.m[4][i]=m[4][i+1];
				}
				temp.m[4][6]=m[4][0];
				temp.Path[g]='G';
				temp.Path[g+1]=0;
				break;
			}
		case 7:
			{
				for(int i=0;i<6;i++)
				{
					temp.m[2][i]=m[2][i+1];
				}
				temp.m[2][6]=m[2][0];
				temp.Path[g]='H';
				temp.Path[g+1]=0;
				break;
			}
		}
		return temp;
	}
}Ini;

const int MAXSTACKELEM =  100000;
template<class Node>
class Stack
{
public:
	int TopPointer;
	Node elem[MAXSTACKELEM];

	void Init()
	{
		TopPointer=0;
	}
	bool empty()
	{
		if(TopPointer == 0)
			return true;
		else 
			return false;
	}
	void push(Node a)
	{
           elem[TopPointer++] = a;
	}
	int  pop()
	{
		if(empty())
			return -1;
		TopPointer--;
	}
	Node top()
	{
		return elem[TopPointer-1];
	}
};

Stack<State> OpenStack;

void Initialization()
{
	for(int i=0;i<7;i++)
		for(int j=0;j<7;j++)
		{
			if(i==2 ||i==4||j==2||j==4)
				Ini.m[i][j] =1 ;
			else 
				Ini.m[i][j]=0;
		}
}

void Input()
{
	for(int i=1;i<24;i++)
	{
		scanf("%d",&elem[i]);
	}
	int k=0;
	for(int i=0;i<7;i++)
		for(int j=0;j<7;j++)
			if(Ini.m[i][j])
				Ini.m[i][j]=elem[k++];
}
int Solution(State s)
{
	for(int i=2;i<=4;i++)
		for(int j=2;j<=4;j++)
			if(s.m[i][j])
			{
				if(s.m[i][j]!=s.m[2][2])
					return 0;
			}
			return 1;
}
int H(State CurrentState)
{
	int cnt[MAXN];
	memset(cnt,0,sizeof(cnt));
	for(int i=2;i<=4;i++)
		for(int j=2;j<=4;j++)
			if(CurrentState.m[i][j])
			   cnt[CurrentState.m[i][j]]++;
	int ans=1;
	int max=0;
	max = cnt[1];
	 for(int i=2;i<=3;i++)
	 {
		 if(cnt[i]>max)
		 {
			 max=cnt[i];
			 ans=i;
		 }
	 }
	 return 8-max;
}

State Child(State CurrentState,int i)
{
	return CurrentState.Transform(i);
}
void IDAStar(State StartState)
{
	int PathLimit=0;
	int Success=0;
	int ResourceLimit=6;
	State TargetState;
	if(Solution(StartState))
	{
		printf("No moves needed\n%d\n",StartState.m[2][2]);
		return ;
	}
	OpenStack.Init();
	while( !Success )
	{
		PathLimit++;
		StartState.g=0;
		OpenStack.push(StartState);
		while( !Success && !OpenStack.empty() )
		{
			State CurrentState;
			CurrentState = OpenStack.top();
			OpenStack.pop();
			if(Solution(CurrentState))
			{
				TargetState=CurrentState;
				Success=1;
			}
			else if( CurrentState.g+H(CurrentState) <= PathLimit  )
			{
				for(int i=7;i>=0;i--)
				{
					State ChildState;
					ChildState=Child(CurrentState,i);
					OpenStack.push(ChildState);
				}
			}
		}
	}
	printf("%s\n%d\n",TargetState.Path,TargetState.m[2][2]);
}

void Output()
{

}
int TheRotationGame()
{
	freopen("c:\\in.txt","r",stdin);
    freopen("c:\\out.txt","w+",stdout);
	clock_t start,end;
	start=clock();
	int cases;
	//	Initialization();
	//	for(scanf("%d",&cases);cases;cases--)
	while(scanf("%d",&elem[0]),elem[0])
	{
		Initialization();
		Input();
		IDAStar(Ini);
		Output();
	}	
	end = clock();
	//	printf("%lfms",(((double)end-(double)start)/CLOCKS_PER_SEC)*1000);
	return 0;
}

int main()
{
//	TheRotationGame();
	return 0;
}