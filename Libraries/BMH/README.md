# BMH - Boyer-Moore-Horspool algorithm #

This algorithm will help you to search faster in big data the most important information for you.
Use for finding pattern in the big (or even not so) string. There are some extra opportunity...

### Starting ###
	
	You should just copied the BMH.h to the programm folder and include it with ""
	
### Opportunity ###
	
	There are 3 functions for user: 
	first_find, count_find, full_find. 

Every function want to get

*	std::placeholder::_1 - the main std::string where we can find patterns 
*	std::placeholder::_2 - the data that you're searching for	

### Result ###

*	first_find() - find only first position of data in base string. Returns class BMH_PROG::finding, but I recommend to use auto. 

	##### Parameters: #####
	            const bool 
	                  is_find \true if found\
	            const std::string::const_iterator
	                  place \first symbol of finding\
	
	The fastest function but only represent first finding. If the speed of finding is most significant - use it!!!

*	count_find() - find only count of finding strings ("aaaa", "aa" found 3 times). Returns class BMH_PROG::copying, but I recommend to use auto. 

	##### Parameters: #####
	            const bool 
	                  is_find \true if found\
	            const size_t
	                  count \obviously\
	
	Isn't so fast - but sometimes you can use it (of course, if you want to understand: how often your word can be found)

*	full_find() - give full info that can get. Returns class BMH_PROG::full_information, but I recommend to use auto. 

	##### Parameters: #####
	            const bool 
	                  is_find \true if found\
	            const std::size_t
	                  count \obviously\
	            const std::vector<BMH_PROG::BMH_pair>
	                  place \first symbols of every finding\
                 
                  Here BMH_PROG::BMH_pair contains:
                  const iterator - where this place is 
                  size_t num_place - where in string this place is
	
### Conclusion ##

It's really cool to use it - my most important target was to do a tool that can be convinient for programmer and fast, because it's using pretty cool algorithm)  

