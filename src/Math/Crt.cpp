PII CRT(int x,int a,int y, int b) {
	int s, t;
	int d = extended_euclid(x, y, s, t);
	if (a % d != b % d) return make_pair(0, -1);
	return make_pair(mod(s*b*x+t*a*y,x*y)/d,x*y/d);
}