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

void replaceAll(string& s, string org, string rep) {
	size_t c = 0;
	while(s.find(org, c) != string::npos) {
		c = s.find(org, c);
		s.replace(c, org.length(), rep);
		c += rep.size();
	}
}

int compareToDouble(double x, double y) {
	if(x - y < -EPS)
		return -1;
	if(x - y > EPS)
		return 1;
	if(abs(x-y) < EPS)
		return 0;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string s = "aab bbc aab aaa bbaaaa";
	replaceAll(s, "aa", "XX");
	cout << s << endl;
	return 0;
}
