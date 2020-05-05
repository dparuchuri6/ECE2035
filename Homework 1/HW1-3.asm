# HW1-3
# Student Name: Dilip Paruchrui
# Date: 1/24/20
#
# This program determines whether the value x (at XLoc) is a 16-Harshad number
# and if so, whether the factors involved are mirrors of each other.
# That is, if x = p * q, where p = sum of hexadecimal digits of x and q is the
# reverse of p (same digits in reverse order).
# For example, 6A5 = 15*51 in base 16.
#
# If x is a 16-Harshad number and its factors are mirrors, 1 will be written
# to memory location labeled Result, otherwise 0 is written there.

.data
# DO NOT change the following two labels (you may change the initial value):
XLoc:     .word  0xE29

Result:   .alloc 1

					.text
Start:		lw    $11, XLoc($0) 		    # load hex number in $11
					addiu $1, $11, 0						# allows for unsigned form of the hex number to be stored in $1
				  addiu $11, $1, 0				    # create copy of unsigned hex number
					addiu $2, $0, 0					    # initialize p = 0
					addiu $3, $0, 0					    # initialize q = 0

defineP:  beq   $11, $0, defineQ      # loop to sum digits of hex and store in $2
          andi  $4, $11, 0xF          # stores lsb of copy hex in $4
          addu  $2, $2, $4            # adds content in $4 to $2
          srl   $11, $11, 4           # Shift copy hex right by 4 bits
          j defineP

defineQ:  div 	$1, $2						    # divides x by p
					mfhi  $5								    # moves remainder to $5 and stores result for isHarshadNumber in $5
          bne   $5, $0, no            # if not Harshad skip to no and store 0 in $4
					mflo  $3								    # moves quotient to $3, quotient is q

copyP:    addiu $11, $2, 0				    # create copy of p and stores in $11
          addiu $6, $0, 0             # initialize $6 to hold reverse p

reverseP: andi  $4, $11, 0xF          # stores lsb of copy p in $4
          addu  $6, $6, $4            # adds result in $4 to $6
          srl   $11, $11, 4           # Shift copy hex right by 4 bits
          beq   $11, $0, isMirror     # break condition, located here to be able to break out of loop
          sll   $6, $6, 4             # shifts $6 left by 4 bits to make space for next hex digits
          j     reverseP              # loops back to reverseP

isMirror: beq   $3, $6, yes           # checks if factors are mirrors of each other

no:       addiu $4, $0, 0             # if no, store 0 in $4
          j     End                   # jumps to end of program

yes:      addiu $4, $0, 1             # if yes,  store 1 in $4

End:      sw    $4, Result($0)        # stores result in memory
          jr    $31
