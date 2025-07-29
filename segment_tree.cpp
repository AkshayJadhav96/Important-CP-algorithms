// Range Max Queries using segment Tree

#include<bits/stdc++.h>
using namespace std;

vector<int> v,seg;

void build(int ind,int low,int high){
    if(low==high){
        seg[ind] = v[low];
        return;
    }
    int mid = (low+high)/2;
    build(2*ind+1,low,mid);
    build(2*ind+2,mid+1,high);
    seg[ind] = max(seg[2*ind+1],seg[2*ind+2]);
}

int query(int ind,int low,int high,int l,int r){
    // Three Conditions
    // 1) The node lies completely within the range(l-r)
    if(low>=l && high<=r) return seg[ind];

    // 2) The node is outside of the range
    if(high<l || low>r) return INT_MIN;

    // 3) The node overlaps with the range (partially or fully)
    int mid = (low+high)/2;
    int left = query(2*ind+1,low,mid,l,r);
    int right = query(2*ind+2,mid+1,high,l,r);
    return max(left,right); 
}

int main(){
    int n;
    cin>>n;
    v.resize(n);
    seg.resize(4*n);
    for(auto &j : v) cin>>j;
    build(0,0,n-1);
    int q;
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<query(0,0,n-1,l,r)<<endl;
    }
}


// Similaraly we can do for min,sum,or,xor,and,gcd queries