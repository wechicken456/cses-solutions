#include<vector>
#include<bits/stdc++.h>

#define ll long long

using namespace std;
vector<vector<int>>tree;
vector<vector<int>>grid;
int n,q;
/*						SLOW SOLUTION USING SEGMENT TREE
int new_n;
int sum(int node, int node_low, int node_high, int row_low, int row_high, int query_low, int query_high){
	if (node_low >= query_low && node_high <= query_high) {
		int all = 0;
		for (int i = row_low; i <= row_high; i++){
			all += tree[i][node];
		}
		return all;
	}
	if(node_low > query_high || node_high < query_low) {
		return 0;
	}
	int middle = (node_low + node_high)/2;
	return sum(2 * node, node_low, middle, row_low, row_high, query_low, query_high) 		// left child
		 + sum(2 * node + 1, middle + 1, node_high, row_low, row_high, query_low, query_high);	// right child
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	char x;
	cin >> n >> q;
	new_n = n;
	vector<vector<int>>a = vector<vector<int>>(n, vector<int>(n,0));
	
	// pad with 0 to make power of 2
	while (__builtin_popcount(new_n) != 1) {
		new_n++;
	}

	tree = vector<vector<int>>(n, vector<int>(2 * new_n, 0));
	for(int i = 0 ; i < n; i++){
		for (int j = 0 ; j < n; j++) {
			cin >> x;
			if (x == '*') tree[i][j + new_n] = 1;
			//else a[i][j] = 0;
		}
		for (int j = new_n - 1; j >= 1; j--){
			tree[i][j] = tree[i][2*j] + tree[i][2*j+1];
		}
	}	
	for (int i = 0 ; i < q; i++){	
		int row_low, row_high, col_low, col_high, ans = 0;
		cin >> row_low >> col_low >> row_high >> col_high;
		row_low--; col_low--; row_high--; col_high--;
		ans = sum(1, 0, new_n-1, row_low, row_high, col_low, col_high);
		cout << ans << "\n";
	}
}
*/

// 				FAST SOLUTION USING DP. grid[i][j] denotes number of trees from [1,1] to [i,j]. 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	char x;
	cin >> n >> q;
	grid = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <=n; j++) {
			cin >> x;
			grid[i][j] = grid[i][j-1] + grid[i-1][j] - grid[i-1][j-1] + (x == '*'); // rectangle to the left + rectangle to the top - rectangle on top left corner.
		}
	}
	for (int i = 0 ; i < q; i++){
		int r_low, r_high, c_low, c_high;
		cin >> r_low >> c_low >> r_high >> c_high;
		int ans = grid[r_high][c_high] - grid[r_high][c_low-1] - grid[r_low-1][c_high] + grid[r_low-1][c_low-1];
		cout << ans << "\n";
	}
}
