	.arch msp430g2553
	.p2align 1,0
	.text

	.global lightControl
	.extern P1OUT

lightControl:
	cmp #0, r12 		;Both LEDs Off
	jne case_1
	and #~65, &P1OUT
	pop r0
case_1:	cmp #1, r12 		;Green LED On Only
	jne case_2
	bis #64, &P1OUT
	and #~1, &P1OUT
	pop r0
case_2: cmp #2, r12 		;Red LED On Only
	jne def
	and #~64, &P1OUT
	bis #1, &P1OUT
	pop r0
def:	bis #65, &P1OUT 	;Both LEDs On
	pop r0
