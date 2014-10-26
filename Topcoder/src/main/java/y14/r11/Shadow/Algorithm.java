/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package y14.r11.Shadow;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

class Algorithm {

    static int Answer;
    static int[] up = new int[40001];
    static int[] down = new int[40001];
    public static StreamTokenizer in;

    public static int readInt() throws IOException {
        in.nextToken();
        return (int) in.nval;
    }
//        static int total;

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

            /////////////////////////////////////////////////////////////////////////////////////////////
			/*
             Implement your algorithm here.
             The answer to the case will be stored in variable Answer.
             */
            /////////////////////////////////////////////////////////////////////////////////////////////
            // Answer = 0;

            int w = readInt();
            int h = readInt();
            int n = readInt();
            Answer = w * h;
            for (int i = 0; i < w; i++) {
                up[i] = h;
                down[i] = h;
            }

            for (int i = 0; i < n; i++) {
                int x0, y0, x1, y1;
                x0 = readInt();
                y0 = readInt();
                x1 = readInt();
                y1 = readInt();

                for (int j = x0; j < x1; j++) {
                    if (y0 < down[j]) {
                        down[j] = y0;
                    }
                    if ((h - y1) < up[j]) {
                        up[j] = (h - y1);
                    }
                }

                Answer -= ((x1 - x0) * (y1 - y0));
            }

            for (int i = 0; i < w; i++) {
                Answer -= up[i];
                if (down[i] != h) {
                    Answer -= down[i];
                }
            }
            // Print the answer to standard output(screen).
            System.out.println("Case #" + (test_case + 1));
            System.out.println(Answer);
        }
    }
}
