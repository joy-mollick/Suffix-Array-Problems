#include <bits/stdc++.h>

    using namespace std;


int exact_pos;
const int mx=100001;
char s[mx];
char t[mx];

struct suffix
{
    int index;
    int rank[2];
};

struct suffix suffixes[mx];

bool comp(struct suffix a,struct suffix b)
{
    if(a.rank[0]==b.rank[0])
    {
        return (a.rank[1]<b.rank[1]);
    }
    return (a.rank[0]<b.rank[0]);
}

void suffix_array_construct()
{
    int n=strlen(s);
    for(int i=0;i<n;i++)
    {
        suffixes[i].index=i;
        suffixes[i].rank[0]=(int)s[i];
        suffixes[i].rank[1]=(i+1<n)?(int)(s[i+1]):-1;
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
    /*
    int *suffixarray = new int[n];
    for(int i=0;i<n;i++) {suffixarray[i]=suffixes[i].index;}*/
}


int main()

{
   /// ios_base::sync_with_stdio(false);
   /// cin.tie(NULL);
   /// cout.tie(NULL);
    int tc,m;
    scanf("%d",&tc);
    while(tc--){
    scanf("%s",s);
    int n=strlen(s);
    suffix_array_construct();
    scanf("%d",&m);
    while(m--)
    {
        scanf("%s",t);
        int low=0,high=n-1,mid;
        bool ans=false;
        int q=strlen(t);
        while(low<=high)
        {
            mid=(low+high)>>1;
            int cs=strncmp(s+suffixes[mid].index,t,q);
            if(cs==0)
            {
                ans=true;
                break;
            }
            else if(cs>0)
            {
                high=mid-1;
            }
            else
            {
                low=mid+1;
            }
        }
        if(ans)
                printf("y\n");
            else
                printf("n\n");
    }

    }
    return 0;
}

