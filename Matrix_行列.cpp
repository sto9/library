template <typename T>
class Matrix
{
public:
  size_t N, M;
  vector<vector<T>> data;

  Matrix(size_t N_, size_t M_) : N(N_), M(M_)
  {
    data.resize(N, vector<T>(M));
  }

  Matrix operator+(const Matrix &A)
  {
    assert(A.N == N && A.M == M);
    Matrix res(N, M);
    rep(i, N) rep(j, M) res[i][j] = data[i][j] + A[i][j];
    return res;
  }

  Matrix &operator+=(const Matrix &A)
  {
    assert(A.N == N && A.M == M);
    rep(i, N) rep(j, M) data[i][j] += A[i][j];
    return *this;
  }

  Matrix operator-(const Matrix &A)
  {
    assert(A.N == N && A.M == M);
    Matrix<T> res(N, M);
    rep(i, N) rep(j, M) res.data[i][j] = data[i][j] - A[i][j];
    return res;
  }

  Matrix &operator-=(const Matrix &A)
  {
    assert(A.N == N && A.M == M);
    rep(i, N) rep(j, M) data[i][j] -= A[i][j];
    return *this;
  }

  Matrix operator*(const Matrix &A)
  {
    assert(M == A.N);
    Matrix res(N, A.M);

    rep(i, N) rep(j, A.M)
    {
      rep(k, M) res[i][j] += data[i][k] * A[k][j];
    }
    return res;
  }

  Matrix &operator*=(const Matrix<T> &A)
  {
    return *this = *this * A;
  }

  Matrix operator*(T a)
  {
    Matrix res(N, M);
    rep(i, N) rep(j, M) res[i][j] = data[i][j] * a;
    return res;
  }

  Matrix &operator*=(ll a)
  {
    rep(i, N) rep(j, M) data[i][j] *= a;
    return *this;
  }

  inline const vector<T> &operator[](int index) const
  {
    return (data.at(index));
  }

  inline vector<T> &operator[](int index)
  {
    return (data.at(index));
  }

  bool operator==(Matrix &A)
  {
    if (N != A.N || M != A.M)
      return false;

    rep(i, N) rep(j, M)
    {
      if (data[i][j] != A[i][j])
        return false;
    }
    return true;
  }

  bool operator!=(Matrix &A)
  {
    return !(*this == A);
  }

  Matrix transpose()
  {
    Matrix res(M, N);
    rep(i, N) rep(j, M) res[j][i] = data[i][j];
    return res;
  }

  T trace()
  {
    assert(N == M);
    T res = 0;
    rep(i, N) res += data[i][i];
    return res;
  }

  void display()
  {
    rep(i, N)
    {
      rep(j, M) cerr << data[i][j] << " ";
      cerr << "\n";
    }
  }

  Matrix E(const int n)
  {
    Matrix res(n, n);
    rep(i, n) rep(j, n) res[i][j] = (i == j);
    return res;
  }

  Matrix pow(ll n)
  {
    assert(N == M);
    Matrix P = *this, res = E(N);
    while (n > 0)
    {
      if (n & 1)
        res *= P;
      P *= P;
      n >>= 1;
    }
    return res;
  }
};

template <typename T>
Matrix<T> operator*(ll a, Matrix<T> &A)
{
  Matrix<T> res(A.N, A.M);
  rep(i, A.N) rep(j, A.M) res[i][j] = A[i][j] * a;
  return res;
}