#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;


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

void insert (vector<long long>& a, long long x, long long& count){
    a[count] = x;
    long long i = count;
    count++;

    while(i > 0){
        long long temp = (i-1)/2;
        if(a[temp] >= a[i]){
            break;
        }
        swap(a[temp], a[i]);
        i = temp;
    }
}
//n k
//o(k) по памяти выводит k самых маленьких
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;
    vector<long long> a(k);
    long long x;
    long long count = 0;
    for(long long i=0;i<n;i++){
        cin >> x;
        if(i>=k){
            if(a[0]>x){
                a[0] = x;
                siftdown(a, 0, count);
                //count--;
            }
        }
        else{
            insert(a, x, count);
        }
    
    }
    cout<<"\n";
    for(long long i = k/2 - 1;i>=0;i--){
        siftdown(a, i, k);
    }
    
    for(long long end = k - 1; end >= 1; --end){
        swap(a[0], a[end]);
        siftdown(a, 0, end);
    }
    
    for(long long i=0;i<k;i++){
        cout<<a[i]<<" ";
    }

    
    return 0;
}