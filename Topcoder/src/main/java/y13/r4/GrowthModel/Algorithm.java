/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package y13.r4.GrowthModel;

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
        	int d = Integer.parseInt(r.readLine());
        	String rule = r.readLine();
        	w.write(getFractal(rule, rule, d) + "\n");
        }
        w.close();
    }     
   
   /* You can add your own functions, 
but main function call "solution" function only. */

	public String getFractal(String rule, String curStr, int degree) {
		if (degree == 1) {
			return curStr;
		}
		StringBuffer sb = new StringBuffer();
		for (int i = 0; i < curStr.length(); ++i) {
			char c = curStr.charAt(i); 
			if (c == 'F') {
				sb.append(rule);
			} else {
				sb.append(c);
			}
		}
		return getFractal(rule, sb.toString(), degree - 1);
	}
}
