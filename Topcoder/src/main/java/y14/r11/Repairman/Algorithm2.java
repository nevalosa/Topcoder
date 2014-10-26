/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package y14.r11.Repairman;

/**
 *
 * @author dengxt
 */
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
class Algorithm2 {

    static long Answer;
    static int n;
    static int[] l = new int[1001];
    static int[] w = new int[1001];
    static long[][][] matrix = new long[1002][1002][2];
    static long[] tempW = new long[1002];
    static StreamTokenizer in;
    final static int R = 0;
    final static int L = 1;

    public static int readInt() throws IOException {
        in.nextToken();
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
        InputStreamReader reader = new InputStreamReader(System.in);
        in = new StreamTokenizer(new BufferedReader(reader));
        //Scanner sc = new Scanner(new FileInputStream("input.txt"));

        int T = readInt();
        for (int test_case = 0; test_case < T; test_case++) {

            n = readInt();
//
            for (int i = 1; i <= n; i++) {
                l[i] = readInt();
            }

            for (int i = 1; i <= n; i++) {
                w[i] = readInt();
            }
            tempW[0] = 0;
            for (int i = 1; i <= n; i++) {
                tempW[i] = tempW[i - 1] + w[i];
            }

            long total_w = tempW[n + 1] = tempW[n];
            matrix[1][n + 1][R] = 0;
            matrix[1][n + 1][L] = 0;

            for (int i = 2; i <= n; i++) {
                matrix[i][n + 1][L] = (l[i] - l[i - 1]) * tempW[i - 1] + matrix[i - 1][n + 1][L];
            }

            matrix[n][0][R] = 0;
            matrix[n][0][L] = 0;
            for (int i = 1; i < n; i++) {
                matrix[i][0][R] = (l[i + 1] - l[i]) * (total_w - tempW[i]) + matrix[i - 1][0][R];
            }

            int p1, p2;
            long weight;
            for (int i = n; i >= 2; i--) {
                for (p1 = 1; p1 <= n + 1 - i; p1++) {
                    p2 = i + p1 - 1;
                    weight = total_w - (tempW[p2 - 1] - tempW[p1 - 1]);
                    matrix[p1][p2][R] = (l[p2] - l[p1]) * weight + min(matrix[p2][p1 - 1][L], matrix[p2][p1 - 1][R]);
                    if (p1 > 1) {
                        matrix[p1][p2][L] = (l[p1] - l[p1 - 1]) * weight + min(matrix[p1 - 1][p2][L], matrix[p1 - 1][p2][R]);
                    }

                    weight = weight - w[p2] + w[p1];
                    matrix[p2][p1][L] = (l[p2] - l[p1]) * weight + min(matrix[p1][p2 + 1][L], matrix[p1][p2 + 1][R]);
                    if (p2 < n) {
                        matrix[p2][p1][R] = (l[p2 + 1] - l[p2]) * weight + min(matrix[p2 + 1][p1][L], matrix[p2 + 1][p1][R]);
                    }
                }
            }

            Answer = Long.MAX_VALUE;
            long t;
            for (p1 = 1; p1 < n; p1++) {
                if ((t = min(matrix[p1][p1 + 1][R], matrix[p1][p1 + 1][L])) < Answer) {
                    Answer = t;
                }
            }
            if ((t = matrix[n][n - 1][L]) < Answer) {
                Answer = t;
            }

            System.out.println("Case #" + (test_case + 1));
            System.out.println(Answer);
        }
    }

    public static long min(long x, long y) {
        return x > y ? y : x;
    }
}
