# Collaborated with Adit Khandelwal

.data 

orig: .space 100
sorted: .space 100

str0: .asciiz "Enter the number of assignments (between 1 and 25): "
str1: .asciiz "Enter score: "
str2: .asciiz "Original scores: "
str3: .asciiz "Sorted scores (in descending order): "
str4: .asciiz "Enter the number of (lowest) scores to drop: "
str5: .asciiz "Average (rounded down) with dropped scores removed: "
newline: .asciiz "\n"
space: .asciiz " "


.text 

# This is the main program.
# It first asks user to enter the number of assignments.
# It then asks user to input the scores, one at a time.
# It then calls selSort to perform selection sort.
# It then calls printArray twice to print out contents of the original and sorted scores.
# It then asks user to enter the number of (lowest) scores to drop.
# It then calls calcSum on the sorted array with the adjusted length (to account for dropped scores).
# It then prints out average score with the specified number of (lowest) scores dropped from the calculation.
main: 
		addi $sp, $sp -4
		sw $ra, 0($sp)
		li $v0, 4 
		la $a0, str0 
		syscall               
		li $v0, 5	# Read the number of scores from user
		syscall               
		move $s0, $v0	# $s0 = numScores
		move $t0, $0
		la $s1, orig	# $s1 = orig
		la $s2, sorted	# $s2 = sorted
loop_in:
		li $v0, 4 
		la $a0, str1 
		syscall               
		sll $t1, $t0, 2
		add $t1, $t1, $s1
		li $v0, 5	# Read elements from user
		syscall               
		sw $v0, 0($t1)
		addi $t0, $t0, 1
		bne $t0, $s0, loop_in
		move $a0, $s0
		jal selSort	# Call selSort to perform selection sort in original array
		
		li $v0, 4 
		la $a0, str2 
		syscall               
		move $a0, $s1	# More efficient than la $a0, orig
		move $a1, $s0
		jal printArray	# Print original scores
		li $v0, 4 
		la $a0, str3 
		syscall               
		move $a0, $s2	# More efficient than la $a0, sorted
		jal printArray	# Print sorted scores
		li $v0, 4 
		la $a0, str4 
		syscall               
		li $v0, 5	# Read the number of (lowest) scores to drop
		syscall               
		move $a1, $v0
		sub $a1, $s0, $a1	# numScores - drop
		move $a0, $s2
		jal calcSum	# Call calcSum to RECURSIVELY compute the sum of scores that are not dropped
# Your code here to compute average and print it
		divu $v0, $a1
		mflo $t0
		li $v0, 4 
		la $a0, str5
		syscall               # prints str5
		li $v0, 1
		move $a0, $t0
		syscall               # prints average as integer
		lw $ra, 0($sp)
		addi $sp, $sp 4
		li $v0, 10 
		syscall               # termination

# printList takes in an array and its size as arguments. 
# It prints all the elements in one line with a newline at the end.
printArray:
# This function prints the elements of an array followed by spaces and a new line.

    # Function prologue: saving necessary registers and allocating space on the stack.
    addi $sp, $sp, -16 
    sw $a0, 12($sp)    # Save $a0 (array pointer)
    sw $s0, 8($sp)     # Save $s0 (loop counter)
    sw $s1, 4($sp)     # Save $s1 (array size)
    sw $s2, 0($sp)     # Save $s2 (temporarily unused)

    # Initialize loop counter ($s0) to 0
    li $s0, 0

    # Check if loop counter is less than array size ($a1)
    slt $t0, $s0, $a1
    beq $t0, $zero, exitPrint   # Exit loop if $s0 >= $a1

printElement:
    # Load array pointer into $a0
    lw $a0, 12($sp)

    # Calculate the memory address of the current element
    sll $t0, $s0, 2
    add $t0, $t0, $a0

    # Load the value of the current element
    lw $t0, 0($t0)

    # Print the value of the current element
    li $v0, 1
    move $a0, $t0
    syscall               # Print the i'th element in the array

    # Print a space after each element
    li $v0, 4
    la $a0, space
    syscall               # Print a space

    # Increment loop counter
    addi $s0, $s0, 1

    # Check if loop counter is still less than array size
    slt $t0, $s0, $a1
    bne $t0, $zero, printElement   # Continue loop if $s0 < $a1

exitPrint:
    # Print a new line after printing all elements
    li $v0, 4
    la $a0, newline
    syscall               # Print a new line

    # Restore saved registers and deallocate stack space
    lw $a0, 12($sp)
    lw $s0, 8($sp)
    lw $s1, 4($sp)
    lw $s2, 0($sp)
    addi $sp, $sp, 12

    # Return from the function
    jr $ra

# selSort takes in the number of scores as argument. 
# It performs SELECTION sort in descending order and populates the sorted array
selSort:
# Your implementation of selSort here
    # Function prologue: saving necessary registers and allocating space on the stack
    addi $sp, $sp, -12
    sw $s0, 8($sp)      # Save $s0 (outer loop counter)
    sw $s1, 4($sp)      # Save $s1 (inner loop counter)
    sw $s2, 0($sp)      # Save $s2 (temporarily unused)

    # Initialize outer loop counter ($s0) to 0
    li $s0, 0

    # Initialize inner loop counter ($s1) to 0
    li $s1, 0

    # Load array pointer ($t0) and temporary array pointer ($t1) from stack
    lw $t0, 4($sp)
    lw $t1, 0($sp)

    # Check if outer loop counter is less than array size ($a0)
    slt $t2, $s0, $a0
    beq $t2, $zero, endCopyArrElement   # Exit outer loop if $s0 >= $a0

copyArrElement:
    # Copy elements from one array to another
    sll $t2, $s0, 2
    add $t3, $t2, $t0
    add $t4, $t2, $t1
    lw $t3, 0($t3)
    sw $t3, 0($t4)

    # Increment outer loop counter
    addi $s0, $s0, 1

    # Check if outer loop counter is still less than array size
    slt $t2, $s0, $a0
    bne $t2, $zero, copyArrElement   # Continue outer loop if $s0 < $a0

    # Reset outer loop counter to 0
    li $s0, 0

endCopyArrElement:
    # Check if outer loop counter is less than array size - 1
    addi $t2, $a0, -1
    slt $t2, $s0, $t2
    beq $t2, $zero, endSelSort   # Exit if $s0 >= $a0 - 1

swapMaxArrElement:
    # Initialize variables for finding maximum element
    addi $s3, $s0, 0     # Initialize index of maximum element
    addi $s1, $s0, 1     # Initialize inner loop counter

    # Check if inner loop counter is less than array size
    slt $t2, $s1, $a0
    beq $t2, $zero, endFindMaxArrElement   # Exit inner loop if $s1 >= $a0

findMaxArrElement:
    # Find maximum element in the array
    sll $t3, $s1, 2
    add $t3, $t3, $t1
    sll $t4, $s3, 2
    add $t4, $t4, $t1
    lw $t3, 0($t3)
    lw $t4, 0($t4)
    slt $t3, $t4, $t3
    beq $t3, $zero, condition   # If current element <= maximum element, skip swapping
    addi $s3, $s1, 0      # Update index of maximum element

condition:
    # Increment inner loop counter
    addi $s1, $s1, 1

    # Check if inner loop counter is still less than array size
    slt $t2, $s1, $a0
    bne $t2, $zero, findMaxArrElement   # Continue inner loop if $s1 < $a0

endFindMaxArrElement:
    # Swap maximum element with current element
    sll $t2, $s3, 2
    add $t2, $t2, $t1
    lw $t3, 0($t2)
    move $s2, $t3   # Store maximum element temporarily in $s2

    # Load current element
    sll $t3, $s0, 2
    add $t3, $t3, $t1
    lw $t4, 0($t3)

    # Swap current element with maximum element
    sw $t4, 0($t2)   # Store current element where maximum element was
    sw $s2, 0($t3)   # Store maximum element where current element was

    # Increment outer loop counter
    addi $s0, $s0, 1

    # Check if outer loop counter is still less than array size - 1
    addi $t2, $a0, -1
    slt $t2, $s0, $t2
    bne $t2, $zero, swapMaxArrElement   # Continue outer loop if $s0 < $a0 - 1

endSelSort:
    # Restore saved registers and deallocate stack space
    lw $s0, 8($sp)
    lw $s1, 4($sp)
    lw $s2, 0($sp)
    addi $sp, $sp, 12

    # Return from the function
    jr $ra

# calcSum takes in an array and its size as arguments.
# It RECURSIVELY computes and returns the sum of elements in the array.
# Note: you MUST NOT use iterative approach in this function.

calcSum:
# Your implementation of calcSum here
    # Function prologue: saving necessary registers and allocating space on the stack
    addi $sp, $sp, -12
    sw $ra, 8($sp)      # Save $ra (return address)
    sw $a0, 4($sp)      # Save $a0 (array pointer)
    sw $a1, 0($sp)      # Save $a1 (array size)

    # Check if array size is greater than 0
    slt $t0, $zero, $a1
    beq $t0, $zero, arrLengthZero   # If $a1 <= 0, return 0

    # Decrement array size by 1
    addi $a1, $a1, -1

    # Recursive call to calcSum with updated array size
    jal calcSum

    # Load current element from the array
    sll $t0, $a1, 2
    add $t0, $t0, $a0
    lw $t0, 0($t0)

    # Add current element to the sum
    add $v0, $v0, $t0

    # End of calculation, return to the caller
    j endCalcSum

arrLengthZero:
    # If array size is 0 or negative, return 0
    li $v0, 0

endCalcSum:
    # Restore saved registers and deallocate stack space
    lw $ra, 8($sp)
    lw $a0, 4($sp)
    lw $a1, 0($sp)
    addi $sp, $sp, 12

    # Return to the caller
    jr $ra
