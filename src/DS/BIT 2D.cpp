void update(int x, int y, int val) {
  int y1;
  while (x <= max_x) {
    y1 = y;
    while (y1 <= max_y) {
      tree[x][y1] += val;
      y1 += (y1 & -y1);
    }
    x += (x & -x);
  }
}