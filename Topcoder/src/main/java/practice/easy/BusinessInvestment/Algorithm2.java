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
public class Algorithm2 {
    
    public static final int FROM_FILE = 0;
    
    private static int[][] MAX = new int[301][21];
    private static int[][] TABLE;
    private static int CPNY;
    private static int UNIT;
    
    public static void main(String args[]) throws Exception {
	
	int T = readInt();
	
	for (int test_case = 0; test_case < T; test_case++) {
	    
	    UNIT = readInt();
	    CPNY = readInt();
	    
	    for(int i = 0; i < UNIT; i++){
		
		int idx = readInt();
		int max = Integer.MIN_VALUE;
		
		for(int j = 0; j < CPNY; j++){
		    int unit = readInt();
		    if(max < unit){
			max = unit;
		    }
		}
		MAX[idx][0] = max;
//		System.out.printf("Unit = %d, Max = %d\n", idx, MAX[idx][0]);
	    }
	    
	    TABLE = new int[UNIT+1][];
	    
	    for(int i = 1; i <= UNIT; i++){
		TABLE[i] = new int[i+1];
	    }
	    
	    TABLE[1][1] = 1;
	    		

	    solve();
	    System.out.printf("%d\n", MAX[UNIT][0]);
//	    int[] choice = TABLE[UNIT];
	    
//	    for(int i = 1; i < choice.length; i++){
//		if(choice[i] == 0) continue;
//		System.out.printf("Select %3d : %d\n", i, choice[i]);
//	    }
	}
    }
    
    public static void solve(){
	
	for(int i = 2; i <= UNIT; i++){
	    findMax(i);
	}
    }
    
    public static void findMax(int n){
    
	int[] finder = TABLE[n-1];
	int max = MAX[n][0];
	int index = 0;
	
	for(int i = 1; i < n; i++){
	    
	    if(finder[i] == 0) continue;
	    int newMAX = MAX[i][0]+MAX[1][0];
	    
	    if(newMAX > max){
		index = i;
		max = newMAX;
	    }
	}
	
	MAX[n][0] = max;
	if(index == 0){
	    TABLE[n][n] = 1;
	}else{
	    for(int i = 1; i < n; i++){
		if(TABLE[n-1][i] == 0) continue;
		TABLE[n][i] = TABLE[n-1][i];
	    }
	    
	    TABLE[n][index]--;
	    TABLE[n][index+1]++;
	}
	
//	System.out.printf("N = %d, Max = %d \n", n, max);
    }

    
    
    /************************************************************/
    
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

}

