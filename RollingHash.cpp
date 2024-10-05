class Hashing{
private:
  using ul = unsigned long long;
  const ul MASK30 = (1ULL << 30) - 1;
  const ul MASK31 = (1ULL << 31) - 1;
  const ul MOD = (1ULL << 61) - 1;
  const ul MASK61 = MOD;
  std::random_device seed_gen;
  std::mt19937_64 engine;
  ul base;
  const signed base_area = 1000009;
  vector<ul> B;
  // Calc (Number) mod 2^61-1
  ul calc_mod(ul x){
    ul xu = x >> 61;
    ul xd = x & MASK61;
    ul res = xu + xd;
    if (res >= MOD) res -= MOD;
    return res;
  }
  // Calc a*b mod 2^61-1
  ul mul(ul a, ul b){
    ul au = a >> 31;
    ul ad = a & MASK31;
    ul bu = b >> 31;
    ul bd = b & MASK31;
    ul mid = ad * bu + au * bd;
    ul midu = mid >> 30;
    ul midd = mid & MASK30;
    return calc_mod(au * bu * 2ULL + midu + (midd << 31) + ad * bd);
  }
public:
  Hashing():engine(seed_gen()),base(((ul)engine())%MOD),B(base_area){
    B[0]=1ULL;
    for(signed i=1;i<base_area;i++)B[i]=mul(B[i-1],base);
  }
  vector<ul> make(const string& S){
    vector<ul> hash(S.size()+1); hash[0]=0;
    for(size_t i=0;i<S.size();i++)hash[i+1]=calc_mod(mul(hash[i], base)+S[i]);
    return hash;
  }
  ul get(const vector<ul>& hash, int l, int r){
    return calc_mod(hash[r]+MOD-mul(hash[l],B[r-l]));
  }
  ul pow(ul a){
    ul res=1ULL, b=base;
    while(a){
      if(a&1)res=mul(res,b);
      b=mul(b,b); a>>=1;
    }
    return res;
  }
};
