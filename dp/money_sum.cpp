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

const int maxN = 100;
const int maxX = 1000;
const int maxSum = maxN*maxX;
int n, m,x;

void solve(){
	scanf("%d", &n);
	vector<int>coin(n + 1);
	for (int i = 1 ; i <= n; i++){
		scanf("%d", &coin[i]);
	}
	vector<vector<int>>sum(n + 2, vector<int>(maxSum + 1));
	for (int i = 1 ; i <= n; i++){
		sum[i][coin[i]] = 1;
		for (int j = 1 ; j <= maxSum; j++){
			sum[i][j] |= sum[i-1][j];					// if it is possible to make sum j using the first i - 1 coins, then it is possible to make sum j with i coins (cause we can use the first i-1 coins)		
			if (j - coin[i] >= 0 ) sum[i][j] |= sum[i-1][j-coin[i]];			// if it is possible to make sum j-coin[i] then it is possible to make sum j with i coins
		}		
	}
	vector<int>ans;
	for (int i = 1; i <= maxSum; i++){
		if (sum[n][i])	ans.pb(i);
	}
	printf("%d\n", ans.size());
	for (auto &c : ans) printf("%d ",c); 
}

int main(){
	solve();
}


