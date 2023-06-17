#include<string> // std::string
#include<iostream> // std::cout

struct LambdaError
{
    bool value = false;
    // false = no error
    // true = error

    auto what()
    {
        return string_;
    }

    LambdaError(std::string s)
    {
        string_ = s;
    }

    LambdaError()
    {
    }

    std::string string_{"nothing to see here."};
};

template<typename ErrorType>
struct LambdaCheck
{
    auto add(auto lambda)
    {
        try
        {
            lambda();
        }
        catch(ErrorType& e)
        {
            error = e.what();
            HasErrorHappened = true;
        }
    }

    auto check(LambdaError& error_)
    {
        error_.value = HasErrorHappened;
        if(HasErrorHappened)
        {
            std::cout << "---------------------------------------------------------------------\n"
                         "The function call LambdaCheck<ErrorType>{}(lambda){lambda()} failed\n"
                         "error.what() = " << error <<
                         "\n---------------------------------------------------------------------\n";
        }
        else
        {
            std::cout << "---------------------------------------------------------------------\n"
                         "The function call LambdaCheck<ErrorType>{}(lambda){lambda()} passed\n"
                         "With no errors\n"
                         "---------------------------------------------------------------------\n";
        }
    }
    
    // member variables.

    std::string error = {};
    bool HasErrorHappened = false;
};

int main()
{
    auto lambda_error = LambdaError{};
    auto lambda_throw = [](){/*throw LambdaError{};*/};
    LambdaCheck<LambdaError> l_e{};
    l_e.add(lambda_throw);
    l_e.check(lambda_error);
}
