import java.util.*;
import java.io.*;
//atcoder pe file vala hta dia kro yaar input.txt output.txt
public class Main{
    public static long solve(long[] arr,int n){
        long[] dp=new long[n];
        dp[0]=0;
        dp[1]=Math.abs(arr[1]-arr[0]);
        for(int i=2;i<n;i++){
            long v1=Math.abs(arr[i]-arr[i-1])+dp[i-1];
            long v2=Math.abs(arr[i]-arr[i-2])+dp[i-2];
            dp[i]=Math.min(v1,v2);
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
            long [] arr=new long[n];
            for(int i=0;i<n;i++){
                arr[i]=sc.nextLong();
            }
            System.out.println(solve(arr,n));
        
    }
}