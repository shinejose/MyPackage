
1.����ͼ��ǿ��ͨ����
int dfn[maxn];   //DFN(u)Ϊ�ڵ�u�����Ĵ�����(ʱ���)
int low[maxn];   //Low(u)Ϊu��u�������ܹ�׷�ݵ��������ջ�нڵ�Ĵ����
int stack[maxn],top;
int instack[maxn];
int belong[maxn]; // �����ĸ�����

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
	if(dfn[node]==low[node])  //��DFN(u)=Low(u)ʱ����uΪ�����������������нڵ���һ��ǿ��ͨ������
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
