package y13.r8.RoadPavement;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
/**
 *
 * @author dengxt
 */
public class Algorithm {
    
    public static final int FROM_FILE = 1;
    
    public static void main(String args[]) throws Exception {
	
	int T = readInt();
	
	for (int test_case = 0; test_case < T; test_case++) {
	    
	    System.out.printf("Case #%d\n%d %d\n", (test_case + 1), T , T);
	}
    }

    
    
    /************************************************************/
    
    public static StreamTokenizer in;
    
    public static int readInt() throws IOException {
	in.nextToken();
	return (int) in.nval;
    }

    public static String readStr() throws IOException {
	in.nextToken();
	return (String) in.sval;
    }
    
     // 0: from console. Otherwise: file.
    static {
	try {
	    //../package_path/inputfile.txt
	    InputStream is;
	    if(FROM_FILE == 1){
		is = Algorithm.class.getResourceAsStream("./sample_input.txt");
	    }else{
		is = System.in;
	    }

	    InputStreamReader reader = new InputStreamReader(is);
	    BufferedReader br = new BufferedReader(reader);
	    in = new StreamTokenizer(br);
	    
	} catch (Exception e) {
	    System.out.println("Exception:\n"+e.getLocalizedMessage());
	}
    }

}
