package y14.r12.Marcher;


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
    static int[]  p;  // p[i] = length of longest palindromic substring of t, centered at i;
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

            n = sc.nextInt();
            s = sc.next();
            solution();
                    
            int length = 0;   // length of longest palindromic substring
            int center = 0;   // center of longest palindromic substring
            for (int i = 1; i < p.length-1; i++) {
                if (p[i] > length) {
                    length = p[i];
                    center = i;
                }
            }
            System.out.println("Case #" + (test_case + 1));
            System.out.println((1+(center - 1 - length) / 2) + " " + length);
        }
    }
    
    public static void solution(){

        char[] t = preprocess(s);
        p = new int[t.length];

        int center = 0, right = 0;
        for (int i = 1; i < t.length-1; i++) {
            int mirror = 2*center - i;

            if (right > i) p[i] = Math.min(right - i, p[mirror]);
 
            // attempt to expand palindrome centered at i
            while (t[i + (1 + p[i])] == t[i - (1 + p[i])])
                p[i]++;
 
            // if palindrome centered at i expands past right,
            // adjust center based on expanded palindrome.
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }
        }
        
    }
    
    static char[] preprocess(String s) {
        char[] t = new char[s.length()*2 + 3];
        t[0] = '$';
        t[s.length()*2 + 2] = '@';
        for (int i = 0; i < s.length(); i++) {
            t[2*i + 1] = '#';
            t[2*i + 2] = s.charAt(i);
        }
        t[s.length()*2 + 1] = '#';
        return t;
    }
       
}
