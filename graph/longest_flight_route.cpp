#include <bits/stdc++.h>

#define pb push_back
#define vvi vector<vector<int>>
#define vi vector<int>

using namespace std;

int n , m;
vvi adj;
vi dist(100000, 0), visited(100000, 0), prv(100000, 0);

void dfs(int cur) {
	dist[cur] = (cur == n - 1) ? 1 : -10;
	visited[cur] = 1;
	if (cur == n -1 ) return;
	for (int nxt : adj[cur]) {
		if (!visited[nxt]) {
			dfs(nxt);
			//prv[cur] = nxt;
		}
		
		if (dist[nxt] + 1 > dist[cur]) {
			dist[cur] = dist[nxt] + 1;
			prv[cur] = nxt;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> m;
	adj = vvi(n);
	for (int i = 0 ; i < m ;i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		adj[a].pb(b);
	}
	
	dist[n-1] = -1;
	dfs(0);
	if (dist[0] < 0 || dist[n-1] < 0) {
		cout << "IMPOSSIBLE\n";
	}
	else {
		vi ans;
		ans.pb(0);
		int cur = 0;
		while (cur != n-1) {
			cur = prv[cur];
			ans.pb(cur);
		}
		cout << ans.size() << "\n";
		for (int x : ans) {
			cout << x + 1 << " ";
		}
	}
}
