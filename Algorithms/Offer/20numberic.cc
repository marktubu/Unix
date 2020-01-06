#include <iostream>

bool scanUnsignedInteger(const char** str)
{
    if(str == nullptr)
        return false;

    const char* before = *str;
    while (*str != nullptr  && **str >= '0' && **str <= '9')
    {
        ++(*str);
    }
    
    return *str > before;
}

bool scanInteger(const char** str)
{
    if(**str == '+' || **str == '-')
        ++(*str);
    return scanUnsignedInteger(str);
}

bool isNumeric(const char* str)
{
    if(str == nullptr)
        return false;
    
    bool numeric = scanInteger(&str);

    if(*str == '.')
    {
        str++;
        numeric = scanUnsignedInteger(&str) || numeric;
    }
    
    if(*str == 'e' || *str == 'E')
    {
        str++;
        numeric = scanInteger(&str) && numeric;
    }
    
    return numeric && *str == '\0' ;
}