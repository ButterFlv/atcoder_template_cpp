#include<vector>
#include<cassert>
/**
* ダブリングをするクラス
* arg_vector は サイズを N として
* * a\in arg_vector => a\in [0, N)
* が要求される.
* 他のデータ構造を組み込みたいときは適切にナンバリングするとよい
*/
class Doubling{
private:
  int size, max_depth; long long max_K;
  std::vector<std::vector<int>> dp;
  int log_2(long long K){
    int res=0;
    while((1LL<<res)<K)res++;
    return res;
  }
public:
  Doubling(const std::vector<int>& arg_vector, long long K){
    max_depth=log_2(K)+1;
    size=arg_vector.size();
    max_K=K;
    dp.assign(max_depth, std::vector<int>(size));
    dp[0]=arg_vector;
    for(int d=1;d<max_depth;d++)for(int i=0;i<size;i++)
      dp[d][i]=dp[d-1][dp[d-1][i]];
  }
  int get(int s, long long k)const{
    assert(k<=max_K);
    int res=s, d=0;
    while(k>0){
      if(k&1)res=dp[d][res];
      d++; k>>=1;
    }
    return res;
  }
};
