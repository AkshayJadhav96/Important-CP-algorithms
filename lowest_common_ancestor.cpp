#include<bits/stdc++.h>
using namespace std;
// we can find the LCA of two nodes u and v in O(log n) time using binary lifting.
int n,l; //n is total number of nodes, l is the maximum power of 2 we need to consider
vector<vector<int>> up; // up[u][j] will store the 2^j
vector<vector<int>> adj; // adjacency list for the tree
vector<int> tin,tout;
int timer;

void dfs(int u, int parent){
    tin[u] = ++timer; // set the entry time of node u
    up[u][0] = parent; // set the immediate parent
    for (int j = 1; j <=l; j++) {
        up[u][j] = up[up[u][j - 1]][j - 1]; // set the 2^j-th ancestor
    }
    for (int v : adj[u]) { // iterate over all children of u
        if (v != parent) { // avoid going back to the parent
            dfs(v, u); // recursive DFS call
        }
    }
    tout[u] = ++timer; // set the exit time of node u
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u]; // check if u is an ancestor of v
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u; // if u is an ancestor of v, return u
    if (is_ancestor(v, u)) return v; // if v is an ancestor of u, return v
    for (int j = l; j >= 0; j--) { // iterate from the highest power of 2 down to 0
        if (!is_ancestor(up[u][j], v)) {
            u = up[u][j]; // move u up to the 2^j-th ancestor
        }
    }
    return up[u][0]; // return the parent of u, which is the LCA
}

int main(){
    int q;
    cin >> n >> q;
    tin.resize(n + 1);
    tout.resize(n + 1);
    adj.resize(n + 1);
    timer = 0;
    l = ceil(log2(n)); // calculate the maximum power of 2 needed
    up.assign(n + 1, vector<int>(l + 1, 0)); // initialize the up table
    for (int i = 2; i <= n; i++) {
        cin >> up[i][0]; // input parent of node i
        adj[up[i][0]].push_back(i); // build the adjacency list
        adj[i].push_back(up[i][0]); // undirected tree, so add both
    }
    
    dfs(1, 1); // start DFS from the root node (1) with no parent so set as 1
    
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v; // input the two nodes for which we need to find LCA
        cout << lca(u, v) << "\n"; // output the LCA of u and v
    }
}
