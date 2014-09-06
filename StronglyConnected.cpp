
1.有向图的强连通分量
int dfn[maxn];   //DFN(u)为节点u搜索的次序编号(时间戳)
int low[maxn];   //Low(u)为u或u的子树能够追溯到的最早的栈中节点的次序号
int stack[maxn],top;
int instack[maxn];
int belong[maxn]; // 属于哪个分量

int index=0;
int scc;

void Init()
{
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	index=1;
	scc=0;
	top=0;
}


void Tarjan(int node)
{
	dfn[node]=low[node]=index++;
	stack[top++]=node;
	instack[node]=1;
	for(int i=first[node];i!=-1;i=arc[i].next)
	{
		if(!dfn[arc[i].y])
		{
			Tarjan(arc[i].y);
			low[node]=Min(low[node],low[arc[i].y]);
		}
		else if(instack[arc[i].y])
		{
			low[node]=Min(low[node],dfn[arc[i].y]);
		}
	}
	if(dfn[node]==low[node])  //当DFN(u)=Low(u)时，以u为根的搜索子树上所有节点是一个强连通分量。
	{
		scc++;
		do
		{
			instack[stack[top-1]]=0;
			belong[stack[top-1]]=scc;
			top--;
		}while(stack[top]!=node);
	}
}
