class Solution {
  //own implemataion
public:
    int minCapability(vector<int>& nums, int k) {
      
        int lo=1;
        int hi=1e9;
        while(lo<=hi){
            int mid=(lo+hi)>>1;
            int cnt=0;
            for(int i=0;i<nums.size();i++){
                if(nums[i]<=mid){
                    i++;
                    cnt++;
                }
            }
            if(cnt>=k) hi=mid-1;
            else lo=mid+1;
        }
         return lo;
    }
};