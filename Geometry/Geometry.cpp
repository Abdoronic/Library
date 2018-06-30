#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define pb push_back

#define INF int(1e9)
#define EPS 1e-9
#define MOD int(1e9 + 7)

//Geometry Library
struct vec;
struct point;
struct line;
struct lineSegment;

struct vec {
	double x, y;

	vec(double _x, double _y) : x(_x), y(_y) {}

	bool operator== (const vec& v) { return abs(x - v.x) < EPS && abs(y - v.y) < EPS; }

	vec scale(double s) { return vec(x * s, y * s); }

	double dot(vec v) { return x * v.x + y * v.y; }

	double cross(vec v) { return x * v.y - y * v.x; }

	double norm2() { return x * x + y * y; }

	vec normalize() { return scale( 1 / sqrt(norm2()) ); }

	vec reverse() { return vec(-x, -y); }
};

struct point {
	double x, y;

	point() { x = y = 0; }

	point(double _x, double _y) : x(_x), y(_y) {}

	bool operator< (const point& p) const {
		if(abs(x - p.x) > EPS)
			return x < p.x;
		return y - p.y < -EPS;
	}

	bool operator== (const point& p) const {
		return abs(x - p.x) < EPS && abs(y - p.y) < EPS;
	}

	static vec make_vec(point a, point b) { return vec(b.x - a.x, b.y - a.y); }

	double dist(point p) { return hypot(p.x - x, p.y - y); }

	point translate(vec v) { return point(x + v.x, y + v.y); }

	point rotate(double theta) {
		double c = cos(theta), s = sin(theta);
		return point(c*x - s*y, s*x + c*y);
	}

	point rotate(double theta, point about) {
		vec v = make_vec(about, point(0, 0));
		return translate(v).rotate(theta).translate(v.reverse());
	}

	bool between(point p, point q) {
		return x - max(p.x, q.x) < EPS && x - min(p.x, q.x) > -EPS
				&& y - max(p.y, q.y) < EPS && y - min(p.y, q.y) > -EPS;
	}

	bool onLine(point p, point q) {
		if(p == q) return (*this) == p;
		vec pq = make_vec(p, q), pr = make_vec(p, *this);
		return abs(pq.cross(pr)) < EPS;
	}

	bool onRay(point p, point q) {
		if(p == q) return (*this) == p;
		vec pq = make_vec(p, q), pr = make_vec(p, *this);
		return pq.normalize() == pr.normalize();
	}

	bool onSegment(point p, point q) {
		if(p == q) return (*this) == p;
		return onRay(p, q) && onRay(q, p);
	}

	static bool colinear(point p, point q, point r) {
		vec pq = make_vec(p, q), pr = make_vec(p, r);
		return abs(pq.cross(pr)) < EPS;
	}

	static bool cw(point p, point q, point r) {
		vec pq = make_vec(p, q), pr = make_vec(p, r);
		//if onLine points acceptable then { < EPS }
		return pq.cross(pr) < 0;
	}

	static bool ccw(point p, point q, point r) {
		vec pq = make_vec(p, q), pr = make_vec(p, r);
		//if onLine points acceptable then { > -EPS }
		return pq.cross(pr) > 0;
	}

	static double angle(point a, point o, point b) {
		vec oa = make_vec(o, a), ob = make_vec(o, b);
		return acos(oa.dot(ob)/sqrt(oa.norm2() * ob.norm2()));
	}

	point reflection(line l);

	double dist_to_line(point a, point b);

};

struct line {
	double a, b, c;

	line(){ a = b = c = 0; };

	line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

	line(point p, point q) {
		if(abs(p.x - q.x) < EPS) {
			//vertical
			b = 0.0;
			a = 1.0;
			c = -p.x;
		} else {
			b = 1.0;
			a = (q.y - p.y) / (p.x - q.x);
			c = -(a*p.x + p.y);
		}
	}

	line(point p, double m) {
		b = 1.0;
		a = -m;
		c = -(a*p.x + p.y);
	}

	bool parallel(line l) { return abs(a - l.a) < EPS && abs(b - l.b) < EPS; }

	bool same(line l) { return parallel(l) && abs(c - l.c) < EPS; }

	bool intersection(line l, point& p) {
		if(parallel(l)) return false;
		p.x = (b * l.c - c * l.b) / (a * l.b - b * l.a);
		if(abs(b) < EPS)
			p.y = -(l.a * p.x + l.c);
		else
			p.y = -(a * p.x + c);
		return true;
	}

	point closest_point(point p) {
		if(abs(b) < EPS) return point(-c , p.y);
		if(abs(a) < EPS) return point(p.x , -c);
		point q;
		intersection(line(p, 1/a), q);
		return q;
	}
};

point point::reflection(line l) {
	point proj = l.closest_point(*this);
	vec v = make_vec(*this, proj);
	return translate(v).translate(v);
}

double point::dist_to_line(point a, point b) {
	line l(a, b);
	point proj = l.closest_point(*this);
	return dist(proj);
}

vec toVec(point a, point b) { return vec(b.x - a.x, b.y - a.y); }

struct lineSegment {
	point a, b;

	lineSegment() {}

	lineSegment(point p, point q) : a(p), b(q) {}

	bool intersection(lineSegment ls) {
		line l1(a, b);
		line l2(ls.a, ls.b);
		if(l1.parallel(l2)) {
			if(l1.same(l2))
				return a.between(ls.a, ls.b) || b.between(ls.a, ls.b)
						|| ls.a.between(a, b) || ls.b.between(a, b);
			return false;
		}
		point x;
		l1.intersection(l2, x);
		return x.between(a, b) && x.between(ls.a, ls.b);
	}
};

//Polygon functions
double perimeter(vector<point> poly) {
	double sum = 0.0;
	for(int i = 0; i < (int)poly.size() - 1; ++i)
		sum += poly[i].dist(poly[i + 1]);
	return sum;
}

double polygonArea(vector<point> poly) {
	double area = 0.0;
	for(int i = 0; i < (int)poly.size() - 1; ++i)
		area += (poly[i].x - poly[i + 1].x) * (poly[i].y + poly[i + 1].y);
	return abs(area) / 2.0;
}

bool isConvex(vector<point> poly) {
	int sz = poly.size();
	if(sz <= 3) return false;
	bool isLeft = point::ccw(poly[sz - 2], poly[0], poly[1]);
	for(int i = 1; i < sz - 1; ++i)
		if(point::ccw(poly[i - 1], poly[i], poly[i+1]) != isLeft)
			return false;
	return true;
}

bool inPolygon(vector<point> poly, point p) { //doesn't handle verticies
	double sum = 0, PI = atan(1) * 4;
	for(int i = 0; i < (int)poly.size() - 1; ++i) {
		double theta = point::angle(poly[i], p, poly[i + 1]);
		if(abs(theta) < EPS || (abs(theta - PI) < EPS && p.between(poly[i], poly[i + 1])))
			return true; //return false if onLine points not Acceptable
		if(point::ccw(p, poly[i], poly[i + 1]))
			sum += theta;
		else
			sum -= theta;
	}
	return abs(abs(sum) - 2 * PI) < EPS;
}

vector<point> cutPolygon(vector<point> poly, point a, point b) {
	vector<point> p;
	line l(a, b);
	vec v = toVec(a, b);
	point x;
	for(int i = 0; i < poly.size(); i++) {
		double left1 = v.cross(toVec(a, poly[i]));
		double left2 = i + 1 == poly.size() ? 0 : v.cross(toVec(a, poly[i + 1]));
		if(left1 > -EPS)
			p.push_back(poly[i]);
		if(left1 * left2 < -EPS) {
			l.intersection(line(poly[i], poly[i + 1]), x);
			p.push_back(x);
		}
	}
	if(!p.empty() && !(p.front() == p.back()))
		p.push_back(p.front());
	return p;
}

void convexHull(vector<point>& pts) {
	if(pts.size() == 1) return;
	sort(pts.begin(), pts.end());
	point leftMost = pts.front(), rightMost = pts.back();
	vector<point> up, down;
	up.push_back(leftMost); down.push_back(leftMost);
	for(int i = 1; i < pts.size(); ++i) {
		if(i == (int)pts.size() - 1 || point::cw(leftMost, pts[i], rightMost)) {
			while(up.size() >= 2 && !point::cw(up[(int)up.size() - 2], up[(int)up.size() - 1], pts[i]))
				up.pop_back();
			up.push_back(pts[i]);
		}
		if(i == (int)pts.size() - 1 || point::ccw(leftMost, pts[i], rightMost)) {
			while(down.size() >= 2 && !point::ccw(down[(int)down.size() - 2], down[(int)down.size() - 1], pts[i]))
				down.pop_back();
			down.push_back(pts[i]);
		}
	}
	pts.clear();
	for(int i = 0; i < down.size(); ++i)
		pts.push_back(down[i]);
	for(int i = (int)up.size() - 2; i >= 0; --i)
		pts.push_back(up[i]);
}
