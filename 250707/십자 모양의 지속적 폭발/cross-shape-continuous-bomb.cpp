#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int n,m;
vector<vector<int>>grid;
vector<int>bomb_cols;

void input(){
    cin>>n>>m;
    grid.resize(n+1,vector<int>(n+1));
    bomb_cols.resize(m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>grid[i][j];
        }
    }
    for(int i=0;i<m;i++){
        cin>>bomb_cols[i];
    }
}

bool range(int x,int y){
    return x>=1 && x<=n && y>=1 && y<=n;
}

void print(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<grid[i][j]<<' ';
        }
        cout<<'\n';
    }
}

void bomb(int col){
    int dx[]={0,0,1,-1};
    int dy[]={1,-1,0,0};
    int row=1;
    int movements=0;

    for(int i=1;i<=n;i++){
        if(grid[i][col]==0) continue;
        row=i;
        break;
    }//폭탄이 터질 중심 위치 확인
    movements=grid[row][col];
    grid[row][col]=0;
    
    if(movements==1) {
        //grid[row][col]=0;
        return;
    }

    for(int i=0;i<4;i++){
        int curRow=row;
        int curCol=col;
        for(int j=0;j<(movements-1);j++){
            int nx = curRow + dx[i];
            int ny = curCol + dy[i];
            if(range(nx,ny)){
                grid[nx][ny]=0;
                curRow=nx;
                curCol=ny;
            }
        }
    }
    
    //print();
}

void gravity(){
    //grid를 열 기준으로 순회하면서 -1이 있으면 위의 행을 땡겨온다. 와서 값을 바꿔주고 땡겨온 행은 -1처리
    for(int col=1;col<=n;col++){
        for(int row=2;row<=n;row++){//1행은 폭탄이 터져도 땡길게 없기 때문에
            if(grid[row][col]!=0) continue;
            for(int i=row;i>1;i--){//위에서 부터 땡겨져야 하니깐
                grid[i][col]=grid[i-1][col];
                grid[i-1][col]=0;
            }
        }
    }
}



int main(){
    input();
    for(int i=0;i<bomb_cols.size();i++){
        int col=bomb_cols[i];
        bomb(col);
        gravity();
    }
    print();
    return 0;
}