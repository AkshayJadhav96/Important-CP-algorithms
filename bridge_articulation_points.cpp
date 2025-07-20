// Finding Bridges and Articulation Points in a Graph:
// This code uses Tarjan's algorithm to find bridges and articulation points in a graph.
// A bridge is an edge that, when removed, increases the number of connected components.
// An articulation point is a vertex that, when removed, increases the number of connected components.

#include<bits/stdc++.h>
using namespace std;

vector<int> tin,low,articulation_points;
vector<vector<int>> adj; // adjacency list for the graph
vector<pair<int, int>> bridges; // to store bridges
vector<bool> visited; // to track visited nodes
int timer;

void dfs(int node,int par){
    tin[node] = low[node] = timer++;
    visited[node] = true; // mark the node as visited
    int children = 0; // count of children for articulation point check (here children referes to the number of dfs calls made from this node)
    for(int neighbour : adj[node]){
        if(neighbour == par) continue; // skip the parent node
        if(visited[neighbour]){ // if neighbour is already visited
            low[node] = min(low[node], tin[neighbour]); // update low value
        }else {
            dfs(neighbour, node); // recursive DFS call
            low[node] = min(low[node], low[neighbour]); // update low value after DFS
            if(low[neighbour] > tin[node]){ // check for bridge condition
                bridges.push_back({node, neighbour}); // store the bridge
            }
            if(low[neighbour] >= tin[node] && par != -1){ // check for articulation point condition
                articulation_points[node] = true; // mark as articulation point
            }
            children++; // increment children count
        }
        if(par==-1 && children > 1){ // special case for root node
            articulation_points[node] = true; // root is an articulation point if it has more than one child
        }
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    tin.resize(n+1, -1);
    low.resize(n+1, -1);
    adj.resize(n + 1); // resize adjacency list to hold n nodes
    visited.resize(n + 1, false); // initialize visited array
    articulation_points.resize(n + 1, false); // initialize articulation points array
    timer = 0;
    for(int i = 0;i<m;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x); // undirected graph, so add both directions
    }
    dfs(0,-1); // start DFS from node 0 with no parent (-1)
    for(int i = 0;i<n;i++){
        if(articulation_points[i]) cout<<i<<" ";
    }
    cout<<endl;
    for(auto &j : bridges){
        cout<<j.first<<" "<<j.second<<endl; // print bridges
    }
}

// This code finds articulation points and bridges in an undirected graph using DFS.
// It uses a timer to track discovery times and low values to determine articulation points and bridges.
// The adjacency list is built from input edges, and the DFS explores the graph while updating the low values.
// The results are printed at the end, showing which nodes are articulation points and which edges are bridges.