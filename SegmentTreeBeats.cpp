class SegmentTreeBeats
{
  int N;
  vector<ll> max_v, smax_v, max_c, min_v, smin_v, min_c;
  vector<ll> sum, len, ladd, lval;

  void update_node_max(int k, ll x)
  {
    sum[k] += (x - max_v[k]) * max_c[k];

    if (max_v[k] == min_v[k])
      max_v[k] = min_v[k] = x;
    else if (max_v[k] == smin_v[k])
      max_v[k] = smin_v[k] = x;
    else
      max_v[k] = x;

    if (lval[k] != LINF && x < lval[k])
      lval[k] = x;
  }
  void update_node_min(int k, ll x)
  {
    sum[k] += (x - min_v[k]) * min_c[k];

    if (max_v[k] == min_v[k])
      max_v[k] = min_v[k] = x;
    else if (smax_v[k] == min_v[k])
      min_v[k] = smax_v[k] = x;
    else
      min_v[k] = x;

    if (lval[k] != LINF && lval[k] < x)
      lval[k] = x;
  }

  void push(int k)
  {

    if (N - 1 <= k)
      return;

    if (lval[k] != LINF)
    {
      updateall(2 * k + 1, lval[k]);
      updateall(2 * k + 2, lval[k]);
      lval[k] = LINF;
      return;
    }

    if (ladd[k] != 0)
    {
      addall(2 * k + 1, ladd[k]);
      addall(2 * k + 2, ladd[k]);
      ladd[k] = 0;
    }

    if (max_v[k] < max_v[2 * k + 1])
      update_node_max(2 * k + 1, max_v[k]);
    if (min_v[2 * k + 1] < min_v[k])
      update_node_min(2 * k + 1, min_v[k]);

    if (max_v[k] < max_v[2 * k + 2])
      update_node_max(2 * k + 2, max_v[k]);
    if (min_v[2 * k + 2] < min_v[k])
      update_node_min(2 * k + 2, min_v[k]);
  }

  void update(int k)
  {
    sum[k] = sum[2 * k + 1] + sum[2 * k + 2];

    if (max_v[2 * k + 1] < max_v[2 * k + 2])
    {
      max_v[k] = max_v[2 * k + 2];
      max_c[k] = max_c[2 * k + 2];
      smax_v[k] = max(max_v[2 * k + 1], smax_v[2 * k + 2]);
    }
    else if (max_v[2 * k + 1] > max_v[2 * k + 2])
    {
      max_v[k] = max_v[2 * k + 1];
      max_c[k] = max_c[2 * k + 1];
      smax_v[k] = max(smax_v[2 * k + 1], max_v[2 * k + 2]);
    }
    else
    {
      max_v[k] = max_v[2 * k + 1];
      max_c[k] = max_c[2 * k + 1] + max_c[2 * k + 2];
      smax_v[k] = max(smax_v[2 * k + 1], smax_v[2 * k + 2]);
    }

    if (min_v[2 * k + 1] < min_v[2 * k + 2])
    {
      min_v[k] = min_v[2 * k + 1];
      min_c[k] = min_c[2 * k + 1];
      smin_v[k] = min(smin_v[2 * k + 1], min_v[2 * k + 2]);
    }
    else if (min_v[2 * k + 1] > min_v[2 * k + 2])
    {
      min_v[k] = min_v[2 * k + 2];
      min_c[k] = min_c[2 * k + 2];
      smin_v[k] = min(min_v[2 * k + 1], smin_v[2 * k + 2]);
    }
    else
    {
      min_v[k] = min_v[2 * k + 1];
      min_c[k] = min_c[2 * k + 1] + min_c[2 * k + 2];
      smin_v[k] = min(smin_v[2 * k + 1], smin_v[2 * k + 2]);
    }
  }

  void update_min(ll x, int a, int b, int k, int l, int r)
  {
    if (b <= l || r <= a || max_v[k] <= x)
      return;
    if (a <= l && r <= b && smax_v[k] < x)
    {
      update_node_max(k, x);
      return;
    }

    push(k);
    update_min(x, a, b, 2 * k + 1, l, (l + r) / 2);
    update_min(x, a, b, 2 * k + 2, (l + r) / 2, r);
    update(k);
  }

  void update_max(ll x, int a, int b, int k, int l, int r)
  {
    if (b <= l || r <= a || x <= min_v[k])
      return;
    if (a <= l && r <= b && x < smin_v[k])
    {
      update_node_min(k, x);
      return;
    }

    push(k);
    update_max(x, a, b, 2 * k + 1, l, (l + r) / 2);
    update_max(x, a, b, 2 * k + 2, (l + r) / 2, r);
    update(k);
  }

  void addall(int k, ll x)
  {
    max_v[k] += x;
    if (smax_v[k] != -LINF)
      smax_v[k] += x;
    min_v[k] += x;
    if (smin_v[k] != LINF)
      smin_v[k] += x;

    sum[k] += len[k] * x;
    if (lval[k] != LINF)
      lval[k] += x;
    else
      ladd[k] += x;
  }

  void updateall(int k, ll x)
  {
    max_v[k] = x;
    smax_v[k] = -LINF;
    min_v[k] = x;
    smin_v[k] = LINF;
    max_c[k] = min_c[k] = len[k];

    sum[k] = x * len[k];
    lval[k] = x;
    ladd[k] = 0;
  }

  void update_add(ll x, int a, int b, int k, int l, int r)
  {
    if (b <= l || r <= a)
      return;
    if (a <= l && r <= b)
    {
      addall(k, x);
      return;
    }

    push(k);
    update_add(x, a, b, 2 * k + 1, l, (l + r) / 2);
    update_add(x, a, b, 2 * k + 2, (l + r) / 2, r);
    update(k);
  }

  void update_val(ll x, int a, int b, int k, int l, int r)
  {
    if (b <= l || r <= a)
      return;
    if (a <= l && r <= b)
      updateall(k, x);
    return;

    push(k);
    update_val(x, a, b, 2 * k + 1, l, (l + r) / 2);
    update_val(x, a, b, 2 * k + 2, (l + r) / 2, r);
    update(k);
  }

  ll query_max(int a, int b, int k, int l, int r)
  {
    if (b <= l || r <= a)
      return -LINF;
    if (a <= l && r <= b)
      return max_v[k];
    push(k);
    ll lv = query_max(a, b, 2 * k + 1, l, (l + r) / 2);
    ll rv = query_max(a, b, 2 * k + 2, (l + r) / 2, r);
    return max(lv, rv);
  }

  ll query_min(int a, int b, int k, int l, int r)
  {
    if (b <= l || r <= a)
      return LINF;
    if (a <= l && r <= b)
      return min_v[k];
    push(k);
    ll lv = query_min(a, b, 2 * k + 1, l, (l + r) / 2);
    ll rv = query_min(a, b, 2 * k + 2, (l + r) / 2, r);
    return min(lv, rv);
  }

  ll query_sum(int a, int b, int k, int l, int r)
  {
    if (b <= l || r <= a)
      return 0;
    if (a <= l && r <= b)
      return sum[k];
    push(k);
    ll lv = query_sum(a, b, 2 * k + 1, l, (l + r) / 2);
    ll rv = query_sum(a, b, 2 * k + 2, (l + r) / 2, r);
    return lv + rv;
  }

public:
  SegmentTreeBeats(int n)
  {
    SegmentTreeBeats(vector<ll>(n, 0));
  }

  SegmentTreeBeats(const vector<ll> &a)
  {
    int sz = a.size();
    N = 1;
    while (N < sz)
      N <<= 1;
    max_v.resize(2 * N);
    smax_v.resize(2 * N);
    max_c.resize(2 * N);
    min_v.resize(2 * N);
    smin_v.resize(2 * N);
    min_c.resize(2 * N);
    sum.resize(2 * N);
    len.resize(2 * N);
    ladd.assign(2 * N, 0);
    lval.assign(2 * N, LINF);

    len[0] = N;
    for (int i = 0; i < N - 1; ++i)
      len[2 * i + 1] = len[2 * i + 2] = (len[i] >> 1);

    for (int i = 0; i < sz; ++i)
    {
      max_v[N - 1 + i] = min_v[N - 1 + i] = sum[N - 1 + i] = a[i];
      smax_v[N - 1 + i] = -LINF;
      smin_v[N - 1 + i] = LINF;
      max_c[N - 1 + i] = min_c[N - 1 + i] = 1;
    }

    for (int i = sz; i < N; ++i)
    {
      max_v[N - 1 + i] = smax_v[N - 1 + i] = -LINF;
      min_v[N - 1 + i] = smin_v[N - 1 + i] = LINF;
      max_c[N - 1 + i] = min_c[N - 1 + i] = 0;
    }
    for (int i = N - 2; i >= 0; --i)
      update(i);
  }

  // range minimize query
  void update_min(int a, int b, ll x) { update_min(x, a, b, 0, 0, N); }

  // range maximize query
  void update_max(int a, int b, ll x) { update_max(x, a, b, 0, 0, N); }

  // range add query
  void update_add(int a, int b, ll x) { update_add(x, a, b, 0, 0, N); }

  // range update query
  void update_val(int a, int b, ll x) { update_val(x, a, b, 0, 0, N); }

  // range minimum query
  ll query_max(int a, int b) { return query_max(a, b, 0, 0, N); }

  // range maximum query
  ll query_min(int a, int b) { return query_min(a, b, 0, 0, N); }

  // range sum query
  ll query_sum(int a, int b) { return query_sum(a, b, 0, 0, N); }
};