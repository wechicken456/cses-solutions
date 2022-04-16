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

const int maxN = 2e5;
const ll maxX = maxN*1e9 + 2;
int n, m, x, k;
vector<pair<int, int>>adj[maxN + 1];
vector<ll>dist[maxN + 1];

//	extended Dijkstra's: https://en.wikipedia.org/wiki/K_shortest_path_routing

void solve(){
	scanf("%d %d %d", &n,  &m , &k);
	
	for (int i = 1 ,a , b , c; i <= m; i++){
		scanf("%d %d %d", &a, &b, &c);
		adj[a].pb({b, c});
	}
	
	priority_queue<pair<ll, int>>pq;
	pq.push({0, 1});

	while (!pq.empty()) {
		pair<ll ,int> cur = pq.top();
		pq.pop();
		
		ll cur_dist = abs(cur.first);
		int cur_parent = cur.second;
		
		if (dist[cur_parent].size() >= k) {		// if we have > k paths leading to cur_parent, we don't need anymorepath to this node as we only need k shortest paths.	Due to priority_queue, these paths are in increasing order already.
			continue;
		}
		
		dist[cur_parent].pb(cur_dist);				// otherwise, add the distance to the list.
					
		for (pair<int , int> p : adj[cur_parent]) {
			ll new_dist = cur_dist + p.second;
			pq.push({-new_dist, p.first});
		}
	}
	for (int i = 0 ; i < k; i++){
		printf("%lld ", dist[n][i]);
	}
}

int main(){
	solve();
}


