// Dinic's algorithm
// Police Chase: https://cses.fi/problemset/task/1695

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

struct Edge {
	int v, u;	// from v to u
	ll cap, flow = 0;
	Edge(int v, int u, ll cap) : v(v), u(u), cap(cap) {}
};

const int maxN = 500;
const ll maxX = 1e17;
int n, m,x;
int s, t;	// source and sink

vector<int>level(maxN, 0);	// for level graph
vector<Edge>edges;	// edges are stored by id = order they are added in
vector<int>ptr(maxN, 0);	// pointer for dfs optimization
vector<vector<int>>adj(maxN);

bool bfs() {
	fill(level.begin(), level.end(), -1);
	level[s] = 0;
	queue<int>q;
	q.push(s);
	while(!q.empty()) {
		int v = q.front();
		q.pop();
		for (int &id : adj[v]) {
			
			if (level[edges[id].u] != -1) continue;
			if (edges[id].cap - edges[id].flow <= 0) continue;
	
			// u hasn't been labeled and (v, u) has pos residual capacity
			level[edges[id].u] = level[v] + 1;
			q.push(edges[id].u);
		}
	}
	return level[t] != -1;	// t reachable?
}

// cur_pushed: current flow on the way to t
ll dfs(int v, ll cur_pushed) {
	if (v == t) return cur_pushed;
	
	// pass by reference to increase the pointer
	for (int &i = ptr[v] ; i < adj[v].size(); i++) {
		int id = adj[v][i];
		
		if ( (level[edges[id].u] != level[v] + 1) || (edges[id].cap - edges[id].flow <= 0) ) {
			continue;
		}
		
		ll pushed = dfs(edges[id].u, min(cur_pushed, edges[id].cap - edges[id].flow));
		if (pushed == 0) continue;
		
		// to update both edges at the same time, storing the edges in the chosen data structure is necessary
		edges[id].flow += pushed;
		edges[id ^ 1].flow -= pushed;
		return pushed;
	}
	return 0;
}

// find all nodes reachable in the residual graph AFTER finding max flow
// the set of saturated edges AT this node forms a min cut
// this is because the max flow is the sum of saturated edges.
vector<int>reach(maxN, 0);
void dfs2(int v, int p) {
	for (int i = 0 ; i < adj[v].size(); i++) {
		int id = adj[v][i];
		if (edges[id].u == p) continue;
		if (reach[edges[id].u] == 1) continue;
		
		if (edges[id].cap - edges[id].flow > 0) {
			reach[edges[id].u] = 1;
			dfs2(edges[id].u, v);
		}
	}
}

int main(){
	cin >> n >> m;
	s = 0, t = n - 1;
	
	for (int i = 0 ; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].pb(edges.size());	// which is the current size of `edges`
		adj[b].pb(edges.size() + 1);
		edges.emplace_back(a, b, 1);
		edges.emplace_back(b, a, 1);
	}
	ll max_flow = 0;
	while (bfs()) {
		fill(ptr.begin(), ptr.end(), 0);	// reset pointers
		while (ll cur_pushed = dfs(s, maxX)) {
			max_flow += cur_pushed;
		}
	}
	cout << max_flow << "\n";
	reach[0] = 1;
	dfs2(0, 0);
	for (auto &e : edges) {
		if (reach[e.v]) {
			if (!reach[e.u]) {
				cout << e.v + 1 << " " << e.u + 1 << "\n";
			}
		}
	}
}


