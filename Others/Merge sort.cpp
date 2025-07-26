#include <bits/stdc++.h>
using namespace std;
const int N=1e5;
int arr[N]={0},b[N]={0};
void merge(int low,int mid,int high){
    int i=low,j=mid+1,k=low;//i,j作为两个指针循环arr[],k循环b[]
    while(i<=mid&&j<=high){
        if(arr[i]<arr[j]) b[k++]=arr[i++];
        else b[k++]=arr[j++];
    }
    while(i<=mid)
        b[k++]=arr[i++];
    while(j<=high)
        b[k++]=arr[j++];
    for(int i=low;i<=high;++i)
        arr[i]=b[i];
}
void merge_sort(int begin,int end){
    if(begin>=end) return;
    int mid=(begin+end)>>1;
    merge_sort(begin,mid); merge_sort(mid+1,end);
    merge(begin,mid,end);
}
int main()
{
    int n; cin>>n;
    for(int i=1;i<=n;++i) scanf("%d",arr+i);
    merge_sort(1,n);
    for(int i=1;i<=n;++i) printf("%d ",arr[i]);
    return 0;
}