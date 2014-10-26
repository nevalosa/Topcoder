/*
 * #!/usr/bin/env python
 * # coding=utf-8
 */
package y14.r14.fakepoint;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

/**
 *
 * @author dengxt
 */
public class Algorithm {
	   //Algorithm
           //Algorithm

    public static StreamTokenizer in;

    static {

	try {
	    InputStreamReader reader = new InputStreamReader(System.in);
	    BufferedReader br = new BufferedReader(reader);
	    in = new StreamTokenizer(br);
	} catch (Exception e) {

	}
    }

    public static int readInt() throws IOException {
	in.nextToken();
	return (int) in.nval;
    }

    public static String readStr() throws IOException {
	in.nextToken();
	return (String) in.sval;
    }

    
    private static int N;
    private static int K;
    

    public static void main(String args[]) throws Exception {

	int a = 100000000;
	System.out.println("a:"+a);
	int T = readInt();

	for (int test_case = 0; test_case < T; test_case++) {

	    int N = readInt();
	    int K = readInt();

	    System.out.printf("Case #%d\n%d %d\n", (test_case + 1), 1+1, 1);
	}
    }


}
