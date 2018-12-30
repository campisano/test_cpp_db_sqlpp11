#include <iostream>
#include <stdexcept>
#include <string>

#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

#include "serializer.hpp"

void testCustomPlainQuery(sqlpp::postgresql::connection & _db)
{
    auto tx = start_transaction(_db);

    std::string sql =
        "SELECT typname, typlen, typinput, typoutput FROM pg_type LIMIT 5;";

    auto statement = custom_query(sqlpp::verbatim(sql))
        .with_result_type_of(select(
                                 sqlpp::value("").as(sqlpp::alias::a),
                                 sqlpp::value(0).as(sqlpp::alias::b),
                                 sqlpp::value("").as(sqlpp::alias::c),
                                 sqlpp::value("").as(sqlpp::alias::d)
                                 ));

    serializer printer = {};
    const auto result = serialize(statement, printer).str();
    std::cout << std::endl << "Executing [" << result << "]:" << std::endl;

    for(const auto & row : _db(statement))
    {
        std::cout << "name: " << row.a
                  << "\tlen: " << row.b
                  << "\tin: " << row.c
                  << "\tout: " << row.d << std::endl;
    }

    tx.commit();

}
