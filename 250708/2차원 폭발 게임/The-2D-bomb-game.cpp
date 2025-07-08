#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int n,m,k;

void debug(vector<vector<int>>&v){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<v[i][j]<<' ';
        }
        cout<<endl;
    }
}

void bomb(vector<vector<int>>&grid){
    for(int col=1;col<=n;col++){
        int cnt=1;
        int num=grid[1][col];//초기화
        //cout<<"num 초기화"<<num<<endl;
        for(int row=2;row<=n;row++){
            if(grid[row][col]==num) {
                cnt++;
                if(row==n){//마지막 행이면
                    if(cnt>=m) for(int k=0;k<cnt;k++) grid[row-k][col]=0;
                }
            }
            else{
                if(cnt>=m) for(int k=0;k<cnt;k++) grid[row-k-1][col]=0;
                cnt=1;
                num=grid[row][col];
            }
        }
    }
    //cout<<"===폭탄 터진 후===\n";
    //debug(grid);
}

void gravity(vector<vector<int>>&v){
    for(int col=1;col<=n;col++){
        int cnt=0;
        for(int row=n;row>=1;row--){
            if(v[row][col]!=0) continue;
            for(int subrow=row-1;subrow>=1;subrow--){
                if(v[subrow][col]==0) continue;
                v[row-(cnt++)][col]=v[subrow][col];
                v[subrow][col]=0;//빈자리
            }
        }
    }
    //cout<<"\n중력의 영향을 받은 후\n";
    //debug(v);
}

vector<vector<int>>rotate(vector<vector<int>>&v){
    //시계 방향으로 90도 회전
    //cout<<"회전하는 함수의 매개변수 행렬\n";
    //debug(v);
    vector<vector<int>>rotateGrid(n+1,vector<int>(n+1,0));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            rotateGrid[j][n-i+1] = v[i][j];
        }
    }
    //cout<<"\n회전 잘했니?\n";
    //debug(rotateGrid);
    return rotateGrid;
}

int solution(vector<vector<int>>&v){
    int cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(v[i][j]==0) continue;
            cnt++;
        }
    }
    return cnt;
}

int main(){
    cin>>n>>m>>k;
    vector<vector<int>>grid(n+1,vector<int>(n+1));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>grid[i][j];
        }
    }
    if(n==1){
        cout<<0<<'\n';
        return 0;
    }

    while(k--){
        bomb(grid);
        gravity(grid);
        vector<vector<int>>rotateGrid = rotate(grid);
        gravity(rotateGrid);
        bomb(rotateGrid);
        grid=rotateGrid;
    }
    cout<<solution(grid)<<'\n';
    return 0;
}