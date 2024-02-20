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

ll my_floor(ll a, ll b) {
	return (a/b) + ( (a%b)==1 );
}

ll my_ceil(ll a, ll b) {
	return (a/b) + ( (a%b)!=0 );
}

const ll maxN = 1e5;
const ll maxX = 1e9;
int n, m,x, ans = 0;
vector<bool> visited1(maxN + 1), visitedN(maxN + 1);
vector<pair<int,int>>adj1[maxN + 1], adjN[maxN + 1];

const ll max_dist = maxN * maxX + 1;
vector<ll>dist1(maxN + 1, max_dist), distN(maxN + 1, max_dist);

// use ll because of int overflow.
void bfs(int start, vector<pair<int,int>>adj[maxN + 1], vector<bool>&visited, vector<ll>&dist) {
	priority_queue<pair<ll,int>>pq;
	dist[start] = 0;
	pq.push({0, start});
	while (!pq.empty()) {
		pair<ll ,int>t = pq.top();
		pq.pop();
		int parent_node = t.second;
		if (visited[parent_node]) continue;
		visited[parent_node] = true;
		for (auto &c: adj[parent_node]) {
			ll weight = c.first;
			int cur_node = c.second;
			if (dist[parent_node] + weight < dist[cur_node]) {
				dist[cur_node] = dist[parent_node] + weight;
				pq.push({-dist[cur_node], cur_node});
			}
		}
	}
}

// bfs to find shortest distance from 1 to other nodes
// bfs again to find shortest distance from n to other nodes
// then loop through all paths and divide them by 2 to see which is the min.
void solve(){
	cin >> n >> m;
	for (int i = 1,a,b,c; i <= m; i++){
		cin >> a >> b >> c;
		adj1[a].pb({c,b});
		adjN[b].pb({c,a});
	}
	bfs(1, adj1, visited1, dist1);
	bfs(n, adjN, visitedN, distN);
	ll ans = 1e18;
	for (int i = 1; i <= n ; i++){
		for (pair<int, int>p: adj1[i]) {
			int node = p.second, weight = p.first;
			ans = min(ans, dist1[i] + distN[node] + (ll)weight / 2);	// distance from 1 to i + (distance from i to node) / 2 + distance from node to n. 
		}
	}

	cout << ans << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();
}


