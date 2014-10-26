package y14.r13.pang;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.Stack;

class Algorithm {

    public static StreamTokenizer in;

    public static int[] MAX;
    public static int[] Idx;
    public static int[] Ns;
    public static int[] Ks;

    public static int K = 0;
    public static int N = 0;

    public static int readInt() throws IOException {
	in.nextToken();
	return (int) in.nval;
    }

    public static void main(String args[]) throws Exception {

	int answer;
	InputStreamReader reader = null;
	BufferedReader br = null;
	try {
	    reader = new InputStreamReader(System.in);
	    br = new BufferedReader(reader);
	    in = new StreamTokenizer(br);
	} catch (Exception e) {

	}

	int T = readInt();
	for (int test_case = 0; test_case < T; test_case++) {

	    answer = Integer.MIN_VALUE;
	    N = readInt();
	    K = readInt();

	    Ns = new int[N];
	    Ks = new int[K];

	    for (int i = 0; i < N; i++) {
		Ns[i] = readInt();
	    }

	    for (int i = 0; i < K; i++) {
		Ks[i] = readInt();
//		System.out.println("K:"+Ks[i]);
	    }

	    try {
		Stack<int[]> stack = new Stack<int[]>();
		MAX = new int[K + N + 1];
		Idx = new int[N];
		stack.add(Ns);

		for (int i = 0; i < K; i++) {

		    if (!stack.isEmpty()) {
			stack = process(stack, i, true);
		    }
		}

		int i = K;

		while (!stack.isEmpty()) {
		    stack = process(stack, i++, false);
		}

		for (int x = 0; x < MAX.length; x++) {
		    if (answer < MAX[x]) {
			answer = MAX[x];
		    }
		}

	    } catch (Exception ex) {

	    }
//	    System.out.printf("N:%d,Ns=%s K=%d Ks=%s\n", N, Arrays.toString(Ns), K, Arrays.toString(Ks));

	    System.out.println("Case #" + (test_case + 1));
	    System.out.println(answer);
	}

	if(br != null)br.close();
	if(reader != null)reader.close();

    }

    public static Stack process(Stack<int[]> stack, int at, boolean append) {

	Stack next = new Stack();

	while (!stack.isEmpty()) {

	    int[] ns = stack.pop();
	    int max = checkPosition(ns);

	    if (max < 0) {
		MAX[at] = ((-1 * max) > MAX[at]) ? (-1 * max) : MAX[at];
	    } else {
		MAX[at] = (max > MAX[at]) ? max : MAX[at];

		if (ns.length == 1) {
		    continue;
		}

		for (int j = 1; j < ns.length; j++) {

		    if (Idx[j] == 0) {
			continue;
		    }

		    int size = append ? N : ns.length - 1;
		    int[] nn = new int[size];

		    if (j == size - 1) {
			copy(ns, 0, size - 1, nn, 0);
		    } else {
			copy(ns, 0, j - 1, nn, 0);
			copy(ns, j + 1, size - 1, nn, j);
		    }

		    nn[j - 1]++;

		    if (append) {
			nn[size - 1] = Ks[at];
		    }

		    next.push(nn);
		    
		    if(next.size() == 100){
			return next;
		    }
		}
	    }
	}

	return next;
    }

    public static void copy(int[] src, int from, int to, int[] tar, int t0) {

	int t = t0;

	for (int i = from; i <= to; i++) {
	    tar[t++] = src[i];
	}

    }

    public static int checkPosition(int[] ns) {

	int same = ns[0];
	int max = ns[0];
	boolean changed = false;
	Idx = new int[ns.length];
	int maxCount = Integer.MIN_VALUE;
	int atMax=0;
	int count = 0;
	for (int i = 1; i < ns.length; i++) {
	    if (same == ns[i]) {
		Idx[i] = 1;
		changed = true;
		count++;
	    } else {
		same = ns[i];
		Idx[i] = 0;
		if(maxCount < count){
		    atMax = i-1;
		    maxCount = count;
		}
		count = 0;
	    }

	    if (max < ns[i]) {
		max = ns[i];
	    }
	}

	if (changed) {
	    if(maxCount > 20) return -1* (maxCount+max+ns[atMax]);
	    return max;
	} else {
	    return (-1 * max);
	}

    }
}
