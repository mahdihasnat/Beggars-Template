const int MAX = 3000009;
ll mods[2] = {1000000007, 1000000009};
//Some back-up primes: 1072857881, 1066517951, 1040160883
ll bases[2] = {137, 281};
ll pwbase[3][MAX];
 
void Preprocess(){
    pwbase[0][0] = pwbase[1][0] = 1;
    for(ll i = 0; i < 2; i++){
        for(ll j = 1; j < MAX; j++){
            pwbase[i][j] = (pwbase[i][j - 1] * bases[i]) % mods[i];
        }
    }
}
 
ll fmod(ll a, ll b, int md=mods[0]) {
  unsigned long long x = (long long) a * b;
  unsigned xh = (unsigned) (x >> 32), xl = (unsigned) x, d, m;
  asm(
    "divl %4; \n\t"
    : "=a" (d), "=d" (m)
    : "d" (xh), "a" (xl), "r" (md)
  );
  return m;
}
 
 
struct Hashing{
    vector<vector<ll>> hsh;
 
    Hashing(){}
    Hashing(string &_str) {
        hsh.push_back(vector<ll>(_str.size()+5, 0));
        hsh.push_back(vector<ll>(_str.size()+5, 0));
        Build1(_str);
    }
 
    void Build(const string &str){Build1(str);Build2(str);}
    void Build1(const string &str) {
        int j = 0;
        for(ll i = str.size() - 1; i >= 0; i--){
                hsh[j][i] = fmod(hsh[j][i + 1], bases[j], mods[j]) + str[i];
                if (hsh[j][i] > mods[j])
                    hsh[j][i] -= mods[j];
        }
    }
    void Build2(const string &str) {
        int j = 1;
        for(ll i = str.size() - 1; i >= 0; i--){
                hsh[j][i] = fmod(hsh[j][i + 1], bases[j], mods[j]) + str[i];
                if (hsh[j][i] > mods[j])
                    hsh[j][i] -= mods[j];
        }
    }
 
    pair<ll,ll> GetHash(ll i, ll j){
        assert(i <= j);
        ll tmp1 = (hsh[0][i] - fmod(hsh[0][j + 1] ,pwbase[0][j - i + 1]));
        ll tmp2 = (hsh[1][i] - fmod(hsh[1][j + 1] , pwbase[1][j - i + 1], mods[1]));
        if(tmp1 < 0) tmp1 += mods[0];
        if(tmp2 < 0) tmp2 += mods[1];
        return make_pair(tmp1, tmp2);
    }
    ll getSingleHash(ll i, ll j) {
        assert(i <= j);
        ll tmp1 = (hsh[0][i] - fmod(hsh[0][j + 1] ,pwbase[0][j - i + 1]));
        if(tmp1 < 0) tmp1 += mods[0];
        return tmp1;
    }
};