#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long ll;
const double eps=1e-6;
const ll modn = 1e9+7;

ll a[100];
ll sa[10]={0,1,2,4,6};
ll solve(ll n){
    if(n<=4)
        return sa[n];
    ll pre=2;
    ll ans=0;
    for(int i=1;pre<=n;i++){
        ans+=a[i];
        ans%=modn;
        pre*=2;
    }
    while(pre>n)
        pre/=2;
    n-=pre;
    if(n==0)
        return ans;
    ans+=((n%modn)*((pre/2)%modn))%modn;
    ans%=modn;
    //cout<<"1111   "<<ans<<endl;
    ans+=solve(n+1);
    ans-=1;
    ans%=modn;
    ans+=modn;
    ans%=modn;
    return ans;

}

int main(){
    a[1]=2;
    a[2]=4;
    for(int i=3;i<65;i++){
        a[i]=a[i-1]*2;
        a[i]%=modn;
        ll temp=(1ll<<(i-2));
        a[i]+=(temp%modn+1+temp%modn*2%modn)%modn*((temp/2)%modn);
        a[i]%=modn;
        //cout<<a[i]<<endl;
    }

    int t;
    scanf("%d",&t);
    while(t--){
        ll n;
        scanf("%lld",&n);
        cout<<solve(n)%modn<<endl;
    }
    return 0;
}

