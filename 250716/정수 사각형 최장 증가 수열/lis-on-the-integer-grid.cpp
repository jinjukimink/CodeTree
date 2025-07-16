#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>>dp;
vector<vector<int>>grid;
int n;
void input(){
    cin>>n;
    dp.resize(n,vector<int>(n+1,1));
    grid.resize(n,vector<int>(n+1));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>grid[i][j];
}

int main(){
    input();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i-1>0 && grid[i][j]>grid[i-1][j]){
                dp[i][j]=max(dp[i][j],dp[i-1][j]+1);
            }
            if(j-1>0 && grid[i][j]>grid[i][j-1]){
                dp[i][j]=max(dp[i][j],dp[i][j-1]+1);
            }
            if(i+1<n && grid[i][j]>grid[i+1][j]){
                dp[i][j]=max(dp[i][j],dp[i+1][j]+1);
            }
            if(j+1<n && grid[i][j]>grid[i][j+1]){
                dp[i][j]=max(dp[i][j],dp[i][j+1]+1);
            }
        }
    }
    for(int i=n-1;i>=0;i--){
        for(int j=n-1;j>=0;j--){
            if(i-1>0 && grid[i][j]>grid[i-1][j]){
                dp[i][j]=max(dp[i][j],dp[i-1][j]+1);
            }
            if(j-1>0 && grid[i][j]>grid[i][j-1]){
                dp[i][j]=max(dp[i][j],dp[i][j-1]+1);
            }
            if(i+1<n && grid[i][j]>grid[i+1][j]){
                dp[i][j]=max(dp[i][j],dp[i+1][j]+1);
            }
            if(j+1<n && grid[i][j]>grid[i][j+1]){
                dp[i][j]=max(dp[i][j],dp[i][j+1]+1);
            }
        }
    }

    for(int i=0;i<n;i++){
        for(int j=n-1;j>=0;j--){
            if(i-1>0 && grid[i][j]>grid[i-1][j]){
                dp[i][j]=max(dp[i][j],dp[i-1][j]+1);
            }
            if(j-1>0 && grid[i][j]>grid[i][j-1]){
                dp[i][j]=max(dp[i][j],dp[i][j-1]+1);
            }
            if(i+1<n && grid[i][j]>grid[i+1][j]){
                dp[i][j]=max(dp[i][j],dp[i+1][j]+1);
            }
            if(j+1<n && grid[i][j]>grid[i][j+1]){
                dp[i][j]=max(dp[i][j],dp[i][j+1]+1);
            }
        }
    }

    for(int i=n-1;i>=0;i--){
        for(int j=0;j<n;j++){
            if(i-1>0 && grid[i][j]>grid[i-1][j]){
                dp[i][j]=max(dp[i][j],dp[i-1][j]+1);
            }
            if(j-1>0 && grid[i][j]>grid[i][j-1]){
                dp[i][j]=max(dp[i][j],dp[i][j-1]+1);
            }
            if(i+1<n && grid[i][j]>grid[i+1][j]){
                dp[i][j]=max(dp[i][j],dp[i+1][j]+1);
            }
            if(j+1<n && grid[i][j]>grid[i][j+1]){
                dp[i][j]=max(dp[i][j],dp[i][j+1]+1);
            }
        }
    }
    
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            ans=max(dp[i][j],ans);
        }
    }
    cout<<ans;
    return 0;
}