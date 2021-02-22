#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

void distance(vector<float>& f, vector<float>& d){
    int n = d.size();
    vector<int> v(n);
    vector<float> z(n+1);
    int k=0;
    v[0]=0;
    z[0]=-float('inf');
    z[1]=float('inf');
    for(int q=1;q<n;q++){
        float s=((f[q]+q*q)-(f[v[k]]+v[k]*v[k]))/(2*q-2*v[k]);
        while(s<=z[k]){
            k--;
            s=((f[q]+q*q)-(f[v[k]]+v[k]*v[k]))/(2*q-2*v[k]);
        }
        k++;
        v[k]=q;
        z[k]=s;
        z[k+1]=float('inf');
    }
    k=0;
    for(int q=0;q<=n-1;q++){
        while(z[k+1]<q){
            k++;
        }
        d[q]=pow(q-v[k],2)+f[v[k]];
    }
}


int main(){
    vector<vector<int>> dists{{0,0,0,0,0,0},
                              {0,1,1,1,0,0},
                              {0,1,0,1,0,0},
                              {0,1,0,1,0,0},
                              {0,1,1,1,0,0},
                              {0,0,0,0,0,0}};
    vector<vector<float>> dp(dists.size(), vector<float>(dists[0].size()));
    // init dp
    for(int i=0;i<dp.size();i++){
        for(int j=0;j<dp[0].size();j++){
            if(dists[i][j]==1){
                dp[i][j]=0;
            }else{
                dp[i][j]=float('inf');
            }
        }
    }
    vector<float> f(max(dp.size(), dp[0].size()));
    vector<float> d(dp[0].size());
    for(int i=0;i<dp.size();i++){
        for(int j=0;j<dp[0].size();j++){
            f[j]=dp[i][j];
        }
        distance(f, d);
        for(int j=0;j<dp[0].size();j++){
            dp[i][j]=d[j];
        }
    }
    d.resize(dp.size());
    for(int j=0;j<dp[0].size();j++){
        for(int i=0;i<dp.size();i++){
            f[i]=dp[i][j];
        }
        distance(f,d);
        for(int i=0;i<dp.size();i++){
            dp[i][j]=d[i];
        }
        
    }
    for (int i=0; i<dp.size(); i++){
        for (int j=0;j<dp[0].size(); j++){
            cout<<sqrt(dp[i][j])<<' ';
        }
        cout<<endl;
    }
    return 0;
}
