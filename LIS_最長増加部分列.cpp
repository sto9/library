//最長部分増加列の長さ
int LIS(vector<ll> &v, bool strict)
{
  vector<ll> lis;
  for (auto p : v)
  {
    vector<ll>::iterator itr;
    if (strict)
      itr = lower_bound(lis.begin(), lis.end(), p);
    else
      itr = upper_bound(lis.begin(), lis.end(), p);
    if (itr == lis.end())
      lis.push_back(p);
    else
      *itr = p;
  }
  return lis.size();
}