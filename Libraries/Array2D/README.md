# 2D Array #

I did this, because I was tired use 'std::unique_ptr', 'new', 'std::vector<std::vector>>'. This structures are complexity, inconvinient with 2D array and I'm confident you understand the reason why.

There is a not bad solution, I often use it. That's why you can download it too - only Array2D.h file)

### Using ###

##### Constructors: #####
1)	Array2D(                            size_t max_x, size_t max_y) noexcept;
2)	Array2D (std::unique_ptr<T>&& data, size_t max_x, size_t max_y) noexcept;
3)	Array2D (const T*             data, size_t max_x, size_t max_y) noexcept;

##### Functions: #####

*	Standart operator [] and operator *
*	void operator = (const T* other)       noexcept;
*	void dump       ()               const noexcept; 

Dump is writing array as a table (for analysing array).

##### Iterators #####
1)	lib::Array2D<T>::iterator
2)	lib::Array2D<T>::const_iterator
3)	lib::Array2D<T>::safe_iterator
	
Difference - const_iterator can't change data, safe_iterator can't read out of array, has a unique method:
 
bool is_out_range() const noexcept

##### Iterator's functions #####
1)	Array2D<T>::iterator       begin ()       noexcept;
2)	Array2D<T>::const_iterator cbegin() const noexcept;
3)	Array2D<T>::safe_iterator  sbegin()       noexcept;

##### I hope you enjoy Array2D) #####

