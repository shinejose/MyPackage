#include <cmath>
using namespace std;

const int MAXN =100005;
const int MAXLOGN = 20;
const int MAXM =200;
const int MAXLOGM =10;
typedef int ElemType;

struct RMQ2DMAX // maxrmq
{
	ElemType d[MAXN][MAXLOGN+1][MAXM][MAXLOGM+1];
	void Set(int n,int m,ElemType elem[MAXN][MAXM]) // n == row, m == column 
	{
		//input matrix
		//row = n, column = m;
        int k; // k =2^j;
		int b; // b= 2^q;
		//row  ==  i ,j ,k;
		//column = p ,q, b;
		for(int j=0,k=1; k <=n ; k<<=1 , j++ )
			for(int i=0;i + k <=n;i++)
			  for(int q=0,b=1; b<=m ;b<<=1 ,q++ )
				  for(int p=0; p + b <=m;p++)
				  {
					  if( j==0 && q== 0)
							  d[i][j][p][q] = elem[i][p];
					  else if( j==0 ) 
						  d[i][j][p][q] = max( d[i][j][p][q-1]    ,   d[i][j][p+(b>>1)][q-1] );
					  else
						  d[i][j][p][q] = max( d[i][j-1][p][q]    ,   d[i+(k>>1)][j-1][p][q]  );
				  }

	}
	ElemType Get(int r1,int c1,int r2,int c2)//int the matrix area 
	{
        // r2<=r1, c2>=c1;
		int k =(int ) (log((double)(r2-r1+1)) / log(2.0));
		int b =(int ) (log((double)(c2-c1+1)) / log(2.0));
		return max( max( d[r1][k][c1][b]           ,  d[r2-(1<<k)+1][k][c1][b]        ),
			        max( d[r1][k][c2-(1<<b)+1][b]  ,  d[r2-(1<<k)+1][k][c2-(1<<b)+1][b]) );
	}
};


struct RMQ2DMIN // minrmq
{
	ElemType d[MAXN][MAXLOGN+1][MAXM][MAXLOGM+1];
	void Set(int n,int m,ElemType elem[MAXN][MAXM]) // n == row, m == column 
	{
		//input matrix
		//row = n, column = m;
        int k; // k =2^j;
		int b; // b= 2^q;
		//row  ==  i ,j ,k;
		//column = p ,q, b;
		for(int j=0,k=1; k <=n ; k<<=1 , j++ )
			for(int i=0;i + k <=n;i++)
			  for(int q=0,b=1; b<=m ;b<<=1 ,q++ )
				  for(int p=0; p + b <=m;p++)
				  {
					  if( j==0 && q== 0)
							  d[i][j][p][q] = elem[i][p];
					  else if( j==0 ) 
						  d[i][j][p][q] = min( d[i][j][p][q-1]    ,   d[i][j][p+(b>>1)][q-1] );
					  else
						  d[i][j][p][q] = min( d[i][j-1][p][q]    ,   d[i+(k>>1)][j-1][p][q]  );
				  }

	}
	ElemType Get(int r1,int c1,int r2,int c2)//int the matrix area 
	{
        // r2<=r1, c2>=c1;
		int k =(int ) (log((double)(r2-r1+1)) / log(2.0));
		int b =(int ) (log((double)(c2-c1+1)) / log(2.0));
		return min( min( d[r1][k][c1][b]           ,  d[r2-(1<<k)+1][k][c1][b]        ),
			        min( d[r1][k][c2-(1<<b)+1][b]  ,  d[r2-(1<<k)+1][k][c2-(1<<b)+1][b]) );
	}
};
