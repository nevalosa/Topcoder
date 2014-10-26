/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package y13.r4.Crosswords;

/**
 *
 * @author dengxt
 */
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.StringTokenizer;
import java.io.IOException;
//You can include standard Java language libraries that you want use.//

public class Algorithm{
    public void solution(String inputFilePath, String usrOutputFilePath ) throws IOException{       
        
        File infile = new File(inputFilePath);
        File outfile = new File(usrOutputFilePath );
        BufferedReader r = new BufferedReader(new FileReader(infile));
        BufferedWriter w = new BufferedWriter(new FileWriter(outfile));
        int t = Integer.parseInt(r.readLine());
        for (int c = 0; c < t; ++c) {
        	w.write("Case# " + String.valueOf(c + 1) + "\n");
            StringTokenizer token = new StringTokenizer(r.readLine());
            int M = Integer.parseInt(token.nextToken());
            int N = Integer.parseInt(token.nextToken());
            int[][] table = new int[M][N];
            for (int i = 0; i < M; ++i) {
                token = new StringTokenizer(r.readLine());
                for (int j = 0; j < N; ++j) {
                	table[i][j] = Integer.parseInt(token.nextToken());
                }
               // w.write(String.valueOf(algo.getCount(m, c, b) + "\n"));
            }
            //Algorithm algo = new Algorithm();
            w.write(String.valueOf(getCount(table)) + "\n");
        }

        w.close();
    }
    
	public int getCount(int[][] t) {
		int M = t.length;
		int N = t[0].length;
		int ret = 0;
		// count garo
		for (int i = 0; i < M; ++i) {
			int consec = 0;
			for (int j = 0; j < N; ++j) {
				if (t[i][j] == 1) {
					consec = 0;
					continue;
				} else {
					++consec;
					if (consec == 2) {
						++ret;
					}
				}
			}
		}
		// count sero
		for (int i = 0; i < N; ++i) {
			int consec = 0;
			for (int j = 0; j < M; ++j) {
				if (t[j][i] == 1) {
					consec = 0;
					continue;
				} else {
					++consec;
					if (consec == 2) {
						++ret;
					}
				}
			}
		}
		return ret;
	}
}
