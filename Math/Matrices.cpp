#include <bits/stdc++.h>

using namespace std;

#define MOD int(1e9 + 7)

vector< vector<int> > matrixMultiply(vector< vector<int> > a, vector<vector<int> > b, int p, int q, int r) {
	vector< vector<int> > ans(p, vector<int>(r));
	for (int i = 0; i < p; i++)
		for (int j = 0; j < r; j++)
			for (int k = 0; k < q; k++)
				ans[i][j] += a[i][k] * b[k][j];
	return ans;
}

vector< vector<int> > matrixMultiplyMod(vector< vector<int> > a, vector< vector<int> > b, int p, int q, int r) {
	vector< vector<int> > ans(p, vector<int>(r));
	for (int i = 0; i < p; i++)
		for (int j = 0; j < r; j++)
			for (int k = 0; k < q; k++) {
				ans[i][j] += (1ll * a[i][k] * b[k][j]) % MOD;
				ans[i][j] %= MOD;
			}
	return ans;
}

vector< vector<int> > matrixPower(vector< vector<int> > a, int p) {
	int n = a.size();
	vector< vector<int> > ans(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		ans[i][i] = 1;
	while (p) {
		if (p & 1)
			ans = matrixMultiply(ans, a, n, n, n);
		a = matrixMultiply(a, a, n, n, n);
		p >>= 1;
	}
	return ans;
}
