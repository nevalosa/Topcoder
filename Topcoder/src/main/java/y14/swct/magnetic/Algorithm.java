package y14.swct.magnetic;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;


class Algorithm {

    static int SIZE;
    static int[][] array = new int[100][100];
    static int h;
    static int l;
    static int times;
 
    public static StreamTokenizer in;

    public static int readInt() throws IOException {
	int nextToken = in.nextToken();
	        return (int) in.nval;
    }
    
    public static void main(String args[]) throws Exception {
	
	int i;
	
        InputStreamReader reader = new InputStreamReader(System.in);
        in = new StreamTokenizer(new BufferedReader(reader));
        int tc = 10;

        for (int test_case = 0; test_case < tc; test_case++) {
	    
	    SIZE = readInt();
	    
	    for(i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
		    array[j][i] = readInt();
		}
	    }
	    
	    int total = 0;
	    for(i = 0; i < SIZE; i++){
		int[] blocks = array[i];
		total += solve(blocks);

	    }
	    
	    System.out.printf("#%d %d\n", test_case+1, total);
	}

    }
     
    public static int solve(int[] blocks){
	
	int left;
	int right;
	
	for(left = 0; left < SIZE && blocks[left]!=1; left++){
	    blocks[left]=0;
	}
	
	// N:SSSSNNNN:S
	for(right = SIZE-1; right >= left && blocks[right]!=2; right--){
	    blocks[right]=0;
	}
	
	int count = 0;
	
	for(int i = left; i <= right ; i++){
	    
	    if(blocks[i] ==2){
		count++;
		while(i<=right && blocks[i]!=1 ){
		    i++;
		}
	    }
	}
	
	return count;
    }

}