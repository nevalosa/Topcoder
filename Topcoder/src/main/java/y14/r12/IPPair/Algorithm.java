package y14.r12.IPPair;


/*
 In S-Topcoder Contest,

 You should use the statndard input/output

 in order to receive a score properly.

 Do not use file input and output

 Please be very careful. 
 */
import java.util.HashMap;
import java.util.Scanner;
/*
 As the name of the class should be Algorithm , using Algorithm.java as the filename is recommended.
 In any case, you can execute your program by running 'java Algorithm' command.
 */

class Algorithm {

    static int Answer;
//    final static long L0 = 255 * 255 * 255 * 255;
//    final static long L1 = 255 * 255 * 255;
//    final static long L2 = 255 * 255;
//    final static long L3 = 255;
 
    static HashMap<Long, Integer> idMap = new HashMap<Long, Integer>(100001);
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
        Scanner sc = new Scanner(System.in);
        //Scanner sc = new Scanner(new FileInputStream("input.txt"));

        int T = sc.nextInt();
        for (int test_case = 0; test_case < T; test_case++) {

            /////////////////////////////////////////////////////////////////////////////////////////////
			/*
             Implement your algorithm here.
             The answer to the case will be stored in variable Answer.
             */
            /////////////////////////////////////////////////////////////////////////////////////////////
            // Answer = 0;
	    System.out.println("Case #" + (test_case + 1));      
            idMap.clear();
            int n = sc.nextInt();
	    boolean b = true;

	    
            for(int i = 0; i < n; i++){
                
                int id = sc.nextInt();
                String[] int1 = sc.next().split("\\.");
                String[] int2 = sc.next().split("\\.");
                
                long ipf = Long.valueOf(int1[0])<<24 + Long.valueOf(int1[1])<<16 + Long.valueOf(int1[2])<<8 + Long.valueOf(int1[3]);
                long ipt = Long.valueOf(int2[0])<<24 + Long.valueOf(int2[1])<<16 + Long.valueOf(int2[2])<<8 + Long.valueOf(int2[3]);
		
		long ip = ipf<<32 + ipt;
		long ipr = ipt<<32 + ipf;

		Integer ex = idMap.get(ipr);
		
		if (ex != null) {
		    System.out.println(ex + " " + i+"\tipr:"+ipr+"\tip:"+ip+"\tex:"+ex+"\tipf:"+ipf+"\tipt:"+ipt);
		    b = false;
		} else {
		    ex = idMap.get(ip);
		    if(ex == null) {
			idMap.put(ip, i);
		    }
		}
            }
            
	    if(b){
		System.out.println("0");
	    }
        }
    }
}