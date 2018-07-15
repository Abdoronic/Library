template<typename T>
struct FenwickTree {
	int N;
	vector<T> tree;
	
	FenwickTree(int n) {
		N = n;
		tree.assign(N + 1, 0);
	}
	
	T query(int idx) {
		T sum = 0;
		while(idx > 0) {
			sum += tree[idx];
			idx ^= idx & -idx;
		}
		return sum;
	}
	
	T query(int l, int r) {
		return query(r) - query(l - 1);
	}
	
	void updatePoint(int idx, int val) {
		while(idx <= N) {
			tree[idx] += val;
			idx += idx & - idx;
		}
	}
};
