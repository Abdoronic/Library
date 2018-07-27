int addMod(int a, int b) {
    return ((a % MOD) + (b % MOD)) % MOD;
}

int subtractMod(int a, int b) {
    return (addMod(a, -b) + MOD) % MOD;
}

int multiplyMod(int a, int b) {
	return (1LL * (a % MOD) * (b % MOD)) % MOD;
}

int modPow(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1)
			res = multiplyMod(res, a);
		a = multiplyMod(a, a);
		n >>= 1;
	}
	return res;
}

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

int modInverse(int a) {
    int x, y;
    egcd(a, MOD, x, y);
    return (x % MOD + MOD) % MOD;
}
