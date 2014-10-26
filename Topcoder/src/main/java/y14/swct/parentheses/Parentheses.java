/*
 * #!/usr/bin/env python
 * # coding=utf-8
 */

package y14.swct.parentheses;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.Stack;

/**
 *
 * @author dengxt
 */
public class Parentheses {

    static String p = "";
    static int len = 0;

    public static Stack stack = new Stack();

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

	InputStreamReader reader = new InputStreamReader(System.in);
	BufferedReader br = new BufferedReader(reader);
	in = new StreamTokenizer(br);

	int tc = 10;
	for (int test_case = 0; test_case < tc; test_case++) {

	    len = readInt();
	    p = br.readLine();
	    stack.clear();

	    int result = solve();
	    System.out.printf("#%d %d\n", test_case + 1, result);

	}
    }

    public static int solve() {

	for (int i = 0; i < len; i++) {

	    if (stack.isEmpty()) {
		stack.push(p.charAt(i));
		continue;
	    }

	    char pre = (char) stack.peek();
	    char c = p.charAt(i);
	    boolean match = false;

	    switch (c) {

		case ')':
		    match = pre == '(';
		    break;
		case '}':
		    match = pre == '{';
		    break;
		case '>':
		    match = pre == '<';
		    break;
		case ']':
		    match = pre == '[';
		    break;
		default:
		    break;
	    }

	    if (match) {
		stack.pop();
	    }else{
		stack.push(c);
	    }
	}
	
	return stack.isEmpty()? 1:0;
    }

}
