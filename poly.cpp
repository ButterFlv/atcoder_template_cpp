map<string,int> merge_msi(const map<string,int>&,const map<string,int>&);

struct Poly{
  using ll=long long;
  using msi=map<string,int>;
  using con=map<msi,ll>;
  // 内部データ
  con a;
  // コンストラクタ
  Poly(){ return; }
  Poly(const ll& num){ a.emplace(msi{}, num); }
  Poly(const string& str){ a.emplace(msi{{str,1}},1LL); }
  // 表示(文字列を返す)
  string s(){
    if(a.size()==0)return "0";
    string res;
    for(auto& mon:a){
      if(mon.second>0)res+='+';
      res+=to_string(mon.second);
      for(auto& sym:mon.first){
        res+="*"+sym.first;
        if(sym.second>1)res+="**"+to_string(sym.second);
      }
      res+=" ";
    }
    return res;
  }
  // 係数取得 引数に指定できるのは単項式のみ
  ll coeff(const Poly& aim){ return a[aim.a.begin()->first]; }
  // 比較演算子
  friend bool operator<(const Poly& l, const Poly& r){ return l.a < r.a; }
  friend bool operator==(const Poly& l, const Poly& r){ return l.a == r.a; }
  // 各種演算
  friend Poly operator+(const Poly& l, const Poly& r){
    Poly new_Poly=l;
    for(auto& mon:r.a){
      new_Poly.a[mon.first]+=mon.second;
      if(new_Poly.a[mon.first]==0)
        new_Poly.a.erase(new_Poly.a.find(mon.first));
    }
    return new_Poly;
  }
  // 引き算
  friend Poly operator-(const Poly& l, Poly r){
    for(auto& mon:r.a)mon.second=-mon.second;
    return l+r;
  }
  // 掛け算 (まだ (単項式*単項式)or(単項式*定数)or(定数*単項式) のみ)
  // 多項式 * 多項式 にも対応
  // l の一つひとつの項とrの一つ一つの項をかける
  friend Poly operator*(const Poly& l, const Poly& r){
    Poly new_Poly;
    if(l.a.empty()||r.a.empty())return new_Poly;
    vector<Poly> tmp;
    for(auto& mon_l:l.a){
      for(auto& mon_r:r.a){
        Poly new_Mono;
        new_Mono.a.emplace(
          merge_msi(mon_l.first, mon_r.first),
          mon_l.second * mon_r.second
        );
        tmp.push_back(new_Mono);
      }
    }
    for(auto& mon:tmp)new_Poly=new_Poly+mon;
    return new_Poly;
  }
  // 多項式と定数の掛け算
  friend Poly operator*(Poly l, ll r){ for(auto& mon:l.a)mon.second*=r; return l; }
  friend Poly operator*(ll l, Poly r){ return r*l; }
  // べき乗 (繰り返し二乗法)
  Poly pow(int n){
    Poly new_Poly(1),beki; beki.a=a;
    while(n){
      if(n&1)new_Poly=new_Poly*beki;
      beki=beki*beki;
      n>>=1;
    }
    return new_Poly;
  }
};

map<string,int> merge_msi(const map<string,int>& l, const map<string,int>& r){
  map<string,int> new_msi=l;
  for(auto& sym:r){
    if(new_msi.find(sym.first)==new_msi.end())
      new_msi.emplace(sym.first, 0);
    new_msi[sym.first]+=sym.second;
  }
  return new_msi;
}
