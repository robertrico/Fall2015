favoriteNumbers(terry,[1,2,3,4]).
favoriteNumbers(jerry,[5,6,7,9]).
lastEle([X],X).
lastEle([_|Y],Z) :- lastEle(Y,Z). /* Underscore is to avoid the singleton error*/
concat([],M,M).
concat([H|X],M,[H|T]) :- concat(X,M,T).
