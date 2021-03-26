# Stack-based Processor # 
### Current version: 7 (data: 7.12.19, time: 11:00) ###

##### Instruction: #####
1)	Installing;
2)	Writting code;
3)	Compilation;
4)	Controlling code;
5)	Updates;

##### 1)Installing: #####
*	compilation.cpp - it's main function that creates a machine code reading your code and gives it to processor.cpp
*	functions.h - it just has important for work functions
*	tables.h - it contains constants for creating machine code

*	processor.cpp - it's main function that do operations
*	stack.cpp & stack.h - simpled by MarkG fuctions in stack
*	tables.h - constants that helps to do smaller files

*	Code.txt - you have to write code on that language exactly in this file

##### 2)Writting code: #####   

*	Accessed variables: ax, bx, cx, dx;
*	In order to create comments, you can write after "space" after last element in the operation string and before ";" (exaple in the "Code.txt")

FUNCTIONS: (without brackets)                     
1)	push (value / variable);
2)	pop (nothing / variable); - command "pop;" means delete last element;
3)	add (nothing / variable); 
4)	mult (nothing / variable);
5)	sub (nothing / variable);
6)	div (nothing / variable);
7)	scan (variable);
8)	print (nothing / variable); - command "print;" means print every number; 
9)	exit (nothing);
10)	(string); - create a label where you will can to jump in order to create circle of operations or for "if" statement
11)	jump (num < 10); - jump into the num
12)	cmp (num/var,num/var); - you can write using ',' without spaces.
	Example: cmp ax,78;
13)	cmp (num/var num/var); - also using spaces as many as you want
	Example: cmp  43   bx;
14)	"cmp" operation allows you to use cmp of numbers many times until next cmp operation (example in the description)
15)	= (string); - if values is equal => jump into num; else continue operations;
16)	!= (string);
17)	> (string);
18)	>= (string);
19)	< (string);
20)	<= (string);

Extra functions: (it uses another stack for these operations)
1)	pushE (value / variable);
2)	popE (nothing / variable);
3)	addE (nothing / variable); 
4)	multE (nothing / variable);
5)	subE (nothing / variable);
6)	divE (nothing / variable);
8)	printE (nothing / variable);

RULES:
1) 	Programm ignores your spaces, tabs, or enters
2) 	In the of end of every action (not neccesary a string) you have to put ';'  
3) 	Other rules isn't neccesary

##### 3)Compilation: #####

To compilate: make complication.cpp and after message that function is read
to use, you can make processor.cpp - follow instructions in the window

Write code you can in .txt file that was named Code.txt

##### 4)Controlling code: #####

Compilator can find mistakes: 
*	in writting (psh instead of push)
*	in logic (scan 5 doesn't have a meaning for programm)
*	in proccessing (your stack is full, popped so many numbers)

To repair your code, follow the number of mistaken string 

##### 5)Updates: #####

MAJOR - big update, MINOR - small

1)	28/11/19: MAJOR: Program was created;
2)	29/11/19: MINOR: Repairs mistake with variables
3)	02/12/19: MAJOR: Added classes, program began to work faster. 
4)	04/12/19: MINOR: Repairs some mistakes in 3rd version with enter numbers. Added external description of finding mistakes in operation (processing). Added labels and possibilities to jump into them. Wasn't done labels with proceesing
5)	05/12/19: MAJOR: Added labels with jumpes. Now you can do an infinite circle (example in the description). File that was translated to processor now has .bin format
6)	06/12/19: MINOR: Added comments, rewrote example.
7)	07/12/19: MAJOR: Added cmp operation and conditional statements.
8)	13/12/19: MAJOR++; Labels now can be called as you want (less 200 bytes). Added extra stack. Now you can do every algorithm.
