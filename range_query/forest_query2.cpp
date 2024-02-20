
// solvded using 2-dimensional segment tree

#include<bits/stdc++.h>
#include<iostream>

using namespace std;

#define ll long long
#define pb push_back

int n , q;
vector<vector<int>>tree;

int query_col(int node_row, int node_col, int col_start, int col_end, int q_col_start, int q_col_end) {
	if (col_start >= q_col_start && col_end <= q_col_end) {
		//cout << node_row << " " << node_col << "\n";
		return tree[node_row][node_col];
	}
	if (col_start > q_col_end || col_end < q_col_start) {
		return 0;
	}
	
	int middle = (col_start + col_end) / 2;
	return query_col(node_row, node_col * 2, col_start, middle, q_col_start, q_col_end) 
		 + query_col(node_row, node_col * 2 + 1, middle + 1, col_end, q_col_start, q_col_end);
}

int query_row(int node_row, int row_start, int row_end, int q_row_start, int q_row_end, int q_col_start, int q_col_end) {
	if ( row_start >= q_row_start && row_end <= q_row_end ) {
		return query_col(node_row, 1, 1, n, q_col_start, q_col_end);
	} 
	
	if (row_start > q_row_end || row_end < q_row_start) {
		return 0;
	}
	
	int middle = (row_start + row_end) / 2;
	return query_row(node_row * 2, row_start, middle, q_row_start, q_row_end, q_col_start, q_col_end)
		 + query_row(node_row * 2 + 1, middle + 1, row_end, q_row_start, q_row_end, q_col_start, q_col_end);
	
}

void build_tree() {
	
	// build the base tree (the lowest level in the mother tree)
	for (int i = 0 ; i < n; i++) {
		for (int j = n - 1; j >= 1 ; j--) {
			tree[i + n][j] = tree[i + n][2*j] + tree[i + n][2*j + 1];
		}
	}
	
	for (int i = n - 1; i >= 1; i--) {
		// build the base row (leaves) in each tree
		for (int j = 2*n - 1; j >= n ; j--) {
			tree[i][j] = tree[2*i][j] + tree[2*i +1][j];
		}
		// then build each tree
		for (int j = n - 1; j >= 1; j--) {
			tree[i][j] = tree[i][2*j] + tree[i][2*j + 1];
		}
	}
	
}

void update(int row, int col) {
	int sign = (tree[row][col] == 1 ? -1 : 1);
	for (int i = row; i > 0 ; i /= 2) {
		for (int j = col; j > 0 ; j /= 2) {
			tree[i][j] += sign;
		}
	}
}

int main () {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> q;
	int old_n = n;
	while (__builtin_popcount(n) != 1) {
		n++;
	}
	
	tree = vector<vector<int>>(2*n, vector<int>(2*n, 0));
	for (int i = 0 ; i < old_n; i ++) {
		for (int j = 0 ; j < old_n; j++) {
			char c;
			cin >> c;
			if (c == '*') {
				tree[i + n][j + n] = 1;
			}
		}
	}
	
	build_tree();
	
	// TODO: print_query and update_tree
	for (int i = 0 ; i < q; i++) {
		int a;
		cin >> a;
		if (a == 1) {
			int row, col;
			cin >> row >> col;
			update(row - 1 + n, col - 1 + n);
		}
		else {
			int row_start, row_end, col_start, col_end;
			cin >> row_start >> col_start >> row_end >> col_end;
			cout << query_row(1, 1, n, row_start, row_end, col_start, col_end) << "\n";
		}
		
	}
	
}

