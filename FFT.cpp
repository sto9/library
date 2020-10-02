template <typename U = ld>
struct FFT
{
  void DFT(vector<complex<U>>(&f), int inv)
  {
    int n = f.size();
    if (n == 1)
      return;
    vector<complex<U>> f_[2];
    rep(i, n) f_[i % 2].push_back(f[i]);
    DFT(f_[0], inv);
    DFT(f_[1], inv);
    complex<U> zeta_pow = 1.0, zeta = polar(U(1.0), inv * 2.0 * U(PI) / n);
    rep(i, n)
    {
      f[i] = f_[0][i % (n / 2)] + zeta_pow * f_[1][i % (n / 2)];
      zeta_pow *= zeta;
    }
  }
  template <typename T>
  vector<U> multiply(vector<T> f, vector<T> g)
  {
    int n = 1;
    while (n < f.size() + g.size())
      n *= 2;
    vector<complex<U>> ft(n), gt(n);
    rep(i, f.size()) ft[i] = f[i];
    rep(i, g.size()) gt[i] = g[i];
    DFT(ft, 1);
    DFT(gt, 1);
    rep(i, n) ft[i] *= gt[i];
    DFT(ft, -1);
    vector<U> res;
    rep(i, n) res.push_back(T(ft[i].real() / n));
    return res;
  }
};