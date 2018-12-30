#include <iostream>
#include <stdexcept>
#include <string>

#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

#include "serializer.hpp"

struct datname
{
    struct _alias_t
    {
        static constexpr const char _literal[] = "datname";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template <typename T>
        struct _member_t
        {
            T datname;
            T & operator()()
            {
                return datname;
            }
            const T & operator()() const
            {
                return datname;
            }
        };
    };
    using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::can_be_null>;
};

struct pg_database : sqlpp::table_t<pg_database, datname>
{
    struct _alias_t
    {
        static constexpr const char _literal[] = "pg_database";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template <typename T>
        struct _member_t
        {
            T pgDatabase;
            T & operator()()
            {
                return pgDatabase;
            }
            const T & operator()() const
            {
                return pgDatabase;
            }
        };
    };
};

void testStaticORMQuery(sqlpp::postgresql::connection & _db)
{
    auto tx = start_transaction(_db);

    const auto t = pg_database{};
    //auto statement = dynamic_select(_db).dynamic_columns(t.datname).from(t).dynamic_where();
    auto statement = select(t.datname).from(t).unconditionally();

    serializer printer = {};
    const auto result = serialize(statement, printer).str();
    std::cout << std::endl << "Executing [" << result << "]:" << std::endl;

    for(const auto & row : _db(statement))
    {
        std::cout << row.datname << std::endl;
    }

    tx.commit();
}
