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
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class Algorithm15 {

	static int N;
	static int K;

	public void solution(String inputFilePath, String usrOutputFilePath) throws IOException {
		@SuppressWarnings("unused")
		String EOL = System.getProperty("line.separator");
		BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream(new File(inputFilePath))));
		BufferedWriter out = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(new File(usrOutputFilePath))));

		String line = in.readLine();
		Integer C = Integer.parseInt(line); // number of excercises
		for (int i = 0; i < C; i++) {
			line = in.readLine();
			N = Integer.parseInt(line.trim());
			String l = in.readLine();
			String w = "F";
			for (int j = 0; j < N; j++) {
				w = w.replaceAll("F", l);
			}
			out.write(w+EOL);

		}

		in.close();
		out.close();
	}
}

