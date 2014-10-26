package y14.swct.flatten;


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
import java.util.Arrays;
/*
 As the name of the class should be Algorithm , using Algorithm.java as the filename is recommended.
 In any case, you can execute your program by running 'java Algorithm' command.
 */

class Algorithm {

    static int[] blocks = new int[100];
    static int h;
    static int l;
    static int times;
 
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
	    
	    times = readInt();
	    for(i = 0; i < 100; i++){
		blocks[i] = readInt();
	    }
	    Arrays.sort(blocks);
	    
//	    validate();
	    
	    int df = solve();
	    System.out.printf("#%d %d\n", test_case+1, df);
	}

    }
    
    public static void validate(){
    
	int avg = 0;
	
	for(int i = 0; i < blocks.length; i++){
	    avg += blocks[i];
	}
	
	avg = avg/blocks.length;
	
	int def = 0;

	for (int i = 0; i < blocks.length; i++) {
	    if(blocks[i]< avg){
		def+= avg-blocks[i];
	    }
	}
    }
    
    public static int solve(){
    
//	System.out.printf("times=%d, size=%d\n", times, blocks.size());
	
	
	for(int i = 0; i <= times; i++){
	    
//	    System.out.println(Arrays.toString(blocks));
	    l = blocks[0];
	    h = blocks[99];
	    
	    if(h==l) return 0;
	    
	    if(h-l ==1) return 1;
	    
	    blocks[99]--;
	    blocks[0]++;
	    int j = 98;
	    while(blocks[99]<blocks[j] && j>0){
		j--;
	    }
	    
	    if(j!=98) swap(99, j+1);
	    
	    j=1;
	    while(blocks[0]>blocks[j] && j<99){
		j++;
	    }
	    
	    if(j!=1) swap(0,j-1);
	}
	
	return blocks[99]-blocks[0];
    }
    
    public static void swap(int i, int j){
	int tmp = blocks[i];
	blocks[i] = blocks[j];
	blocks[j] = tmp;
    }
}