# My realization of map #
### Was finished 27/02/2020 ###
##### That map in some cases now is better than original #####

I made two operators: [] and ()
Difference between them:
1)	They both return T2&
2)	They both can replace the value in the key:
	
##### Example: #####
	my_map.insert(23, "something");
	my_map[23] = "anything";
	And my_map(23) = "anything" can do exactly the same thing

3)	my_map[] CAN'T do another object in order to make progress safety. It can only change value
##### Example: #####
	my_map[56] = "cool";
	my_map.full_print() // shows nothing in the map

4)	my_map() CAN do another object in every case if /key/ wasn't found
##### Example: #####
	my_map(56) = "cool";
	my_map.full_print() // shows our object

5)	But my_map() isn't safe for user - it's source of mistakes. You can see problem if you're going to use object in another function
##### Example: #####
	std::cout << my_map(100); // at first you will see new object - he didn't exist before calling of this function. In order to avoid this mistakes use () only for creating new object or for changing elements 
