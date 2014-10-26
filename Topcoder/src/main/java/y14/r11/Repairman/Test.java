/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package y14.r11.Repairman;

/**
 *
 * @author dengxt
 */
public class Test {
    
    public static void main(String args[]){
        int i = 1, j = 2;
        int k = add(i,j);
        System.out.println(i+","+j+","+k);
    }
    
    public static int add(int i , int j){
        i++;
        j++;
        return i;
    }
}
