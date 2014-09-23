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

const double myeps = 1e-8;

typedef double ElemType;

struct Point2d
{
	ElemType x,y;
	Point2d()
	{

	}
	Point2d operator = (Point2d o)
	{
		x=o.x;
		y=o.y;
		return *this;
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
	ElemType DotProduct(Vector2d o)
	{
		return x*o.x+y*o.y;
	}
};
struct Line2d
{
	Point2d s,e;
	Line2d() 
	{}
	Line2d(Point2d ss,Point2d ee)
	{
		s=ss;
		e=ee;
	}
};
struct HalfPlane
{
	Line2d h;
	Vector2d v;
	HalfPlane() {}
	HalfPlane(Vector2d vv,Line2d hh)
	{
		v=vv;
		h=hh;
	}
};
int Filtration(ElemType x)
{
	if(fabs(x)<=myeps)
		return 0;
	if(x>0)
		return 1;
	else
		return -1;
}

bool IsLineIntersection(Line2d u,Line2d v,Point2d &ret) // no consider coincide
{
	if( Filtration((u.e.x-u.s.x)*(v.e.y-v.s.y)-(u.e.y-u.s.y)*(v.e.x-v.s.x))==0 )
		return false;
	else
		ret=u.s;
	double t=((u.s.x-v.s.x)*(v.s.y-v.e.y)-(u.s.y-v.s.y)*(v.s.x-v.e.x))
		/((u.s.x-u.e.x)*(v.s.y-v.e.y)-(u.s.y-u.e.y)*(v.s.x-v.e.x));
	ret.x+=(u.e.x-u.s.x)*t;
	ret.y+=(u.e.y-u.s.y)*t;
	return true;
}

double area_polygon(vector<Point2d> p){
	double s1=0,s2=0;
	int i;
	int n =p.size();
	if(n<3)
		return 0.00;
	for (i=0;i<n;i++)
		s1+=p[(i+1)%n].y*p[i].x,s2+=p[(i)%n].y*p[(i+1)%n].x;
	return (s1-s2)/2;
}

bool HPIcmp(HalfPlane a,HalfPlane  b)
{
	int f1 = Filtration(a.v*b.v);
	if(f1==0 )
	{
		Vector2d s(a.h.s,a.h.e);
		Vector2d t(a.h.s,b.h.s);
		int f2 = Filtration(a.v*t);
		if(f2<0)
			return true ;
		else 
			return false;		
	}
	else if(f1>0)
		return true;
	else
		return false;
}

vector<HalfPlane> upper;
vector<HalfPlane> lower;

deque<HalfPlane> hpans;
deque<Point2d> pans;
vector<Point2d> ans;

vector<HalfPlane> vv;
vector<HalfPlane> v;

Point2d pf,pb;
Point2d ppf,ppb;
HalfPlane front;
HalfPlane top;
Point2d lip;
HalfPlane hpf,hpb;
vector<Point2d> HalfPlaneIntersection(vector<Point2d> pset) //半平面交 O(nlogn) 返回核的顶点集
{
	hpans.clear();
	upper.clear();
	lower.clear();
	ans.clear();
	pans.clear();
	v.clear();
	vv.clear();

	int n =pset.size();
	if(Filtration(area_polygon(pset))>0 )
		{
			for(int i=0;i<n;i++)
			{
				if(pset[i]==pset[(i+1)%n])
					continue;
				v.push_back(HalfPlane(Vector2d(pset[i],pset[(i+1)%n]),Line2d( pset[i],pset[(i+1)%n])));
			}
		}
		else
		{
			for(int i=0;i<n;i++)
			{
				if(pset[i]==pset[(i-1+n)%n])
					continue;
				v.push_back(HalfPlane(Vector2d(pset[i],pset[(i-1+n)%n]),Line2d( pset[i],pset[(i-1+n)%n])));
			}
		}


	Vector2d x(Point2d(0.0,0.0),Point2d(1.0,0.0));
	Vector2d y(Point2d(0.0,0.0),Point2d(0.0,1.0));
	for(vector<HalfPlane>::iterator i=v.begin();i!=v.end();i++)
	{
		if(  Filtration (x.DotProduct(i->v)) < 0 )
			upper.push_back(*i);
		else if(Filtration( x.DotProduct(i->v)) == 0)
		{
			if( Filtration( y.DotProduct(i->v))>=0)
				upper.push_back(*i);
			else
				lower.push_back(*i);
		}
		else
			lower.push_back(*i);
	}
	sort(upper.begin(),upper.end(),HPIcmp);
	sort(lower.begin(),lower.end(),HPIcmp); // 分开上下图壳 ，各自排序

	for(vector<HalfPlane>::iterator i=upper.begin();i!=upper.end();i++) // 斜率相同的平片面 保留最里面的一个
	{
		if( i==upper.begin())
			vv.push_back(*i);
		else
		{
			top = vv.back();
			if(Filtration(top.v*i->v) ==0) 
				continue;
			else
				vv.push_back(*i);
		}
	}
	for(vector<HalfPlane>::iterator i=lower.begin();i!=lower.end();i++)
	{
		if( i==lower.begin())
				vv.push_back(*i);
			else
			{
				top = vv.back();
				if(Filtration(top.v*i->v) ==0) 
					continue;
				else
					vv.push_back(*i);
			}
	}


	for(vector<HalfPlane>::iterator i=vv.begin();i!=vv.end();i++)   // 半平面的选择
	{
		if(hpans.size()==0)
			hpans.push_front(*i);
		else if( hpans.size()==1)
		{
			front = hpans.front();
			hpans.push_front(*i);
			IsLineIntersection(front.h,i->h,lip);
			pans.push_front(lip);
		}
		else
		{
			if(pans.size()!=0)
				pf= pans.front();
			while( pans.size() > 0 && Filtration(i->v*Vector2d(i->h.s,pf))<0 )
			{
				pans.pop_front();
				hpans.pop_front();
				if(pans.size() !=0 )
				pf =pans.front();
			}
			if(pans.size()!=0)
			   pb=pans.back();
			while( pans.size() > 0 && Filtration(i->v*Vector2d(i->h.s,pb))<0 )
			{
				pans.pop_back();
				hpans.pop_back();
				if(pans.size() !=0 )
				pb =pans.back();
			}
			
			front = hpans.front();
			IsLineIntersection(front.h,i->h,lip);
	          
			pans.push_front (lip);
			hpans.push_front(*i);
		}
	}
	//删除两端不合适的
	while(1)
	{
		if(pans.size()<=1)
			break;
		int flag=0;
		if(pans.size()!=0)
			pf=pans.front();
		hpb=hpans.back();
		while(pans.size()>0 && Filtration(hpb.v * Vector2d ( hpb.h.s,pf))<0)
		{
			pans .pop_front();
			hpans.pop_front();
			if(pans.size()!=0)
				pf=pans.front();
			flag=1;
		}
		if(pans.size()!=0)
			pb=pans.back();
		hpf=hpans.front();
		while(pans.size()>0 && Filtration(hpf.v * Vector2d ( hpf.h.s,pb))<0)
		{
			pans .pop_back();
			hpans.pop_back();
			if(pans.size()!=0)
				pb=pans.back();
			flag=1;
		}
		if(!flag)
			break;
	}

	// 加上最后一点
	if(pans.size()>1)
	{
		hpf= hpans.front();
		hpb= hpans.back();
		IsLineIntersection(hpf.h,hpb.h,lip);
		pans.push_back(lip);
	}

	//构造点集
	for(deque<Point2d>::iterator i=pans.begin();i!=pans.end();i++)
		ans.push_back(*i);
	return ans;
}



vector<Point2d> pset;
void Problem()
{
	int n;
	int cases;
	int counting =0;
	for(scanf("%d",&cases);cases;cases--)
//	while(scanf("%d",&n),n)
	{
		scanf("%d",&n);
		Point2d x,y;
		pset.clear();
		for(int i=0;i<n;i++)
		{
		    scanf("%lf%lf",&x.x,&x.y);
			pset.push_back(x);
		}
		pset = HalfPlaneIntersection(pset);
		if(pset.size()<2 ) 
			printf("NO\n");
		else
			printf("YES\n");
	}
}

int main()
{
	clock_t start,end;
	start = clock();
	freopen("c:\\in.txt","r",stdin);
	freopen("c:\\out.txt","w+",stdout);
	end = clock();
	Problem();
	//	printf("%lfs\n",(double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}
