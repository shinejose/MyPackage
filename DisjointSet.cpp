
struct DisjointSets
{
	static const int MAXELEM = 1005;
	int father[MAXELEM];
	int rank[MAXELEM];
	DisjointSets()
	{
		for(int i=0;i<MAXELEM;i++)
		{
			father[i] = i;
			rank[i]=1;
		}
	}
	void Init()
	{
		for(int i=0;i<MAXELEM;i++)
		{
			father[i] = i;
			rank[i]=1;
		}
	}
	/*
	int  Find(int x)
	{
	if(x!=father[x])
	return father[x]=Find(father[x]);
	}
	*/
	int Find(int x)  
	{  
		int t=x;  
		int temp;  
		while(father[x]!=x)  
			x=father[x];  
		while(father[t]!=x)  
		{  
			temp=father[t];  
			father[t]=x;  
			rank[t]=1;  
			t=temp;  
		}  
		return x;  
	}  
	void Merge(int x,int y)
	{
		int fx=Find(x);
		int fy=Find(y);
		if(fx==fy)
			return;
		if(rank[fx]<rank[fy])
			father[fx] = fy;
		else
		{
			father[fy]=fx;
			if(rank[fx]==rank[fy])
				rank[fy]++;
		}
	}
};