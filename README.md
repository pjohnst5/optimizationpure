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
PERIOD  | The '.' character  | Content Cell
Q_MARK  | The '?' character| ?
LEFT_PAREN  | The '(' character | (
RIGHT_PAREN  | The ')'  | )
COLON  | The ':' character | :
COLON_DASH  | the string ":-" | :-
MULTIPLY  | The '\*' character | \*
ADD  | The '+' character  | +
SCHEMES  | The string "Schemes"  | Schemes
FACTS  | The string "Facts"  | Facts
RULES  | The string "Rules"  | Rules
QUERIES  | The string "Queries"  | Queries
ID  | An identifier is a letter followed by zero or more letters or digits, and is not a keyword (Schemes, Facts, Rules, Queries).  | Valid - "Identifier1" Invalid - "1stPerson"
STRING  | A string is a sequence of characters enclosed in single quotes. White space (space, tab) is not skipped when inside a string. Two adjacent single quotes within a string denote an apostophe. THe line number for a string token is the line where the string begins. If a string is not terminated (end of file is encountered before the end of the string), the token becomes an undefined token. | Valid - " 'This is a string' " Valid - " 'This isn''t two strings' " Valid - " '' " (the empty string)
COMMENT  | A line comment starts with a has character (#) and ends at the end of the line or end of the file  | # hello
COMMENT | A comment may also be a block comment which starts with \#\| and ends with \|\#. Block comments may cover multiple lines. Block comments can be empty and multiple comments can appear on the same line. The line number for a comment token is the line where the comment begins. If a block comment is not terminated (end of file is encountered before the end of the comment), the token becomes an undefined token. | Valid - " \#\|\|\# " Valid - " \#\|This is a multiline comment \|\#"
UNDEFINED  | Anything that doesn't fit the above categories  | $%&
EOF | The end of the input file | 

