#include<vector>
#include<queue>
#include<tuple>
namespace graph_algorithm{
  /* 終点のみのリスト */
  using Graph=std::vector<std::vector<int>>;
  /* (終点, 重み) のリスト */
  using WGraph=std::vector<std::vector<std::pair<int,long long>>>;
  /* 隣接行列表現 */
  using MGraph=std::vector<std::vector<long long>>;
  const int inf=1000000000;
  const long long INF=1000000000000000000;

  /**
  * 隣接リスト表現された重み無し有向グラフの頂点 s から頂点 g への距離を返す.
  * 頂点数: N, 辺の数: M に対して O(N+M)
  * 頂点 s から頂点 g に到達不可能なとき, inf を返す
  */
  int bfs_list(const Graph& G, int s, int g){
    int N=G.size();
    std::vector<bool> used(N, false);
    std::vector<int> dist(N, inf);
    std::queue<int> d; d.push(s);
    dist[s]=0;
    while(!d.empty()){
      int v=d.front(); d.pop();
      if(used[v])continue;
      used[v]=true;
      for(const int& nv:G[v]){
        if(dist[v]+1<dist[nv]){
          dist[nv]=dist[v]+1;
          d.push(nv);
        }
      }
    }
    return dist[g];
  }

  /**
  * 隣接リスト表現された重み有り有向グラフの頂点 s から頂点 g への距離を返す.
  * 頂点数: N, 辺の数: M に対して O((N+M)log(N+M))
  * 頂点 s から頂点 g に到達不可能なとき, INF を返す
  * long long 型であるのに注意
  * 各辺の重みは非負
  */
  long long Dijkstra(const WGraph& G, int s, int g){
    int N=G.size();
    std::vector<bool> used(N, false);
    int used_count=0;
    std::vector<long long> dist(N, INF);
    dist[s]=0;
    std::priority_queue<std::pair<long long, int>,std::vector<std::pair<long long, int>>,std::greater<std::pair<long long, int>>> d;
    d.emplace(0, s);
    while(!d.empty()){
      int v; std::tie(std::ignore, v)=d.top(); d.pop();
      if(used[v])continue;
      used[v]=true; used_count++;
      if(used_count>=N)break;
      for(const auto& np:G[v]){
        if(dist[v]+np.second<dist[np.first]){
          dist[np.first]=dist[v]+np.second;
          d.emplace(dist[np.first], np.first);
        }
      }
    }
    return dist[g];
  }

  /**
  * 隣接行列表現された重み有り有効グラフの任意の頂点間の距離を求める.
  * 頂点数: N に対して O(N^3)
  * 隣接行列表現は a->b の辺が存在するときその重み, 存在しないとき, INF とする.
  * long long 型を用いていることに注意
  */
  MGraph Floyd_Warshall(MGraph G){
    int N=G.size();
    for(int k=0;k<N;k++)for(int i=0;i<N;i++)for(int j=0;j<N;j++){
      if(G[i][k]+G[k][j]<G[i][j])G[i][j]=G[i][k]+G[k][j];
    }
    return G;
  }
}
