#pragma once
#include <string>

enum class Type {error, string, number};

class Typeless
{
public:

    Typeless();
    Typeless(const double t_initialValue);
    Typeless(const std::string& t_initialValue);

    //Operator Overrides
    Typeless& operator=(const Typeless& t_base);
    Typeless& operator=(const std::string& t_base);
    Typeless& operator=(const double t_base);

    Typeless& operator
private:
    Type m_type;
    std::string m_string;
    double m_number;
};