package y14.r13.typo;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.TreeMap;

class Algorithm {

    public static StreamTokenizer in;
    public static String typo;
    public static int[] visited;
    public static int[] index;
    public static int[] max;
    public static int[][] positions;
    public static TreeMap<Integer, LinkedList<String>> map;

    public static Comparator<Integer> comp = new Comparator<Integer>() {

	@Override
	public int compare(Integer o1, Integer o2) {
	    return o2.compareTo(o1);
	}

    };

    public static int readInt() throws IOException {
	in.nextToken();
	return (int) in.nval;
    }

    public static String readStr() throws IOException {
	in.nextToken();
	return (String) in.sval;
    }

    public static void main(String args[]) throws Exception {

	InputStreamReader reader = new InputStreamReader(System.in);
//	FileReader reader = new FileReader("D:\\2.case");
	BufferedReader br = new BufferedReader(reader);
	in = new StreamTokenizer(br);

	int T = readInt();
	for (int test_case = 0; test_case < T; test_case++) {

	    int line = readInt();
	    typo = readStr();
	    visited = new int[26];
	    max = new int[26];
	    index = new int[26];
	    positions = new int[26][];

	    for (int i = 1; i < typo.length() - 1; i++) {
		int idx = typo.charAt(i) - 'a';
		max[idx] = i;
		index[idx]++;
	    }

	    init();

	    map = new TreeMap<Integer, LinkedList<String>>(comp);

	    for (int i = 0; i < line; i++) {
		String w = readStr();
		int freq = readInt();
		if (w == null || w.length() == 1) {
		    continue;
		}

		if (w.charAt(0) == typo.charAt(0) && w.charAt(w.length() - 1) == typo.charAt(typo.length() - 1)) {
		    LinkedList list = map.get(freq);
		    if (list == null) {
			list = new LinkedList<String>();
			map.put(freq, list);
		    }
		    list.add(w);
		}
	    }

	    String answer = resolve();

	    System.out.printf("Case #%d\n%s\n", (test_case + 1), answer);
	}
    }

    public static String resolve() {

	if (map.isEmpty()) {
	    return "ERROR";
	}

	for (int k : map.keySet()) {
	    LinkedList<String> list = map.get(k);
	    
	    for (String s : list) {
		if (matched(s)) {
		    return s;
		}
	    }
	}

	return "ERROR";
    }

    public static void init() {
	System.arraycopy(index, 0, visited, 0, 26);
	int len = typo.length() - 1;

	for (int i = 0; i < 26; i++) {
	    if(visited[i]>0){
		positions[i] = new int[visited[i]];
	    }
	    
	}

	int at;
	for (int i = 1; i < len; i++) {
	    at = typo.charAt(i) - 'a';
	    positions[at][index[at] - visited[at]] = i;
	    visited[at]--;
	}

    }

    public static boolean matched(String s) {

	if (s.length() == 2) {
	    return true;
	}
	
	int len = s.length() - 1;
	int position = 0;
	System.arraycopy(index, 0, visited, 0, 26);
	
//	System.out.printf("index:%s\n", Arrays.toString(index));
//	System.out.printf("visit:%s\n", Arrays.toString(visited));
	
	for (int i = 1; i < len; i++) {
	    int at = s.charAt(i) - 'a';
//	    System.out.printf("%s[%s]=%d->\n", s,s.charAt(i),visited[at]);
	    if (visited[at] > 0) {
		int[] ps = positions[at];
		int from = index[at] - visited[at];
		
		int current = ps[from];
		
		while(current < position && from+1 < ps.length){
		    from ++;
		    visited[at]--;
		    current = ps[from];
		}
		
//		System.out.printf("prePosition:%d, current:%d\n", position,current);
		if (current > position) {
		    visited[at]--;
		    position = current;
		}else{
//		    System.out.printf("[%s]=%d->%b\n", s.charAt(i),visited[at], false );
		    return false;
		}

	    }else{
//		System.out.printf("[%s]=%d->%b\n", s.charAt(i),visited[at], false );
		return false;
	    }
	}
	
	return true;

    }

}
