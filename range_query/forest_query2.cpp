#include<bits/stdc++.h>
#include<iostream>

using namespace std;

#define ll long long
#define pb push_back

int n , q;
vector<vector<int>>grid;

int main () {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> q;
	int old_n = n;
	while (__builtin_popcount(n) != 1) {
		n++;
	}
	
	grid = vector<vector<int>>(n, vector<int>(n, 0));
	for (int i = 0 ; i < old_n; i ++) {
		for (int j = 0 ; j < old_n; j++) {
			char c;
			cin >> c;
			if (c == '*') {
				grid[i][j] = 1;
			}
		}
	}
	
}
