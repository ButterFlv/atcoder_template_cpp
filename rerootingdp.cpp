#include<vector>
#include<utility>
#include<stack>
#include<queue>
#include<cassert>
#include<tuple>
/**
* RerootingDP
* -template-
* * class V: 頂点の情報を持たせる構造体
* * class E: 辺の情報を持たせる構造体
* * class S: dpの計算結果を持たせる構造体
* * op: 有効辺に結び付けたdpの結果をマージする関数
* * e: Sの単位元
* * com: dpの結果と頂点と辺の情報をマージする関数
* -args-
* * node_arg: Vのベクター
* * edge_arg: 辺を隣接リスト表現で渡す
*/
template <class V, class E, class S, S (*op)(S,S), S (*id)(), S (*com)(V,E,S)>
class RerootingDP{
private:
  int N;
  std::vector<V> node;
  std::vector<std::vector<std::pair<int,E>>> edge;
  std::vector<std::vector<S>> dp;
  std::vector<S> ans;

  void dfs_post_order(const int& sv){
    std::stack<std::tuple<int,int,S*,E*>> stk;
    stk.emplace(~sv, -1, nullptr, nullptr);
    stk.emplace( sv, -1, nullptr, nullptr);
    while(!stk.empty()){
      auto [v, par, s, e]=stk.top(); stk.pop();
      S res=id();
      if(v>=0){
        for(int i=0;i<edge[v].size();i++){
          int nv=edge[v][i].first; if(nv==par)continue;
          stk.emplace(~nv, v, &dp[v][i], &edge[v][i].second);
          stk.emplace( nv, v, &dp[v][i], &edge[v][i].second);
        }
      }else if(par==-1){
        for(const auto& ns:dp[~v])res=op(res,ns);
      }else{
        v=~v;
        for(int i=0;i<edge[v].size();i++){
          if(edge[v][i].first==par)continue;
          res=op(res, dp[v][i]);
        }
        *s=com(node[v], *e, res);
      }
    }
  }

  /**
  累積を計算するのにBFSのほうがいい
  */
  void bfs_pre_order(const int& sv){
    std::vector<bool> used(N, false);
    std::queue<std::tuple<int,int,S>> que;
    que.emplace(sv, -1, id());
    while(!que.empty()){
      auto [v,par,s]=que.front(); que.pop();
      if(used[v])continue; used[v]=true;
      int L=edge[v].size(); if(L==0)continue;
      for(int i=0;i<L;i++)if(edge[v][i].first==par){
        dp[v][i]=s; break;
      }
      std::vector<S> acc_l(L+1, id()), acc_r(L+1, id());
      for(int i=0;i<L;i++){
        acc_l[i+1]=op(acc_l[i], dp[v][i]);
        acc_r[L-1-i]=op(acc_r[L-i], dp[v][L-1-i]);
      }
      ans[v]=acc_l.back();
      for(int i=0;i<L;i++){
        int nv=edge[v][i].first; if(used[nv])continue;
        que.emplace(nv, v, com(node[v], edge[v][i].second, op(acc_l[i],acc_r[i+1])));
      }
    }
  }

public:
  RerootingDP(std::vector<V> node_arg,
          std::vector<std::vector<std::pair<int,E>>> edge_arg):
          node(node_arg),edge(edge_arg){
    assert((int)node_arg.size()==(int)edge_arg.size());
    N=node_arg.size();
  }
  void make(const int sv=0){
    dp.clear();
    dp.resize(N);
    for(int i=0;i<N;i++)
      dp[i].resize(edge[i].size(), id());
    ans.clear(); ans.resize(N, id());
    dfs_post_order(sv);
    bfs_pre_order(sv);
  }
  S get(int v){ return ans[v]; }
};
