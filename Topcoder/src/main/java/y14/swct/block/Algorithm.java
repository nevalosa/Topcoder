package y14.swct.block;


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
    
    static int T = 0;
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
	    int max = 0;
	    int count = 0;
	    int at = 0;
	    for(i = 0; i< T; i++){
		int v = readInt();
		if(v > max){
		    max = v;
		    count = 1;
		    at = i;
		}else if(v == max){
		    count++;
		}
	    }
	    
	    System.out.printf("#%d %d\n", test_case+1, T - count - at);
	}

    }
}