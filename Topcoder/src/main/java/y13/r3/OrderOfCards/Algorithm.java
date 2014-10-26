package y13.r3.OrderOfCards;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.Arrays;
import java.util.Scanner;

/*
 As the name of the class should be Algorithm , using Algorithm.java as the filename is recommended.
 In any case, you can execute your program by running 'java Algorithm' command.
 */
class Algorithm {

    static int[] Answer;
    public static StreamTokenizer in;
    private final static int M = 2;

    public static String readString() throws IOException {
        in.nextToken();
        return in.sval;
    }

    public static double readDouble() throws IOException {
        in.nextToken();
        return in.nval;
    }

    public static int readInt() throws IOException {
        in.nextToken();
        return (int) in.nval;
    }

    public static void main(String args[]) throws Exception {
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

        for (int test_case = 0; test_case < tc; test_case++) {
            /*
             Read each test case from standard input.
             The number of node is  N[0], N[1], ..., N[9]
             */

            int N = readInt();
            Answer = new int[N];
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            /*
             Implement your algorithm here.
             The answer to the case will be stored in variable Answer.
             */
            /////////////////////////////////////////////////////////////////////////////////////////////
            // Answer = 0;
            // Print the answer to standard output(screen).
            System.out.println("Case #" + (test_case + 1));
            for(int i = 0; i < Answer.length; i++){
                System.out.println(Arrays.toString(Answer).replaceAll("[|]|,", " ").trim());
            }
        }
    }
    
    public static void solution(int n){
	int r = 1;
	
	int m = 2;
	int[] a = new int[n];
	int len = n;
	for (int i = 0; i < a.length; i++)
	    a[i] = i + 1;
	int i = 0;
	int j = 1;
	while (len > 0) {
	    if (a[i % n] > 0) {
		if (j % m == 0) {
		    //find index
		    Answer[a[i % n] -1] = r++;
		    a[i % n] = -1;
		    j = 1;
		    i++;
		    len--;
		} else {
		    i++;
		    j++;
		}
	    } else {
		i++;
	    }
	}
    }
}

/**
 Resouce: 
 * http://www.exploringbinary.com/powers-of-two-in-the-josephus-problem/
 * http://openhome.cc/Gossip/AlgorithmGossip/JosephusProblem.htm
 * http://acm.nudt.edu.cn/~twcourse/JosephusProblem.html
 * http://primepuzzle.com/tunxis/counting-stars.html
 */
