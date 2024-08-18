class Mersenne_modint{
  using ul=uint_fast64_t;
  const ul MASK30=(1ULL<<30)-1;
  const ul MASK31=(1ULL<<31)-1;
  const ul MOD=(1ULL<<61)-1;
  const ul MASK61=MOD;
  const ul POSITIVIZER=MOD*4;
  ul CalcMod(const ul& x){
    ul xu=x>>61, xd=x&MASK61;
    ul res=xu+xd;
    if(res>=MOD)res-=MOD;
    return res;
  }
  ul Mul(const ul& a, const ul& b){
    ul au=a>>31, ad=a&MASK31;
    ul bu=b>>31, bd=b&MASK31;
    ul mid=ad*bu+au*bd;
    ul midu=mid>>30, midd=mid&MASK30;
    return CalcMod(au*bu*2+midu+(midd<<31)+ad*bd);
  }
  ul extgcd(const ul& x){
    long long a=x, b=MOD, u=1, v=0;
    while(b){
      long long t=a/b;
      a-=t*b; swap(a, b);
      u-=t*v; swap(u, v);
    }
    u%=MOD; if(u<0)u+=MOD;
    return u;
  }
  ul a;
public:
  Mersenne_modint(const ul& x=0):a(CalcMod(x)){}
  Mersenne_modint inv(){ return Mersenne_modint(extgcd(a)); }
  ul val(){ return a; }
  Mersenne_modint operator=(const Mersenne_modint& rhs){
    a=rhs.a;
    return *this;
  }
  bool operator==(const Mersenne_modint& rhs){
    return a==rhs.a;
  }
  Mersenne_modint operator+(const Mersenne_modint& rhs){
    return Mersenne_modint(a+rhs.a);
  }
  Mersenne_modint operator-(const Mersenne_modint& rhs){
    return Mersenne_modint(a+POSITIVIZER-rhs.a);
  }
  Mersenne_modint operator*(const Mersenne_modint& rhs){
    return Mersenne_modint(Mul(a,rhs.a));
  }
  Mersenne_modint operator/(const Mersenne_modint& rhs){
    return Mersenne_modint(Mul(a,extgcd(rhs.a)));
  }
  Mersenne_modint& operator+=(const Mersenne_modint& rhs){
    a=CalcMod(a+rhs.a);
    return *this;
  }
  Mersenne_modint& operator-=(const Mersenne_modint& rhs){
    a=CalcMod(a+POSITIVIZER-rhs.a);
    return *this;
  }
  Mersenne_modint& operator*=(const Mersenne_modint& rhs){
    a=Mul(a,rhs.a);
    return *this;
  }
  Mersenne_modint& operator/=(const Mersenne_modint& rhs){
    a=Mul(a,extgcd(rhs.a));
    return *this;
  }
};

using mint=Mersenne_modint;
