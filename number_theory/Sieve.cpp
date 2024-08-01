class Sieve{
  using ll=long long;
  using vb=vector<bool>;
  using vi=vector<int>;
  using pli=pair<ll,int>;
  using vpli=vector<pli>;
public:
  bool isprime(int);
  vpli factorint(ll);
  vi get_mobius(int);
  vi get_d(int);
  vi get_prime();
  Sieve(int N=9){
    make_sieve(N);
    make_prime_table(N);
  }
private:
  vb sieve; vi prime_table;
  void make_sieve(int);
  void make_prime_table(int);
};

bool Sieve::isprime(int N){
  assert(N<sieve.size());
  return sieve[N];
}
Sieve::vpli Sieve::factorint(ll N){
  assert(N>0);
  vpli res;
  int limit=(int)sqrt(N) + 9;
  int idx=0; int p=prime_table[idx];
  while(p<limit){
    if(N%p==0){
      res.push_back(pli{p,0});
      while(N%p==0){ N/=p; res.back().second++; }
    }
    if(++idx<prime_table.size())p=prime_table[idx];
    else ++p;
  }
  if(N!=1)res.push_back(pli{N,1});
  return res;
}
Sieve::vi Sieve::get_mobius(int N){
  vi res(N+1, 1);
  vb isp(N+1, true);
  isp[0]=false; isp[1]=false;
  for(int p=2;p<=N;p++){
    if(!isp[p])continue;
    res[p]=-1;
    for(int n=p*2;n<=N;n+=p){
      isp[n]=false;
      res[n]=-res[n];
      if((n/p)%p==0)res[n]=0;
    }
  }
  return res;
}
Sieve::vi Sieve::get_d(int N){
  vi res(N+1);
  res[0]=(int)1e9;
  for(int n=1;n<=N;n++)for(int m=n;m<=N;m+=n)res[m]++;
  return res;
}
Sieve::vi Sieve::get_prime(){ return prime_table; }

void Sieve::make_sieve(int N){
  sieve.resize(N+1, true);
  sieve[0]=0; sieve[1]=0;
  for(int p=2;p<=N;p++){
    if(!sieve[p])continue;
    for(int n=p*2;n<=N;n+=p)sieve[n]=false;
  }
}
void Sieve::make_prime_table(int N){
  for(int i=0;i<=N;i++)
    if(sieve[i])prime_table.push_back(i);
}
