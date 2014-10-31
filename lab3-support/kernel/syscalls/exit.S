	.file	"exit.S"
	.text

	.global exit

exit:
	ldr	r3, =ksp
	ldr	sp, [r3]
	ldr     r3, =err
        str     r3,[r0]

	ldmfd	sp!, {r0-r12, lr}
	add	sp, sp, #4
	mov	pc, lr
	
