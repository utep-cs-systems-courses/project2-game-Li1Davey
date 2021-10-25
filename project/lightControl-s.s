	.arch msp430g2553
	.p2align 1,0
	.text

	.global lightControl
	.extern P1OUT

lightControl:
	cmp #0, r12 		;Both Lights Off
	jne case_1
	and #~65, &P1OUT
	pop r0
case_1:	cmp #1, r12 		;Green Light On Only
	jne case_2
	bis #64, &P1OUT
	and #~1, &P1OUT
	pop r0
case_2: cmp #2, r12 		;Red Light On Only
	jne def
	and #~64, &P1OUT
	bis #1, &P1OUT
	pop r0
def:	bis #65, &P1OUT 	;Both Lights On
	pop r0
