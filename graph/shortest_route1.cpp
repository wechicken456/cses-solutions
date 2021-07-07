#include<bits/stdc++.h>
#include<climits>
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

ull power(ull x, ull y) {
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

const int maxN = 1e5;
const int maxX = 1e9+1;
int n, m,x;
bool visited[maxN + 1];
vector<pair<int,int>>adj[maxN + 1];
vector<ull>dist;

void solve(){
	cin >> n >> m;
	dist = vector<ull>(n + 1);
	fill(dist.begin(), dist.end(), ULLONG_MAX); 		// don't wanna fill with INFINITY so fill with this instead
	for (int i = 1 , a, b , l; i <= m ; i++){
		cin >> a >> b >> l;
		adj[a].pb({b, l});					// note that in this problem l is the one-way distance from a to b.
	}
	// find shortest path using Dijkstra's algorithm
	priority_queue<pair<ull,int>>q; 		// default sort by first element in pairs
	dist[1] = 0;
	q.push({0, 1});
	while (!q.empty()) {
		pair<ull,int> cur_top = q.top();
		q.pop();
		ull parent_node = cur_top.second;
		if (visited[parent_node]) continue;
		visited[parent_node] = true;
		for (auto &cur : adj[parent_node]) {
			ull weight = cur.second, cur_node = cur.first;
			if (dist[parent_node] + weight < dist[cur_node]) {
				dist[cur_node] = dist[parent_node] + weight;
				q.push({-dist[cur_node], cur_node});
			}
		}
	}
	for (int i = 1; i <= n; i++) cout << dist[i] << " " ;
}

int main(){
	solve();
}


