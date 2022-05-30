///Z[i] = LCP(s, s[i....])
vector<int> z_function(string s) {
  int n = s.size(), l=0, r=0; vector<int> z(n);
  for (int i=1; i<n; i++) {
    if (i<=r)   z[i] = min(r-i+1, z[i-l]);
    while (i+z[i]<n && s[i+z[i]]==s[z[i]]) z[i]++;
    if (i+z[i]-1>r)   l = i, r = i+z[i]-1;
  } z[0] = s.size(); return z;
}
