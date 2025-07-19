// Here for each node u we store what is the node that is 2^i-th ancestor of u
// We can then use this to find the k-th ancestor of a node in O(log n) time
// This is useful for problems where we need to find the k-th ancestor of a node
// in a tree, such as Lowest Common Ancestor (LCA) problems.

// Here I have solved the problem "Company Queries I" from cses problem sheet using this technique.

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,q;
    cin>>n>>q;
    vector<vector<int>> up(n+1, vector<int>(20, -1)); // 2^i-th ancestor of node u assuming the tree has max height of 2^20
    for(int i=2;i<=n;i++){ 
        cin>>up[i][0];
    }
    for(int j=1;j<20;j++){
        for(int i=2;i<=n;i++){
            if(up[i][j-1] == -1) // if the previous ancestor is -1, we cannot go further up
                up[i][j] = -1;
            else up[i][j]=up[up[i][j-1]][j-1];
        }
    }
    for(int i = 0;i<q;i++){
        int u,k;
        cin>>u>>k;
        for(int j = 0;j<20 && u != -1;j++){
            if(k & (1 << j)){ // if the j-th bit of k is set
                u = up[u][j]; // move to the 2^j-th ancestor
            }
        }
        cout<<u<<"\n"; // print the k-th ancestor of node u
    }
}

// This code runs in O(n log n) for preprocessing and O(log n) for each query.
// The space complexity is O(n log n) due to the storage of ancestors.
// This technique is very efficient for tree queries and can be adapted for various problems involving tree structures.
// For LCA like this:
