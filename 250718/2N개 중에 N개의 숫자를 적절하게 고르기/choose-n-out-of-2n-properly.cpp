#include <iostream>
#include<cmath>
#include<vector>
#include<climits>

using namespace std;

int n;
int num[20];
vector<int>combi;
int totalSum=0;
int ans=INT_MAX;

void debugging(){
    for(int i=0;i<combi.size();i++){
        cout<<combi[i]<<' ';
    }
    cout<<endl;
}

int diff(){
    int combiSum1=0;
    for(int i=0;i<combi.size();i++){
        combiSum1+=num[combi[i]];
    }
    
    int combiSum2 = abs(totalSum-combiSum1);
    //cout<<"combiSum1: "<<combiSum1<<" combiSum2: "<<combiSum2<<endl;
    return abs(combiSum1-combiSum2);
}

void makeCombi(int st){
    if(combi.size()==(n)){
        //combi 벡터에 커플이 완성된 상태
        //debugging();
        ans=min(ans,diff());
        return;
    }
    //if(st > n-1) return; //굳이 같은 행위를 2번할 필요가 없음.
    for(int i=st;i<(2*n);i++){
        combi.push_back(i);
        makeCombi(i+1);
        combi.pop_back();
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < 2 * n; i++) {
        cin >> num[i];
        totalSum+=num[i];
    }
    //cout<<"totalSum: "<<totalSum<<endl;
    makeCombi(0);
    cout<<ans<<endl;

    // Please write your code here.

    return 0;
}
