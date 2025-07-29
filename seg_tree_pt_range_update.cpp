// Point and Range Updates

// Range Max Queries with point updates using segment Tree

// #include<bits/stdc++.h>
// using namespace std;

// vector<int> v,seg;

// void build(int ind,int low,int high){
//     if(low==high){
//         seg[ind] = v[low];
//         return;
//     }
//     int mid = (low+high)/2;
//     build(2*ind+1,low,mid);
//     build(2*ind+2,mid+1,high);
//     seg[ind] = max(seg[2*ind+1],seg[2*ind+2]);
// }

// void update(int ind,int low,int high,int q_index,int new_val){
//     if(low==high){
//         seg[ind] = new_val;
//     }
//     int mid = (low+high)/2;
//     if(mid>=q_index) update(2*ind+1,low,mid,q_index,new_val);
//     else update(2*ind+2,mid+1,high,q_index,new_val);
//     seg[ind] = max(seg[2*ind+1],seg[2*ind+2]);
// }

// int query(int ind,int low,int high,int l,int r){
//     // Three Conditions
//     // 1) The node lies completely within the range(l-r)
//     if(low>=l && high<=r) return seg[ind];

//     // 2) The node is outside of the range
//     if(high<l || low>r) return INT_MIN;

//     // 3) The node overlaps with the range (partially or fully)
//     int mid = (low+high)/2;
//     int left = query(2*ind+1,low,mid,l,r);
//     int right = query(2*ind+2,mid+1,high,l,r);
//     return max(left,right); 
// }

// int main(){
//     int n;
//     cin>>n;
//     v.resize(n);
//     seg.resize(4*n);
//     for(auto &j : v) cin>>j;
//     build(0,0,n-1);
//     int q;
//     cin>>q;
//     while(q--){
//         int i,l,r;
//         cin>>i>>l>>r;
//         if(i==0) update(l,0,n-1,l,r);
//         else cout<<query(0,0,n-1,l,r)<<endl;
//     }
// }


// Range Sum Queries with Range updates (lazy Propogation)

#include<bits/stdc++.h>
using namespace std;

vector<int> v,seg,lazy;

void build(int ind,int low,int high){
    if(low==high){
        seg[ind] = v[low];
        return;
    }
    int mid = (low+high)/2;
    build(2*ind+1,low,mid);
    build(2*ind+2,mid+1,high);
    seg[ind] = seg[2*ind+1]+seg[2*ind+2];
}

void rangeUpdate(int ind,int low,int high,int l,int r,int val){
    if(lazy[ind]!=0){
        seg[ind] += (high-low+1)*lazy[ind];
        if(low!=high){
            lazy[2*ind+1] += lazy[ind];
            lazy[2*ind+2] += lazy[ind];
        }
        lazy[ind] = 0;
    }

    if(r<low || l>high) return;

    if(low>=l && high<=r){
        seg[ind] += (high-low+1)*val;
        if(low!=high){
            lazy[2*ind+1] += val;
            lazy[2*ind+2] += val;
        }
        return;
    }

    int mid = (low+high-1)>>1;
    rangeUpdate(2*ind+1,low,mid,l,r,val);
    rangeUpdate(2*ind+2,mid+1,high,l,r,val);
    seg[ind] = seg[2*ind+1]+seg[2*ind+2]; 
}

int querySum(int ind,int low,int high,int l,int r){
    if(lazy[ind]!=0){
        seg[ind] += (high-low+1)*lazy[ind];
        if(low!=high){
            lazy[2*ind+1] += lazy[ind];
            lazy[2*ind+2] += lazy[ind];
        }
        lazy[ind] = 0;
    }

    if(r<low || l>high) return 0;
    if(low>=l && high<=r) return seg[ind];
    int mid = (low+high)>>1;
    
    return querySum(2*ind+1,low,mid,l,r) + 
            querySum(2*ind+2,mid+1,high,l,r);
}

int main(){
    int n;
    cin>>n;
    v.resize(n);
    seg.resize(4*n);
    lazy.resize(4*n);
    for(auto &j : v) cin>>j;
    build(0,0,n-1);
    int q;
    cin>>q;
    while(q--){
        int i,l,r;
        cin>>i>>l>>r;
        if(i==-1) cout<<querySum(0,0,n-1,l,r)<<endl;
        else rangeUpdate(0,0,n-1,l,r,i);
    }
}
