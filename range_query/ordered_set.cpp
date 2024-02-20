
// https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/

// Common file containing the tree-based data structure we will use which is present in this file
#include <ext/pb_ds/assoc_container.hpp>
// Including tree_order_statistics_node_update
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>

using namespace std;

// replace int type in the 1st and 3rd argument with the necessary type
typedef ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
}
