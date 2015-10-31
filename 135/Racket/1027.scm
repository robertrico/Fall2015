#lang scheme


(define (isEven x) (= 0 (modulo x 2)))
(define (isOdd x) (= 1 (modulo x 2)))
(define (isNeg x) (< x 0))
(define (negate x) (- 0 x))
(define (isPos x) (> x 0))
(define (square x) (* x x))
(define (cube x) (* x (* x x)))

(define (remove-if-builder f)
	(define (g L)
		(if (null? L) '()
			(if (f (car L)) (g (cdr L))
				(cons (car L) (g (cdr L))))))
g
)


(define (removeIf f L)
	(if (null? L) '()
		(if (f (car L)) (removeIf f(cdr L))
			(cons (car L) (removeIf f(cdr L))))))

(define (remove-if-builderv2 f)
	(lambda (L)
		(removeIf f L)))

(define removeEvens (remove-if-builder isEven))
(define removeEvensv2 (remove-if-builderv2 isEven))

(removeEvens '(1 2 4 5 8 7 4))
(removeEvensv2 '(1 2 4 5 8 7 4)) ;Output should be the same as above

((remove-if-builder isOdd) '(1 2 3 5 4 8 7 9 6 8))

(newline)
(newline)

; We want a function to take two functions f(x) and g(x), and return f(g(x))
(define (composeDef f g)
	(define (h x) (f (g x)))
	h
)

(define (composeDefv2 f g)
	(lambda (x)
		(f (g x))))

(display "((composeDef negate square) 10) = ")
((composeDef negate square) 10)

(display "((composeDef square cube) 2) = ")
((composeDef square cube) 2)
(display "((composeDef cube square) 2) = ")
((composeDef cube square) 2)


(define fourD (composeDef cube cube))
(define fourDv2 (composeDef cube cube))

(display "(fourD 10) = ")
(fourD 10)
(display "(fourDv2 10) = ")
(fourDv2 10)

(if (= 0 (- (fourDv2 10) (fourD 10))) (display "fourD and fourDv2 are equal")
	(display "fourD and fourDv2 are not equal"))

(define fiveD (composeDef fourD fourD))
;(fiveD 10) BIG
(define sixD (composeDef fiveD fiveD))
;(sixD 10) BIGGER
(define sevenD (composeDef sixD sixD))
;(sevenD 10) TOO BIG 
(newline)
(newline)

;###############################################################################
;#################### Tail Recursion ###########################################
;###############################################################################

;Factorial of x = x * factorial(x-1) factorial(5) = 5*factorial(4)
(define (factorialv1 x) 
	(if (= x 0) 1 
				(* x (factorialv1 (- x 1)))))
(display "Factorial Version 1")
(newline)
(factorialv1 5)

;because order of operations, multiplication is the last operation performed
;therefore, this is not a tail recursive function

; to convert to tail recursion
	;▪ pre-compute operations done after the recursive call (if possible)
	;▪ pass the latter results as final parameters (accumulating parameters) to the recursive call
	;▪ Initialize accumlating parameters with an external driver call
	;▪ May need to adjust base case

(define (tailFactorial x product)
	(if (= x 0) product
		(tailFactorial (- x 1) (* x product))))

(define (factorial i) (tailFactorial i 1))

(display "Factorial Version 2")
(newline)
(factorial 5)

(newline)
(newline)
