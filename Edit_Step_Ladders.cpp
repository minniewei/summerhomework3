#include <bits/stdc++.h>
#define N 25005
using namespace std;
vector<string>strnum;
map<string,int>mp;
int dp[N];

string strChange(string str,int x){
    string src;
    for(int i=0;i<str.size();i++){
        if(i!=x)
            src.push_back(str[i]);
        else
            src.push_back('*');
    }
    return src;
}
string strAdd(string str,int x){
    string src;
    if(x==str.size()) {
        src = str + '*';
        return src;
    }
    for(int i=0;i<str.size();i++){
        if(i==x)
            src.push_back('*');
        src.push_back(str[i]);
    }
    return src;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    string str;
    while(getline(cin,str)){
        if(str.size()==0)
            break;
        strnum.push_back(str);
    }
    memset(dp,0, sizeof(dp));
    int ans=0;
    for(int i=0;i<strnum.size();i++){
        for(int j=0;j<strnum[i].size();j++){
            string src=strChange(strnum[i],j);
            if(mp.count(src)>0)
                dp[i]=max(dp[i],dp[mp[src]]+1);
            mp[src]=i;
            src=strAdd(strnum[i],j);
            if(mp.count(src)>0)
                dp[i]=max(dp[i],dp[mp[src]]+1);
            mp[src]=i;
        }
        string src=strAdd(strnum[i],strnum[i].size());
        if(mp.count(src)>0)
            dp[i]=max(dp[i],dp[mp[src]]+1);
        mp[src]=i;
        ans=max(ans,dp[i]+1);
    }
    cout<<ans<<endl;
    return 0;
}