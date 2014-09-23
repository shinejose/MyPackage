#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

// RMQ := range minimum query ;
// construct O(nlog(n) )  ; query O(1) 
// min([i,i+2^j-1]) = min ( min([i,i+2^(j-1)-1])  ,min([i+2^(j-1),[i+2^j-1] );
// dp(i,j) = min(dp(i,j-1),dp(i+2^(j-1),j-1));
template <class T=int> 
class RMQ {
    public:
    vector<vector<T>>  dp;
    vector<vector<T>> pos;
    T (*compare)(const T &a,const T &b) ;
    void init(vector<T> a){
        int n = a.size();
        int k = log2(n) +1;
        vector<int> temp(k);
        dp.assign(n,temp);
        pos.assign(n,temp);
        
        for(int i=0;i<n;i++){
            dp[i][0] = a[i];
            pos[i][0] = i;
        }
        for(int j=1;(1<<j)<=n;j++)
            for(int i=0;i+(1<<j)-1<n;i++){
                dp[i][j] = compare(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
                if(dp[i][j] == dp[i][j-1] )
                    pos[i][j] = pos[i][j-1];
                else
                    pos[i][j] = pos[i+(1<<(j-1))][j-1];
            }
    }
    T get_min(T i,T j){
        T k =log2(j-i+1.0)  ;
        return  compare(dp[i][k],dp[j-(1<<k)+1][k]);
    }
    T get_index(T i,T j){
        T k =log2(j-i+1.0)  ;
        if(dp[i][k] == compare(dp[i][k], dp[j-(1<<k)+1][k]) )
            return pos[i][k];
        else
            return pos[j-(1<<k)+1][k];
    }
};

RMQ<> rmq;
int rmq_min(const int &a,const int &b){
    return min(a,b);
}



int n;
int a[5005];
int d[5005][15];
int pos[5005][15];


void  rmq_set(){
    for(int i=0;i<n;i++){
        d[i][0] = a[i];
        pos[i][0] = i;
    }
    for(int j=1;(1<<j)<=n;j++)
        for(int i=0;i+(1<<j)-1<n;i++){
            d[i][j] = min(d[i][j-1],d[i+(1<<(j-1))][j-1]);
            if(d[i][j] == d[i][j-1] )
                pos[i][j] = pos[i][j-1];
            else
                pos[i][j] = pos[i+(1<<(j-1))][j-1];
        }
}
int rmq_get(int i,int j){
    int k =log2(j-i+1.0)  ;
    return  min(d[i][k],d[j-(1<<k)+1][k]);
}
int rmq_get_index(int i,int j){
    int k =log2(j-i+1.0)  ;
    if(d[i][k]<d[j-(1<<k)+1][k])
        return pos[i][k];
    else
        return pos[j-(1<<k)+1][k];
}
int main(){
    return 0;
}
