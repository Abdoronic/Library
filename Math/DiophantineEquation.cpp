#include <bits/stdc++.h>

using namespace std;

int egcd(int a, int b, int& x, int &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int x1, y1;
	int d = egcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - a / b * y1;
	return d;
}

bool findAnySolution(int a, int b, int c, int& x0, int& y0, int& g) {
	g = egcd(abs(a), abs(b), x0, y0);
	if(c % g != 0)
		return false;
	x0 *= (c / g);
	y0 *= (c / g);
	if(a < 0) x0 *= -1;
	if(b < 0) y0 *= -1;
	return true;
}

void shiftEqn(int a, int b, int& x, int& y, int k) {
	x += (k * b);
	y -= (k * a);
}

int countAllsolutions(int a, int b, int c, int minX, int maxX, int minY, int maxY) {
	int x, y, g;
	if(!findAnySolution(a, b, c, x, y, g))
		return 0;
	a /= g; b /= g;
	int sgnA = a > 0 ? +1 : -1;
	int sgnB = b > 0 ? +1 : -1;
	shiftEqn(a, b, x, y, (minX - x) / b);
	if(x < minX)
		shiftEqn(a, b, x, y, sgnB);
	if(x > maxX)
		return 0;
	int lx1 = x;
	shiftEqn(a, b, x, y, (maxX - x) / b);
	if(x > maxX)
		shiftEqn(a, b, x, y, -sgnB);
	int rx1 = x;

	shiftEqn(a, b, x, y, -(minY - y) / a);
	if(y < minY)
		shiftEqn(a, b, x, y, -sgnA);
	if(y > maxY)
		return 0;
	int lx2 = x;
	shiftEqn(a, b, x, y, -(maxY - y) / a);
	if(y > maxY)
		shiftEqn(a, b, x, y, sgnA);
	int rx2 = x;
	if(rx2 < lx2)
		swap(lx2, rx2);
	int lx = max(lx1, lx2);
	int rx = min(rx1, rx2);
	return (rx - lx) / abs(b) + 1;
}

vector< pair<int, int> > findAllsolutions(int a, int b, int c, int minX, int maxX, int minY, int maxY) {
	int x, y, g;
	if(!findAnySolution(a, b, c, x, y, g))
		return {};
	a /= g; b /= g;
	int sgnA = a > 0 ? +1 : -1;
	int sgnB = b > 0 ? +1 : -1;
	shiftEqn(a, b, x, y, (minX - x) / b);
	if(x < minX)
		shiftEqn(a, b, x, y, sgnB);
	if(x > maxX)
		return {};
	int lx1 = x;
	shiftEqn(a, b, x, y, (maxX - x) / b);
	if(x > maxX)
		shiftEqn(a, b, x, y, -sgnB);
	int rx1 = x;

	shiftEqn(a, b, x, y, -(minY - y) / a);
	if(y < minY)
		shiftEqn(a, b, x, y, -sgnA);
	if(y > maxY)
		return {};
	int lx2 = x;
	shiftEqn(a, b, x, y, -(maxY - y) / a);
	if(y > maxY)
		shiftEqn(a, b, x, y, sgnA);
	int rx2 = x;
	if(rx2 < lx2)
		swap(lx2, rx2);
	int lx = max(lx1, lx2);
	int rx = min(rx1, rx2);
	vector< pair<int, int> > sols;
	for(x = lx; x <= rx; x += abs(b))
		sols.push_back({x, (c - a * x) / b});
	return sols;
}
