#include <algorithm>
#include <vector>
#include <cassert>
template <class T>
class zaatsu{
private:
  std::vector<T> a;
  bool is_built=true;
  void make(void){
    if(!is_built){
      std::sort(a.begin(),a.end());
      a.erase(std::unique(a.begin(),a.end()),a.end());
      is_built=true;
    }
  }
public:
  void insert(const T& x){a.emplace_back(x); is_built=false;}
  int operator[](const T& x){
    make();
    int idx=std::lower_bound(a.begin(),a.end(),x)-a.begin();
    assert(idx!=a.size()&&a[idx]==x);
    return idx;
  }
  const T& inv(int k){make(); return a[k];}
  size_t size(void){make(); return a.size();}
  auto begin(void){make(); return a.begin();}
  auto end(void){make(); return a.end();}
};
