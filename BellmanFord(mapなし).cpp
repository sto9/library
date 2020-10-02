struct BellmanFord
{
  static const ll MAX_V = 1010 * 1010;
  struct edge
  {
    ll from, to;
    ll cost;
  };

  ll V;
  vector<edge> E;
  ll d[MAX_V];

  BellmanFord(ll V_) : V(V_) {}

  void calc(ll s)
  {
    fill(d, d + V + 1, LINF);
    d[s] = 0;
    bool update;
    while (1)
    {
      update = false;
      for (auto e : E)
      {
        if (d[e.from] != LINF && d[e.to] > d[e.from] + e.cost)
        {
          d[e.to] = d[e.from] + e.cost;
          update = true;
        }
      }
      if (!update)
        return;
    }
  }

  bool negative[MAX_V];

  bool calc_and_find_negative_loop(ll s, ll g = -1)
  {
    fill(d, d + V + 1, LINF);
    fill(negative, negative + V + 1, false);
    d[s] = 0;

    rep(i, V)
    {
      bool update = false;
      for (auto e : E)
      {
        if (d[e.from] != LINF && d[e.to] > d[e.from] + e.cost)
        {
          d[e.to] = d[e.from] + e.cost;
          update = true;
          if (i == V - 1)
            negative[e.from] = negative[e.to] = true;
        }
      }
      if (!update)
        return false;
    }
    if (g == -1)
    {
      rep(i, V + 1)
      {
        if (negative[i])
          return true;
      }
      return false;
    }
    else
    {
      return negative[g];
    }
  }

  bool find_any_negative_loop()
  {
    ll d_[MAX_V];
    rep(i, V) for (auto e : E)
    {
      if (d_[e.to] > d_[e.from] + e.cost)
      {
        d_[e.to] = d_[e.from] + e.cost;
        if (i == V - 1)
          return true;
      }
    }
    return false;
  }
};