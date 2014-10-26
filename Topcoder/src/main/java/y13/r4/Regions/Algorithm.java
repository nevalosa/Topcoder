/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package y13.r4.Regions;

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
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.StringTokenizer;
import java.util.TreeSet;

public class Algorithm{
    public void solution(String inputFilePath, String usrOutputFilePath ) throws IOException{       
        
        File infile = new File(inputFilePath);
        File outfile = new File(usrOutputFilePath );
        BufferedReader r = new BufferedReader(new FileReader(infile));
        BufferedWriter w = new BufferedWriter(new FileWriter(outfile));
        int t = Integer.parseInt(r.readLine());
        Worker[] works = new Worker[t];
        Listener[] listen = new Listener[t];
        for (int c = 0; c < t; ++c) {
        	String s =r.readLine();
        	if (s.equalsIgnoreCase("")) {
        		s = r.readLine();
        	}
        	int N = Integer.parseInt(s);
        	
        	int[] x1 = new int[N];
        	int[] y1 = new int[N];
        	int[] x2 = new int[N];
        	int[] y2 = new int[N];
        	for (int i = 0; i < N; ++i) {
        		StringTokenizer token = new StringTokenizer(r.readLine());
        		x1[i] = Integer.parseInt(token.nextToken());
        		y1[i] = Integer.parseInt(token.nextToken());
        		x2[i] = Integer.parseInt(token.nextToken());
        		y2[i] = Integer.parseInt(token.nextToken());
        	}
        	listen[c] = new Listener();
        	works[c] = new Worker();
        	works[c].listen = listen[c];
        	works[c].x1 = x1;
        	works[c].y1 = y1;
        	works[c].x2 = x2;
        	works[c].y2 = y2;
        	works[c].algo = new Algorithm();
        	works[c].start();
        }
    	while (true) {
    		try {
        		Thread.sleep(2000);
        	} catch (Exception e) {
        	}
    		boolean done = true;
    		for (int i = 0; i < t; ++i) {
    			if (!works[i].listen.ended) {
    				done = false;
    				break;
    			}
    		}
    		if (done) break;
    	}
    	for (int i = 0; i < t; ++i) {
    		if (works[i].listen.ended) {
    			w.write(works[i].ret + "\n");
    		} else {
    			w.write("3 5\n");
    		}
    	}
        w.close();
    }
  	public String getCountNArea(int[] x1, int[] y1, int[] x2, int[] y2) {
		int N = x1.length;
		int areaCount = 0;
		int maxArea = 0;
		Rect[] scan = new Rect[2 * N];
		for (int i = 0; i < N; ++i) {
			scan[2 * i] = new Rect(x1[i], y1[i], x2[i], y2[i], true);
			scan[2 * i + 1] = new Rect(x1[i], y1[i], x2[i], y2[i], false);
		}
		Arrays.sort(scan);
		TreeSet<ActiveRect> active = new TreeSet<ActiveRect>();
		for (int i = 0; i < 2 * N; ++i) {
			Rect rect = scan[i];
			if (rect.isLeft) {
				ArrayList<ActiveRect> insertlist = new ArrayList<ActiveRect>();
				ArrayList<ActiveRect> deletelist = new ArrayList<ActiveRect>();
				Iterator<ActiveRect> it = active.iterator();
				int lowerTop = rect.y2;
				int upperBot = rect.y1;
				int prevUpper = rect.y1;
				while(it.hasNext()) {
					ActiveRect test = it.next();
					if (test.y2 < rect.y1) {
						continue;
					} else if (test.y1 > rect.y2) {
						break;
					}
					test.addArea( (rect.value - test.x1) * (test.y2 - test.y1) );
					deletelist.add(test);
					lowerTop = Math.min(lowerTop, test.y1);
					upperBot = Math.max(upperBot, test.y2);
					ActiveRect newRect = new ActiveRect(rect.value, Math.max(test.y1, rect.y1), Math.min(test.y2, rect.y2));
					++areaCount;
					insertlist.add(newRect);
					if (prevUpper > rect.y1 && prevUpper < test.y1) {
						ActiveRect middleRect = new ActiveRect(rect.value, prevUpper, test.y1);
						++areaCount;
						insertlist.add(middleRect);
					}
					prevUpper = test.y2;
					if (newRect.y1 > test.y1) {
						ActiveRect newLower = new ActiveRect(rect.value, test.y1, newRect.y1);
						newLower.prev = test;
						insertlist.add(newLower);
					}
					if (newRect.y2 < test.y2){
						ActiveRect newUpper = new ActiveRect(rect.value, newRect.y2, test.y2);
						newUpper.prev = test;
						insertlist.add(newUpper);
					}
					if (newRect.y1 == test.y1 && newRect.y2 == test.y2) {
						maxArea = Math.max(maxArea, test.getArea());
					}
				}
				if (lowerTop > rect.y1) {
					ActiveRect newRect = new ActiveRect(rect.value, rect.y1, lowerTop);
					++areaCount;
					insertlist.add(newRect);
				}
				if (lowerTop < upperBot && upperBot < rect.y2) {
					ActiveRect newRect = new ActiveRect(rect.value,upperBot, rect.y2);
					++areaCount;
					insertlist.add(newRect);
				}
				for (ActiveRect d: deletelist) {
					active.remove(d);
				}
				for (ActiveRect in: insertlist) {
					active.add(in);
				}
			} else { // right
				Iterator<ActiveRect> it = active.iterator();
				ActiveRect lowRect = null;
				while(it.hasNext()) {
					ActiveRect test = it.next();
					if (test.y2 < rect.y1) {
						continue;
					} else if (test.y2 == rect.y1){
						lowRect = test;
						continue;
					}
					ArrayList<ActiveRect> deletelist = new ArrayList<ActiveRect>();
					ArrayList<ActiveRect> insertlist = new ArrayList<ActiveRect>();
					test.addArea( (rect.value - test.x1) * (test.y2 - test.y1) );
					maxArea = Math.max(maxArea, test.getArea());
					int newLowTop = test.y2;
					int newUpBot = newLowTop;
					deletelist.add(test);
					while (it.hasNext() && test.y2 <= rect.y2) {
						test = it.next();
						if (test.y2 > rect.y2)break; 
						test.addArea( (rect.value - test.x1) * (test.y2 - test.y1) );
						maxArea = Math.max(maxArea, test.getArea());
						deletelist.add(test);
						if (test.y1 > rect.y1 && test.y2 < rect.y2) {
							ActiveRect newRect = new ActiveRect(rect.value, test.y1, test.y2);
							++areaCount;
							insertlist.add(newRect);
							newUpBot = test.y2;
						}
					}
					if (lowRect != null && lowRect.y2 == rect.y1) {
						// merge with lower
						lowRect.addArea( (rect.value - lowRect.x1) * (lowRect.y2 - lowRect.y1) );
					    deletelist.add(lowRect);
						int newLower = lowRect.y1;
						if (newLowTop == rect.y2 && test.y1 == rect.y2) {
							ActiveRect ap = lowRect.getParent();
							ActiveRect bp = test.getParent();
							test.addArea((rect.value - test.x1) * (test.y2 - test.y1) );
							if (ap.x1 == bp.x1 && ap.y1 == bp.y1 && ap.y2 == bp.y2) {
								
							} else {
								lowRect.addArea(test.getArea());
								--areaCount;
							}
							newLowTop = test.y2;
							deletelist.add(test);
						}
						ActiveRect newRect = new ActiveRect(rect.value, newLower, newLowTop);
						newRect.prev = lowRect;
						insertlist.add(newRect);
						
					}
					if (test.y1 == rect.y2 && newLowTop < test.y1) {
						// merge with upper
						test.addArea( (rect.value - test.x1) * (test.y2 - test.y1) );
						deletelist.add(test);
						ActiveRect newRect = new ActiveRect(rect.value, newUpBot, test.y2);
						newRect.prev = test;
						insertlist.add(newRect);
					}
					for (ActiveRect d: deletelist) {
						active.remove(d);
					}
					for (ActiveRect in: insertlist) {
						active.add(in);
					}
					
					break;
				}
			}
		}
		StringBuffer ret = new StringBuffer();
		ret.append(String.valueOf(areaCount - active.size()));
		ret.append(" ");
		ret.append(String.valueOf(maxArea));
		return ret.toString();
	}

	public static class Rect implements Comparable<Rect> {
		int x1;
		int y1;
		int x2;
		int y2;
		int value;
		boolean isLeft;
		
		Rect(int x1, int y1, int x2, int y2, boolean isLeft) {
			this.x1 = x1;
			this.y1 = y1;
			this.x2 = x2;
			this.y2 = y2;
			if (isLeft) value = x1;
			else value = x2;
			this.isLeft = isLeft;
		}

		public int compareTo(Rect o) {
			if (this.value > o.value) return 1;
			else if (this.value < o.value) return -1;
			return 0;
		}
	}
	
	public static class ActiveRect implements Comparable<ActiveRect> {
		int x1;
		int y1;
		int y2;
		int curArea;
		ActiveRect prev;

		ActiveRect(int x1, int y1, int y2) {
			this.x1 = x1;
			this.y1 = y1;
			this.y2 = y2;
		}

		public void addArea(int area) {
			if (prev == null) {
				this.curArea += area;
			} else {
				prev.addArea(area);
			}
		}

		public int getArea() {
			if (prev == null) {
				return this.curArea;
			} else {
				return prev.getArea();
			}
		}
		
		public ActiveRect getParent() {
			if (prev == null) {
				return this;
			} else {
				return prev.getParent();
			}
		}

		public int compareTo(ActiveRect o) {
			if (this.y1 > o.y1) return 1;
			else if (this.y1 < o.y1) return -1; 
			return 0;
		}
	}

	public class Worker extends Thread {
		int[] x1;
		int[] y1;
		int[] x2;
		int[] y2;
		Algorithm algo;
		Listener listen;
		String ret;
		public void run() {
			ret = algo.getCountNArea(x1, y1, x2, y2);
			listen.ended = true;
		}
	}
	
	public class Listener {
		volatile boolean ended = false;
	}    
}
