#include "names.h"

#ifndef ERROR(num, string) /
    #define ERROR(num, string)          pt::print_error(num, string, __LINE__, iter_) 
#endif // !ERROR(num, string)

//SAFE_ITERATOR
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
     Safe_iterator::Safe_iterator       (const Safe_iterator& other)    noexcept:
     begin_     (other.get_begin()),
     cur_iter_  (other.get_iter()),
     end_       (other.get_end())
{}
     Safe_iterator::Safe_iterator       (std::string::iterator begin, std::string::iterator end) noexcept :
     begin_     (begin),
     cur_iter_  (begin),
     end_       (end)
{}

//quite dangerous!
void       Safe_iterator::move_to       (const std::string::iterator& new_iter) noexcept
{
    cur_iter_ = new_iter;
}
//carefull

const bool Safe_iterator::skip_if       (const char symbol)
{
    if (cur_iter_ != end_ && *cur_iter_ == symbol) {
        ++cur_iter_;
        return true;
    }
    return false;
}
const bool Safe_iterator::is_symbol     (const char symbol) const
{
    if (cur_iter_ != end_ && *cur_iter_ == symbol)
        return true;
    return false;
}

const bool Safe_iterator::operator =    (const Safe_iterator& other)
{
    begin_ = other.get_begin();
    cur_iter_ = other.get_iter();
    end_ = other.get_end();
    return true;
}

const bool Safe_iterator::operator ++   ()
{
    if (cur_iter_ != end_) {
        ++cur_iter_;
        return true;
    }
    return false;
}
const bool Safe_iterator::operator +=   (int dist)
{
    if (dist == 0)
        return true;

    if (dist > 0) {
        for (int i = 0; i < dist; ++i) {
            if (cur_iter_ != end_)
                cur_iter_++;
            else
                return false;
        }
        return true;
    }

    //now dist < 0
    dist *= -1;

    for (int i = 0; i < dist; ++i) {
        if (cur_iter_ != begin_)
            cur_iter_--;
        else
            return false;
    }
    return true;
}
const bool Safe_iterator::operator -=   (int dist)
{
    if (dist == 0)
        return true;

    if (dist < 0) {
        
        dist *= -1;

        for (int i = 0; i < dist; ++i) {
            if (cur_iter_ != end_)
                cur_iter_++;
            else
                return false;
        }
        return true;
    }

    //now dist > 0
    for (int i = 0; i < dist; ++i) {
        if (cur_iter_ != begin_)
            cur_iter_--;
        else
            return false;
    }
    return true;
}
const bool Safe_iterator::operator --   ()
{
    if (cur_iter_ != begin_) {
        --cur_iter_;
        return true;
    }
    return false;
}


void       Safe_iterator::must_change   (int num)
{
    if (!(*this += num))
        pt::print_error(38, "Safe_iterator::_must_change wasn't completely done", __LINE__, *this);
}

const bool Safe_iterator::operator ==   (const char symbol) const
{
    if (*cur_iter_ == symbol)
        return true;
    return false;
}
const bool Safe_iterator::operator !=   (const char symbol) const
{
    if (*cur_iter_ == symbol)
        return false;
    return true;
}
const char Safe_iterator::operator *    () const
{
    if (cur_iter_ == end_)
        return '\0';
    //not end
    return *cur_iter_;
}

const char Safe_iterator::get_symbol    (int dist)          const
{
    if (dist == 0)
        return *cur_iter_;

    int cur_dist = 0;
    std::string::iterator it = cur_iter_;

    if (dist > 0) {
        while (it != end_ && cur_dist < dist) {
            it++;
            cur_dist++;
        }
        if (it != end_)
            return *it;

        //wasn't completely done
        return '\0';
    }

    //now dist < 0

    while (it != begin_ && cur_dist > dist) {
        it--;
        cur_dist++;
    }
    if (it != end_)
        return *it;

    //wasn't completely done
    return '\0';

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////


//NAME
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    name::name              (const std::string& new_name):
                    name_(new_name)
{}
                    name::name              (std::string&& new_name)    noexcept:
                    name_(std::move(new_name))
{}


const std::string   name::get_name          ()                          const
{
#pragma warning("slow function const std::string name::get_name() was used")
    return name_;
}
const bool          name::is_equal_names    (const char* str)           const   noexcept
{

    if (name_ == std::string(str)) 
        return true;

    return false;

}
const bool          name::is_equal_names    (const std::string& str)    const   noexcept
{

    if (name_ == str) 
        return true;

    return false;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Variable
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Variable::Variable      (const Variable& new_var):
        name(new_var.get_name()),
        type_(new_var.type_),
        data_(new_var.get_data())
{}
        Variable::Variable      (TypeVariable new_type, std::string&& str):
        name(std::move(str)),
        type_(new_type),
        data_(0)
{}
        Variable::Variable      (double new_data, TypeVariable new_type, std::string&& str) :
        name(std::move(str)),
        type_(new_type),
        data_(new_data)
{}


void    Variable::correct_value (const double new_data)  noexcept
{
    data_ = new_data;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////



//NAMESPACES PT
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void    pt::print_error         (const unsigned num_error, const char* text_error, const unsigned line, Safe_iterator& iter)
{
    if (text_error == nullptr)
        exit(EXIT_FAILURE);

    std::cout << "\n\nAssert was found : " << num_error << std::endl;
    std::cout << "Description: " << text_error << std::endl;
    
    if (!iter.is_end()) {
        
        while (iter != '\n' && --iter);//Safe_iterator);

        ++iter; //next string

        std::cout << "In your programm mistake was found in string:\n";
        while (iter != '\n') {
            printf("%c", *iter);
            ++iter;
        }

    }

    std::cout << "\nIn compiler at string: " << line << "\n\n\n";
    exit(EXIT_FAILURE);

}
void    pt::print_error         (const unsigned num_error, const std::string& text_error, const unsigned line, Safe_iterator& iter)
{

    std::cout << "\n\nAssert was found : " << num_error << std::endl;
    std::cout << "Description: " << text_error << std::endl;

    if (!iter.is_end()) {

        while (iter != '\n' && --iter);//Safe_iterator);

        ++iter; //next string

        std::cout << "In your programm mistake was found in string:\n";
        while (iter != '\n') {
            printf("%c", *iter);
            ++iter;
        }

    }

    std::cout << "\nIn compiler at string: " << line << "\n\n\n";
    exit(EXIT_FAILURE);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////