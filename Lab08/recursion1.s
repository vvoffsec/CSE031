.data
inputPrompt:	.asciiz "Please enter an integer: "

.text
main:	addi $sp, $sp, -16
		
	
	la $a0, inputPrompt
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	move $s0, $v0	
	move $a0, $s0
	jal recursion	
	
	move $a0, $v0
	li $v0, 1		 
	syscall
	
	j end

recursion:
	addi $sp, $sp, -32 
	sw $s0, 16($sp)
	sw $ra, 20($sp)
	sw $s1, 24($sp)
	sw $a0, 32($sp)
	addi $t0, $a0, 1
	bne $t0, $zero, not_minus_one
	addiu $v0, $zero, 3
	j end_recur
		
not_minus_one:
	li $t0, -2
	bgt $a0, $t0, not_lte_negative_two
	bge $a0, $t0, not_lt_negative_two
	addiu $v0, $zero, 2
	j end_recur
	
not_lt_negative_two:
	addiu $v0, $zero, 1
	j end_recur

not_lte_negative_two: sw $a0, 4($sp) 	
	lw $a0, 32($sp)	
	subiu $a0, $a0, 3
	jal recursion

	addu $s1, $v0, $zero	
	lw $a0, 32($sp)
	addu $s1, $s1, $a0
	lw $a0, 32($sp)
	subiu $a0, $a0, 2
	jal recursion
	
	addu $v0, $v0, $s1
	j end_recur
			
end_recur:
	lw $s0, 16($sp)		
	lw $ra, 20($sp)		
	lw $s1, 24($sp)		
	addi $sp, $sp, 32	
	jr $ra

end:	addi $sp, $sp 16
	li $v0, 10 
	syscall
