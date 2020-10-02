template <typename T, typename E>
struct SegmentTree
{
  using F = function<T(T, T)>;
  using G = function<T(T, E)>;
  using H = function<E(E, E)>;
  using P = function<E(E, int)>;
  int n;
  F f;
  G g;
  H h;
  P p;
  T ti;
  E ei;
  vector<T> dat;
  vector<E> laz;
  SegmentTree() {}
  SegmentTree(int n_, F f, G g, H h, T ti, E ei, P p = [](E a, int b) { return a; })
      : f(f), g(g), h(h), ti(ti), ei(ei), p(p)
  {
    init(n_);
  }
  SegmentTree(vector<T> &v, F f, G g, H h, T ti, E ei, P p = [](E a, int b) { return a; })
      : f(f), g(g), h(h), ti(ti), ei(ei), p(p)
  {
    init(v.size());
    build(v);
  }
  void init(int n_)
  {
    n = 1;
    while (n < n_)
      n *= 2;
    dat.clear();
    dat.resize(2 * n - 1, ti);
    laz.clear();
    laz.resize(2 * n - 1, ei);
  }
  void build(const vector<T> v)
  {
    for (int i = 0; i < v.size(); i++)
      dat[i + n - 1] = v[i];
    for (int i = n - 2; i >= 0; i--)
      dat[i] = f(dat[i * 2 + 1], dat[i * 2 + 2]);
  }
  void eval(int len, int k)
  {
    if (laz[k] == ei)
      return;
    if (k * 2 + 1 < n * 2 - 1)
    {
      laz[k * 2 + 1] = h(laz[k * 2 + 1], laz[k]);
      laz[k * 2 + 2] = h(laz[k * 2 + 2], laz[k]);
    }
    dat[k] = g(dat[k], p(laz[k], len));
    laz[k] = ei;
  }
  T update(int a, int b, E x, int k, int l, int r)
  {
    eval(r - l, k);
    if (r <= a || b <= l)
      return dat[k];
    if (a <= l && r <= b)
    {
      laz[k] = h(laz[k], x);
      return g(dat[k], p(laz[k], r - l));
    }
    return dat[k] = f(update(a, b, x, k * 2 + 1, l, (l + r) / 2),
                      update(a, b, x, k * 2 + 2, (l + r) / 2, r));
  }
  T update(int a, int b, E x) { return update(a, b, x, 0, 0, n); }
  T query(int a, int b, int k, int l, int r)
  {
    eval(r - l, k);
    if (r <= a || b <= l)
      return ti;
    if (a <= l && r <= b)
      return dat[k];
    T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
    T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
    return f(vl, vr);
  }
  T query(int a, int b) { return query(a, b, 0, 0, n); }
};