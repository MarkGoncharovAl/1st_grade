#pragma once
#include <iostream>
#include <memory>
#include <functional>

//CURRENT TARGETS
//close opportunity of new_iter(-10)
//append to readmes

namespace lib {

	template <typename T> class const_span;
	template <typename T> class span;
	template <typename T> class new_span;



	//abstract help class
	template <typename T>
	class basic_span {

	public:
		basic_span()                                                  noexcept;
		basic_span(const basic_span<T>&)                              noexcept;
		basic_span(basic_span<T>&&)                                   noexcept;

		basic_span(T* const   start, std::size_t count)               noexcept;
		basic_span(T* const   start, T* const    end)                 noexcept;
		basic_span(T*&& start,       T*&& end)                        noexcept;
		basic_span(T* const& start,  T* const& cur,    T* const& end) noexcept;
		basic_span(T*&& start,       T*&& cur,         T*&& end)      noexcept;

		inline operator bool()                                  const noexcept { return beg_ != nullptr; }

		bool operator ++ ()                                           noexcept;
		bool operator ++ (int)                                        noexcept;
		bool operator -- ()                                           noexcept;
		bool operator -- (int)                                        noexcept;

		void operator += (std::size_t dist)                           noexcept;
		void operator += (int         dist)                           noexcept;
		void operator -= (std::size_t dist)                           noexcept;
		void operator -= (int         dist)                           noexcept;

		void each(std::function<void(const T&)> func);              //except
		void each(std::function<void(const T&, std::size_t)> func); //except

		inline bool is_begin     ()                             const noexcept { return (cur_ == beg_); }
		inline bool is_end       ()                             const noexcept { return (cur_ == end_); }
		inline void to_begin     ()                                   noexcept { cur_ = beg_; }
		inline void to_end       ()                                   noexcept { cur_ = end_; }


		inline std::size_t size     ()                          const noexcept { return  end_ - beg_; }
		inline T* get_beg           ()                          const noexcept { return  beg_; }
		inline T* get_cur           ()                          const noexcept { return  cur_; }
		inline T* get_end           ()                          const noexcept { return  end_; }

	protected:

		T* beg_;
		T* cur_;
		T* end_;

		virtual void dump()                                noexcept = 0;
	};

	template <typename T>
	class span : public basic_span <T>
	{
	public:
		span(const span<T>& other)                          noexcept;
		span(span <T>&& other)                              noexcept;
		span(const lib::new_span<T>& other)                 noexcept;

		span(T* const start, std::size_t count)             noexcept;
		span(T* const start, T* const    end)               noexcept;

		void    operator = (const lib::span<T>& other)      noexcept;
		void    operator = (lib::span<T>&& other)           noexcept;
		void    operator = (const lib::new_span<T>& other)  noexcept;

		T&      operator * ()                       const   noexcept;
		T&      operator[] (int dist)               const   noexcept;
		T&      operator[] (std::size_t dist)       const   noexcept;

		void each(std::function<void(T&)> func);             //except
		void each(std::function<void(T&, std::size_t)> func);//except

		span<T> operator + (std::size_t dist)      const & noexcept;
		span<T> operator + (std::size_t dist)           && noexcept;
		span<T> operator + (int         dist)      const & noexcept;
		span<T> operator + (int         dist)           && noexcept;
		span<T> operator - (std::size_t dist)      const & noexcept;
		span<T> operator - (std::size_t dist)           && noexcept;
		span<T> operator - (int         dist)      const & noexcept;
		span<T> operator - (int         dist)           && noexcept;

	private:

		void dump()                                        noexcept override;
		span()                                             noexcept;
	};


	template <typename T>
	class const_span : public basic_span <T>
	{
	public:
		const_span(const const_span<T>& other)              noexcept;
		const_span(const_span<T>&& other)                   noexcept;
		const_span(const lib::span<T>& other)               noexcept;
		const_span(lib::span<T>&& other)                    noexcept;
		const_span(const lib::new_span<T>& other)           noexcept;

		const_span(T* const start, std::size_t count)       noexcept;
		const_span(T* const start, T* const end)            noexcept;

		void operator =   (const lib::const_span<T>& other) noexcept;
		void operator =   (lib::const_span<T>&& other)      noexcept;
		void operator =   (const lib::span<T>& other)       noexcept;
		void operator =   (lib::span<T>&& other)            noexcept;

		T             operator * ()                 const   noexcept;
		T             operator[] (int dist)         const   noexcept;
		T             operator[] (std::size_t dist) const   noexcept;

		const_span<T> operator + (std::size_t dist) const & noexcept;
		const_span<T> operator + (std::size_t dist)      && noexcept;
		const_span<T> operator + (int         dist) const & noexcept;
		const_span<T> operator + (int         dist)      && noexcept;
		const_span<T> operator - (std::size_t dist) const & noexcept;
		const_span<T> operator - (std::size_t dist)      && noexcept;
		const_span<T> operator - (int         dist) const & noexcept;
		const_span<T> operator - (int         dist)      && noexcept;

	private:

		void dump()                                         noexcept override;
		const_span()                                        noexcept {}
	};


	template <typename T>
	class new_span : public basic_span <T>
	{
	public:
		new_span(const new_span<T>& other)                      noexcept;
		new_span(new_span <T>&& other)                          noexcept;
		new_span(std::size_t          count)                    noexcept;
		new_span(const const_span<T>& other)                    noexcept;
		new_span(const span<T>& other)                          noexcept;

		T& operator * ()                                const   noexcept;
		T& operator[] (int dist)                        const   noexcept;
		T& operator[] (std::size_t dist)                const   noexcept;

		void each(std::function<void(T&)> func);                //except
		void each(std::function<void(T&, std::size_t)> func);   //except

	private:

		std::unique_ptr<T>     owner_;
		new_span()                                              noexcept;
		void copy(T* start, T* end);              //except
		void dump()                                             noexcept override;
	};


	//For user help
	void print_error(std::string info, std::size_t LINE);
	void print_warning(std::string info, std::size_t LINE);

}


//CONSTRUCTORS
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
lib::basic_span<T>::basic_span()                                     noexcept :
	beg_(nullptr),
	cur_(nullptr),
	end_(nullptr)
{}
template <typename T>
lib::basic_span<T>::basic_span(const lib::basic_span<T>& other) noexcept :
	beg_(other.beg_),
	cur_(other.cur_),
	end_(other.end_)
{}
template <typename T>
lib::basic_span<T>::basic_span(lib::basic_span<T>&& other) noexcept :
	beg_(std::move(other.beg_)),
	cur_(std::move(other.cur_)),
	end_(std::move(other.end_))
{}
template <typename T>
lib::basic_span<T>::basic_span(T* const   start, std::size_t count)      noexcept :
	beg_(start),
	cur_(start),
	end_(start + count)
{}
template <typename T>
lib::basic_span<T>::basic_span(T* const   start, T* const    end)                 noexcept :
	beg_(start),
	cur_(start),
	end_(end)
{}
template <typename T>
lib::basic_span<T>::basic_span(T*&& start, T*&& end)                 noexcept :
	beg_(start),
	cur_(std::move(start)),
	end_(std::move(end))
{}
template <typename T>
lib::basic_span<T>::basic_span(T* const& start, T* const& cur, T* const& end)  noexcept :
	beg_(start),
	cur_(cur),
	end_(end)
{}
template <typename T>
lib::basic_span<T>::basic_span(T*&& start, T*&& cur, T*&& end)                 noexcept :
	beg_(std::move(start)),
	cur_(std::move(cur)),
	end_(std::move(end))
{}


template <typename T>
lib::const_span<T>::const_span(lib::const_span<T>&& other)                 noexcept :
	lib::basic_span<T>(std::move(other.beg_), std::move(other.cur_), std::move(other.end_))
{}
template <typename T>
lib::const_span<T>::const_span(const lib::const_span<T>& other)                 noexcept :
	lib::basic_span<T>(other.beg_, other.cur_, other.end_)
{}
template <typename T>
lib::const_span<T>::const_span(const lib::span<T>& other)                        noexcept :
	lib::basic_span<T>(other.get_beg(), other.get_cur(), other.get_end())
{}
template <typename T>
lib::const_span<T>::const_span(lib::span<T>&& other)                             noexcept :
	lib::basic_span<T>(std::move(other.beg_), std::move(other.cur_), std::move(other.end_))
{}
template <typename T>
lib::const_span<T>::const_span(const lib::new_span<T>& other)                    noexcept :
	lib::basic_span<T>(other.beg_, other.cur_, other.end_)
{}
template <typename T>
lib::const_span<T>::const_span(T* const start, std::size_t count)                noexcept :
	lib::basic_span<T>(start, count)
{}
template <typename T>
lib::const_span<T>::const_span(T* const start, T* const    end)                  noexcept :
	lib::basic_span<T>(start, end)
{}


template <typename T>
lib::span<T>::span(lib::span<T>&& other)                                         noexcept :
	lib::basic_span<T>(std::move(other.beg_), std::move(other.cur_), std::move(other.end_))
{}
template <typename T>
lib::span<T>::span(const lib::span<T>& other)                                    noexcept :
	lib::basic_span<T>(other.beg_, other.cur_, other.end_)
{}
template <typename T>
lib::span<T>::span(const lib::new_span<T>& other)                                noexcept :
	lib::basic_span<T>(other.beg_, other.cur_, other.end_)
{}
template <typename T>
lib::span<T>::span(T* const start, std::size_t count)                            noexcept :
	lib::basic_span<T>(start, count)
{}
template <typename T>
lib::span<T>::span(T* const start, T* const    end)                              noexcept :
	lib::basic_span<T>(start, end)
{}


template <typename T>
lib::new_span<T>::new_span(lib::new_span<T>&& other)                             noexcept :
	owner_(std::move(other.owner_)),
	lib::basic_span<T>(std::move(other.beg_), std::move(other.cur_), std::move(other.end_))
{}
template <typename T>
lib::new_span<T>::new_span(const lib::new_span<T>& other)                        noexcept :
	owner_(new T[other.size()]),
	lib::basic_span<T>()
{
	this->beg_ = owner_.get();
	this->cur_ = this->beg_;
	this->end_ = this->beg_ + other.size();
	copy(other.beg_, other.end_);
}
template <typename T>
lib::new_span<T>::new_span(std::size_t count)                                    noexcept :
	owner_(new T[count]),
	lib::basic_span<T>()
{
	this->beg_ = owner_.get();
	this->cur_ = this->beg_;
	this->end_ = this->beg_ + count;
}

template <typename T>
lib::new_span<T>::new_span(const lib::const_span<T>& other)                      noexcept :
	owner_(new T[other.size()]),
	lib::basic_span<T>()
{
	this->beg_ = owner_.get();
	this->cur_ = this->beg_;
	this->end_ = this->beg_ + other.size();
	copy(other.beg_, other.end_);
}
template <typename T>
lib::new_span<T>::new_span(const lib::span<T>& other)                            noexcept :
	owner_(new T[other.size()]),
	lib::basic_span<T>()
{
	this->beg_ = owner_.get();
	this->cur_ = this->beg_;
	this->end_ = this->beg_ + other.size();
	copy(other.beg_, other.end_);
}



template <typename T>
void lib::const_span<T>::
operator =   (const lib::const_span<T>& other) noexcept
{
	this->beg_ = other.get_beg();
	this->cur_ = other.get_cur();
	this->end_ = other.get_end();
}
template <typename T>
void lib::const_span<T>::
operator =   (lib::const_span<T>&& other) noexcept
{
	this->beg_ = std::move(other.get_beg());
	this->cur_ = std::move(other.get_cur());
	this->end_ = std::move(other.get_end());
}
template <typename T>
void lib::const_span<T>::
operator =   (const lib::span<T>& other)       noexcept
{
	this->beg_ = other.get_beg();
	this->cur_ = other.get_cur();
	this->end_ = other.get_end();
}
template <typename T>
void lib::const_span<T>::
operator =   (lib::span<T>&& other)       noexcept
{
	this->beg_ = std::move(other.get_beg());
	this->cur_ = std::move(other.get_cur());
	this->end_ = std::move(other.get_end());
}


template <typename T>
void    lib::span<T>::
operator =   (const lib::span<T>& other)             noexcept
{
	this->beg_ = other.get_beg();
	this->cur_ = other.get_cur();
	this->end_ = other.get_end();
}
template <typename T>
void    lib::span<T>::
operator =   (lib::span<T>&& other)             noexcept
{
	this->beg_ = std::move(other.get_beg());
	this->cur_ = std::move(other.get_cur());
	this->end_ = std::move(other.get_end());
}
template <typename T>
void    lib::span<T>::
operator =   (const lib::new_span<T>& other)          noexcept
{
	this->beg_ = other.get_beg();
	this->cur_ = other.get_cur();
	this->end_ = other.get_end();
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


//Actions BASIC_SPAN
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void lib::basic_span<T>::
operator += (std::size_t dist)         noexcept
{
	if (dist == 0)
		return;

	cur_ += dist;
	if (cur_ > end_)
		cur_ = end_;
}
template <typename T>
void lib::basic_span<T>::
operator += (int         dist)         noexcept
{
	if (dist == 0)
		return;

	cur_ += dist;

	if (cur_ > end_)
		cur_ = end_;
	if (cur_ < beg_)
		cur_ = beg_;

}
template <typename T>
void lib::basic_span<T>::
operator -= (std::size_t dist)         noexcept
{
	if (dist == 0)
		return;

	cur_ -= dist;
	if (cur_ < beg_)
		cur_ = beg_;
}
template <typename T>
void lib::basic_span<T>::
operator -= (int         dist)         noexcept
{
	if (dist == 0)
		return;

	cur_ -= dist;

	if (cur_ > end_)
		cur_ = end_;
	if (cur_ < beg_)
		cur_ = beg_;

}

template <typename T>
void lib::basic_span<T>::
each(std::function<void(const T&)> func)
{
	T* cur_obj = beg_;
	while (cur_obj != end_) {
		func(*cur_obj);
		cur_obj++;
	}
}
template <typename T>
void lib::basic_span<T>::
each(std::function<void(const T&, std::size_t)> func)
{
	T* cur_obj = beg_;
	std::size_t cur_num = 0;
	while (cur_obj != end_) {
		func(*cur_obj, cur_num);
		cur_obj++;
		cur_num++;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


//Actions CONST_SPAN 
//******************************************************************************************
//******************************************************************************************
template <typename T>
T lib::const_span<T>::
operator * ()                 const   noexcept
{
	if (this->cur_ == this->end_) {
		lib::print_warning("You tried to use operator [] on unexisted element! - it can create some problems!", __LINE__);
		return std::move(T());
	}
	return *this->cur_;
}
template <typename T>
T lib::const_span<T>::
operator[] (int dist)         const   noexcept
{
	if (dist == 0)
		return *this->cur_;

	T* out = this->cur_ + dist;

	if (out >= this->end_ || out < this->beg_) {
		lib::print_warning("You tried to use operator [] on unexisted element! - it can create some problems!", __LINE__);
		return std::move(T());
	}
	return *out;

}
template <typename T>
T lib::const_span<T>::
operator[] (std::size_t dist) const   noexcept
{
	if (dist == 0)
		return *this->cur_;

	T* out = this->cur_ + dist;

	if (out >= this->end_) {
		lib::print_warning("You tried to use operator [] on unexisted element! - it can create some problems!", __LINE__);
		return std::move(T());
	}
	return *out;
}

template <typename T>
lib::const_span<T> lib::const_span<T>::
operator + (std::size_t dist) const& noexcept
{
	lib::const_span<T> new_iter = *this;
	new_iter += dist;
	return new_iter;
}

template <typename T>
lib::const_span<T> lib::const_span<T>::
operator + (std::size_t dist) && noexcept
{
	this->operator+=(dist);
	return std::move(*this);
}

template <typename T>
lib::const_span<T> lib::const_span<T>::
operator + (int         dist) const& noexcept
{
	lib::const_span<T> new_iter = *this;
	new_iter += dist;
	return new_iter;
}

template <typename T>
lib::const_span<T> lib::const_span<T>::
operator + (int         dist) && noexcept
{
	this->operator+=(dist);
	return std::move(*this);
}

template <typename T>
lib::const_span<T> lib::const_span<T>::
operator - (std::size_t dist) const& noexcept
{
	lib::const_span<T> new_iter = *this;
	new_iter -= dist;
	return new_iter;
}

template <typename T>
lib::const_span<T> lib::const_span<T>::
operator - (std::size_t dist) && noexcept
{
	this->operator-=(dist);
	return std::move(*this);
}

template <typename T>
lib::const_span<T> lib::const_span<T>::
operator - (int         dist) const& noexcept
{
	lib::const_span<T> new_iter = *this;
	new_iter -= dist;
	return new_iter;
}

template <typename T>
lib::const_span<T> lib::const_span<T>::
operator - (int         dist) && noexcept
{
	this->operator-=(dist);
	return std::move(*this);
}

template <typename T>
void lib::const_span<T>::
dump() noexcept
{
	if (this->cur_ != nullptr) {
		std::cout << "Start point: " << this->beg_ << "\tCurrent: " << this->cur_ << "\tAfter last: " << this->end_ << std::endl;
	}
	else
		std::cout << "Span is empty!\n";
}
//******************************************************************************************
//******************************************************************************************

//Actions SPAN
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
template <typename T>
T& lib::span<T>::
operator * ()                 const   noexcept
{
	if (this->cur_ == this->end_)
		lib::print_error("Can't return Type& in operator * in span! Check boundaries!", __LINE__);
	return *this->cur_;
}
template <typename T>
T& lib::span<T>::
operator [] (int dist)         const   noexcept
{
	if (dist == 0)
		return this->operator*();

	T* out = this->cur_ + dist;

	if (out >= this->end_ || out < this->beg_)
		lib::print_error("Operator [] was subscribed out of range. Can't return Type&. Be careful!!!", __LINE__);

	return *out;

}
template <typename T>
T& lib::span<T>::
operator[] (std::size_t dist) const   noexcept
{
	if (dist == 0)
		return this->operator*();

	T* out = this->cur_ + dist;

	if (out >= this->end_)
		lib::print_error("Operator [] was subscribed out of range. Can't return Type&. Be careful!!!", __LINE__);

	return *out;
}

template <typename T>
void lib::span<T>::
each(std::function<void(T&)> func)
{
	T* cur_obj = this->beg_;
	while (cur_obj != this->end_) {
		func(*cur_obj);
		cur_obj++;
	}
}
template <typename T>
void lib::span<T>::
each(std::function<void(T&, std::size_t)> func)
{
	T* cur_obj = this->beg_;
	std::size_t cur_num = 0;
	while (cur_obj != this->end_) {
		func(*cur_obj, cur_num);
		cur_obj++;
		cur_num++;
	}
}

template <typename T>
lib::span<T> lib::span<T>::
operator + (std::size_t dist) const& noexcept
{
	lib::span<T> new_iter = *this;
	new_iter += dist;
	return new_iter;
}

template <typename T>
lib::span<T> lib::span<T>::
operator + (std::size_t dist) && noexcept
{
	this->operator+=(dist);
	return std::move(*this);
}

template <typename T>
lib::span<T> lib::span<T>::
operator + (int         dist) const& noexcept
{
	lib::span<T> new_iter = *this;
	new_iter += dist;
	return new_iter;
}

template <typename T>
lib::span<T> lib::span<T>::
operator + (int         dist) && noexcept
{
	this->operator+=(dist);
	return std::move(*this);
}

template <typename T>
lib::span<T> lib::span<T>::
operator - (std::size_t dist) const& noexcept
{
	lib::span<T> new_iter = *this;
	new_iter -= dist;
	return new_iter;
}

template <typename T>
lib::span<T> lib::span<T>::
operator - (std::size_t dist) && noexcept
{
	this->operator-=(dist);
	return std::move(*this);
}

template <typename T>
lib::span<T> lib::span<T>::
operator - (int         dist) const& noexcept
{
	lib::span<T> new_iter = *this;
	new_iter -= dist;
	return new_iter;
}

template <typename T>
lib::span<T> lib::span<T>::
operator - (int         dist) && noexcept
{
	this->operator-=(dist);
	return std::move(*this);
}

template <typename T>
void lib::span<T>::
dump() noexcept
{
	if (this->cur_ != nullptr) {
		std::cout << "Start point: " << this->beg_ << "\tCurrent: " << this->cur_ << "\tAfter last: " << this->end_ << std::endl;
	}
	else
		std::cout << "Span is empty!\n";
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------


//NEW_SPAN
//******************************************************************************************
//******************************************************************************************
template <typename T>
T& lib::new_span<T>::
operator * ()                 const   noexcept
{
	if (this->cur_ == this->end_)
		lib::print_error("Can't return Type& in operator * in span! Check boundaries!", __LINE__);
	return *this->cur_;
}
template <typename T>
T& lib::new_span<T>::
operator [](int dist)         const   noexcept
{
	if (dist == 0)
		return this->operator*();

	T* out = this->cur_ + dist;

	if (out >= this->end_ || out < this->beg_)
		lib::print_error("Operator [] was subscribed out of range. Can't return Type&. Be careful!!!", __LINE__);

	return *out;

}
template <typename T>
T& lib::new_span<T>::
operator[] (std::size_t dist) const   noexcept
{
	if (dist == 0)
		return this->operator*();

	T* out = this->cur_ + dist;

	if (out >= this->end_)
		lib::print_error("Operator [] was subscribed out of range. Can't return Type&. Be careful!!!", __LINE__);

	return *out;
}

template <typename T>
void lib::new_span<T>::
each(std::function<void(T&)> func)
{
	T* cur_obj = this->beg_;
	while (cur_obj != this->end_) {
		func(*cur_obj);
		cur_obj++;
	}
}

template <typename T>
void lib::new_span<T>::
each(std::function<void(T&, std::size_t)> func)
{
	T* cur_obj = this->beg_;
	std::size_t cur_num = 0;
	while (cur_obj != this->end_) {
		func(*cur_obj, cur_num);
		cur_obj++;
		cur_num++;
	}
}

template <typename T>
void lib::new_span<T>::
copy(T* start, T* end)
{
	T* const prev_loc = this->cur_;

	this->cur_ = this->beg_;
	while (start != end && this->cur_ != this->end_) {
		*(this->cur_) = *start;
		start++;
		(this->cur_)++;
	}

	this->cur_ = prev_loc;
}

template <typename T>
void lib::new_span<T>::
dump() noexcept
{
	if (this->cur_ != nullptr) {
		std::cout << "Start point: " << this->beg_ << "\tCurrent: " << this->cur_ << "\tAfter last: " << this->end_ << std::endl;
	}
	else
		std::cout << "Span is empty!\n";
}
//******************************************************************************************
//******************************************************************************************


//PRINTING FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
inline void lib::print_error(std::string info, std::size_t LINE)
{
	std::cout << std::endl << info << std::endl;
	printf("Mistake was found in line %ld\n", LINE);
	exit(EXIT_FAILURE);
}
inline void lib::print_warning(std::string info, std::size_t LINE)
{
	std::cout << std::endl << info << std::endl;
	printf("Warning was found in line %ld\n", LINE);
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


//OPERATORS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <typename T>
bool lib::basic_span<T>::
operator ++ ()    noexcept
{
	if (cur_ == end_)
		return false;

	cur_++;
	return true;
}

template <typename T>
bool lib::basic_span<T>::
operator ++ (int) noexcept
{
	if (cur_ == end_)
		return false;

	cur_++;
	return true;
}

template <typename T>
bool lib::basic_span<T>::
operator-- ()    noexcept
{
	if (cur_ == beg_)
		return false;

	cur_--;
	return true;
}

template <typename T>
bool lib::basic_span<T>::
operator-- (int) noexcept
{
	if (cur_ == beg_)
		return false;

	cur_--;
	return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~