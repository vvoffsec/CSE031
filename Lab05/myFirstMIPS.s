.text

main:
	move $t0, $s0
	
	subi $t1, $t0, 7
	
	add $t2, $t1, $t0
	
	addi $t3, $t2, 2
	
	add $t4, $t3, $t2
	
	subi $t5, $t4, 28
	
	sub $t6, $t4, $t5
	
	addi $t7, $t6, 12
	
	li $v0, 1
	move $a0, $t7
	syscall