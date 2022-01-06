#include <bits/stdc++.h>
using namespace std;
int findTargetSumWays(vector<int>& nums, int target) {
        
        int n = nums.size();
        int dp[n+1][2001];
        for(int i=0;i<=2000;i++){
            dp[0][i] = 0;
        }
        dp[0][1000] = 1;
        
        for(int i=1;i<=n;i++){
            for(int j=0;j<=2000;j++){
                dp[i][j] = 0;
                if(j-nums[i-1]>=0){
                    dp[i][j]+=dp[i-1][j-nums[i-1]];
                }
                if(j+nums[i-1]<=2000){
                    dp[i][j]+=dp[i-1][j+nums[i-1]];
                }
            }
        }
        
        return dp[n][target+1000];
        
        
}

int main(){
    int n, target;
    cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }
    cin>>target;
    cout<<findTargetSumWays(v, target)<<"\n";
}