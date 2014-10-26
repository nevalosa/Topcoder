/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package y13.r4.Crosswords;

/**
 *
 * @author dengxt
 */
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class Algorithm17 {

    public void solution(String inputFilePath, String usrOutputFilePath)
            throws IOException {
        Scanner sc = new Scanner(new File(inputFilePath));
        BufferedWriter out = new BufferedWriter(new FileWriter(usrOutputFilePath));
        int num = 0;
        int numTc = sc.nextInt();
        while ((numTc--) > 0) {
            int M = sc.nextInt();
            int N = sc.nextInt();
            int board[][] = new int[M][N];
            int width = 0;
            int height = 0;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    board[i][j] = sc.nextInt();
                }
            }

            int consecuCnt = 0;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    if (board[i][j] == 0) {
                        consecuCnt++;
                    }
                    if (board[i][j] == 1 || j == N - 1) {
                        if (consecuCnt >= 2) {
                            width++;
                        }
                        consecuCnt = 0;
                    }
                }
            }

            consecuCnt = 0;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (board[j][i] == 0) {
                        consecuCnt++;
                    }
                    if (board[j][i] == 1 || j == M - 1) {
                        if (consecuCnt >= 2) {
                            height++;
                        }
                        consecuCnt = 0;
                    }
                }
            }

            out.write("Case# " + (++num));
            out.newLine();
            out.write(width + height + "");
            out.newLine();
        }
        sc.close();
        out.close();
    }

    public static void main(String[] args) {
        Algorithm algo = new Algorithm();
        try {
            algo.solution("c:\\c.txt", "c:\\output.txt");
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
