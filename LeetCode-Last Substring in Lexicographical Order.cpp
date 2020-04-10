
/// All test case passed , here I would use O(n) construction of suffix array ,but I just changed my sort algorithm from nlogn to linear complexity 
/// You can Improve this solution by yourself

class Solution {
public:
     
struct suffix
{
    int index;
    int rank[2];
};
    static const int mx=400001;
    struct suffix temp[mx];
    struct suffix suffixes[mx];
    int ind[mx];

    int pos[mx];
    void LinearSort(int n,int index){
	int i;
	///struct suffix *temp=new struct suffix[n];
	memset(pos,0,sizeof(pos));
	for(i=0;i<n;++i){
		pos[suffixes[i].rank[index]+1]++;
	}
	for(i=1;i<mx;++i){
		pos[i]+=pos[i-1];
	}
	for(i=n-1;i>=0;i--){
		temp[pos[suffixes[i].rank[index]+1]-1]=suffixes[i];
		pos[suffixes[i].rank[index]+1]--;
	}
	for(i=0;i<n;++i){
		suffixes[i]=temp[i];
	}
	///free(temp);
	if(index==0){
	return;}
	else{
	LinearSort(n,index-1);}
}

    string lastSubstring(string s) {
         int n=s.length();
    for(int i=0;i<n;++i)
    {
        suffixes[i].index=i;
        suffixes[i].rank[0]=(s[i]-'a');
        suffixes[i].rank[1]=(i+1<n)?(s[i+1]-'a'):-1;/// INT_MAX for finding lowest one with same sort_index
    }
    LinearSort(n,1);
    for(int k=4;k<2*n;k=(k<<1)) /// It will take O(logn) time
    {
        int rank=0;/// initialize rank is obviously zero
        int prev_rank=suffixes[0].rank[0];/// It alltime keep rank of previous which will be compared with current rank
        suffixes[0].rank[0]=rank;
        ind[suffixes[0].index]=0;/// It will be used to get the rank of suffix start with ith index for assigning next rank

        for(int i=1;i<n;++i)
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
        for(int i=0;i<n;++i)
        {
            int indx_of_k_2_th_char=suffixes[i].index+k/2;/// it will take all time cover k characters beacause already two charcters sort by sort function
            suffixes[i].rank[1]=indx_of_k_2_th_char<n?suffixes[ind[indx_of_k_2_th_char]].rank[0]:-1;
        /// assign that suffix's first rank ,because that is also updated according to k/2 characters already ,now it will be sorted according to k characters
        }
      LinearSort(n,1);
    }
    
    int exact=n-1;
    int start_pos=suffixes[exact].index;
    return s.substr(start_pos,n-start_pos);
    }
};
