#     Intensity Matcher
#
# Your Name: Dilip Paruchuri
# Date: January 31, 2020
#
# This program finds the two colors with the closest intensity
# in an eight color palette.
#
#  required output register usage:
#  $10: MinDelta, $11: Color A address, $12: Color B address
#

                .data
Array:          .alloc  8                       # allocate static space for packed color data
                .word 0, 0, 0, 0, 0, 0, 0, 0    # creates spaces in memory for each intensity
                .text

IMatch:         addi  $1, $0, Array        # set memory base
                swi   589                  # create color palette and update memory
        				addi  $10, $0, 255		     # Sets $10 to max intensity for later comparison
        				addi  $11, $1, 32	         # $11 takes on address value after the 8 colors
        				addi  $12, $0, 3	         # $12 set to 3 for intenity division


Intensity:      lbu   $13, 0($1)           # Assigns blue byte to $13
                lbu   $14, 1($1)           # Assigns green byte to $14
                addu  $13, $13, $14        # sum register that will add R,G,B values
                lbu   $14, 2($1)           # Assigns red byte to $14
                addu  $13, $13, $14        # sum register that will add R,G,B values
                divu  $13, $12             # divides the sum by 3 according to intensity formula
                mflo  $13                  # stores quotient into $13 reusing it
                sb    $13, 32($1)          # stores the intensity in the next available memory space
                addiu $1, $1, 4            # increments by 4 to address next memory address
                bne   $11, $1, Intensity   # loop exit condition

                addi  $1, $1, -32          # reverts $1 make to hold address of the first value stored in memory
                addiu $15, $1, 4           # initializes $15 to the next color in memory than $1
                addiu $13, $0, 7           # initializes a counter for outer loop

OutLoop:        addi  $14, $13, 0          # initializes a counter for inner loop which starts at int after outerloop counter
InLoop:         addi  $14, $14, -1         # decrement to loop through the intensities in the inner loop
                lbu   $4, 32($1)           # reads intensity value corresponding to 32($1)
                lbu   $5, 32($15)          # reads intensity value corresponding to 32($15)
                sltu  $6, $4, $5           # checks which number is greater
                bne   $6, $0, SubRev       # if $4 less than, flip the subtraction equation (SubRev)
                subu  $6, $4, $5           # otherwise subtract the same way
                j     checkMin             # jumps to function that checks if difference is a minimum
SubRev:         subu  $6, $5, $4           # does difference backwards
checkMin:       sltu  $4, $6, $10          # checks if difference is min
                beq   $4, $0, CheckIn      # skips to end and checks if inner counter is 0
StoreMin:       addiu $10, $6, 0           # stores the min dif in $10
                addiu $11, $1, 0           # stores address A in $11
                addiu $12, $15, 0          # stores address B in $12
CheckIn:        addiu $15, $15, 4          # increment the inner loops memory address to get next intensity value
                bne   $14, $0, InLoop      # inner loop exit condition
                addiu $1, $1, 4            # increment the outer loop memory address to get next intensity value
                addiu $15, $1, 4           # set the inner loop to start at value after outer loop to avoid repeat comparisons
                addi  $13, $13, -1         # decrement outer loop counter
                bne   $13, $0, OutLoop     # outer loop exit condition

End:            swi   581                  # Displays min in $10, address A in $11, and address B in $12
                jr    $31                  # return to caller
