#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long t;
    cin>>t;
    while(t--){
        long long x,y,z;
        cin>>x>>y>>z;
        long long n = x+y+z;
        if(x>=y and x>=z){
            while(n--){
                cout<<"P";
            }
            cout<<endl;
        }
        else if(y>=x and y>=z){
            while(n--){
                cout<<"R";
            }
            cout<<endl;
        }
        else if(z>=y and z>=x){
            while(n--){
                cout<<"S";
            }
            cout<<endl;
        }
    }
    return 0;
}