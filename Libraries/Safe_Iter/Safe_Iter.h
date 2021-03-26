#include <iostream>
#include <string>

//just overload std::string::iterator that have several extra protections:
//1)protect data when you trying to change iterator(operator ++, --)
//2)Safe_Iter::change_iter(int) safe to, only you should check bool 

//DECLARATIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Safe_Iter
{
public:
    
                Safe_Iter       (const Safe_Iter& other)                                 noexcept;
                Safe_Iter       (Safe_Iter&& other)                                      noexcept;
    explicit    Safe_Iter       (std::string::iterator begin, std::string::iterator end) noexcept;

    void        move_to         (const std::string::iterator& new_iter)                  noexcept; //DANGEROUS, use if it really necessary

    const bool  is_end          ()                      const               { return (cur_iter_ == end_); }
    const bool  is_begin        ()                      const               { return (cur_iter_ == begin_); }
    
    const bool  skip_if         (const char symbol);                                               //equal to operator == but also skip if true

    const bool  operator =      (const Safe_Iter& other)    noexcept;                              //return false if operation wasn't done correctly

    const bool  operator ++     ();
    const bool  operator +=     (int dist);
    const bool  operator +=     (std::size_t dist);
    const bool  operator -=     (int dist);
    const bool  operator -=     (std::size_t dist);
    const bool  operator --     ();
    
    //////////////////////////////////////////////////////////////////////////
    //important function: do the same as Safe_Iter::_change_iter, but also
    void        must_change     (int num);   
    //if operation wasn't complitly done - do exit from all programm
    //////////////////////////////////////////////////////////////////////////

    const bool  operator ==     (const char symbol)     const;
    const bool  operator !=     (const char symbol)     const;
    char&       operator *      ()                            &;
    const char  operator *      ()                            &&;
    char&       get_symbol      (int dist);                                                         //slow but safe function! Return '\0' if can't be done

    //complexity operators
    Safe_Iter   operator +      (std::size_t dist)      const &;                                    //used move-semantics
    Safe_Iter   operator +      (std::size_t dist)            &&;
    Safe_Iter   operator -      (std::size_t dist)      const &;
    Safe_Iter   operator -      (std::size_t dist)            &&;

    std::string::iterator       get_begin()             const noexcept { return begin_; }           //I'm copying elements in order to save data and give programmer opportunity to next upgrades
    std::string::iterator       get_iter ()             const noexcept { return cur_iter_; }
    std::string::iterator       get_end  ()             const noexcept { return end_; }

private:

    std::string::iterator       begin_;                 //can't be declared const: constructor of copy and operator = 
    std::string::iterator       cur_iter_;
    std::string::iterator       end_;                   //can't be declared const: constructor of copy and operator = 

    char                        trash_symbol_;          //returns if cur_iter_ == end_
    char&                       return_trash() noexcept;//for protect trash use this function

    //in order to delete call this
    Safe_Iter                   ();
};




class Safe_Iter_Const
{
public:

                Safe_Iter_Const (const Safe_Iter_Const& other)                                       noexcept;
                Safe_Iter_Const (Safe_Iter_Const&&)                                                  noexcept;
    explicit    Safe_Iter_Const (const std::string& other)                                           noexcept;
    explicit    Safe_Iter_Const (std::string::const_iterator begin, std::string::const_iterator end) noexcept;

    void        move_to         (const std::string::iterator& new_iter)                              noexcept; //DANGEROUS, use if it really necessary

    const bool  is_end          ()                      const { return (cur_iter_ == end_); }
    const bool  is_begin        ()                      const { return (cur_iter_ == begin_); }

    const bool  skip_if         (const char symbol);                                                           //equal to operator == but also skip if true

    const bool  operator =      (const Safe_Iter_Const& other)                                       noexcept; //return false if operation wasn't done correctly
 
    const bool  operator ++     ();
    const bool  operator +=     (int dist);
    const bool  operator +=     (std::size_t dist);
    const bool  operator -=     (int dist);
    const bool  operator -=     (std::size_t dist);
    const bool  operator --     ();

    //////////////////////////////////////////////////////////////////////////
    //important function: do the same as Safe_Iter_Const::_change_iter, but also
    void        must_change(int num);
    //if operation wasn't complitly done - do exit from all programm
    //////////////////////////////////////////////////////////////////////////

    const bool  operator ==     (const char symbol)     const;
    const bool  operator !=     (const char symbol)     const;
    const char  operator *      ()                      const;
    const char  get_symbol      (int dist)              const;                                                 //slow but safe function! Return '\0' if can't be done

    //moving iterators
    Safe_Iter_Const             operator +  (std::size_t dist)     const&;                                     //used move-semantics
    Safe_Iter_Const             operator +  (std::size_t dist)&&;
    Safe_Iter_Const             operator -  (std::size_t dist)     const&;
    Safe_Iter_Const             operator -  (std::size_t dist)&&;

    std::string::const_iterator get_begin()             const noexcept { return begin_; }                      //I'm copying elements in order to save data and give programmer opportunity to next upgrades
    std::string::const_iterator get_iter ()             const noexcept { return cur_iter_; }
    std::string::const_iterator get_end  ()             const noexcept { return end_; }

private:

    std::string::const_iterator       begin_;                 //can't be declared const: constructor of copy and operator = 
    std::string::const_iterator       cur_iter_;
    std::string::const_iterator       end_;                   //can't be declared const: constructor of copy and operator = 

    //in order to delete call this
    Safe_Iter_Const();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////REALIZATION///////////////////////////////////////////////////////////////////////////

//NOT CONST
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     Safe_Iter::Safe_Iter           (const Safe_Iter& other)    noexcept:
     begin_     (other.get_begin()),
     cur_iter_  (other.get_iter()),
     end_       (other.get_end()),
     trash_symbol_('\0')
{}
     Safe_Iter::Safe_Iter           (Safe_Iter&& other)         noexcept :
     begin_     (std::move(other.begin_)),
     cur_iter_  (std::move(other.cur_iter_)),
     end_       (std::move(other.end_)),
     trash_symbol_('\0')
{}
     Safe_Iter::Safe_Iter           (std::string::iterator begin, std::string::iterator end) noexcept :
     begin_     (begin),
     cur_iter_  (begin),
     end_       (end),
     trash_symbol_('\0')
{}

//quite dangerous!
void       Safe_Iter::move_to       (const std::string::iterator& new_iter) noexcept
{
    cur_iter_ = new_iter;
}
//carefull

const bool Safe_Iter::skip_if       (const char symbol)
{
    if (cur_iter_ != end_ && *cur_iter_ == symbol) {
        ++cur_iter_;
        return true;
    }
    return false;
}

const bool Safe_Iter::operator =    (const Safe_Iter& other) noexcept
{
    begin_ = other.get_begin();
    cur_iter_ = other.get_iter();
    end_ = other.get_end();
    return true;
}

const bool Safe_Iter::operator ++   ()
{
    if (cur_iter_ != end_) {
        ++cur_iter_;
        return true;
    }
    return false;
}
const bool Safe_Iter::operator +=   (int dist)
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
const bool Safe_Iter::operator +=   (std::size_t dist)
{
    if (dist == 0)
        return true;

    for (std::size_t i = 0; i < dist; ++i) {
        if (cur_iter_ != end_)
            cur_iter_++;
        else
            return false;
    }
    return true;
}
const bool Safe_Iter::operator -=   (int dist)
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
const bool Safe_Iter::operator -=   (std::size_t dist)
{
    if (dist == 0)
        return true;

    for (std::size_t i = 0; i < dist; ++i) {
        if (cur_iter_ != begin_)
            cur_iter_--;
        else
            return false;
    }
    return true;
}
const bool Safe_Iter::operator --   ()
{
    if (cur_iter_ != begin_) {
        --cur_iter_;
        return true;
    }
    return false;
}


void       Safe_Iter::must_change   (int num)
{
    if (!(*this += num)) {
        printf("Safe_Iter::_must_change wasn't completely done");
	exit(EXIT_FAILURE);
    }
}

const bool Safe_Iter::operator ==   (const char symbol) const
{
    if (*cur_iter_ == symbol)
        return true;
    return false;
}
const bool Safe_Iter::operator !=   (const char symbol) const
{
    if (*cur_iter_ == symbol)
        return false;
    return true;
}
char&      Safe_Iter::operator *    () &
{
    if (cur_iter_ == end_) 
        return return_trash();
    //not end
    return *cur_iter_;
}
const char Safe_Iter::operator *    () &&
{
    if (cur_iter_ == end_)
        return '\0';
    //not end
    return *cur_iter_;
}

char&      Safe_Iter::get_symbol    (int dist)          
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
        return return_trash();
    }

    //now dist < 0

    while (it != begin_ && cur_dist > dist) {
        it--;
        cur_dist++;
    }
    if (it != end_)
        return *it;

    //wasn't completely done
    return return_trash();

}

char&      Safe_Iter::return_trash  () noexcept
{
    if (trash_symbol_ != '\0')
        trash_symbol_ = '\0';

    return trash_symbol_;
}



Safe_Iter  Safe_Iter::operator +    (std::size_t dist)     const &
{
    Safe_Iter new_iter = *this;
    if (dist == 0)
        return std::move(new_iter);

    std::size_t cur_dist = 0;

    while (!new_iter.is_end() && cur_dist < dist) {
        ++new_iter;
        ++cur_dist;
    }

    return std::move(new_iter);

}
Safe_Iter  Safe_Iter::operator +    (std::size_t dist)           &&
{

    if (dist == 0)
        return std::move(*this);

    std::size_t cur_dist = 0;

    while (!is_end() && cur_dist < dist) {
        ++cur_iter_;
        ++cur_dist;
    }

    return std::move(*this);

}
Safe_Iter  Safe_Iter::operator -    (std::size_t dist)     const &
{

    Safe_Iter new_iter = *this;
    if (dist == 0)
        return std::move(new_iter);

    std::size_t cur_dist = 0;

    while (!new_iter.is_begin() && cur_dist < dist) {
        --new_iter;
        ++cur_dist;
    }

    return std::move(new_iter);

}
Safe_Iter  Safe_Iter::operator -    (std::size_t dist)           &&
{

    if (dist == 0)
        return std::move(*this);

    std::size_t cur_dist = 0;

    while (!is_begin() && cur_dist < dist) {
        --cur_iter_;
        ++cur_dist;
    }

    return std::move(*this);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







//CONST
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Safe_Iter_Const::Safe_Iter_Const          (const Safe_Iter_Const& other)    noexcept :
    begin_   (other.get_begin()),
    cur_iter_(other.get_iter()),
    end_     (other.get_end())
{}
Safe_Iter_Const::Safe_Iter_Const          (Safe_Iter_Const&& other)         noexcept :
    begin_   (std::move(other.begin_)),
    cur_iter_(std::move(other.cur_iter_)),
    end_     (std::move(other.end_))
{}
Safe_Iter_Const::Safe_Iter_Const          (const std::string& other)        noexcept :
    begin_   (other.begin()),
    cur_iter_(other.begin()),
    end_     (other.end())
{}
Safe_Iter_Const::Safe_Iter_Const          (std::string::const_iterator begin, std::string::const_iterator end) noexcept :
    begin_   (begin),
    cur_iter_(begin),
    end_     (end)
{}

//quite dangerous!
void       Safe_Iter_Const::move_to       (const std::string::iterator& new_iter) noexcept
{
    cur_iter_ = new_iter;
}
//carefull

const bool Safe_Iter_Const::skip_if       (const char symbol)
{
    if (cur_iter_ != end_ && *cur_iter_ == symbol) {
        ++cur_iter_;
        return true;
    }
    return false;
}

const bool Safe_Iter_Const::operator =    (const Safe_Iter_Const& other) noexcept
{
    begin_    = other.get_begin();
    cur_iter_ = other.get_iter();
    end_      = other.get_end();
    return true;
}

const bool Safe_Iter_Const::operator ++   ()
{
    if (cur_iter_ != end_) {
        ++cur_iter_;
        return true;
    }
    return false;
}
const bool Safe_Iter_Const::operator +=   (int dist)
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
const bool Safe_Iter_Const::operator +=   (std::size_t dist)
{
    if (dist == 0)
        return true;

    for (std::size_t i = 0; i < dist; ++i) {
        if (cur_iter_ != end_)
            cur_iter_++;
        else
            return false;
    }
    return true;
}
const bool Safe_Iter_Const::operator -=   (int dist)
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
const bool Safe_Iter_Const::operator -=   (std::size_t dist)
{
    if (dist == 0)
        return true;

    for (std::size_t i = 0; i < dist; ++i) {
        if (cur_iter_ != begin_)
            cur_iter_--;
        else
            return false;
    }
    return true;
}
const bool Safe_Iter_Const::operator --   ()
{
    if (cur_iter_ != begin_) {
        --cur_iter_;
        return true;
    }
    return false;
}


void       Safe_Iter_Const::must_change   (int num)
{
    if (!(*this += num)) {
        printf("Safe_Iter_Const::_must_change wasn't completely done");
        exit(EXIT_FAILURE);
    }
}

const bool Safe_Iter_Const::operator ==   (const char symbol) const
{
    if (*cur_iter_ == symbol)
        return true;
    return false;
}
const bool Safe_Iter_Const::operator !=   (const char symbol) const
{
    if (*cur_iter_ == symbol)
        return false;
    return true;
}
const char Safe_Iter_Const::operator *    () const
{
    if (cur_iter_ == end_)
        return '\0';
    //not end
    return *cur_iter_;
}

const char Safe_Iter_Const::get_symbol    (int dist)          const
{
    if (dist == 0)
        return *cur_iter_;

    int cur_dist = 0;
    std::string::const_iterator it = cur_iter_;

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




Safe_Iter_Const Safe_Iter_Const::operator + (std::size_t dist)     const &
{
    Safe_Iter_Const new_iter = *this;
    if (dist == 0)
        return std::move(new_iter);

    std::size_t cur_dist = 0;

    while (!new_iter.is_end() && cur_dist < dist) {
        ++new_iter;
        ++cur_dist;
    }

    return std::move(new_iter);

}
Safe_Iter_Const Safe_Iter_Const::operator + (std::size_t dist)     &&
{
    
    if (dist == 0)
        return std::move(*this);

    std::size_t cur_dist = 0;

    while (!is_end() && cur_dist < dist) {
        ++cur_iter_;
        ++cur_dist;
    }

    return std::move(*this);

}
Safe_Iter_Const Safe_Iter_Const::operator - (std::size_t dist)     const &
{

    Safe_Iter_Const new_iter = *this;
    if (dist == 0)
        return std::move(new_iter);

    std::size_t cur_dist = 0;

    while (!new_iter.is_begin() && cur_dist < dist) {
        --new_iter;
        ++cur_dist;
    }

    return std::move(new_iter);

}
Safe_Iter_Const Safe_Iter_Const::operator - (std::size_t dist)     &&
{

    if (dist == 0)
        return std::move(*this);

    std::size_t cur_dist = 0;

    while (!is_begin() && cur_dist < dist) {
        --cur_iter_;
        ++cur_dist;
    }

    return std::move(*this);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////