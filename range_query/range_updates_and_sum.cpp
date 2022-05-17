#include<bits/stdc++.h>
#include<vector>
#include<tuple>
#include<queue>

using namespace std;

#define ll long long
#define pb push_back

ll n,q;
vector<tuple<ll , ll, ll>>tree;
vector<ll>a;

// return the value of the current node after lazy update. lazy update means we only stop processing when the current range is completely inside the query range
ll increase(ll node, ll node_l, ll node_h, ll query_l, ll query_h, ll val, ll prev_inc, ll prev_all) {
	// lazy update 
	if (prev_all > 0) {
		get<0>(tree[node]) = prev_all*(node_h - node_l + 1) ;
		get<1>(tree[node]) = prev_inc;
		get<2>(tree[node]) = prev_all;
	}
	else get<1>(tree[node]) += prev_inc;
	if (node_l >= query_l && node_h <= query_h) {
		get<1>(tree[node]) += val;
		// if its a leaf
		if (node_l == node_h) {
			get<0>(tree[node]) += get<1>(tree[node]);
			get<1>(tree[node]) = 0;
			get<2>(tree[node]) = 0;
		}
		
		return get<0>(tree[node]) + get<1>(tree[node])*(node_h - node_l + 1);
	}
	else if (node_l > query_h || node_h < query_l) return 0;

	// since we have to go down (because the previous "if" statement made sure there is an intersection between the node range and the query), we lazy-update this node
	ll tmp_inc = get<1>(tree[node]);
	ll tmp_all = get<2>(tree[node]);
	
	// intersection size between the node range and the query range
	ll intersection = min(node_h, query_h) - max(node_l, query_l) + 1;
	get<0>(tree[node]) += tmp_inc*(node_h - node_l + 1) + val*intersection;
	get<1>(tree[node]) = 0;
	get<2>(tree[node]) = 0;

	ll middle = (node_l + node_h) / 2;
	return increase(2 * node, node_l, middle, query_l, query_h, val, tmp_inc, tmp_all)
	    +  increase(2 * node + 1, middle + 1, node_h, query_l, query_h, val, tmp_inc, tmp_all);

}

// 3rd value = value of all leaves in current range
// every time we have to go down to children of this node, we lazy-update this parent node then pass the lazy update values down to them
ll update_range(ll node, ll node_l, ll node_h, ll query_l, ll query_h, ll val, ll prev_inc, ll prev_all) {
	// process lazy updates first
	if (prev_all > 0) {
		get<0>(tree[node]) = prev_all*(node_h - node_l + 1) ;
		get<1>(tree[node]) = prev_inc;
		get<2>(tree[node]) = prev_all;
	}
	else get<1>(tree[node]) += prev_inc;
	if (node_l > query_h || node_h < query_l) {
		return 0;
	}
	else if (node_l >= query_l && node_h <= query_h) {
		
		//  process current query
		ll diff = val*(node_h - node_l + 1) - get<0>(tree[node]) - get<1>(tree[node])*(node_h - node_l + 1);
		get<0>(tree[node]) = val*(node_h - node_l + 1);
		get<1>(tree[node]) = 0;
		get<2>(tree[node]) = val;
		return diff;
	}
	
	// since we have to go down (because the previous "if" statement made sure there is an intersection between the node range and the query), we lazy-update this node
	ll tmp_inc = get<1>(tree[node]);
	ll tmp_all = get<2>(tree[node]);
	
	get<1>(tree[node]) = 0;
	get<2>(tree[node]) = 0;
	
	ll middle = (node_h + node_l) / 2;
	ll diff = update_range(2 * node, node_l, middle, query_l, query_h, val, tmp_inc, tmp_all)
	    +  update_range(2 * node + 1, middle + 1, node_h, query_l, query_h, val, tmp_inc, tmp_all);
	get<0>(tree[node]) += tmp_inc*(node_h - node_l + 1) + diff;
	return diff;
}

int main() {
	
	scanf("%lld %lld", &n, &q);
	a = vector<ll>(n);
	for(ll i = 0 ; i < n; i++){
		scanf("%lld", &a[i]);
	}
	while (__builtin_popcount(n) != 1) {
		a.pb(0);
		n++;
	}
	tree.resize(2*n);
	for (ll i = 0 ; i < n; i++) {
		tree[i + n] = make_tuple(a[i], 0 , 0);
	}
	for (ll i = n-1 ; i > 0 ; i--) {
		tree[i] = make_tuple(get<0>(tree[2*i]) + get<0>(tree[2*i + 1]), 0, 0);
	}
	
	
	
	for (ll t = 0; t < q; t++){
		/*for (ll i = 0 ; i < n; i++) {
			cout << get<0>(tree[i]) << " "<< get<1>(tree[i]) << " "<< get<2>(tree[i]) << "\n";
		}
		cout << "------------------\n";
		for (ll i = n ; i < 2*n; i++) {
			cout << get<0>(tree[i]) << " "<< get<1>(tree[i]) << " "<< get<2>(tree[i]) << "\n"; 
		}
		cout << "xxxxxxxxxxxxxxxx\n";*/
		ll choice;
		scanf("%lld", &choice);
		if (choice == 1) {
			ll l , h, x;
			scanf("%lld %lld %lld", &l, &h, &x);
			l--; h--;
			increase(1, 0, n - 1, l, h, x, 0, 0);
		}
		else if (choice == 2) {
			ll l, h,  x;
			scanf("%lld %lld %lld", &l, &h, &x);
			l--; h--;
			update_range(1, 0, n - 1, l, h , x, 0, 0);
		}
		else {
			ll l, h;
			scanf("%lld %lld", &l, &h);
			l--; h--;
			printf("%lld\n", increase(1, 0, n - 1, l, h, 0, 0, 0));
		}
	}
	
}

/* DEBUG TREE
for (ll i = 0 ; i < n; i++) {
	cout << get<0>(tree[i]) << " "<< get<1>(tree[i]) << " "<< get<2>(tree[i]) << "\n";
}
cout << "------------------\n";
for (ll i = n ; i < 2*n; i++) {
	cout << get<0>(tree[i]) << " "<< get<1>(tree[i]) << " "<< get<2>(tree[i]) << "\n"; 
}
*/

