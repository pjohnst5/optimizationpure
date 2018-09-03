# Datalog Parser

This datalog parser can be used to enter information into tables and join said tables by writing rules.

## How to run ##

Clone the repository

Run this command in the repo directory
* g++ -Wall -Werror -std=c++17 -g \*.cpp -o parser

Run this command replacing "in.txt" with your desired text file that follows the Datalog Grammar (See "Grammar" section for details)
* ./parser in.txt [ > outfile.txt]


## Grammar ##

Every text file used as input to the Datalog Parser must follow this grammar where words in all caps are tokens (see "Tokens" section).

* datalogProgram	-> 	
	* SCHEMES COLON scheme schemeList	
	* FACTS COLON factList 
	* RULES COLON ruleList 
	* QUERIES COLON query queryList


* scheme   	-> 	
	* headPredicate
* schemeList	->	
	* scheme schemeList | lambda
* fact    	->	
	* ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
* factList	->	
	* fact factList | lambda
* rule    	->
	* headPredicate COLON_DASH predicate predicateList PERIOD
* ruleList	->	
	* rule ruleList | lambda
* query	        ->      
	* predicate Q_MARK
* queryList	->	
	* query queryList | lambda





* headPredicate	->	
	* ID LEFT_PAREN ID idList RIGHT_PAREN
* predicate	->	
	* ID LEFT_PAREN parameter parameterList RIGHT_PAREN

* predicateList	->	
	* COMMA predicate predicateList | lambda
* parameterList	-> 	
	* COMMA parameter parameterList | lambda
* stringList	-> 	
	* COMMA STRING stringList | lambda
* idList  	-> 	
	* COMMA ID idList | lambda

* parameter	->	
	* STRING
* parameter	->	
	* ID
* parameter	->	
	* expression

* expression	-> 	
	* LEFT_PAREN parameter operator parameter RIGHT_PAREN
* operator	->	
	* ADD | MULTIPLY

## Tokens
Tokey Type  | Description | Examples
------------- | ------------- | -------------
COMMA  | The ',' character  | ,
PERIOD  | 	The '.' character  | Content Cell
Q_MARK  | Content Cell  | Content Cell
LEFT_PAREN  | Content Cell  | Content Cell
RIGHT_PAREN  | Content Cell  | Content Cell
COLON  | Content Cell  | Content Cell
COLON_DASH  | Content Cell  | Content Cell
MULTIPLY  | Content Cell  | Content Cell
ADD  | Content Cell  | Content Cell
SCHEMES  | Content Cell  | Content Cell
FACTS  | Content Cell  | Content Cell
RULES  | Content Cell  | Content Cell
QUERIES  | Content Cell  | Content Cell
ID  | Content Cell  | Content Cell
STRING  | Content Cell  | Content Cell
COMMENT  | Content Cell  | Content Cell
UNDEFINED  | Content Cell  | Content Cell

