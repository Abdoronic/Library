struct DSU {   //Zero-based
	int size;
	int* p;
	int* rank;

	DSU (int n) {
		size = n;
		p = new int[n];
		rank = new int[n];
		for(int i = 0; i < n; i++) {
			p[i] = i;
			rank[i] = 0;
		}
	}

	int findSet(int i) { return i == p[i] ? i : p[i] = findSet(p[i]); }

	bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

	void merge(int i, int j) {
		i = findSet(i);
		j = findSet(j);
		if(i == j) return;
		if(rank[i] < rank[j]) {
			p[i] = j;
		} else {
			p[j] = i;
			if(rank[i] == rank[j])
				rank[i]++;
		}
		size--;
	}
};
