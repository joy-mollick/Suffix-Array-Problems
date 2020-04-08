#include <bits/stdc++.h>

using namespace std;

/// suffix array build an array and sort suffixes according lexicographically and keep its starting index in logn.nlogn`=n(logn)^2

string s;
int exact_pos;

struct suffix
{
    int index;
    int rank[2];
};

bool comp(struct suffix a,struct suffix b)
{
    if(a.rank[0]==b.rank[0])
    {
        return (a.rank[1]<b.rank[1]);
    }
    return (a.rank[0]<b.rank[0]);
}

vector<int> lcp_construct(int suffixarray[],int n)
{
    vector<int>lcp(n,0);
    vector<int>inv_suffixarray(n,0);
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

    return lcp;/// lcp array
}

int suffix_array_construct()
{
    int n=s.length();
    struct suffix suffixes[n];
    for(int i=0;i<n;i++)
    {
        suffixes[i].index=i;
        suffixes[i].rank[0]=(s[i]-'a');
        suffixes[i].rank[1]=(i+1<n)?(s[i+1]-'a'):-1;/// INT_MAX for finding lowest one with same sort_index
    }
    sort(suffixes,suffixes+n,comp);
    int ind[n];
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
    int suffixarray[n];
    for(int i=0;i<n;i++) {suffixarray[i]=suffixes[i].index;}

     vector<int>lcp;

    lcp=lcp_construct(suffixarray,n);
    int ans=0;
    for(int i=0;i<n-1;i++)
    {
        if(suffixarray[i]<exact_pos && suffixarray[i+1]>exact_pos || (suffixarray[i]>exact_pos && suffixarray[i+1]<exact_pos)) ans=max(ans,lcp[i]);
    }

    return ans;
}

int main()

{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string a,b;
    int tc,m;
    cin>>tc;
    cin>>a;
    b=a;
    reverse(b.begin(),b.end());
    exact_pos=a.length();
    s=a+"$"+b;
    int ans=suffix_array_construct();
    cout<<ans<<endl;
    return 0;
}
