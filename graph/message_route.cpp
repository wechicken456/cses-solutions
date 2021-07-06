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
vector<int>adj[maxN + 1];

void solve(){
	bool check = false;
	cin >> n >> m;
	for (int i = 1 , a, b; i <= m; i++){
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	vector<int>ans(n + 2);
	queue<int>q;
	q.push(1);
	while (!q.empty()) {
		int top = q.front();
		q.pop();
		if (top == n) {
			check = true;
			break;
		}
		for (auto &c : adj[top]) {
			if (visited[c]) continue;
			visited[c] = true;
			q.push(c);
			ans[c] = top;
		}
	}
	if (!check) {
		cout << "IMPOSSIBLE" << "\n";
	}
	else {
		int cur = n;
		vector<int>res;
		while (cur != 1) {
			res.pb(cur);
			cur = ans[cur];
		}
		res.pb(1);
		cout << res.size() << "\n";
		for (int i = res.size() - 1 ; i >= 0; i--){
			cout << res[i] << " ";
		}
	}
}

int main(){
	solve();
}


