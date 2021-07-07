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
int n, m,x, start;
int visited[maxN + 1];
vector<int>adj[maxN + 1];
bool check = true;

void dfs(int cur, int start){
	if (visited[cur] && (visited[cur] % 2 != start % 2)) {		// same parity can be in the same team. if the cur pupil is visited and its parity != to the current parity, that means it belongs to both teams so it is impossible to form teams. 
		check = false;
		return;
	}
	else if (visited[cur] || check == false) return;
	visited[cur] = start;
	// process node cur
	
	for (auto &c : adj[cur]) {
		dfs(c, start + 1);
	}
}

void solve(){
	cin >> n >> m;
	for (int i = 0,a,b; i < m ; i++){
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
	}	
	for (int i = 1; i <= n ; i++){
		if (!visited[i]) {
			start = 0;		// set parity to 0;
			dfs(i, start);
		}
	}
	if (!check) cout << "IMPOSSIBLE\n";
	else {
		for (int i = 1; i <= n ; i++){
			if (visited[i] % 2 == 1)  cout << 1;
			else cout << 2;
			cout << " ";
		}
	}
}

int main(){
	solve();
}


