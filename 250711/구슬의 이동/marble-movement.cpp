#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
#include<tuple>

using namespace std;

map<pair<int,int>,vector<tuple<pair<int,int>,int,int>>>myMap;
map<char,pair<int,int>>dirs;
map<char,pair<int,int>>rdirs;
int n,m,t,k;

void initDir(){
    dirs['L']={0,-1};
    rdirs['L']={0,1};

    dirs['R']={0,1};
    rdirs['R']={0,-1};

    dirs['U']={-1,0};
    rdirs['U']={1,0};

    dirs['D']={1,0};
    rdirs['D']={-1,0};
}

void input(){
    initDir();
    cin>>n>>m>>t>>k;
    for(int i=0;i<m;i++){
        int r,c,v;
        char d;
        cin>>r>>c>>d>>v;
        myMap[{r,c}].push_back({dirs[d],v,i+1});
    }
}

tuple<int, int, pair<int,int>,int, int>move(int r,int c, pair<int,int>dxdy,int v,int id){
    int curX=r;
    int curY=c;
    auto[dx,dy]=dxdy;

    // for(int i=1;i<=v;i++){
    //     if(curX==1||curY==1||curX==n||curY==n){//시작 하자마자 벽이면
    //         dx*=-1;
    //         dy*=-1;
    //     }
    //     curX+=dx;
    //     curY+=dy;
    //     // if(curX==1||curY==1||curX==n||curY==n){//벽에 부딪히는 순간 방향을 바꿔 그리고 계속 전진
    //     //     dx*=-1;
    //     //     dy*=-1;
    //     // }

    // }

    for(int i=1;i<=v;i++){
        if (curX+dx < 1 || curX+dx > n) dx *= -1;
        if (curY+dy < 1 || curY+dy > n) dy *= -1;

        curX += dx;
        curY += dy;
    }

    return make_tuple(curX,curY,make_pair(dx,dy),v,id);
}

bool compare(const tuple<pair<int,int>,int,int>& a, const tuple<pair<int,int>, int,int>& b) {
    if(get<1>(a)!=get<1>(b)) return get<1>(a)>get<1>(b);//속도가 빠른
    return get<2>(a) > get<2>(b);
}

void check(int x,int y,map<pair<int,int>,vector<tuple<pair<int,int>,int,int>>>&map){
    if(map[{x,y}].size()<=k) return;

    sort(map[{x,y}].begin(),map[{x,y}].end(),compare);
    int cnt=map[{x,y}].size()-k;//
    while(cnt--){
        map[{x,y}].pop_back();
    }
}

int solution(map<pair<int,int>,vector<tuple<pair<int,int>,int,int>>>&map){
    int cnt=0;
    for(auto [key,value]:map){
        cnt+= value.size();
    }
    return cnt;
}

int main(){
    input();
    while(t--){
        map<pair<int,int>,vector<tuple<pair<int,int>,int,int>>> tmpMap;
        for(auto[key,value]:myMap){
            auto[x,y]=key;
            for(auto [dir,vel,id]:value){
                auto[nx,ny,nd,nv,nid]=move(x,y,dir,vel,id);
                tmpMap[{nx,ny}].push_back({nd,nv,nid});
            }
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                check(i,j,tmpMap);
            }
        }
        myMap=tmpMap;
    }

    cout<<solution(myMap)<<'\n';

}


