/*------------------------------------------------------------------------- 
1.  "catSibling"*/

catSibling(X,Y) :- catowner(L,X),catowner(M,Y), catparent(J,L) , catparent(J,M), J\=M,X\=Y.

catparent(sniffles,jam).
catparent(sniffles,cocacola).

catowner(sniffles,frank).
catowner(jam,sam).
catowner(cocacola,betty).

/* ------------------------------------------------------------------------- 
2.  "listMins"*/

listMins([],[],[]).
listMins(L,[],L).
listMins([],L,L).
listMins([X|L],[Y|M],[X|H]) :- X = Y, listMins(L,M,H).
listMins([X|L],[Y|M],[X|H]) :- X < Y, listMins(L,M,H).
listMins([X|L],[Y|M],[Y|H]) :- X > Y, listMins(L,M,H).

/* -------------------------------------------------------------------------
4.  "catFriends"*/


compareAtt([W|[X|[Y|[_|_]]]],[J|[L|[M|[_|_]]]]) :- W - J < 6, X - L < 3, Y - M < 2.
compareAtt([W|[X|[_|[Z|_]]]],[J|[L|[_|[N|_]]]]) :- !,W - J < 6, X - L < 3, Z - N < 2.
compareAtt([W|[X|[Y|[_|_]]]],[J|[L|[M|[_|_]]]]) :- W - J > 6, X - L > 3, Y - M > 2.
compareAtt([W|[X|[_|[Z|_]]]],[J|[L|[_|[N|_]]]]) :- W - J > 6, X - L > 3, Z - N > 2.

cat(ham,[4,20,19,1]).
cat(cheese,[4,18,17,1]).
cat(peanutbutter,[19,12,19,1]).

catFriends(X,L) :- cat(X,Y),cat(L,M), compareAtt(Y,M).


/*
5.  Write a Prolog rule "overlap2", that takes two lists, and returns true
    if the lists have at least two elements in common.  For example:

      overlap2([3,4,5],[7,8,3,9]).   should return false.
      overlap2([3,4,5],[4,7,3,8,6]).  should return true.

overlap2(X,Y) :- 
*/
