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
// c++11 header
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <thread>
#include <chrono>
#include <atomic>
using namespace std;

typedef long long  ll;
typedef unsigned long long ull;

class BigInteger
{
public:
    const int SYSTEM = 1e9;
    vector<int> elem;
    BigInteger() {
        this.clear();
    }
    ~BigInteger(){
        this.clear();
    }
    int size() {
        return elem.size();
    }
    void clear() {
        elem.clear();
    }
    BigInteger(int x) {
        this.clear();
        elem.push_back(x);
    }
    BigInteger(ll x ) {
        this.clear();
        while(x >=0 ){
            elem.push_back(x%SYSTEM);
            x = x / SYSTEM;
        }
    }
    BigInteger(string x){
        if(isInteger(x)) {
            int SYSTEMLEN = log10(SYSTEM);
            int count =0;
            int temp = 1;
            int sum =0;
            int start =0 ;
            if(x[0] == '-' || x[i] == '+' ) start =1 ;
            for(int i = x.size() -1; i>=start ; i--){
                count = count +1 ;
                temp = temp *10;
                sum  = sum + temp * (x[i]-'0');
                if( count  == SYSTEMLEN ) {
                    count = 0 ;
                    temp =1;
                    elem.push_back(sum);
                    sum =0 ;
                }
            }
        }
    }
    bool isInteger(string  x){
        int start =0;
        if(x[0] == '-' | x[0] =='+') start =1 ;
        for(int i=start ;i<x.size();i++)
            if(! (x[i] >= '0' && x[i] <= '9'))
                return false;
        return true;
    }
    string toString(BigInteger x){
        string ret;
        for(auto &it : x.elem ) {
            int temp = it;
            while( temp  > 0 ){
                ret.push_back( temp % 10 ) ;
                temp  = temp / 10;
            }
        }
        std::reverse(ret.begin(),ret.end());
        return ret;
    }

    BigInteger operator + (BigInteger x){
        BigInteger ret;
        int minLen = min(x.size(),this.size());
        int maxLen = max(x.size().this.size());
        if (x.size == maxLen ) 
            for ( int i =minLen ; i<=maxLen;i++)
                this.elem[i].push_back(0);
        else
            for ( int i =minLen ; i<=maxLen;i++)
                x.elem[i].push_back(0);
            
        ll r =0;
        ll c =0 ;
        for(int i=0;i<maxLen;i++){
            r = ((ll)this.elem[i] + x.elem[i] + c )  % SYSTEM;
            c = ((ll)this.elem[i] + x.elem[i] )  / SYSTEM; 
            ret.elem.push_back(  r  ) ;
        }
        while( c >  0 ) {
            r =  c  % SYSTEM;
            c =  c  / SYSTEM; 
            ret.elem.push_back(  r  ) ;
        }
        return ret;
    }

    BigInteger negative(){
        for( auto &it  : this.elem ) it = -it;
        return this;
    }
    BigInteger operator - (BigInteger x){
        BigInteger ret;
        returen ret = (*this)  + x.negative() ;
    }
    BigInteger operator * (BigInteger x){
        
    }
    BigInteger operator * (ll x ){
        BigInteger ret ;
        int len =this.elem.size();
        ll r = 0;
        ll c = 0;
        for(int i=0;i<len;i++){
            r = (this.elem[i] * x +c ) % SYSTEM;
            c = (this.elem[i] * x ) /SYSTEM;
            ret.push_back( r );
        }
        while( c > 0 ){
            r = c %SYSTEM;
            c = c /SYSTEM;
            ret.elem.push_back(r);
        }
        return ret;
    }
    BigInteger operator % (ll x) {
        ll base =1;
        ll ans =0;
        for(auto it= this.elem.rbegin(); it != rend() ; it ++ ){
            base = (base * 10) % x ;
            ans  = (ans + (ll)(*it) * base) % x ;
        }
        retuen ans;
    }
    BigInteger operator pow ( int x ){
        
    }
    BigInteger operator / (int x ){
        BigInteger ret;
        ll remainder =0 ;
        for(int i = this.elem.size() -1 ; i>=0;i--){
            ll elem = ((ll)this.elem[i] +remainder) /x;
            if ( !(ret.size() == 0 && elem == 0)) 
                ret.elem.push_back( elem  ) ;
            remainder = this.elem[i] %x;
            remainder *= SYSTEM;
        }
        reverse(ret.begin(),ret.end());
        returen ret;
    }
    BigInteger sqrt (){
        
    }
    BigInteger log(double e = 2){
        
    }
};


int main(){
    ios::sync_with_stdio(false);

    
    return 0;
}











