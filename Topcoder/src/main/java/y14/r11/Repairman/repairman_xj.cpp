#include "stdafx.h"
#include <iostream>

using namespace std;

int positions[1000][2];
int locationWeight[1000000][2];//0: weight   1:position 
int numOfPoint;
int rount;
int sumUpWeight;
int checkLocation;

int T(int location){

         int getRightPos;
         int getLeftPos;
         int rightVal(0);
         int leftVal(0);
         int inPositionsIndex = locationWeight[location][1];
         int index(0);
         bool findRight=false;
         bool findLeft=false;
         while(inPositionsIndex+index<numOfPoint-1){
                   index++;
                   if(positions[inPositionsIndex+index][1]!=checkLocation)//if ==location means the position has been used
                   {
                            getRightPos = inPositionsIndex+index;

                            rightVal = locationWeight[positions[getRightPos][0]][0];
                            findRight=true;

                            //cout<<"get right pos "<<getRightPos<<"  rightVal"<<rightVal<<endl;
                            break;
                   
                   }

         }
         index=inPositionsIndex;
         while(index>0){
                   index--;
                   if(positions[index][1]!=checkLocation)
                   {
                            getLeftPos = index;
                            leftVal = locationWeight[positions[getLeftPos][0]][0];
                            findLeft=true;

                            //cout<<"get left pos "<<getLeftPos<<"  leftVal"<<leftVal<<endl;
                            break;
                   
                   }
         }
         if(!findLeft){
                   if(!findRight)
         return sumUpWeight;
         }

         if(rightVal>leftVal){
         rount = rount + positions[getRightPos][0]-location;
         sumUpWeight = sumUpWeight+rount*rightVal;
         positions[getRightPos][1]=checkLocation;
         location = positions[getRightPos][0];
         //cout<<"rount is "<<rount<<"sumUpWeight "<<sumUpWeight<<"  now location is "<<location<<endl;
         //cout<<"next location is"<<location<<"sum up weight "<<sumUpWeight<<endl;
         return T(location);
         }
         else{
         
         rount = rount + location-positions[getLeftPos][0];
         sumUpWeight = sumUpWeight + rount * leftVal;
         positions[getLeftPos][1]=checkLocation;
         location = positions[getLeftPos][0];
         cout<<"next location is"<<location<<"  sum up weight "<<sumUpWeight<<"  rount  "<<rount<<endl;
         return T(location);
         }
         


}
int main(){
         int numOfPoints;
         cin>>numOfPoints;
         numOfPoint=numOfPoints;
         rount=0;
         sumUpWeight=0;
         
         for(int i=0;i<numOfPoints;i++){
                   cin>>positions[i][0];
         }
         for(int i=0;i<numOfPoints;i++){
                   int getPos= positions[i][0];
                   cin>>locationWeight[getPos][0];
                   locationWeight[getPos][1]=i;
         }
         int min(999999999);
         for(int i=0;i<numOfPoints;i++){
                   checkLocation=positions[i][0];
                   positions[i][1]=checkLocation;
                   sumUpWeight=0;
                   rount=0;
                   int getSumIs = T(positions[i][0]);
                   positions[i][1]=0;
                   //cout<<i<<"  getSumIs "<<getSumIs<<endl;
         if(getSumIs<min)
                   min = getSumIs;
         
         }
         cout<<"the result is"<<min<<endl;


         return 0;
}

