#include <bits/stdc++.h>
using namespace std;
const int N=1e5+3;
long long arr[N];
//对于洛谷P1177题,可能key不能取为l
//建议使用并归排序或者参考https://oi-wiki.org/basic/quick-sort/
void quicksort(int begin,int end)
{
    if(begin>=end)return;
    int l=begin,r=end;
    int key=l;
    while(l<r){
        while(arr[r]>=arr[key]&&r>l){
            --r;
        }
        while(arr[l]<=arr[key]&&r>l){
            ++l;
        }
        swap(arr[l],arr[r]);
    }
    swap(arr[key],arr[r]);
    //key=r;//此时r右边的数>key,左边的数(包括r)<=key
    quicksort(begin,l-1);quicksort(l+1,end);
    return;
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>arr[i];
    random_shuffle(arr+1,arr+1+n);//随机排列数组，防止通过特殊数据卡O(n^2)
    quicksort(1,n);
    printf("%d",arr[1]);
    for(int i=2;i<=n;++i)printf(" %d",arr[i]);
    printf("\n");
    return 0;
}