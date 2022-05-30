vector<int>edg[MAXN]; int done[MAXN];
/// START of auxi functions that use Centroid Deco
void solveForCentroid(int centroid) {
  cout << "centroid " << centroid << endl;
}
/// END of auxi functions that use Centroid Deco
int sbtr[MAXN];
int subtreeSize(int u, int p) {
  sbtr[u] = 1;
  for (int v : edg[u]) {
    if (v==p || done[v]) continue;
    sbtr[u] += subtreeSize(v, u);
  }
  return sbtr[u];
}
int nextCentroid(int n, int u, int p) {
  for (int v : edg[u]) {
    if (v==p||done[v]) continue;
    if (sbtr[v]+sbtr[v]>n)
      return nextCentroid(n,v,u);
  }
  return u;
}
void decompose(int u, int pcent) {
  int n = subtreeSize(u, pcent);
  int centroid = nextCentroid(n, u, pcent);
  solveForCentroid(centroid); done[centroid] = 1;
  for (int v : edg[centroid]) {
    if (done[v]) continue; decompose(v, centroid);
  }
}
void start(int n) {
  for (int i = 1; i <= n; i++) done[i] = 0;
  decompose(1, 0);
}
