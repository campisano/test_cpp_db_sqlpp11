#ifndef SERIALIZER__HPP
#define SERIALIZER__HPP

#include <iostream>
#include <stdexcept>
#include <string>

#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

struct serializer
{
    std::ostringstream _os;

    serializer() = default;
    serializer(const serializer & rhs)
    {
        _os << rhs._os.str();
    }

    std::string str() const
    {
        return _os.str();
    }

    void reset()
    {
        _os.str("");
    }

    template <typename T>
    std::ostream & operator<<(T t)
    {
        return _os << t;
    }

    static std::string escape(std::string arg)
    {
        return serializer::escape(arg);
    }
};

#endif
