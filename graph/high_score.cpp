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

const int maxN = 2.5e3;
const ll maxX = 2500*1e9+5;
int n, m,x;
vector<bool> visited(maxN + 1);
vector<pair<int,int>>adj[maxN + 1];
vector<ll>dist;
set<int>grey;
set<int>black;
set<int>white;
bool check = false;
int parents[maxN + 1];

void find_cycle(int node, int parent) {
	white.erase(node);
	grey.insert(node);
	
	for (pair<int, int>p : adj[node]) {
		if (white.find(p.first) != white.end()) {
			parents[p.first] = node;
			find_cycle(p.first, node);
		}
		
		if (grey.find(p.first) != grey.end() && (p.first != parent)) {
			check = 1;
			ll sum = 0;
			parents[p.first] = node;
			int next = parents[p.first], bef = p.first;
			
			while (next != p.first) {
				for (pair<int, int> p2 : adj[next]) {
					if (p2.first == bef) {
						sum += p2.second;
						break;
					}
				}
				bef = next;
				next = parents[next];
			}
			for (pair<int, int>p2 : adj[p.first]) {		// now next = p.first (first node in cycle)
				if (p2.first == bef) {
					sum += p2.second;
					break;
				}
			}
			if (sum > 0) {
				cout << -1;
				exit(0);
			}
		}
	}
	grey.erase(node);
	black.insert(node);
}

void solve(){
	cin >> n >> m;
	dist = vector<ll>(n + 1, -maxX);
	for (int i = 1 , a, b , l; i <= m ; i++){
		cin >> a >> b >> l;
		adj[a].pb({b, l});					// note that in this problem l is the one-way distance from a to b.
	}
	for (int i = 1 ; i <= n; i ++){
		white.insert(i);
	}
	find_cycle(1, 1);
	// find shortest path using Dijkstra's algorithm
	priority_queue<pair<ll,int>>q; 		// default sort by first element in pairs
	dist[1] = 0;
	q.push({0, 1});
	while (!q.empty()) {
		pair<ll,int> cur_top = q.top();
		q.pop();
		int parent_node = cur_top.second;
		if (visited[parent_node]) continue;
		visited[parent_node] = true;
		for (auto &cur : adj[parent_node]) {
			ll weight = cur.second, cur_node = cur.first;
			if (dist[parent_node] + weight > dist[cur_node]) {
				dist[cur_node] = dist[parent_node] + weight;
				q.push({dist[cur_node], cur_node});
			}
		}
	}
	cout << dist[n];
}

int main(){
	solve();
}


