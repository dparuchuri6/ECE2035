/*      I c o n   M a t c h
Student Name: Dilip Paruchuri
Date: 2/14/2020

ECE 2035 Project 1-1

This program loads 8 icons (each is a 12x12 array of pixels) into a
linear array of candidates and a single icon that serves as a pattern,
which matches exactly one candidate icon.

Add code to find which of the eight candidates matches the pattern icon.
*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

#define IconSize (12 * 12)
#define NumCandidates 8
#define CandidateArraySize (IconSize * NumCandidates)

int Load_Mem(char *InputFileName, int Candidates[], int Pattern[]);
int Load_N_Values(FILE *FP, int N, int Array[]);

int main(int argc, char *argv[]) {
  int	Candidates[CandidateArraySize];
  int	Pattern[IconSize];
  int	Length, Match=0;

  if (argc != 2) {
    printf("usage: P1-1 valuefile\n");
    exit(1);
  }
  Length = Load_Mem(argv[1], Candidates, Pattern);
  if (Length != CandidateArraySize + IconSize) {
     printf("valuefile does not contain valid data.\n");
     exit(1);
  }
  if (DEBUG){
     printf("Sample debugging print statement.\n");
  }

  /* Your icon matching code goes here */

  //Keeps track of which icon is being compared
  int iconNum = 0;
  //counter for number of pixels matched
  int count = 0;

  //for loop that checks through all possible values of icons
  for (int i = 0; i < CandidateArraySize; i++) {
      //checks corresponding pixels of each icon with pattern icon
      if (Candidates[i] == Pattern[i % IconSize]) {
          //increases count if pixel matches
          count++;
      //if at least one pixel does not matach skip to next iconNum
      } else {
          iconNum++;
          count = 0;
          i = iconNum * IconSize - 1;
      }

      //if found one match break
      if (count == 144) {
          Match = iconNum;
          break;
      }
  }

  //print out result
  printf("The matching icon is %d\n", Match);
  exit(0);
}

/* This routine loads in pairs of integers of the form "Addr: Value"
from a named file in the local directory. Each pair is delimited by a
newline. The first values are placed in the passed integer arrays
Candidates and Pattern. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int Candidates[], int Pattern[]) {
  int	Nc, Np;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
      printf("%s could not be opened; check the filename\n", InputFileName);
      return 0;
   } else {
     Nc = Load_N_Values(FP, CandidateArraySize, Candidates);
     if (Nc == CandidateArraySize)
       Np = Load_N_Values(FP, IconSize, Pattern);
     fclose(FP);
     return Nc+Np;
   }
}

int Load_N_Values(FILE *FP, int N, int Array[]){
  int i, NumVals, Addr, Value;
  for (i = 0; i < N; i++){
    NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
    if (NumVals == 2)
      Array[i] = Value;
    else
      return(i);
  }
  return(N);
}
