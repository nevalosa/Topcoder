/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package y13.r4.CyclicCipher;

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
//You can include standard Java language libraries that you want use.//

public class Algorithm{
     
    public void solution(String inputFilePath, String usrOutputFilePath ) throws IOException{       
        
        File infile = new File(inputFilePath);
        File outfile = new File(usrOutputFilePath );
        BufferedReader r = new BufferedReader(new FileReader(infile));
        BufferedWriter w = new BufferedWriter(new FileWriter(outfile));
        int t = Integer.parseInt(r.readLine());
        for (int c = 0; c < t; ++c) {
        	r.readLine();// string number
        	String a = r.readLine();
        	String b = r.readLine();
        	w.write(String.valueOf(getCycle(a,b)) + "\n");
        }
        w.close();
    }     
   
	public int getCycle(String a, String b) {
		if (a.length() != b.length()) return -1;
		int N = a.length();
		int[] prefixes = new int[N];
		int j = 0;
		for (int i = 1; i < N; ++i) {
			while (j > 0 && a.charAt(i) != a.charAt(j)) {
				j = prefixes[j - 1];
			}
			if (a.charAt(i) == a.charAt(j)) j++;
			prefixes[i] = j;
		}
		
		j = 0;
		for (int i = 0; i < N; ++i) {
			while (j > 0 && b.charAt(i) != a.charAt(j)) {
				j = prefixes[j - 1];
			}
			if (b.charAt(i) == a.charAt(j)) j++;
		}
		for (int i = 0; i < N; ++i) {
			if (j >= N) return i;
			while (j > 0 && b.charAt(i) != a.charAt(j)) {
				j = prefixes[j - 1];
			}
			if (b.charAt(i) == a.charAt(j)) j++;
		}
		return -1;
	}

}
