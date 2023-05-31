; partners: akshat4, ribhavs2,adnanmc2
;In this programming assignment, we wrote an LC-3 program capable of evaluating postfix expressions (aka reverse polish notation) using a stack. 
;A postfix expression is a sequence of numbers ('1','5', etc.) and operators ('+', '*', '-', etc.) where every operator comes after its pair of operands. 
;For example “3 + 2” would be represented as “3 2 + ­” in postfix. The expression "(3 − 4) + 5" with 2 operators would be "3 4 − 5 +" in postfix.
; We have handled the multiplcation and division using 4 different testcases to check for all possible combination of positive and negative values
;REGISTER TABLE
;R0: CHARACTER TAKEN FORM THE USER 
;R1: LOCAL REGISTERS IN A FUNCTION
;R2: LOCAL REGISTERS IN A FUNCTION
;R3: INPUT REGISTERS
;R4: INPUT REGISTERS
;R5: OUTPUT FROM THE FUNCTION
;R6: LOCAL REGISTER USED FOR OPERATINONS
;R7: USED in JSR
.ORIG x3000
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ; We are using the Evaluate function to take in our input character and then determine if it's a operator, operand, space
EVALUATE
	GETC                    ; Takes in user input
	OUT                     ; Outputs on the csreen and stores the value in R0

	LD R2, ASCII_SPACE
	NOT R2, R2
	ADD R2, R2, #1
	ADD R2, R2, R0
	BRz EVALUATE

	LD R2, ASCII_FOR_POW    ; We will now subtract 94 in the next few steps to check if its exponent or not
	NOT R2,R2               ; negating 94 to subtract
	ADD R2, R2, #1           ; R2 -> #-94
	ADD R0, R0, R2          ; R0 -> R0 - #94
	BRz EXP                 ; if zero branch to Exponent function


	LD R2, ASCII_EQ_POW_DIF ; #33 ; Add 33 to check if the char is EQUAL 
	ADD R0, R0, R2
	BRz EQUAL               ; If yes move to EQUAL

	ADD R0,R0, #13          ; Adding 13
	BRn NOT_NUMBER 

	ADD R2, R0, #-9          ; Adding -9 to cehck for invalid Characters
	BRp INVALID 
	BRnzp DO_PUSH            ; if not it will be a number and we will push it onto the Stack
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
NOT_NUMBER
	ADD R0, R0, #6 

	BRnzp OPERATOR
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ASCII_FOR_POW .FILL x5E
ASCII_EQ_POW_DIF .FILL x21
ASCII_SPACE .FILL x20
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;  R0: We are using this Register for storing and printing the Values through TRAPx21 OUT

;  R3 : We are using this regsiter as a Digit Counter 

;  R4 : We are using this register as a Bit Counter 

;  R5 : We are using this register to store the bits during the Left Shift

;  R6 : We are using this register to store the frequency of each Charecter 



PRINT_HEX 

AND R3, R3, #0
ADD R3, R3, #4
ST R5, RESULT_OF_EXPRESSION
ADD R6, R5, #0
	
EACH_LINE
	AND R5, R5, #0 ; Initializing R5
	AND R4, R4, #0 ; Initializing R4
	ADD R4, R4, #4 ; Setting the Bit Counter to 4
DIGIT_GET
	ADD R5, R5, R5 ; Left Shifting R5
	ADD R6, R6, #0 ; To set up the Branch condition
	BRzp SHIFT     ; If its zero Branch 
	ADD R5, R5, #1 ; If its not zero add 1 to the temporary register 

SHIFT
	ADD R6, R6, R6  ;left shift R6
	ADD R4, R4, #-1 ; decrement the bit counter
	BRp DIGIT_GET   ; if the bit counter is positive go back to the previous LABEL, otherwise move to the next set of digits

ADD R5, R5, #-9 	; Adding the -9 to check weather its a digit or an alphabet in HEX of its ASCII value
BRnz DIGIT      	;If its Negative or Zero it means it's a digit
LD R0, ALPHA_ASCII  ; Otherwise it's a alphebet 
ADD R0, R5,R0 		; Add the Value we got from R5 to ALPHA_ASCII to get the correct value to be printed on to the screen
BRnzp PRINT 		; Regardless move to the print condition  

DIGIT
	LD R0, DIGIT_ASCII ; Load the value into R0
	ADD R0, R0, R5     ; Add the Value we got from R5 to DIGIT_ASCII to get the correct value to be printed on to the screen

PRINT
	TRAP x21
	AND R0, R0, #0 ; Initialize R0
	ADD R3, R3, #-1 ; Decrement the COunter
	BRp EACH_LINE ; If its postive countinue with the next set of bits

	LD R5, RESULT_OF_EXPRESSION

	BRnzp DONE



ALPHA_ASCII .FILL x0040 ; hexadecimal ascii code for @''
DIGIT_ASCII .FILL X0039 ; hexadecimal ascii code for '9'
RESULT_OF_EXPRESSION .BLKW #1

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DO_PUSH  
	JSR PUSH        ; Move to push the value on the stack

	ADD R5, R5, #0 
	BRp INVALID     ; Chekcing for overflow of stack
	BRnzp EVALUATE  ;Take in a new value 


;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
EQUAL

	JSR POP         ; If it encounters equal first pop two value
	ADD R5, R5, #0  
	BRp INVALID_FOR_EQUAL

	ST R0, EQUAL_TEMP_LOC

	JSR POP
	ADD R5, R5, #0
	BRz INVALID_FOR_EQUAL

	LD R1, INVALID_FLAG
	ADD R1, R1, #-1
	BRz DO_INVALID
	LD R0, EQUAL_TEMP_LOC
	ADD R5, R0, #0

	BRnzp PRINT_HEX  ; After poping the values print it 

EQUAL_TEMP_LOC .BLKW #1
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

DO_INVALID
	LEA R0, INVALID_STRING
	PUTS
	BRnzp DONE




;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
OPERATOR              ; To check for different operators
	ST R0, OPERATOR_OFFSET

	JSR POP             ;If it encounters an Operator pop two items to perform the operation
	ADD R5, R5, #0
	BRp INVALID
	ADD R3, R0, #0

	JSR POP
	ADD R5, R5, #0
	BRp INVALID
	ADD R4, R0, #0

	LD R0, OPERATOR_OFFSET
	ADD R0, R0, #0
	BRz DO_MUL          ; Do Multiply

	ADD R0, R0, #-1
	BRz PLUS            ; Do Addition

	ADD R0, R0, #-2
	BRz MIN             ; Do Subtraction

	ADD R0, R0, #-2
	BRz DIV             ; Do Divsion


	;ADD R0,R0, #15
	;BRz EVALUATE ; Space encountered

	BRnzp INVALID       ; Else give an invalid message
OPERATOR_OFFSET .BLKW #1
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


PLUS	
;input R3, R4
;out R0
;doing R0=R3+R4
	ADD R0, R3, R4       ; Addition of the two Values from the Stack
	BRnzp DO_PUSH        ; Push the value onto the Stack 
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
MIN	
;input R3, R4
;out R0
;doing R0 = R4 - R3
	NOT R0, R3
	ADD R0, R0, #1
	ADD R0, R0, R4

	BRnzp DO_PUSH 
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DO_MUL
	JSR MUL
	BRnzp DO_PUSH 
MUL
;input R3, R4
;out R0
; As we have to encounter for 4 diff possible cases we have various functions under the Multiplication function
	ST R4, MULT_SAVE_R4
	AND R0, R0, #0
	ADD R4, R4, #0; next BR to check if R4 is 0, result will also be 0 if R3 is 0 based on operations in MULT_LOOP
	BRn MUL_NEG

	ADD  R4, R4, #0
	BRp MUL_POS

	ADD  R4, R4, #0
	BRz MULT_DONE

MUL_NEG
	ADD R0, R0, R3
	ADD R4, R4, #1
	BRz CHANGE_SIGN
	BRnzp MUL_NEG

MUL_POS
	ADD R0, R0, R3
	ADD R4, R4, #-1
	BRz MULT_DONE
	BRnzp MUL_POS

CHANGE_SIGN
	NOT R0, R0
	ADD R0, R0, #1

MULT_DONE
	LD R4, MULT_SAVE_R4

RET
MULT_SAVE_R4 .BLKW #1
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DIV	
; Just like multiplication we have 4 possible cases for division as well
	
	AND R1, R1, #0 ; Quotient Counter
	AND R6, R6, #0 ; Temporary Value for repeated Subtraction
	AND R0, R0, #0 ; Output Value

; start checking r3 and r4 signs
	ADD R3, R3, #0
	BRn R3_NEG ; Atleast R3 is negative

	ADD R4, R4, #0
	BRn R4_NEG ; Only R4 is negative

;; Code for both positive
	NOT R6, R3
	ADD R6, R6, #1

DIV_LOOP 
    ADD R4, R4, R6
    BRn LOOP_END
    ADD R1, R1, #1
    BRnzp DIV_LOOP

R3_NEG
; if atleast r3 is neg
	ADD R4, R4, #0
	BRn BOTH_NEG

; IF ONLY R3 IS NEGATIVE
	ADD R6, R3, #0
DIV_R3NEG
	ADD R4, R4, R6
    BRn LOOP_END
    ADD R1, R1, #-1
    BRnzp DIV_R3NEG

; IF only r4 is neg
R4_NEG
	ADD R6, R3, #0
DIV_R4NEG
	ADD R4, R4, R6
    BRp LOOP_END
    ADD R1, R1, #-1
    BRnzp DIV_R4NEG

; If both are negative
BOTH_NEG
	NOT R6, R3
	ADD R6, R6, #1
DIV_LOOP_BN
    ADD R4, R4, R6
    BRp LOOP_END
    ADD R1, R1, #1
    BRnzp DIV_LOOP_BN
LOOP_END 
	ADD R0, R0, R1

	BRnzp DO_PUSH 
		
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
EXP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;doing R4^R3

	JSR POP
	ADD R5, R5, #0
	BRp INVALID
	ADD R3, R0, #0

	JSR POP
	ADD R5, R5, #0
	BRp INVALID
	ADD R4, R0, #0

	AND R1, R1, #0
	ADD R1, R1, R3 ; counter for power
	AND R3, R3, #0
	ADD R3, R3, R4

EXP_LOOP
	ADD R1, R1, #-1
	BRz EXP_DONE
	JSR MUL
	ST R0, EXP_INTERMEDIATE_VALUE
	LD R4, EXP_INTERMEDIATE_VALUE
	BRnzp EXP_LOOP
EXP_DONE
	LD R0, EXP_INTERMEDIATE_VALUE
	BRnzp DO_PUSH 

EXP_SAVE_R3 .BLKW #1
EXP_SAVE_R4 .BLKW #1
EXP_SAVE_R7 .BLKW #1
EXP_INTERMEDIATE_VALUE .BLKW #1
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PUSH	
;your code goes here
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
POP	
;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R4
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
INVALID_STRING .STRINGZ "Invalid Expression"
ASCII_EQUAL .FILL x003D ;
;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INVALID 
		AND R1, R1, #0
		ADD R1, R1, #1
		ST R1, INVALID_FLAG
		BRnzp EVALUATE
		
INVALID_FOR_EQUAL
	BRnzp DO_INVALID

;;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INVALID_FLAG .BLKW #1

DONE

.END
