#include "Parsing.h"

//Rules to correct data in the code:
//      1)In order to check current symbol use ONLY function Parsing::CheckSymbol(const char);
//IMPORTANT
//if you will add new mistake don't forget to add to count_mistakes in Names.h
//IMPORTANT


//What should I add:
//  1)Preprocessoring
//  2)The possibility of changing vars in other functions
//  3)More examples of using
//  4)List of mistakes that can be occured
//  5)Arrays


//DEFINES
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ERROR(num, string) /
    #define ERROR(num, string)          pt::print_error(num, string, __LINE__, iter_) 
#endif // !ERROR(num, string)

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////





            Parsing::Parsing            (const Safe_iterator& new_iter) :
            vars_(),
            iter_(new_iter)
{}


//standart library functions
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
bool        Parsing::STANDART_LIBRARY   (TypeVariable type)
{
    
    switch (type)
    {
    case TypeVariable::SHOW:
        return show();
        break;
    case TypeVariable::GET:
        return get();
        break;
    }
    return false;

}
bool        Parsing::show               ()
{

    Spaces();

    while (iter_.skip_if('$')) {

        if (iter_.skip_if('"')) {
            std::string reading = Read('"');
            if (!(++iter_))    //miss (") symbol
                ERROR(40, "Reading was till the end of file");

            std::cout << reading;
        }
        else {
            //read var
            double output = 0;
            if (!MathExpression(&output)) {
                ERROR(14, "no parameters for function (show)");
            }
            std::cout << output;
        }

        Spaces();
    }

    std::cout << std::endl;
    if (!iter_.skip_if(';')) {
        ERROR(15, "Symbol ; didn't found or maybe been forgot to use $!");
    }
    Spaces();

    return true;

}
bool        Parsing::get                () 
{

    Spaces();

    while (iter_.skip_if('$')) {

        std::string new_name = Name();
        if (new_name.empty()) {
            ERROR(18, "Function get didn't found anything to do!");
        }

        double new_data = 0;
        std::cin >> new_data;

        if (!CorrectDataVariable(new_data, new_name)) {
            if (new_name.empty())
                ERROR(17, std::string("Function get can't correct object that wasn't created!\t") + new_name);
            else
                ERROR(17, "Function get can't correct object that wasn't created!");
        }
    
        Spaces();
    }

    if (!iter_.skip_if(';')) {
        ERROR(15, "Symbol ; didn't found or maybe been forgot to use $!");
    }
    Spaces();
    return true;

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////



//condition functions
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
bool        Parsing::Condition          ()
{

    Spaces();
    if (!iter_.skip_if('[')) {
        ERROR(15, "Symbol [ afther 'if' didn't found or maybe been forgot to use!");
    }
    
    Spaces();
    const bool is_doing = CheckCondition();

    Spaces();
    if (!iter_.skip_if(']')) {
        ERROR(15, "Symbol ] didn't found or maybe been forgot to use!");
    }

    Spaces();
    if (!iter_.skip_if('{')) {
        ERROR(15, "Symbol { didn't found or maybe been forgot to use!");
    }

    Spaces();
    if (!is_doing)
        LongSkip('}', '{');
    else
        while (Action());

    Spaces();
    if (!iter_.skip_if('}')) {
        ERROR(15, "Symbol } didn't found or maybe been forgot to use!");
    }

    Spaces();
    std::string else_name = Name();
    
    if (!else_name.empty()) {

        if (else_name == "else") {

            Spaces();
            if (!iter_.skip_if('{')) {
                ERROR(15, "Symbol { didn't found or maybe been forgot to use after else!");
            }
            Spaces();

            if (is_doing)
                LongSkip('}', '{');
            else
                while (Action());

            Spaces();
            if (!iter_.skip_if('}')) {
                ERROR(15, "Symbol } didn't found or maybe been forgot to use after else!");
            }
            Spaces();
        }
        else {
            NameBack();
        }
    }

    return true;
}
bool        Parsing::CheckCondition     ()
{

    bool is_doing = false;
    OrCondition(&is_doing);
    return is_doing;

}

bool        Parsing::OrCondition        (bool* is_doing)
{

    if (is_doing == nullptr)
        return false;

    Spaces();
    if (!AndCondition(is_doing))
        return false;
    
    Spaces();
    while (iter_.is_symbol('o') && iter_.get_symbol(1) == 'r') {

        iter_.must_change(2);
            
        bool new_doing = false;
        if (!AndCondition(&new_doing)) {
            ERROR(19, "Waited continue of action!");
        }

        if (new_doing || *is_doing)
            *is_doing = true;
    }

    Spaces();
    return true;

}
bool        Parsing::AndCondition       (bool* is_doing)
{

    if (is_doing == nullptr)
        return false;

    Spaces();
    if (!BracketsCondition(is_doing))
        return false;
    Spaces();

    while (iter_.is_symbol('a') && iter_.get_symbol(1) == 'n' && iter_.get_symbol(2) == 'd') {

        iter_.must_change(3);

        bool new_doing = false;
        if (!BracketsCondition(&new_doing)) {
            ERROR(20, "Waited continue condition after 'and'!");
        }

        if (new_doing && *is_doing)
            *is_doing = true;
        else
            *is_doing = false;

    }

    Spaces();
    return true;

}
bool        Parsing::BracketsCondition  (bool* is_doing)
{

    if (is_doing == nullptr)
        return false;

    Spaces();

    if (iter_.skip_if('(')) {

        Spaces();
        if (!OrCondition(is_doing)) {
            ERROR(21, "Waited continue condition after bracket!");
        }
        Spaces();

        if (!iter_.skip_if(')')) {
            ERROR(22, "Waited closed bracket!");
        }
        Spaces();

        return true;
    }

    return PureCondition(is_doing);

}
bool        Parsing::PureCondition      (bool* is_doing)
{

    if (is_doing == nullptr)
        return false;

    double first = 0;
    double second = 0;

    Spaces();
    if (!MathExpression(&first))
        return false;
    Spaces();


    ComparingAction act = ComparingAction::Empty;
    switch (*iter_)
    {
    case '>':
        act = ComparingAction::Bigger;
        break;
    case '<':
        act = ComparingAction::Smaller;
        break;
    case '=':
        act = ComparingAction::Equal;
        break;
    case '!':
        ++iter_;
        if (!iter_.is_symbol('='))
            ERROR(15, "Waited symbol = for comparing!");

        act = ComparingAction::NotEqual;
        break;
    default:
        ERROR(6, "No such Comparison symbol!\n");
        break;
    }
    
    iter_.must_change(1); //miss comparing symbol
    
    Spaces();
    if (!MathExpression(&second)) {
        ERROR(36, "Waited math expression after comparison symbol!");
    }
    Spaces();


    switch (act)
    {
    case ComparingAction::Bigger:
        if (first > second)
            *is_doing = true;
        else
            *is_doing = false;
        break;
    case ComparingAction::Smaller:
        if (first < second)
            *is_doing = true;
        else
            *is_doing = false;
        break;
    case ComparingAction::Equal:
        if (first == second)
            *is_doing = true;
        else
            *is_doing = false;
        break;
    case ComparingAction::NotEqual:
        if (first != second)
            *is_doing = true;
        else
            *is_doing = false;
        break;
    default:
        ERROR(7, "Problem in PureCondition!\n");
        break;
    }

    return true;
}

bool        Parsing::Loop               ()
{
    
    Spaces();
    if (!iter_.skip_if('['))
        ERROR(15, "Waited symbol [ in loop!");
    Spaces();

    std::string::iterator start_pointer = iter_.get_iter();

    while (true) {

        const bool is_doing = CheckCondition();

        if (!iter_.skip_if(']'))
            ERROR(15, "Waited symbol ] in loop!");
        
        Spaces();
        if (!iter_.skip_if('{'))
            ERROR(15, "Waited symbol { in loop!");
        
        Spaces();
        if (!is_doing) {
            Skip('}');
            if (iter_.is_end())
                ERROR(15, "Waited symbol } in loop!");
            
            Spaces();
            break;
        }
        else {
            while (Action());
            Spaces();
            if (!iter_.skip_if('}'))
                ERROR(15, "Waited symbol } in loop!");
            Spaces();
        }

        iter_.move_to(start_pointer);
    }

    return true;

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////



//mathematical functions
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
bool        Parsing::MathExpression     (double* num)
{

    if (num == nullptr)
        return false;

    if (IsStopSymbol(*iter_))
        return false;


    if (!PlusMinus(num))
        return false;
    return true;

}

bool        Parsing::PlusMinus          (double* num)
{

    if (num == nullptr)
        return false;

    Spaces();
    if (!MultDiv(num))
        return false;

    Spaces();

    while (iter_.is_symbol('+') || iter_.is_symbol('-')) {
        
        const char current_operation = *iter_;
        ++iter_; //miss operation sign

        double new_value = 0;
        if (!MultDiv(&new_value)) {
            ERROR(23, "Waited expression after + or -");
        }

        if (current_operation == '+')
            *num += new_value;
        else
            *num -= new_value;
    }

    return true;

}
bool        Parsing::MultDiv            (double* num)
{

    if (num == nullptr)
        return false;

    Spaces();
    if (!Degree(num))
        return false;
    
    Spaces();
    while (iter_.is_symbol('*') || iter_.is_symbol('/')) {
        
        const char current_operation = *iter_;
        double new_value = 0;

        ++iter_;
        Spaces();
        if (!Degree(&new_value)) {
            ERROR(24, "Waited expression after * or /");
        }

        Spaces();
        if (current_operation == '*')
            *num *= new_value;
        else
            *num /= new_value;
    }

    return true;

}
bool        Parsing::Degree             (double* num)
{

    if (num == nullptr)
        return false;

    Spaces();
    if (!Brackets(num))
        return false;
    
    Spaces();
    while (iter_.is_symbol('^')) {

        const char current_operation = *iter_;
        double new_value = 0;
        
        ++iter_;
        Spaces();
        if (!Brackets(&new_value)) {
            ERROR(25, "Waited expression after ^");
        }
        Spaces();

        *num = pow(*num, new_value);
    }

    return true;

}

bool        Parsing::Brackets           (double* num)
{

    if (num == nullptr)
        return false;

    Spaces();

    if (iter_.skip_if('(')) {

        Spaces();
        if (!PlusMinus(num)) {
            ERROR(26, "Waited expression after (");
        }

        Spaces();
        if (!iter_.skip_if(')')) {
            ERROR(27, "Waited closed bracket!");
        }

        return true;
    }

    if (DoubleNumber(num))
        return true;

    Spaces();
    if (ReadFunction(num)) {
        return true;
    }
    
    Spaces();
    if (ReadVariable(num)) {
        return true;
    }
    else {
        ERROR(8, "Expression can't be undrstood!");
    }

    return false;

}

bool        Parsing::DoubleNumber       (double* num)
{

    if (num == nullptr)
        return false;

    Spaces();
    double sign = 1;
    if (iter_.skip_if('-')) {
        sign = -1;
    }

    int current_value = 0;
    if (!PureNumber(&current_value)) {
        if (sign == -1)
            --iter_;
        return false;
    }

    *num = static_cast<double>(current_value);

    if (iter_.skip_if('.')) {
        int length_fraq = 0;

        if (!PureNumber(&current_value, &length_fraq)) {
            ERROR(28, "Waited a number after '.' symbol in the number!");
            return false;
        }

        *num += static_cast<double>(current_value) / pow(10, length_fraq);
    }
    *num *= sign;

    return true;

}
bool        Parsing::PureNumber         (int* num, int* length /* = nullptr*/)
{

    if (num == nullptr)
        return false;

    char cur_sym = *iter_;
    if (cur_sym < '0' || cur_sym > '9')
        return false;

    int current_length = 0;
    *num = 0;

    while (cur_sym >= '0' && cur_sym <= '9') {
        *num = *num * 10 + (cur_sym - '0');
        if (!(++iter_))
            break;

        current_length++;
        cur_sym = *iter_;
    }

    if (length != nullptr)
        *length = current_length;

    return true;

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////



//work with variables
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
bool        Parsing::ReadVariable       (double* num)
{

    Spaces();
    std::string new_name = Name();
    if (new_name.empty())
        return false;

    Spaces();
    if (!GetDataVariable(new_name, num))
        return false;

    return true;

}
bool        Parsing::ReadFunction       (double* num) 
{

    if (!CallFunc(num)) {
        NameBack(); 
        return false;
    }
    
    return true;

}

std::vector<double> Parsing::ReadParameters(const std::size_t count_variables)
{

    //if was mistake from programmer
    if (count_variables == 0)
        return std::move(std::vector <double>());

    std::vector <double> params(count_variables);

    for (int i = 0; i < count_variables - 1; ++i) {

        Spaces();
        double new_num = 0;
        if (!MathExpression(&new_num)) {
            ERROR(12, "Parametr for function was waited!");
        }

        Spaces();
        if (!iter_.skip_if(',')) {
            ERROR(13, "Waited signed (,) in calling function");
        }

        params.at(i) = new_num;
    }

    Spaces();
    double new_num = 0;
    if (!MathExpression(&new_num)) {
        ERROR(12, "Parametr for function was waited!");
    }

    params.at(static_cast<std::size_t>(count_variables) - 1) = new_num;
    return std::move(params);
}

bool        Parsing::IsVariable         (const char* name)
{
    if (name == nullptr)
        return false;

    for (const auto& it : vars_) {
        if (it.is_equal_names(name))
            return true;
    }
    for (const auto& it : global_vars_) {
        if (it.is_equal_names(name))
            return true;
    }
    return false;
}
bool        Parsing::IsVariable         (const std::string& name)
{

    if (name.empty())
        return false;

    for (const auto& it : vars_) {
        if (it.is_equal_names(name))
            return true;
    }
    for (const auto& it : global_vars_) {
        if (it.is_equal_names(name))
            return true;
    }
    return false;
}
bool        Parsing::IsFunction         (const char* name)
{

    if (name == nullptr)
        return false;
    
    for (const auto& it : functions_) {
        if (it.is_equal_names(name))
            return true;
    }
    return false;
}
bool        Parsing::IsFunction         (const std::string& check_name)
{
    if (check_name.empty())
        return false;

    for (const auto& it : functions_) {
        if (it.is_equal_names(check_name))
            return true;
    }
    return false;
}

bool        Parsing::GetDataVariable    (const char* name,          double* num) //true if found
{
    if (name == nullptr || num == nullptr)
        return false;

    for (const auto& it : vars_) {
        if (it.is_equal_names(name)) {
            *num = it.get_data();
            return true;
        }
    }
    for (const auto& it : global_vars_) {
        if (it.is_equal_names(name)) {
            *num = it.get_data();
            return true;
        }
    }
    return false;
}
bool        Parsing::GetDataVariable    (const std::string& name,   double* num)
{

    if (num == nullptr || name.empty())
        return false;

    for (const auto& it : vars_) {
        if (it.is_equal_names(name)) {
            *num = it.get_data();
            return true;
        }
    }
    for (const auto& it : global_vars_) {
        if (it.is_equal_names(name)) {
            *num = it.get_data();
            return true;
        }
    }
    return false;

}

bool        Parsing::CorrectDataVariable(const double new_data,     const std::string& name)
{
    
    if (name.empty())
        return false;

    for (auto& it : vars_) {
        if (it.is_equal_names(name)) {
            it.correct_value(new_data);
            return true;
        }
    }
    for (auto& it : global_vars_) {
        if (it.is_equal_names(name)) {
            it.correct_value(new_data);
            return true;
        }
    }
    return false;

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////



//string functions
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

//check with method empty()
std::string  Parsing::Name              ()
{

    std::string new_name;
    char current_symbol = *iter_;

    if (    (current_symbol >= 'a' && current_symbol <= 'z')
        ||  (current_symbol >= 'A' && current_symbol <= 'Z')
        ||   current_symbol == '_') {

        const std::string::iterator start = iter_.get_iter();

        ++iter_;
        current_symbol = *iter_;
        while ((current_symbol >= 'a' && current_symbol <= 'z')
            || (current_symbol >= 'A' && current_symbol <= 'Z')
            || (current_symbol >= '0' && current_symbol <= '9')
            ||  current_symbol == '_') {

            if (!(++iter_)) //if the end of string
                break;
            current_symbol = *iter_;

        }
        
        new_name.append(start, iter_.get_iter());
    }

    return std::move(new_name);

}

TypeVariable Parsing::Type              ()
{

    Spaces();
    std::string new_type = Name();
    Spaces();

    if (new_type.empty()) {
        ERROR(30, "Identifier of action wasn't recognized!");
    }

    return pt::check_type(new_type);

}

//stops on the first letter of name that was backed
void        Parsing::NameBack           ()
{

    SpacesBack();
    if (!(--iter_))
        ERROR(43, "Can't name back!");
    char current_symbol = *iter_;

    while   (   (current_symbol >= 'a' && current_symbol <= 'z')
            ||  (current_symbol >= 'A' && current_symbol <= 'Z')
            ||   current_symbol == '_'
            ||  (current_symbol >= '0' && current_symbol <= '9')) {
        
        if (!(--iter_))
            break;

        current_symbol = *iter_;
    }

    ++iter_;//if it possible

}
void        Parsing::SpacesBack         ()
{

    --iter_;//in the end of function iter_++ in order to simplify algorithm
    char current_symbol = *iter_;

    while   (   current_symbol == ' '
            ||  current_symbol == '\n'
            ||  current_symbol == '\t') {
        
        if (!(--iter_))
            break;
        current_symbol = *iter_;
    }
    ++iter_;//stops on first space symbol

}
void        Parsing::Spaces             ()
{

    char current_symbol = *iter_;
    while (current_symbol == ' '
        || current_symbol == '\n'
        || current_symbol == '\t'
        || current_symbol == '#') {

        SkipComments();
        if (!(++iter_))
            break;
        current_symbol = *iter_;
    }
}
void        Parsing::SkipComments       ()
{

    if (iter_.skip_if('#')) {

        if (iter_.skip_if('{')) {
            while (!(iter_.is_symbol('}') && iter_.get_symbol(1) == '#')) {
                if (!(++iter_))
                    break;
            }
            if (!iter_.is_end())
                iter_ += 2;
        }
        else {

            while (!iter_.is_symbol('\n')) {
                if (!(++iter_)) //check for end
                    break;
            }
        }
    }

}

void        Parsing::Skip               (char end)
{

    char current_symbol = *iter_;

    while (current_symbol != end && current_symbol != '\0') {
        if (!(++iter_))
            break;

        current_symbol = *iter_;
    }
    ++iter_; //move if it can

}
bool        Parsing::LongSkip           (char end,      char symbol)
{

    int count = 0;

    char current_symbol = *iter_;

    while (count >= 0 && current_symbol != '\0') {
        if (current_symbol == symbol)
            count++;
        if (current_symbol == end) {
            if (count == 0)
                return true;
            count--;
        }

        if (!(++iter_))
            return false;

        current_symbol = *iter_;
    }
    return true;

}

std::string Parsing::Read               (char end) 
{
    
    std::string output;

    std::string::iterator start_iter = iter_.get_iter();
    while (!iter_.is_symbol(end)) {
        if (!(++iter_))
            break;
    }
    std::string::iterator end_iter = iter_.get_iter();
    
    if (start_iter != end_iter)
        output.append(start_iter, end_iter);

    return std::move(output);

}

bool        Parsing::IsStopSymbol       (const char symbol) noexcept
{
    switch (symbol)
    {
    case EOF:
        return true;
    case '\0':
        return true;
    case '[':
        return true;
    case ']':
        return true;
    case ')':
        return true;
    case '{':
        return true;
    case '}':
        return true;
    case '=':
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


//main functions 
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
bool        Parsing::Action()
{

    Spaces();
    if (IsStopSymbol(*iter_))
        return false;

    Spaces();
    const TypeVariable new_type = Type();

    if (new_type == TypeVariable::Result) {
        NameBack();
        return false;
    }

    if (new_type == TypeVariable::If) {
        return Condition();
    }

    if (new_type == TypeVariable::While) {
        return Loop();
    }

    if (STANDART_LIBRARY(new_type)) {
        return true;
    }

    if (new_type == TypeVariable::Empty && iter_.is_symbol('[')) {
        //we're backing to function name
        --iter_;
        NameBack();

        const bool out = CallFunc();
        if (!iter_.skip_if(';')) {
            ERROR(15, "Symbol ; was not found!");
        }
        return out;
    }

    if (new_type == TypeVariable::Empty || new_type == TypeVariable::New)
        return Variables(new_type);

    ERROR(9, "Type was found but wasn't done!\n");

    return false;

}
bool        Parsing::CallFunc           (double* num /*= nullptr*/)
{

    Spaces();
    std::string name_func = Name();

    if (name_func.empty())
        return false;

    if (!IsFunction(name_func))
        return false;

    //now it's definitely function

    Spaces();
    if (!iter_.skip_if('[')) {
        ERROR(15, "Symbol [ afther 'if' didn't found or maybe been forgot to use!");
    }

    const std::size_t count_variables = get_count_by_name(name_func);

    if (count_variables > 0) {
        std::vector <double> parameters = ReadParameters(count_variables);
        if (parameters.empty())
            ERROR(42, std::string("Parameters to the function were waiting\t") + name_func);

        pt::call_func(name_func, std::move(parameters), num);
    }
    else {
        //count_variables = 0
        pt::call_func(name_func, num);
    }

    Spaces();
    if (!iter_.skip_if(']')) {
        ERROR(15, "Symbol ] didn't found or maybe been forgot to use!");
    }

    return true;

}

bool        Parsing::Variables          (TypeVariable type)
{

    bool output = true;

    if (type == TypeVariable::Empty) {
        NameBack();
        Spaces();
        output = CorrectVariable();
    }
    if (type == TypeVariable::New)
        output = CreateVariable();
    
    Spaces();
    if (!iter_.skip_if(';')) {
        ERROR(16, "You forgot print ; !");
    }
    Spaces();
    return output;

}

bool        Parsing::CreateVariable     ()
{

    double num = 0;
    std::string new_name = Equation(&num);
    
    if (new_name.empty()) {
        ERROR(44, "Waited expression for creating variable!");
        return false;
    }

    if (IsVariable(new_name)) {
        ERROR(1, std::string("Redefinition variable ") + new_name);
    }

    vars_.push_back(Variable(num, TypeVariable::New, std::move(new_name)));
    
    return true;
}
bool        Parsing::CorrectVariable    ()
{

    double num = 0;
    std::string new_name = Equation(&num);
    if (new_name.empty())
        return false;

    if (!CorrectDataVariable(num, new_name)) {
        ERROR(2, std::string("Variable wasn't identified!\t") + new_name);
    }

    return true;

}

std::string Parsing::Equation           (double* num)
{

    Spaces();
    std::string variable = Name();
    Spaces();

    if (!variable.empty()) {

        if (!iter_.skip_if('=')) {
            ERROR(31, "Waited symbol = in the equation!");
        }
        Spaces();

        if (!MathExpression(num)) {
            ERROR(32, "Waited mathematical expression after symbol =");
        }
        Spaces();

    }
    return std::move(variable);

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////



//only for programmer
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void                Parsing::Dump               ()
{

    printf("\nDump is starting: \n");

    for (const auto& it : vars_) {
        std::cout << it.get_name() << "\t" << it.get_data() << std::endl;
    }

}
const std::size_t   Parsing::get_count_by_name  (const std::string& current_name)
{

    if (current_name.empty())
        ERROR(46, "Name for searching count of pararmeters wasn't found!");

    for (const auto& it : functions_) {
        if (it.is_equal_names(current_name))
            return it.get_count();
    }

    ERROR(46, "Name for searching count of pararmeters wasn't found!");
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////









//FUNCTION //STILL SHOULD BE CHANGED
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
            Function::Function          (std::string&& new_name, const Safe_iterator& new_iter, std::size_t new_count) :
            name        (std::move(new_name)),
            Parsing     (new_iter),
            func_iter_  (new_iter),
            count_      (new_count)
{}
            Function::Function          (const Function& other):
            name        (other.name_),
            Parsing     (other.iter_),
            func_iter_  (other.func_iter_),
            count_      (other.count_)
            {}
            
            Function::Function          (Function&& other) noexcept:
            name        (other.name_),
            Parsing     (other.iter_),
            func_iter_  (other.func_iter_),
            count_      (other.count_)
            {}

void        Function::add_vars(std::vector<std::string>&& names)
{

    std::size_t counter = 0;
    for (const auto& it : names) {

        counter++;
        if (counter > count_ || it.empty())
            ERROR(45, "Mistake in writing arguments to function!");

        std::string new_name = it;
        this->vars_.push_back(Variable(TypeVariable::New, std::move(new_name)));
    }
}

double      Function::call_func         (std::vector <double> params /*= std::vector<double>()*/)
{   

    if (!params.empty()) {
        //fill vars
        int ct = 0; //just countable parametr only in next loop
        for (auto& it : vars_) {
            it.correct_value(params.at(ct));
            ct++;

        }
    }

    while (Action());
    
    double final_result = 0;

    Spaces();
    std::string ending = Name();

    if (!ending.empty() && ending == "result") {
        Spaces();
        if (!MathExpression(&final_result)) {
            ERROR(32, "Waited expression after result!");
        }
        
        Spaces();
        if (!iter_.skip_if(';')) {
            ERROR(15, "Symbol ; didn't found or maybe been forgot to use $!");
        }
    }
    
    Spaces();
    
    if (!iter_.skip_if('}')) {
        ERROR(15, "Symbol } didn't found or maybe been forgot to use after else!");
    }

    ToStartPosition();
    return final_result;

}

void        Function::ToStartPosition   ()
{

    if (!(this->iter_ = func_iter_)) //return false if operation done incorrectly
        ERROR(39, "Problems with changing iterator in function!");
    ClearExtraVariables();

}
void        Function::ClearExtraVariables()
{

    const std::size_t size = vars_.size();
    
    //size > 0
    for (std::size_t i = count_; i < size; ++i) {
        vars_.pop_back();
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////






//PROGRAMM
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
            Programm::Programm          (std::string&& new_prog):
            iter_(new_prog.begin(), new_prog.end()),
            programm_()
{
    
    Preprocessor();
    if (programm_.empty())
        ERROR(47, "Problems with Preprocessoring!");

    iter_ = Safe_iterator(programm_.begin(), programm_.end());
    
    //just printing
    const std::string::iterator ending     = iter_.get_end();
    for (std::string::iterator start = iter_.get_begin(); start != ending; ++start) {
        std::cout << *start;
    }

}

double      Programm::Start             ()
{

    while (DeclarateFunctions());

    double main_returning = 0;
    if (!pt::call_func("main", &main_returning)) {
        ERROR(11, "Main function wasn't found");
    }

    return main_returning;

}
bool        Programm::DeclarateFunctions()  noexcept
{

    Spaces();
    if (iter_.is_end())
        return false;

    std::string new_func = Name();

    if (new_func.empty()) {
        ERROR(4, "Not understandable name of function!");
    }

    Spaces();
    if (!iter_.skip_if('[')) {
        ERROR(15, "Symbol [ afther 'if' didn't found or maybe been forgot to use!");
    }

    Spaces();
    int count_vars = 0;

    //check logic
    if (!PureNumber(&count_vars)) 
        ERROR(28, "Waited a number after symbol [!");
    if (count_vars < 0)
        ERROR(46, "Function can't get negative number of parameters!");

    Spaces();
    std::vector <std::string> names_vars;

    Spaces();
    for (int i = 0; i < count_vars; ++i) {
        if (!iter_.skip_if(',')) {
            ERROR(32, "Waited symbol , in declaration function");
        }
        
        Spaces();
        std::string new_name = Name();
        if (new_name.empty())
            ERROR(5, std::string("Problem with initializing parameters of function!\t") + new_func);
        
        names_vars.push_back(std::move(new_name)); //fast with move semantics
    }

    Spaces();
    if (!iter_.skip_if(']')) {
        ERROR(15, "Symbol ] didn't found or maybe been forgot to use!");
    }
    Spaces();
    if (!iter_.skip_if('{')) {
        ERROR(15, "Symbol { didn't found!");
    }

    functions_.push_back
    (Function   (std::move(new_func),   iter_,  static_cast<std::size_t>(count_vars) ) );

    if (count_vars > 0)
        functions_.back().
        add_vars(std::move(names_vars));
   
    if (!LongSkip('}', '{'))
        ERROR(38, "Symbol } wasn't found in right position!");

    Spaces();

    return true;

}

void        Programm::Preprocessor      ()
{

    //it's learning programm - i wanted to have a nice background of working with stl)

    std::map    <char, std::vector<int>>  first_symbol;                                             //comparing variables
    std::vector <std::string>             base;                                                     //changing names
    std::vector <std::string>             result;                                                   //new names
    int                                   count = 0;                                                //count of defines


    //key words for preprocessoring
    first_symbol.insert
        (std::pair<char, std::vector<int>>   ('#', std::vector<int>(1, -2)));
    first_symbol.insert    
        (std::pair<char, std::vector<int>>   ('\\', std::vector<int>(1, -1)));


    while(!iter_.is_end()) {
        
        
        auto cur_iter = first_symbol.find(*iter_);                                                  //check for key words

        if (cur_iter != first_symbol.end()) {                                                       //if it's one of the key words!
            /////////////////////////////////////////////////////////////////////////////////////
            if (cur_iter->second.at(0) == -2) {
                //it's committe
                Skip('\n');
            }
            /////////////////////////////////////////////////////////////////////////////////////
            else if (cur_iter->second.at(0) == -1) {                                                //probable new set
                
                ++iter_;    
                if (iter_.skip_if('\\')) {                                                          //definetely know set or not
                    //now definitely set
                    Spaces();

                    //check for "collusions" in first element
                    /**********************************************/
                    auto check_iter = first_symbol.find(*iter_);
                    if (check_iter == first_symbol.end()) {
                        first_symbol.insert
                        (std::pair<char, std::vector<int>>(*iter_, std::vector<int>(1, count)));
                    }
                    else {
                        (check_iter->second).push_back(count);
                    }
                    count++;
                    /***********************************************/

                    base.push_back
                        (Read('|')); //read till |

                    if (!iter_.skip_if('|'))
                        ERROR(48, "Waiting a symbol | after declaring defining");

                    Spaces();
                    result.push_back
                        (Read('\\'));
                    
                    if ( !(iter_.skip_if('\\')) || !(iter_.skip_if('\\')) )
                        ERROR(48, "Waiting a symbol \\\\ after declaring defining");
                }

                else {                                                                              //it's ordinary symbol but we missed a symbol earlier
                    programm_.push_back('\\');
                }

            }
            /////////////////////////////////////////////////////////////////////////////////////
            else {                                                                                  //probably a key!
      
                bool is_key = false;
                /************************************************************/
                for (const int& num : (cur_iter->second)/*it's vector in the map*/) {
                    if (is_string   (base.at(num))) {                                               //definetely a key
                                                                                                    //copying the result string at programm_
                        programm_.insert
                            (      programm_.end    (),
                            (result.at(num)).begin  (),
                            (result.at(num)).end    ());

                        is_key = true;
                        break;
                    }
                }
                /************************************************************/
                if (!is_key) {                                                                      //just an ordinary word
                    programm_.push_back(*iter_);
                    ++iter_;
                }
            }
            /////////////////////////////////////////////////////////////////////////////////////
        }
        /////////////////////////////////////////////////////////////////////////////////////////
        else {                                                                                      //if it's ordinary symbol
            programm_.push_back(*iter_);
            ++iter_;
        }
        /////////////////////////////////////////////////////////////////////////////////////////
    }
    return;
}


//check with method empty()
std::string  Programm::Name()
{

    std::string new_name;
    char current_symbol = *iter_;

    if ((current_symbol >= 'a' && current_symbol <= 'z')
        || (current_symbol >= 'A' && current_symbol <= 'Z')
        || current_symbol == '_') {

        const std::string::iterator start = iter_.get_iter();

        ++iter_;
        current_symbol = *iter_;
        while ((current_symbol >= 'a' && current_symbol <= 'z')
            || (current_symbol >= 'A' && current_symbol <= 'Z')
            || (current_symbol >= '0' && current_symbol <= '9')
            || current_symbol == '_') {

            if (!(++iter_))
                break;
            current_symbol = *iter_;

        }

        new_name.append(start, iter_.get_iter());
    }

    return std::move(new_name);

}

void        Programm::Spaces            ()
{

    char current_symbol = *iter_;
    while ( current_symbol == ' ' 
        ||  current_symbol == '\n' 
        ||  current_symbol == '\t' 
        ||  current_symbol == '#') {

        SkipComments();
        if (!(++iter_))
            break;
        current_symbol = *iter_;
    }
}
void        Programm::Skip              (char end)
{

    char current_symbol = *iter_;

    while (current_symbol != end && current_symbol != '\0') {
        if (!(++iter_))
            break;

        current_symbol = *iter_;
    }
    ++iter_; //move if it can

}
void        Programm::SkipComments      ()
{

    if (iter_.skip_if('#')) {

        if (iter_.skip_if('{')) {
            while (!(iter_.is_symbol('}') && iter_.get_symbol(1) == '#') ) {
                if (!(++iter_))
                    break;
            }
            if (!iter_.is_end())
                iter_ += 2;
        }
        else {

            while (!iter_.is_symbol('\n')) {
                if (!(++iter_)) //check for end
                    break;
            }
        }
    }

}
bool        Programm::LongSkip          (char end, char symbol)
{

    int count = 0;

    char current_symbol = *iter_;
    while (count >= 0 && current_symbol != '\0') {
        if (current_symbol == symbol)
            count++;
        if (current_symbol == end)
            count--;

        if (!(++iter_))
            return false;

        current_symbol = *iter_;
    }
    return true;

}

std::string Programm::Read              (char end) noexcept
{

    std::string output;

    std::string::iterator start_iter = iter_.get_iter();
    while (!iter_.is_symbol(end)) {
        if (!(++iter_))
            break;
    }
    std::string::iterator end_iter = iter_.get_iter();

    if (start_iter != end_iter)
        output.append(start_iter, end_iter);

    return std::move(output);

}

bool        Programm::DoubleNumber      (double* num)
{

    if (num == nullptr)
        return false;

    Spaces();
    double sign = 1;
    if (iter_.skip_if('-')) {
        sign = -1;
    }

    int current_value = 0;
    if (!PureNumber(&current_value)) {
        if (sign == -1)
            --iter_;
        return false;
    }

    *num = static_cast<double>(current_value);

    if (iter_.skip_if('.')) {
        int length_fraq = 0;

        if (!PureNumber(&current_value, &length_fraq)) {
            ERROR(28, "Waited a number after '.' symbol in the number!");
            return false;
        }

        *num += static_cast<double>(current_value) / pow(10, length_fraq);
    }
    *num *= sign;

    return true;

}
bool        Programm::PureNumber        (int* num,      int* length /* = nullptr*/)
{

    if (num == nullptr)
        return false;

    char cur_sym = *iter_;
    if (cur_sym < '0' || cur_sym > '9')
        return false;

    int current_length = 0;
    *num = 0;
    
    while (cur_sym >= '0' && cur_sym <= '9') {
        *num = *num * 10 + (cur_sym - '0');
        if (!(++iter_))
            break;
        
        current_length++;
        cur_sym = *iter_;
    }

    if (length != nullptr)
        *length = current_length;

    return true;

}

bool        Programm::is_string         (const std::string& other)
{

    const int                       our_size = static_cast<int>(other.size());
    std::string::iterator           cur_iter = iter_.get_iter   ();
    const std::string::iterator     end_iter = iter_.get_end    ();

    for (int i = 0; i < our_size && cur_iter != end_iter; ++i) {
        if (other.at(i) != *cur_iter) 
            return false;
       
        cur_iter++;
    }

    if (cur_iter != end_iter) {
        iter_.move_to(cur_iter);
        return true;
    }

    return false;

}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////












//NAMESPACE
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
bool        pt::call_func               (const std::string& name,   double* returning /*= nullptr*/)
{

    if (name.empty())
        return false;

    for (auto& it : functions_) {
        if (it.is_equal_names(name)) {
            if (returning == nullptr)
                it.call_func();
            else
                *returning = it.call_func();
            return true;
        }
    }
    return false;

}
bool        pt::call_func               (const char* name,          double* returning /*= nullptr*/)
{

    if (name == nullptr)
        return false;

    for (auto& it : functions_) {
        if (it.is_equal_names(name)) {
            if (returning == nullptr)
                it.call_func();
            else
                *returning = it.call_func();
            return true;
        }
    }
    return false;

}
bool        pt::call_func               (const std::string& name,   std::vector<double> params,     double* returning)
{

    if (name.empty() || params.empty())
        return false;

    for (auto& it : functions_) {
        if (it.is_equal_names(name)) {
            if (returning == nullptr)
                it.call_func(std::move(params));
            else
                *returning = it.call_func(std::move(params));
            return true;
        }
    }
    return false;

}

TypeVariable pt::check_type             (const std::string& type)
{

    if (type.empty())
        return TypeVariable::Empty;

    switch (type.front())
    {
    case 'n':
        if (type == "new")
            return TypeVariable::New;
        break;
    case 'i':
        if (type == "if")
            return TypeVariable::If;
        break;
    case 's':
        if (type == "show")
            return TypeVariable::SHOW;
        break;
    case 'g':
        if (type == "get")
            return TypeVariable::GET;
        break;
    case 'w':
        if (type == "while")
            return TypeVariable::While;
        break;
    case 'r':
        if (type == "result")
            return TypeVariable::Result;
        break;
    }

    return TypeVariable::Empty;
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////