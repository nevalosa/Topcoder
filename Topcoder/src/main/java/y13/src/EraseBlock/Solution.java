/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package y13.src.EraseBlock;

import java.util.Scanner;

/*
   As the name of the class should be Solution, using Solution.java as the filename is recommended.
   In any case, you can execute your program by running 'java Solution' command.
*/
class Solution {
	
	static final int MAX_N = 20;
	static int N, K;
	static int[][] grid;
	static int[] Answers = new int[MAX_N + 1];
	static Block[] blocks;
	
	static Solution solution = new Solution();
	
	
	public static void main(String args[]) throws Exception	{
		
		/*
		   The method below means that the program will read from input.txt, instead of standard(keyboard) input.
		   To test your program, you may save input data in input.txt file,
		   and call below method to read from the file when using nextInt() method.
		   You may remove the comment symbols(//) in the below statement and use it.
		   But before submission, you must remove the freopen function or rewrite comment symbols(//).
		 */
		//System.setIn(new FileInputStream("input.txt"));

		/*
		   Make new scanner from standard input System.in, and read data.
		 */
		Scanner sc = new Scanner(System.in);

		/*
		   Your program should handle 10 test cases given.
		 */
		for(int test_case = 1; test_case <= 10; test_case++) {
			/*
				Read each test case from standard input.
				The size of matirx is stored in 'N' and the total number of blocks is stored in 'K'.
				After, the shape of the matrix is stored in the array 'grid'.
				For example, if there is no block in the cell(2, 3), grid[2][3] has a value 0.
		   		On the other hand, if there is a block 'K' in the cell (2,3), grid[2][3] has a value 'K'.
			*/
			N = sc.nextInt();
			K = sc.nextInt();
			blocks = new Block[K+1];
			
			grid = new int[N + 1][N + 1];
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					grid[i][j] = sc.nextInt();
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				Implement your algorithm here.
				Assume your answer, a sequnce of N numbers, is stored in an array 'Answers'.
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			for (int i = 1; i <= N; i++) Answers[i] = -1;
			
			for(int i = 1; i <=N; i++){
				for(int j = 1; j <= N; j++){
					setBlocks(i,j);
				}
			}
			
			boolean dropped = false;
			boolean erased = false;
			
			do{
				dropped = dropped()> 0 ? true:false;
				erased = erased();
				
			}while(dropped || erased);
			
			countGrit();
			// Print the answer to standard output(screen).
			System.out.print("#" + test_case);
			for (int i = 1; i <= N; i++) System.out.print(" " + Answers[i]);
			System.out.println();
		}
	}
	
	
	private static boolean erased() {
		
		boolean erased = false;
		
		for(int row = 1; row <= N; row ++){
			
			boolean toErase = true;
			
			for(int col = 1; col <= N; col++){
				toErase = toErase&&(grid[row][col]>0);
			}
			
			if(toErase){
				for(int col = 1; col <= N; col++){
					//blocks[grid[row][col]] should not be null;
					if(blocks[grid[row][col]] != null){
						blocks[grid[row][col]].erase(row);
					}
				}
				erased = true;
			}
		}
		return erased;
	}


	private static int dropped(){
		
		int dropped = 0;
		
		for(int row = N; row >= 1; row --){
			for(int col = 1; col <= N; col++){
				if(blocks[grid[row][col]]!= null){
					dropped +=blocks[grid[row][col]].drop();
				}
			}
		}
		
		return dropped;
	}
	

		
	/**
	 *  	.1.			.2.			  	.3.                         .4.
	 * 	[i,j]                   [i,j]                       [i,j][i,j+1]                [i, j ][i  ,j+1]
         *                              [i+1,j]                                                 [i+1,j][i+1,j+1]
	 * 
	 * @param i
	 * @param j
	 */
	public static void setBlocks(int i, int j){
		
		if(grid[i][j] ==0 || blocks[grid[i][j]] != null){
			return;
		}
		
		int p01 = 0; int p10 = 0; int p11 = 0;
		
		if(j+1 <= N && grid[i][j] == grid[i][j+1]){
			p01 = 1;
		}
		
		if(i+1 <= N && grid[i][j] == grid[i+1][j]){
			p10 = 1;
		}
		
		if(i+1 <= N && j+1 <= N && grid[i][j] == grid[i+1][j+1]){
			p11 = 1;
		}
		
		int t = (p01 == 1? 1 : 0)+(p10 == 1? 2 : 0)+(p11 == 1? 4 : 0);
		
		
		Block block= null;
		switch(t){
		case 0:
			block = solution.new SQUARE1(i,j);
			break;
		case 7:
			block = solution.new SQUARE4(i,j);
			break;
		case 1:
			block = solution.new RecH(i,j);
			break;
		case 2:
			block = solution.new RecV(i,j);
			break;
		default:
			block = null;
		}
		
		blocks[grid[i][j]]= block;
	}
	
	public static void countGrit(){
		
		for(int j = 1; j <= N; j++){
			int i = 1;
			for(; i <= N; i++){
				if(grid[i][j] != 0){
					break;
				}
			}
			Answers[j]= N - i + 1;
		}
	}
	
	
	public class SQUARE1 extends Block{
		
		public SQUARE1(int i, int j){
			super(i,j);
		}

		@Override
		public int erase(int row) {
			blocks[grid[x][y]] = null;
			grid[x][y] = 0;
			return 1;
		}

		@Override
		public int drop() {
			
			int tmp = x;
			
			while(x+1 <=N && grid[x+1][y] == 0){
				grid[x][y] = 0;
				grid[x+1][y] = id;
				x++;
			}
			
			return x-tmp;
		}
	}
	
	
	/**
	 * 
	 * @author dengxt
	 *
	 */
	public class SQUARE4 extends Block{
		
		public SQUARE4(int i, int j){
			super(i,j);
		}

		@Override
		public int erase(int row) {
			
			if(x == row){
				grid[x][y] = 0;
				grid[x][y+1] = 0;
				x++;
			}else{
				grid[x+1][y] = 0;
				grid[x+1][y+1] = 0;
			}
			
			Block rec_h = new RecH(x,y);
			blocks[rec_h.id] = rec_h; 
			
			return 2;
		}

		
		@Override
		public int drop() {
			
			int tmp = x;
			
			while(x+2 <= N && grid[x+2][y] == 0 && grid[x+2][y+1] == 0){
				
				grid[x+2][y] = id;
				grid[x+2][y+1] = id;
				grid[x][y] = 0;
				grid[x][y+1] = 0;
				x++;
			}
			
			return x-tmp;
		}
	}
	
	/**
	 * Block Rectangle Hierarchy Shape
	 *   
	 *   []
	 *   []	
	 *   
	 * @author dengxt
	 *
	 */
	public class RecV extends Block{

		public RecV(int i, int j) {
			super(i, j);
		}

		@Override
		public int erase(int row) {
			
			if(x == row){
				grid[x][y] = 0;
				x = x+1;
			}else{
				grid[x+1][y] = 0;
			}
			
			Block square1 = new SQUARE1(x,y);
			blocks[square1.id] = square1;
			
			return 1;
		}

		@Override
		public int drop() {
			int tmp = x;
			
			while(x+2 <= N && grid[x+2][y] == 0){
				grid[x+2][y] = id;
				grid[x][y] = 0;
				x++;
			}
			
			return x-tmp;
		}
		
	}
	
	
	/**
	 * Block Rectangle Hierarchy Shape
	 *   
	 *   [i,j][i,j+1]
	 *   
	 * @author dengxt
	 *
	 */
	public class RecH extends Block{

		RecH(int i, int j) {
			super(i, j);
		}

		@Override
		public int erase(int row) {
			
			blocks[grid[x][y]] = null;
			grid[x][y]= 0;
			grid[x][y+1] = 0;
			return 2;
		}

		@Override
		public int drop() {
			
			int tmp = x;

			while (x + 1 <= N && grid[x + 1][y] == 0 && grid[x + 1][y + 1] == 0) {

				grid[x][y] = 0;
				grid[x][y + 1] = 0;
				grid[x + 1][y] = id;
				grid[x + 1][y + 1] = id;
				x++;
			}

			return x - tmp;
		}
	}
	
	
	public abstract class Block{
		
		protected int id;
		
		protected int x;
		
		protected int y;
		
		
		Block(int i, int j){
			this.x = i;
			this.y = j;
			this.id = grid[x][y];
		}
		
		/**
		 * Erase block if it stays at current row.
		 * @param row
		 * @return number of column move to right
		 */
		public abstract int erase(int row);
		
		
		/**
		 * Drop blocks till stop.
		 * @return the level block dropped.
		 */
		public abstract int drop();
	}
}
