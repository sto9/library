template <typename T>
class HLD
{
public:
  vector<vector<int>> g;
  int n, root;
  vector<int> sz, par, in, out, head;
  bool calculated = false;
  void dfs_sz(int v, int p)
  { //最大サイズの部分木を最も左に配置　これによりオイラーツアーで訪れた順に番号を振るだけでよくなる　さらに部分木クエリにも対応できる
    sz[v] = 1, par[v] = p;
    for (auto &e : g[v])
    {
      if (e == p)
        swap(e, g[v].back());
      if (e == p)
        continue;
      dfs_sz(e, v);
      sz[v] += sz[e];
      if (sz[e] > sz[g[v][0]])
        swap(e, g[v][0]);
    }
  }
  void dfs_hld(int v, int p, int &t)
  { //inはオイラーツアーで訪れた順番　outはオイラーツアーで帰ってきた時の番号
    in[v] = t++;
    for (auto e : g[v])
    {
      if (e == p)
        continue;
      head[e] = (e == g[v][0] ? head[v] : e);
      dfs_hld(e, v, t);
    }
    out[v] = t;
  }

  void init()
  {
    dfs_sz(root, -1);
    int t = 0;
    head[root] = root;
    dfs_hld(root, -1, t);
  }

public:
  HLD(int _n, int _root = 0)
      : n(_n), g(_n), root(_root), sz(_n), par(_n, -1), head(_n, -1), in(_n), out(_n) {}
  void add_E(int a, int b)
  {
    g[a].emplace_back(b);
    g[b].emplace_back(a);
  }

  int get(int a) { return in[a]; } // オイラーツアーで振りなおした番号に変換
  int subtree_size(int a) { return sz[a]; }
  int get_ch(int a, int b) { return a == par[b] ? in[b] : in[a]; } // 辺の端点のうち下にある方をget

  int lca(int a, int b)
  {
    for (;; b = par[head[b]])
    {
      if (in[a] > in[b])
        swap(a, b);
      if (head[a] == head[b])
        return a;
    }
  }
  pii subtree_query(int a)
  {
    if (!calculated)
    {
      init();
      calculated = true;
    }
    return make_pair(in[a], out[a]);
  } // aを根とする部分木は[in[a],out[a])で表せる　よってセグ木などを利用可能
  vector<pii> path_query(int a, int b, bool isedge = false)
  { // aとbのパスを最大log(n)個の区間で表す　辺属性クエリの場合isedgeをtrueにする
    // for(auto [l,r]:path_query(a,b))seg.update(l,r,hoge);　みたいに使う
    if (!calculated)
    {
      init();
      calculated = true;
    }
    vector<pii> ret;
    for (;; b = par[head[b]])
    {
      if (in[a] > in[b])
        swap(a, b);
      if (head[a] == head[b])
        break;
      ret.push_back({in[head[b]], in[b] + 1});
    }
    ret.push_back({in[a] + isedge, in[b] + 1});
    return ret;
  }
};