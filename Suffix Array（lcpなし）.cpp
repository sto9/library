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
};