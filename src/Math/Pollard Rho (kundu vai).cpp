/**
Range: 10^18 (tested), should be okay up to 2^63-1
miller_rabin(n)
    returns 1 if prime, 0 otherwise
    Magic bases:
        n < 4,759,123,141        3 :  2, 7, 61
        n < 1,122,004,669,633    4 :  2, 13, 23, 1662803
        n < 3,474,749,660,383    6 :  2, 3, 5, 7, 11, 13
n < 2^64 7 : 2, 325, 9375, 28178, 450775, 9780504, 1795265022
    Identifies 70000 18 digit primes in 1 second on Toph
pollard_rho(n):
    If n is prime, returns n
    Otherwise returns a proper divisor of n
Note: for factorizing large number, do trial division upto
      cubic root and then call pollard rho once.
*/
LL mult(LL a, LL b, LL mod) {
    assert(b < mod && a < mod);
    long double x = a;
    uint64_t c = x * b / mod;
    int64_t r = (int64_t)(a * b - c * mod) % (int64_t)mod;
    return r < 0 ? r + mod : r;
}
LL power(LL x, LL p, LL mod){
	LL s=1, m=x;
	while(p) {
		if(p&1) s = mult(s, m, mod);
		p>>=1;
		m = mult(m, m, mod);
	}
	return s;
}
bool witness(LL a, LL n, LL u, int t){
	LL x = power(a,u,n);
	for(int i=0; i<t; i++) {
		LL nx = mult(x, x, n);
		if (nx==1 && x!=1 && x!=n-1) return 1;
		x = nx;
	}
	return x!=1;
}
vector<LL> bases = {2, 325, 9375, 28178, 450775, 9780504,
1795265022};
bool miller_rabin(LL n) {
	if (n<2)    return 0;
	if (n%2==0)   return n==2;
	LL u = n-1;
	int t = 0;
	while(u%2==0)   u/=2, t++;  // n-1 = u*2^t
	for (LL v: bases) {
		LL a = v%(n-1) + 1;
		if(witness(a, n, u, t)) return 0;
    }
	return 1;
}
LL gcd(LL u, LL v) {
    if (u == 0) return v;
    if (v == 0) return u;
    int shift = __builtin_ctzll(u | v);
    u >>= __builtin_ctzll(u);
    do {
        v >>= __builtin_ctz(v);
        if (u > v) swap(u, v);
        v = v - u;
    } while (v);
    return u << shift;
}
mt19937_64 rng(chrono::steady_clock::now().
							time_since_epoch().count());
LL pollard_rho(LL n) {
    if (n==1)               return 1;
    if (n%2==0)             return 2;
	if (miller_rabin(n))    return n;
    while (true) {
        LL x = uniform_int_distribution<LL>(1, n-1)(rng);
        LL y = 2, res = 1;
        for (int sz=2; res == 1; sz*=2) {
            for (int i=0; i<sz && res<=1; i++) {
                x = mult(x, x, n) + 1;
                res = gcd(abs(x-y), n);
            }
            y = x;
        }
        if (res!=0 && res!=n) return res;
    }
}