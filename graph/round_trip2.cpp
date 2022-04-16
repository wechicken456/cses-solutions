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
#include<chrono>

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

const int maxN = 1e5 + 1;
const int maxX = 1000;
int n, m;
vector<bool>visited(maxN + 1);
vector<int>adj[maxN + 1];
vector<int>parents(maxN + 1);
vector<int>visited_after;
int start, city_num;

void dfs(int cur, int parent) {
	if (visited[cur]) {
		vector<int>ans;
		int start = cur;
		int next = parents[cur];
		ans.pb(cur);
		while (next != start) {			// just keep following parent nodes to where we first started (root node). 
			ans.pb(next);
			next = parents[next];
		}
		printf("%d\n", ans.size() + 1);

		printf("%d ", start);
		for (int i = ans.size() - 1; i >= 0 ; i--) printf("%d ", ans[i]);	
		exit(0);
	}
	visited[cur] = true;
	visited_after.pb(cur);
	for (auto &c : adj[cur]) {
		parents[c] = cur;				// keep track of where we're from 
		dfs(c, cur);
		visited[c] = false;
	}	
}

// this problem is all about finding if there's any cycle in the graph.
void solve(){
	scanf("%d %d", &n, &m);
	for (int i = 1 , a, b; i <= m ; i++){
		scanf("%d %d", &a, &b);
		adj[a].pb(b);
	}
	for (int i = 1; i <= n; i++){
		if (!visited[i]) {
			fill(visited.begin(), visited.end(), 0);
			dfs(i, i);
			for (int x : visited_after) visited[x] = true;
			visited_after.clear();
		}
	}
	puts("IMPOSSIBLE");
}

void test() {
	for (int i = 1; i <= n; i++){ 
	}
}

int main(){
	/*using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
	
	auto t1 = high_resolution_clock::now();
	solve();
	auto t2 = high_resolution_clock::now();
    // Getting number of milliseconds as a double. 
    duration<double, std::milli> ms_double = t2 - t1;
	cout << ms_double.count() << "\n";

	t1 = high_resolution_clock::now();
	test();
	t2 = high_resolution_clock::now();
    // Getting number of milliseconds as a double. 
    ms_double = t2 - t1;
	cout << ms_double.count() << "\n";
	*/	
	solve();

}




