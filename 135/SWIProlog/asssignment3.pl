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
2.  "listMins" 
------------------------------------------------------------------------- */

listMins([],[],[]).
listMins(L,[],L).
listMins([],L,L).
listMins([X|L],[Y|M],[X|H]) :- X = Y, listMins(L,M,H).
listMins([X|L],[Y|M],[X|H]) :- X < Y, listMins(L,M,H).
listMins([X|L],[Y|M],[Y|H]) :- X > Y, listMins(L,M,H).

/* -------------------------------------------------------------------------
5.  "overlap2" 
------------------------------------------------------------------------- */

overlap2(X,Y) :- 
