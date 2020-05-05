#     I c o n   M a t c h
#
# ECE 2035 Project P1-2
#
# Student Name: Dilip Paruchuri
# Date: February 26, 2020
#
# This routine determines which of eight candidate icons matches a pattern icon.


.data
CandBase: 				.alloc 	1152										# allocates space for candidate array
PatternBase:			.alloc 	144											# allocates space for pattern array

.text

IconMatch:  			addi  $1, $0, CandBase					# base address for Candbase
									swi   584												# generates array
									addi  $3, $0, 0									# counter for CandBase
									addi  $7, $0, 0									# Match variable
									addi  $9, $0, 0									# counter for number of pixels matched
check:						lw    $5, PatternBase($3)				# stores Pattern[i]
									bne   $5, $0, checkIcon					# if black pixel skip to next one
increment:        addi  $3, $3, 4									# increment CandBase
									j     check											# if not black pixel check with candidates
checkIcon:        add	  $2, $1, $3								# address of corresponding nextPixel
									lw    $2, 0($2)									# loads corresponding pixel
									bne   $2, $5, Skip							# if pixels equal then generates
									addi  $9, $9, 1									# increases counter for num of matches
									addi  $11, $7, 0								# stores candidate number
Skip: 						addi  $7, $7, 1									# else move on to next icon
									addi  $1, $1, 576								# address for next icon
									addi  $2, $0, 8									# for next statements comparison
									bne   $2, $7, checkIcon					# checks if reached 8 iterations
End:              addi  $9, $9, -1								# checks if count is 1
									addi  $1, $0, CandBase					# resets Candbase register
									addi  $7, $0, 0									# resets match variable
									beq   $9, $0, Store							# if count was 1, store match variable
									addi  $9, $0, 0									# if not reset count num matches
									j     increment									# loop to the next pixel of pattern
Store:						addi  $2, $11, 0								# stores matched icon
									swi		544												# submit answer and check
                  jr		$31												# return to caller
