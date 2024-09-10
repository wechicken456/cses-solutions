// Teleporters Path: https://cses.fi/problemset/list/
// https://cp-algorithms.com/graph/euler_path.html
// 


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

const int maxN = 1e5;
const int maxX = 1000;

void solve(){
	int n , m;
	cin >> n >> m;
	vector<int>ans;
	vector<int>st;
	vector<vector<int>>adj(n);
	vector<int>ptr(n, 0);
	vector<int>indeg(n, 0);
	vector<int>outdeg(n, 0);

	for (int i = 0 ; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].pb(b);
		outdeg[a]++;
		indeg[b]++;
	}
	// true if no Eulerian path exists - there are more than 2 vertices with odd degree
	// one of the odd-degree vertices will be the starting and the other will ve the ending point.
	bool bad = false;
	int v1 = -1, v2 = -1;
	for (int i = 0 ; i < n; i++) {
		
		// indeg can ONLY be 1 larger than outdeg for the odd-degree vertices
		if (indeg[i] - 2 >= outdeg[i] || outdeg[i] - 2 >= indeg[i]) {
			bad = true;
			break;
		}
		if (indeg[i] > outdeg[i]) {
			if (v2 == -1) v2 = i;
			else { // case more than 2 odd-indegree vertices
				bad = true;
				break;
			}
		}
		else if (outdeg[i] > indeg[i]) {
			if (v1 == -1) v1 = i;
			else { // case more than 2 odd-outdegree vertices
				bad = true;
				break;
			}
		}
	}
	/*
	// case where there are ONLY 2 odd-degree vertices
	if (v1 != -1 && v2 != -1) {
		if (v1 == 0 && 2 == n - 1){	// add edge to create a cycle, then remove edge in answer later
			adj[n-1].pb(0);
			outdeg[n-1]++;
			indeg[0]++;
			// has to be from n-1 to 0, as indeg == outdeg for an Eulerian circuit/cycle
		}
		else if (v1 == n - 1 && v1 == 0) {
			// has to be from 0 to n-1, as indeg == outdeg for an Eulerian circuit/cycle
			adj[0].pb(n - 1);
			outdeg[0]++;
			indeg[n-1]++;
		}
	}*/
	if (v1 == n - 1 && v2 == 0) {	// an edge from end point to start point
		// this causes 1 to have 1 more incoming edge than outgoing edge which should be impossible
		bad = true;
	}
	if (bad) {
		cout << "IMPOSSIBLE\n";
		return;
	}
	
	st.pb(0);
	while (!st.empty()) {
		int cur = st.back();
		if (outdeg[cur] == 0) {
			ans.pb(cur);
			st.pop_back();
		}
		else {
			int nxt = adj[cur][ptr[cur]];
			st.pb(nxt);
			ptr[cur]++;	// remove that edge from the graph
			outdeg[cur]--;
			indeg[nxt]--;
		}
	}
	
	// check if there are still unvisited edges
	for (int i = 0 ; i < n; i++) {
		if (indeg[i] || outdeg[i]) {
			bad = true;
			break;
		}
	}
	
	// case 1->2->1 is bad as well!
	if (ans[0] != n - 1 || bad) {
		cout << "IMPOSSIBLE\n";
		return ;
	}
	else {
		for (int i = ans.size() - 1; i >= 0 ; i--) {
				cout << ans[i] + 1 << " ";
		}
	}
}

int main(){
	solve();
}


