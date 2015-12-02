/*Check if X^2+Y^2=Z^2*/
triple(X,Y,Z) :- W is X*X + Y*Y, U is Z*Z, W = U. 

factoyal(0,1).
factoyal(N,F) :- N1 is N-1, factoyal(N1,F1), !, F is F1*N.
