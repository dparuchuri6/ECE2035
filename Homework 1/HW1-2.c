#include <stdio.h>
#include <stdlib.h>

/*
 Student Name: Dilip Paruchuri
 Date: January 24, 2020

ECE 2035 Homework 1-2

This is the only file that should be modified for the C implementation
of Homework 1.

This program determines whether the value of the global variable x
(expressed in hexadecimal notation) is a 16-Harshad number and if so,
whether the factors involved are mirrors of each other.  That is, if x
= p * q, where p = sum of hexadecimal digits of x and q is the reverse
of p (same digits in reverse order).  For example, 6A5 = 15*51 in base
16.

The program prints a statement indicating which of 3 cases is true:
1) x is not a 16-Harshad number,
2) x is a 16-Harshad number without mirror factors (and gives the factors), or
3) x is a 16-Harshad number with mirror factors (and gives the factors).

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

*/
// DO NOT change the following declaration (you may change the initial value):
unsigned x = 0x6A5;

int main() {
   //variables to hold factors of x
   unsigned p = 0x0;
   unsigned q = 0x0;

   //copy of the initial value
   unsigned copy = x;

   //calculating the sum of the digits of x and storing in p
   while (copy != 0x0) {
     p = p + (copy % 16);
     copy /= 16;
   }
   //defining q
   q = x / p;

   //creating a copy of p
   unsigned copyp = p;

   //creating a variable to hold the reverse of p
   unsigned reversep = 0x0;

   //reverses the digits of p and stores in reversep
   while(copyp > 0) {
        reversep = reversep * 16 + copyp % 16;
        copyp = copyp / 16;
    }

    //Conditionals statements that determines
    //    1). if x is a harshad number in base 16
    //    2). if the factors are mirror factors
    //    3). if they are none of the above
    if ((p*q == x) && (reversep == q)) {
      printf("%#x is a 16-Harshad number, w/ mirror factors: %#x * %#x\n", x, p, q );
    }
    else if ((p*q == x) && (reversep != q)) {
      printf("%#x is a 16-Harshad number, w/out mirror factors: %#x * %#x\n", x, p, q );
    }
    else {
      printf("%#x is not a 16-Harshad number.\n", x);
    }
  return 0;
}
