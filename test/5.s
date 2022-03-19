	.text
	.global main
main:
	li t0, 2233
	addi sp, sp, -4
	sw t0, 0(sp)
	lw t1, 0(sp)
	addi sp, sp, 4
	lw t0, 0(sp)
	addi sp, sp, 4
	add t0,t0,t1
	addi sp, sp, -4
	sw t0, 0(sp)
	lw a0, 0(sp)
	addi sp, sp, 4
	ret
