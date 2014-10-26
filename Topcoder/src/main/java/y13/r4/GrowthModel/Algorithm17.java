/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package y13.r4.GrowthModel;

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
		int num=0;
		int numTc = sc.nextInt();
		while ((numTc--) > 0) {
			int n = sc.nextInt();
			sc.nextLine();
			String rule = sc.nextLine();
			String target = rule;
			
			for(int i=1; i < n; i++) {
				target = rule.replaceAll("F", target);
			}
			
			out.write(target);
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
