//ランレングス圧縮
template <typename T>
vector<pair<T, ll>> RLE(const vector<T> &v)
{
  vector<pair<T, ll>> res;
  T before;
  rep(i, v.size())
  {
    if (i == 0 || v[i] != before)
    {
      before = v[i];
      res.push_back(MP(v[i], 0LL));
    }
    res.rbegin()->second++;
  }
  return res;
}

template <typename T>
vector<ll> RLE_simple(const vector<T> &v)
{
  vector<ll> res;
  T before;
  rep(i, v.size())
  {
    if (i == 0 || v[i] != before)
    {
      before = v[i];
      res.push_back(0);
    }
    (*res.rbegin())++;
  }
  return res;
}