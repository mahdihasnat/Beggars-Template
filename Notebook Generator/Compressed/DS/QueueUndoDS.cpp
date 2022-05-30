struct Upd {  };
struct CommutativeUndoableDS {
  void addUpd(Upd u) { }
  void undoLastUpd() { }
};
struct QueueUndoDS {
  typedef pair< Upd, int >ABUpd;
  vector< ABUpd >qu;
  CommutativeUndoableDS ds;
  QueueUndoDS() {
    ///call appropriate constructor for ds here
  }
  void pushBack(ABUpd u) {
    ds.addUpd(u.first); qu.emplace_back(u);
  }
  void pushBack(Upd u){ pushBack(ABUpd(u,1)); }
  void popFront() {
    assert(!qu.empty()); vector<ABUpd>pop[2];
    while (!qu.empty()) {
      ds.undoLastUpd();
      pop[qu.back().second].push_back(qu.back());
      qu.pop_back();
      if (pop[0].size() >= pop[1].size()) break;
    }
    if (pop[0].empty()) {
      for (ABUpd &u : pop[1]) {
        u.second = 0; pushBack(u);
      }
    } else {
      for (int i : {1, 0}) {
        reverse(pop[i].begin(), pop[i].end());
        for (ABUpd &u : pop[i]) pushBack(u);
      }
    }
    ds.undoLastUpd(); qu.pop_back();
  }
};
