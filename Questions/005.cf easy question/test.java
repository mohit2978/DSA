import java.util.*;
import java.io.*;
//https://codeforces.com/contest/71/problem/A
public class test{
    	public static void solve(int t,String word){
	   //	System.out.println("In function solve t val is "+ t);
		
		if(word.length()<=10){
			System.out.println(word);
			return;
		}
		StringBuilder sb=new StringBuilder();
		char ch1=word.charAt(0);
        char ch2=word.charAt(word.length()-1);
        int len=word.length()-2;
        sb.append(ch1);
        sb.append(len);
        sb.append(ch2);
        System.out.println(sb.toString());
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
	//	Solver solver=new Solver();
		//System.out.println("Please enter input");
		int testCases=sc.nextInt();
		for(int t=1;t<=testCases;t++){
			String word=sc.next();
			solve(t,word);
		}
	}
}