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
#include <utility>
#include <bitset>
using namespace std;

typedef long long  ll;
typedef unsigned long long ull;

template<typename   T > 
set<T>  create_prime(T n) {
    set<T>  ret;
    vector<bool> isprime;
    isprime.assign(n+1,true);
    for(T i=2;i<=n;i++)
        for(int j=i+i;j<=n;j+=i)
            isprime[j]=false;
    for(T i=2;i<=n;i++)
        if(isprime[i])
            ret.insert(i);
    return ret;
}

template<typename  T,typename  N > 
map<T,T>  prime_decompose(set<T> prime,N n){
    map<T,T>  ret;
    ret.clear();
    N t =n ;
    for(typename set<T>::iterator it=prime.begin();it!=prime.end() && (*it)*(*it) <= n ;it++){
        if( t % (*it) == 0) ret[*it] = 0 ;
        while ( t  % (*it) == 0 ){
            t /= (*it);
            ret[*it] ++;
        }
    }
    if( t!= 1  ) ret[t]=1;
    return ret;
}

int main(){
    return 0;
}













