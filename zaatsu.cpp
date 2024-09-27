#include<algorithm>
#include<vector>
template <class T>
class zaatsu{
private:
  std::vector<T> a;
  bool is_built=true;
public:
  void insert(const T& x){a.emplace_back(x); is_built=false;}
  int operator[](const T& x){
    if(!is_built){
      std::sort(a.begin(),a.end());
      a.erase(std::unique(a.begin(),a.end()),a.end());
      is_built=true;
    }
    int idx=std::lower_bound(a.begin(),a.end(),x)-a.begin();
    assert(idx!=a.size()&&a[idx]==x);
    return idx;
  }
  const T& inv(int k){return a[k];}
};
