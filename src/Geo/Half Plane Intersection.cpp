#define MAX 200005
#define MOD 1009
#define SMOD 998244353
#define ROOT 318
#define GMAX 19
#define INF 1000000000000000000
#define EPS 0.000000001
#define NIL 0
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
class HalfPlaneIntersection{
    static double eps, inf;
public:
    struct Point{
        double x, y;
explicit Point(double x=0,double y=0):x(x), y(y) {}
friend Point operator+(const Point&p,const Point&q){
    return Point(p.x + q.x, p.y + q.y);
}
friend Point operator-(const Point&p,const Point&q){
    return Point(p.x - q.x, p.y - q.y);
}
friend Point operator*(const Point&p,double&k){
    return Point(p.x * k, p.y * k);
}
friend double cross(const Point& p, const Point& q){
    return p.x * q.y - p.y * q.x;
}
};
// Basic half-plane struct.
    struct Halfplane
    {// 'p' is a passing point of the line and
        //'pq' is the direction vector of the line.
        Point p, pq;    double angle;
        Halfplane() {}
        Halfplane(const Point&a,const Point&b):p(a)
        ,pq(b-a){
            angle = atan2l(pq.y, pq.x);
        }
// Check if point 'r' is outside this half-plane.
// Every half-plane allows the region to the LEFT
// of its line.
        bool out(const Point& r){
            return cross(pq, r - p) < -eps;
        }
//Comparator for sorting. If the angle of both half-
//planes is equal, the leftmost one should go first.
        bool operator < (const Halfplane& e) const{
            if (fabsl(angle - e.angle) < eps)
                return cross(pq, e.p - p) < 0;
            return angle < e.angle;
        }// We use equal comparator for std::unique
        //to easily remove parallel half-planes.
        bool operator == (const Halfplane& e) const{
            return fabsl(angle - e.angle) < eps;
        }// Intersection point of the lines of two
//half-planes. It is assumed they're never parallel.
        friend Point inter(const Halfplane& s,
                           const Halfplane& t){
double alpha=cross((t.p-s.p),t.pq)/cross(s.pq,t.pq);
return s.p + (s.pq * alpha);
        }
    };
vector<Point>hp_intersect(vector<Halfplane>&H)
    {
        Point box[4] =  // Bounding box in CCW order
        {
            Point(inf, inf),
            Point(-inf, inf),
            Point(-inf, -inf),
            Point(inf, -inf)
        };
for(int i=0;i<4;i++){//Add bounding box half-planes.
            Halfplane aux(box[i], box[(i+1) % 4]);
            H.push_back(aux);
        }
        // Sort and remove duplicates
        sort(H.begin(), H.end());
        H.erase(unique(H.begin(),H.end()), H.end());
        deque<Halfplane> dq;
        int len = 0;
        for(int i = 0; i < int(H.size()); i++){
// Remove from the back of the deque while last
// half-plane is redundant
while(len>1&&H[i].out(inter(dq[len-1], dq[len-2]))){
                dq.pop_back();
                --len;
            }// Remove from the front of the deque
        //while first half-plane is redundant
    while (len > 1 && H[i].out(inter(dq[0],dq[1]))){
                dq.pop_front();
                --len;
            } // Add new half-plane
            dq.push_back(H[i]); ++len;
        } // Final cleanup: Check half-planes at the
        //front against the back and vice-versa
while(len>2&&dq[0].out(inter(dq[len-1],dq[len-2]))){
            dq.pop_back();  --len;
        }
while(len > 2 && dq[len-1].out(inter(dq[0],dq[1]))){
            dq.pop_front(); --len;
        }
        // Report empty intersection if necessary
        if (len < 3) return vector<Point>();
// Reconstruct the convex polygon from
//the remaining half-planes.
        vector<Point> ret(len);
        for(int i = 0; i+1 < len; i++){
            ret[i] = inter(dq[i], dq[i+1]);
        }
        ret.back() = inter(dq[len-1], dq[0]);
        return ret;
    }
};
double HalfPlaneIntersection::eps=1e-9;
double HalfPlaneIntersection::inf=1e9;
		vector<HalfPlaneIntersection::Halfplane> V;
		vector<HalfPlaneIntersection::Point> P;
		for(i=0; i<n; i++){
				int c;
				scanf("%d",&c);
				HalfPlaneIntersection::Halfplane h;
				HalfPlaneIntersection::Point p;
				for(j=0; j<c; j++){
						scanf("%lf %lf",&p.x,&p.y);
						P.push_back(p);
				}
				for(j=0; j<c; j++){
h=HalfPlaneIntersection::Halfplane(P[j],P[(j+1)%c]);
						V.push_back(h);
				}
				P.clear();
		}
		P=HalfPlaneIntersection::hp_intersect(V);
		double ans=0;
		n=P.size();
		for(i=0; i<n; i++){
ans=ans+P[i].x*P[(i+1)%n].y-P[i].y*P[(i+1)%n].x;
		}
		ans=ans/2;