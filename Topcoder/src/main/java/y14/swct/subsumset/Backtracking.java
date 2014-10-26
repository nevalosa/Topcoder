/*
 * #!/usr/bin/env python
 * # coding=utf-8
 */

package y14.swct.subsumset;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.StreamTokenizer;
import java.util.TreeSet;

/**
 *
 * @author dengxt
 */
public class Backtracking {

    public static StreamTokenizer in;

    public static int readInt() throws IOException {
	int nextToken = in.nextToken();
	return (int) in.nval;
    }

    public static String readStr() throws IOException {
	in.nextToken();
	return (String) in.sval;
    }

    public static TreeSet readInts(String s, String spli) {

	String[] ss = s.split(spli);
	TreeSet set = new TreeSet();

	for (String s1 : ss) {
	    set.add(Integer.valueOf(s1));
	}

	return set;
    }

    public static void main(String[] args) throws IOException {

//	InputStreamReader reader = new InputStreamReader(System.in);
	FileReader reader = new FileReader("D:\\subsetsum_TC.txt");
	BufferedReader br = new BufferedReader(reader);
	in = new StreamTokenizer(br);

	int tc = 1;

	for (int test_case = 0; test_case < tc; test_case++) {

	   int[] ints = new int[]{1,2,3,4,5,6,7,8,9,10};
	    subsum(10, ints, 0, ints.length-1);
	    System.out.println("");
	}

    }

    public static boolean subsum(int sum, int[] ints, int from, int to) {

	for(int i = from; i <= to; i++){
	    int poll = ints[from];
	    
	    if(poll == sum){
		System.out.printf("{%d", poll);
		return true;
	    }else if(sum-poll>0){
		
		for(int j = i+1; j <= to; j++){
		    boolean ret = subsum(sum-poll, ints, j, to);
		    if(ret){
			System.out.printf("%d", poll);
		    }
		}
	    }
	}
	return true;
    }

}
