
/*
数论
一些定理：
（1）Wilson定理: 若P为素数，则 (P-1)!≡-1 (mod P)
 (2)  Fermat定理： 若P为素数，a为正整数，且gcd(a,P)==1, 则a^(P-1) ≡1 (mod P)
 (3)  Fermat小定理：若P为素数，则a^P ≡a  (mod P)
 (4)  Euler 定理：若gcd(a,m)==1, 则 a^φ(m) ≡1 (mod m)
{
引理1
①	若n为某一素数p ,则φ(n)=φ(p)=p-1
②	若n为某一素数p的幂次p^a , 则φ(n)= φ(p^a)=(p-1)*p^(a-1)
③	若n为任意两个互质的数a，b的积，则φ(n)= φ(a*b)= φ(a)*φ(b)
 //即φ为积性函数
引理2
n=p1^a1*p2^a2*……*pk^ak 。。为正整数n的素数幂乘积表示式，则：
φ(n)=n*(1-1/p1)*(1-1/p2)*……*(1-1/pk)   //运用了引理1. ②和③
}
（5）同余的性质
  对于整数a,b,c ,自然数m,n则对模m同余满足
①	自反性：a≡a (mod m)
②	对称性：若a≡b (mod m)，则b≡a (mod m)
③	传递性：若a≡b (mod m), b≡c (mod m) ,则a≡c (mod m)
④	同加性: 若 a≡b (mod m), 则a+c≡b+c (mod m)
⑤	同乘性：若 a≡b (mod m), 则a*c≡b*c (mod m)
⑥	同幂性：若 a≡b (mod m), 则a^c≡b^c (mod m)
⑦	若a mod p =x ,b mod q =x ,gcd(p,q)==1 则 a mod (p*q) =x 

*/


/*
算法:
1.素数生成//接近 O(n)
2.	分解key！素因数之积
3.	快速幂取模 求 a^b%m //  (logb)^3
4. 欧几里德算法
5. 扩展欧几里德算法  //ax+by=gcd(a,b)=d
6.Miller-Rabbin 测试   //  O(s* (logb)^3)
7. 分解key素因数之积
8. 线性同余方程 O(n+logb)
9.中国剩余定理（线性同余方程组的特殊形式）// O(k*logm)
10.欧拉函数计算
11. a*b%m (a*b超出的__int64) (将b转成2进制)
12.枚举因子 x的因子n 满足  a^n≡b (mod m)
13.分解因子
14.baby step-gaint step
*/


1.
struct Number  //记录一个的10进制值 和 素因子乘积表示
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

算法
	1.素数生成   //接近 O(n)  //每个合数被删除一次，每个素数记录一次，
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
			isprime[i*prime[j]]=1; //删去 （当前这个数×小于等于+其最小素因子）的数
			if(i%prime[j]==0)  // 也就是每个合数可以划分成一个最小素因子和另一个数
				break;      // 一个是另一个数×最小素因子来删除这个合数的
		}                // 不能找到第二种删除方法也就是说每个合数只能被删除1次
	}
 }

2.分解key！素因数之积
int power[maxp];
void  FDecomposition(int model,int key) //model  1为+，-1为-
{
    for(int i=0; prime[i]<=key;i++)
        for(int j=key;j;j/=prime[i])
            power[i]+=model*(j/prime[i]);
}

3. 快速幂取模 求 a^b%m //  (logb)^3
inline __int64 ModularExp(__int64 a,int b,int m)
{
	__int64 sum;
    for( sum=1;b;b>>=1,a=(a*a)%m)  //若a*a超__int64时用ModularMul(a,a,m);
        if(b&1)
            sum=(sum*a)%m;
        return sum%m;
}

4. 欧几里德算法
int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}

5. 扩展欧几里德算法
int exgcd(int a,int b,int &x,int &y) //ax+by=gcd(a,b)=d  
{
	if(b==0)     
	{
		x=1;   //倒推
		y=0; 
		return a;
	}
	int d=exgcd(b,a%b,x,y);
	int temp=x;
	x=y;
	y=temp-(a/b)*y;
	return d;
}

6.Miller-Rabbin 测试   //  O(s* (logb)^3)
需要Modular(a,b,m) a^b%m
#include <ctime>
#include <cstdlib>
const int maxs= 100; //随机数的个数
int MillerRabbin(int n) /// a^(n-1)≡1 (mod n)  //  n是基于a的伪素数
{                 // 基于费马定理
	srand((unsigned int)time(NULL));
	for(int i=0;i<s;i++)
	{
		a=rand()%(n-2)+2;  // 2到(n-1)
        if(ModularExp(a,n-1,n)!=1)
			return 0;
	}
	return 1;
}
7. 分解key素因数之积  
Number Decomposition(__int64 key) //若key是合数，
//则key必有一个小于等于key^0.5的素因子
{
	int i;
	Number x;
	x.n=key;
    for(i=0;prime[i]*prime[i]<=key;i++) //只需要分解到key^0.5 
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
	if(key>1) //处理最后一个素因子  //剩下的key一定是素数。
	{
		x.exp[x.size]=1;
		x.prime[x.size]=key;
		x.size++;
	}
	return x;
}

8. 线性同余方程 O(n+logb)
int ans[maxn]; // 输出一个模 n'=n/d 的剩余系
int  LinerModularEquation(int a,int b,int n)//  a*x≡b (mod n) 
{                                  //   a*x+n*(-y)=b 
	int x,y;                         //   a*(x*d/b) + n*(-y*d/b) = d 
    int d=exgcd(a,n,x,y);              //   a*x'+n*y'=gcd(a,n)=d
	if(b%d!=0)                      //   x=x'*b/d;
		return -1;
	int e=(x*b/d +n) %n;              
	for(int i=0;i<d;i++)
		ans[i]=(e+i*n/d + n) % n;
	return  (e+n)%(n/d);    //返回最小正数解
}
9.中国剩余定理（线性同余方程组的特殊形式）
// O(k*logm)  
// 0<=x<m内有唯一解
// x≡a[i] (mod m[i]) ( m[i]两两互素） 共有k条方程
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

10.欧拉函数计算

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
11. a*b%m (a*b超出的__int64) (将b转成2进制)
__int64 ModularMul(__int64 a,__int64 b,__int64 m)
{
	__int64 sum;
	for(sum=0;b;b>>=1,a=(a<<=1)>m?(a-m):a)  //减法取代mod 时间更优
	  if(b&1)
		  sum=(sum+a)>m?(sum+a-m):(sum+a);
	return sum;
}
12.枚举因子 x的因子n 满足  a^n≡b (mod m)
void DFS(int depth,__int64 a,__int64 b,__int64 m,__int64 n，Number  x)
{
	if(depth==x.size)
	{
		if(ModularExp(a,n,m)==b)      
		{
			if(ans>n)
				ans=n;
		}
	}
	 if(depth>=x.size) ///////防止 生成depth+1 
		return ;
	for(int i=0;i<=x.exp[depth];i++)//如果depth>x.size ,因为x.exp没有初始//化，所以x.exp[depth+1]可能很大 导致TLE！！
	{
	  int temp=n*(int)pow((double)x.prime[depth],i);
      if(temp >=ans)
		  break;
	  DFS(depth+1,a,b,m,temp);
	}
}


13.分解因子
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