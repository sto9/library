class SegmentTree
{
public:
  int N;
  vector<ll> dat;
  int unit = INF;

  void init(int n_ = 400010)
  {
    N = 1;
    while (N < n_)
      N *= 2;
    dat.assign(2 * N - 1, unit);
  }

  void update(int k, int a)
  {
    k += N - 1;
    dat[k] = a;
    while (k > 0)
    {
      k = (k - 1) / 2;
      //更新
      dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]); //
    }
  }

  int query(int a, int b, int k = 0, int l = 0, int r = -1)
  {
    if (r < 0)
      r = N;
    if (r <= a || b <= l)
      return unit;
    if (a <= l && r <= b)
      return dat[k];
    else
    {
      int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
      int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
      return min(vl, vr); //
    }
  }
};

template <typename T = string>
class SuffixArray
{
public:
  static const int MAX_N = 400010;
  int n, k;
  T S;
  int rank_sa[MAX_N + 1];
  int tmp[MAX_N + 1];
  int sa[MAX_N];

  SuffixArray(T S_) : S(S_)
  {
    construct_sa();
  }

  //文字列Sの接尾辞配列を構築

  void construct_sa()
  {
    n = distance(S.begin(), S.end());

    //最初は1文字，ランクは文字コードにすればよい
    for (int i = 0; i <= n; ++i)
    {
      sa[i] = i;
      rank_sa[i] = i < n ? S[i] : -1;
    }

    //(rank_sa[i],rank_sa[i+k])と(rank_sa[j],rank_sa[j+k])を比較
    auto comp = [&](int i, int j) {
      if (rank_sa[i] != rank_sa[j])
        return rank_sa[i] < rank_sa[j];
      else
      {
        int ri = i + k <= n ? rank_sa[i + k] : -1;
        int rj = j + k <= n ? rank_sa[j + k] : -1;
        return ri < rj;
      }
    };

    //k文字についてソートされているところから，2k文字でソートする
    for (k = 1; k <= n; k *= 2)
    {
      //compare_sa csa(n, k, rank_sa);
      sort(sa, sa + n + 1, comp);

      //いったんtmpに次のランクを計算し，それからrank_saに移す
      tmp[sa[0]] = 0;
      for (int i = 1; i <= n; ++i)
      {
        tmp[sa[i]] = tmp[sa[i - 1]] + (comp(sa[i - 1], sa[i]) ? 1 : 0);
      }
      for (int i = 0; i <= n; ++i)
        rank_sa[i] = tmp[i];
    }
  }

  void match(T t, vector<int> &res)
  {
    int l, r;

    int lo = -1, hi = n + 1;
    while (hi - lo > 1)
    {
      int mi = (lo + hi) / 2;
      T temp;
      for (int i = sa[mi]; i < min(sa[mi] + (int)distance(t.begin(), t.end()), n); i++)
        temp.push_back(S[i]);
      if (t <= temp)
        hi = mi;
      else
        lo = mi;
    }
    l = hi;

    lo = -1, hi = n + 1;
    while (hi - lo > 1)
    {
      int mi = (lo + hi) / 2;
      T temp;
      for (int i = sa[mi]; i < min(sa[mi] + (int)distance(t.begin(), t.end()), n); i++)
        temp.push_back(S[i]);
      if (t < temp)
        hi = mi;
      else
        lo = mi;
    }
    r = hi;
    for (int i = l; i < r; i++)
      res.push_back(sa[i]);
    sort(res.begin(), res.end());
  }

  //----------LCP----------

  int rank_lcp[MAX_N + 1];
  int lcp[MAX_N];
  //文字列Sとその接尾辞配列saを受け取り，高さ配列をlcpに計算

  void construct_lcp()
  {
    for (int i = 0; i <= n; ++i)
      rank_lcp[sa[i]] = i;

    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < n; ++i)
    {
      //文字列中での位置iの接尾辞と，接尾辞配列中でその1つ前の接尾辞のLCPを求める
      int j = sa[rank_lcp[i] - 1];

      //hを先頭の分1減らし，後ろが一致しているだけ増やす
      if (h > 0)
        h--;
      for (; j + h < n && i + h < n; ++h)
      {
        if (S[j + h] != S[i + h])
          break;
      }

      lcp[rank_lcp[i] - 1] = h;
    }
  }

  SegmentTree sg;

  void construct_LCP_RMQ()
  {
    sg.init(n);
    for (int i = 0; i < n; ++i)
    {
      sg.update(i, lcp[i]);
    }
  }

  void lcp_init()
  {
    construct_lcp();
    construct_LCP_RMQ();
  }

  //末尾からi,j文字の接尾辞の先頭何文字が一致しているか

  int suffix_match(int i, int j)
  {
    int l = min(rank_lcp[i], rank_lcp[j]), r = max(rank_lcp[i], rank_lcp[j]);
    return sg.query(l, r);
  }
};