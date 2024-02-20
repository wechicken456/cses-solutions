#include<bits/stdc++.h>
#include<set>
#include<stdio.h>
#include<vector>
#include<map>
#include<iterator>
#include<algorithm>
#include<math.h>
#include<cmath>
#include<fstream>

#define ll long long
#define ull unsigned long long
#define pb push_back

using namespace std;

ull power(ll x, ull y) {
    if (y == 0)
        return 1;
    else if (y % 2 == 0)
        return power(x, y / 2) * power(x, y / 2);
    else
        return x * power(x, y / 2) * power(x, y / 2);
}
 
ll my_ceil(ll a, ll b) {
	return (a/b) + ( (a%b)!=0 );
}

const int maxN = 1e3;
int n, m,x;
bool visited[maxN + 3][maxN + 3];
void solve(){
	cin >> n >> m;
	char x;
	pair<int, int>start;
	pair<int, int>end;
	vector<vector<int>>grid(n+2, vector<int>(m+2));
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m ; j++){
			cin >> x;
			if (x == '.') {
				grid[i][j] = 1;
				//add_adj(i,j);
			}
			if (x == 'A') { 
				grid[i][j] = 1;
				start.first = i;
				start.second = j;
			}
			if (x == 'B') {
				grid[i][j] = 1;
				end.first = i;
				end.second = j;
			}
		}
	}
	bool check = false;
	queue<pair<int,int>>q;
	vector<vector<pair<int,int>>>ans(n+2, vector<pair<int,int>>(m+2));
	map<pair<int,int>, char>compass;
	compass[make_pair(0,1)] = 'R';
	compass[make_pair(0, -1)] = 'L';
	compass[make_pair(1,0)] = 'D';
	compass[make_pair(-1,0)] = 'U';
	vector<pair<int,int>>dir = {{0, 1}, {0, -1}, {1,0}, {-1,0}};
	q.push(start);
	while (!q.empty()) {
		pair<int,int> top = q.front();
		q.pop();
		int root_row = top.first, root_col = top.second;
		if (root_row == end.first && root_col == end.second) {
			check = true;
			break;
		}
		for (pair<int,int>p : dir) {
			int new_row = root_row + p.first, new_col = root_col + p.second;
			if (new_row < 0 || new_row > n || new_col < 0 || new_col > m) continue;
			if (grid[new_row][new_col] == 0) continue;
			if (visited[new_row][new_col]) continue;
			visited[new_row][new_col] = true;
			
			ans[new_row][new_col] = p;						// the step we took
			q.push({new_row, new_col});
		}
	}
	if (!check) cout << "NO" << "\n";
	else {
		cout << "YES" << "\n";
		string res;
		int row = end.first, col = end.second;
		while (row != start.first || col != start.second) {
			char c = compass[ans[row][col]];
			res.pb(c);
			int new_row = row - ans[row][col].first;		// go back to the "parent cell"
			int new_col = col - ans[row][col].second;
			row = new_row;
			col = new_col;
		}
		cout << res.size() << "\n";
		for (int i = res.size()-1; i >= 0; i--){
			cout << res[i];
		}
	}
}	

int main(){
	solve();
}


