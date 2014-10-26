package y14.r12.LCS;


/*
 In S-Topcoder Contest,

 You should use the statndard input/output

 in order to receive a score properly.

 Do not use file input and output

 Please be very careful. 
 */

import java.util.Scanner;

/*
 As the name of the class should be Algorithm , using Algorithm.java as the filename is recommended.
 In any case, you can execute your program by running 'java Algorithm' command.
 */

class Algorithm {
    
    static String s;
    static int max = Integer.MIN_VALUE;
    static int index = 1;
    static int n = 0;
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
           
            max = Integer.MIN_VALUE;
            index = 1;
            n = sc.nextInt();
            s = sc.next();
            
            
            solution();

            System.out.println("Case #" + (test_case + 1));
            System.out.println(index + " " + max);
        }
    }
    
    public static void solution(){
        
        boolean b = true;
        for(int i = 0, j = n-1; j>=i; i++, j--){
            if(s.charAt(i)!=s.charAt(j)){
                b = false;
                break;
            }
        }
        
        if(b){
            index = 1;
            max = n;
            return;
        }
        
        if(n > 100000 ){
                index = 1;
                max = 1;
                return;
        }
        
        int count = 0;
        
        for(int i = 0; i < n-1; i++){
            count = 0;
            int j = 0, k = i ;
            for(; j <= i; j++, k--){
                if(s.charAt(j) == s.charAt(k)){
                    count++;
                }else{
                   if(max < count){
                       max = count;
                       index = (j-count+1);
                   }
                   count = 0;
                }
            }
            if(count>0){
                if(max < count){
                       max = count;
                       index = (j-count+1);
                   }
            }
        }
        
        
        for(int i = 0; i < n -1; i++){
            count = 0;
            int j = 0, k = i;
            for(;j <= i; j++, k--){
                if(s.charAt(n-1-j) == s.charAt(n-1-k)){
                    count++;
                }else{
                   if(max < count){
                       max = count;
                       index = n-j;
                   }
                   count = 0;
                }
            }
            
            if(count>0){
                if(max < count){
                       max = count;
                       index = n-j;
                   }
            }
        }
    }
}
