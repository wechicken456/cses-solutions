#include<stdio.h>
#include<vector>
#include<iostream>

#define ll long long 
#define ull unsigned long long 
#define pb push_back

using namespace std;

int n;
vector<vector<int>>adj;
vector<vector<int>>children;
vector<int>ans;
vector<struct maxLength> longest_path;

struct maxLength {
	int toLeaf1;
	int toLeaf2;
	int max_child;
};

void make_tree(int node, int p) {
	for (int nxt : adj[node]) {
		if (nxt != p) {
			children[node].pb(nxt);
			make_tree(nxt, node);
		}
	}
	
}


int calc_to_leaf(int node) {
	for (int nxt : children[node]) {
		int tmp = calc_to_leaf(nxt) + 1;
		if (tmp > longest_path[node].toLeaf1) {
			longest_path[node].toLeaf2 = max(longest_path[node].toLeaf2, longest_path[node].toLeaf1);
			longest_path[node].toLeaf1 = tmp;
			longest_path[node].max_child = nxt;
		}
		else {
			longest_path[node].toLeaf2 = max(longest_path[node].toLeaf2, tmp);
		}
	}
	if (children[node].size() == 0) {
		longest_path[node].max_child = node;
		return 0;
	}
	return longest_path[node].toLeaf1;
}

void calc_longest_path(int node, int p) {
	if (node != 1) {
		if (longest_path[p].max_child == node) {
			if (longest_path[p].toLeaf2 + 1 > longest_path[node].toLeaf2) {
				longest_path[node].toLeaf2 = longest_path[p].toLeaf2 + 1; 
			}
			if (longest_path[node].toLeaf2 > longest_path[node].toLeaf1) {
				//longest_path[node].toLeaf1 = longest_path[node].toLeaf1 + longest_path[node].toLeaf2;
				//longest_path[node].toLeaf2 = longest_path[node].toLeaf1 - longest_path[node].toLeaf2;
				//longest_path[node].toLeaf1 = longest_path[node].toLeaf1 - longest_path[node].toLeaf2; 
				swap(longest_path[node].toLeaf2 , longest_path[node].toLeaf1);
				longest_path[node].max_child = p;
			}
		}
		else {
			if (longest_path[p].toLeaf1 + 1 > longest_path[node].toLeaf2) {
				longest_path[node].toLeaf2 = longest_path[p].toLeaf1 + 1; 
			}
			if (longest_path[node].toLeaf2 > longest_path[node].toLeaf1) {
				//longest_path[node].toLeaf1 = longest_path[node].toLeaf1 + longest_path[node].toLeaf2;
				//longest_path[node].toLeaf2 = longest_path[node].toLeaf1 - longest_path[node].toLeaf2;
				//longest_path[node].toLeaf1 = longest_path[node].toLeaf1 - longest_path[node].toLeaf2; 
				swap(longest_path[node].toLeaf2 , longest_path[node].toLeaf1);
				longest_path[node].max_child = p;
			}
		}
		ans[node] = max(longest_path[node].toLeaf1, longest_path[node].toLeaf2);

	}
	for (int i : children[node]) {
		calc_longest_path(i, node);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	adj = vector<vector<int>>(n + 1);
	children = vector<vector<int>>(n + 1);
	ans = vector<int>(n + 1);
	longest_path = vector<struct maxLength>( n + 1);
	for (int i = 0; i < n - 1; i ++) {
		int a , b;
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	make_tree(1, 1);
	calc_to_leaf(1);
	
	cout << longest_path[1].toLeaf1 << " ";
	calc_longest_path(1, 1);
	
	for (int i = 2; i <= n; i++) cout << ans[i] << " " ;
	return 0;
}
