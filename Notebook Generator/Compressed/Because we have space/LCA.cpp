const int N = 3e5+7, K = 20; vector<int> adj[N];
int anc[N][K]; int level[N];
void setup(int u, int par) {
  level[u] = level[par]+1;
  anc[u][0] = par;
  for (int k=1; k<K; k++)   anc[u][k] = anc[anc[u][k-1]][k-1];
  for (int v: adj[u]) {
    if (v == par)   continue;
    setup(v, u);
  }
}
int lca(int u, int v) {
  if (level[u] > level[v])  swap(u, v);
  for (int k=K-1; k>=0; k--)
    if (level[u] + (1<<k) <= level[v])  v = anc[v][k];
  if (u == v) return u;
  for (int k=K-1; k>=0; k--)
    if (anc[u][k] != anc[v][k])
      u = anc[u][k], v = anc[v][k];
  return anc[u][0];
}
int getanc(int u, int d) {
  for (int k=0; k<K; k++)
    if (d & (1<<k))
      u = anc[u][k];
  return u;
}
int dist(int u, int v) {
  int g = lca(u, v);
  return level[u] + level[v] - 2*level[g];
}
