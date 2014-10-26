/*
 * #!/usr/bin/env python
 * # coding=utf-8
 */

package y14.swct.palindrome;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

/**
 *
 * @author dengxt
 */
public class Palindrome {

    public static StreamTokenizer in;
    static int T = 10;
    static int SIZE = 8;
    static char[][] chs = new char[8][8];

    public static int readInt() throws IOException {
	int nextToken = in.nextToken();
	return (int) in.nval;
    }

    public static String readStr() throws IOException {
	in.nextToken();
	return (String) in.sval;
    }

    public static void main(String args[]) throws Exception {

	InputStreamReader reader = new InputStreamReader(System.in);
	in = new StreamTokenizer(new BufferedReader(reader));
	//Scanner sc = new Scanner(new FileInputStream("input.txt"));


	for (int test_case = 0; test_case < T; test_case++) {

	    int len = readInt();
	    int c = 0;

	    for (int i = 0; i < 8; i++) {
		String s = readStr();
		fill(s, i);
		c+=count(len, s);
	    }

	    for (int i = 0; i < 8; i++) {
		String s = new String(chs[i]);
		c+=count(len, s);
	    }
	    
	    System.out.printf("#%d %d\n", (test_case + 1), c);

	}
    }
    
    public static void fill(String s, int at){
	
	for(int i = 0; i < 8; i++){
	    chs[i][at] = s.charAt(i);
	}
    }
    
    public static int count(int len, String s){
    
	if(s.length() < len) return 0;

	int count = 0;
	for(int i = 0; i+len <= s.length(); i++){
	    boolean match = true;
	    for(int from = i, to = i+len-1; from<=to; from++, to--){
		match = match&&(s.charAt(from)==s.charAt(to));
	    }
	    if(match)count++;
	}
	
	return count;
    }

}
