.text
	.global main
main:
	li t0, 100
	addi sp, sp, -4
	sw t0, 0(sp)
	lw a0, 0(sp)
	addi sp, sp, 4
	ret
