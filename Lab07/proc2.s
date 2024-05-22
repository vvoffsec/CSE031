.data
x:	.word 5
y:	.word 10
m:	.word 15
b:	.word 2

.text
MAIN:	la $t0, x
	lw $s0, 0($t0)
	la $t0, y
	lw $s1, 0($t0) 
		
	add $a0, $zero, $s0	
	jal SUM
	add $t0, $s1, $s0
	add $s1, $t0, $v0
	addi $a0, $s1, 0
	li $v0, 1
	syscall
	j END
		
SUM:    addi $sp, $sp -4
	sw $s0, 0($sp)		
        la $t0, m
	lw $s0, 0($t0)		
        addi $sp, $sp, -4
        sw $a0, 0($sp)     
	add $a0, $s0, $a0	
        addi $sp, $sp, -4
        sw $ra, 0($sp)    
	jal SUB
	lw $a0, 4($sp)
	lw $s0, 8($sp)
	add $v0, $a0, $v0
        lw $ra, 0($sp)
	jr $ra
		
SUB:	la $t0, b
	addi $sp, $sp -4
	sw $s0, 0($sp)		
	lw $s0, 0($t0)		
	sub $v0, $a0, $s0
	lw $s0, 0($sp)		
	addi $sp, $sp 4
	jr $ra
		
END: