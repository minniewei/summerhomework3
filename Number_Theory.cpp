#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define N 50000
vector <int> prime;
int IsNotPrime[N+10],prime_num=0;
void makeprime()
{
    for(int i=2;i<N;i++)
    {
        if(!IsNotPrime[i])
        {
            prime.push_back(i);
            prime_num++;
        }
        for(int j=0;j<prime_num&&prime[j]*i<=N;j++)
        {
            IsNotPrime[prime[j]*i]=1;
            if(i%prime[j]==0)
                break;
        }
    }
}
int NotRes(int n)
{
    int res1=n,res2=1;
    if(n==1)
        return 1;
    for(int i=0;i<prime_num&&n!=1;i++)
    {
        if(n%prime[i]==0)
        {
            res1=(res1/prime[i])*(prime[i]-1);n/=prime[i];
            int c=1;
            while(n%prime[i]==0)
            {
                n/=prime[i];
                c++;
            }
            res2*=c+1;
        }
    }
    if(n>1)
    {
        res1=(res1/n)*(n-1);
        res2*=2;
    }
    return res1+res2-1;
}
int main()
{
    int n;
    makeprime();
    cin.sync_with_stdio(false);
    while(cin>>n&&n)
    {
        cout<<n-NotRes(n)<<"\n";
    }
    return 0;
}