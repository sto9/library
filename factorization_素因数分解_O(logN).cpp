const int MAX_N = 2e7;
ll can_div[MAX_N] = {};

void init_prime()
{
  can_div[1] = -1;
  for (ll i = 2; i < MAX_N; i++)
  {
    if (can_div[i] != 0)
      continue;
    for (ll j = i + i; j < MAX_N; j += i)
      can_div[j] = i;
  }
}

inline bool is_prime(ll n)
{
  if (n <= 1)
    return false;
  return !can_div[n];
}

void factorization(int n, unordered_map<ll, int> &res)
{
  if (n <= 1)
    return;
  if (!can_div[n])
  {
    ++res[n];
    return;
  }
  ++res[can_div[n]];
  factorization(n / can_div[n], res);
}