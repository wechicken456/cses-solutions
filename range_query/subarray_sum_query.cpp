
// https://usaco.guide/plat/segtree-ext/#solution---subarray-sum-queries

#include<vector>
#include<bits/stdc++.h>

#define ll long long
#define pb push_back

using namespace std;

struct Node {
	ll max_sum, max_l, max_r, sum; 
	Node operator+ (Node b) {
		return {
			max(max(max_sum, b.max_sum), max_r + b.max_l),
			max(max_l, sum + b.max_l),
			max(b.max_r, b.sum + max_r),
			sum + b.sum
		};
	}
};

int n,q;
vector<int>a;
vector<Node>tree;

void build_tree() {
	while (__builtin_popcount(n) != 1) {
		n++;
		a.pb(0);
	}
	
	tree.resize(2 * n );
	for (int i = 0 ; i < n ;i ++) {
		tree[i + n] = {max(0, a[i]), max(0, a[i]), max(0, a[i]), a[i]};
	}
	
	for (int i = n - 1; i >= 1; i--) {
		tree[i] = tree[2*i] + tree[2*i+1];
	}
	
}

void update(int pos , int value) {
	a[pos] = value;
	tree[pos + n] = {max(0, a[pos]), max(0, a[pos]), max(0, a[pos]), a[pos]};
	pos += n;
	pos /= 2;
	while (pos > 0) {
		tree[pos] = tree[2*pos] + tree[2*pos+1];
		pos /= 2;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;
	a = vector<int>(n);
	for(int i = 0 ; i < n; i++){
		cin >> a[i];
	}	
	build_tree();
	
	for (int i = 0 ; i < q; i++){
		int pos , value;
		cin >> pos >> value;
		pos--;
		update(pos, value);
		cout << tree[1].max_sum << "\n";
	}
}
