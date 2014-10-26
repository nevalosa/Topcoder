/*
 * #!/usr/bin/env python
 * # coding=utf-8
 */
package practice.easy.NumericalCirculation;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.HashMap;
import java.util.LinkedList;

/**
 *
 * @author dengxt
 */
public class Algorithm {
    
    private static int[][] SQARE = new int[6][10];
    
    private final static HashMap<Integer, Integer>[] QUERY = new HashMap[6];
    
    static{
	for(int i = 2; i <= 5; i++){
	    for(int j = 1; j <= 9; j++){
		SQARE[i][j] = (int)Math.pow(j, i);
	    }
	}
	
	for(int i = 0; i < QUERY.length; i++){
	    QUERY[i] = new HashMap<>();
	}
    }

    
    public static final int FROM_FILE = 0;
    
    public static void main(String args[]) throws Exception {
	
	int T = readInt();
	StringBuilder bd = new StringBuilder();
	for (int test_case = 0; test_case < T; test_case++) {
	    
	    int n = readInt();
	    int p = readInt();
	    System.out.printf("%d\n", solve(n,p));
//	    System.out.printf("Case #%d\n%d\n", (test_case + 1), solve(n,p));

	}
	System.out.println(bd.toString());
    }
    
    
    public static int solve(int n, int p){
	
//	System.out.printf("N=%d, P = %d\n", n, p);
	
	int[] index_sum = getIndexAndSum(n, p);
	LinkedList<Integer> index = new LinkedList();
	LinkedList<Integer> seqs = new LinkedList();
	seqs.add(n);
	index.add(index_sum[0]);
	
	HashMap<Integer, Integer> map = QUERY[p];
	boolean path = map.containsKey(index_sum[0]);
	
	
	boolean inmap = true;
	
	while(!path){
	    
	    int newN = index_sum[1];
	    index_sum = getIndexAndSum(newN, p);

	    if(index.contains(index_sum[0])){
		inmap = false;
		seqs.add(newN);
		index.add(index_sum[0]);
		break;
	    }else{
	    	seqs.add(newN);
		index.add(index_sum[0]);
	    }
	    
	    path = map.containsKey(index_sum[0]);
	}
	
	if(inmap){
	    index.add(index_sum[0]);
	    seqs.add(index_sum[1]);
	    int theSum = map.get(index_sum[0]);
	    
	    return (theSum == index_sum[1])? index.size()-1 : index.size();
	}else{
	    int start = index.indexOf(index_sum[0]);
	    int from = (seqs.get(start).equals( seqs.getLast()))? start:start+1;
	    
	    for(int j = from; j < index.size(); j++){
		map.put(index.get(j), seqs.get(j));
	    }
	    
	    return seqs.get(start).equals( seqs.getLast())? start:start+1;
	}
    }
    
    public static int[] getIndexAndSum(int n, int p){
	
	int theN = n;
	int[] number = new int[10];
	
	while( theN != 0){
	    number[theN%10]++;
	    theN /=10; 
	}
	
	int index = 0;
	
	int sum = 0;
	
	for(int i = 1; i < 10; i++){
	    index += 10*index + number[i];
	    sum += number[i]*SQARE[p][i];
	}
	
	return new int[]{index, sum};
    }  
    
    
    /**
     * @return 
     * @throws java.io.IOException
     */
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
	    InputStream is;
	    if(FROM_FILE == 1){
		is = Algorithm.class.getResourceAsStream("./sample_input.txt");
	    }else{
		is = System.in;
	    }

	    InputStreamReader reader = new InputStreamReader(is);
	    BufferedReader br = new BufferedReader(reader);
	    in = new StreamTokenizer(br);
	    
	} catch (Exception e) {
	    System.out.println("Exception:\n"+e.getLocalizedMessage());
	}
    }
    
    public static StreamTokenizer in;
}

