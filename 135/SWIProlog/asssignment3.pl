/*-------------------------------------------------------------------------
1.  "catSibling"
-------------------------------------------------------------------------*/

catSibling(X,Y) :- catowner(L,X),catowner(M,Y), catparent(J,L) , catparent(J,M), J\=M,X\=Y.

catparent(sniffles,jam).
catparent(sniffles,cocacola).

catowner(sniffles,frank).
catowner(jam,sam).
catowner(cocacola,betty).

/* -------------------------------------------------------------------------
2.  Implement the "listMins" function from Homework #2 as a Prolog rule.
    For example, the query:  listMins([2,8,7], [5,4,4], M) should
    result in Prolog's response:  M = [2, 4, 4].

(define (listMins L M)
	(if (null? L) '()
		(cons (if (< (car L) (car M)) (car L)
									  (car M)) (listMins (cdr L) (cdr M)))))
------------------------------------------------------------------------- */

listMins(X,_,[]) :- X = [] .
listMins([J|K],[L|M],X) :- listMins(J,K,X), J < L. 
listMins([J|K],[L|M],X) :- listMins(K,M,X), J > L. 
