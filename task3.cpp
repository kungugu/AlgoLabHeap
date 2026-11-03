#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <string>
using namespace std;

void siftup(vector<long long>& a, long long i){
    long long temp = 0;
    while(i>0 and a[i] > a[(i-1)/2]){
        temp = a[i];
        a[i] = a[(i-1)/2];
        a[(i-1)/2] = temp;
        i = (i - 1) / 2;
    }
}

void insert (vector<long long>& a, long long x, long long& count){
    a[count] = x;
    long long i = count;
    count++;
    siftup(a, count-1);
}

void siftdown (vector<long long>& a, long long i, long long count){
    while(true){
    long long left = 2*i+1, right = 2*i+2;
    long long great = i;
    if(left < count and a[left] > a[great]){
        great = left;
    }
    if(right < count and a[right] > a[great]){
        great = right;
    }
    if(great == i){
        break;
    }
    else{
        swap(a[i], a[great]);
        i = great;
    }
    }
}

void deletei(vector<long long>& a, long long& count, long long i){
    a[i]=a[count-1];
    count--;
    if(i<count){
    siftup(a, i);
    siftdown(a, i, count);
    }
}

void getmax(vector<long long>& a, long long& count){
   cout<<a[0]<<"\n"; 
   deletei(a, count, 0);
}

void getmin(vector<long long>& a, long long& count){
    long long minpr = a[count/2];
    long long indx = count / 2;
    for(long long j = count/2; j<count;++j){
        minpr = min(minpr, a[j]);
        if(a[j]<a[indx]){
            indx = j;
        }
    }
   cout<<a[indx] << '\n'; 
   deletei(a, count, indx);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    long long count = 0;
    cin >> n;
    vector<long long> a(n);
    long long x=0;
    string s;
    for(long long i=0;i<n;i++){
        cin>>s;
        if(s[0] == 'I'){
            x = 0;
            for(long long j = 7; j<s.length()-1;++j){
                x+=s[j]-'0';
                if(j!=s.length()-2){
                    x*=10;
                }
            }
            insert(a, x, count);
        }
        else if(s[5] == 'x'){
           getmax(a, count); 
        }
        else{
            getmin(a, count);
        }
    }
   
    
    return 0;
}