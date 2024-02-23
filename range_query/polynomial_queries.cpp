#include<bits/stdc++.h>
#include<vector>

using namespace std;

#define ll long long
#define pb push_back

struct tree_node {
	ll sum;
	ll z1, z0;	
/*
Intuition: for a query (l1, r1), that covers our node, then the increase for each element is: 

(index) l1   l1 + 1                  l 			...	     r 	
(inc)   1       2     + ... +    l - l1 + 1     ...  r - l1 + 1

then the increase in sum can be decomposed into:
how far we are from l1 + (1 + 2 + ... + r - l + 1)
Example: (l1, r1) = (2, 9). (l, r) = (5, 8).
by the time we reach index 5, the increase for the 5-th element is 5 -2 + 1 = 4.
inc(6-th element)=5
inc(7-th element)=6
inc(8-th element)=7

=> increase in sum for our node = 4 + 5 + 6 + 7 = 
* 								= (3 + 1) + (3 + 2) + (3 + 3) + (3 + 4)
* 								= 3*4 + (1+2+3+4)
* 

So say we have some increase queries denoted as (l1, r1), (l2, r2), ... (lk, rk) that COVERS our node
Then, let our node's range be (l, r), the increase in sum for our node is:

  (l - l1) + (l - l1 + 1) + ... + (l - l1 + r - l + 1)	(there are r - l + 1 terms)
+ (l - l2) + (l - l2 + 1) + ... + (r - l2 + 1)
...
+ (l - lk) + (l - lk + 1) + ... + (r - lk + 1)

= (r - l + 1) * (l - l1) + (1 + 2 + ... + r - l + 1)
+ (r - l + 1) * (l - l2) + (1 + 2 + ... + r - l + 1)
...
+ (r - l + 1) * (l - lk) + (1 + 2 + ... + r - l + 1)

= (r - l + 1) * ( (l - l1) + (l - l2) + ... + (l - lk) ) + k*(r -l + 1)*(r - l + 2) / 2

=> z1 = k
=> z0 = (l - l1) + (l - l2) + ... + (l - lk) 

Now if the queries don't entirely covers the node's range but overlap the node's range.
Then, the increase in sum for an overlap into the RIGHT of a query range is :
	1. the previous update using the method above: sum += z0*(r - l + 1) + k*(r -l + 1)*(r - l + 2) / 2
	2. the current update: how far we are from the LEFT of the query * range(node) + (1 + 2 + ... + range(node)).
							= (l - l1)*(r - l + 1) + 1*(r - l + 1)*(r - l + 2) / 2


Then, to propagate the update to the LEFT child, we pass `z1` and `z0` to it. 
This works because the LEFT of the child is also the LEFT of the current node, 
so the distances to the LEFT of the previous queries are the same.

To propagate the update to the RIGHt child, we use the same strategy, 
except that the distances to the LEFT of the previous queries (`z0`) are INCREASED by `(r - l + 1)/2`
Finally, we set `z0 = z1 = 0` for the current node.
*/
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
	tree[node].z1 += z1;	// receive update from parent 
	tree[node].z0 += z0;	// receive udpate from parent
	if (node_l > query_h || node_h < query_l) {		// query completely outside node
		return 0;
	}
	else if (node_l >= query_l && node_h <= query_h) {	// query completely covers node
		// if its an increase query
		if (q_type == 1) {
			tree[node].z1 += 1;
			tree[node].z0 += node_l - query_l;
		} 
		return tree[node].sum + polynomial_update(1, tree[node].z1, node_h - node_l + 1) + polynomial_update(0, tree[node].z0, node_h - node_l + 1);
	}
	
	ll middle = (node_l + node_h) / 2;
	// update sum from previous lazy updates
	tree[node].sum += polynomial_update(1, tree[node].z1, node_h - node_l + 1) + polynomial_update(0, tree[node].z0, node_h - node_l + 1);

	if (q_type == 1){	// an increase query, then update sum first so we can propagate updates to children
		ll intersection = min(node_h, query_h) - max(node_l, query_l) + 1;
		if (query_l <= node_l) {
			tree[node].sum += polynomial_update(0, node_l - query_l, intersection) + polynomial_update(1, 1, intersection);
		}
		else {
			tree[node].sum += polynomial_update(1, 1, intersection);
		}
	}

	ll tmp_z1 = tree[node].z1, tmp_z0 = tree[node].z0, tmp_z0_2 = 0;
	if (tmp_z0 > 0 || tmp_z1 > 0 ) {
		tmp_z0_2 = tmp_z0 + tmp_z1*(node_h - node_l + 1) / 2;	// right child's increase in `z0`
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


