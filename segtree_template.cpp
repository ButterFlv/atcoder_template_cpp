
#include<utility>

#include<atcoder/segtree>
namespace SegTree{
  // return id
  template<class T, T _id_ele> T _id(void){return _id_ele;}
  // Range Sum
  template<class T> T _sum(T l,T r){return l+r;}
  template<class T> using range_sum=atcoder::segtree<T,_sum<T>,_id<T,(T)0>>;
  // Range Multiple
  template<class T> T _mul(T l,T r){return l*r;}
  template<class T> using range_mul=atcoder::segtree<T,_mul<T>,_id<T,(T)1>>;
  // Range Min
  template<class T> T _min(T l,T r){return std::min(l,r);}
  template<class T, T inf> using range_min=atcoder::segtree<T,_min<T>,_id<T,inf>>;
  // Range Max
  template<class T> T _max(T l,T r){return std::max(l,r);}
  template<class T, T minus_inf> using range_max=atcoder::segtree<T,_max<T>,_id<T,minus_inf>>;
  // Range Min and Max
  template<class T> T _min_max(T l,T r){
    return T(std::min(l.first,r.first),std::max(l.second,r.second)); }
  template<class T, T inf, T minus_inf> std::pair<T,T> _min_max_id(void){
    return std::pair<T,T>(inf,minus_inf); }
  template<class T, T inf, T minus_inf>
  using range_min_max=atcoder::segtree<std::pair<T,T>,_min_max<std::pair<T,T>>,_min_max_id<T,inf,minus_inf>>;
};
