#include<iostream>
#include<vector>
using namespace std;

int n,r,c,dir;
vector<int>m;
vector<vector<int>>grid;
vector<vector<int>>copyGrid;    
vector<pair<int,int>>rects;

void input(){
    cin>>n;
    grid.resize(n+1,vector<int>(n+1));
    copyGrid.resize(n+1,vector<int>(n+1));
    m.resize(4);
    //1부터 채우실게요~
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>grid[i][j];
            copyGrid[i][j]=grid[i][j];//값을 복사해줍니다.
        }
    }
    cin>>r>>c;
    for(int i=0;i<4;i++) cin>>m[i];
    cin>>dir;
    
}

void makeRect(){
    int dx[]={-1,-1,1,1};
    int dy[]={1,-1,-1,1};
    int curX=r;
    int curY=c;

    for(int i=0;i<4;i++){
        for(int j=0;j<m[i];j++){
            int nx=curX+dx[i];
            int ny=curY+dy[i];
            rects.push_back({nx,ny});
            curX=nx;
            curY=ny;
        }
    }
}

void rotate(){
    int len=rects.size();
    //cout<<len<<endl;
    for(int i=0; i < len;i++){
        auto[curX,curY] = rects[(len+i) % len];
        auto[nx,ny] = rects[(i+1+len) % len];
        if(dir==1) copyGrid[curX][curY]=grid[nx][ny];
        else copyGrid[nx][ny]=grid[curX][curY];
    }
}

void print(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<copyGrid[i][j]<<' ';
        }
        cout<<'\n';
    }
}

int main(){
    input();
    makeRect();

    rotate();
    print();
    return 0;
}