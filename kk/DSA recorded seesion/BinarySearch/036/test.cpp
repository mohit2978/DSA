#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll a[100000+1] = {0};
ll b[100000+1] = {0};
ll c[100000+1] = {0};
ll n  ; 
ll check(ll g){
    
    ll k1 = 0 ; 
    ll k5 = 0 ; 
    ll i = 1 ; 
    while(i<=n){
        
        if(a[i]<g){
            k1+=(g-a[i]);
        }
        else{
            k5+=(a[i]-max(g,b[i]));//RRRRR
        }
        
        i++;
    }
    
    if(k5>=k1){
        return true;
    }
    return false;
}
int main() {
    cin>>n ; 
    ll limit = 0 ; 
    ll i = 1 ; 
    while(i<=n){
        cin>>a[i];
        limit = max(limit,a[i]);
        i++;
    }
    
    i = 1 ; 
    while(i<=n){
        cin>>b[i];
        i++;
    }
    
    i = 1 ; 
    while(i<=n){
        cin>>c[i];
        i++;
    }
    
    ll r = 0 ;
    i = 1 ; 
    while(i<=limit){
        
        if(check(i)==false){
            r = i - 1 ; 
            break ; 
        }
        
        i++;
    }
    
    cout<<r<<' '; 
    ll g = r ; 
    vector <pair<ll,ll>> G ; 
    i = 1 ; ll k8 = 0 ;
    ll k1 = 0 ;
    while(i<=n){
        if(a[i]>g){
        k8=(a[i]-max(g,b[i]));//RRRRR
        G.push_back({c[i],k8});
        }
        else{
            k1 = k1 + (g-a[i]);
        }
        i++;
    }
    ll TopG = 0 ; 
    sort(G.begin(),G.end());
    ll v = G.size();
    i = 0 ; ll u = 0 ; 
    while(i<v && u==0){
        k1 = k1 - G[i].second ; 
        if(k1<=0){ u = 1 ; 
    
            k1 = k1 + G[i].second; 
            (TopG = TopG + (G[i].first*k1));
        }
        else{
            (TopG = TopG + (G[i].first*G[i].second));   
        }
        
        i++;
    }
    
    cout<<TopG ; 
    
    
    return 0 ;
}