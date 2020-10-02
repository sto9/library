template <typename T>
struct BIT
{
  int n;
  vector<T> dat;

  BIT() {}
  BIT(int n_) : n(n_), dat(n_, 0) {}

  // 0-indexed
  void add(int i, T x)
  {
    i++;
    while (i <= n)
    {
      dat[i - 1] += x;
      i += i & -i;
    }
  }

  // [0, i)
  T sum(int i)
  {
    T res = 0;
    while (i > 0)
    {
      res += dat[i - 1];
      i -= i & -i;
    }
    return res;
  }

  // 0-indexed
  T get(int i) { return sum(i + 1) - sum(i); }

  // [l, r)
  T sum(int l, int r) { return sum(r) - sum(l); }

  void display()
  {
    for (int i = 0; i < n; i++)
      cerr << get(i) << " ";
    cerr << "\n";
  }
};