/*
 * #!/usr/bin/env python
 * # coding=utf-8
 */
package y14.r14.anthome;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.HashMap;
import java.util.TreeSet;

/**
 *
 * @author dengxt
 */
public class Algorithm {

    private static int N;
    private static int Q;
    private static Node[] nodes;
    private static int[] PARENT = new int[200001];
    private static int[] ANSWER = new int[200001];
    private static int range = 0;

    public static void main(String args[]) throws Exception {

	int T = readInt();

	for (int test_case = 0; test_case < T; test_case++) {

	    N = readInt();//Node
	    Q = readInt();//Query
	    range = 0;
	    nodes = new Node[N+1];

	    HashMap<Integer, TreeSet<Integer>> map = new HashMap<Integer, TreeSet<Integer>>();

	    for (int i = 0; i < N - 1; i++) {
		//Par < Chld
		int n1 = readInt();
		int n2 = readInt();
		addToMap(n1, n2, map);

	    }

	    buildTree(1, map);
	    
	    

	    for (int i = 0; i < Q; i++) {

		int n1 = readInt();
		int n2 = readInt();
		ANSWER[i] = answerQuery(n1, n2);
	    }

	    StringBuilder bd = new StringBuilder(2 * Q);
	    for (int i = 0; i < Q; i++) {
		bd.append(ANSWER[i] == 0 ? '0' : '1').append('\n');
	    }

	    System.out.printf("Case #%s\n%s", (test_case + 1), bd.toString());
	}
    }

    public static void buildTree(int p, HashMap<Integer, TreeSet<Integer>> map) {
	
	nodes[p] = new Node();
	nodes[p].id = p;
	nodes[p].pre = range++;

	TreeSet<Integer> sp = map.get(p);

	for (Integer key : sp) {
	    map.get(key).remove(p);
	    buildTree(key, map);
	    PARENT[key] = p;
	}
	
	nodes[p].post = range++;
    }

    private static void addToMap(int n1, int n2, HashMap<Integer, TreeSet<Integer>> map) {

	TreeSet s1 = map.get(n1);
	if (s1 == null) {
	    s1 = new TreeSet();
	    map.put(n1, s1);
	    s1.add(n2);
	} else {
	    s1.add(n2);
	}

	TreeSet s2 = map.get(n2);
	if (s2 == null) {
	    s2 = new TreeSet();
	    map.put(n2, s2);
	    s2.add(n1);
	} else {
	    s2.add(n1);
	}
    }

    public static int answerQuery(int node1, int node2) {
	
	if(node1 == 1 || node2 == 1 || node1 == node2 || PARENT[node1] == node2 || PARENT[node2] == node1) return 0;
	Node n1 = nodes[node1];
	Node n2 = nodes[node2];
	return (n1.pre < n2.pre && n1.post > n2.post) || (n1.pre > n2.pre && n1.post < n2.post) ? 1 : 0;
    }

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

}

class Node {
    
    int id;
    int pre;
    int post;

    public Node() {
	
    }
    
    public String toString(){
	return id+":["+pre+","+post+"]\n";
    }
}
