import java.util.*;
import java.io.*;
//atcoder pe file vala hta dia kro yaar input.txt output.txt
public class Main{
    public static long solve(long[] arr,int n,int k){
        long[] dp=new long[n];
        Arrays.fill(dp,Integer.MAX_VALUE);
        dp[0]=0;
        dp[1]=Math.abs(arr[1]-arr[0]);
        for(int i=2;i<n;i++){
            for(int j=i-1;j>=0 && j>=i-k;j--){
                long v1=Math.abs(arr[i]-arr[j])+dp[j];
                dp[i]=Math.min(dp[i],v1);
                //System.out.println(i+" "+j+" "+dp[i]+" "+v1);
           }
        }
        return dp[n-1];
       }

    public static void main(String[] args){

         Scanner sc = new Scanner(System.in);
         if (System.getProperty("ONLINE_JUDGE") == null) {
            // Try block to check for exceptions
            try {
                System.setOut(new PrintStream(new FileOutputStream("output.txt")));
                sc= new Scanner(new File("input.txt"));
            }
            catch (Exception e) {
            }
        }
            int n=sc.nextInt();
            int k=sc.nextInt();
            long [] arr=new long[n];
            for(int i=0;i<n;i++){
                arr[i]=sc.nextLong();
            }
            System.out.println(solve(arr,n,k));
        
    }
}