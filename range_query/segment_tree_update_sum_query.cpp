#include<vector>
#include<bits/stdc++.h>

#define ll long long

using namespace std;
vector<ll>tree;

int n,q;

ll dum(int node, int node_low, int node_high, int query_low, int query_high){
	if (node_low >= query_low && node_high <= query_high) {
		return tree[node];
	}
	if(node_low > query_high || node_high < query_low) {
		return 0;
	}
	int middle = (node_low + node_high)/2;
	return sum(2 * node, node_low, middle, query_low, query_high) 		// left child
		 + sum(2 * node + 1, middle + 1, node_high, query_low, query_high);	// right child
}

void build_tree(vector<ll>a) {
	// pad with 0 to make power of 2
	while (__builtin_popcount(n) != 1) {
		a.push_back(0);
		n++;
	}
	tree.resize(2 * n);
	// copy elements 
	for (int i = 0 ; i < n; i++){
		tree[i+n] = a[i];
	}
	// start building nodes
	for (int i = n-1; i >= 1; i--){
		tree[i] = tree[2*i] + tree[2*i+1];
	}

}

// recursive style, can apply to all problems
void update(int node, int node_low, int node_high, int query_low, int query_high, ll value) {
	if (node_low == node_high && node_low == query_low) { // only happens if node is a leaf
		tree[node] = value;
		return;
	}
	if (node_low > query_high || node_high < query_low) return;
	int middle = (node_low + node_high)/2;
	update(2 * node, node_low, middle, query_low, query_high, value);			// update left child if needed
	update(2 * node+1 , middle + 1, node_high, query_low, query_high, value);	// update right child if needed
	tree[node] = tree[2*node] + tree[2*node + 1];						// update parent after updating children
}

/*
void update(int pos, ll value){ 	// O(log n). Iterative style, cannot apply to all problem
	ll diff = value - tree[pos];
	while (pos > 0){
		tree[pos] += diff;	
		pos /= 2;
	}
}
*/

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;
	vector<ll>a(n);
	for(int i = 0 ; i < n; i++){
		cin >> a[i];
	}	
	build_tree(a);

	for (int i = 0 ; i < q; i++){
		int type;
		cin >> type; 
		if (type == 2) {
			int low, high;
			cin >> low >> high;
			low--; high--;
			cout << sum(1, 0, n-1, low, high) << "\n";
		}
		else {
			int pos;
			ll value;
			cin >> pos >> value;
			pos--;
			//update(pos + n, value);
			update(1, 0, n-1, pos, pos, value);
		}	
	}
}
