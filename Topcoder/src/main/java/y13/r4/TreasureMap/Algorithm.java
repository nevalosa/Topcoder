/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package y13.r4.TreasureMap;

/**
 *
 * @author dengxt
 */
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class Algorithm {
	private static final char BIT_OFF = '0';
	private static final char BIT_ON = '1';
	private static final String INIT_16BIT_ON = "1111111111111111";
	int map[][];
	int R;
	int C;
	Point E;
	HashMap<String, Integer> costCache = new HashMap<String, Integer>(); 
	HashMap<String, Integer> findCache = new HashMap<String, Integer>();
	class Point{
		int id;
		int x;
		int y;
		int v;
		Point() {
		}
		
		Point(int tId, int x, int y, int v) {
			this.x = x;
			this.y = y;
			this.v = v;
			this.id = tId;
		}
	}
	public void solution(String inputFilePath, String usrOutputFilePath)
			throws IOException {
		Scanner sc = new Scanner(new File(inputFilePath));
		BufferedWriter out = new BufferedWriter(new FileWriter(usrOutputFilePath));
		int numTc = sc.nextInt();
		while ((numTc--) > 0) {
			R = sc.nextInt();
			C = sc.nextInt();
			sc.nextLine();
			
			map = new int[R][C];
			
			ArrayList<Point> tList = new ArrayList<Point>();
			int tId = 0;
			for(int i=0; i < R; i++) {
				String line = sc.nextLine();
				for(int j=0; j < C; j++) {
					if(line.charAt(j)=='~') {
						map[i][j] = -1;
					} else if (line.charAt(j)=='.') {
						map[i][j] = 0;
					} else if (line.charAt(j)=='E') {
						E = new Point(99, j,i,0);
					} else {
						// Treasure
						int theValue = Integer.parseInt(line.charAt(j)+"");
						map[i][j] = theValue;
						tList.add(new Point(tId++, j,i,theValue));
					}
				}
			}
			
			int result = getCost(E, INIT_16BIT_ON, tList);
			if(result <0) result = 0;
			out.write(result + "");
			out.newLine();
			costCache.clear();
			findCache.clear();
		}
		sc.close();
		out.close();
	}
	
	int getCost(Point start, String currentBit, ArrayList<Point> tList) {
		int best = -999999999;
		// finish now
		Integer sp = findCache.get(start.id+"_"+E.id);
		if(sp==null) {
			sp = findSP(start.x, start.y, E.x, E.y, 0, new HashMap<Integer, Integer>());
			findCache.put(start.id+"_"+E.id, sp);
		}
		int cost = E.v - sp;
		if(sp!=0 && cost>best) {
			best = cost;
		}

		for(int i=0; i < tList.size(); i++) {
			ArrayList<Point> clone = new ArrayList<Point>(tList);
			Point p = clone.remove(i);
			
			
			sp = findCache.get(start.id+"_"+p.id);
			if(sp==null) {
				sp = findSP(start.x, start.y, p.x, p.y, 0, new HashMap<Integer, Integer>());
				findCache.put(start.id+"_"+p.id, sp);
			}
			
			cost = -1 * sp;
			if(cost == 0) {
				// can not go.
				continue;
			}
			cost += p.v; // Add treasure value.
			
			String newString = nBitOff(currentBit, p.id);
			String newString2 = p.x + "_" + p.y;
			Integer current = costCache.get(newString+newString2);
			if(current == null) {
				current = cost + getCost(p, newString, clone);
			} else {
				current+=cost;
			}
			//current = cost + current;
			if(current > best) {
				best = current;
			}
		}
		
		costCache.put(currentBit+start.x+"_"+start.y, best);		
		return best;
	}
	
	private String nBitOff(String remainsCat, int x) {
		char[] newCat = remainsCat.toCharArray();
		newCat[x] = BIT_OFF;
		return new String(newCat);
	}

	HashMap<Integer, Integer> cache = new HashMap<Integer, Integer>();
	int findSP(int sX, int sY, int eX, int eY, int cost, HashMap<Integer, Integer> visitedQueue) {
		if(cost==0) {
			cache.clear();
		}

		int best=0;
		LinkedList<Point> queue = new LinkedList<Point>();
		queue.add(new Point(0, sX, sY, 0));
		cache.put(sX*100 + sY, 1);
		while(!queue.isEmpty()) {
			Point c = queue.pollFirst();
			if(c.x==eX && c.y==eY) {
				best = c.v*2;
				break;
			}
			
			Point childP = new Point(0, c.x-1, c.y, c.v+1);
			if(childP.x>=0 && map[childP.y][childP.x] != -1) {
				int cacheId = childP.x*100 + childP.y;
				if(cache.get(cacheId)==null) {
					queue.add(childP);
					cache.put(cacheId, 1);
				}
			}
			childP = new Point(0, c.x+1, c.y, c.v+1);
			if(childP.x<C && map[childP.y][childP.x] != -1) {
				int cacheId = childP.x*100 + childP.y;
				if(cache.get(cacheId)==null) {
					queue.add(childP);
					cache.put(cacheId, 1);
				}
			}
			childP = new Point(0, c.x, c.y+1, c.v+1);
			if(childP.y<R && map[childP.y][childP.x] != -1) {
				int cacheId = childP.x*100 + childP.y;
				if(cache.get(cacheId)==null) {
					queue.add(childP);
					cache.put(cacheId, 1);
				}
			}
			childP = new Point(0, c.x, c.y-1, c.v+1);
			if(childP.y>=0 && map[childP.y][childP.x] != -1) {
				int cacheId = childP.x*100 + childP.y;
				if(cache.get(cacheId)==null) {
					queue.add(childP);
					cache.put(cacheId, 1);
				}
			}

			
			
		}
		
		
		return best;
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

