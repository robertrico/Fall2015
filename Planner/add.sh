#!bin/bash

if [ -z $1 ] 
then
	echo "Need Week Number";
	return -1;
fi
cp BaseCopy.txt Week$1.txt
