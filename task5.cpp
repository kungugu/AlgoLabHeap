#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <string>
using namespace std;
const long long L = 600;

void siftup(vector<long long>& a, long long i){
    long long temp = 0;
    while(i>0 and a[i] < a[(i-1)/2]){
        temp = a[i];
        a[i] = a[(i-1)/2];
        a[(i-1)/2] = temp;
        i = (i - 1) / 2;
    }
}

void siftuppair(vector<pair<long long, long long>>& a, long long i){
    long long temp = 0;
    while(i>0 and a[i].first < a[(i-1)/2].first){
        swap(a[i], a[(i-1)/2]);
        i = (i - 1) / 2;
    }
}

void insertpair (vector<pair<long long, long long>>& a, pair<long long, long long> x, long long& count){
    a[count] = x;
    long long i = count;
    count++;
    siftuppair(a, count-1);
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
    if(left < count and a[left] < a[great]){
        great = left;
    }
    if(right < count and a[right] < a[great]){
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

void siftdownpair (vector<pair<long long, long long>>& a, long long i, long long count){
    while(true){
    long long left = 2*i+1, right = 2*i+2;
    long long great = i;
    if(left < count and a[left].first < a[great].first){
        great = left;
    }
    if(right < count and a[right].first < a[great].first){
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

void deleteipair(vector<pair<long long, long long>>& a, long long& count, long long i){
    a[i]=a[count-1];
    count--;
    if(i<count){
    siftuppair(a, i);
    siftdownpair(a, i, count);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m; 
    char c;
    long long start;
    long long count = 0, countpair = 0, ans = 0;
    vector<long long> a(30000);
    vector<bool> used(30001, false);
    vector<long long> actualtime(30001);
    vector<pair<long long, long long>> b(80001); 
    for(long long i=0;i<30000;++i){
        insert(a, i+1, count);
    }
    while(cin>>start>>c){
        while(countpair>0 and b[0].first <= start) { 
            pair<long long, long long> p = b[0];
            deleteipair(b, countpair, 0);
            if (used[p.second] and actualtime[p.second] == p.first) {
                used[p.second] = false;
                insert(a, p.second, count);
            }
        }
        if (c == '+') {//добавляем во вторую кучу
            if(count!=0){
                insertpair(b, {start + L, a[0]}, countpair);
                used[a[0]] = true;
                actualtime[a[0]] = start + L;
                cout<<a[0]<<"\n";
                deletei(a, count, 0);
            }
        }  
        else {
            long long block;
            cin >> block;
            if(used[block]){
                actualtime[block] = start + L;
                insertpair(b, {start + L, block}, countpair);
                cout<<"+\n";
            }
            else{
                cout<<"-\n";
            }
        }
    }
    return 0;
}