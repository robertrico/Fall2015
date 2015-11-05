#lang scheme

;Eric Wong, CSC135, Professor Gordon, 11/4/2015

(define (isEven x)
	(equal? 0 (modulo x 2))) 

(define (isOdd x)
	(not (isEven x)))

(define (getTwoDigits x)
	(if (> x 99) (getTwoDigits (quotient x 10))
		x))
(define (getSmallest x y)
	(if (> x y) y
		x))
(define (getLength L)
	(if (null? L) 0 
		(+ 1 (getLength (cdr L) ))))
(define (getHalfLength L)
	(if (null? L) -1
		(quotient (getLength L) 2)))

(define (getMedian L)
	(if (isEven (getLength L)) (list-ref L (- (getHalfLength L) 1)) 
		(list-ref L (getHalfLength L))))

;-------------------------------------A------------------------------------------
(define (buildLR x y)
 (if (< (abs x) 10) -1
	(if (< (abs y) 10) -1
		(+ (* 100 (getTwoDigits (abs x))) (modulo (abs y) 100)))))

(buildLR 78432 -139) ;should return 7839
(buildLR -78432 139) ;should return 7839
(buildLR -78432 -139) ;should return 7839
(buildLR 0 100)	;should return -1
(buildLR 100 0) ;should return -1
;-------------------------------------B------------------------------------------
(define (listMins L M)
 (if (null? L) '() 
 	(cons (getSmallest (car L) (car M)) (listMins (cdr L) (cdr M)))))
	
(listMins '(2 8 7) '(5 4 4)) ;should return (2 4 4)
;-------------------------------------C------------------------------------------
(define (unwind L)
 (if (null? L) '()
    (cons (getMedian L) (unwind (remove (getMedian L) L))))) 

(unwind '(7 8 2 9 5 6)) ;should return (2 9 8 5 7 6)
(unwind '(7 8 2 3 9 5 6)) ;should return (3 2 9 8 5 7 6)
;-------------------------------------D------------------------------------------
;(define (functionWinner F G L)

;-------------------------------------E------------------------------------------
;(define getNestedCount L)

;-------------------------------------F------------------------------------------
;(define makeCutter N)




