#include<bits/stdc++.h>
#include<vector>

using namespace std;

#define ll long long
int n,q;
vector<ll>tree;

ll get_val(int node, int node_low, int node_high, int query_low, int query_high, ll val) {
	if (node_low >= query_low && node_high <= query_high) {
		if (val != -1) tree[node] += val;
		return tree[node];
	}
	if (node_low > query_high || node_high < query_low) return 0;
	int middle = (node_low + node_high) / 2;
	ll sum = get_val(2 * node, node_low, middle, query_low, query_high, val)
		   + get_val(2 * node + 1, middle + 1, node_high, query_low, query_high, val);
	return tree[node] + sum;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;
	vector<ll>x(n);
	for(int i = 0 ; i < n; i++){
		cin >> x[i];
	}
	while (__builtin_popcount(n) != 1) n++;
	tree.resize(2*n);
	for (int i = 0; i < x.size(); i++){ 	// use x.size() not n cause we changed n. If it is changed from 2^31 to 2^32 then we're trying to access illegal memory from 2^31+1 to 2^32 in x
		tree[i+n] = x[i];
	}
	
	for (int i = 0; i < q; i++){
		int choice;
		cin >> choice;
		if (choice == 1) {
			int low, high;
			ll u;
			cin >> low >> high >> u;
			get_val(1, 0, n-1, --low, --high, u);
		}
		else {
			int k;
			cin >> k;
			k--;
			cout << get_val(1, 0, n-1, k , k, -1) << "\n";
		}
	}
}


