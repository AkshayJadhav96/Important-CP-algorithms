// // Here the index and tight dimensions are guaranteed to be present.. and other extra dimensions may also be present
// Number of digit one in numbers from 0 to n Digit DP

#include<bits/stdc++.h>
using namespace std;

int solve(string &s,int ind,int tight,int cnt,vector<vector<vector<int>>> &dp){
    if(ind==s.length()) return cnt;
    if(dp[ind][tight][cnt]!=-1) return dp[ind][tight][cnt];
    int lim = (tight==1 ? (s[ind]-'0') : 9);
    int ans = 0;
    for(int i = 0;i<=lim;i++){
        int upCnt = cnt+ (i == 1 ? 1: 0);
        ans += solve(s,ind+1,tight & ((s[ind]-'0') == i),upCnt,dp);
    }
    return dp[ind][tight][cnt]=ans;
}

int countDigitOne(int n) {
    string g = to_string(n);
    vector<vector<vector<int>>> dp(10,vector<vector<int>> (2,vector<int> (10,-1)));
    return solve(g,0,1,0,dp);
}

int main(){
    int n;
    cin>>n;
    cout<<countDigitOne(n)<<endl;
    return 0;
}
