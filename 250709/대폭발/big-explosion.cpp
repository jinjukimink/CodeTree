#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int n,m,r,c;

bool range(int x,int y){
    return x>=1 && x<=n && y>=1 && y<=n;
}

void debugging(vector<vector<int>>&v){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<v[i][j]<<' ';
        }
        cout<<'\n';
    }
}

vector<vector<int>>bomb(vector<vector<int>>&prev,int t){
    vector<vector<int>>bGrid(n+1,vector<int>(n+1,0));
    int dx[]={0,0,-1,1};
    int dy[]={1,-1,0,0};
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(prev[i][j]==0) continue;//폭탄이 아니면 건너뜀
            bGrid[i][j]=-1;
            for(int k=0;k<4;k++){
                //cout<<"이동거리: "<<pow(2,t-1)<<endl;
                int nx= i + (dx[k]*pow(2,t-1));
                int ny= j + (dy[k]*pow(2,t-1));
                //cout<<i<<','<<j<<','<<nx<<','<<ny<<endl;
                if(!range(nx,ny)) continue;
                if(bGrid[nx][ny]==-1) continue;
                bGrid[nx][ny]=-1;
            }
        }
    }
    //cout<<'\n'<<t<<"초에 터진 폭탄 결과\n";
    //debugging(bGrid);
    return bGrid;
}


int solution(vector<vector<int>>&v){
    int cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(v[i][j]==-1) cnt++;
        }
    }
    return cnt;
}

int main(){
    cin>>n>>m>>r>>c;
    vector<vector<int>>grid(n+1,vector<int>(n+1,0));
    grid[r][c]=-1;
    for(int i=1;i<=m;i++){
        vector<vector<int>>bGrid=bomb(grid,i);
        grid=bGrid;//앞선 폭탄을 누적으로 폭발해야 한다.
    }
    cout<<solution(grid)<<endl;

}