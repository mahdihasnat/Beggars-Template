const int M = 1e9+7;
typedef vector<int>row; typedef vector<row>matrix;
matrix operator*(const matrix&a, const matrix &b) {
  int n = a.size(), p = b.size(), m = b[0].size();
  matrix ans(n, row(m));
  for (int i=0; i<n; i++)
    for (int j=0; j<m; j++)
      for (int k=0; k<p; k++)
       ans[i][j]=(ans[i][j]+1LL*a[i][k]*b[k][j])%M;
  return ans;
}
matrix unit(int n) {
  matrix ans(n, row(n));
  for (int i=0; i<n; i++)   ans[i][i] = 1;
  return ans;
}
matrix power(const matrix &a, long long p) {
  if (p == 0)   return unit(a.size());
  matrix ans = power(a, p/2); ans = ans * ans;
  if (p%2)    ans = ans*a;
  return ans;
}
