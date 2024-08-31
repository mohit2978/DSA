import java.util.*;
import java.io.*;
class Solver{
	public int solve(int[] arr,int n){
       	int[] dp=new int[n];
       	dp[0]=0;
       	dp[1]=Math.abs(arr[1]-arr[0]);
       	for(int i=2;i<n;i++){
       		int v1=Math.abs(arr[i]-arr[i-1])+dp[i-1];
       		int v2=Math.abs(arr[i]-arr[i-2])+dp[i-2];
       		dp[i]=Math.min(v1,v2);
       	}
       	return dp[n-1];
       }

}
public class test{

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
		Solver solver=new Solver();
		System.out.println("Please enter input");
		int testCases=sc.nextInt();
		for(int t=1;t<=testCases;t++){
			int n=sc.nextInt();
            int [] arr=new int[n];
            for(int i=0;i<n;i++){
            	arr[i]=sc.nextInt();
            }
            System.out.println(solver.solve(arr,n));
		}
	}
}