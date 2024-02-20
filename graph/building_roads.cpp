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
int n, m,x;
bool visited[maxN + 1];
vector<int>adj[maxN + 1], ans;

void dfs(int cur){
	if (visited[cur]) return;
	visited[cur] = true;
	// process node cur
	for (auto &c : adj[cur]) {
		dfs(c);
	}
}

void solve(){
	cin >> n >> m;
	for (int i = 1, a, b ; i <= m; i++){
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	for (int i = 1 ; i <= n; i++){		
		if (!visited[i]) {				// if a node is not visited, that means there's no path from the previous node to it, so we need to connect these nodes. => ans increment. 
			dfs(i);
			ans.pb(i);					// does not matter which cities we connect, we can still get to other cities as long as there's a path.
		}
	}
	cout << ans.size() - 1 << "\n";		// if ans = 1 that means there's a path to every city from any starting point.
	for (int i = 1; i < ans.size(); i++){
		cout << ans[0] << " "  << ans[i] << "\n";
	}
}

int main(){
	solve();
}


