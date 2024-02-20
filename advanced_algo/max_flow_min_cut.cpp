// https://cp-algorithms.com/graph/edmonds_karp.html
// https://cses.fi/problemset/result/8167226/


#include<bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vll vector<ll>
#define vvll vector<vector<ll>>
#define vb vector<bool>

#define SET(v, len, val) for (int i = 0 ; i < len; i++) v[i] = val;

using namespace std;

int n, m;
vector<vector<int>>capacity;
vector<vector<int>>adj;
vector<int>par;
vector<vector<int>>ans;

vector<vector<bool>>succ;

int find_flow() {
	SET(par, n, -1);
	par[0] = -2;
	queue<pair<int, int>>q;
	q.push({0, 1e9});
	while (!q.empty()) {
		int node = q.front().first, cur_flow = q.front().second;
		q.pop();
		
		for (int &nxt : adj[node]) {
			if (par[nxt] == -1 && capacity[node][nxt] != 0) {
				par[nxt] = node;
				int next_flow = min(capacity[node][nxt], cur_flow);
				if (nxt == n - 1) {
					return next_flow;
				}
				q.push({nxt, next_flow});
			}
		}
	}
	return 0;
}

// as each edge is only used once, mark it false after each use.
// returns true if there's a path from 0 to n-1 such that each edge is used only ONCE throughout all solutions.
bool dfs(int node) {
	if (node == n-1) return true;
	for (int i = 0 ; i < n ;i++) {
		if (succ[node][i] == true && par[i] == -1) {
			succ[node][i] = false;
			par[i] = node;
			//cout << node + 1<< ":" << i + 1 << ",,";
			if (dfs(i)) return true;
		}
	}
	return false;
}

vector<vector<bool>>isedge;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	
	cin >> n >> m;
	capacity.assign(n, vector<int>(n, 0));
	adj.assign(n, vector<int>());	
	par.resize(n);
	isedge.assign(n, vector<bool>(n, false));	
	succ.assign(n, vector<bool>(n, false));	// mark if an edge is taken in the solution.
	for (int i= 0 ; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;b--;
		adj[a].pb(b);
		adj[b].pb(a);
		isedge[a][b] = true;
		capacity[a][b] = 1;
	}
	
	int new_flow = 0;
	int cnt = 0;
	while ((new_flow = find_flow())) {
		// new_flow is either 1 or 0 in this problem
		int cur = n - 1;
		while (cur != 0) {
			int prev = par[cur];
			capacity[cur][prev] += new_flow; // reverse edge
			capacity[prev][cur] -= new_flow; // edge
			
			if (isedge[prev][cur]) {
				succ[prev][cur] = true;
			}
			else {	// if we're using reverse edge, then the corresponding correct edge is not used
					// because instead of taking the correct edge in the previous rotation (before this augmenting path), we take another edge. 
				succ[cur][prev] = false;
			}
			cur = prev;
		}
		cnt++;
	}
	cout << cnt << "\n";
	SET(par, n, -1);
	par[0] = -2;
	while (dfs(0)) {
		int cur =  n - 1;
		vector<int>v;
		while (cur != 0) {
			v.pb(cur);
			cur = par[cur];
		}
		v.pb(0);
		
		cout << v.size() << "\n";
		for (int i = v.size() - 1; i >= 0; i--) cout << v[i]+1 << " ";
		cout << "\n";
		
		SET(par, n, -1);
		par[0]= -2;
	};

}


