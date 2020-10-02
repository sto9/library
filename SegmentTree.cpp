template <typename T>
class SegmentTree
{
private:
  using Fn = function<T(T, T)>;
  int N;
  vector<T> dat;
  T unit;
  Fn func;

public:
  SegmentTree() {}
  SegmentTree(int n_, Fn func_, T unit_) : func(func_), unit(unit_)
  {
    N = 1;
    while (N < n_)
      N *= 2;
    dat.assign(2 * N - 1, unit);
  }
  SegmentTree(const vector<T> &v, Fn func_, T unit_) : func(func_), unit(unit_)
  {
    N = 1;
    int sz = v.size();
    while (N < sz)
      N *= 2;
    dat.resize(2 * N - 1);
    for (int i = 0; i < N; ++i)
      dat[i + N - 1] = (i < sz ? v[i] : unit);
    for (int i = N - 2; i >= 0; --i)
      dat[i] = func(dat[i * 2 + 1], dat[i * 2 + 2]);
  }

  void update(int k, T a)
  {
    k += N - 1;
    dat[k] = a;
    while (k > 0)
    {
      k = (k - 1) / 2;
      dat[k] = func(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  T get(int k) { return dat[k + N - 1]; }

  T query(int l, int r)
  {
    T vl = unit, vr = unit;
    for (l += (N - 1), r += (N - 1); l < r; l >>= 1, r >>= 1)
    {
      if ((l & 1) == 0)
        vl = func(vl, dat[l]);
      if ((r & 1) == 0)
        vr = func(vr, dat[--r]);
    }
    return func(vl, vr);
  }
};