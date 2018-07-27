#include <bits/stdc++.h>
using namespace std;

vector<int> factors;

void sieveNumFactors(int N) {
	factors.assign(N + 1, 0);
	for(int i = 2; i <= N; i++) {
		if(factors[i] == 0) {
			for(int j = i; j <= N; j += i) {
				int x = j, pf = 0;
				while(x % i == 0 && ++pf) x /= i;
				factors[j] += pf;
			}
 		}
	}
}

vector<int> nod;

void sieveNumDivsors(int N) {
	nod.assign(N + 1, 1);
	for(int i = 2; i <= N; i++) {
		if(nod[i] == 1) {
			for(int j = i; j <= N; j += i) {
				int x = j, pf = 1;
				while(x % i == 0 && ++pf) x /= i;
				nod[j] *= pf;
			}
 		}
	}
}

vector<int> sod;

void sieveSumDivsors(int N) {
	sod.assign(N + 1, 1);
	for(int i = 2; i <= N; i++) {
		if(sod[i] == 1) {
			for(int j = i; j <= N; j += i) {
				int x = j, e = 0;
				while(x % i == 0 && ++e) x /= i;
				if(e > 0)
					sod[j] *= ((pow(i, e + 1) - 1) / (i - 1));
			}
 		}
	}
}

vector<int> spf;

void sievePrimeFactors(int N) { 
	spf.resize(N + 1);
	for (int i = 1; i <= N; i++)
		spf[i] = i & 1 ? i : 2;
	for (int i = 3; i <= N; i++) {
		if (spf[i] == i) {
			if (1LL * i * i <= N)
				for (int j = i * i; j <= N; j += i) {
					if (spf[j] == j)
						spf[j] = i;
				}
		}
	}
}

vector<int> getPrimeFactors(int N) {
	vector<int> ret;
	while (N > 1) {
		ret.push_back(spf[N]);
		N /= spf[N];
	}
	return ret;
}

vector<int> phi;

void sievePhi(int N) {
	phi.resize(N + 1);
	for(int i = 1; i <= N; i++)
		phi[i] = i;
	for(int i = 2; i <= N; i++)
		if(phi[i] == i)
			for(int j = i; j <= N; j += i)
				phi[j] -= phi[j] / i;
}
