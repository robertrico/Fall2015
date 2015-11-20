parent(carmen,herb,mary).
parent(alexander,herb,mary).
parent(andre,herb,mary).
female(carmen).
male(alexander).
male(andre).
sister(X,Y) :- female(X), parent(X,F,M), parent(Y,F,M), X\=Y.
