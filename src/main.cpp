#include <iostream>
#include <stdexcept>
#include <string>

#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

void testStaticORMQuery(sqlpp::postgresql::connection & _db);
void testCustomPlainQuery(sqlpp::postgresql::connection & _db);

int main(int /*_argc*/, char ** /*_argv*/)
{
    try
    {
        auto config = std::make_shared<sqlpp::postgresql::connection_config>();
        config->host = "127.0.0.1";
        config->user = "postgres";
        config->password = "postgres";
        config->dbname = "tstcppdb";

        sqlpp::postgresql::connection db;

        try
        {
            db.connectUsing(config);
        }
        catch(const sqlpp::exception & _ex)
        {
            std::cerr << "Error: " << _ex.what() << std::endl;
            throw;
        }

        testStaticORMQuery(db);
        testCustomPlainQuery(db);
    }
    catch(std::exception const & _ex)
    {
        std::cerr << "Error: " << _ex.what() << std::endl;
        throw;
    }

    return 0;
}
