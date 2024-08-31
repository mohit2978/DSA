import java.util.*;
import java.io.*;

public class test{
	//https://codeforces.com/problemset/problem/1833/B
	public static void print (int [] a,int n){
		for(var v :a){
			System.out.print(v+" ");
		}
		System.out.println();
	}
    public static void solve(int[][] a,int [] b,int k,int n){
       Arrays.sort(a,(v1,v2)->(v1[0]-v2[0]));
       Arrays.sort(b);
       int [] res=new int[n];
       for(int i=0;i<n;i++){
       	int idx=a[i][1];
       	res[idx]=b[i];
       }
	   print(res,n);
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
		//System.out.println("Please enter input");
		int testCases=sc.nextInt();
		for(int t=1;t<=testCases;t++){
			int n=sc.nextInt();
			int k=sc.nextInt();
			int [][] a=new int[n][2];
			int[] b=new int[n];
			for(int i=0;i<n;i++){
				a[i][0]=sc.nextInt();
				a[i][1]=i;
			}
			for(int i=0;i<n;i++){
				b[i]=sc.nextInt();
			}
			solve(a,b,k,n);
		}
	}
}