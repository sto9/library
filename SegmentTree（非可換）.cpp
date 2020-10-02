template <typename T>
class SegmentTree
{
private:
  using F = function<T(T, T)>;
  int N;
  vector<T> dat;
  T ti;
  F f;

public:
  SegmentTree() {}
  SegmentTree(int n, F f, T ti) : f(f), ti(ti)
  {
    N = 1;
    while (N < n)
      N *= 2;
    dat.assign(2 * N - 1, ti);
  }
  SegmentTree(const vector<T> &v, F f, T ti) : f(f), ti(ti)
  {
    N = 1;
    int sz = v.size();
    while (N < sz)
      N *= 2;
    dat.resize(2 * N - 1);
    for (int i = 0; i < N; ++i)
      dat[i + N - 1] = (i < sz ? v[i] : ti);
    for (int i = N - 2; i >= 0; --i)
      dat[i] = f(dat[i * 2 + 1], dat[i * 2 + 2]);
  }

  void update(int k, T a)
  {
    k += N - 1;
    dat[k] = a;
    while (k > 0)
    {
      k = (k - 1) / 2;
      dat[k] = f(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  T get(int k) { return dat[k + N - 1]; }

  T query(int a, int b, int k, int l, int r)
  {
    if (r <= a or b <= l)
      return ti;
    if (a <= l and r <= b)
      return dat[k];
    T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
    T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
    return f(vl, vr);
  }
  T query(int a, int b) { return query(a, b, 0, 0, N); }
  T query_all() { return dat[0]; }
};