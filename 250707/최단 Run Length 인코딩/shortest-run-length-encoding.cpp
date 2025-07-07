#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>

using namespace std;

string runEncoding(string & s,int shift){
    string cs="";
    int len = s.size();
    //string cs(len, ' '); // 길이가 len이고, 공백으로 초기화
    //cout<<"shift: "<<shift<<endl;
    for(int i=0;i<len;i++){
        int mx=(i+len-shift)%len;
        cs.push_back(s[mx]);
        //cout<<"mx: "<<mx<<endl;
    }
    //cout<<"cs: "<<cs<<endl;
    return cs;
}

int solution(string &cs){
    string es="";
    char c=cs[0];
    int cnt=1;

    if(cs.size()==1) {
        es.push_back(c);
        es.push_back(cnt+'0');
        return es.size();
    }

    for(int i=1;i<cs.size();i++){
        if(c==cs[i]) cnt++;
        else {
            es.push_back(c);
            es.push_back(cnt+'0');
            cnt=1;
            c=cs[i];
        }
        if(i == cs.size()-1){
            es.push_back(c);
            string s_cnt=to_string(cnt);
            //cout<<"cnt: "<<cnt<<','<<to_string(cnt)<<endl;
            for(int i=0;i<s_cnt.size();i++) es.push_back(s_cnt[i]);
            //es.push_back(to_string(cnt));
        }
    }
    //cout<<"es: "<<es<<endl;
    return es.size();
    
}

int main(){
    string s;
    cin>>s;
    int ans=INT_MAX;
    for(int i=0;i<=s.size();i++){
        string cs=runEncoding(s,i);
        ans = min(ans,solution(cs));
    }
    cout<<ans<<'\n';
    return 0;
}