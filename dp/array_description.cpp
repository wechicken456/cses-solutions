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
const int mod = 1e9 + 7;
int n, m,x;

void solve(){
	scanf("%d%d", &n, &m);
	bool check = true;
	vector<int>a(n+1);
	scanf("%d", &a[1]);
	for (int i = 2; i <= n; i++){
		scanf("%d", &a[i]);
		if ( (a[i] != 0 && a[i-1] != 0) && abs(a[i] - a[i-1]) > 1) check = false;
	}
	// THIS IS MY OWN SOLUTION, USE 2D array[i][x] where i is the current index and x is the current element at this index, then a[i][x] denotes the number of possible arrays if the i-th element is x.  
	if (check == false) puts("0");
	else {
		set<int>s;
		vector<vector<ull>>num_ways(n+1, vector<ull>(m+2, 0));
		num_ways[0][a[1]] = 1;
		for (int i = 1; i <= n; i++){
			if (a[i] == 0) {
				if (i == 1) {				// if first element is 0 then there are m possible values.
					for (int j = 1; j <= m; j++){
						s.insert(j);
						num_ways[1][j] = 1;
					}
					continue;
				}
				for (auto &c : s) {			// otherwise loop through all values, the number of possible arrays if the we chose the current element to be "c" is the sum of all possible ways of the previous "c-1", "c" and "c+1". 
					for (int j = -1; j < 2; j++) {
						int cur = c + j;
						if (cur > 0 && cur <= m) {
							num_ways[i][cur] += num_ways[i-1][c];
							num_ways[i][cur] %= mod;
						}
					}
				}
				auto first_elem = *(s.begin());
				auto last_elem = *(--s.end());
				if (first_elem - 1 > 0) s.insert(first_elem - 1);
				if (last_elem + 1 <= m) s.insert(last_elem + 1);
				
			}
			else {				// if element is not 0 then the current possible is the sum of possible ways for the previous element to be a[i] -1 , a[i] and a[i+1]
				s.clear();
				s.insert(a[i]);
				num_ways[i][a[i]] = num_ways[i-1][a[i] - 1] + num_ways[i-1][a[i]] + num_ways[i-1][a[i]+1];
				num_ways[i][a[i]] %= mod;
			}
		}

		if (n == 1 && a[1] == 0) printf("%d", m); // if there's only 1 element and it is 0 then there are m ways.
		else {
			if (a[n] != 0) printf("%lld", num_ways[n][a[n]]);	
			else {
				ll sum = 0;
				for (int i = 1; i <= m; i++){	// if last element is 0 then we did not calculate num_ways[n][i] using the dp algorithm above so now we need to sum up the values.
					sum += num_ways[n][i];
					sum %= mod;
				}
				printf("%lld", sum);
			}
		}
	}
}

int main(){
	solve();
}


