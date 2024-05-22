.data
x:  .word 2
y:  .word 4
z:  .word 6
fooStr: .asciiz "p + q: "
newline:  .asciiz "\n"

.text
MAIN:
    la $t0, x
    lw $s0, 0($t0)        
    la $t0, y
    lw $s1, 0($t0)        
    la $t0, z
    lw $s2, 0($t0)        
    addu $a0, $zero, $s0   
    addu $a1, $zero, $s1      
    addu $a2, $zero, $s2   
    jal FOO
   
    addu $t0, $s1, $s0
    addu $t0, $s2, $t0
    addu $t0, $t0, $v0
    addu $a0, $zero, $t0
    li $v0, 1         
    syscall    
    j END
    
FOO:   
    addi $sp, $sp, 24
    sw $ra, 20($sp)    
    sw $a0, 16($sp)       
    sw $a1, 12($sp)       
    sw $a2, 8($sp)       
    sw $s1, 4($sp)       
    sw $s0, 0($sp)     
    addu $t0, $a0, $a2
    addu $t1, $a1, $a2
    addu $t2, $a0, $a1
    addu $a0, $zero, $t0
    addu $a1, $zero, $t1
    addu $a2, $zero, $t2
    jal BAR
    
    addu $s0, $zero, $v0  
    lw $a0, 16($sp)       
    lw $a1, 12($sp)        
    lw $a2, 8($sp)        
    subu $t0, $a0, $a2
    subu $t1, $a1, $a0
    addu $t2, $a1, $a1
    addu $a0, $zero, $t0
    addu $a1, $zero, $t1
    addu $a2, $zero, $t2
    jal BAR
    
    addu $s1, $zero, $v0
    la $a0, fooStr
    li $v0, 4
    syscall
    addu $v1, $s0, $s1
    addu $a0, $zero, $v1
    li $v0, 1         
    syscall
    li $v0, 4
    la $a0, newline
    syscall
    lw $s1, 0($sp)      
    lw $s0, 4($sp)       
    lw $ra, 20($sp)       
    addi $sp, $sp, 24
    addu $v0, $zero, $v1  
    jr $ra

BAR:    
    subu $t0, $a1, $a0
    sllv $t0, $t0, $a2
    addu $v0, $zero, $t0
    jr $ra
    
END:
