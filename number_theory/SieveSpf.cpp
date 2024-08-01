class SieveSpf{
  using ll=long long;
  using vi=vector<int>;
  using pii=pair<int,int>;
  using vpii=vector<pii>;
public:
  vpii factorint(int);
  SieveSpf(int N){
    make_spf(N);
  }
private:
  vi spf;
  void make_spf(int);
};

SieveSpf::vpii SieveSpf::factorint(int N){
  assert(0<N && N<spf.size());
  vpii res;
  while(N!=1){
    const auto& p=spf[N];
    res.push_back(pii{p,0});
    while(N%p==0){ N/=p; res.back().second++; }
  }
  return res;
}

void SieveSpf::make_spf(int N){
  spf.resize(N+1);
  spf[0]=1; spf[1]=1;
  for(int p=2;p<=N;p++){
    if(spf[p])continue; spf[p]=p;
    for(int n=p*2;n<=N;n+=p)if(!spf[n])spf[n]=p;
  }
}
