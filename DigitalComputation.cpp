struct DigitalComputation 
{
	struct Polynomial
	{
		typedef double PolyValue;
		typedef double CoefficientValue;
		struct Hernor //����ʽ��ֵ O(n) �ؾ����㷨
		{
			// �������ʽ������)  ����ʽ�Ĵ���
			// �� ����ʽ p(x*) ��ֵ  O(n)
			PolyValue Value(CoefficientValue *a,int n,int xstar) // nΪ����ʽ�Ĵ��� �� a ϵ������
			{
				PolyValue  bi,bj;
				bi = a[0];
				for(int i=1;i<=n;i++) 
				{
					bj = bi * xstar + a[i];
					bi = bj;
				}
				return bj;
			}
			// �����ʽ�ĵ��� P'(x*) O(n��
			PolyValue PieValue(CoefficientValue *a,int n,int xstar) // nΪ����ʽ�Ĵ��� �� a ϵ������
			{
				PolyValue bi,bj,ci,cj;
				bi = a[0];
				ci = bi;
				for(int i = 1; i<n;i++)
				{
					bj  = bi *xstar +a[i];
					bi = bj;
					cj = ci*xstar +bi;
					ci = cj;
				}
				return cj;
			}
			void Test()
			{
				double a[10]={2,0,-3,3,-4};
				printf("%lf\n",Value (a,4,-2));
	            printf("%lf\n",PieValue (a,4,-2));
			}
		}hernor;
		// ��֪�ĵ�
		struct Point
		{
			PolyValue x,y;
			Point(){};
			Point(PolyValue xx,PolyValue yy) 
			{
				x= xx;
				y= yy;
			}
			Point operator = (Point tmp)
			{
				x=tmp.x;
				y=tmp.y;
				return *this;
			}
		};
		struct LagrangeInterpolation  //�������ղ�ֵ����ʽ 
		{
			// ����֪�ĵ�����������㣨x*,y*);
            PolyValue Interpolation(Point *p,int n,PolyValue xstar)//  O(n^2) 
			{
				PolyValue res=0;
				for(int k=0;k<n;k++)
				{
					PolyValue lk,lkup,lkdown;
					lkup=lkdown =1;
					 for(int i =0;i< n;i++)
					  if(i!= k)
					  {
						  lkup *= (xstar-p[i].x);
						  lkdown *= (p[k].x-p[i].x );
					  }
					lk = lkup / lkdown ;
					res += p[k].y*lk;
				}
				return res ;
			}
			void Test()
			{
				 Point p[10];
				 p[0] = Point(4,10);
				 p[1] = Point(5,5.25);
				 p[2] = Point(6,1);
				 printf("%lf\n",Interpolation(p,3,18));

				 p[0] = Point(0.32,0.314567);
				 p[1] = Point(0.34,0.333487);
				 p[2] = Point(0.36,0.352274);

				 printf("%lf\n",Interpolation(p,3,0.3367));

			}
		}largrangeInterpolation ;
		struct NewtonInterpolation //ţ�ٲ�ֵ��
		{
			const static int MAXN = 100; // ����ʽ����ߴ���
			PolyValue DQmat[MAXN][MAXN];
			int  n ; //����ʽ�Ĵ���
			NewtonInterpolation()
			{
				n = 0 ;
			}
			void Init()
			{
				n=0;
			}
			void AddInterpolation(Point x)
			{
				DQmat[n][0]=x.x;
				DQmat[n][1]=x.y;
				for(int i=0 ;i<n;i++)
					DQmat[n][2+i]=  (DQmat[n][i+1]-DQmat[n-1][i+1]) /(DQmat[n][0]-DQmat[n-i-1][0]);
				n++;
			}
			PolyValue Interpolation(PolyValue xstar)//���ؾ����㷨��˼�뽵��O(n) 
			{
				PolyValue res;
				res = DQmat[n-1][n];
				for(int i=n-2;i>=0;i--)
					res = DQmat[i][i+1]+ res*(xstar-DQmat[i][0]);
				return res;
			}
			void Test()
			{
				AddInterpolation(Point(0.4,0.41075));
				AddInterpolation(Point(0.55,0.57815));
				AddInterpolation(Point(0.65,0.69675));
				AddInterpolation(Point(0.8,0.88811));
				AddInterpolation(Point(0.9,1.02652));
				AddInterpolation(Point(1.05,1.25382));
				printf("%lf\n",Interpolation(0.596));
				Init();
				AddInterpolation(Point(0.32,0.314567));
				AddInterpolation(Point(0.34,0.333487));
				AddInterpolation(Point(0.36,0.352274));
				printf("%lf\n",Interpolation(0.3367)) ;
				Init();
				AddInterpolation(Point(0,1));
				AddInterpolation(Point(1,2));
				AddInterpolation(Point(2,4));
				AddInterpolation(Point(3,7));
				for(int i=0;i<n;i++)
					printf("%lf ",DQmat[i][i+1]);
			}
		}newtonInterpolation;
	}polynomial;
};