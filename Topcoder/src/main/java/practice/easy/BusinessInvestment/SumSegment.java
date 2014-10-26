/*
 * #!/usr/bin/env python
 * # coding=utf-8
 */
package practice.easy.BusinessInvestment;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author dengxt
 */
public class SumSegment {

    public static void sumseg(int sum, int size, int[] list, int depth, List<int[]> result) {

	if (1 == size) {
	    list[depth] = sum;
	    result.add(list);
	} else {
	    int i = (depth == 0 ? 1 : list[depth - 1]);
	    for (; i <= sum / size; i++) {
		list[depth++] = i;
		sumseg(sum - i, size - 1, list, depth, result);
		depth--;
	    }
	}
    }
    
    public static int[] getSeg(int sum, int len){
	
	if(len == 1) return new int[]{sum};
	int[] ret = new int[len];
	ret[0] = sum - 1;
	
	for(int i = 1; i < len; i++){
	    ret[i] = 1;
	}
	
	return ret;
    }
    
    public static void main(String[] args) {
	
	for(int i = 1; i <= 20; i++ ){
	    int[] list = new int[i];
	    ArrayList<int[]> array = new ArrayList<>();
	    sumseg(300, i, list, 0, array);
	    System.out.printf("%2d:%d\n", i, array.size());
	}
    }
}
