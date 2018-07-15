template<typename T>
struct SparseTable {   //Zero-based
	T* data;
	int* logTwo;
	int** st;

	void computeLog(int n) {
		logTwo = new int[n + 1];
		logTwo[0] = logTwo[1] = 0;
		int logVal = 0;
		for (int i = 2; i <= n; i++) {
			if ((i & (i - 1)) == 0)
				logVal++;
			logTwo[i] = logVal;
		}
	}

	inline int f(int i, int j) {
		if(data[i] <= data[j])
			return i;
		return j;
	}

	SparseTable(T input[], int n) {
		computeLog(n);
		int k = logTwo[n];
		data = new T[n];
		st = new int*[k + 1];
		for (int i = 0; i <= k; i++)
			st[i] = new int[n];
		for (int i = 0; i < n; i++) {
			data[i] = input[i];
			st[0][i] = i;
		}
		for (int i = 1; i < k; i++)
			for (int j = 0; j + (1 << i) <= n; j++)
				st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
	}

	int query(int i, int j) {
		int k = logTwo[j - i + 1];
		return f(st[k][i], st[k][j - (1 << k) + 1]);
	}
};
