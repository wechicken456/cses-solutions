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
vector<int>adj[maxN];

void dfs(int cur){
	if (visited[cur]) return;
	visited[cur] = true;
	// process node cur
	for (auto &c : adj[cur]) {
		dfs(c);
	}
}

void solve(){
	queue<int>test;
}

int main(){
	solve();
}


