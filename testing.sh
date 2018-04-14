#!/bin/bash

echo "Comiling..." 

 g++ -Wall -Werror -std=c++17 -g *.cpp -o testex


 	echo " in50"
 ./testex in50.txt > actual.txt 
 diff actual.txt out50.txt

 	echo " in54"
 ./testex in54.txt > actual.txt 
 diff actual.txt out54.txt

 	echo " in55"
 ./testex in55.txt > actual.txt 
 diff actual.txt out55.txt

 	echo " in56"
 ./testex in56.txt > actual.txt 
 diff actual.txt out56.txt

 	echo " in58"
 ./testex in58.txt > actual.txt 
 diff actual.txt out58.txt

 	echo " in59"
 ./testex in59.txt > actual.txt 
 diff actual.txt out59.txt

 	echo " in61"
 ./testex in61.txt > actual.txt 
 diff actual.txt out61.txt

 	echo " in62"
 ./testex in62.txt > actual.txt 
 diff actual.txt out62.txt

 	echo " in64"
 ./testex in64.txt > actual.txt 
 diff actual.txt out64.txt

 echo "done" 
