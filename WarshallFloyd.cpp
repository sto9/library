class WarshallFloyd
{
  static const ll MAX_V = 210;
  ll V;
  ll d[MAX_V][MAX_V];

public:
  WarshallFloyd(ll V_) : V(V_)
  {
    rep(i, V) rep(j, V)
    {
      d[i][j] = (i == j ? 0 : LINF);
    }
  }

  inline void add_E(int s, int t, ll d_)
  {
    d[s][t] = d_;
  }

  inline void calc()
  {
    rep(k, V) rep(i, V) rep(j, V)
    {
      d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }
  }

  inline ll dist(int s, int t)
  {
    return (d[s][t] >= LINF / 2 ? LINF : d[s][t]);
  }
};