/*
 * #!/usr/bin/env python
 * # coding=utf-8
 */

package y14.swct.gns;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

/**
 *
 * @author dengxt
 */
public class GNS {

    static int T = 0;
    static int count[];
    enum NUM {ZRO,ONE,TWO,THR,FOR,FIV,SIX,SVN,EGT,NIN}
    public static StreamTokenizer in;
    
    public static int readInt() throws IOException {
	int nextToken = in.nextToken();
	return (int) in.nval;
    }

    public static String readStr() throws IOException {
	in.nextToken();
	return (String) in.sval;
    }

    public static void main(String args[]) throws Exception {
	
	int i;
	String[] TAG = new String[]{"ZRO","ONE","TWO","THR","FOR","FIV","SIX","SVN","EGT","NIN"};
	
	InputStreamReader reader = new InputStreamReader(System.in);
	in = new StreamTokenizer(new BufferedReader(reader));

	int tc = readInt();
	for (int test_case = 0; test_case < tc; test_case++) {

	    readStr();
	    readInt();
	    T = readInt();
	    count = new int[10];
	    for (i = 0; i < T; i++) {
		int index =  NUM.valueOf(readStr()).ordinal();
		count[index]++;
	    }
	    
	    System.out.printf("#%d ", test_case + 1);
	    for(i = 0; i < count.length; i++){
		if(count[i]!=0){
		    System.out.printf("%s %d ", TAG[i], count[i]);
		}
	    }
	    
	    System.out.println("");
	}
    }
}
