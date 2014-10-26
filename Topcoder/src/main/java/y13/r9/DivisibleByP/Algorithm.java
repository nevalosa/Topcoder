package y13.r9.DivisibleByP;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.Scanner;

/*
   As the name of the class should be Algorithm , using Algorithm.java as the filename is recommended.
   In any case, you can execute your program by running 'java Algorithm' command.
 */
class Algorithm {
	static long Answer;

    public static StreamTokenizer in;

    public static String readString() throws IOException {
        in.nextToken();
        return  in.sval;
        }

    public static double readDouble() throws IOException {
        in.nextToken();
        return in.nval;
        }

    public static int readInt() throws IOException {
        in.nextToken();
        return (int) in.nval;
    }

	
	public static void main(String args[]) throws Exception	{
		/*
		   The method below means that the program will read from input.txt, instead of standard(keyboard) input.
		   To test your program, you may save input data in input.txt file,
		   and call below method to read from the file when using nextInt() method.
		   You may remove the comment symbols(//) in the below statement and use it.
		   But before submission, you must remove the freopen function or rewrite comment symbols(//).
		 */		

		/*
		   Make new scanner from standard input System.in, and read data.
		 */
		InputStreamReader reader = new InputStreamReader(System.in);
		in = new StreamTokenizer(new BufferedReader(reader));

		/*
		    Program is given to the problem, test cases should be handled.		
                                If a test case is given to 10   ex) test_case < 10
		 */
		int tc = readInt();
		
		for(int test_case = 0; test_case < tc; test_case++) {
		/*
			Read each test case from standard input.
			The number of node is  N[0], N[1], ..., N[9]
		 */

			int N = readInt();
			int P = readInt();
			
			int sum[] = new int[N+1];
			long qsum[] = new long[P]; 
			
			int cursum = 0;
			
			for (int i = 0; i < N; i++) {
				int cur =  readInt();
				cursum = (cursum+cur)%P;
				sum[i+1] = cursum;
			}

			for (int i = 0; i < N+1; i++) {
				qsum[sum[i]]++;
			}
			
			Answer = 0;
			
			for (int i = 0; i < P; i++) {
				Answer += qsum[i]*(qsum[i]-1)/2;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
			   Implement your algorithm here.
			   The answer to the case will be stored in variable Answer.
			 */
			/////////////////////////////////////////////////////////////////////////////////////////////
			// Answer = 0;


			// Print the answer to standard output(screen).
                                          System.out.println("Case #"+(test_case+1));
			System.out.println(""+Answer);
		}
	}
}
