package y14.swct.ladder;


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

    static int[][] array;
    static int SIZE;
    static int[] result;
 
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
	int j;
	
        InputStreamReader reader = new InputStreamReader(System.in);
        in = new StreamTokenizer(new BufferedReader(reader));
	

        int tc = 5;

        for (int test_case = 0; test_case < tc; test_case++) {
	    
	    SIZE = readInt();
	    result = new int[SIZE];
	    
	    array = new int[SIZE][SIZE];
	    for(int x = 0; x < SIZE; x++){
		for(int y = 0; y < SIZE; y++){
		    array[y][x] = readInt();
		}
	    }
	    
	    for(i = 0; i < SIZE; i++){
		if(array[0][i] == 1){
		    result[i] = solve(i, 1, false, false);
//		    System.out.printf("\n[%d,%d]=%d:", 0, i, result[i]);
		}
	    }
   
	    int min = Integer.MAX_VALUE;
	    int index = 0;
	    
	    for(i = SIZE-1; i >= 0; i--){
		
		if(result[i]< min){
		    index = i;
		    min = result[i];
		}
	    }
	    
	    System.out.printf("#%d %d\n", test_case+1, index+1);
	}

    }
      
    public static int solve(int x, int y, boolean towardX, boolean left){
	
	if(y == SIZE-1) return 1;
	int step = 1;
	int x0, x1, y0;
	int min = Integer.MAX_VALUE;

	if(!towardX){
	    //At y direction and move down.
	    //Find left(x-1) turning or right(x+1) turning
	    
	    while(y<SIZE){
		
		if((x-1>=0 && array[y][x-1]==1) || (x+1<SIZE && array[y][x+1]==1)){
		    break;
		}else {
//		    System.out.print("V ");
		    y++;
		    step++;
		}
	    }
	    
	    if(x-1>=0 && array[y][x-1]==1){
//		System.out.print("< ");
		x0 = step+solve(x-1, y, true, true);
		min = Integer.min(x0, min);
	    }
	    
	    if(x+1<SIZE && array[y][x+1]==1){
//		System.out.print("> ");
		x1 = step+ solve(x+1, y, true, false);
		min = Integer.min(x1, min);
	    }
	}else{
	    //At x direction
	    if(left){
		while(x-1>=0 && array[y][x-1]==1 && array[y+1][x]!=1 ){
		    x--;
		    step++;
//		    System.out.print("< ");
		}
	    }else{
		while(x+1<SIZE && array[y][x+1]==1 && array[y+1][x]!=1 ){
		    x++;
		    step++;
//		    System.out.print(">");
		}
	    }
	    
	    if (y + 1 < SIZE && array[y+1][x] == 1) {
//		System.out.print("V");
		y0 = step + solve(x, y + 1, false, false);
		min = Integer.min(y0, min);
	    }
	}
	
	return min;
    }

}