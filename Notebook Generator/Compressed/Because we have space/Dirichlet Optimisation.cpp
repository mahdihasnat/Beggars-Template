//Let h = f*g and sf, sg and sh be sums of f, g, h.
//If we can calculate values of sg and sh quickly,
//we can then calculate sf(n) quickly using the
// following formula and the harmonic lemma.
//sf(n) = (sh(n) - sum{2...n} sf(n/d) g(d)) / g(1).
// Only values of the form n/k are needed.
// these value should be memoized. This has
// complexity O(n^(3/4)). If you precalc values
// upto n^(2/3), complexity becomes O(n^(2/3)).

const long long N=1e9, RT=2e6, K=N/RT+100, M=1e9+7;
long long pre[RT];
void precal() { ///calc pre[i] = sf(i) for i<RT
  for (int i=1; i<RT; i++) pre[i] = (i-1LL)*(i-2LL)%M;
  for (int i=1; i<RT; i++) {
    for (int j=2*i; j<RT; j+=i)   {
      pre[j] -= pre[i];
      if (pre[j] < 0) pre[j] += M;
    }
  }
  for (int i=1; i<RT; i++) {
    pre[i] += pre[i-1];
    if (pre[i] >= M)  pre[i] -= M;
  }
}

// all values are needed are of the form N/x, so we
// use mem[x] = sf(N/x), use a hashmap otherwise
long long mem[K]; bool vis[K];
long long sh(long long n) {     ///Define sh
  long long ans = (n*(n+1))%M;
  ans = (ans * (n+n+1))%M;
  while (ans%6)   ans += M;
  ans/=6; ans += -3*n*(n+1)/2 + 2*n;
  return (ans%M+M)%M;
}
long long sg(long long n) {return n;} ///Define sg
long long solve(long long x) {///Calc and mem sh(n)
  if (x < RT)   return pre[x];
  if (vis[N/x])   return mem[N/x];
  vis[N/x] = 1;
  long long ans = sh(x);
  for (long long i=1, last=x; i*i<=x; i++) {
    long long l=i, r=i, inv=last;
    if (i>1)ans=(ans-(sg(r)-sg(l-1))*solve(inv))%M;
    l=x/(i+1)+1, r=last, inv=i;
    if (last!=i)
        ans=(ans-(sg(r)-sg(l-1))*solve(inv))%M;
    last = l-1;
  }
  ans = (ans%M+M)%M; return mem[N/x] = ans;
}
