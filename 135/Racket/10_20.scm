#lang scheme

(define (myAppend x L)
	(if (null? L) (cons x L)
					(cons (car L) (myAppend x (cdr L)))))

(myAppend 2 `(4 5 6))

(define (concat L M)
	(if (null? L) M
					(cons (car L) (concat (cdr L) M))))

(concat `(1 2 3) `(7 6 5))


(define (isEven x) (= 0 (modulo x 2)))
(define (isOdd x) (= 1 (modulo x 2)))
(define (isNeg x) (< x 0))
(define (isPos x) (> x 0))
							
(isEven 2)
(isEven 7)

(isOdd 2)
(isOdd 7)

(isNeg -1)
(isNeg 2)

(isPos 2)
(isPos -1)

(define (removeIf f L)
	(if (null? L) '()
		(if (f (car L)) (removeIf f(cdr L))
			(cons (car L) (removeIf f(cdr L))))))

(removeIf isEven `(1 2 3 4 5 6))
(removeIf isOdd `(1 2 3 4 5 6))
(removeIf isNeg `(1 -2 3 4 5 6))

(removeIf null? `(() (2 3) (4 5)))

