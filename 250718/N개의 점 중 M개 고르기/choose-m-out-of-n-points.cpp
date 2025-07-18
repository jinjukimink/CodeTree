#include <iostream>
#include<vector>
#include<climits>
#include<algorithm>

using namespace std;

int n, m;
vector<pair<int,int>>ps;

//점 m개를 뽑아서 그 중 거리가 가장 먼 두 점 사이의 거릿값이 최소
//1. 일단 n개 중에 m개를 뽑아야 겠지
//2. m개 중에서 거리가 가장 먼 두 점을 찾아야겠지
vector<int>combi;
vector<int>pick2;
int dist=INT_MIN;
int ans=INT_MAX;

void findFar(int st){
    //combi벡터 사용 ex){1,2};

    if(pick2.size()==2){//2개를 뽑았을 거 아니야
        // for(int i=0;i<pick2.size();i++) cout<<pick2[i]<<' ';
        // cout<<endl;
        auto[x1,y1]=ps[pick2[0]];
        auto[x2,y2]=ps[pick2[1]];
        //cout<<abs(x2-x1)<<','<<abs(y2-y1)<<endl;
        dist = max(dist,(abs(x2-x1)*abs(x2-x1))+(abs(y2-y1)*abs(y2-y1)));
        //cout<<"dist: "<<dist<<endl;
        return;

    }
    for(int i= st;i < combi.size();i++){//2
        pick2.push_back(combi[i]);
        findFar(i+1);
        pick2.pop_back();
    }
}


void makeCombi(int st){
    if(combi.size()==m){
        dist=0;
        findFar(0);
        ans = min(ans,dist);
        //cout<<"ans: "<<ans<<endl;
        return;
    }
    for(int i=st;i<n;i++){
        combi.push_back(i);
        makeCombi(i+1);
        combi.pop_back();
    }
}

int main() {
    cin >> n >> m;
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        ps.push_back({x,y});
    }
    makeCombi(0);
    cout<<ans<<endl;

    return 0;
}
