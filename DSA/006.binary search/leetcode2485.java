class Solution {
    public int pivotInteger(int n) {
        int s=(n*(n+1))/2;
        int lo=1;
        int hi=n;
        while(lo<=hi){
            int x=(lo+hi)/2;
            int s1=(x*(x+1))/2;
            int s2=s-s1+x;
            if(s1==s2) return x;
            else if(s1<s2) lo=x+1;
            else hi=x-1;
        }
        return -1;
        
    }
}