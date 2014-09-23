// 1. enumate floor(n/x)   | x belongs of [1,n]   |  O(2*sqrt(n))
template<typename Integer>
vector<tuple<Integer,Integer,Integer>>
    enumate_floor_n_divide_x(Integer n) ;











// 1. enumate floor(n/x)   | x belongs of [1,n]   |  O(2*sqrt(n)) 
// input  : n
// output : ([n/i],i,next)
// example : enumate_floor_n_divide_x(100)
// return : {(100,1,1), (50,2,2), (33,3,3), (25,4,4), (20,5,5), (16,6,6), (14,7,7), (12,8,8), (11,9,9), (10,10,10), (9,11,11), (8,12,12), (7,13,14), (6,15,16), (5,17,20), (4,21,25), (3,26,33), (2,34,50), (1,51,100)}
template<typename Integer>
vector<tuple<Integer,Integer,Integer>>
enumate_floor_n_divide_x(Integer n){
    vector<tuple<Integer,Integer,Integer>> ret;
    for(Integer i=1,next =1 ;i<=n;i = next +1 ){
        next = n / (n /i) ;
        ret.push_back(make_tuple(n/i,i,next)) ;
    }
    return ret;
}

