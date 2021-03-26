#pragma once
#include <iostream>
#include <ostream>
#include <string.h>
#include <utility>
#include <cassert>

int __strlen(const char* str);
void swap(char*& str1, char*& str2);


class String {
private:

	char* data_;
	int length_;                      //original length - "tree" = 4
	int capacity_;                    //real in computer - "tree" = 5;
	std::string data_label_;


	void make_empty_data(const int other_length);

public:

	String();
	String(const char* str);
	String(const std::string);
	String(const String& other);
	String(String&& other) noexcept;
	~String();

	int size() const;
	int get_capacity() const;
	bool is_empty() const; 
	std::string show_data() const;
	void dump() const;

	void push_back(const char& new_elem);
	char pop_back();
	char& operator [] (int num) const;

	String& operator = (String&& str) noexcept;
	String& operator = (const char* str);
	String& operator = (char*&& str);
	String& operator = (const std::string& str);
	String& operator = (const String& str);

	String operator + (const std::string& str) const &; 
	String operator + (const std::string& str) &&;
	String operator + (const String& other) const &;
	String operator + (const String& other) &&;
	String operator + (const char* str) const &;
	String operator + (const char* str) &&;

	String& operator += (const std::string& str);
	String& operator += (const String& str);
	String& operator += (const char* str);
	
	bool operator == (const std::string& str) const;
	bool operator == (const String& str) const; 
	bool operator == (const char* str) const;


	friend std::ostream& operator << (std::ostream& out, const String& string1);

};
#include "code_my_String.cpp"

//extra options:

#define STR(a)\
	String a(#a)