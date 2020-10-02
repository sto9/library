map<ll, int> factrization(ll n)
{
  map<ll, int> res;
  for (ll i = 2; i * i <= n; ++i)
  {
    while (n % i == 0)
    {
      n /= i;
      res[i]++;
    }
  }
  if (n > 1)
    res[n]++;
  return res;
}