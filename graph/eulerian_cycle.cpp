// Mail Delivery: https://cses.fi/problemset/task/1691
// https://cp-algorithms.com/graph/euler_path.html


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


void solve(){
	int n , m;
	cin >> n >> m;
	vector<int>ans;
	vector<int>st;
	vector<vector<int>>adj(n);
	vector<int>ptr(n, 0);
	vector<int>deg(n, 0);

	for (int i = 0 ; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].pb(b);
		adj[b].pb(a);
		deg[a]++;
		deg[b]++;
	}
	// true if no Eulerian cycle exists - there are vertices with odd degree
	// one of the odd-degree vertices will be the starting and the other will ve the ending point.
	bool bad = false;
	for (int i = 0 ; i < n; i++) {
		if (deg[i] & 1) {
			bad = true;
		}
	}
	
	if (bad) {
		cout << "IMPOSSIBLE\n";
		return;
	}
	
	map<pair<int, int>, bool>taken;
	st.pb(0);
	while (!st.empty()) {
		int cur = st.back();
		if (deg[cur] == 0) {
			ans.pb(cur);
			st.pop_back();
		}
		else {
			int nxt;
			do  {
				nxt = adj[cur].back();
				adj[cur].pop_back();
			} while (taken[{cur, nxt}]);
			
			st.pb(nxt);
			deg[cur]--;
			deg[nxt]--;
			taken[{nxt, cur}] = true;	// mark the reversed edge as taken
		}
	}
	
	// check if there are still unvisited edges
	for (int i = 0 ; i < n; i++) {
		if (deg[i]) {
			bad = true;
			break;
		}
	}
	
	// make sure endpoint = starting point
	if (ans[0] != 0 || bad) {
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


