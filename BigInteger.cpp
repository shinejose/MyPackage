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


struct BigInteger
{
	const static int system=10000;
	vector<int>elem; //ËÙ¶ÈÂý
	int IsMinus;
	BigInteger() {}
	BigInteger(int x)
	{
		elem.clear();
		if(x<0)
		{
			IsMinus=1 ;
			x=-x;
		}
		else 
			IsMinus=-1;
		if(x==0)
			elem.push_back(0);
		 while(x)
		 {
			 elem.push_back(x%system);
			 x/=system;
		 }
	}
	void Set(int x)
	{
		elem.clear();
		if(x<0)
		{
			IsMinus=1 ;
			x=-x;
		}
		else 
			IsMinus=-1;
		if(x==0)
			elem.push_back(0);
		 while(x)
		 {
			 elem.push_back(x%system);
			 x/=system;
		 }
	}
	void Init()
	{
		IsMinus=1;
		elem.clear();
	}
	BigInteger operator =(BigInteger m)
	{
		elem.clear(); 
		for(vector<int>::iterator i=m.elem.begin();i!=m.elem.end();i++)
		   elem.push_back(*i);
		IsMinus=m.IsMinus;
		return *this;
	}
	bool operator >=(BigInteger m)
	{
		int lenthis=elem.size();
		int lenm = m .elem.size();
		if(lenthis>lenm)
			return true;
		else if(lenthis==lenm)
		{
			for(int i =lenm-1;i>=0;i--)
			{
				if(elem[i]>m.elem[i])
					return true;
				else if( elem[i]==m.elem[i])
					continue;
				else 
					return false;
			}
		}
		else
			return false ;
		return true;
	}
	BigInteger sub(BigInteger a,BigInteger b)
	{
		BigInteger sum;
		int lena = a.elem.size();
		int lenb = b.elem.size();
		int render = 0;
		int c =0;
		for(int i=0;i<lena;i++)
		{
			int elema,elemb;
			if( i>=lenb)	elemb=0;
			else            elemb=b.elem[i];
			elema  = a.elem[i];
			render = (elema-elemb+c);
			if(render < 0 )
		    {  
				render += system;
		        	c = -1;
			}
			else c=0;
			sum.elem.push_back(render%system);
		}
		sum.IsMinus=a.IsMinus;
		return sum;
	}
	BigInteger operator -(BigInteger m)
	{
	    if(*this>=m)
		{
			this->IsMinus=1;
			return sub(*this,m);
		}
		else 
		{
			 m.IsMinus=-1;
			 return sub(m,*this);
		}
	}
	BigInteger operator +(BigInteger m)
	{
		int lenthis= this->elem.size();
		int lenm = m.elem.size();
		int maxlen = max( lenthis,lenm);
		BigInteger sum;
		int render;
		int c=0;
		for(int i=0;i<maxlen;i++)
		{
			int elemthis,elemm;
			if(i>=lenthis) elemthis=0;
			else           elemthis=elem[i];
			if(i>=lenm)    elemm   =0;
			else           elemm   =m.elem[i];
			render = (elemthis+elemm+c)%system;
		     c     = (elemthis+elemm+c)/system;
			sum.elem.push_back(render);
		}
		if(c) 
			sum.elem.push_back(c);
		sum.IsMinus=this->IsMinus;
		return sum ;
	}
	void DelLeadingZero(BigInteger &m)
	{
		int len = m.elem.size();
		if(len==1)
			return ;
		for(int i=len-1;i>=0;i--)
		{
			if(i<=0)
				return ;
			if(m.elem[i]!=0)
				break;
			else
			{
				m.elem.pop_back();
			}
		}
	}
	BigInteger operator *(BigInteger m)
	{
		int lenthis= this->elem.size();
		int lenm = m.elem.size();
		int sumlen =lenthis+lenm-1;
		BigInteger sum;
		int render = 0;
	    int c      = 0;
		for(int i=0;i<sumlen ;i++)
		{
			render = c;
			c      = 0;
			for(int j=0;j<=i;j++)
			{
				int elemthis,elemm;
			    if(i-j>=lenthis) elemthis=0;
		      	else           elemthis=elem[i-j];
			    if(j>=lenm)    elemm   =0;
			    else           elemm   =m.elem[j];
			    c      += (elemthis*elemm+render )/system;
				render = (elemthis*elemm+render)%system;
			}
			sum.elem.push_back(render);
		}
		while(c)
		{
			 sum.elem.push_back(c%system);
			 c/=system;
		}
		DelLeadingZero(sum);
		return sum;
	}
	BigInteger Pow(int x)
	{
		BigInteger sum(1);
		BigInteger temp;
		temp = *this;
		for(int i=x;i;i>>=1,temp=temp*temp)
		 if(i&1)
		  sum=sum*temp;
		return sum;
	}
	void sqrtadjust(BigInteger &y,BigInteger &r,BigInteger c,int taget)
	{
		int l,u,k;
		int ans ;
		BigInteger t1,t2 ,t3;
		t1 = (r*BigInteger(100)+BigInteger(taget));
		l=0;
		u=9;
		while(u-l>1)
		{
			k= (u+l) >>1;
			t2 = (c*y+BigInteger(k))*BigInteger(k);
			t3 = t1 -t2;
			if(!(t3.IsMinus < 0)) 
			{
				ans = k;
				l = k;
			}
			else
				u=k;
		}
		t2 = (c*y+BigInteger(l))*BigInteger(l);
		t3 = t1 -t2;
		if(!(t3.IsMinus < 0))
			ans = l;
		t2 = (c*y+BigInteger(u))*BigInteger(u);
		t3 = t1 -t2;
		if(!( t3.IsMinus < 0))
			ans =u;
		r = ( ((r*BigInteger(100))+BigInteger(taget)) - (c*y+BigInteger(ans))*BigInteger(ans));
		y = y*BigInteger(10)+BigInteger(ans) ;
	}
	BigInteger sqrt()
	{
          BigInteger y(0),r(0);
		  BigInteger c(20);
		  int len = elem.size();
		  for(int i=len-1;i>=0;i--)
		  {
		     if(i==len-1)
			 {
				 if(elem[i]>=100) 
				{
					sqrtadjust(y,r,c,elem[i]/100);
					sqrtadjust(y,r,c,elem[i]%100);
				 }
				 else
					 sqrtadjust(y,r,c,elem[i]);
			 }
			 else
			 {
				 sqrtadjust(y,r,c,elem[i]/100);
				 sqrtadjust(y,r,c,elem[i]%100);
			 }
		  }
		  return y;
	}
	void Scan()
	{
		vector<int> str;
		char c;
		int n=0;
		while(1)
		{
			c=getchar();
			if(c=='\n'|| c==EOF)
				break;
		    str.push_back(c-'0');
		}
		int temp=1;
		int count =1;
	    for(int i = str.size()-1;i>=0;i--,count ++)
		{
			n = str[i]*temp+n;
			if(count  ==4 )
			{
				elem.push_back(n);
				n= 0;
				count  =0;
				temp =1;
			}
			else
				temp*=10;
		}
		if( n !=0)
			elem.push_back(n);
	}
	void Print()
	{
		int len = elem.size();
		DelLeadingZero(*this);
		if(elem.size()==0)
		{
			putchar('0');
			return;
		}
		for(int i=len-1;i>=0;i--)
		{
			if( i==len-1)
				printf("%d",elem[i]);
			else
			{
				for(int j=3;j>=0;j--)
				{
					int num = (int)pow(10.0,j);
					if(abs(elem[i])>=num)
						putchar(elem[i]/num+'0');
					else
						putchar('0');
					elem[i]%=num;
				}
			}
		}
	}
};

struct Verysimpleproblem
{
	BigInteger  Work(BigInteger n)
	{
		return n.sqrt();
	}
};
void Problem()
{
	BigInteger n;
	n.Scan();
//	for(int i=0;i<300;i++)
//	{
//	n.Set(i);
		Verysimpleproblem solution;
		n=solution.Work(n);
		n.Print();
		putchar('\n');
//	}
}
/*
int main()
{
	clock_t start,end;
	start = clock();
	freopen("in.txt","r",stdin);
	freopen("out.txt","w+",stdout);
	end = clock();
	Problem();
	//	printf("%lfs\n",(double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}
*/
