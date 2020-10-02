ll modpow(ll a, ll n, ll mod)
{
  ll res = 1;
  while (n > 0)
  {
    if (n & 1)
      res = res * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return res;
}

// gcd(a, mod) = 1
ll modinv(ll a, ll mod)
{
  ll b = mod, u = 1, v = 0;
  while (b)
  {
    ll t = a / b;
    a -= t * b;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  u %= mod;
  if (u < 0)
    u += mod;
  return u;
}

// a^x ≡ b
ll modlog(ll a, ll b, ll mod, bool include0 = false)
{
  a %= mod, b %= mod;
  constexpr ll sqrtM = 10000;

  // {a^0, a^1, ..., a^sqrt{M-1}}
  unordered_map<ll, ll> mp;
  ll p = 1;
  for (ll r = 0; r < sqrtM; ++r)
  {
    if (p == b)
    {
      if (r > 0 || include0)
        return r;
    }
    if (!mp.count(p))
      mp[p] = r;
    p = p * a % mod;
  }

  ll A = modpow(modinv(a, mod), sqrtM, mod);
  p = b;
  for (ll q = 1; q <= CEIL(mod, sqrtM); ++q)
  {
    p = p * A % mod;
    if (mp.count(p))
      return q * sqrtM + mp[p];
  }

  return -1;
}