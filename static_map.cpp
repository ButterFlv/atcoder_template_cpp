/**
* キーの追加がない map
* std::map よりも検索が高速でメモリ効率も良い
*/
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

template <class KEY, class VAL>
class static_map{
private:
  std::vector<std::pair<KEY,VAL > > a;
  bool is_built=true;
  int my_lower_bound(const KEY& key)const{
    int ok=a.size(), ng=-1;
    while(ok-ng>1){
      int mid=(ok+ng)/2;
      if(a[mid].first>=key)ok=mid;
      else ng=mid;
    }
    return ok;
  }
  void make(void){ std::sort(a.begin(), a.end()); is_built=true; }
public:
  static_map(void){}
  void emplace(const KEY& key, const VAL& val){
    is_built=false;
    a.emplace_back(std::make_pair(key, val));
  }
  bool count(const KEY& key){
    if(!is_built)make();
    int idx=my_lower_bound(key);
    return idx!=a.size()&&a[idx].first==key;
  }
  VAL& operator[](const KEY& key){
    if(!is_built)make();
    int idx=my_lower_bound(key);
    assert(idx!=a.size()&&a[idx].first==key);
    return a[idx].second;
  }
  int size(void)const{ return a.size(); }
  const std::vector<std::pair<KEY,VAL > >& get(void){ return a; }
};
