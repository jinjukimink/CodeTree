#include<iostream>
#include<vector>
#include<tuple>

using namespace std;
#define OFFSET 2000
#define COORD_SIZE 4000

int mapper[128];
int curTime=0;
int lastCollisionTime=0;

typedef tuple<int,int,int,int,int>Marble;//x,y,w,d,id
vector<Marble>marbles;
vector<Marble>next_marbles;
int next_marble_index[COORD_SIZE + 1][COORD_SIZE + 1];

int t;
int dx[4] = {0, 1, -1, 0};
int dy[4] = {1, 0, 0, -1};

Marble move(Marble marble){
   //1초 후 어디에 있는지 구하기 
   int x,y,w,d,id;
   tie(x,y,w,d,id) = marble;
   int nx=x + dx[d];
   int ny=y+dy[d];
   return make_tuple(nx,ny,w,d,id);
}

int findDupMarble(Marble marble){
    //해당 구슬과 충돌이 일어나는 구슬이 있는지 반환
    int targetX,targetY;
    tie(targetX,targetY,ignore,ignore,ignore) = marble;
    return next_marble_index[targetX][targetY];
}

Marble collide(Marble marble1, Marble marble2){
    //두 구슬이 같은 위치에서 충돌했을 경우 살아남은 구슬을 반환한다
    int w1,w2,num1,num2;
    tie(ignore,ignore,w1,ignore,num1)=marble1;
    tie(ignore,ignore,w2,ignore,num2)=marble2;

    if(w1>w2 || (w1==w2 && num1>num2)) return marble1;
    return marble2;
}

bool range(Marble marble){
    //구슬이 범위를 넘어가면 더 이상 충돌이 일어나지 않는다
    int x,y;
    tie(x,y,ignore,ignore,ignore)=marble;
    return x<0 || x>COORD_SIZE || y<0 || y>COORD_SIZE;
}

void pushNextMarble(Marble marble){
    //그 다음 구슬의 목록에 반영
    if(range(marble)) return;

    int idx=findDupMarble(marble);

    if(idx==-1){//충돌하지 않았다면
        next_marbles.push_back(marble);
        int x,y;
        tie(x,y,ignore,ignore,ignore)=marble;
        next_marble_index[x][y]=(int)(next_marbles.size())-1;
    }
    else{//해당 x,y좌표에 이미 누가 들어있어
        next_marbles[idx]=collide(next_marbles[idx],marble);
        lastCollisionTime=curTime;
    }
}

void simulate(){
    //모든 구슬을 한 칸씩 움직이는 시뮬레이션을 반영
    for(int i=0;i<(int)marbles.size();i++){
        Marble next_marble = move(marbles[i]);
        pushNextMarble(next_marble);
    }
    marbles=next_marbles;

    for(int i=0;i<(int)next_marbles.size();i++){
        int x,y;
        tie(x,y,ignore,ignore,ignore)=next_marbles[i];
        next_marble_index[x][y]=-1;
    }
    next_marbles.clear();
}

int main(){
    mapper['U'] = 0;
    mapper['R'] = 1;
    mapper['L'] = 2;
    mapper['D'] = 3;
    cin>>t;

    for(int i = 0; i <= COORD_SIZE; i++)
         for(int j = 0; j <= COORD_SIZE; j++)
            next_marble_index[i][j] = -1;//처음에는 전혀 채워지지 않음
    
    while(t--){
        lastCollisionTime=-1;
        marbles.clear();
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            int x,y,w;
            char d;
            cin>>x>>y>>w>>d;
            x*=2;y*=2;

            x+=OFFSET;y+=OFFSET;
            marbles.push_back(make_tuple(x,y,w,mapper[d],i));
        }

        for(int i=1;i<=COORD_SIZE;i++){
            curTime=i;
            simulate();
        }
        cout<<lastCollisionTime<<endl;
    }
    return 0;
}