num(1).
num(2).
num(3).
num(4).
num(5).
num(6).
num(7).
num(8).
num(9).
num(0).

crypto(P,H,A,R,E,D,L,I,O,S) :-
    %% assign all the numbers
    num(P), num(H), num(A), num(R), num(E), num(D), num(L), num(I), num(O), num(S),

    %% make sure the elements don't equal each other
    P \= H, P \= A, P \= R, P \= E, P \= D, P \= L, P \= I, P \= O, P \= S,
    H \= A, H \= R, H \= E, H \= D, H \= L, H \= I, H \= O, H \= S,
	A \= R, A \= E, A \= D, A \= L, A \= I, A \= O, A \= S,
	R \= E, R \= D, R \= L, R \= I, R \= O, R \= S,
    E \= D, E \= L, E \= I, E \= O, E \= S,
   	D \= L, D \= I, D \= O, D \= S,
	L \= I, L \= O, L \= S, 
	I \= O, I \= S,
	O \= S,
	
			
    PA is (P * 10) + A, 
    RA is (R * 10) + A,	
	SH is (S * 10) + H,
	OEOA is (O * 1000) + (E * 100) + (O * 10) + A,
	SS is (S * 10) + S,
	ES is (E * 10) + S,
	OI is (O * 10) + I,
	
    ANSWER1 is P * I * PA * RA,  
	ANSWER2 is SH * OEOA, 
	ANSWER3 is H * SS * ES * OI,
	
	PHARE is (P * 10000) + (H * 1000) + (A * 100) + (R * 10) + E,
    DELAI is (D * 10000) + (E * 1000) + (L * 100) + (A * 10) + I,
	ALORS is (A * 10000) + (L * 1000) + (O * 100) + (R * 10) + S,
	
    %% compare the results to make sure they are equal. we only one should have one answer
    PHARE = ANSWER1,
	DELAI = ANSWER2,
	ALORS = ANSWER3,!.
	
	%if it doesn't work then take out the ,! on line 47