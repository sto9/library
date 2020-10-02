template <typename T>
struct dijkstra
{
  int V;
  T INF_d;
  struct edge
  {
    int to;
    T cost;
  };
  vector<vector<edge>> E;
  vector<T> d;
  using pt = pair<T, int>;
  dijkstra(int V_) : V(V_)
  {
    E.resize(V);
    d.resize(V);
    if (is_same<int, T>::value)
      INF_d = 2e9;
    else
      INF_d = 8e18;
  }

  void add_E(int a, int b, T c = 1, bool directed = true)
  {
    E[a].emplace_back(edge{b, c});
    if (!directed)
      E[b].emplace_back(edge{a, c});
  }

  void calc(int s)
  {
    priority_queue<pt, vector<pt>, greater<pt>> que;
    fill(d.begin(), d.end(), INF_d);
    que.emplace(T(0), s);
    d[s] = 0;
    while (!que.empty())
    {
      pt p = que.top();
      que.pop();
      int v = p.second;
      if (d[v] < p.first)
        continue;
      for (auto &&e : E[v])
      {
        if (d[e.to] > d[v] + e.cost)
        {
          d[e.to] = d[v] + e.cost;
          que.emplace(d[e.to], e.to);
        }
      }
    }
  }
};