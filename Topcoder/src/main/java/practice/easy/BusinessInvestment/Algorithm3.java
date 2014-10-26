/*
 * #!/usr/bin/env python
 * # coding=utf-8
 */
package practice.easy.BusinessInvestment;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.PriorityQueue;

/**
 *
 * @author dengxt
 */
public class Algorithm3 {

    public static final int FROM_FILE = 0;

    
    public static int CPNY;
    public static int UNIT;
    private static int MAX = Integer.MIN_VALUE;
    private static int DEPTH;
    private static QNode HEAD;
    private static QNode[] NODES;

    private static final Comparator<QNode> comparator = new Comparator<QNode>() {
	@Override
	public int compare(QNode o1, QNode o2) {
	    return o1.compareTo(o2);
	}
    };

    public static void main(String args[]) throws Exception {

	int T = readInt();

	for (int test_case = 0; test_case < T; test_case++) {

	    UNIT = readInt();
	    CPNY = readInt();
	    DEPTH = CPNY;
	    MAX = Integer.MIN_VALUE;
	    boolean[] ck = new boolean[CPNY+1];
	    HEAD = new QNode(0,0,ck);
	    PriorityQueue<QNode> items = new PriorityQueue<QNode>(CPNY * UNIT, comparator);

	    for (int i = 0; i < UNIT; i++) {

		int weight = readInt();

		for (int j = 1; j <= CPNY; j++) {
		    int profit = readInt();
		    QNode node = new QNode(profit, weight, j);
		    items.add(node);
		}
	    }
	    
	    NODES = new QNode[items.size()];
	    items.toArray(NODES);
	    
	    
	    for(int i = 0; i < NODES.length; i++ ){
		LinkedList<QNode> v = new LinkedList<QNode>();
		v.add(HEAD.merge(NODES[i]));
		v.add(NODES[i]);
		backtrace(v, i);
	    }
	    
	    System.out.printf("%d\n", MAX);
	}
    }
    
    public static void backtrace(LinkedList<QNode> v , int depth){
	
	if(depth > DEPTH)return;
	
	QNode head = v.get(0);
		
	if(head.weight > UNIT) return;
	
	if(head.weight == UNIT) {
	    
	    if(head.profit > MAX){
		System.out.printf("Changed:MAX[%4d->%d], DEPTH[%2d->%2d]\n", MAX, head.profit,DEPTH, depth);
		MAX = head.profit;
		DEPTH = depth;
		
	    }
	    
	    return;
	}
	
	QNode tmp = null;
	for(int i = depth+1; i < NODES.length; i++){
	    QNode newNode = head.merge(NODES[i]);
	    if(newNode == null) continue;
	    v.set(0, newNode);
	    v.add(NODES[i]);
	    backtrace(v, i);
	    v.remove(v.size()-1);
	}
    }
    

    /**
     * *********************************************************
     */
    public static StreamTokenizer in;

    public static int readInt() throws IOException {
	in.nextToken();
	return (int) in.nval;
    }

    public static String readStr() throws IOException {
	in.nextToken();
	return (String) in.sval;
    }

    // 0: from console. Otherwise: file.
    static {
	try {
	    //../package_path/inputfile.txt
	    InputStream is;
	    if (FROM_FILE == 1) {
		is = Algorithm3.class.getResourceAsStream("./sample_input.txt");
	    } else {
		is = System.in;
	    }

	    InputStreamReader reader = new InputStreamReader(is);
	    BufferedReader br = new BufferedReader(reader);
	    in = new StreamTokenizer(br);

	} catch (Exception e) {
	    System.out.println("Exception:\n" + e.getLocalizedMessage());
	}
    }

}

class QNode implements Comparable<QNode> {
    
    
    double ratio = 1.0d;
    int weight;
    int profit;
    boolean[] check;

    public QNode(int p, int w, boolean[] ck) {
	
	this.profit = p;
	this.weight = w;
	this.ratio = ratio * profit / weight;
	this.check = ck;
    }
    
    public QNode(int p, int w, int category) {

	this.weight = w;
	this.profit = p;
	ratio = ratio * profit / weight;
	check = new boolean[Algorithm3.CPNY+1];
	check[category] = true;
    }
    
    
    public QNode merge(QNode node ){
	
	int w = weight + node.weight;
	
	if(w > Algorithm3.UNIT) return null;
	
	for(int i = 1; i <= Algorithm3.CPNY; i++){
	    if(check[i] && node.check[i]) return null;
	}
	
	boolean[] ck = new boolean[Algorithm3.CPNY+1];
	for(int i = 1; i <= Algorithm3.CPNY; i++){
	    ck[i] = check[i] || node.check[i];
	}
	
	int p = profit + node.profit;
	
	
	QNode newNode = new QNode(p, w, ck);
	
	return newNode;
    }

    @Override
    public int compareTo(QNode o) {

	if (o.ratio == ratio) {
	    if (o.profit == profit) {
		return Integer.compare(o.weight, weight);
	    }
	    return Integer.compare(o.profit, profit);
	}

	return Double.compare(o.ratio, ratio);
    }

    @Override
    public String toString() {

	return "Unit:" + weight + ", profile:" + profit;
    }

}
