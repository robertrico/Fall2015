#lang scheme

(define (testforzero x) (= x 0))

(define (uset) (if (testforzero (read)) "Equal to 0" "Not equal to 0"))

;Factorial of x = x * factorial(x-1) factorial(5) = 5*factorial(4)
(define (factorial x) 
	(if (= x 0) 1 
				(* x (factorial (- x 1)))))

(display "Enter a number") 
(newline)
(uset)

(newline)
(factorial 50)

(newline)
(factorial -1)
