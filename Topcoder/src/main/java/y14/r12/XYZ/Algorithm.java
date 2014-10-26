package y14.r12.XYZ;

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

    static long Answer;
    static StreamTokenizer in;
    static OP op[] = new OP[2000];
    static int num;

    public static int readInt() throws IOException {
        in.nextToken();
        return (int) in.nval;
    }

    public static void main(String args[]) throws Exception {
        
        InputStreamReader reader = new InputStreamReader(System.in);
        in = new StreamTokenizer(new BufferedReader(reader));
        //Scanner sc = new Scanner(new FileInputStream("input.txt"));
        
        int i, j, a, b, k;
        int gcd;
        int T = readInt();
        
        for (int test_case = 0; test_case < T; test_case++) {
            
            for(int s = 0; s < 2000; s++){
                op[s] = new OP();
            }
            a = readInt();
            b = readInt();
            k = readInt();
            System.out.println("Case #" + (test_case + 1));

            if (a == k) {
                System.out.println("YES\n");
                continue;
            }
            
            num = 0;
            getPositive(a, b);
            gcd = gcd(a, b);
            a = gcd;
            b = 0;
            swap(a, b);
            if (k != 0 && !getKFromB(k, b)) {
                System.out.println("NO\n");
            } else {
                System.out.println("YES\n");
                for (j = 0; j < num; j++) {
                    System.out.println(String.format("%c %d\n", op[j].op, op[j].times));
                }
            }
        }
    }

    static void swap(int a, int b) {
        int t = a;
        a = b;
        b = t;
        if (num > 0 && op[num - 1].op == 'X') {
            op[num - 1].times++;
        } else {
            op[num].op = 'X';
            op[num++].times = 1;
        }
        op[num].op = 'Z';
        op[num++].times = 1;
        op[num].op = 'Y';
        op[num++].times = 1;
    }

    static void getPositive(int a, int b) {
        if (a < 0 && b > 0) {
            op[num].op = 'X';
            op[num++].times = -a / b + 1;
            a = a + b * op[num++].times;
        } else if (a > 0 && b < 0) {
            op[num].op = 'Z';
            op[num++].times = 1;
            b = a - b;
        } else if (a < 0 && b < 0) {
            if (a < b) {
                swap(a, b);
            }
            op[num].op = 'Y';
            op[num++].times = 1;
            a = a - b;
            op[num].op = 'Z';
            op[num++].times = 1;
            b = a - b;
        }
    }

    static int gcd(int a, int b) {
        if (a < b) {
            swap(a, b);
        }
        while (b != 0) {
            if (num > 0 && op[num - 1].op == 'Y') {
                op[num - 1].times += a / b;
            } else {
                op[num].op = 'Y';
                op[num++].times = a / b;
            }
            a %= b;
            swap(a, b);
        }
        return a;
    }

    static boolean getKFromB(int k, int b) // b should be gcd
    {
        if (k % b != 0) {
            return false;
        }
        if (k > 0) {
            if (num > 0 && op[num - 1].op == 'X') {
                op[num - 1].times += k / b;
            } else {
                op[num].op = 'X';
                op[num++].times = k / b;
            }
        } else if (k < 0) {
            if (num > 0 && op[num - 1].op == 'Y') {
                op[num - 1].times += -k / b;
            } else {
                op[num].op = 'Y';
                op[num++].times = -k / b;
            }
        }
        return true;
    }
}

class OP {

    public char op = ' ';
    public int times = 0;

    public OP() {
    }
}