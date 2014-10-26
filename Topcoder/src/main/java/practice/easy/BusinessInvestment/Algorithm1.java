package practice.easy.BusinessInvestment;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

/**
 *
 * @author dengxt
 */
public class Algorithm1 {

    public static final int FROM_FILE = 0;

    private static final int TT = 300 * 20;

    private static int[] profit = new int[TT + 1];
    private static int[] weight = new int[TT + 1];
    
    private static int[][] opt = new int[TT + 1][300 + 1];
    private static boolean[][] sol = new boolean[TT + 1][300 + 1];
    private static int[] category;

    private static int UNIT;
    private static int CPNY;
    private static int N;

    public static void main(String args[]) throws Exception {

	int T = readInt();
	for (int test_case = 0; test_case < T; test_case++) {

	    UNIT = readInt();
	    CPNY = readInt();
	    N = UNIT * CPNY;
	    category = new int[N+1];
	    for (int i = 0; i < UNIT; i++) {
		int w = readInt();
		for (int j = 1; j <= CPNY; j++) {
		    profit[i*CPNY + j] = readInt();
		    weight[i*CPNY + j] = w;
		    category[i*CPNY+j] = j;
		}
	    }

	    System.out.printf("%d\n",  solve());
//	    System.out.printf("Case #%d\n%d\n", (test_case + 1), solve());
	}
    }

    public static long solve() {

	for (int n = 1; n <= N; n++) {
	    boolean[] check = new boolean[CPNY+1];
	    for (int w = 1; w <= UNIT; w++) {
		
		int choice = category[n];

		// don't take item n
		int option1 = opt[n - 1][w];
		// take item n
		int option2 = Integer.MIN_VALUE;
		
		if (weight[n] <= w) {
		    option2 = profit[n] + opt[n - 1][w - weight[n]];
		}

		// select better of two options
		opt[n][w] = Math.max(option1, option2);
		sol[n][w] = (option2 > option1);
	    }
	}

	// determine which items to take
	boolean[] take = new boolean[N + 1];
	for (int n = N, w = UNIT; n > 0; n--) {
	    if (sol[n][w]) {
		take[n] = true;
		w = w - weight[n];
	    } else {
		take[n] = false;
	    }
	}

	long maxprofit = 0;
	// print results
	System.out.println("item" + "\t" + "profit" + "\t" + "weight" + "\t" + "take");
	for (int n = 1; n <= N; n++) {
	    if (take[n]) {
		maxprofit += profit[n];
	    }
	    System.out.println(n + "\t" + profit[n] + "\t" + weight[n] + "\t" + take[n]);
	}
	
	return maxprofit;
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
		is = Algorithm1.class.getResourceAsStream("./sample_input.txt");
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

//class QNode implements Comparable<QNode> {
//
//     private static Queue queue = new PriorityQueue(300, new Comparator<QNode>(){
//
//	@Override
//	public int compare(QNode o1, QNode o2) {
//	    return o1.compareTo(o2);
//	}
//    });
//     
//    int unit;
//    int profile;
//
//    public QNode(int p, int a) {
//
//	this.unit = p;
//	this.profile = a;
//    }
//
//    @Override
//    public int compareTo(QNode o) {
//	if (o.profile == profile) {
//	    return Integer.compare(o.unit, unit);
//	}
//	return Integer.compare(o.profile, profile);
//    }
//    
//    @Override
//    public String toString(){
//    
//	return "Unit:" + unit + ", profile:" + profile;
//    }
//
//}
