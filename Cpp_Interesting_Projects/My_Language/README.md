# --C #

### Finished 16/05/2020 ###

Was written on base language C++17
Can be used in GCC and VS compiles.

The programmer:
# EverRest (Goncharov Mark) #

### Version: ER_1.4 ###


# Itroduction:
	The programm was done for educational purposes only - the last project in first course ILab. It's the language I used in ingeneer lessons, therefore it's not an useless programm)) 

# Rules: #

### 1)Common rules: ###

-	Every action must be ended with ';'

-	Variables should be declared with 'new', further 	it's 	not necessary

-	Every spaces, tabs, relate to the next string are 	ignored by programm

-	Comments can be:
	using '#' till the end of the current string	
	#{ comments }# is equal to /* comments */ in C++

-	Math operations doing with obviously priority

### 2)Conditions: ###

-	If and while declares should have such view:
	if [condition] {action} | while [conditions] {actions}

-	Else can be used too (can be not declared)
	if ...{actions} else {actions}

-	Complexity conditions doign with obviously priority	too
	An example:
	new cat = 65;
	if [cat = 65 or cat  < 65 and cat != 65] -> true
	if [(cat = 65 or cat  < 65) and cat != 65] -> false
	


### 3)Functions: ###

-	In declaration first parameter is count of NEXT 	parameters
	main[0], do_cat[1, kitten], make_some_noize[3, a, b, c]

-	Every programm must have 'main[0]' - it's the start 	of 	programm

-	You can return value or not - how you want, the key 	word 	is 'result'
	(instead of return in C++)

-	Every function must have only one or zero result 	keys.
	In that version you can use result only when programm 	ends

	(But in some cases if you understand where you can use 	everywhere and more than one...
	I hope I will create a solution)

-	In function you give only a number - not a variable 	and 	so on, that means:
	-it will not change the value of giving number
	-you shouldn't create in function names again - look at 	the example
		
-	Function that you declare can be seen everywhere - i 	hope 	you're glad to read this

### 4)Macroses: ###

-	The macroses includes fast algorithm that replaces 	strings with different containers. It's no matter what 	exactly in the string (you can look at example 	"macroses")
-	The warning: the expressions \\string1|string2\\ - it 	means that every "string1" in the code will be replace 	to "string2" even before programmer will call method 	.Start()   