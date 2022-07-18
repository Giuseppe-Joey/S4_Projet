/************************************
 * Name :     	babylonn_s.s
 * Author:    	Giuseppe Lomonaco - lomg2301
 *		Lucas Corrales - corl0701	
 * Version :  	h2022
 ************************************/

.set noreorder  
.data
.text
.global module
.ent module
calcul:	

    MULT $a0, $a0
    MFHI $t0
    MFLO $t1

    MULT $a1, $a1
    MFHI $t2
    MFLO $t3

    MULT $a2, $a2
    MFHI $t4
    MFLO $t5
    
    add $t1, $t1, $t3 
    add $t0, $t2, $t0
    add $t0, $t4, $t0

    clz $t1, $t0    
    srl $t2, $t1, 1 
    
    lb $t4, 00000001
    addi $t6, $t2, -1
    sll $t4, $t4, $t6	
    
    boucle:
	div $t5, $t4
	MFLO $t6  
	negu $t7, $t4
	add $t6, $t6, $t7 
	srl $t6, $t6, 1	   
	add $t4, $t4, $t6  

	li $t7, 00000001 
	bge $t6, $t7, boucle
	nop
    .end 
    
    addi $v0, $t4, 0
.end module


