import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.StringTokenizer;
//You can include standard Java language libraries that you want use.//

public class Algorithm5{
     
	public void solution(String inputFilePath, String usrOutputFilePath ) throws IOException{
		File infile = new File(inputFilePath);
		File outfile = new File(usrOutputFilePath);
		BufferedReader r = new BufferedReader(new FileReader(infile));
		BufferedWriter w = new BufferedWriter(new FileWriter(outfile));
		int t = Integer.parseInt(r.readLine());
		for (int i = 0; i < t; ++i) {
			StringTokenizer token = new StringTokenizer(r.readLine());
			int X = Integer.parseInt(token.nextToken());
			int Y = Integer.parseInt(token.nextToken());
			boolean[][] graph = new boolean[X][Y];
			for (int j = 0; j < X; ++j) {
				Arrays.fill(graph[j], true);
			}
			int K = Integer.parseInt(r.readLine());
			for (int j = 0; j < K; ++j) {
				token = new StringTokenizer(r.readLine());
				int x = Integer.parseInt(token.nextToken());
				int y = Integer.parseInt(token.nextToken());
				graph[x - 1][y - 1] = false;
			}
			int ret = getmax(graph);
			w.write("Case# " + String.valueOf(i + 1));
			w.write('\n');
			w.write(String.valueOf(ret));
			w.write('\n');
			/*// prob 1
			int N = Integer.parseInt(r.readLine());
			int[] a = new int[N];
			int[] b = new int[N];
			for (int j = 0; j < N; ++j) {
				StringTokenizer token = new StringTokenizer(r.readLine());
				a[j] = Integer.parseInt(token.nextToken());
				b[j] = Integer.parseInt(token.nextToken());
			}
			ret = 0;
			long ret = getret(N, a, b);
			w.write("Case# " + String.valueOf(i + 1));
			w.write('\n');
			w.write(String.valueOf(ret));
			w.write('\n');
			*/
		}
		w.close();
	}
	
	int X, Y;
	private int getID(int i, int j) {
		return i * Y + j;
	}
	boolean[][] map;
	int[] ret;
	public int getmax(boolean[][] graph) {
		X = graph.length;
		Y = graph[0].length;
		map = new boolean[X * Y][X * Y];
		ret = new int[X * Y];
		Arrays.fill(ret, -1);
		int[] dx = new int[]{1, 0, -1, 0};
		int[] dy = new int[]{0, 1, 0, -1};
		for (int i = 0; i < X + Y - 1; i += 2) {
			for (int x = i; x >= 0; --x) {
				int y = i - x;
				if (x >= X || y >= Y || y < 0) continue;
				if (!graph[x][y]) continue;
				int id = getID(x, y);
				for (int k = 0; k < dx.length; ++k) {
					int nx = x + dx[k];
					int ny = y + dy[k];
					if (nx >= 0 && nx < X && ny >= 0 && ny < Y && graph[nx][ny]) {
						add_edge(id, getID(nx, ny));
					}
				}
			}
		}
		int ret = 0;
		for (int i = 0; i < X * Y; ++i) {
			boolean[] v = new boolean[X * Y];
			if (dfs(i, v)) {
				ret++;
			}
		}
		return ret;
	}

	private void add_edge(int i, int j) {
		map[i][j] = true;
	}
	
	private boolean dfs(int index, boolean[] v) {
		for (int i = 0; i < X * Y; ++i) {
			if (v[i]) continue;
			if (map[index][i]) {
				v[i] = true;
				if (ret[i] == -1 || dfs(ret[i], v)) {
					ret[i] = index;
					return true;
				}
			}
		}
		return false;
	}
     
   
   /* You can add your own functions, 
but main function call "solution" function only. */


}
