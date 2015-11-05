#lang scheme

;---A---------------------------------------------------------------------------

(define (firstNums x)
	(if (> 10 (/ (- x (modulo x 10)) 10)) x
		(firstNums (/ (- x (modulo x 10)) 10))))

(define (buildLR x y)
	(if (< 0 (- 10 (abs x))) -1
		(if (< 0 (- 10 (abs y))) -1
			(+ (* (firstNums (abs x)) 100) (+ (- (modulo (abs y) 10) (modulo (abs y) 10)) (modulo (abs y) 100))))))

(buildLR 2365656 456)
(buildLR 858373476 23401230156)
(buildLR -8476 -234012)
(buildLR 86 -234012301)
(buildLR 77786 -1230156)
(buildLR 6 -13412)
(buildLR -346 2)
(buildLR 8 6)
(buildLR -2 -9)

;Prove Type Integer
(if (= 9999 (+ 8888 (buildLR 11898989 646464646411))) (display "Data Type is integer")
	(display ("Data Type is not integer")))
(newline)

;---B---------------------------------------------------------------------------

(define (listMins L M)
	(if (null? L) '()
		(cons (if (< (car L) (car M)) (car L)
									  (car M)) (listMins (cdr L) (cdr M)))))

(listMins `(1 2 3) `(0 1 5))
(listMins `(6 5 3 7 8 9 53 22) `(2 43 1 23 45 65 23 78))
(listMins `(6 5 3 7 8 9 53 22) `(2 -43 1 -23 -45 65 23 78))

;---C---------------------------------------------------------------------------

(define (isEven x)
	(equal? 0 (modulo x 2))) 

(define (isOdd x)
	(not (isEven x)))

(define (listLen L)
	(if (null? L) 0 
		(+ 1 (listLen (cdr L)))))

(define (getMidIndex L)
	(if (isEven (listLen L)) (list-ref L (- (quotient (listLen L) 2) 1)) 
		(list-ref L (quotient (listLen L) 2))))

(define (unwind L)
 (if (null? L) '()
    (cons (getMidIndex L) (unwind (remove (getMidIndex L) L))))) 

(unwind '(7 8 2 9 5 6)) ;should return (2 9 8 5 7 6)
(unwind '(7 8 2 3 9 5 6)) ;should return (3 2 9 8 5 7 6)
(unwind '(1 2 3 4 5)) ;should return (3 2 4 1 5)
(unwind '(1 2 3 4 5 6)) ;should return (3 4 2 5 1 6)

;---D---------------------------------------------------------------------  

(define (isNeg x)
	(> 0 x)) 

(define (truthList f L)
	(if (null? L) '()
		(cons (f (car L)) (truthList f (cdr L)))))

(define (score L)
	(if (null? L) 0
		(if (car L) (+ 1 (score (cdr L)))
			(score (cdr L)))))

(define (functionWinner f g L)
	(if (= (score (truthList f L)) (score (truthList g L))) 0
		(if (> (score (truthList f L)) (score (truthList g L))) 1
		2)))

(functionWinner isNeg isEven '(7 -3 2 1 -5))
(functionWinner isNeg isEven '(7 3 2 1 -5))
(functionWinner isNeg isEven '(7 4 -3 2 1 -5))
(functionWinner isNeg isEven '(7 4 6 2 1 -5))


;------E-----------------------------------------------------
(define (getNestedCount L)
	(if (null? L) 0
		(if (list? (car L)) (+ (getNestedCount (cdr L)) (getNestedCount (car L)))
			(+ 1 (getNestedCount (cdr L))))))

(display "No nest = 5 ? ")
(getNestedCount '(1 2 3 4 5))
(display "1 nest = 7 ? ")
(getNestedCount '((2 2) 1 2 3 4 5))
(display "3 nest = 14 ? ")
(getNestedCount '(1 2 3 4 5 (2 (1 2 (1 2 3) 3 4) 2)))
(display "3 nest = 6 ? ")
(getNestedCount '(2 3 (4 (7 6) 5)))

;----F--------------------------------------------------  
(define (makeCutter x)
	(define (preCut L x)
		(if (= 0 x) '()
			(cons (car L) (preCut (cdr L) (- x 1)))))
	(lambda (L)
		(preCut L x)))

(define testCut3 (makeCutter 3))
(testCut3 '(1 2 3 4 5 6 7))

(define testCut8 (makeCutter 8))
(testCut8 '(1 2 3 4 5 6 7 9 8 10 12))

