void swap(char*& str1, char*& str2)
{
	char* temp = std::move(str1);
	str1 = std::move(str2);
	str2 = std::move(temp);
}
int __strlen(const char* str)
{
	if (str == nullptr)
		return 0;
	else {
		int len = 0;
		while (str[len] != '\0')
			len++;
		return len;
	}
}

std::ostream& operator << (std::ostream& out, const String& string1)
{
	return out << string1.data_;
}




String::String() :
	data_(new char[1]),
	length_(0),
	capacity_(0),
	data_label_()
{
	data_[0] = '\0';
	std::cout << "Ordinary constructor\n";
}
String::String(const char* str) :
	data_(nullptr),
	length_(__strlen(str)),
	capacity_(0),
	data_label_()
{
	if (str != nullptr) {
		capacity_ = length_ + 1;
		data_ = new char[capacity_];
		memcpy(data_, str, length_);
		data_[length_] = '\0';
		data_label_ = str;

		std::cout << "Const char* constructor: " << data_label_ << std::endl;
	}
}
String::String(const std::string str):
	data_(nullptr),
	length_(str.size()),
	capacity_(0),
	data_label_(str)
{
	capacity_ = length_ + 1;
	data_ = new char[capacity_];

	std::cout << "String constructor: " << data_label_ << std::endl;
	memcpy(data_, &(str[0]), length_);
	data_[length_] = '\0';
}
String::String(const String& other):
	data_(nullptr),
	length_(other.size()),
	capacity_(0),
	data_label_("COPY" + other.data_label_)
{
	capacity_ = length_ + 1;
	data_ = new char[capacity_];
	memcpy(&((*this)[0]), &(other[0]), length_ + 1);

	std::cout << "Constructor of copy: " << data_label_ << std::endl;
}
String::String(String&& other) noexcept:
	data_(nullptr),
	length_(other.size()),
	capacity_(other.get_capacity()),
	data_label_(other.data_label_)
{
	data_label_ = "&&(" + other.data_label_ + ")";
	swap(data_, other.data_);
	std::cout << "Constructor of moving: " << data_label_ << std::endl;
}
String::~String()
{
	std::cout << "Destructor: " << data_label_ << std::endl;
	delete[] data_;
}





int String::size() const
{
	return length_;
}
int String::get_capacity() const
{
	return capacity_;
}
bool String::is_empty() const
{
	if (length_ == 0)
		return true;
	return false;
}
void String::make_empty_data(const int other_length)
{
	if (capacity_ - 1 > other_length) {
		data_[0] = '\0';
		length_ = other_length;
	}
	else {
		capacity_ = other_length + 1;
		length_ = other_length;
		delete[] data_;
		data_ = new char[capacity_];
	}
}


void String::push_back(const char& new_elem)
{
	if (new_elem == '\0')
		return;
	if (capacity_ - 1 == length_) {

		capacity_ *= 2;
		length_++;

		char* new_data = new char[capacity_];
		memcpy(new_data, data_, length_);
		new_data[length_ - 1] = new_elem;
		new_data[length_] = '\0';

		delete[] data_;
		data_ = new_data;
	}
	else {
		length_++;
		data_[length_ - 1] = new_elem;
		data_[length_] = '\0';
	}
}
char String::pop_back()
{
	if (length_ != 0) {
		length_--;
		char output_data = data_[length_];
		data_[length_] = '\0';
		return output_data;
	}
	else
	{
		std::cout << "U'r a piece of shit! What r you doing maaan!\n";
	}
	return '\0';
}
char& String::operator [] (int num) const
{
	if (num > length_ || num < 0) {
		std::cout << "You are fuc**ng idiot!!You catched overflow in data!!\n";
		assert(0);
	}
	return data_[num];
}


String& String::operator = (String&& str) noexcept
{
	length_ = str.size();
	capacity_ = str.get_capacity();
	this->data_label_ = "(" + data_label_ + " = &=&(" + str.data_label_ + "))";
	swap(data_, str.data_);
	return (*this);
}
String& String::operator = (const char* str)
{
	make_empty_data(__strlen(str));
	memcpy(data_, str, length_ + 1);

	this->data_label_ = "(" + this->data_label_ + " = (" + str + "))";
	return (*this);
}
String& String::operator = (char*&& str)
{
	this->data_label_ = "(" + this->data_label_ + " = (&&" + str + "))";
	length_ = __strlen(str);
	capacity_ = length_ + 1;
	swap(data_, str);

	return (*this);
}
String& String::operator = (const String& other)
{
	make_empty_data(other.size());
	memcpy(data_, &(other[0]), length_ + 1);

	this->data_label_ = "(" + this->data_label_ + " = (" + other.show_data() + "))";
	return (*this);
}
String& String::operator = (const std::string& str)
{
	make_empty_data(str.size());
	memcpy(data_, &(str[0]), length_ + 1);

	this->data_label_ = "(" + this->data_label_ + " = (" + str + "))";
	return (*this);
}


String String::operator + (const std::string& str)
{
	String out_string(str);
	return std::move(std::forward<String>(*this) += out_string);
}
String String::operator + (const String& str) const &
{
	std::cout << "Operator + &\n";
	String out_string = (*this);
	out_string += str;
	return (std::move(out_string));
}
String String::operator + (const String& str) &&
{
	std::cout << "Operator + &&\n";
	return (std::move(*this += str));
}
String String::operator + (const char* str)
{
	String out_string(str);
	return std::move(std::forward<String>(*this) += out_string);
}


String& String::operator += (const std::string& str)
{
	int length_str = str.size();
	length_ += length_str;

	if (capacity_ > length_) {
		memcpy(data_ + length_ - length_str, &(str[0]), length_str + 1);
	}
	else {
		while (capacity_ <= length_)
			capacity_ *= 2;

		char* new_data = new char[capacity_];
		memcpy(new_data, data_, length_ - length_str);
		memcpy(new_data + length_ - length_str, &(str[0]), length_str + 1);

		delete[] data_;
		data_ = new_data;
	}
	this->data_label_ = "(" + this->data_label_ + " += (" + str + "))";
	return (*this);
}
String& String::operator += (const String& str) &
{
	int length_str = str.size();
	length_ += length_str;

	if (capacity_ > length_) {
		memcpy(data_ + length_ - length_str, &(str[0]), length_str + 1);
	}
	else {
		while (capacity_ <= length_)
			capacity_ *= 2;

		char* new_data = new char[capacity_];
		memcpy(new_data, data_, length_ - length_str);
		memcpy(new_data + length_ - length_str, &(str[0]), length_str + 1);

		delete[] data_;
		data_ = new_data;
	}
	this->data_label_ = "(" + this->data_label_ + " += (" + str.data_label_ + "))";
	return (*this);
}
String& String::operator += (const char* str)
{
	int length_str = __strlen(str);
	length_ += length_str;

	if (capacity_ > length_) {
		memcpy(data_ + length_ - length_str, str, length_str + 1);
	}
	else {
		while (capacity_ <= length_)
			capacity_ *= 2;

		char* new_data = new char[capacity_];
		memcpy(new_data, data_, length_ - length_str);
		memcpy(new_data + length_ - length_str, str, length_str + 1);

		delete[] data_;
		data_ = new_data;
	}
	this->data_label_ = "(" + this->data_label_ + " += (" + str + "))";
	return (*this);
}
String String::operator += (const String& str) &&
{
	std::cout << "Operartor += &&\n";
	int length_str = str.size();
	length_ += length_str;

	if (capacity_ > length_) {
		memcpy(data_ + length_ - length_str, &(str[0]), length_str + 1);
	}
	else {
		while (capacity_ <= length_)
			capacity_ *= 2;

		char* new_data = new char[capacity_];
		memcpy(new_data, data_, length_ - length_str);
		memcpy(new_data + length_ - length_str, &(str[0]), length_str + 1);

		delete[] data_;
		data_ = new_data;
	}
	this->data_label_ = "(" + this->data_label_ + " += (" + str.data_label_ + "))";
	return std::move(*this);
}


bool String::operator == (const std::string& str) const
{
	if ((size_t)this->length_ != str.size())
		return false;
	
	const char* start_str = &(str[0]);
	for (int i = 0; i < length_; ++i) {
		if (data_[i] != *(start_str + i))
			return false;
	}
	return true;
}
bool String::operator == (const String& str) const
{
	std::string new_string = str.data_;
	return (*this == new_string);
}
bool String::operator == (const char* str) const
{
	std::string new_string = str;
	return (*this == new_string);
}


std::string String::show_data() const
{
	return data_label_;
}
void String::dump() const
{
	std::cout << "Data: " << *this << "\nHistory of data: " << show_data() << std::endl;
}