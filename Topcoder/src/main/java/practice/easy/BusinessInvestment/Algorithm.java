package practice.easy.BusinessInvestment;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.Collection;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.PriorityQueue;

/**
 *
 * @author dengxt
 */
public class Algorithm {

    public static final int FROM_FILE = 0;

    private static PriorityQueue<Node> ITEMS;
    public static int CPNY;
    public static int UNIT;
    private static int MAX = 0;

    private static final Comparator<Node> comparator = new Comparator<Node>() {
	@Override
	public int compare(Node o1, Node o2) {
	    return o1.compareTo(o2);
	}
    };

    public static void main(String args[]) throws Exception {

//	Node node1 = new Node(5, 2);
//	Node node2 = new Node(5, 3);
//	Node node3 = new Node(4, 3);
//	PriorityQueue q = new PriorityQueue(2,comparator);
//	
//	q.add(node1);q.add(node2);q.add(node3);
//	System.out.println("Q:"+q);
//	node1.weight = 3;
//	System.out.println("Q:"+q);
	int T = readInt();

	for (int test_case = 0; test_case < T; test_case++) {

	    UNIT = readInt();
	    CPNY = readInt();
	    ITEMS = new PriorityQueue<Node>(CPNY * UNIT, comparator);

	    for (int i = 0; i < UNIT; i++) {

		int weight = readInt();

		for (int j = 1; j <= CPNY; j++) {
		    int profit = readInt();
		    Node node = new Node(profit, weight, j);
		    ITEMS.add(node);
		}
	    }
	    
	    solve();
	    
	    
	    System.out.printf("%d\n", MAX);
	}
    }

    public static void solve() {
	
//	System.out.println("Queue size:"+ ITEMS.size());

	Node node = ITEMS.poll();
	
	if(node.weight == UNIT){
	    MAX = node.profit;
//	    System.out.println("MAX:"+ MAX + ", Choice:"+ Arrays.toString(node.check));
	    return;
	}
	
	Collection<Node> c = new LinkedList<Node>();
	for(Node n : ITEMS){
	    Node newOne = node.merge(n);
	    if(newOne == null) continue;
	    c.add(newOne);
	}
	
	ITEMS.addAll(c);
	solve();
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
		is = Algorithm.class.getResourceAsStream("./sample_input.txt");
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

class Node implements Comparable<Node> {
    
    
    double ratio = 1.0d;
    int weight;
    int profit;
    boolean[] check;

    public Node(int p, int w, boolean[] ck) {
	
	this.profit = p;
	this.weight = w;
	this.ratio = ratio * profit / weight;
	this.check = ck;
    }
    
    public Node(int p, int w, int category) {

	this.weight = w;
	this.profit = p;
	ratio = ratio * profit / weight;
	check = new boolean[Algorithm.CPNY+1];
	check[category] = true;
    }
    
    
    public Node merge(Node node ){
	
	int w = weight + node.weight;
	
	if(w > Algorithm.UNIT) return null;
	
	for(int i = 1; i <= Algorithm.CPNY; i++){
	    if(check[i] && node.check[i]) return null;
	}
	
	boolean[] ck = new boolean[Algorithm.CPNY+1];
	for(int i = 1; i <= Algorithm.CPNY; i++){
	    ck[i] = check[i] || node.check[i];
	}
	
	int p = profit + node.profit;
	
	
	Node newNode = new Node(p, w, ck);
	
	return newNode;
    }

    @Override
    public int compareTo(Node o) {

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
