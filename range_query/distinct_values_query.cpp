
// sort the queries following MO's algorithm: https://blog.anudeep2011.com/mos-algorithm/

/*  Why don't we just sort all the pairs by L pointer normally?

The problem there is that the right pointer might jump too much. Imagine the scenario with N=100:
1 100
2 2
3 100
4 4
5 100
6 6
7 100
8 8
9 100
If we sort on L and R, we will traverse about 500 blocks. If we sort on the left block index first, we traverse as:
BLOCK 1:
2 2
1 100
3 100
BLOCK 2:
4 4
6 6
5 100
BLOCK 3:
8 8
7 100
9 100
Now the right pointer traverses about 300 blocks. Left pointer traversal is still negligible. Hence we go for this sorting technique.

*/

#include<bits/stdc++.h>
#include<tuple>
#include<iostream>

#define ll long long
#define pb push_back

using namespace std;
int n,b;
vector<int>a;
vector<vector<tuple<int , int, int>>> q;

bool comp (const tuple<int ,int, int>&u, const tuple<int ,int, int>&v) {
	return get<1>(u) < get<1>(v);
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> b;
	
	int block_size = ceil(sqrt(n));
	q = vector<vector<tuple<int ,int ,int>>>(block_size);
	a = vector<int>(n);
	vector<int>ans(b);
	vector<int>occ(n, 0);
	
	// coordinate compression - read Errichto: https://codeforces.com/blog/entry/84164
	vector<pair<int ,int>>pairs;
	pairs.resize(n);
	for (int i = 0 ; i < n; i++) {
		cin >> a[i];
		pairs[i] = {a[i], i};
	}
	sort(pairs.begin(), pairs.end());
	int nxt = 0;
	for (int i =0 ; i < n; i++) {
		if (i > 0 && pairs[i].first != pairs[i-1].first) nxt++;
		a[pairs[i].second] = nxt;
	}
	
	// sort by L based on the blocks they belong to
	for (int i = 0; i < b; i++){
		int low, high;
		cin >> low >> high;
		low--;
		high--;
		int cur = (int) low / block_size;
		q[cur].pb(make_tuple(low, high, i));
	}
	
	// now sort by R
	for (int i =0  ; i < block_size; i++) {
		sort(q[i].begin(), q[i].end(), comp);
	}
	
	int cur_ans = 1, cur_left = 0, cur_right = 0;
	occ[a[0]] = 1;
	
	for (int i = 0 ; i < block_size; i++) {
		for (auto &j : q[i]) {
			int left_query, right_query, idx;
			tie(left_query, right_query ,idx) = j;
			// handle left pointer first
			
			while (cur_left < left_query) {
				occ[a[cur_left]]--;
				if (occ[a[cur_left]] == 0) cur_ans--;
				cur_left++;
			}
		
			while (cur_left > left_query) {
				cur_left--;
				occ[a[cur_left]]++;
				if (occ[a[cur_left]] == 1) cur_ans++;
			}
		

			// handle right pointer now
			while (cur_right > right_query) {
				occ[a[cur_right]]--;
				if (occ[a[cur_right]] == 0) cur_ans--;
				cur_right--;
			}
	
			while (cur_right < right_query) {
				cur_right++;
				occ[a[cur_right]]++;
				if (occ[a[cur_right]] == 1) cur_ans++;
			}
			ans[idx] = cur_ans;
		}
	}
	for (int i =0 ; i < b; i++) {
		cout << ans[i] << "\n";
	}
}








