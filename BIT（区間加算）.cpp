// 0-indexed
template <typename T>
struct BIT
{
  int n;
  vector<T> bit[2];
  BIT(int n) : n(n)
  {
    for (int p = 0; p < 2; p++)
      bit[p].assign(n, 0);
  }

  void add_sub(int p, int i, T x)
  {
    for (int idx = i; idx < n + 1; idx += (idx & -idx))
      bit[p][idx - 1] += x;
  }
  // [l,r) に加算
  void add(int l, int r, T x)
  {
    ++l, ++r;
    add_sub(0, l, -x * (l - 1));
    add_sub(0, r, x * (r - 1));
    add_sub(1, l, x);
    add_sub(1, r, -x);
  }
  T sum_sub(int p, int i)
  {
    T s(0);
    for (int idx = i; idx > 0; idx -= (idx & -idx))
      s += bit[p][idx - 1];
    return s;
  }
  T sum(int i)
  {
    ++i;
    return sum_sub(0, i) + sum_sub(1, i) * i;
  }
  // [l,r)
  T query(int l, int r) { return sum(r - 1) - sum(l - 1); }
  T get(int i) { return sum(i) - sum(i - 1); }
  void display()
  {
    rep(i, n) cerr << get(i) << " ";
    cerr << "\n";
  }
};
