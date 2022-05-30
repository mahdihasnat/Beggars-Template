struct DSU {
  vector< int >bap, sz; vector< PII >stk;
  DSU(int n) : bap(n, 0), sz(n, 1) {
    for (int i = 0; i < n; i++) bap[i] = i;
  }
  int parent(int u) {
    while (u != bap[u]) u = bap[u]; return u;
  }
  bool addEdge(int u, int v) {
    u = parent(u); v = parent(v);
    if (u == v) return false;
    if (sz[u] < sz[v]) swap(u, v);
    bap[v] = u; sz[u] += sz[v];
    stk.emplace_back(u, v); return true;
  }
  void rollBack(int lastSize) {
    while (stk.size() > lastSize) {
      int u = stk.back().first;
      int v = stk.back().second;
      stk.pop_back(); bap[v] = v; sz[u] -= sz[v];
    }
  }
};
