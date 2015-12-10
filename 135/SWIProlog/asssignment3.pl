/*------------------------------------------------------------------------- 
1.  "catSibling" */

catSibling(X,Y) :- catowner(L,X),catowner(M,Y), catparent(J,L) , catparent(J,M), J\=M,X\=Y.

catparent(sniffles,jam).
catparent(sniffles,cocacola).

catowner(sniffles,frank).
catowner(jam,sam).
catowner(cocacola,betty).

/* ------------------------------------------------------------------------- 
2.  "listMins" */

listMins([],[],[]).
listMins(L,[],L).
listMins([],L,L).
listMins([X|L],[Y|M],[X|H]) :- X = Y, listMins(L,M,H).
listMins([X|L],[Y|M],[X|H]) :- X < Y, listMins(L,M,H).
listMins([X|L],[Y|M],[Y|H]) :- X > Y, listMins(L,M,H).

/* ------------------------------------------------------------------------- 
3.  "crypto" */

/* Assign Values to Variables*/
assignNum(1).
assignNum(2).
assignNum(3).
assignNum(4).
assignNum(5).
assignNum(6).
assignNum(7).
assignNum(8).
assignNum(9).
assignNum(0).

crypto(P,H,A,R,E,D,L,I,O,S) :-

	/* Permutations of all letters and assigned integer values */
    assignNum(P), assignNum(H), assignNum(A), assignNum(R), assignNum(E), assignNum(D), assignNum(L), assignNum(I), assignNum(O), assignNum(S),

	/* Ensure Uniquness */
    P \= H, P \= A, P \= R, P \= E, P \= D, P \= L, P \= I, P \= O, P \= S,
    H \= A, H \= R, H \= E, H \= D, H \= L, H \= I, H \= O, H \= S,
	A \= R, A \= E, A \= D, A \= L, A \= I, A \= O, A \= S,
	R \= E, R \= D, R \= L, R \= I, R \= O, R \= S,
    E \= D, E \= L, E \= I, E \= O, E \= S,
   	D \= L, D \= I, D \= O, D \= S,
	L \= I, L \= O, L \= S, 
	I \= O, I \= S,
	O \= S,
			
	/* Brute Force All Possible Answers */
    PA is (P * 10) + A, 
    RA is (R * 10) + A,	
	SH is (S * 10) + H,
	OEOA is (O * 1000) + (E * 100) + (O * 10) + A,
	SS is (S * 10) + S,
	ES is (E * 10) + S,
	OI is (O * 10) + I,
	
	/* Ensure Possible Answers With Provided Equations */
    CHECK1 is P * I * PA * RA,  
	CHECK2 is SH * OEOA, 
	CHECK3 is H * SS * ES * OI,
	
	/* 5 digit integers, base 10 (10^4 , 10^3 , 10^2 , 10^1 , 10^0) */
	PHARE is (P * 10000) + (H * 1000) + (A * 100) + (R * 10) + E,
    DELAI is (D * 10000) + (E * 1000) + (L * 100) + (A * 10) + I,
	ALORS is (A * 10000) + (L * 1000) + (O * 100) + (R * 10) + S,
	
	/* Ensure Answer Correctness */
    PHARE = CHECK1,
	DELAI = CHECK2,
	ALORS = CHECK3,!.

/* -------------------------------------------------------------------------
4.  "catFriends" */


compareAtt([W|[X|[Y|[_|_]]]],[J|[L|[M|[_|_]]]]) :- W - J < 6, X - L < 3, Y - M < 2.
compareAtt([W|[X|[_|[Z|_]]]],[J|[L|[_|[N|_]]]]) :- !,W - J < 6, X - L < 3, Z - N < 2.
compareAtt([W|[X|[Y|[_|_]]]],[J|[L|[M|[_|_]]]]) :- W - J > 6, X - L > 3, Y - M > 2.
compareAtt([W|[X|[_|[Z|_]]]],[J|[L|[_|[N|_]]]]) :- W - J > 6, X - L > 3, Z - N > 2.

cat(ham,[4,20,19,1]).
cat(cheese,[4,18,17,1]).
cat(peanutbutter,[19,12,19,1]).

catFriends(X,L) :- cat(X,Y),cat(L,M), compareAtt(Y,M).


/* -------------------------------------------------------------------------
5.  "overlap2" */

overlap2([W|X],M) :- member(W,M). 
overlap2([W|[X|T]],M) :- overlap2([X|T],M),overlap2(T,M). 
