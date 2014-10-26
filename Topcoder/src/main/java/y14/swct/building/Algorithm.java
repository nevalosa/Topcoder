package y14.swct.building;


/*
 In S-Topcoder Contest,

 You should use the statndard input/output

 in order to receive a score properly.

 Do not use file input and output

 Please be very careful. 
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
/*
 As the name of the class should be Algorithm , using Algorithm.java as the filename is recommended.
 In any case, you can execute your program by running 'java Algorithm' command.
 */

class Algorithm {

    static int[] building = new int[1001];
    static int T = 0;
    static int c = 1;
    
    public static StreamTokenizer in;

    public static int readInt() throws IOException {
	int nextToken = in.nextToken();
	        return (int) in.nval;
    }
    
    public static void main(String args[]) throws Exception {
        /*
         The method below means that the program will read from input.txt, instead of standard(keyboard) input.
         To test your program, you may save input data in input.txt file,
         and call below method to read from the file when using nextInt() method.
         You may remove the comment symbols(//) in the below statement and use it.
         But before submission, you must remove the freopen function or rewrite comment symbols(//).
         */

        /*
         Make new scanner from standard input System.in, and read data.
         */
	
	int i;
	
        InputStreamReader reader = new InputStreamReader(System.in);
        in = new StreamTokenizer(new BufferedReader(reader));
	

        int tc = 10;

        for (int test_case = 0; test_case < tc; test_case++) {

	    
	    T = readInt();
	    
	    if(T <= 0) break;
	    
    
	    for(i = 0; i < T; i++){
		int b = readInt();
		building[i] = b;
	    }
	    
	    if(i < 5){
		System.out.printf("#%d %d\n", test_case+1, 0);
		continue;
	    }
	    
	    if(i == 5){
		System.out.printf("#%d %d\n", test_case+1, building[2]);
		continue;
	    }
	    
	    int total = solve();
	    System.out.printf("#%d %d\n", test_case+1, total);
	}

    }
    
    public static int solve(){
    
	int block = 0;
	//From left to right;
	for(int i = 2; i < T; i++){
	    
	    int l = building[i] - building[i-1];
	    int r = building[i] - building[i+1];
	    
	    if( l> 0 && r > 0 ){
		block += (l>r ? r :l);
		i++;
	    }
	}
	
	return block;
    }
}