;	DME assembly file, generated by lcc 4.2

;  temp boiler plate puts SP at 0x64 and branches to main
	ldi	sp, 0x64
	br	_main


	.dseg
	.global _result
_result:
	defw 0x0
	.dseg
L2:
	defw 0x1
	defw 0x2
	defw 0x3
	.global _foo
	.cseg
_foo:
	push	bp
	mov	bp, sp
	ldi	r4, 8
	sub	sp, r4, sp
	lda	r4,-6[BASE][BASE]
	lda	r3,L2[BASE][BASE]
	ldw	r4,-6(bp)
	ldw	r3,-2(bp)
	add	r4,r4,r3
	stw	r4,-8(bp)
	ldw	r1,-8(bp)
L1:
	mov	sp, bp
	pop	bp
	pop	pc

	.global _main
_main:
	push	bp
	mov	bp, sp
	ldi	r4, 2
	sub	sp, r4, sp
	ldi	r4, 2
	push	r4
	addi	r1,pc,4
	push	r1
	br	_foo XX
	stw	r1,-2(bp)
	ldw	r4,-2(bp)
	addi	r4,r4,1
	stw	r4,-2(bp)
	ldw	r4,-2(bp)
	lda	r3,_result[BASE][BASE]
	stwb	r4,r3,r0
	mov	r1,r4
L4:
	mov	sp, bp
	pop	bp
	pop	pc

	.end
