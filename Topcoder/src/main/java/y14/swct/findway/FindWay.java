package y14.swct.findway;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.ArrayList;
import java.util.HashMap;

/**
 *
 * @author dengxt
 */
public class FindWay {

    static HashMap<Integer, Integer[]> path = new HashMap<>();
    static ArrayList<Integer> traveled = new ArrayList<>(100);
    static int start = 0;
    static int end = 99;

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

//	FileReader reader = new FileReader("4_findingway_TC.txt");
	

	long t = System.currentTimeMillis();
	FileReader reader = new FileReader("D:\\4_findingway_TC.txt");
//	InputStreamReader reader = new InputStreamReader(System.in);
	BufferedReader br = new BufferedReader(reader);
	in = new StreamTokenizer(br);
	int tc = 10;
	for (int test_case = 0; test_case < tc; test_case++) {

	    int pair = readInt();
	    path.clear();
	    traveled.clear();

	    for (int i = 0; i < pair; i++) {

		int from = readInt();
		in.nextToken();
		int to = readInt();

		if (i < pair - 1) {
		    in.nextToken();
		}

		Integer[] tos = path.get(from);

		if (tos == null) {
		    tos = new Integer[]{null, null};
		    tos[0] = to;
		    path.put(from, tos);
		} else {
		    tos[1] = to;
		}
	    }

	    
	    traveled.add(0);
	    Integer[] tos = path.get(start);
	    int result = findway(tos);
	    System.out.printf("#%d %d\n", test_case + 1, result);
	}
	
	System.out.println("Cost:"+(System.currentTimeMillis() - t));
    }

    public static int findway(Integer[] tos) {

	if (tos == null) {
	    return 0;
	}

	int result = 0;

	for (Integer node : tos) {
	    
	    if(result == 1) return 1;

	    if (node == null) {
		continue;
	    }

	    if (node == end) {
		traveled.add(end);
		return 1;
	    }else if (traveled.contains(node)) {
		return 0;
	    } else {
		traveled.add(node);
		Integer[] way = path.get(node);
		result = findway(way);
		
		if (result == 0) {
		    traveled.remove(traveled.size()-1);
		}
	    }
	}

	return result;
    }
}
