/*
#include<bits/stdc++.h>
using namespace std;
が先頭に必要
*/
struct Dijkstra
{
  using ll=long long;
  using pli=pair<ll, int>;
  int N; ll inf;
  vector<vector<pair<int,ll>>> edge;
  Dijkstra(int vertex_number, ll inf_value=(ll)1e18)
  {
    N=vertex_number;
    edge.resize(N);
    inf = inf_value;
  }
  void add_edge(int from, int to, ll cost)
  {
    edge[from].push_back(make_pair(to, cost));
  }
  vector<ll> make(int start_vertex = 0, ll start_dist = 0){
    vector<ll> dist(N, inf);
    dist[start_vertex] = start_dist;
    vector<bool> used(N, false);
    priority_queue<pli, vector<pli>, greater<pli>> queue;
    queue.push(pli(start_dist, start_vertex));
    while(queue.size())
    {
      ll vdist; int v;
      tie(vdist, v) = queue.top(); queue.pop();
      if(used[v])continue;
      used[v] = true;
      for(auto& elm:edge[v])
      {
        if(dist[elm.first] <= dist[v] + elm.second)continue;
        dist[elm.first] = dist[v] + elm.second;
        queue.push(pli(dist[elm.first], elm.first));
      }
    }
    return dist;
  }
};
