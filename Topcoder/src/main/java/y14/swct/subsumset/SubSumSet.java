/*
 * #!/usr/bin/env python
 * # coding=utf-8
 */

package y14.swct.subsumset;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.StreamTokenizer;
import java.util.Set;
import java.util.TreeSet;

/**
 *
 * @author dengxt
 */
public class SubSumSet {

    public static StreamTokenizer in;

    public static int readInt() throws IOException {
	int nextToken = in.nextToken();
	return (int) in.nval;
    }

    public static String readStr() throws IOException {
	in.nextToken();
	return (String) in.sval;
    }

    public static TreeSet readInts(String s, String spli) {

	String[] ss = s.split(spli);
	TreeSet set = new TreeSet();

	for (String s1 : ss) {
	    set.add(Integer.valueOf(s1));
	}

	return set;
    }

    public static void main(String[] args) throws IOException {

//	InputStreamReader reader = new InputStreamReader(System.in);
	FileReader reader = new FileReader("D:\\subsetsum_TC.txt");
	BufferedReader br = new BufferedReader(reader);
	in = new StreamTokenizer(br);

	int tc = 10;

	for (int test_case = 0; test_case < tc; test_case++) {

	    String l1 = br.readLine();
	    String l2 = br.readLine();
	    TreeSet<Integer> ints1 = readInts(l1, " ");
	    TreeSet<Integer> ints2 = readInts(l2, " ");

	    System.out.printf("#%d ", test_case + 1);

	    ints1.stream().forEach((i) -> {
		TreeSet<Integer> tmp = new TreeSet();
		tmp.addAll(ints2);
		subsum(i, tmp, new TreeSet());
	    });

	    System.out.println("");
	}

    }

    public static boolean subsum(int sum, TreeSet<Integer> ints, Set<Integer> set) {

	int size = ints.size();

	for (int i = 0; i < size; i++) {

	    int poll = ints.pollFirst();

	    if (sum - poll == 0) {

		System.out.printf("%s", "{");
		set.stream().forEach((x) -> {
		    System.out.printf("%d,", x);
		});
		System.out.printf("%d}", poll);
		break;
	    } else if (sum - poll > 0) {

		TreeSet nset = new TreeSet();
		nset.addAll(set);
		nset.add(poll);

		TreeSet nints = new TreeSet();
		nints.addAll(ints);

		while (!nints.isEmpty()) {
		    subsum(sum - poll, nints, nset);
		    nints.pollFirst();
		}
	    } else {
		break;
	    }

	}

	return false;
    }

}
