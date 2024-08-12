struct Symbol{
  string name;
  friend bool operator<(const Symbol& a, const Symbol& b){ return a.name < b.name; }
  friend bool operator==(const Symbol& a, const Symbol& b){ return a.name == b.name; }
};
map<Symbol,int> merge_symbol_map(const map<Symbol,int>& a,const map<Symbol,int>& b){
  map<Symbol,int> res=a;
  for(const auto& x:b){
    if(res.find(x.first)==res.end())res[x.first]=0;
    res[x.first]+=x.second;
  }
  return res;
}
struct Monomial{
  using ll=long long;
  long long coeff; map<Symbol,int> symbols;
  Monomial(){ return; }
  Monomial(const ll& x){ coeff=x; }
  Monomial(const Symbol& x){ coeff=1LL; symbols[x]=1; }
  Monomial(const string& name){ coeff=1LL; symbols[Symbol{name}]=1; }
  void print(){
    if(coeff==0)return;
    if(coeff>0)cout<<'+';
    if(abs(coeff)!=1)cout<<coeff;
    if(symbols.size())cout<<'*';
    int cnt=0;
    for(auto& elm:symbols){
      cout<<elm.first.name;
      if(elm.second!=1)cout<<"**"<<elm.second;
      if(cnt!=symbols.size()-1)cout<<'*'; cnt++;
    }
  }
  friend Monomial operator*(const Monomial& a, ll b){
    Monomial res=a; res.coeff*=b; return res;
  }
  friend Monomial operator*(ll b, const Monomial& a){
    Monomial res=a; res.coeff*=b; return res;
  }
  friend Monomial operator*(const Monomial& a, const Monomial& b){
    map<Symbol,int> sym=merge_symbol_map(a.symbols, b.symbols);
    Monomial res; res.coeff=a.coeff*b.coeff;
    res.symbols=sym;
    return res;
  }
};
