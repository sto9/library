template <typename T, typename U>
struct dijkstra
{
  U INF_d;
  dijkstra()
  {
    if (is_same<U, int>::value)
      INF_d = 2e9;
    else
      INF_d = 8e18;
  }
  struct edge
  {
    T to;
    U cost;
  };

  using P = pair<U, T>;
  map<T, vector<edge>> E;
  map<T, U> d;

  void add_E(T a, T b, U c = 1, bool directed = true)
  {
    E[a].emplace_back(edge{b, c});
    if (!directed)
      E[b].emplace_back(edge{a, c});
  }

  void calc(T s)
  {
    priority_queue<P, vector<P>, greater<P>> que;
    que.emplace(U(0), s);
    d[s] = U(0);
    while (!que.empty())
    {
      P p = que.top();
      que.pop();
      T v = p.second;
      if (d[v] < p.first)
        continue;
      for (auto e : E[v])
      {
        if (!d.count(e.to))
          d[e.to] = INF_d;
        if (d[e.to] > d[v] + e.cost)
        {
          d[e.to] = d[v] + e.cost;
          que.emplace(d[e.to], e.to);
        }
      }
    }
  }

  U dist(T v) { return d.count(v) ? d[v] : INF_d; }
};