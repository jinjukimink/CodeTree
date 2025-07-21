#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>

using namespace std;
vector<pair<int,int>>vp;//<an,bn>
int n,m;
vector<int>selected;
vector<int>canGo;
int result=INT_MAX;
int H=0;

void input(){
    cin>>n>>m;
    vp.resize(m);
    canGo.resize(n+1);
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        vp[i]=make_pair(a,b);//세로줄, 가로줄(높이)
        H=max(H,b);

    }
}

vector<vector<bool>>makeLadders(){
    vector<vector<bool>>ladders(H+1,vector<bool>(n+1));//높이*세로줄
    for(int i=0;i<selected.size();i++){
        auto[x,h] = vp[selected[i]];
        ladders[h][x]=true;
    }
    return ladders;
}


vector<int> move(){
    //현재 selected={0,1,2,4};
    vector<vector<bool>>ladders=makeLadders();
    vector<int>tmpCanGo(n+1);

    for(int start=1;start<=n;start++){
        int pos=start;
        for(int i=1;i<=H;i++){//높이
            if(ladders[i][pos]) pos++;
            else if(ladders[i][pos-1]) pos--;
        }
        tmpCanGo[start]=pos;
    }
    return tmpCanGo;
}

void makeCombi(int size,int st){
    //cout<<"size: "<<size<<endl;
    if(size==m){//처음 시작할 때
        canGo = move();//첫 값은 해줘야지
        return;
    }
    if(selected.size()==size){
        //처리: 여기까지 오면 m개가 뽑혔다는 거임
        vector<int>tmpCanGo = move();
        if(canGo==tmpCanGo){//결과값이 같아야 함.
            //cout<<"단 한번도 결과값이 같은 적이 없니?\n";
            result=min(result,size);
        }
        return;//exit()하면 안되나? 왜냐면 결과값이 같으면 더이상 다른 경우의 수를 볼 필요가 없음..
    }
    for(int i=st;i<m;i++){
        selected.push_back(i);
        makeCombi(size,i+1);
        selected.pop_back();
    }
}

int main(){
    input();
    for (int i = 0; i < m; i++) selected.push_back(i);
    canGo = move();
    selected.clear();
    //처음에 모든 가로줄을 고려한 결과

    for(int i=m-1;i>=0;i--){
        makeCombi(i,0);//i개를 뽑아볼게요.
    }
    if (result == INT_MAX) cout << m << endl; // 모든 가로줄 필요
    else cout<<result<<endl;
    return 0;
}
//시간복잡도: n 개중에 i개를 뽑아야 함(i=1,2,3,4,~,m-1) 모든 경우의 수를 뽑아 봐야 함.
//(for int i=1;i<=(m-1);i++) nCi를 해야 함//=O((m-1)*)
