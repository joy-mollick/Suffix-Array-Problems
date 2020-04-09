/*
Think about this aaaa string , how much unique duplicate substrings can be here 
This will be like in suffix array in serially 

lcp[i] = 1 = a
lcp[i] = 2 = aa
lcp[i] = 3 =aaa
lcp[i] =-1 =aaaa

Initial res=0;
Initial base =0;
Here , when aa that means it can produce two substrings which can occur next substring so keep it at base ,base=2(lcp[i]),res+=(lcp[i]-base)
and iterate the next lcp, so for aaa now lcp[i] is 3 that means this three a,aa,aaa substrings will occur more than one take 
this three !! No , think here a,aa substring has been already occured , our base is two so here new substring occuring more than one is 
only one (aaa) so now add lcp[i]-base =1. and now base=lcp[i] (3) ,so total res is 2+1 = 3 total three unique substrings which has occured more than one 
*/
#include <bits/stdc++.h>

using namespace std;

/// suffix array build an array and sort suffixes according lexicographically and keep its starting index in logn.nlogn`=n(logn)^2

string s;

const int mx=100005;

struct suffix
{
    int index;
    int rank[2];
};

int inv_suffixarray[mx];
int lcp[mx];
int suffixarray[mx];
struct suffix suffixes[mx];
int ind[mx];

bool comp(struct suffix a,struct suffix b)
{
    if(a.rank[0]==b.rank[0])
    {
        return (a.rank[1]<b.rank[1]);
    }
    return (a.rank[0]<b.rank[0]);
}

void lcp_construct(int n)
{
    ///int inv_suffixarray[n]={0};
    ///int lcp[n]={0};
    int pref=0;
    for(int i=0;i<n;i++) inv_suffixarray[suffixarray[i]]=i;/// get sorting index of suffixarray

    for(int i=0;i<n;i++)
    {
        int pos_in_suffixarray=inv_suffixarray[i];
        if(pos_in_suffixarray==n-1) /// there is no adjacent suffix in the suffixarray
        {
            pref=0;
            continue;
        }
        int next_pos=suffixarray[pos_in_suffixarray+1];
        /// i - is current suffix's starting position in string s
        /// next_pos is next suffix's current position in string s
        while(i+pref<n && next_pos+pref<n && s[i+pref]==s[next_pos+pref])
            pref++;

        lcp[pos_in_suffixarray]=pref;

        if(pref>0) pref--;/// obviously next pref will be at least pref-1
    }

    ///return lcp;/// lcp array
}

long long suffix_array_construct()
{
    int n=s.length();
    ///struct suffix suffixes[n];
    ///int ind[n];
    for(int i=0;i<n;i++)
    {
        suffixes[i].index=i;
        suffixes[i].rank[0]=(int)(s[i]);
        suffixes[i].rank[1]=(i+1<n)?(int)(s[i+1]):-1;/// INT_MAX for finding lowest one with same sort_index
    }
    sort(suffixes,suffixes+n,comp);
    for(int k=4;k<2*n;k=k*2) /// It will take O(logn) time
    {
        int rank=0;/// initialize rank is obviously zero
        int prev_rank=suffixes[0].rank[0];/// It alltime keep rank of previous which will be compared with current rank
        suffixes[0].rank[0]=rank;
        ind[suffixes[0].index]=0;/// It will be used to get the rank of suffix start with ith index for assigning next rank

        for(int i=1;i<n;i++)
        {
            if(suffixes[i].rank[0]==prev_rank && suffixes[i].rank[1]==suffixes[i-1].rank[1])/// Here rank is changed,rank is updated
            {
                prev_rank=suffixes[i].rank[0];
                suffixes[i].rank[0]=rank;
            }
            else
            {
                prev_rank=suffixes[i].rank[0];
                suffixes[i].rank[0]=++rank;
            }
            ind[suffixes[i].index]=i;
        }
        /// updating next rank
        for(int i=0;i<n;i++)
        {
            int indx_of_k_2_th_char=suffixes[i].index+k/2;/// it will take all time cover k characters beacause already two charcters sort by sort function
            suffixes[i].rank[1]=indx_of_k_2_th_char<n?suffixes[ind[indx_of_k_2_th_char]].rank[0]:-1;
        /// assign that suffix's first rank ,because that is also updated according to k/2 characters already ,now it will be sorted according to k characters
        }
        sort(suffixes,suffixes+n,comp);
    }
    ///int suffixarray[n];
    for(int i=0;i<n;i++) {suffixarray[i]=suffixes[i].index;}
    lcp_construct(n);
            long long ret = 0, base = 0;
        lcp[n] = -1;
        for(int i = 1; i <=n; i++) {
            if(lcp[i]<lcp[i-1])
                {ret += lcp[i-1] - base, base = lcp[i];}
        }
        return ret;
}

int main()

{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string a;
    while(cin>>a && a!="*"){
    memset(suffixes,0,sizeof(suffixes));
    memset(lcp,0,sizeof(lcp));
    memset(ind,0,sizeof(ind));
    memset(suffixarray,0,sizeof(suffixarray));
    memset(inv_suffixarray,0,sizeof(inv_suffixarray));
    s=a;
    long long ans=suffix_array_construct();
    ///tot=tot-ans;
    cout<<ans<<endl;
    }
    return 0;
}
