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
public class Algorithm4 {

    public static final int FROM_FILE = 0;
    public static int[][] MAX_PROFIT = new int[301][21];
    public static int[][] PROFIT = new int[301][21];
    public static int CPNY;
    public static int UNIT;

    public static void main(String args[]) throws Exception {

	int T = readInt();

	for (int test_case = 0; test_case < T; test_case++) {
	    
	    UNIT = readInt();
	    CPNY = readInt();
	    
	    for (int i = 0; i < UNIT; i++) {
		int invest = readInt();
		
		for (int j = 1; j <= CPNY; j++) {
		    int profit = readInt();
		    PROFIT[invest][j] = profit;
		}
	    }
	    
	    initMaxProfit();
		    
	    System.out.printf("%d\n", MAX_PROFIT[UNIT][CPNY]);
	}
    }
    
    
    public static void initMaxProfit(){
    
	for(int N = 1; N <= CPNY; N++){
	    for(int i = 0; i <= UNIT; i++){
		MAX_PROFIT[i][N] = getMaxProfit(i, N);
//		System.out.printf("MAX[%d, %d] = %d\n", i, N, MAX_PROFIT[i][N]);
	    }
	}
    }
    
    
    public static int getMaxProfit(int invest, int N){
	
	if(invest == 0) return 0;
	if(N == 1) return PROFIT[invest][1];
	
	int max = Integer.MIN_VALUE;
	int profit;
	//2,2
	for(int i = 0; i < invest; i++){
		//M[2][1] + P[2][2]
		if(i == 0){
//		    System.out.printf("MAX_PROFIT[%d][%d] = %d, PROFIT[%d][%d] = %d\n", invest, N-1, MAX_PROFIT[invest][N-1], invest-i, N, PROFIT[invest-i][N]);
		    max = Math.max(MAX_PROFIT[invest][N-1], PROFIT[invest-i][N]);
		    continue;
		}
		profit = MAX_PROFIT[i][N-1] + PROFIT[invest-i][N];
		if(max < profit){
		    max = profit;
		}
	}

	return max;
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
		is = Algorithm4.class.getResourceAsStream("./sample_input.txt");
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
