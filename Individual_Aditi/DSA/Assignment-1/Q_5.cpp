#include <bits/stdc++.h>

using namespace std;


bool poss(vector<int>&v, int mid, int c){
    
    int n = v.size();
    int last = v[0];
    int count = 1;
    
    for(int i=1;i<n;i++){
        if(last+mid <= v[i]){
            last = v[i];
            count++;
        }
        
        if(count>=c){
            return true;
        }
    }
    return false;
    
    
}
int main() {
    
    int t,n,c;
    cin>>t;
    while(t>0){
        cin>>n>>c;
        vector<int>v(n);
        for(int i=0;i<n;i++){
            cin>>v[i];
        }
        sort(v.begin(), v.end());
        int start=1;
        int end = 1e9;
        while(start<end){
            
            int mid = (start+end+1)/2;
            if(poss(v, mid, c)){
                start = mid;
            }
            else{
                end = mid-1;
            }
            
        }
        cout<<start<<"\n";
        t--;
    }
    
}
