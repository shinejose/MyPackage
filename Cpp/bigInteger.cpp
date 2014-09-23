// c header 
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <memory.h>
// c++ header
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <bitset>
#include <utility>
#include <iomanip>
using namespace std;

typedef long long  ll;
typedef unsigned long long ull;

ll a[8] = {8,1,3,4};
ll b[8] = {6,4,3,2};
ll c[8] = {8,2,0,0,3,1,0,1};
ll d[8] = {48,38,46,55,27,18,8};
ll ans[8];
ll wn[8];
ll y[8];
vector<int> ai;
int main(){

    const int WIDTH = 18; 
    int t=2;
    int n=8;
    ll m = pow(2,t*n/2)+1;
    ll w = pow(2,t);
    ll wi = pow(pow(2,t),0) ;
    cout . setf(ios::right);
    cout << "m=" << m << endl;
    for(ll i=0;i<=n;i++){
        cout<<   "w["<< i<< "]= " ;
        cout<<setw(WIDTH/3) <<wi%m ;
        cout<<setw(WIDTH/3) << (wi%m)*(wi%m) ;
        cout<<setw(WIDTH/3)<< (wi%m)*(wi%m)%m ;
        ll ax =0 ;
        ll bx = 0;
        ll cx =0;
        ll dx=0;
        for(int j=0;j<n;j++){
            ax += a[j]*pow((wi%m),j);
            bx += b[j]*pow((wi%m),j);
            cx += c[j]*pow((wi%m),j);
            dx += d[j]*pow((wi%m),j) ;
        }
        cout <<setw( WIDTH/2) << "A="   << setw(WIDTH/2) <<ax <<setw(WIDTH/5+1)<< ax % m ;
        cout <<setw( WIDTH/2) << "B="   << setw(WIDTH/2) <<bx <<setw(WIDTH/5+1)<< bx % m ;
        cout <<setw( WIDTH) << "C="   << setw(WIDTH) <<ax*bx<<setw(WIDTH/5+1)<< (ax*bx) % m  ;
        cout <<setw( WIDTH) << "C'="   << setw(WIDTH) <<cx  ;
        cout <<setw( WIDTH) << "D="   << setw(WIDTH) <<dx <<setw(WIDTH/5+1) << dx%m ;
        cout << endl;
        if( i <n) {
            wn[i] = wi%m;
            y[i] = (ax*bx)%m ;
            
        }
        wi = (wi*w) %m;
    }
    for(int i=0;i<n;i++){
        cout << setw(WIDTH/3)<<"y["<<i<<"]="<<setw(WIDTH/3) << y[i] ;
    }
    cout << endl;
    
    for(int i=0;i<n;i++){
        cout << setw(WIDTH/3)<<"wn["<<i<<"]="<<setw(WIDTH/3) << wn[i] ;
    }
    cout << endl;

    for(int j=0;j<n;j++){
        for(int k=0;k<n;k++){
            ans[j] += ( ( wn[(((-k*j)%n)+n)%n] * y[k] * (-32) ) %m + m) %m  ;
        }
        ans[j] = (ans[j])%m  ;
        cout << setw(WIDTH/3) << "ans["<<j<<"]="<<setw(WIDTH/3) << ans[j] ;
    }
    cout << endl;
    int r ,c;
    r= c =0 ;
    for(int i=0;i<n;i++){
        r = (ans[i] +c ) %10;
        c = (ans[i]+c) /10;
        ai.push_back(r);
    }
    for(auto &i:ai) cout << setw(WIDTH/2) << i ;
    cout << endl;
    
    return 0;
}















