/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package y13.r3.OrderOfCards;

/**
 *
 * @author dengxt
 */
public class Solution {

    public static int[][] JMatrix;
    public static int[] answer;

    static {
        System.out.println("Initialization...");
        long time = System.currentTimeMillis();
        JMatrix = new int[10000][];
        JMatrix[0] = new int[]{1};

        for (int i = 1; i < 10000; i++) {
            JMatrix[i] = new int[i + 1];
            int k = (i + 1) / 2;
            for (int j = 0; j < k; j++) {
                JMatrix[i][j] = (j + 1) << 1;
            }
        }

        System.out.println("Initial Matrix Cost Time: " + (System.currentTimeMillis() - time));
        time = System.currentTimeMillis();
        josephus2(4096, 4096);
        josephus2(8192, 8192);
        josephus2(10000, 10000);
        System.out.println("Call Api Cost Time: " + (System.currentTimeMillis() - time));
    }

    public static int josephus2(int n) {

        if (n <= 1) {
            return 1;
        }

        return 2 * n + 1 - (int) Math.pow(2, Math.ceil(Math.log(n) / Math.log(2)));
    }

    public static int josephus2(int n, int x) {

        if (n == 1 && x == 1) {
            return 1;
        }

        if (n > 1 && x == 1) {
            return 2;
        }

        int jm = 0;
        if (JMatrix[n - 1 - 1][x - 1 - 1] == 0) {
            jm = josephus2(n - 1, x - 1);
            JMatrix[n - 1 - 1][x - 1 - 1] = jm;
        }

        if (jm == n - 1) {
            return 1;
        } else {
            return jm + 2;
        }
    }

    public static int josephus(int n, int x) {

        if (x <= n / 2) {
            return x << 1;
        }

        float k = 2 * n - 2 * x + 1f;
        double log = Math.ceil(Math.log(Math.ceil(n / k)) / Math.log(2));
        int o = (int) (k * Math.pow(2, log));
        int power = (int) Math.pow(2, log + 1);
        int result = 2 * n + 1 - (int) k * power;

        if (result == 1) {
            return 1;
        }
        return result + o;
    }

    public static int josephus3(int n, int x) {

        if (x <= n / 2) {
            return x << 1;
        }

        int k = ((n - x) << 1) + 1;
        int i = n / k;
        
        if (n > i * k) {
            i++;
        }

        int log = 0;
        int j = i;

        while ((j = j >> 1) != 0) {
            log++;
        }

        int o = 1 << log;
        if (i > o) {
            log++;
            o = o << 1;
        }

        o = k * o;
        int power = 1 << (log + 1);
        int result = (n << 1) + 1 - k * power;
        
        if(result == 1) return 1;
        
        return result + o;
    }

    private static int ceilOfLogN(int n) {

        if (n <= 1) {
            return 0;
        }
        int i = 0, j = n;

        while ((j = (j >> 1)) > 0) {
            i++;
        }

        if ((1 << i) < n) {
            i++;
        }

        return i;
    }

    public static void solution(int n) {

        long time = System.currentTimeMillis();

        if (n > 10000) {
            n = 10000;
        }

        answer = new int[n];

        for (int i = 1; i <= n; i++) {
            answer[josephus2(n, i) - 1] = i;
        }

        System.out.println("Solution2 when n is " + n + ", cost time: " + (System.currentTimeMillis() - time) + "ms.");
    }

    public static void solution2(int n) {

        long time = System.currentTimeMillis();

        answer = new int[n];

        for (int i = 1; i <= n; i++) {
            answer[josephus3(n, i) - 1] = i;
        }

        System.out.println("Solution2 when n is " + n + ", cost time: " + (System.currentTimeMillis() - time) + "ms.");
    }

    public static void solution3(int n) {
        answer = new int[n];

        for (int i = 0; i < n; i++) {
            int a = 0;
            if (i < n - 1) {
                a = 1;
            }
            for (int j = n + 1 - i; j < n + 1; j++) {
                if (a + 2 < j) {
                    a = a + 2;
                } else {
                    a = a + 2 - j;
                }
            }
            answer[a] = i + 1;
        }
    }

    /**
     * 正向推理：直接模拟游戏规则。由于游戏经过N次位移后，所有的序号将会列出。
     *
     * @param n
     */
    public static void solution4(int n) {
        answer = new int[n];
        //分配2*N的空间，以保证append操作。
        int[] cards = new int[2 * n];

        //设置编号，该编号的意思表示：第一个出来的数字应该放在该编号上。
        for (int i = 0; i < n; i++) {
            cards[i] = i + 1;
        }

        int i = 0;
        int j = n;

        while (j > 0) {
            //将当前编号放入cards末尾。
            cards[i + j] = cards[i];
            //重复利用cards的空闲资源。
            cards[n - j] = cards[i + 1];

            //进入下一轮循环。
            i = i + 2;
            j--;
        }

        for (i = 0; i < n; i++) {
            answer[cards[i] - 1] = i + 1;
        }
    }

    /**
     * 反向倒推：
     *
     * @param n
     */
    public static void solution5(int n) {
        answer = new int[n];
        int first = 2 * (n - 1);
        int last = first;
        int[] cards = new int[2 * n - 1];
        cards[last] = n;

        for (int i = n - 1; i >= 1; i--) {
            cards[--first] = i;
            cards[--first] = cards[last--];
        }

        System.arraycopy(cards, 0, answer, 0, n);
    }

    public static void main(String[] args) {
        
        int n = 1000000;
        long time = System.currentTimeMillis();
        solution4(n);
        System.out.println("Cost Time: " + (System.currentTimeMillis() - time));

//        System.out.println(Arrays.toString(answer));
    }
}
