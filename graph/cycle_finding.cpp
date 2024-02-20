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
#include<tuple>

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

const int maxN = 2500;
const ll maxX = 1e9*2500+5;
int n, m,x;
bool visited[maxN + 1];
vector<int>adj[maxN];
int parents[maxN + 1];

struct Edges {
	int from, to, weight;
};

vector<Edges>edges;
void solve(){
	cin >> n >> m;
	edges = vector<Edges>(m);
	
	vector<int>parents(n + 1);
	for (int i = 0,a,b,c; i < m; i++){
		cin >> a >> b >> c;
		edges[i].from = a;
		edges[i].to = b;
		edges[i].weight = c;
		parents[b] = a;
	}
	
	vector<ll>dist(n + 1, maxX);

	for (int i = 1; i <= n - 1; i++){
		for (auto &c : edges) {
			if (dist[c.to] > dist[c.from] + c.weight) {
				dist[c.to] = dist[c.from] + c.weight;
				parents[c.to] = c.from;
			}
		
		}
	}
	for (int j = 1; j <= n; j++ ) {
		for (auto &c : edges){
			if (dist[c.to] > dist[c.from] + c.weight) {
				cout << "YES" << "\n";
				vector<int>ans;
				ans.pb(c.from);
				int next = parents[c.from];
				while (next != c.from) {
					ans.pb(next);
					next = parents[next];
				}
				reverse(ans.begin(), ans.end());
				for (int a : ans) cout << a << " "; 
				cout << c.to;
				return;
			}
		}
	}
	cout << "NO" << "\n";
}

int main(){
	solve();
}


