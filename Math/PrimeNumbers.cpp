#include <bits/stdc++.h>

using namespace std;

vector<int> primes;
vector<bool> isPrime;

void sieve(int N) {  //all prime numbers from 1 to N aprox. (N / log N) numbers
	isPrime.assign(N + 1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 2; i <= N; i++) {
		if(isPrime[i]) {
			primes.push_back(i);
			if(1LL * i * i <= N)
				for(int j = i * i; j <= N; j += i)
					isPrime[j] = false;
 		}
	}
}

bool checkPrime(int N) {
	if(N < isPrime.size())
		return isPrime[N];
	for(int p : primes) {
		if(p * p > N) break;
		if(N % p == 0)
			return false;
	}
	return true;
}

int numDiv(int N) {
	int num = 1;
	for(int p : primes) {
		if(p * p > N) break;
		int e = 0;
		while(N % p == 0 && ++e) N /= p;
		num *= (e + 1);
	}
	if(N > 1) num *= 2;
	return num;
}

vector<int> primeFactors(int N) {
	vector<int> factors;
	for(int p : primes) {
		if(p * p > N) break;
		while(N % p == 0) {
			N /= p;
			factors.push_back(p);
		}
	}
	if(N > 1)
		factors.push_back(N);
	return factors;
}

vector< pair<int, int> > primeFactorsPowers(int N) {
	vector<	pair<int, int> > factorsPowers;
	for(int p : primes) {
		if(p * p > N)
			break;
		int e = 0;
		while(N % p == 0 && ++e) N /= p;
		if(e > 0)
			factorsPowers.push_back({p, e});
	}
	if(N > 1)
		factorsPowers.push_back({N, 1});
	return factorsPowers;
}

int phi(int N) {
	int res = N;
	for(int i = 2; i * i <= N; i++) {
		if(N % i == 0) {
			while(N % i == 0) N /= i;
			res -= res / i;
		}
	}
	if(N > 1)
		res -= res / N;
	return res;
}
