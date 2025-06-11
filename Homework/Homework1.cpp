#include<bits/stdc++.h>
using namespace std;

const int N=1e5;

int n,a[N],ans,max_num;

int main(){
    cin>>n;
    for (int i=0;i<n;i++) cin>>a[i];
    ans = a[0];
    max_num = a[0];
    for (int i=1;i<n;i++){
        max_num = max(max_num+a[i],a[i]);
        ans = max(ans,max_num);
    }
    cout<<ans<<endl;
    return 0;
}