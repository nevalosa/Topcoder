/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package y14.r11.Repairman;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

/**
 *
 * @author dengxt
 */
public class Repairman {

    public static long Answer;
    public static int n;
    public static int[] l;
    public static int[] w;
    public static long[][] dw;
    public static StreamTokenizer in;

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
            dw = new long[1000][1000];
            for (int i = 0; i < n; i++) {
                l[i] = readInt();
            }

            for (int i = 0; i < n; i++) {
                w[i] = readInt();
            }
            
            for(int i = 0; i <1000; i++){
                for(int j = 0; j < 1000; i++){
                    int len = 0;
                    if(i< j){
                        len = l[j]-l[i];
                    }else{
                        len = l[i]-l[j];
                    }
                    dw[i][j] = len*w[j];
                }
            }

            Answer = Long.MAX_VALUE;
        }
    }
    
    public class Node{
        
        int left = 1;
        int right = n;
        int current = -1;
        
        int[] path = new int[1000];
        long wleft = Long.MAX_VALUE;
        long wright = Long.MAX_VALUE;
        
        public Node(int c){
            
        }
        
        public void findPath(){
            
            if(dw[current][left] < dw[current][right]){
                
            }
        
        }
    
    }
}