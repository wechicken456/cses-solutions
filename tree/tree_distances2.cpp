// Sum of distances of every node to all other nodes
// https://cses.fi/problemset/task/1133

// SoD: sum of distances

#include<stdio.h>
#include<vector>
#include<iostream>

#define ll long long 
#define ull unsigned long long 
#define pb push_back

using namespace std;

int n;
vector<vector<int>>adj;

vector<struct Node> tree;

struct Node {
	ull sum = 0;
	int child_cnt = 0;
};

// calculate for each node the SoD from it to its children.
// this is possible by adding all SoD of its children + the number of children because for each child, the distance increases by 1.
void make_tree(int node, int p) {
	
	if (node != 1) {
		if (adj[node].size() == 1) {
			return;
		}
	}
	
	for (int nxt : adj[node]) {
		if (nxt != p) {
			make_tree(nxt, node);
			
			tree[node].sum += tree[nxt].sum;
			tree[node].sum += tree[nxt].child_cnt;
			tree[node].sum += 1;
			tree[node].child_cnt += tree[nxt].child_cnt + 1;
			
		}
	}
	
}

// then calculate SoD for each node from the top to bottom.
// as we go down 1 level, we subtract "the number of children of this current child" from the SoD of the parent as all the paths from the current child's children to the parent are 1 greater than the paths to this current child.
// similarly, the distances from the current child to other children of the parent increases by 1 which is "n - number of children of this current child - 2 (current node and the parent)"
void calc_dist_sum(int node, int p) {
	if (node != 1) {
		tree[node].sum = tree[p].sum + n - 2 - 2*tree[node].child_cnt;
	}
	for (int &nxt : adj[node]) {
		if (nxt != p) {
			calc_dist_sum(nxt, node);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	adj = vector<vector<int>>(n + 1);
	tree = vector<Node>(n + 1);

	for (int i = 0; i < n - 1; i ++) {
		int a , b;
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	make_tree(1, 1);
	calc_dist_sum(1, 1);
	
	for (int i = 1; i <= n; i++) cout << tree[i].sum << " " ;
	return 0;
}
