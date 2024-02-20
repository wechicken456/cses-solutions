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

const int maxN = 500;
const int maxX = 1000;
const int mod = 1e9 + 7;
int n, m,x;
int series[maxN + 1];

void solve(){
	cin >> n;
	series[n] = n*(n+1)/2;
	if (series[n] % 2 == 1) cout << 0;		// if sum from 1 to n is odd then 1 set will be odd and the other will be even => no possible way.
	else {			
		vector<vector<ull>>dp(series[n]/2+1, vector<ull>(n+1));	// just find the number of ways we can construct the sum of 1 to n divides by 2.
		dp[0] = vector<ull>(n+1, 1);		// there's 1 way to create an empty set. 
		
		// NOTE: we only take numbers up to n-1 as we default n to be in the 2nd set. 
		// For example: if n = 7, and 1st set is {1,3,4,6} then the numbers {2,5} are left to the 2nd set with 7: {2,5,7}.
		for (int sum = 1; sum <= series[n] / 2;  sum++){
			for (int i = 1; i < n; i++){
				if (sum - i >= 0) dp[sum][i] += dp[sum-i][i-1];	// num of ways to create sum-i from the first i-1th numbers. 
				dp[sum][i] += dp[sum][i-1];
				dp[sum][i] %= mod;
			}
		}
		cout << dp[series[n]/2][n-1];
	}	
}

int main(){
	solve();
}


