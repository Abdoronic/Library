struct SparseTable {
	int n;
	int** st;

	SparseTable(int input[], int n) {
		this->n = n;
		int k = (int)floor(log(n) / log(2));
		st = new int*[k + 1];
		for(int i = 0; i <= k; i++)
			st[i] = new int[n];
		for(int j = 0; j < n; j++)
			st[0][j] = input[j];
		for(int i = 1; i < k; i++)
			for(int j = 0; j + (1 << i) <= n; j++)
				st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
	}

	int query(int i, int j) {
		int k = (int)floor(log(j - i + 1) / log(2));
		return min(st[k][i], st[k][j - (1 << k) + 1]);
	}
};
