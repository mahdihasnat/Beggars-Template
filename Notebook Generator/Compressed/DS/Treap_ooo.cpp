namespace treap{
struct node{
  int key, prior;
  //int val, agg;
  node *l, *r;
  node() {}
  node(int _k, int _p) :
    key(_k), prior(_p), l(NULL), r(NULL){}
};
typedef node* pnode;
//inline int getagg(pnode t){
//  return t? t->agg : 0;
//}
//inline void updagg(pnode t){
//  if(t) t->agg = t->val +
//    getagg(t->l) + getagg(t->r);
//}
void split(pnode t,int key,pnode &l, pnode &r){
  if(!t) l = r = NULL;
  else if(key < t->key)
    split(t->l, key, l, t->l), r = t;
  else  split(t->r, key, t->r, r), l = t;
  //updagg(t);
}
void merge(pnode &t, pnode l, pnode r){
  if(!l || !r) t = l? l : r;
  else if(l->prior > r-> prior)
    merge(l->r, l->r, r), t = l;
  else  merge(r->l, l, r->l), t = r;
  //updagg(t);
}
/// inserts it into t, duplicate will be kept
void ins(pnode &t, pnode it){
  if(!t) t = it;
  else if(it->prior > t->prior)
    split(t, it->key, it->l, it->r), t = it;
  else  ins(it->key < t->key? t->l : t->r, it);
  //updagg(t);
}
/// erases key from t, in case of duplicate,
/// an arbitrary one is deleted
/// returns true if something was deleted
bool ers(pnode &t, int key){
  if(t == NULL) return false;
  bool ret = true;
  if(t->key == key) merge(t, t->l, t->r);
  else  ret = ers(key < t->key? t->l : t->r, key);
  //updagg(t);
  return ret;
} }
