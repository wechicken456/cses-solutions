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

void solve(){
	int n;
	cin >> n;
	map<int, vector<pair<int,int>>>projects;
	int latest = 0;
	for (int i = 1 , start, end, weight; i <= n; i++ ){
		cin >> start >> end >> weight;
		projects[end].pb({start, weight});
		latest = max(end ,latest);
		
	}
	
	vector<int>days = {0};
	for (auto &c: projects) days.pb(c.first + 1);
	int s = days.size();
	vector<ll>dp(s, 0);		// the amount of money we can earn BEFORE day i. 
	int i = 1;
	for (auto &c : projects){
		dp[i] = dp[i-1];
	//	cout << days[i] << " ";
		
		ll cur = dp[i];
		for (pair<int ,int>p : c.second) {
			int start = upper_bound(days.begin(), days.end(), p.first) - days.begin();
			start--;
			ll sum = dp[start];
			sum += p.second;
	//		cout << start << "-" << sum << " " ;
			cur = max(cur , sum);	
		}
		
		dp[i] = max(cur, dp[i]);
	//	cout << dp[i];
	//	cout << "\n";
		i++;
	}
	//cout << i << " " << s;
	cout << dp[s - 1] << "\n";
}

int main(){
	solve();
}


