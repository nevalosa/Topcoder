/*
 * #!/usr/bin/env python
 * # coding=utf-8
 */
package y14.r14.polyfunction;

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

    private static final int[][] FN = new int[1001][3];
    private static int[] F;
    private static int SIZE = 0;
    private static int COUNT = 0;

    public static void main(String args[]) throws Exception {

	int T = readInt();

	for (int test_case = 0; test_case < T; test_case++) {

	    SIZE = readInt();
	    COUNT = 0;

	    for (int i = 1; i <= SIZE; i++) {
		FN[i][0] = readInt();
		FN[i][1] = readInt();
		FN[i][2] = readInt();
		readInt();
	    }

	    F = new int[SIZE + 1];

	    initIntersctionPoint();
	    for (int i = 1; i <= SIZE; i++) {
		F[0] += 2 + F[i];
	    }

	    System.out.printf("Case #%d\n%d %d\n", (test_case + 1), COUNT+1, F[0]);
	}
    }

    public static void initIntersctionPoint() {

	for (int f1 = 1; f1 <= SIZE - 1; f1++) {

	    for (int f2 = f1 + 1; f2 <= SIZE; f2++) {

		int key = f1 << 10 + f2;
		int a = FN[f1][0] - FN[f2][0];
		int b = FN[f1][1] - FN[f2][1];
		int c = FN[f1][2] - FN[f2][2];

		if (a == 0) {
		    if (b == 0) {
			//No intersection
			continue;
		    }
		    
		    if(c != 0){
			count(f1, f2);
		    }
		    
		    continue;
		}

		int delta = b * b - 4 * a * c;

		if (delta < 0) {
		    //No intersection
		    continue;
		}

		if (delta == 0) {
		    if (b != 0) {
			count(f1, f2);
		    }
		    continue;
		}

//		double x = Math.sqrt(delta);
		
		//a!=0
		if( c == 0){
		    if (b != 0) {
			count(f1, f2);
		    }
		    continue;
		}

		count(f1, f2);
		count(f1, f2);
	    }
	}
    }

    public static void count(int f1, int f2) {
	F[f1]++;
	F[f2]++;
	COUNT++;
    }

}
