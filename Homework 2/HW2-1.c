/*  ECE 2035 Homework 2-1: Intensity Matcher

Your Name: Dilip Paruchuri
Date: January 31, 2020

  This program finds the two closest colors in an array of packed RGB values,
  based on the difference in their intensities.  Intensity is measured as mean
  color component value: I = (R+G+B)/3).
  It prints the difference in intensities of the two closest colors.

This is the only file that should be modified for the C implementation
of Homework 2.

FOR FULL CREDIT (on all assignments in this class), BE SURE TO TRY
MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

*/
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

int main(int argc, char *argv[]) {
   int	Nums[8];
   int	NumNums, MinDelta=255;  // temporary initial value
   int  Load_Mem(char *, int *);

   //Debugging tools
   if (argc != 2) {
     printf("usage: ./HW2-1 valuefile\n");
     exit(1);
   }

   //Debugging tools
   NumNums = Load_Mem(argv[1], Nums);
   if (NumNums != 8) {
      printf("valuefiles must contain 8 entries\n");
      exit(1);
   }

   //Debugging tools
   if (DEBUG){
     printf("Debugging print statement.\n");
     printf("These will only show up when DEBUG is set to 1.\n");
     printf("You should wrap DEBUG around any print statements you add");
     printf(" so that they do not confuse the grading scripts.\n");
     printf("You must set DEBUG to 0 before submitting your code.\n");
   }

   //creates array to hold intensity values for RGB values
   int Intensity[8];

   //used to extract the R, G, B values and calculate intensity
   for (int i = 0; i < 8; i++) {
     //extracts B value
     int blue = Nums[i] % 0x100;
     Nums[i] /= 0x100;
     //extracts G value
     int green = Nums[i] % 0x100;
     Nums[i] /= 0x100;
     //extracts R value
     int red = Nums[i] % 0x100;
     Nums[i] /= 0x100;
     //Calculates intensity
     Intensity[i] = (red + blue + green) / 0x3;
   }

   //Nested for loop compares every pair of intensties together to find min dif
   for (int i = 0; i < 8; i++) {
     for (int j = 0; j < 8; j++) {
       //compound predicate determines of min and skips case when comparing value with itself.
       if((i != j) & ((abs(Intensity[i] - Intensity[j])) < MinDelta)) {
         MinDelta = abs(Intensity[i] - Intensity[j]);
       }
     }
   }

   //prints out minimun intensity difference
   printf("The 2 closest colors have an intensity difference of %d\n", MinDelta);
   exit(0);
}

/* This routine loads in up to 8 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
      printf("%s could not be opened; check the filename\n", InputFileName);
      return 0;
   } else {
      for (N=0; N < 8; N++) {
         NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
         if (NumVals == 2)
            IntArray[N] = Value;
         else
            break;
      }
      fclose(FP);
      return N;
   }
}
