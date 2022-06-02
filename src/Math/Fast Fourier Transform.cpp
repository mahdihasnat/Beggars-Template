#define MOD 1000000007
#define MAX 200005
#define PMAX 55
#define PRECISION 0.000001
#define INF 2000000000
using cd = complex<double>;
const double PI = acos(-1);
void fft(vector<cd>& a, bool invert){
    int n = a.size();
    for(int i = 1, j = 0; i < n; i++){
        int bit = n>>1;
        for(; j&bit; bit>>=1){
            j^=bit;
        }
        j ^= bit;
        if(i < j)	swap(a[i], a[j]);
    }
    for(int len = 2; len <= n; len <<= 1){
        double ang = 2*PI/len*(invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for(int i = 0; i < n; i += len){
            cd w(1);
            for(int j = 0; j < len/2; j++){
                cd u = a[i+j], v = a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }
    if(invert){
        for(cd &x: a)	x /= n;
    }
}
vector<int> multiply(vector<int>&a,vector<int>&b){
    vector<cd> fa(a.begin(), a.end());
    vector<cd> fb(b.begin(), b.end());	int n = 1;
    while(n < a.size()+b.size())	n <<= 1;
    fa.resize(n);	fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for(int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);
    vector<int> result(n);
    for(int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}
//Number Theoretic Transformation
ll gcd(ll a,ll b){
    if(b==0) return a;
    else return gcd(b,a%b);
}
ll egcd(ll a, ll b, ll & x, ll & y) {
    if (a == 0) {
        x = 0;	y = 1;
        return b;
    }
    ll x1, y1;	ll d = egcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;	y = x1;
    return d;
}
ll ModuloInverse(ll a,ll n){
    ll x,y;	x=gcd(a,n);
    a=a/x;	n=n/x;
    ll res = egcd(a,n,x,y);	x=(x%n+n)%n;
    return x;
}
const int mod = 998244353;
const int root = 15311432;
const int root_1 = 469870224;
const int root_pw = 1 << 23;
void fft(vector<int> & a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
int u=a[i+j],v=(int)(1LL*a[i+j+len/2]*w%mod);
a[i+j] = u + v < mod ? u + v : u + v - mod;
a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
w = (int)(1LL * w * wlen % mod);
            }
        }
    }
    if (invert) {
        int n_1 = (int) ModuloInverse(n, mod);
        for (int & x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}
vector<int> multiply(vector<int>&a,vector<int> &b){
    vector<int> fa(a.begin(), a.end());
    vector<int> fb(b.begin(), b.end());
    int n = 1;
    while(n < a.size()+b.size())
        n <<= 1;
    fa.resize(n);	fb.resize(n);
    fft(fa, false);	fft(fb, false);
    for(int i = 0; i < n; i++)
        fa[i] = (int) (1LL*fa[i]*fb[i]%mod);
    fft(fa, true);
    vector<int> result(n);
    for(int i = 0; i < n; i++)
        result[i] = fa[i];
    return result;
}