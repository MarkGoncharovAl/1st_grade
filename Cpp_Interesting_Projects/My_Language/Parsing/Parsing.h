#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <cassert>

#include "../Additional/Names.h"

#ifndef ERROR(num,string) /
    #define ERROR(num, string)          pt::print_error(num, string, __LINE__, iter_) 
#endif // !ERROR(num, string)

//IMPORTANT
//if you will add new mistake don't forget to add to count_mistakes in Names.h
//IMPORTANT

////////////////////////////////////////////////////////////////////////////////////////////////
//DECLARATION:  
//
//              'symbol'
//              "Function"
//              ~ == "Spaces"
//              @extra actions
////////////////////////////////////////////////////////////////////////////////////////////////
//"Programm.Start()"::= ~ ("DeclarateFunctions" ~ "main")
//
//every function returns as 'result'
////////////////////////////////////////////////////////////////////////////////////////////////
//
//                              PREPROCESSOR
//
//"Preprocessor"::= ~ 'set' ~ "prog string" ~ 'as' ~ "prog string" @than change main_iter_
//                  It means that iter_ will be changed is set will be found  
////////////////////////////////////////////////////////////////////////////////////////////////
//
//                              MAIN ACTIONS
//
//Parsing(const std::string&) ::=   ~ ("Action")* ~ '\0'
//                                        ||
//                                        ||
//                ------------------------------------------------------------------------------------
//"Action"::=     ~ ("Type") ~ ("Variable" | "Condition" | "Loop" | "CreateFunc"  | "CallFunc" | "STANDART_LIBRARY") ~
//                                                                                          
//
//
//"STANDART_LIBRARY"::= "show" | "get"
//
//"show"::= ~ ('$'"ReadVariable" ~)* ';'
//"get"::= ~ ('$'"Name""CorrectDataVariable" ~)* ';'
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//                          WORK WITH VARIABLES
//      
//"Type"::= ~ "Name" ~ @check is type@ 
//
//
//"Variables"::=  ~ ("CreateVariable") | ("CorrectVariable") ~ ';'                                                                       
//                         ||                           ||                                                      
//                     -----------------------------    ||                                                                              
//"CreateVariable"::=  ~ @create var@ ~ "Equation" ~    ||                                                                                                                                                   
//                                                      ||
//                                            -------------------------                                        
//"CorrectVariable"::=                        ~ "Equation" ~ @fill var@                                                                                     
//                                                  ||                                                      
//                                    --------------------------------                        
//"Equation"::=                       "Name" ~ '=' "MathExpression"  ~                                                                                        
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//                          CONDITION OPERATIONS:
//
//"Loop" ::=                (   ~'[' ~"CheckCondition" ~']' ~'{' ~"Action" * ~ '}' ~    )*
//                                              ||
//"Condition":: =               ~'[' ~"CheckCondition" ~']' ~'{' ~"Action" * ~ '}' ~
//                                              ||
//                                       -----------------
//"CheckCondition"::=                    ~ "OrCondition" ~
//                                              ||
//                          -----------------------------------------
//"OrCondition"::=          "AndCondition" ~ ('or' "AndCondition" ~)*
//                                                     ||                                                         
//                                  ------------------------------------------------------
//"AndCondition"::=                 ~ "Bracketscondition" ~ ('and' "Bracketscondition" ~)*      
//                                            ||                
//                          ---------------------------------------------------
//"BracketsCondition"::=    ~ ('(' "CheckCondition" ~ ')' | "PureCondition" ) ~
//                                                              ||
//                                  ------------------------------------------------------------
//"PureCondition"::=                ~ "MathExpression"  ~ @check operation@ ~ "MathExpression" ~
//
////////////////////////////////////////////////////////////////////////////////////////////////
//
//                          MATHEMATICAL OPERATION:
//
//"MathExpression"::=             ~ "PlusMinus" ~   
//                                      ||
//                          -----------------------------------
//"PlusMinus"::=            ~ "MultDiv" ~ ([+-] ~ "MultDiv" ~)*
//                              ||   
//                      -------------------------------
//"MultDiv"::=          ~ "Degree" ~ ([*/] ~ "Degree" ~)*
//                          ||            
//                  -----------------------------------
//"Degree"::=       ~ "Brackets" ~ ( '^' ~ "Brackets" ~)*   
//                      ||
//              ------------------------------------------------------------------------------
//"Brackets"::= ( '(' ~ "PlusMinus" ~ ')' | "DoubleNumber" | "ReadVariable"  | "ReadFunction")
//                                               ||               
//                              ---------------------------------                                
//"DoubleNumber"::=             "PureNumber" ( '.' "PureNumber")?     
//                                                  ||
//                                                 ------
//"PureNumber"::=                                  [0-9]+
//
////////////////////////////////////////////////////////////////////////////////////////////////



//MAIN FOR PROGRAMMER
////////////////////////////////////////////////////////////////////////////////////////////////
class Parsing
{
protected:
                Parsing         ()                  = delete;
                Parsing         (const Parsing&)    = delete;
                Parsing         (Parsing&&)         = delete;
               ~Parsing         () {}

    explicit    Parsing         (const Safe_iterator& new_iter);


    //standart library functions
    //////////////////////////////////////////////////////////////////////
    bool    show                ();                                             //print programmmer parameters
    bool    get                 ();                                             //wait for new data
    //////////////////////////////////////////////////////////////////////


    //condition dunctions
    //////////////////////////////////////////////////////////////////////
    bool    Condition           ();
    bool    CheckCondition      ();

    bool    OrCondition         (bool* is_doing);
    bool    AndCondition        (bool* is_doing);
    bool    BracketsCondition   (bool* is_doing);
    bool    PureCondition       (bool* is_doing);

    bool    Loop                ();
    //////////////////////////////////////////////////////////////////////
    

    //mathematical functions
    //////////////////////////////////////////////////////////////////////
    bool    MathExpression      (double* num);

    bool    PlusMinus           (double* num);
    bool    MultDiv             (double* num);
    bool    Degree              (double* num);

    bool    Brackets            (double* num);

    bool    DoubleNumber        (double* num);                                      //complexity number
    bool    PureNumber          (int* num,      int* length = nullptr);             //unsigned
    //////////////////////////////////////////////////////////////////////


    //work with variables and functions
    //////////////////////////////////////////////////////////////////////
    bool    ReadVariable        (double* num);                                      //GetDataVar -> num + READ Name
    bool    ReadFunction        (double* num);                                      //Call function ->num
    
    std::vector<double> ReadParameters (const std::size_t count_variables);

    bool    IsVariable          (const char* name);                                 //true if found
    bool    IsVariable          (const std::string& name);          
    bool    IsFunction          (const char* name);
    bool    IsFunction          (const std::string& name);

    bool    GetDataVariable     (const char* name,          double* num);           //true if found
    bool    GetDataVariable     (const std::string& name,   double* num);           //data -> num

    bool    CorrectDataVariable (const double new_data, const std::string& name);   //fill data
    //////////////////////////////////////////////////////////////////////


    //string functions
    //////////////////////////////////////////////////////////////////////
    std::string   Name          ();                                                 //check returnig with method empty

    TypeVariable  Type          ();                                                 //Read type and MOVE CUR POSITION

    void    Spaces();
    void    SkipComments();

    //stops on the first letter of name that was backed
    //////////////////////////////////////////////////////////////////////
    void    NameBack            ();
    void    SpacesBack          ();
    //////////////////////////////////////////////////////////////////////

    void    Skip                (char end);                                         //miss till 'end' symbol and miss it too
    bool    LongSkip            (char end,   char symbol);                          //Skip untill 'end' symbols will be more than 'symbol'
    std::string Read            (char end);                                         //read till char end and stops at 'end' symbol

    bool    IsStopSymbol        (const char symbol)         noexcept;               //show if symbol isn't good for next actions such as Action, MathExpression
    //////////////////////////////////////////////////////////////////////


    //main functions
    //////////////////////////////////////////////////////////////////////
    bool    STANDART_LIBRARY    (TypeVariable type);

    bool    Action              ();

    bool    CallFunc            (double* num = nullptr);                            //READ NAME, you should provide right adress to first symbol

    //work with variables
    //////////////////////////////////////////////////////////////////////
    bool    Variables           (TypeVariable type);                                

    bool    CreateVariable      ();
    bool    CorrectVariable     ();

    std::string  Equation       (double* num);                                      //return name of variable
    //////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////


    //only for the programmer
    ///////////////////////////////////////////////////////////////////////
    //DEBUG_PRINT_0 (or 1, or 2);
    void                Dump                ();
    const std::size_t   get_count_by_name   (const std::string& current_name);      //return count pararmeters in function
    ///////////////////////////////////////////////////////////////////////


    std::vector <Variable> vars_;
    Safe_iterator iter_;

};
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
class Function : public name, public Parsing
{
public:

             Function           ()                  = delete;
    
    explicit Function           (const Function&);
    explicit Function           (Function&& other)  noexcept;
    explicit Function           (std::string&& name, const Safe_iterator& new_iter, std::size_t new_count);

    //use for declare new function
    void    add_vars            (std::vector<std::string>&& names);
    //till this

    double  call_func           (std::vector<double> params = std::vector<double>());//if function doesn't have any params

    const std::size_t get_count ()  const noexcept {return count_; };

private:

    const   Safe_iterator       func_iter_;
    std::size_t                 count_;

    void    ToStartPosition     ();                                                 //Use this!
    void    ClearExtraVariables ();                                                 //For class only, use ToStartPosition instead
};
////////////////////////////////////////////////////////////////////////////////////////////////


//EVERY FUNCTIONS
    static  std::vector <Function> functions_;
    static  std::vector <Variable> global_vars_;
//It's for only god help, I swear


//has been done!
//MAIN OBJECT FOR USER
////////////////////////////////////////////////////////////////////////////////////////////////
class Programm 
{
public:
            Programm            (std::string&& new_prog);
    double  Start               ();
private:

    bool    DeclarateFunctions  () noexcept;
    void    Preprocessor        ();

    //the same as Parsing_Tree function
    /////////////////////////////////////////////////////////////////////
    std::string Name            ();
    void    Spaces              ();
    void    SkipComments        ();
    
    //true if last symbol was found
    void    Skip                (char end);
    bool    LongSkip            (char end, char symbol);
    //also skip symbol 'end'

    bool    DoubleNumber        (double* num);
    bool    PureNumber          (int* num,      int* length = nullptr);
    /////////////////////////////////////////////////////////////////////

    std::string Read            (char end)              noexcept;
    bool    is_string           (const std::string&);

    //parameters
    Safe_iterator iter_;
    std::string programm_;
};
////////////////////////////////////////////////////////////////////////////////////////////////




//Help functions
////////////////////////////////////////////////////////////////////////////////////////////////
namespace pt
{
    bool    call_func           (const std::string& name,   double* returning = nullptr);
    bool    call_func           (const char* name,          double* returning = nullptr);
    bool    call_func           (const std::string& name,   std::vector<double> params,     double* returning);

    TypeVariable check_type     (const std::string& type);
}
////////////////////////////////////////////////////////////////////////////////////////////////