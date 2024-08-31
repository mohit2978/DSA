import java.util.*;
import java.io.*;

public class test{
    public static void solve(int t){
	   //	System.out.println("In function solve t val is "+ t);
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
            finally{
            	sc.close();
            }
        }
		//System.out.println("Please enter input");
		int testCases=sc.nextInt();
		for(int t=1;t<=testCases;t++){
			solve(t);
		}
	}
}