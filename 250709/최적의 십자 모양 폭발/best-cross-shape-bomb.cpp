#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
int n;
vector<vector<int>>grid;

void input(){
    cin>>n;
    grid.resize(n+1,vector<int>(n+1));
    //1-based
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>grid[i][j];
}

void debugging(vector<vector<int>>&v){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<v[i][j]<<' ';
        }
        cout<<endl;
    }

}
bool range(int x,int y){
    return x>=1 && x<=n && y>=1 && y<=n;
}

void bomb(vector<vector<int>>&v,int x,int y){
    int move=v[x][y];
    int dx[]={0,0,1,-1};
    int dy[]={1,-1,0,0};
    for(int i=0;i<4;i++){
        for(int j=0;j<move;j++){//가운데 자리는 중복되긴 함
            int nx= x+dx[i]*j;
            int ny= y+dy[i]*j;
            if(range(nx,ny)){
                v[nx][ny]=0;//폭탄 처리
            }
        }
    }
    //cout<<"\n폭탄이 터진후\n";
    //debugging(v);
}

vector<vector<int>> gravity(vector<vector<int>>&v){
    vector<vector<int>>gGrid(n+1,vector<int>(n+1));

    for(int col=1;col<=n;col++){//열을 순회하면서
        int pointer=n;
        for(int row=n;row>=1;row--){
            if(v[row][col]==0) continue;
            gGrid[pointer--][col]=v[row][col];
        }
        while(pointer>=1){
            gGrid[pointer--][col]=0;
        }
    }

    //cout<<"\n중력의 힘을 받은 후\n";
    //debugging(gGrid);
    return gGrid;
}

int coupleCnt(vector<vector<int>>&v){
    int dx[]={0,0,1,-1};
    int dy[]={1,-1,0,0};
    int validCoupleCnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(v[i][j]==0) continue;
            for(int k=0;k<4;k++){
                int nx = i+dx[k];
                int ny = j+dy[k];
                if(!range(nx,ny)) continue;
                if(v[nx][ny]==0) continue;
                if(v[i][j]==v[nx][ny]){
                    //cout<<i<<','<<j<<','<<nx<<','<<ny<<endl;
                    validCoupleCnt++;
                }
            }
        }
    }

    return validCoupleCnt/2;
}

int main(){
    input();
    int ans=0;
    vector<vector<int>>cGrid=grid;//복사본
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            //cout<<"testing: "<<i<<','<<j<<endl;
            bomb(cGrid,i,j);
            vector<vector<int>>gGrid=gravity(cGrid);//중력을 받은 후 grid;
            ans = max(ans,coupleCnt(gGrid));
            cGrid=grid;//케이스가 끝난 후에는 다시 원 상태로 돌아와야
        }
    }
    cout<<ans<<endl;

    return 0;

}