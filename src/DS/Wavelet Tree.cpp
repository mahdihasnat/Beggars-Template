struct wavelet_tree{
  int lo  , hi ;
  wavelet_tree *l=0,*r=0;
  vi b,c;//c for prefix sum
//nos are in range [x,y] , array indices [from,to)
  wavelet_tree(int *from, int *to, int x, int y){
    lo = x, hi = y;
    if( from >= to) return;
    if( hi == lo ) {
      b.reserve(to-from+1);
      b.pb(0);
      c.reserve(to-from+1);
      c.pb(0);
      for(auto it = from; it != to; it++){
        b.pb(b.back() + 1);
        c.pb(c.back()+*it);
      }
      return ;
    }
    int mid = (lo+hi)/2;
    auto f = [mid](int x){
      return x <= mid;
    };
    b.reserve(to-from+1);
    b.pb(0);
    c.reserve(to-from+1);
    c.pb(0);
    for(auto it = from; it != to; it++){
      b.pb(b.back() + f(*it));
      c.pb(c.back() + *it);
    }
    auto pivot = stable_partition(from, to, f);
    l = new wavelet_tree(from, pivot, lo, mid);
    r = new wavelet_tree(pivot, to, mid+1, hi);
  }// swap a[i] with a[i+1]  , if a[i]!=a[i+1]
  void swapadjacent(int i){
    if(lo == hi) return ;
    b[i]= b[i-1] + b[i+1] - b[i];
    c[i] = c[i-1] + c[i+1] - c[i];
    if( b[i+1]-b[i] == b[i] - b[i-1]){
      if(b[i]-b[i-1])
            return this->l->swapadjacent(b[i]);
      else  return this->r->swapadjacent(i-b[i]);
    }
  }
//count of nos in [l, r] Less than or equal to k
  int LTE(int l, int r, int k){
    if(l > r or k < lo) return 0;
    if(hi <= k) return r - l + 1;
    int lb = b[l-1], rb = b[r];
    return this->l->LTE(lb+1,rb,k)+
            this->r->LTE(l-lb,r-rb,k);
  }
//count of nos in [l, r] equal to k
  int count(int l, int r, int k){
    if(l > r or k < lo or k > hi) return 0;
    if(lo == hi)  return r - l + 1;
    int lb = b[l-1], rb = b[r], mid = (lo+hi)/2;
    if(k <= mid) return this->l->count(lb+1,rb,k);
    return this->r->count(l-lb, r-rb, k);
  }
//sum of nos in [l ,r] less than or equal to k
  int sumk(int l, int r, int k){
    if(l > r or k < lo) return 0;
    if(hi <= k) return c[r]-c[l-1];
    int lb = b[l-1], rb = b[r];
    return this->l->sumk(lb+1,rb,k)+
            this->r->sumk(l-lb,r-rb,k);
  }
  ~wavelet_tree(){
    if(l) delete l;
    if(r) delete r;
  }
}