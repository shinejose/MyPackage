
/*
����
һЩ����
��1��Wilson����: ��PΪ�������� (P-1)!��-1 (mod P)
 (2)  Fermat���� ��PΪ������aΪ����������gcd(a,P)==1, ��a^(P-1) ��1 (mod P)
 (3)  FermatС������PΪ��������a^P ��a  (mod P)
 (4)  Euler ������gcd(a,m)==1, �� a^��(m) ��1 (mod m)
{
����1
��	��nΪĳһ����p ,���(n)=��(p)=p-1
��	��nΪĳһ����p���ݴ�p^a , ���(n)= ��(p^a)=(p-1)*p^(a-1)
��	��nΪ�����������ʵ���a��b�Ļ������(n)= ��(a*b)= ��(a)*��(b)
 //����Ϊ���Ժ���
����2
n=p1^a1*p2^a2*����*pk^ak ����Ϊ������n�������ݳ˻���ʾʽ����
��(n)=n*(1-1/p1)*(1-1/p2)*����*(1-1/pk)   //����������1. �ں͢�
}
��5��ͬ�������
  ��������a,b,c ,��Ȼ��m,n���ģmͬ������
��	�Է��ԣ�a��a (mod m)
��	�Գ��ԣ���a��b (mod m)����b��a (mod m)
��	�����ԣ���a��b (mod m), b��c (mod m) ,��a��c (mod m)
��	ͬ����: �� a��b (mod m), ��a+c��b+c (mod m)
��	ͬ���ԣ��� a��b (mod m), ��a*c��b*c (mod m)
��	ͬ���ԣ��� a��b (mod m), ��a^c��b^c (mod m)
��	��a mod p =x ,b mod q =x ,gcd(p,q)==1 �� a mod (p*q) =x 

*/


/*
�㷨:
1.��������//�ӽ� O(n)
2.	�ֽ�key��������֮��
3.	������ȡģ �� a^b%m //  (logb)^3
4. ŷ������㷨
5. ��չŷ������㷨  //ax+by=gcd(a,b)=d
6.Miller-Rabbin ����   //  O(s* (logb)^3)
7. �ֽ�key������֮��
8. ����ͬ�෽�� O(n+logb)
9.�й�ʣ�ඨ������ͬ�෽�����������ʽ��// O(k*logm)
10.ŷ����������
11. a*b%m (a*b������__int64) (��bת��2����)
12.ö������ x������n ����  a^n��b (mod m)
13.�ֽ�����
14.baby step-gaint step
*/


1.
struct Number  //��¼һ����10����ֵ �� �����ӳ˻���ʾ
{
	int size;
	__int64 n;
    int prime[maxlen];
	int exp[maxlen];
	Number()
	{
		size =0;
		n=1;
		memset(prime,0,sizeof(prime));
		memset(exp,0,sizeof(exp));
	}
};

�㷨
	1.��������   //�ӽ� O(n)  //ÿ��������ɾ��һ�Σ�ÿ��������¼һ�Σ�
int isprime[maxn];
int prime[maxp];
int primenum;
void CreatePrime() 
{
	for(int i=2;i<maxn;i++)
	{
		if(!isprime[i])
			prime[primenum++]=i;
		for(int j=0; j<primenum && i*prime[j]<maxn;j++) 
		{
			isprime[i*prime[j]]=1; //ɾȥ ����ǰ�������С�ڵ���+����С�����ӣ�����
			if(i%prime[j]==0)  // Ҳ����ÿ���������Ի��ֳ�һ����С�����Ӻ���һ����
				break;      // һ������һ��������С��������ɾ�����������
		}                // �����ҵ��ڶ���ɾ������Ҳ����˵ÿ������ֻ�ܱ�ɾ��1��
	}
 }

2.�ֽ�key��������֮��
int power[maxp];
void  FDecomposition(int model,int key) //model  1Ϊ+��-1Ϊ-
{
    for(int i=0; prime[i]<=key;i++)
        for(int j=key;j;j/=prime[i])
            power[i]+=model*(j/prime[i]);
}

3. ������ȡģ �� a^b%m //  (logb)^3
inline __int64 ModularExp(__int64 a,int b,int m)
{
	__int64 sum;
    for( sum=1;b;b>>=1,a=(a*a)%m)  //��a*a��__int64ʱ��ModularMul(a,a,m);
        if(b&1)
            sum=(sum*a)%m;
        return sum%m;
}

4. ŷ������㷨
int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}

5. ��չŷ������㷨
int exgcd(int a,int b,int &x,int &y) //ax+by=gcd(a,b)=d  
{
	if(b==0)     
	{
		x=1;   //����
		y=0; 
		return a;
	}
	int d=exgcd(b,a%b,x,y);
	int temp=x;
	x=y;
	y=temp-(a/b)*y;
	return d;
}

6.Miller-Rabbin ����   //  O(s* (logb)^3)
��ҪModular(a,b,m) a^b%m
#include <ctime>
#include <cstdlib>
const int maxs= 100; //������ĸ���
int MillerRabbin(int n) /// a^(n-1)��1 (mod n)  //  n�ǻ���a��α����
{                 // ���ڷ�����
	srand((unsigned int)time(NULL));
	for(int i=0;i<s;i++)
	{
		a=rand()%(n-2)+2;  // 2��(n-1)
        if(ModularExp(a,n-1,n)!=1)
			return 0;
	}
	return 1;
}
7. �ֽ�key������֮��  
Number Decomposition(__int64 key) //��key�Ǻ�����
//��key����һ��С�ڵ���key^0.5��������
{
	int i;
	Number x;
	x.n=key;
    for(i=0;prime[i]*prime[i]<=key;i++) //ֻ��Ҫ�ֽ⵽key^0.5 
	{
		if(key%prime[i]==0)
		{
			x.prime[x.size]=prime[i];
			x.exp[x.size]=0;
			while(key%prime[i]==0)
			{
				x.exp[x.size]++;
				key/=prime[i];
			}
			x.size++;
		}
	}
	if(key>1) //�������һ��������  //ʣ�µ�keyһ����������
	{
		x.exp[x.size]=1;
		x.prime[x.size]=key;
		x.size++;
	}
	return x;
}

8. ����ͬ�෽�� O(n+logb)
int ans[maxn]; // ���һ��ģ n'=n/d ��ʣ��ϵ
int  LinerModularEquation(int a,int b,int n)//  a*x��b (mod n) 
{                                  //   a*x+n*(-y)=b 
	int x,y;                         //   a*(x*d/b) + n*(-y*d/b) = d 
    int d=exgcd(a,n,x,y);              //   a*x'+n*y'=gcd(a,n)=d
	if(b%d!=0)                      //   x=x'*b/d;
		return -1;
	int e=(x*b/d +n) %n;              
	for(int i=0;i<d;i++)
		ans[i]=(e+i*n/d + n) % n;
	return  (e+n)%(n/d);    //������С������
}
9.�й�ʣ�ඨ������ͬ�෽�����������ʽ��
// O(k*logm)  
// 0<=x<m����Ψһ��
// x��a[i] (mod m[i]) ( m[i]�������أ� ����k������
int mp[maxn]; 
int LinerModularEquationSystem(int k)
{
	int m=1;
	int ans=0;
    for(int j=0;j<k;j++)
       m=m*m[j];
	for(int i=0;i<k;i++)
	{
		mp[i]=m/m[i];
        int p,q;
		exgcd(mp[i],m[i],p,q);
		ans= (ans+mp[i]*p*a[i])%m;
	}
	return ans<0?ans+m:ans;
}

10.ŷ����������

__int64 Phi(__int64 n)
{
	if(n<maxn&&!IsPrime[n])
	  return n-1;
	__int64 count=1;
	for(int i=0;i<power.size;i++)
		count*=(power.prime[i]-1)*pow((double)power.prime[i],power.exp[i]-1);
	return count;
}
 long long  Phi( long long  n,Number power)
{
	for(int i=0;i<power.size;i++)
		n-= n/power.prime [i];
	return n;
 }
11. a*b%m (a*b������__int64) (��bת��2����)
__int64 ModularMul(__int64 a,__int64 b,__int64 m)
{
	__int64 sum;
	for(sum=0;b;b>>=1,a=(a<<=1)>m?(a-m):a)  //����ȡ��mod ʱ�����
	  if(b&1)
		  sum=(sum+a)>m?(sum+a-m):(sum+a);
	return sum;
}
12.ö������ x������n ����  a^n��b (mod m)
void DFS(int depth,__int64 a,__int64 b,__int64 m,__int64 n��Number  x)
{
	if(depth==x.size)
	{
		if(ModularExp(a,n,m)==b)      
		{
			if(ans>n)
				ans=n;
		}
	}
	 if(depth>=x.size) ///////��ֹ ����depth+1 
		return ;
	for(int i=0;i<=x.exp[depth];i++)//���depth>x.size ,��Ϊx.expû�г�ʼ//��������x.exp[depth+1]���ܴܺ� ����TLE����
	{
	  int temp=n*(int)pow((double)x.prime[depth],i);
      if(temp >=ans)
		  break;
	  DFS(depth+1,a,b,m,temp);
	}
}


13.�ֽ�����
__int64 PollardRho(__int64 n)
{
	__int64 x=2;
	__int64 y=x;
	__int64 k=2;
	__int64 i=1;
	while(1)
	{
		i++;
		 x=(ModularMul(x,x,n)-1)%n;  // possibillity overflow  x=(x*x-1) % n;
		__int64 d=gcd(abs(y-x),n);
		if(d!=1 & d!=n)
			return d;
		if(i==k)
		{
			y=x;
			k=2*k;
		}
	}
}

int64 PollardRho(int64 n)
{
	if( n==1 || MillerRabbin(n,1000))
		return -1 ;
	int64 x=2;
	int64 y=2;
	int64 d=1;
	while( d ==  1 )
	{
		x=(ModularMul(x,x,n)+1)%n;
		y=(ModularMul(y,y,n)+1)%n;
		y=(ModularMul(y,y,n)+1)%n;
		d = gcd( Abs(x-y)  , n);
	}
	if(d== n )
		return -1; 
	else
		return d;
}

//14. baby step -gaint step
map<__int64,int> myhash;
__int64 BabyStepGaintStep(__int64 a,__int64 b,__int64 n)
{
	int m  = (int) sqrt((double)n);
	if((__int64)m*(__int64)m !=n)
		m++;
    for(int j=0;j<m;j++)
		myhash[ModularExp(a,(__int64)j,n)]=j;
	__int64 apfm = LinerModularEquation(ModularExp(a,(__int64)m,n),1,n);
	__int64 ganma=b;
	map<__int64,int>::iterator hashit;
	for(int i =0;i<m;i++)
   {
			hashit= myhash.find(ganma);
			if(hashit!=myhash.end())
				return i*m+hashit->second;
			else
				ganma=(ganma*apfm)%n;
	}
}