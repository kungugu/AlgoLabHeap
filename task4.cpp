#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <string>
using namespace std;

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
    while(i>0 and a[i].first < a[(i-1)/2].first) {
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

    long long n, m; //количество ядер и количество задач
    //Вторая строка содержит n целых чисел a1,a2,…,an​ — ставки ядер (рублей в минуту), все различные.
    //Далее следуют m строк: в j-й строке заданы два целых числа  (время прибытия и сколько действует)
    long long count = 0, countpair = 0, ans = 0;
    cin >> n >> m;
    vector<long long> a(n); 
    vector<pair<long long, long long>> b(n); // время когда освободится, цена
    long long x=0;
    for(long long i=0;i<n;i++){
        cin>>x;
        insert(a, x, count);//строим кучу из ядер
    }
    long long start, timeof;
    for(long long i=0;i<m;i++){
        cin>>start>>timeof;
        while(countpair>0 and b[0].first <= start){ //если корневая задача закончилась
            insert(a, b[0].second, count);
            deleteipair(b, countpair, 0);
        }
        if(count!=0){//если есть свободные то используем
            ans+=a[0]*timeof;
            insertpair(b, {start + timeof, a[0]}, countpair);
            deletei(a, count, 0);
        }
    }
    cout<<ans<<"\n";
    return 0;
}