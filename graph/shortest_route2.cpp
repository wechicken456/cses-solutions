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

const int maxN = 500;
const int maxX = 1e9+1;
int n, m,x;
bool visited[maxN + 1][maxN + 1];
vector<pair<int,int>>adj[maxN + 1];
vector<vector<ull>>dist(501, vector<ull>(501, 500*1e9+1));

void solve(){
	int query;
	cin >> n >> m >> query;
	for (ull i = 1, a, b, c; i <= m ; i++){
		cin >> a >> b >> c;
		dist[a][b] = min(dist[a][b], c);	// just in case there are multiple distances, we take the smallest one.
		dist[b][a] = min(dist[b][a], c);
	}
	for (int i = 1; i <= n; i++) dist[i][i] = 0;	
	// essentially we start at city j, go to city k through city i.
	for (int i = 1; i <= n; i++){			// i is the intermediate city
		for (int j = 1; j <= n; j++){		// starting from city j
			for (int k = 1; k <= n; k++){	// destination is city k
				dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
			}
		}
	}
	for (int i = 1, a, b; i <= query; i++){
		cin >> a >> b;
		if (dist[a][b] >= 500*1e9+1) cout << -1 << "\n";
		else cout << dist[a][b] << "\n";
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();
}


