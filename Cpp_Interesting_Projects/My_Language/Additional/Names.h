#pragma once

//for debugging only------------------------------------

#ifdef _DEBUG /
#define DEBUG_PRINT_0 std::cout << "\n!!!\n" 
#define DEBUG_PRINT_1(a) std::cout << a << std::endl 
#define DEBUG_PRINT_2(a,b) std::cout << a << "\t" << b << std::endl 
#else 
#define DEBUG_PRINT_0 
#define DEBUG_PRINT_1(a)     
#define DEBUG_PRINT_2(a,b) 
#endif // DEBUG

//-----------------------------------------------------

#ifndef ERROR(num, string) /
    #define ERROR(num, string)          pt::print_error(num, string, __LINE__, iter_) 
#endif // !ERROR(num, string)

//-----------------------------------------------------
constexpr static unsigned COUNT_MISTAKES = 48;
//-----------------------------------------------------

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <memory>
#include "Constants.h"

//just overload std::string::iterator that have several extra protections:
//1)protect data when you trying to change iterator(operator ++, --)
//2)Safe_iterator::change_iter(int) safe to, only you should check bool 
class Safe_iterator
{
public:
                Safe_iterator   ()                      = delete;
                Safe_iterator   (Safe_iterator&&)       = delete;
    
    explicit    Safe_iterator   (const Safe_iterator& other)                             noexcept;
    explicit    Safe_iterator   (std::string::iterator begin, std::string::iterator end) noexcept;

    void        move_to         (const std::string::iterator& new_iter)                  noexcept; //DANGEROUS, use if it really necessary

    const bool  is_end          ()                      const { return (cur_iter_ == end_); }
    const bool  is_begin        ()                      const { return (cur_iter_ == begin_); }
    
    const bool  is_symbol       (const char symbol)     const;
    const bool  skip_if         (const char symbol);                //equal to operator == but also skip if true

    const bool  operator =      (const Safe_iterator& other);       //return false if operation wasn't done correctly

    const bool  operator ++     ();
    const bool  operator +=     (int dist);
    const bool  operator -=     (int dist);
    const bool  operator --     ();
    
    //////////////////////////////////////////////////////////////////////////
    //important function: do the same as Safe_iterator::_change_iter, but also
    void        must_change    (int num);   
    //if operation wasn't complitly done - do exit from all programm
    //////////////////////////////////////////////////////////////////////////

    const bool  operator ==     (const char symbol)     const;
    const bool  operator !=     (const char symbol)     const;
    const char  operator *      ()                      const;
    const char  get_symbol      (int dist)              const;      //slow but safe function! Return '\0' if can't be done

    //slow function, used for constructor of copy
    const std::string::iterator get_begin()             const noexcept { return begin_; }
    const std::string::iterator get_iter()              const noexcept { return cur_iter_; }
    const std::string::iterator get_end()               const noexcept { return end_; }

private:

    std::string::iterator       begin_;                 //can't be declared const: constructor of copy and operator = 
    std::string::iterator       cur_iter_;
    std::string::iterator       end_;                   //can't be declared const: constructor of copy and operator = 
};







class name
{
public:

                    name            ()                          = delete;
                    name            (const name&)               = delete;
                    name            (name&&)                    = delete;

    explicit        name            (const std::string& new_name);
    explicit        name            (std::string&& new_name)            noexcept;
    

    const std::string get_name      ()                          const;//slow, use rare
    
    const bool      is_equal_names  (const char* str)           const   noexcept;
    const bool      is_equal_names  (const std::string& str)    const   noexcept;

protected:

    const std::string name_;
};


class Variable : public name
{
public:

                        Variable        () = delete;

    explicit            Variable        (const Variable& new_var);
    explicit            Variable        (TypeVariable new_type,     std::string&& str);
    explicit            Variable        (const double new_data,     TypeVariable new_type,  std::string&& str);

    void                correct_value   (const double new_data)     noexcept;

    const TypeVariable  get_type        ()  const noexcept { return type_; }
    const double        get_data        ()  const noexcept { return data_; }

private:

    TypeVariable    type_;
    double          data_;

};



namespace pt {
    void            print_error     (const unsigned num_error, const char* text_error, const unsigned line, Safe_iterator& iter);
    void            print_error     (const unsigned num_error, const std::string& text_error, const unsigned line, Safe_iterator& iter);
}