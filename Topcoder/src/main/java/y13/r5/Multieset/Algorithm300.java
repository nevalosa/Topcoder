package y13.r5.Multieset;

import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Scanner;

/**
 * Total score is 500. But this solution is 300.
 * @author dengxt
 */
public class Algorithm300 {

	/**
	 * @param args
	 * @throws FileNotFoundException 
	 */
	
	public static String in="in.txt";

	public static String out="out.txt";
	
	
    public void solution(String inputFilePath, String usrOutputFilePath ) throws IOException{    
		Scanner rd = new Scanner(new FileReader(inputFilePath));		
		PrintStream stream = new PrintStream(usrOutputFilePath);
		
		int t = rd.nextInt();
		
		int kmax=500;
		
		for (int i = 0; i < t; i++) {
			int n = rd.nextInt();
			stream.print("Case # "+(i+1)+"\n");
			boolean tt=false;
			
/*			for (int a = 2; a < kmax; a++) {
				if (tt) break;
				for (int b = a; b < kmax; b++) {
					if (a+b+a*b*(a*b-a-b)==n) {
						stream.print(a*b-a-b+2+"\n");
						stream.print(a+" "+b);
						for (int j = 0; j < a*b-a-b; j++) {
							stream.print(" "+a*b);						
						}
						stream.print("\n");
						tt=true;
						break;
					}
				}
			}
	
			*/
			if (!tt)
			for (int a = 2; a < kmax; a++) {
				if (tt) break;
				for (int b = a; b < kmax; b++) {
					if (tt) break;
					for (int x = 1; x < 100; x++) {
						long prz=-(n-a*x-a*a*b*b+a*b*b*x);
						if (prz%(a*a*b-b)==0&&(prz/(a*a*b-b)>0)) {
							int y=(int) (prz/(a*a*b-b));
							int z=(a*b-a*y-b*x);
							
							if (x+y+z>100||z<0)continue;
							
							stream.print(x+y+z+"\n");

							int arr[]=new int[x+y+z];
							int carr=0;
							
							for (int j = 0; j < x; j++) {
								arr[carr]=a;carr++;
						
							}							
							for (int j = 0; j < y; j++) {
								arr[carr]=b;carr++;
						
							}							
						
							for (int j = 0; j < z; j++) {
								arr[carr]=a*b;carr++;
						
							}		
							
							for (int j = 0; j < carr-1; j++) {
							stream.print(arr[j]+" ");}
							
							stream.print(arr[carr-1]+"\n");
							
							tt=true;
							break;
						}
					}
				}
			}
			
			if (!tt){
			stream.print("1\n");
			stream.print("1\n");
			}
		}
		
		
		
		rd.close();
		stream.close();
	}
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		Algorithm300 alg = new Algorithm300();
		alg.solution(in, out);
	}

}