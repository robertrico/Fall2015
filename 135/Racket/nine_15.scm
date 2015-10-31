#lang scheme

(car `(3 4 5))
(cdr `(3 4 5))
(cons 6 `(3 4 5))
(cons (car `(3 4 5)) (cdr `(3 4 5)))
(car `((3 4) (5 6)))

(cons `(1 2) `(3 4))
(cons `(1 2) `((3 4)))
(cons `(1 2) `())
(cons `() `())
(list 3)

;(car `()) error thrown
;(cdr `()) error thrown

(null? `())
(null? (cons `() `()))
(null? `(1 2 3 4))

(define (last L)
	(if (null? (cdr L)) (car L)
						(last (cdr L))))
(last `(1 2 3 4))

(define (isMemberOf x L)
	(if (null? L) #f 
					(if (equal? x (car L)) #t 
										(isMemberOf x (cdr L)))))
(isMemberOf 3 `(4 5 8 6 3))

