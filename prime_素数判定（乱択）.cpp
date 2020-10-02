using Int = __int128;

Int modpow(Int a, Int n, Int m)
{
  Int res = 1;
  while (n > 0)
  {
    if (n & 1)
      res = res * a % m;
    n >>= 1;
    a = a * a % m;
  }
  return res;
}

// Miller–Rabin
bool is_prime(Int n)
{
  if (n == 2)
    return true;
  if (n <= 1 or (n & 1) == 0)
    return false;

  Int d = n - 1;
  while ((d & 1) == 0)
    d >>= 1;

  vector<Int> v;

  if (n < 4'759'123'141)
  {
    v = {2, 7, 61};
  }
  else if (n < 341'550'071'728'321)
  {
    v = {2, 3, 5, 7, 11, 13, 17};
  }
  else
  {
    static random_device seed_gen;
    static mt19937_64 engine(seed_gen());
    static const int sim_times = 100;
    for (int i = 0; i < sim_times; ++i)
      v.emplace_back(engine() % (n - 1) + 1);
  }
  for (Int a : v)
  {
    if (a >= n)
      continue;
    Int t = d;
    Int y = modpow(a, t, n);
    while (t != n - 1 and y != 1 and y != n - 1)
    {
      y = y * y % n;
      t <<= 1;
    }
    if (y != n - 1 and (t & 1) == 0)
      return false;
  }
  return true;
}