#include <iostream>
#include <vector>
#include <array>

//PROGRAMMER
//****************************************************************************************************************************
namespace BMH_PROG {

	constexpr size_t    COUNT_SYMBOLS       = 256;                                                 //Number of symbols in Askii code
	constexpr size_t    SYMBOL_WAS_NOT_DECL = 0;
	constexpr int       WAS_NOT_FOUND       = -1;                                                  //To check array for declaration

	class table
	{
	public:
		using type_table = std::array<size_t, COUNT_SYMBOLS>;

		table()             = delete;
		table(const table&) = delete;
		table(table&&)      = delete;

		table                  (const std::string& pattern) noexcept;
		
		size_t calculate_shift (const char cur_sym)   const noexcept;
	
	private:

		type_table data_ = {};
		size_t     size_ = 0;
	};


	//OUTPUT CLASSES
	class finding {
	public:
		finding (const std::string::const_iterator& new_place,  const std::size_t new_num, const bool found)  noexcept;
		finding (      std::string::const_iterator&& new_place, const std::size_t new_num, const bool found)  noexcept;
		finding (const finding& other)                                                                        noexcept;
		finding (finding&& other)                                                                             noexcept;

		std::string::const_iterator place;
		std::size_t                 num_place;
		bool                        is_find;
	};
	class counting {
	public:
		counting (const std::size_t new_count, const bool found)                                               noexcept;
		counting (const counting& other)                                                                       noexcept;
		counting (counting&& other)                                                                            noexcept;

		std::size_t                 count;
		bool                        is_find;
	};
	class BMH_pair {
	public:
		BMH_pair(std::string::const_iterator&& new_iter, const std::size_t)                                    noexcept;
		BMH_pair(const BMH_pair& other)                                                                        noexcept;
		BMH_pair(BMH_pair&& other)                                                                             noexcept;

		std::string::const_iterator iter_place;
		std::size_t                 num_place;
	};
	class full_information {
	public:
		full_information(std::vector< BMH_pair >&& new_places, const std::size_t new_count, const bool found)  noexcept;
		full_information(const full_information&  other)                                                       noexcept;
		full_information(      full_information&& other)                                                       noexcept;

		std::vector <BMH_pair>      places;
		std::size_t                 count;
		bool                        is_find;
	};


	std::string::const_iterator find_iter
	                            (const std::string& str, size_t place) noexcept;
}
//****************************************************************************************************************************

//USER
//-------------------------------------------------------------------------------------------------------------------------------------------
namespace BMH {

	BMH_PROG::finding          first_find(const std::string& base, const std::string& pattern);       //find only first finding             
	BMH_PROG::counting         count_find(const std::string& base, const std::string& pattern);       //just give information about count of findings
	BMH_PROG::full_information full_find (const std::string& base, const std::string& pattern);       //returns every information that found

}
//-------------------------------------------------------------------------------------------------------------------------------------------




//REALIZATION FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BMH_PROG::finding
	BMH::first_find(const std::string& base, const std::string& pattern)
{
	if (base.empty()    || 
		pattern.empty() || 
		base.size() < pattern.size()) {
		
		//obviously wrong case
		return std::move(BMH_PROG::finding{ base.end(), 0, false });
	}

	//preparing data
	BMH_PROG::table data_table { pattern };

	const size_t  len_word    = pattern.size();
	const size_t  last_pos    = base.size() - 1;
	      size_t  cur_place   = len_word - 1;

	const char*   cur_data    = base.data()    + cur_place;
	const char*   end_pattern = pattern.data() + cur_place;

	const size_t  last_letter = data_table.calculate_shift
	                                       (pattern[len_word - 1]); //so often used

	while (cur_place <= last_pos) {
		
		//check for finding
		bool        is_found   = true;

		//check letters
		for (size_t i = 0; i < len_word; ++i) {
			
			const char cur_symbol = *(cur_data - i);
			if (cur_symbol != *(end_pattern - i)) {
				
				if (i == 0) {
					size_t moving_to = data_table.calculate_shift(cur_symbol);
					cur_data  += moving_to;
					cur_place += moving_to;
				}
				else {
					//use last symbol
					cur_data  += last_letter;
					cur_place += last_letter;
				}

				is_found = false;
				break;
			}
		}

		if (is_found) {
			const size_t output = cur_place - len_word + 1;
			return std::move( BMH_PROG::finding(  std::move( BMH_PROG::find_iter(base, output) ), output , true  ) );
		}

	}

	return std::move(BMH_PROG::finding ( base.cend(), 0, false ));
}

BMH_PROG::counting
	BMH::count_find(const std::string& base, const std::string& pattern)
{
	BMH_PROG::counting output_data{ 0, false };

	if (!base.empty() &&
		!pattern.empty() &&
		base.size() >= pattern.size()) {

		//preparing data
		BMH_PROG::table data_table{ pattern };

		const size_t  len_word    = pattern.size();
		const size_t  last_pos    = base.size() - 1;
		      size_t  cur_place   = len_word - 1;

		const char*   cur_data    = base.data()    + cur_place;
		const char*   end_pattern = pattern.data() + cur_place;

		const size_t  last_letter = data_table.calculate_shift
		                                       (pattern[len_word - 1]); //so often used

		while (cur_place <= last_pos) {

			//check for finding
			bool        is_found = true;

			//check letters
			for (size_t i = 0; i < len_word; ++i) {

				const char cur_symbol = *(cur_data - i);
				if (cur_symbol != *(end_pattern - i)) {

					if (i == 0) {
						size_t moving_to = data_table.calculate_shift(cur_symbol);
						cur_data  += moving_to;
						cur_place += moving_to;
					}
					else {
						//use last symbol
						cur_data  += last_letter;
						cur_place += last_letter;
					}

					is_found = false;
					break;
				}
			}

			if (is_found) {
				cur_data  += last_letter;
				cur_place += last_letter;

				output_data.count++;
				output_data.is_find = true;
			}

		}
	}
	return std::move(output_data);
}

BMH_PROG::full_information
	BMH::full_find(const std::string& base, const std::string& pattern)
{

	BMH_PROG::full_information output_data{ std::vector<BMH_PROG::BMH_pair>(), 0, false };

	if (!base.empty() &&
		!pattern.empty() &&
		base.size() >= pattern.size()) {

		//preparing data
		BMH_PROG::table data_table{ pattern };

		const size_t  len_word    = pattern.size();
		const size_t  last_pos    = base.size() - 1;
		      size_t  cur_place   = len_word - 1;

		const char*   cur_data    = base.data()    + cur_place;
		const char*   end_pattern = pattern.data() + cur_place;

		const size_t  last_letter = data_table.calculate_shift
		                                       (pattern[len_word - 1]); //so often used

		while (cur_place <= last_pos) {

			//check for finding
			bool        is_found = true;

			//check letters
			for (size_t i = 0; i < len_word; ++i) {

				const char cur_symbol = *(cur_data - i);
				if (cur_symbol != *(end_pattern - i)) {

					if (i == 0) {
						size_t moving_to = data_table.calculate_shift(cur_symbol);
						cur_data  += moving_to;
						cur_place += moving_to;
					}
					else {
						//use last symbol
						cur_data  += last_letter;
						cur_place += last_letter;
					}

					is_found = false;
					break;
				}
			}

			if (is_found) {
				std::size_t output = cur_place - len_word + 1;
				output_data.places.push_back(
					                          std::move(BMH_PROG::BMH_pair
											 (std::move(BMH_PROG::find_iter(base, output)), cur_place - 1) ));

				output_data.count++;
				output_data.is_find = true;

				cur_data  += last_letter;
				cur_place += last_letter;
			}

		}
	}
	return std::move(output_data);
}





BMH_PROG::table::table (const std::string& pattern) noexcept :
	data_ ({}),
	size_ (pattern.size())
{

	if (size_ > 0) {

		for (size_t i = size_ - 1; i > 0; --i) {

			if (data_.at(pattern.at(i - 1)) == SYMBOL_WAS_NOT_DECL) {
				data_.at(pattern.at(i - 1)) = size_ - i;                  //fill data with number of further symbols
			}

		}

		//check last symbol
		if (data_.at(pattern.at(size_ - 1)) == SYMBOL_WAS_NOT_DECL) {
			data_.at(pattern.at(size_ - 1)) = size_;
		}
		//**********************************************
	}
}

size_t BMH_PROG::table::calculate_shift(const char sym) const noexcept
{
	const size_t data_sym = data_.at(sym);
	if (data_sym == SYMBOL_WAS_NOT_DECL)
		return size_;

	return data_sym;
}



//Help for user classes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BMH_PROG::finding::finding                  (const std::string::const_iterator&  new_place, const std::size_t new_num, const bool found)  noexcept:
	place     (new_place),
	num_place (new_num),
	is_find   (found)
{}
BMH_PROG::finding::finding                  (      std::string::const_iterator&& new_place, const std::size_t new_num, const bool found)  noexcept:
	place     (std::move(new_place)),
	num_place (new_num),
	is_find   (found)
{}
BMH_PROG::finding::finding                  (finding&& other)                                                                             noexcept:
	place     (std::move(other.place)),
	num_place (std::move(other.num_place)),
	is_find   (std::move(other.is_find))
{}
BMH_PROG::finding::finding                  (const finding& other)                                                                        noexcept:
	place     (other.place),
	num_place (other.num_place),
	is_find   (other.is_find)
{}

BMH_PROG::counting::counting                  (const std::size_t new_count,                   const bool found)                           noexcept:
	count     (new_count),
	is_find   (found)
{}
BMH_PROG::counting::counting                  (counting&& other)                                                                          noexcept:
	count     (std::move(other.count)),
	is_find   (std::move(other.is_find))
{}
BMH_PROG::counting::counting                  (const counting& other)                                                                     noexcept:
	count     (other.count),
	is_find   (other.is_find)
{}

BMH_PROG::BMH_pair::BMH_pair                (std::string::const_iterator&& new_iter,        const std::size_t new_num)                    noexcept:
	iter_place(std::move(new_iter)),
	num_place (new_num)
{}
BMH_PROG::BMH_pair::BMH_pair                (BMH_pair&& other)                                                                            noexcept:
	iter_place(std::move(other.iter_place)),
	num_place (std::move(other.num_place))
{}
BMH_PROG::BMH_pair::BMH_pair                (const BMH_pair& other)                                                                       noexcept:
	iter_place(other.iter_place),
	num_place (other.num_place)
{}

BMH_PROG::full_information::full_information(std::vector<BMH_PROG::BMH_pair>&& new_places,  const std::size_t new_count, const bool found)noexcept:
	places    (std::move(new_places)),
	count     (new_count),
	is_find   (found)
{}
BMH_PROG::full_information::full_information(BMH_PROG::full_information&& other)                                                          noexcept:
	places    (std::move(other.places)),
	count     (std::move(other.count)),
	is_find   (std::move(other.is_find))
{}
BMH_PROG::full_information::full_information(const BMH_PROG::full_information& other)                                                     noexcept:
	places    (other.places),
	count     (other.count),
	is_find   (other.is_find)
{}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Help function
std::string::const_iterator BMH_PROG::find_iter
                                      (const std::string& str, size_t place) noexcept
{
	std::string::const_iterator output = str.cend();
	//check possibility of place
	if (place < str.size())
		output = str.cbegin() + place;

	return output;
}