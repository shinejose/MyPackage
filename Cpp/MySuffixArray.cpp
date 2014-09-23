#include <algorithm>
using namespace std;


struct SuffixArray
{
    static const int MAXLEN  =100;
	char str[MAXLEN];
	int SA[MAXLEN];
	int Rank[MAXLEN];
	int Rank2[MAXLEN];
	int j;
	int len;
	SuffixArray() {}
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
	void FromSuffixArray()  // O( n*log(n)*log(n) )
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
	int lcp[MAXLEN];
	int r[MAXLEN];
	void calheight(int n)
	{
		int i,j,k=0;
		for(i=1;i<=n;i++) Rank[SA[i]]=i;
		for(i=0;i<n;lcp[Rank[i++]]=k)
			for(k?k--:0,j=SA[Rank[i]-1];r[i+k]==r[j+k];k++);
		return;
	}
	void Set(char *tstr)
	{
		int len=strlen(str);
		for(int i=0;i<len;i++)
		{
			 r[i] = (int)tstr[i];
			 str[i] = tstr[i];
		}
		FromSuffixArray();
		calheight(len+1);
	}
};