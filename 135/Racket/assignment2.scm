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

;	"unwind" - takes a list and returns the unwinded version of
;	the list.  "Unwinding" a list means extracting the two centermost
;	elements and putting them at the front of the list, then repeating
;	the process until the entire list is "unwound".  For example,
;	(unwind '(7 8 2 9 5 6)) should return the list (2 9 8 5 7 6).
;	If the list has an odd number of elements, the centermost value
;	should be extracted first, then the algorithm proceeds normally.
;	For example, (unwind '(7 8 2 3 9 5 6)) would return (3 2 9 8 5 7 6).


(define (listLen L)
	(if (null? L) 0 (+ 1 (listLen (cdr L)))))

(define (extractEMid L l)
	(if (= (listLen L) (+ (/ l 2) 1)) (cons (car L) (cons (car (cdr L)) '())) 
			(extractEMid (cdr L) l)))

(define (extractOMid L l)
	(if (= (listLen L) (+ (/ (- l 1) 2) 1)) (car L) 
			(extractOMid (cdr L) l)))

(listLen `(1 2 3 4 5))
(listLen `(1 2 3 4 5 12 12 12 13))
(listLen `())
(listLen `(5))

(extractEMid '(1 2 3 4) (listLen '(1 2 3 4)))
(extractEMid '(1 2 3 4 5 7 8) (listLen '(1 2 3 4 5 6 7 8)))
(extractEMid '(1 2 3 4 5 7 8 9 10) (listLen '(1 2 3 4 5 6 7 8 9 10)))

(extractOMid '(1 2 3 4 5) (listLen '(1 2 3 4 5)))
(extractOMid '(1 2 3 4 5 7 8 9 10 11) (listLen '(1 2 3 4 5 6 7 8 9 10 11)))



