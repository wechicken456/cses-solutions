#include<vector>
#include<bits/stdc++.h>

#define ll long long

using namespace std;
vector<ll>tree;
const ll maxA = 1e9+1;
int n,q;

void update(int pos, ll value){
	tree[pos] = value;
	pos /= 2;
	while (pos > 0) {
		ll cur_max = max(tree[2*pos], tree[2*pos+1]);
		if ( cur_max == tree[pos]) return;
		tree[pos] = cur_max;
		pos /= 2;
	}
}


ll query(int node, ll value) {
	if (node >= n && node <= 2*n && node > 1) {
		update(node, tree[node] - value);
		return node - n + 1;
	}
	int left = 2 * node;
	int right = 2 * node + 1;
	if (tree[left] >= value && tree[right] >= value) return query(left, value);
	else if (tree[left] >= value) return query(left, value);
	else if (tree[right] >= value) return query(right, value);
	return 0;
}

void build_tree(vector<ll>a) {
	// pad with 0 to make power of 2
	while (__builtin_popcount(n) != 1) {
		a.push_back(0);
		n++;	
	}
	tree.resize(2 * n, 0);
	// copy elements 
	for (int i = 0 ; i < n; i++){
		tree[i+n] = a[i];
	}
	// start building nodes
	for (int i = n-1; i >= 1; i--){
		tree[i] = max(tree[2*i] , tree[2*i+1]);
	}

}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;
	vector<ll>a(n);
	for(int i = 0 ; i < n; i++){
		cin >> a[i];
	}	
	build_tree(a);
	ll x;
	for (int i = 0 ; i < q; i++){
		cin >> x;
		/*
		if (tree[1] < x) cout << 0 << "\n";
		else cout << query(1, x) << "\n";
		*/
		cout << query(1,x) << " ";
	}
}
