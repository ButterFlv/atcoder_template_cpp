#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>
template <typename KEY, typename VAL>
class static_map{
private:
  std::vector<std::pair<KEY,VAL > > a;
  int my_lower_bound(const KEY& key)const{
    int ok=a.size(), ng=-1;
    while(ok-ng>1){
      int mid=(ok+ng)/2;
      if(a[mid].first>=key)ok=mid;
      else ng=mid;
    }
    return ok;
  }
public:
  static_map(void){}
  void insert(const KEY& key, const VAL& val){
    a.emplace_back(std::make_pair(key, val));
  }
  void make(void){ std::sort(a.begin(), a.end()); }
  bool contains(const KEY& key)const{
    int idx=my_lower_bound(key);
    return (idx!=a.size())?(a[idx].first==key):false;
  }
  const VAL& operator[](const KEY& key)const{
    int idx=my_lower_bound(key);
    assert((idx!=a.size())?(a[idx].first==key):false);
    return a[idx].second;
  }
};
