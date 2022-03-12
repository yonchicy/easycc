.text
	.global main
main:
	li t0, 2233
	addi sp, sp, -4
	sw t0, 0(sp)
	lw a0, 0(sp)
	addi sp, sp, 4
	ret
