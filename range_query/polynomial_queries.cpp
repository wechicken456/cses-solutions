#include<bits/stdc++.h>
#include<vector>

using namespace std;

#define ll long long
#define pb push_back

struct tree_node {
	ll sum;
	ll z1, z0;
};

ll n ,q ;
vector<tree_node>tree;
vector<ll>a;

void build_tree() {
	for (ll i = 0 ; i < n; i++) {
		tree[i + n].sum = a[i];
		tree[i + n].z1 = tree[i+n].z0 = 0;
	}
	
	for (ll i = n-1 ; i > 0; i--) {
		tree[i].sum = tree[2*i].sum + tree[2*i + 1].sum;
		tree[i].z1 = tree[i].z0 = 0;
	}
}

ll polynomial_update(ll degree, ll coef, ll range) {
	if (degree == 0) {
		return range*coef;
	}
	else {
		return (coef*range*(range + 1)) / 2;
	}
}

ll increase(ll node, ll node_l, ll node_h, ll query_l, ll query_h, ll z1, ll z0, ll q_type) {
	tree[node].z1 += z1;
	tree[node].z0 += z0;
	if (node_l > query_h || node_h < query_l) {
		return 0;
	}
	else if (node_l >= query_l && node_h <= query_h) {
		// if its an increase query, otherwise its a prll query
		if (q_type == 1) {
			tree[node].z1 += 1;
			tree[node].z0 += node_l - query_l;
		} 
		//cout << node << " = " << node_l << ":" << node_h << " " << tree[node].sum << " " << tree[node].z1 << " " << tree[node].z0 << "\n";
		return tree[node].sum + polynomial_update(1, tree[node].z1, node_h - node_l + 1) + polynomial_update(0, tree[node].z0, node_h - node_l + 1);
	}
	
	ll middle = (node_l + node_h) / 2;
	tree[node].sum += polynomial_update(1, tree[node].z1, node_h - node_l + 1) + polynomial_update(0, tree[node].z0, node_h - node_l + 1);

	if (q_type == 1){
		ll llersection = min(node_h, query_h) - max(node_l, query_l) + 1;
		if (query_l <= node_l) {
			tree[node].sum += polynomial_update(0, node_l - query_l, llersection) + polynomial_update(1, 1, llersection);
		}
		else {
			tree[node].sum += polynomial_update(1, 1, llersection);
		}
	}
	//cout << node << " = " << tree[node].sum << " " << tree[node].z1 << " " << tree[node].z0 << "\n";

	ll tmp_z1 = tree[node].z1, tmp_z0 = tree[node].z0, tmp_z0_2 = 0;
	if (tmp_z0 > 0 || tmp_z1 > 0 ) {
		tmp_z0_2 = tmp_z0 + tmp_z1*(node_h - node_l + 1) / 2;
	}
	tree[node].z1 = 0;
	tree[node].z0 = 0;
	return  increase(2*node, node_l, middle, query_l, query_h, tmp_z1, tmp_z0, q_type) 
		 +  increase(2*node + 1, middle + 1, node_h, query_l, query_h, tmp_z1, tmp_z0_2, q_type);
	
	
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> q;
	a = vector<ll>(n);
	for (ll i= 0 ;i < n;i ++) {
		cin >> a[i];
	}
	while (__builtin_popcount(n) != 1) {
		a.pb(0);
		n++;
	}
	
	tree.resize(2*n);
	build_tree();
	
	for (ll i = 0 ; i < q; i++) {
		/*
for (ll b= 0 ; b< n; b++) {
	cout << b << " = " << tree[b].sum << " " << tree[b].z1 << " " << tree[b].z0 << "\n";
}
cout << "----------------\n";
for (ll b= n; b < 2*n; b++) {
	cout << b << " = " << tree[b].sum << " " << tree[b].z1 << " " << tree[b].z0 << "\n";
}
cout << "******************\n\n";
*/
		//cout << "--------------------\n";
		ll c, l , h;
		cin >> c >> l >> h; 
		l--; h--;
		if (c == 1) {
			increase(1, 0, n - 1, l , h, 0, 0, 1);
		}
		else {
			cout << increase(1, 0, n - 1, l , h, 0, 0, 2) << "\n";
		}
	}
}


