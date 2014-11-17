package y14.r11.Repairman;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

/*
As the name of the class should be Algorithm , using Algorithm.java as the filename is recommended.
In any case, you can execute your program by running 'java Algorithm' command.
*/
class Algorithm {

    static long Answer;
    static int n;
    static int[] l;
    static int[] w;
    static StreamTokenizer in;

    public static int readInt() throws IOException {
        in.nextToken();
        return (int) in.nval;
    }

    public static void main(String args[]) throws Exception {
        InputStreamReader reader = new InputStreamReader(System.in);
        in = new StreamTokenizer(new BufferedReader(reader));
        int T = readInt();

        for (int test_case = 0; test_case < T; test_case++) {

            n = readInt();
            l = new int[n];
            w = new int[n];

            for (int i = 0; i < n; i++) {
                l[i] = readInt();
            }

            for (int i = 0; i < n; i++) {
                w[i] = readInt();
            }

            if (n <= 1) {
                System.out.println("Case #" + (test_case + 1));
                System.out.println(0);
                continue;
            }

            Answer = Long.MAX_VALUE;
            long l2r = fromL2R(0, n - 1, 0, 0);
            long r2l = fromR2L(0, n - 1, 0, 0);
            Answer = r2l;
            Answer = Answer < l2r ? Answer : l2r;
            solution();
            System.out.println("Case #" + (test_case + 1));
            System.out.println(Answer);
        }
    }

    public static void solution() {
        
        for (int i = 1; i < n-1; i++) {
            if(i == 2){
                i = 2;
            }
            int left = i - 1;
            int right = i + 1;
            int count = 0;
            int li = 0;
            long weight = 0;
            int currentid = i;
            while (count< n -1) {
                if(weight > Answer) break;
                boolean toRight = toLorR(currentid, left, right);
                
                if(toRight){
                    li += l[right] - l[currentid]; 
                    weight += li* w[right];
                    if(right== n-1){
                        li+= l[right]-l[left];
                        weight += li*w[left];
                        weight += fromL2R(0, left,weight, li);
                        break;
                    }
                    currentid=right;
                    right++;
                }else{
                    li += l[currentid] - l[left]; 
                    weight += li* w[left];
                    if(left == 0){
                       li+= l[right]-l[left];
                       weight += li*w[right];
                       weight = fromL2R(right, n-1,weight, li);
                       break;
                    }
                    currentid = left;
                    left--;
                }
                count++;
            }
            
            Answer = Answer > weight ? weight : Answer;
        }
    }

    /**
     * L --x-- A --y-- R
     * Move left or right? true move to right false move to left
     */
    public static boolean toLorR(int i, int left, int right) {

        int x = l[i] - l[left];
        int y = l[right] - l[i];
//        long rw = (y+li)*w[right]+(x+y+li)*w[left];
//        long lw = (x+li)*w[left]+(x+y+li)*w[right];
        //rw - lw = y*w[left] - x*w[right];
        long result = y*w[left] - x*w[right];
        if (result < 0) {
            return true;
        } else {
            return false;
        }
    }

    public static long fromL2R(int left, int right, long weight, int d) {

        for (int i = left; i < right; i++) {
            d += l[i + 1] - l[i];
            weight += w[i + 1] * d;
        }

        return weight;
    }

    public static long fromR2L(int left, int right, long weight, int d) {

        for (int i = right; i > left; i--) {
            d += l[i] - l[i - 1];
            weight += w[i - 1] * d;
        }

        return weight;
    }

}
