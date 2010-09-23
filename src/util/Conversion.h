#ifndef CONVERSION_H
#define CONVERSION_H

#include<string>
#include<sstream>

template<typename T>
std::string toString(const T& t)
{
    std::stringstream stream;
    stream << t;
    return stream.str();
}

#endif // CONVERSION_H
