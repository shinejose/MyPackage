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
using namespace std;
/*
const double eps= 1e-8;
const double PI = atan2(0.0,-1.0);
typedef double ElemType;




struct Point2d
{
	ElemType x,y;
	Point2d()
	{
		
	}
	Point2d(int xx,int yy)
	{
		x=xx;
		y=yy;
	}
	friend int Filtration(ElemType x);
	bool operator ==(Point2d o)
	{
		if( Filtration(o.x-x) == 0 && Filtration(o.y-y) == 0 )
			return true;
		else
			return false ;
	}
};
struct Vector2d
{
	ElemType x,y;
	Vector2d()
	{
	}
	Vector2d(Point2d a,Point2d b) //  a->b
	{
		x=b.x-a.x;
		y=b.y-a.y;
	}
	ElemType operator *(Vector2d o) 
	{
		return (x*o.y-o.x*y);
	}
	int GetPosition(Vector2d o)
	{
		return Filtration(x*o.y-o.x*y);
		// return 0 == *this 与 o 在一条直线上
	}
    ElemType DotProduct(Vector2d o)
	{
		return x*o.x+y*o.y;
	}
	ElemType operator ,(Vector2d o)
	{
		return x*o.x+y*o.y;
	}
	ElemType Mo2()
	{
		return x*x+y*y;
	}
	ElemType Mo()
	{
		return sqrt(x*x+y*y);
	}

};
struct LineSegment
{
	Point2d s;
	Point2d e;
	
};
struct Polygon
{
	static const int MAXPOLYGON = 105;
	int size;
	Point2d elem[MAXPOLYGON ];
	Polygon()
	{
		size=0;
	}
	void init()
	{
		size=0;
	}
	void push_back(Point2d o)
	{
		elem[size++] =o;
	}
	void pop_back()
	{
		size--;
	}
	Point2d PolygonBarycenter()
	{
		//多边形重心 n为点数，p为点集 ，返回重心点
		ElemType A=0,cx=0,cy=0;
		Point2d res,s(0.0,0.0);
		Vector2d p1,p2;
		for(int i=0;i<size-1;i++)
		{
			Vector2d p1(s,elem[i]);
			Vector2d p2(s,elem[i+1]);
			A+=p1*p2/2;
			cx+=(p1.x+p2.x)*(p1*p2);
			cy+=(p1.y+p2.y)*(p1*p2);
		}
		Vector2d p3(s,elem[size-1]);
		Vector2d p4(s,elem[0]);
		A+=p3*p4/2;
		cx+=(p3.x+p4.x)*(p3*p4);
		cy+=(p3.y+p4.y)*(p3*p4);
		res.x=cx/(6*A);
		res.y=cy/(6*A);
		return res;
	}
	friend ElemType Distance(Point2d ,Point2d );

	friend Polygon CoverHull(Polygon o) ;
};
struct Circle
{
	ElemType r;
	Point2d o;
};
int Filtration(ElemType x)
{
	if(abs(x)<=eps)
		return 0;
	if(x>0)
		return 1;
	else
		return -1;
}

ElemType Distance(Point2d a,Point2d b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
// 向量的点积
double  DotProduct(Vector2d a,Vector2d o)
{
	return a.x*o.x+a.y*o.y;
}
//点是否在线段上
bool IsPointInLineSegment(Point2d a,LineSegment b)  //用点积来判断
{
	Vector2d t1(a,b.e);
	Vector2d t2(a,b.s);
	if(Filtration(DotProduct(t1,t2))<=0)
		return true;
	else 
		return false;
}

//线段是否相交
bool  IsLineSegmentIntersection(LineSegment x,LineSegment y,Point2d &p)
	{ 
		//IsLineSegmentIntersection(线段是否相交) 规范相交（p为交点） 1，非规范相交2，不相交0,
	    //   p; //交点  //有一种非规范相交不满足的 
	   //非规范相交 ： 相交点为某一线段的端点 || 有无数的个交点
		
		// a == x.s , b==x.y  , c== y.s , d==y.e  
		ElemType s1,s2,s3,s4;
		int d1,d2,d3,d4;
		int ans;
		// a == x.s   ;   b == x.e  ;  c == y.s  ;  d=  y.e ;
		Vector2d ab(x.s    ,x.e);
		Vector2d ac(x.s    ,y.s);
		Vector2d ad(x.s    ,y.e);

		Vector2d cd(y.s  ,y.e);
		Vector2d ca(y.s  ,x.s);
		Vector2d cb(y.s  ,x.e);

		d1=Filtration(s1=ab*ac);
		d2=Filtration(s2=ab*ad);
		d3=Filtration(s3=cd*ca);
		d4=Filtration(s4=cd*cb);

		if((d1^d2)==-2&&(d3^d4)==-2)    // 1^-1 
		{
			p.x=(y.s.x*s2-y.e.x*s1)/(s2-s1);
			p.y=(y.s.y*s2-y.e.y*s1)/(s2-s1);
			
			ans = 1;
		}
		// 若a,b,c共线，且c在ab的范围内 
		if( d1==0 && IsPointInLineSegment(y.s,x) ||    
			d2==0 && IsPointInLineSegment(y.e,x) ||
			d3==0 && IsPointInLineSegment(x.s,y) ||
			d4==0 && IsPointInLineSegment(x.e,y) )
			ans =  2;
		ans = 0;
		if(ans > 0 )
			return true;
		else
			return false;
	}
// 凸包
static Point2d key ;
bool CoverHullCmp(const Point2d & a, const Point2d & b)
{

	Vector2d va(key,a);
	Vector2d vb(key,b);
	int temp=Filtration(va*vb);
	if(temp==0)
		return (Distance(key,a)<Distance(key,b));
	else if (temp>0)
		return true;
	else 
		return false;
}
Polygon CoverHull(Polygon o)
{
	int minindex =0;
	for(int i=1;i<o.size;i++)
		if(o.elem[i].y<o.elem[minindex].y||
			(o.elem[i].y==o.elem[minindex].y && o.elem[i].x<o.elem[minindex].x))
			minindex=i;
	swap(o.elem[0],o.elem[minindex]);
	key =o.elem[0];
	sort(o.elem+1,o.elem+o.size,CoverHullCmp);

	Polygon res;
	res.push_back(o.elem[0]);
	res.push_back(o.elem[1]);
	res.push_back(o.elem[2]);
	o.push_back(o.elem[0]);
	for(int i=3;i<o.size;i++)
	{
		while(1)
		{
			Vector2d ab(res.elem[res.size-2],res.elem[res.size-1]);
		    Vector2d ac(res.elem[res.size-2],o.elem[i]);
			if(Filtration(ab*ac)<0)
				res.pop_back();
			else
				break;
		}
		res.push_back(o.elem[i]);
	}
	return res;
}



/// 最近点对

#define Min(x,y) ((x)>(y)?(x):(y))
bool Cmp_x(const Point2d &a,const Point2d &b)
{
    if(a.x==b.x)
        return a.y<b.y;
    return a.x<b.x;
}
bool Cmp_y(const Point2d &a,const Point2d &b)
{
    if(a.y==b.y)
        return a.x<b.x;
    return a.y<b.y;
}

double  NearestPoint(int l,int r,Point2d *p,Point2d *midp)
{ 
    if(r-l==1)
        return Distance(p[l],p[r]);
    else if(r-l==2)
        return Min(Distance(p[l],p[l+1]),Min(Distance(p[l+1],p[r]),Distance(p[l],p[r])));
    int mid=(l+r)/2;
    double  mindist=Min(NearestPoint(l,mid,p,midp),NearestPoint(mid+1,r,p,midp));
    int i,j,count=0;
    for(i=mid;i>=l&&p[mid].x-p[i].x<mindist;i--)
        midp[count++]=p[i];
    for(i=mid+1;i<=r&&p[i].x-p[mid+1].x<mindist;i++)
        midp[count++]=p[i];
    sort(midp,midp+count,Cmp_y);
    for(i=0;i<count;i++)
        for(j=i+1;j<count&&midp[j].y-midp[i].y<mindist;j++)
            mindist=Min(mindist,Distance(midp[i],midp[j]));
        return mindist;
}  

double NearestPointDistance(Point2d *p,Point2d *midp,int n)
{
	 sort(p,p+n,Cmp_x);  
	 return NearestPoint(0,n-1,p,midp);
}

//半平面交
*/
const double eps = 1e-8;
const double pi = std::acos(-1.0);
//点
class point
{
public:
    double x, y;
    point(){};
    point(double x, double y):x(x),y(y){};
 
    static int xmult(const point &ps, const point &pe, const point &po)
    {
        return (ps.x - po.x) * (pe.y - po.y) - (pe.x - po.x) * (ps.y - po.y);
    }
};
 
//两点表示的向量
class pVector
{
public:
    point s, e;//两点表示，起点[s]，终点[e]
 
    pVector(){}
    pVector(const point &s, const point &e):s(s),e(e){}
 
    //向量与向量的叉乘,参数：向量[_Off]
    double operator *(const pVector &_Off) const
    {
        return (e.x - s.x) * (_Off.e.y - _Off.s.y) - (e.y - s.y) * (_Off.e.x - _Off.s.x);
    }
 
    //直线平行，参数：直线向量[_Off]
    bool parallel(const pVector &_Off) const
    {
        return std::fabs((*this) * _Off) < eps;
    }
 
    //两直线交点，参数：目标直线[_Off]
    point crossLPt(pVector _Off)
    {
        //注意先判断平行和重合
        point ret = s;
        double t = ((s.x - _Off.s.x) * (_Off.s.y - _Off.e.y) - (s.y - _Off.s.y) * (_Off.s.x - _Off.e.x))
                / ((s.x - e.x) * (_Off.s.y - _Off.e.y) - (s.y - e.y) * (_Off.s.x - _Off.e.x));
        ret.x += (e.x - s.x) * t;
        ret.y += (e.y - s.y) * t;
        return ret;
    }
};
 
class polygon
{
public:
    const static long maxpn = 20010;
    point pt[maxpn];//点（顺时针或逆时针）
    long n;//点的个数
 
    //-----------半平面交-------------
    //复杂度:O(nlog2(n))
    //#include <algorithm>
    //半平面计算极角函数[如果考虑效率可以用成员变量记录]
    static double hpc_pa(const pVector &_Off)
    {
        return atan2(_Off.e.y - _Off.s.y, _Off.e.x - _Off.s.x);
    }
    //半平面交排序函数[优先顺序: 1.极角 2.前面的直线在后面的左边]
    static bool hpc_cmp(const pVector &l, const pVector &r)
    {
        double lp = hpc_pa(l), rp = hpc_pa(r);
        if(fabs(lp - rp) > eps)
            return lp < rp;
        return point::xmult(l.s, r.e, r.s) < 0.0;
    }
    //用于计算的双端队列
    pVector dequeue[maxpn];
    //获取半平面交的多边形
    //参数：向量集合[l]，向量数量[ln];(半平面方向在向量左边）
    polygon& halfPanelCross(pVector _Off[], int ln)
    {
        int i, tn;
        n = 0;
        std::sort(_Off, _Off + ln, hpc_cmp);
        //平面在向量左边的筛选
        for(i = tn = 1; i < ln; i ++)
 
            if(fabs(hpc_pa(_Off[i]) - hpc_pa(_Off[i - 1])) > eps)
                _Off[tn ++] = _Off[i];
        ln = tn;
        int bot = 0, top = 1;
        dequeue[0] = _Off[0];
        dequeue[1] = _Off[1];
        for(i = 2; i < ln; i ++)
        {
            if(dequeue[top].parallel(dequeue[top - 1]) ||
                dequeue[bot].parallel(dequeue[bot + 1]))
                return (*this);
            while(bot < top &&
                point::xmult(dequeue[top].crossLPt(dequeue[top - 1]), _Off[i].e, _Off[i].s) > eps)
                top --;
            while(bot < top &&
                point::xmult(dequeue[bot].crossLPt(dequeue[bot + 1]), _Off[i].e, _Off[i].s) > eps)
                bot ++;
            dequeue[++ top] = _Off[i];
        }
 
        while(bot < top &&
            point::xmult(dequeue[top].crossLPt(dequeue[top - 1]), dequeue[bot].e, dequeue[bot].s) > eps)
            top --;
        while(bot < top &&
            point::xmult(dequeue[bot].crossLPt(dequeue[bot + 1]), dequeue[top].e, dequeue[top].s) > eps)
            bot ++;
        //计算交点(注意不同直线形成的交点可能重合)
        if(top <= bot + 1)
            return (*this);
        for(i = bot; i < top; i ++)
            pt[n ++] = dequeue[i].crossLPt(dequeue[i + 1]);
        if(bot < top + 1)
            pt[n ++] = dequeue[bot].crossLPt(dequeue[top]);
        return (*this);
    }
};
 
pVector line[ 20010];
point pt[ 20010];
point a,b;
polygon ans;
 
double area_polygon(int n,point* p){
	double s1=0,s2=0;
	int i;
	for (i=0;i<n;i++)
		s1+=p[(i+1)%n].y*p[i].x,s2+=p[(i+1)%n].y*p[(i+2)%n].x;
	return fabs(s1-s2)/2;
}

int Problem()
{
    int n, i;
    int t = 1;
    //freopen("d:\\in.txt", "r", stdin);
    //freopen("d:\\myout.txt", "w", stdout);
    while(scanf("%d", &n)!=EOF)
    {
        for(i = 0; i < n; i ++)
         {
			 scanf("%lf%lf%lf%lf", &a.x, &a.y,&b.x,&b.y);
            line[i] = pVector( a,b);
		}
        line[n] = pVector(point(0.0,0.0),point(10000.0,0.0));
		line[n+1] = pVector(point(10000.0,0.0),point(10000.0,10000.0));
		line[n+2] =pVector(point(10000.0,10000.0),point(0.0,10000.0));
		line[n+3] =pVector(point(0.0,10000.0),point(0.0,0.0));
		n = n+4;
        ans.halfPanelCross(line, n);
			for(int i=0;i<ans.n;i++)
				pt[i]=ans.pt[i];
			printf("%.1lf\n",area_polygon(ans.n,pt));
	

     
    }
    return 0;
}
int main()
{
	clock_t start,end;
	start = clock();
	freopen("in.txt","r",stdin);
	//	freopen("out.txt","w+",stdout);
	end = clock();
	Problem();
	//	printf("%lfs\n",(double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}